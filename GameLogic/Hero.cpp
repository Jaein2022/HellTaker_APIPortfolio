#include "Hero.h"
#include <J_Renderer.h>
#include <J_Input.h>
#include <J_ImageFile.h>
#include "Tile.h"
#include <J_ImageManager.h>
#include <J_GameEngineTime.h>
#include <J_SoundManager.h>
#include <J_SoundPlayer.h>

Hero::Hero() 
	: moveLimit_(-1),
	fontSize_(500, 87),
	moveLimitFont_(nullptr),
	backBufferHDC_(NULL), 
	hero_Renderer_(nullptr),
	blood_Renderer_(nullptr), 
	thornDamageSound_Player_(nullptr), 
	heroMoveSound_Player_(nullptr), 
	isBleeding_(false), 
	isGotKey_(false),
	isWin_(false),
	justBlackBoard_(nullptr),
	heroDeath_Animation_(),
	heroDeathDelay_(0.05f), 
	curFrameDelay_(0.0f),
	curFrameIndex_(0), 
	heroDeath_ImagePivot_(360, 975),
	isHeroDeathFinish_(false),
	heroDeath_Player_(nullptr), 
	isHeroDeathCameffectOn_(false)
{
}

Hero::~Hero()
{
}

void Hero::Start()
{
	hero_Renderer_ = CreateRenderer("hero.bmp", "hero_Renderer");
	if (true == hero_Renderer_->GetActorImage()->IsCuttingSizesEmpty())
	{
		hero_Renderer_->GetActorImage()->CutImage({ 100, 200 });
	}
	hero_Renderer_->CreateAnimation("idleL", "hero.bmp", 0, 11, true, 0.065f);
	hero_Renderer_->CreateAnimation("idleR", "hero.bmp", 12, 23, true, 0.065f);
	hero_Renderer_->CreateAnimation("moveL", "hero.bmp", 24, 29, false, 0.03f);
	hero_Renderer_->CreateAnimation("moveR", "hero.bmp", 30, 35, false, 0.03f);
	hero_Renderer_->CreateAnimation("pushL", "hero.bmp", 36, 42, false, 0.03f);
	hero_Renderer_->CreateAnimation("pushR", "hero.bmp", 43, 49, false, 0.03f);
	hero_Renderer_->CreateAnimation("winL", "hero.bmp", 50, 84, false, 0.1f);
	hero_Renderer_->CreateAnimation("winR", "hero.bmp", 85, 119, false , 0.1f);
	hero_Renderer_->SetPivotPos(float4::ZERO);
	hero_Renderer_->ChangeAnimation("idleL");	//curAnimation 초기화 안하면 터짐. 

	blood_Renderer_ = CreateRenderer("blood.bmp", "blood_Renderer");
	if (true == blood_Renderer_->GetActorImage()->IsCuttingSizesEmpty())
	{
		blood_Renderer_->GetActorImage()->CutImage({ 340, 340 });
	}
	blood_Renderer_->CreateAnimation("bloodEffect0R", "blood.bmp", 0, 5, false, 0.075f );
	blood_Renderer_->CreateAnimation("bloodEffect0L", "blood.bmp", 6, 11, false, 0.075f);
	blood_Renderer_->CreateAnimation("bloodEffect1R", "blood.bmp", 12, 17, false, 0.075f);
	blood_Renderer_->CreateAnimation("bloodEffect1L", "blood.bmp", 18, 23, false, 0.075f);
	blood_Renderer_->CreateAnimation("bloodEffect2R", "blood.bmp", 24, 29, false, 0.075f);
	blood_Renderer_->CreateAnimation("bloodEffect2L", "blood.bmp", 30, 35, false, 0.075f);
	blood_Renderer_->SetPivotPos({0, 30});

	if (nullptr == J_SoundManager::GetInstance().FindPlayer("thornDamageSound_Player"))
	{
		thornDamageSound_Player_ = J_SoundManager::GetInstance().CreatePlayer("thornDamageSound_Player");
		thornDamageSound_Player_->PushBackInAlbum("spikes_damage_01.wav");
		thornDamageSound_Player_->PushBackInAlbum("spikes_damage_02.wav");
	}
	if (nullptr == thornDamageSound_Player_)
	{
		thornDamageSound_Player_ = J_SoundManager::GetInstance().FindPlayer("thornDamageSound_Player");
	}


	if (nullptr == J_SoundManager::GetInstance().FindPlayer("heroMoveSound_Player"))
	{
		heroMoveSound_Player_ = J_SoundManager::GetInstance().CreatePlayer("heroMoveSound_Player", "character_move_01.wav");
	}
	if (nullptr == heroMoveSound_Player_)
	{
		heroMoveSound_Player_ = J_SoundManager::GetInstance().FindPlayer("heroMoveSound_Player");
	}


	moveLimitFont_ = CreateFontA(	//폰트 생성 함수.
		500,						//폰트 세로길이
		87,							//폰트 폭. 
		GM_ADVANCED,				//??
		0,							//??
		FW_REGULAR,					//글씨 획 두께.
		false,						//true면 글씨 기울임.
		false,						//true면 글씨 밑줄.
		false,						//true면 글씨 중간선(취소선).
		DEFAULT_CHARSET,			//기본 영어 글자모음.
		OUT_DEFAULT_PRECIS,			//??
		CLIP_DEFAULT_PRECIS,		//??
		ANTIALIASED_QUALITY,		//글씨 디테일 퀄리티.
		DEFAULT_PITCH,				//????
		"Amiri Regular"				//폰트 이름.
	);
	if (NULL == moveLimitFont_)	//폰트 생성 실패. 폭파.
	{
		J_GameEngineDebug::AssertFalse();
		return;
	}

	backBufferHDC_ = J_ImageManager::GetInstance().GetBackBufferImage()->GetDC();	//백버퍼HDC를 가져온다.
	if (NULL == backBufferHDC_)	//가져오는데 실패하면 폭파.
	{
		J_GameEngineDebug::AssertFalse();
		return;
	}

	SetTextColor(backBufferHDC_, RGB(255, 255, 255));		//글씨 색 지정. 
	SetTextAlign(backBufferHDC_, TA_CENTER);				//글씨 정렬 세팅. TA_CENTER: 가로로 중앙 정렬.
	SetBkMode(backBufferHDC_, TRANSPARENT);					//글씨 배경모드 설정.
	//SetBkColor(backBufferHDC_, RGB(255, 0, 255));			//글씨 배경색 지정.


	justBlackBoard_ = J_ImageManager::GetInstance().FindImage("JustBlackBoard.bmp");

	if (true == heroDeath_Animation_.empty())
	{
		heroDeath_Animation_.reserve(18);
		for (int i = 0; i < 18; ++i)
		{
			heroDeath_Animation_.push_back(J_ImageManager::GetInstance().FindImage("death" + std::to_string(i) + ".bmp"));
		}
	}

	if (nullptr == J_SoundManager::GetInstance().FindPlayer("heroDeath_Player"))
	{
		heroDeath_Player_ = J_SoundManager::GetInstance().CreatePlayer("heroDeath_Player", "player_death_01.wav");
	}
	if (nullptr == heroDeath_Player_)
	{
		heroDeath_Player_ = J_SoundManager::GetInstance().FindPlayer("heroDeath_Player");
	}
	

	SetUpdateOrder(2);
	SetRenderOrder(9);

}

