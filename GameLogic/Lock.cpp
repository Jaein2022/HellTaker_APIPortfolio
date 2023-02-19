#include "Lock.h"
#include <J_Renderer.h>
#include <J_ImageFile.h>
#include "Tile.h"
#include <J_GameEngineTime.h>
#include <J_SoundManager.h>
#include <J_SoundPlayer.h>

Lock::Lock() 
	: lock_Renderer_(nullptr),
	radiant_Renderer_(nullptr),
	shakingTime_(0.0f),
	closedLockSound_Player_(nullptr),
	lockOpenningSound_Player_(nullptr)
{
}

Lock::~Lock()
{
	lock_Renderer_ = nullptr;
	radiant_Renderer_ = nullptr;
}

void Lock::Start()
{
	lock_Renderer_ = CreateRenderer("lockbox.bmp", "lock_Renderer");
	lock_Renderer_->SetPivotPos({ 0, 10 });
	lock_Renderer_->SetActorImagePivot(RENDERPIVOT::BOT);

	radiant_Renderer_ = CreateRenderer("radiant.bmp", "radiant_Renderer");
	if (true == radiant_Renderer_->GetActorImage()->IsCuttingSizesEmpty())
	{
		radiant_Renderer_->GetActorImage()->CutImage({ 340, 340 });
	}
	radiant_Renderer_->CreateAnimation("shine", "radiant.bmp", 0, 8, false, 0.05f, RENDERPIVOT::CENTER);
	radiant_Renderer_->ChangeAnimation("shine");
	radiant_Renderer_->SetPivotPos({ 0, -50 });

	if (nullptr == J_SoundManager::GetInstance().FindPlayer("lockOpenningSound_Player"))
	{
		lockOpenningSound_Player_ = J_SoundManager::GetInstance().CreatePlayer("lockOpenningSound_Player", "door_opening_01.wav");
	}
	if (nullptr == lockOpenningSound_Player_)
	{
		lockOpenningSound_Player_ = J_SoundManager::GetInstance().FindPlayer("lockOpenningSound_Player");
	}

	if (nullptr == J_SoundManager::GetInstance().FindPlayer("closedLockSound_Player"))
	{
		closedLockSound_Player_ = J_SoundManager::GetInstance().CreatePlayer("closedLockSound_Player");
		closedLockSound_Player_->PushBackInAlbum("door_closed_kick_01.wav");
		closedLockSound_Player_->PushBackInAlbum("door_closed_kick_02.wav");
		closedLockSound_Player_->PushBackInAlbum("door_closed_kick_03.wav");
	}
	if (nullptr == closedLockSound_Player_)
	{
		closedLockSound_Player_ = J_SoundManager::GetInstance().FindPlayer("closedLockSound_Player");
	}




	SetUpdateOrder(3);
	SetRenderOrder(5);
}

void Lock::Update()
{
	if (true == parentChapter_->IsHeroGotKey())
	{
		curTile_->SetHellActor(nullptr);
	}

	if (curTileIndex_ == parentChapter_->GetHeroCurTileIndex())
	{
		curState_ = HellActorState::DEAD;
	}

	switch (curState_)
	{
	case HellActorState::IDLE:
		Idle();
		break;

	case HellActorState::DEAD:
		Die();
		return;

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

void Lock::Render()
{
	if (HellActorState::DEAD == curState_)
	{
		radiant_Renderer_->UpdateAnimation();

		lockOpenningSound_Player_->PlayCurSound();

		return;
	}

	if (0.0f < shakingTime_)
	{
		float4 shakingPivotPos = { J_Arithmetic::Random().RandomFloat(-75.0f, 75.0f) * shakingTime_,
			J_Arithmetic::Random().RandomFloat(-75.0f, 75.0f) * shakingTime_ };
		lock_Renderer_->SetPivotPos(shakingPivotPos);
	}

	lock_Renderer_->Render();
}

void Lock::ChangeState()
{
	if (float4::ZERO != direction_)
	{
		direction_ = float4::ZERO;
		shakingTime_ = 0.15f;
		closedLockSound_Player_->ChangeCurSound(J_Arithmetic::Random().RandomInt(0, 
			closedLockSound_Player_->GetAlbumSize() - 1));
		closedLockSound_Player_->PlayCurSound(1, true);
	}
}

void Lock::Die()
{
	if (HellActorState::DEAD != curState_)
	{
		J_GameEngineDebug::AssertFalse();
		return;
	}

	if (true == radiant_Renderer_->IsCurAnimationFinish())
	{
		curTile_->SetHellActor(nullptr);
		isDestroyed_ = true;
	}
}


