#include "Demon.h"
#include <J_Renderer.h>
#include <J_ImageFile.h>
#include <J_SoundManager.h>
#include <J_SoundPlayer.h>

Demon::Demon(): demon_Renderer_(nullptr), loveSign_Renderer_(nullptr), demonDeadSound_Player_(nullptr), isWin_(false)
{
}

Demon::~Demon()
{
}

void Demon::Start()
{
	demon_Renderer_ = CreateRenderer(GetName() + ".bmp", "demon_Renderer");
	if (true == demon_Renderer_->GetActorImage()->IsCuttingSizesEmpty())
	{
		demon_Renderer_->GetActorImage()->CutImage({ 100, 100 });
	}
	demon_Renderer_->CreateAnimation("idle", GetName() + ".bmp", 0, 11, true, 0.065f);
	demon_Renderer_->ChangeAnimation("idle");


	loveSign_Renderer_ = CreateRenderer("loveSign.bmp", "loveSign_Renderer");
	loveSign_Renderer_->SetActorImagePivot(RENDERPIVOT::BOT);
	loveSign_Renderer_->SetPivotPos({ -50, -50 });

	if (nullptr == J_SoundManager::GetInstance().FindPlayer("demonDeadSound_Player"))
	{
		demonDeadSound_Player_ = J_SoundManager::GetInstance().CreatePlayer("demonDeadSound_Player", "succub_capture_01.wav");
	}
	if (nullptr == demonDeadSound_Player_)
	{
		demonDeadSound_Player_ = J_SoundManager::GetInstance().FindPlayer("demonDeadSound_Player");
		demonDeadSound_Player_->Stop();
	}


	SetUpdateOrder(3);
	SetRenderOrder(5);

}

void Demon::SetIsWin()
{
	isWin_ = true;
}

void Demon::Update()
{
	//한가할 때 러브사인렌더러 피벗포스값에 변화를 줘서 주기적으로 위아래로 움직이게 할 것.


	if (true == isWin_)
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
		break;

	default:
		J_GameEngineDebug::AssertFalse();
		return;
	}
}

void Demon::Render()
{
	demon_Renderer_->UpdateAnimation();
	loveSign_Renderer_->Render();
}

void Demon::SetCamEffectOn()
{
	demon_Renderer_->SetCameraEffectOn();
	loveSign_Renderer_->SetCameraEffectOn();
}

void Demon::SetCamEffectOff()
{
	demon_Renderer_->SetCameraEffectOff();
	loveSign_Renderer_->SetCameraEffectOff();
}

void Demon::Die()
{
	//if (false == demonDeadSound_Player_->IsPlayChannelEmpty() && false == demonDeadSound_Player_->IsPlaying())
	//{
	//	isDestroyed_ = true;
	//	return;
	//}
	demonDeadSound_Player_->PlayCurSound();
}