void Hero::Update()
{
	if (true == isWin_)
	{
		curState_ = HellActorState::WIN;
	}

	if (parentChapter_->IsGoal(curTileIndex_))	//골타일에 도착하면 즉시 대화창으로 전환.
	{
		if (false == parentChapter_->GetIsInDialogue())
		{
			parentChapter_->SetIsInDialogue(true);
		}
	}

	if (0 > moveLimit_)			//hero 이동횟수가 음수가 되면 즉시 사망.
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

	case HellActorState::PUSH:
		Push();
		break;

	case HellActorState::DEAD:
		Die();
		break;

	case HellActorState::WIN:
		Win();
		break;

	default:
		J_GameEngineDebug::AssertFalse();
		return;
	}
}

void Hero::Render()
{
	if (HellActorState::DEAD == curState_)
	{
		Render_HeroDeath();
		return;
	}

	if (0 < moveLimit_)
	{
		HGDIOBJ tempHandle = SelectObject(backBufferHDC_, moveLimitFont_);			//백버퍼HDC에 폰트 입력.
		SetTextColor(backBufferHDC_, RGB(255, 255, 255));
		TextOutA(
			backBufferHDC_,
			200,
			650,
			std::to_string(moveLimit_).c_str(),
			static_cast<int>(std::to_string(moveLimit_).size())
		);
		SelectObject(backBufferHDC_, tempHandle);
	}
	else if (0 == moveLimit_)
	{
		HGDIOBJ tempHandle = SelectObject(backBufferHDC_, moveLimitFont_);			//백버퍼HDC에 폰트 입력.
		SetTextColor(backBufferHDC_, RGB(255, 255, 255));
		TextOutA(
			backBufferHDC_,
			200,
			650,
			"X",
			1
		);
		SelectObject(backBufferHDC_, tempHandle);
	}

	hero_Renderer_->UpdateAnimation();

	if (true == isBleeding_ )
	{
		blood_Renderer_->UpdateAnimation();
		if (true == blood_Renderer_->IsCurAnimationFinish())
		{
			isBleeding_ = false;
		}
	}
}

