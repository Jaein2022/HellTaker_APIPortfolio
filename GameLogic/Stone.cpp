#include "Stone.h"
#include "Tile.h"
#include <J_Renderer.h>
#include <J_ImageFile.h>
#include <J_GameEngineTime.h>
#include <J_SoundManager.h>
#include <J_SoundPlayer.h>

Stone::Stone()
	: stone_Renderer_(nullptr),
	shakingTime_(0.0f),
	smallSpark_Renderer_(nullptr),
	spark_Renderer_(nullptr), 
	stoneKickSound_Player_(nullptr),
	stoneMoveSound_Player_(nullptr)
{
}

Stone::~Stone()
{
}

void Stone::Start()
{
	int stoneImageNumber = J_Arithmetic::Random().RandomInt(0, 8);
	stone_Renderer_ = CreateRenderer("stone" + std::to_string(stoneImageNumber)+ ".bmp", "stone_Renderer");
	stone_Renderer_->SetPivotPos({ 0, 5 });
	stone_Renderer_->SetActorImagePivot(RENDERPIVOT::BOT);


	smallSpark_Renderer_ = CreateRenderer("smallSpark.bmp", "smallSpark_Renderer");
	if (true == smallSpark_Renderer_->GetActorImage()->IsCuttingSizesEmpty())
	{
		smallSpark_Renderer_->GetActorImage()->CutImage({ 100, 100 });
	}
	smallSpark_Renderer_->CreateAnimation("smallSparkEffect0L", "smallSpark.bmp", 0, 3, false, 0.01f, RENDERPIVOT::CENTER);
	smallSpark_Renderer_->CreateAnimation("smallSparkEffect0R", "smallSpark.bmp", 4, 7, false, 0.01f, RENDERPIVOT::CENTER);
	smallSpark_Renderer_->CreateAnimation("smallSparkEffect1L", "smallSpark.bmp", 8, 11, false, 0.01f, RENDERPIVOT::CENTER);
	smallSpark_Renderer_->CreateAnimation("smallSparkEffect1R", "smallSpark.bmp", 12, 15, false, 0.01f, RENDERPIVOT::CENTER);
	//smallSpark_Renderer_->SetPivotPos({ ? , ? });

	spark_Renderer_ = CreateRenderer("spark.bmp", "spark_Renderer");
	if (true == spark_Renderer_->GetActorImage()->IsCuttingSizesEmpty())
	{
		spark_Renderer_->GetActorImage()->CutImage({ 228, 228 });
	}
	spark_Renderer_->CreateAnimation("sparkEffect0L", "spark.bmp", 0, 4, false, 0.01f, RENDERPIVOT::CENTER);
	spark_Renderer_->CreateAnimation("sparkEffect0R", "spark.bmp", 5, 9, false, 0.01f, RENDERPIVOT::CENTER);
	spark_Renderer_->CreateAnimation("sparkEffect1L", "spark.bmp", 10, 14, false, 0.01f, RENDERPIVOT::CENTER);
	spark_Renderer_->CreateAnimation("sparkEffect1R", "spark.bmp", 15, 19, false, 0.01f, RENDERPIVOT::CENTER);
	//spark_Renderer_->SetPivotPos({ ? , ? });



	if (nullptr == J_SoundManager::GetInstance().FindPlayer("stoneKickSound_Player"))
	{
		stoneKickSound_Player_ = J_SoundManager::GetInstance().CreatePlayer("stoneKickSound_Player");
		stoneKickSound_Player_->PushBackInAlbum("stone_kick_01.wav");
		stoneKickSound_Player_->PushBackInAlbum("stone_kick_02.wav");
		stoneKickSound_Player_->PushBackInAlbum("stone_kick_03.wav");
	}
	if (nullptr == stoneKickSound_Player_)
	{
		stoneKickSound_Player_ = J_SoundManager::GetInstance().FindPlayer("stoneKickSound_Player");
	}

	if (nullptr == J_SoundManager::GetInstance().FindPlayer("stoneMoveSound_Player"))
	{
		stoneMoveSound_Player_ = J_SoundManager::GetInstance().CreatePlayer("stoneMoveSound_Player");
		stoneMoveSound_Player_->PushBackInAlbum("stone_move_01.wav");
		stoneMoveSound_Player_->PushBackInAlbum("stone_move_02.wav");
		stoneMoveSound_Player_->PushBackInAlbum("stone_move_03.wav");
	}
	if (nullptr == stoneMoveSound_Player_)
	{
		stoneMoveSound_Player_ = J_SoundManager::GetInstance().FindPlayer("stoneMoveSound_Player");
	}


	SetUpdateOrder(3);
	SetRenderOrder(5);
}

void Stone::Update()
{
	switch (curState_)
	{
	case HellActorState::IDLE:
		Idle();
		break;

	case HellActorState::MOVE:
		Move();
		break;

	default:
		J_GameEngineDebug::AssertFalse();
		return;
	}

	if (0.0f < shakingTime_)
	{
		shakingTime_ -= J_GameEngineTime::GetInstance().GetDeltaTimeF();
	}
	else
	{
		shakingTime_ = 0.0f;
	}
}

void Stone::Render()
{
	if (0.0f < shakingTime_)
	{
		float4 shakingPivotPos = { J_Arithmetic::Random().RandomFloat(-75.0f, 75.0f) * shakingTime_,
			J_Arithmetic::Random().RandomFloat(-75.0f, 75.0f) * shakingTime_ };

		stone_Renderer_->SetPivotPos(shakingPivotPos);
	}
	stone_Renderer_->Render();
}

void Stone::BeginMoving()
{
	stoneMoveSound_Player_->ChangeCurSound(J_Arithmetic::Random().RandomInt(0,
		stoneMoveSound_Player_->GetAlbumSize() - 1));
	stoneMoveSound_Player_->PlayCurSound(1, true);

	stoneKickSound_Player_->ChangeCurSound(J_Arithmetic::Random().RandomInt(0,
		stoneKickSound_Player_->GetAlbumSize() - 1));
	stoneKickSound_Player_->PlayCurSound(1, true);
}

void Stone::ChangeState()
{
	destTileIndex_ = curTileIndex_ + direction_;
	destTile_ = parentChapter_->FindTile(destTileIndex_);
	if (nullptr == destTile_)
	{
		J_GameEngineDebug::AssertFalse();
		return;
	}

	if (nullptr == destTile_->GetHellActor())
	{
		if (TileState::WALL == destTile_->GetTileState())
		{
			direction_ = float4::ZERO;		//방향 초기화를 해주지 않으면 destTileState가 none으로 바뀌는 순간 자동으로 움직인다.
			shakingTime_ = 0.15f;
			stoneKickSound_Player_->ChangeCurSound(J_Arithmetic::Random().RandomInt(0,
				stoneKickSound_Player_->GetAlbumSize() - 1));
			stoneKickSound_Player_->PlayCurSound(1, true);
			curState_ = HellActorState::IDLE;
		}
		else
		{
			curState_ = HellActorState::MOVE;
		}
	}
	else
	{
		direction_ = float4::ZERO;		//방향 초기화를 해주지 않으면 destTileState가 none으로 바뀌는 순간 자동으로 움직인다.
		shakingTime_ = 0.15f;
		stoneKickSound_Player_->ChangeCurSound(J_Arithmetic::Random().RandomInt(0,
			stoneKickSound_Player_->GetAlbumSize() - 1));
		stoneKickSound_Player_->PlayCurSound(1, true);
		curState_ = HellActorState::IDLE;
	}
}
