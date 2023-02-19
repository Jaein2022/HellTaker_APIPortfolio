#include "Skeleton.h"
#include <J_Renderer.h>
#include <J_ImageFile.h>
#include "Tile.h"
#include <J_SoundManager.h>
#include <J_SoundPlayer.h>

Skeleton::Skeleton()
	: skeleton_Renderer_(nullptr),
	skeletonMoveSound_Player_(nullptr),
	skeletonDeadSound_Player_(nullptr)
{
}

Skeleton::~Skeleton()
{
}

void Skeleton::Start()
{
	skeleton_Renderer_ = CreateRenderer("skeleton.bmp", "skeleton_Renderer");
	skeleton_Renderer_->SetPivotPos(float4::ZERO);
	if (true == skeleton_Renderer_->GetActorImage()->IsCuttingSizesEmpty())
	{
		skeleton_Renderer_->GetActorImage()->CutImage({ 100, 100 });
	}
	skeleton_Renderer_->CreateAnimation("moveR", "skeleton.bmp", 0, 5, false, 0.05f, RENDERPIVOT::BOT);
	skeleton_Renderer_->CreateAnimation("moveL", "skeleton.bmp", 6, 11, false, 0.05f, RENDERPIVOT::BOT);
	skeleton_Renderer_->CreateAnimation("idleR", "skeleton.bmp", 12, 23, true, 0.065f, RENDERPIVOT::BOT);
	skeleton_Renderer_->CreateAnimation("idleL", "skeleton.bmp", 24, 35, true, 0.065f, RENDERPIVOT::BOT);
	skeleton_Renderer_->ChangeAnimation("idleL");	//curAnimation 초기화 안하면 터짐. 

	if (nullptr == J_SoundManager::GetInstance().FindPlayer("skeletonMoveSound_Player"))
	{
		skeletonMoveSound_Player_ = J_SoundManager::GetInstance().CreatePlayer("skeletonMoveSound_Player");
		skeletonMoveSound_Player_->PushBackInAlbum("enemy_kick_01.wav");
		skeletonMoveSound_Player_->PushBackInAlbum("enemy_kick_02.wav");
		skeletonMoveSound_Player_->PushBackInAlbum("enemy_kick_03.wav");
	}
	if (nullptr == skeletonMoveSound_Player_)
	{
		skeletonMoveSound_Player_ = J_SoundManager::GetInstance().FindPlayer("skeletonMoveSound_Player");
	}

	if (nullptr == J_SoundManager::GetInstance().FindPlayer("skeletonDeadSound_Player"))
	{
		skeletonDeadSound_Player_ = J_SoundManager::GetInstance().CreatePlayer("skeletonDeadSound_Player");
		skeletonDeadSound_Player_->PushBackInAlbum("enemy_die_01.wav");
		skeletonDeadSound_Player_->PushBackInAlbum("enemy_die_02.wav");
		skeletonDeadSound_Player_->PushBackInAlbum("enemy_die_03.wav");
	}
	if (nullptr == skeletonDeadSound_Player_)
	{
		skeletonDeadSound_Player_ = J_SoundManager::GetInstance().FindPlayer("skeletonDeadSound_Player");
	}


	SetUpdateOrder(3);
	SetRenderOrder(5);
}

void Skeleton::Update()
{
	if (TileState::THORN_UP == curTile_->GetTileState())
	{
		curState_ = HellActorState::DEAD;
	}

	switch (curState_)
	{
	case HellActorState::IDLE:
		Idle();
		break;

	case HellActorState::MOVE:
		Move();
		break;

	case HellActorState::DEAD:
		Die();
		break;


	default:
		J_GameEngineDebug::AssertFalse();
		return;
	}
}

void Skeleton::Render()
{
	skeleton_Renderer_->UpdateAnimation();
}

void Skeleton::SetCamEffectOn()
{
	skeleton_Renderer_->SetCameraEffectOn();
}

void Skeleton::SetCamEffectOff()
{
	skeleton_Renderer_->SetCameraEffectOff();
}

void Skeleton::ChangeState()
{
	//이동할 목적지에 따라서 스테이트가 달라진다.
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
			curState_ = HellActorState::DEAD;
		}
		else
		{
			curState_ = HellActorState::MOVE;
		}
	}
	else
	{
		curState_ = HellActorState::DEAD;
	}

	if (0 < direction_.IntX())
	{
		isRight_ = true;
	}
	else if (0 > direction_.IntX())
	{
		isRight_ = false;
	}
}

void Skeleton::ChangeAnimation(const std::string& _animationName, bool _isForceChange /*= true*/)
{
	if (true == skeleton_Renderer_->IsCurAnimationName(_animationName))
	{
		return;
	}
	skeleton_Renderer_->ChangeAnimation(_animationName, _isForceChange);
}

bool Skeleton::IsActorAnimationFinish()
{
	return skeleton_Renderer_->IsCurAnimationFinish();
}

void Skeleton::BeginMoving()
{
	skeletonMoveSound_Player_->ChangeCurSound(J_Arithmetic::Random().RandomInt(0,
		skeletonMoveSound_Player_->GetAlbumSize() - 1));
	skeletonMoveSound_Player_->PlayCurSound(1, true);
}

void Skeleton::FinishMoving()
{
	if (TileState::THORN_FIXED == curTile_->GetTileState() ||
		TileState::THORN_UP == curTile_->GetTileState())
	{
		curState_ = HellActorState::DEAD;
	}
	curTile_->SetHellActor(this);
}

void Skeleton::Die()
{
	//사망 이펙트 넣을 것.
	skeletonMoveSound_Player_->ChangeCurSound(J_Arithmetic::Random().RandomInt(0,
		skeletonMoveSound_Player_->GetAlbumSize() - 1));
	skeletonMoveSound_Player_->PlayCurSound(1, true);

	skeletonDeadSound_Player_->ChangeCurSound(J_Arithmetic::Random().RandomInt(0,
		skeletonDeadSound_Player_->GetAlbumSize() - 1));
	skeletonDeadSound_Player_->PlayCurSound(1, true);
	isDestroyed_ = true;
	curTile_->SetHellActor(nullptr);
}