void Hero::SetCamEffectOn()
{
	hero_Renderer_->SetCameraEffectOn();
	isHeroDeathCameffectOn_ = true;
}

void Hero::SetCamEffectOff()
{
	hero_Renderer_->SetCameraEffectOff();
	isHeroDeathCameffectOn_ = false;
}

void Hero::ChangeState()
{
	destTileIndex_ = curTileIndex_ + direction_;
	destTile_ = parentChapter_->FindTile(destTileIndex_);
	if (nullptr == destTile_)
	{
		J_GameEngineDebug::AssertFalse();
		return;
	}

	if (nullptr != destTile_->GetHellActor())
	{
		--moveLimit_;
		curState_ = HellActorState::PUSH;
		parentChapter_->SwitchThornUpDown();
	}
	else
	{
		if (TileState::WALL != destTile_->GetTileState())
		{
			--moveLimit_;
			parentChapter_->SwitchThornUpDown();
			curState_ = HellActorState::MOVE;
		}
		else
		{
			curState_ = HellActorState::IDLE;
		}
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

void Hero::ChangeAnimation(const std::string& _animationName, bool _isForceChange /*= false*/)
{
	if (true == hero_Renderer_->IsCurAnimationName(_animationName))
	{
		return;
	}
	hero_Renderer_->ChangeAnimation(_animationName, _isForceChange);
}

bool Hero::IsActorAnimationFinish()
{
	return hero_Renderer_->IsCurAnimationFinish();
}

void Hero::BeginMoving()
{
	heroMoveSound_Player_->PlayCurSound(1, true);
}

void Hero::FinishMoving()
{
	if (TileState::THORN_FIXED == curTile_->GetTileState() ||
		TileState::THORN_UP == curTile_->GetTileState())
	{
		--moveLimit_;
		isBleeding_ = true;
		if (true == isRight_)
		{
			blood_Renderer_->ChangeAnimation("bloodEffect" + std::to_string(J_Arithmetic::Random().RandomInt(0, 2)) 
				+ "R", true);
		}
		else
		{
			blood_Renderer_->ChangeAnimation("bloodEffect" + std::to_string(J_Arithmetic::Random().RandomInt(0, 2)) 
				+ "L", true);
		}

		thornDamageSound_Player_->ChangeCurSound(
			J_Arithmetic::Random().RandomInt(
				0,
				thornDamageSound_Player_->GetAlbumSize() - 1
			)
		);
		thornDamageSound_Player_->PlayCurSound(1, true);
	}
}

void Hero::Die()
{
	if (HellActorState::DEAD != curState_)	//Dead상태가 아닌데 여기 들어오면 폭파.
	{
		J_GameEngineDebug::AssertFalse();
		return;
	}

	if (true == isHeroDeathFinish_)		//애니메이션이 끝날때까지 리셋을 지연시킨다.
	{
		parentChapter_->ResetLevel();	//heroDeath 애니메이션이 끝나면 바로 리셋.
		return;
	}

	Update_HeroDeath();
}

void Hero::Push()
{
	if (true == hero_Renderer_->IsCurAnimationName("pushL") ||
		true == hero_Renderer_->IsCurAnimationName("pushR") )
	{
		if (true == hero_Renderer_->IsCurAnimationFinish())
		{
			//방향과 목적지, curState초기화.
			direction_ = float4::ZERO;
			destTileIndex_ = float4::ZERO;
			destTile_ = parentChapter_->leftTopTile_;
			curState_ = HellActorState::IDLE;
		}
		return;
	}

	if (TileState::THORN_FIXED == curTile_->GetTileState() ||
		TileState::THORN_UP == curTile_->GetTileState())
	{
		--moveLimit_;			//Push함수를 실행하는데 현재 타일이 가시 타일이라면 moveCount를 한번 더 깎는다.
		if (0 > moveLimit_)		//moveLimit가 0 아래라면 바로 DEAD로 상태 전환.
		{
			curState_ = HellActorState::DEAD;
			return;
		}

		thornDamageSound_Player_->ChangeCurSound(J_Arithmetic::Random().RandomInt(0, thornDamageSound_Player_->GetAlbumSize() - 1));
		thornDamageSound_Player_->PlayCurSound(1, true);

		if (true == isRight_)
		{
			blood_Renderer_->ChangeAnimation("bloodEffect" + std::to_string(J_Arithmetic::Random().RandomInt(0, 2)) + "R");
		}
		else
		{
			blood_Renderer_->ChangeAnimation("bloodEffect" + std::to_string(J_Arithmetic::Random().RandomInt(0, 2)) + "L");
		}
		isBleeding_ = true;
	}

	destTile_->GetHellActor()->ChangeDirection(direction_);	//Push 대상 액터에게 방향을 줘서 이동하게 한다.
	if (true == isRight_)
	{
		this->ChangeAnimation("pushR", true);
	}
	else
	{
		this->ChangeAnimation("pushL", true);
	}
}

void Hero::Win()
{
	if (true == hero_Renderer_->IsCurAnimationName("winL") ||
		true == hero_Renderer_->IsCurAnimationName("winR"))
	{
		if (true == hero_Renderer_->IsCurAnimationFinish())
		{
 			parentChapter_->ChangeToNextChapter();
		}
		return;
	}

	if (true == isRight_)
	{
		this->ChangeAnimation("winR", false);
	}
	else
	{
		this->ChangeAnimation("winL", false);
	}
}

void Hero::Update_HeroDeath()
{
	curFrameDelay_ -= J_GameEngineTime::GetInstance().GetDeltaTimeF();
	if (0.0f >= curFrameDelay_)
	{
		curFrameDelay_ = heroDeathDelay_;
		if (17 <= curFrameIndex_)
		{
			isHeroDeathFinish_ = true;
		}
		else
		{
			++curFrameIndex_;
			isHeroDeathFinish_ = false;
		}
	}
}

void Hero::Render_HeroDeath()
{
	J_ImageFile* backBufferImage = J_ImageManager::GetInstance().GetBackBufferImage();
	if (nullptr == backBufferImage)
	{
		J_GameEngineDebug::AssertFalse("bakcBufferImage is null.");
		return;
	}
	backBufferImage->Bitcopy(justBlackBoard_, justBlackBoard_->GetImageSize());

	float4 heroDeath_shakingPivotPos_ = //heroDeath 애니메이션을 재생할때 흔들리게 할 값.
		{ J_Arithmetic::Random().RandomFloat(-4.0f, 4.0f),
		J_Arithmetic::Random().RandomFloat(-4.0f, 4.0f) };	


	float4 renderPos = float4::ZERO;

	if (true == isHeroDeathCameffectOn_)
	{
		renderPos = GetCameraPos() - heroDeath_ImagePivot_ + heroDeath_shakingPivotPos_;
	}
	else
	{
		renderPos = GetActorPos() - heroDeath_ImagePivot_ + heroDeath_shakingPivotPos_;
	}

	backBufferImage->PasteOnBackBuffer(
		heroDeath_Animation_[curFrameIndex_],
		renderPos,
		heroDeath_Animation_[curFrameIndex_]->GetImageSize(),
		float4::ZERO,
		heroDeath_Animation_[curFrameIndex_]->GetImageSize()
	);

	heroDeath_Player_->PlayCurSound();
}
