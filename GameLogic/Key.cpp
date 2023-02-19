#include "Key.h"
#include <J_Renderer.h>
#include <J_ImageFile.h>
#include "Tile.h"
#include <J_SoundManager.h>
#include <J_SoundPlayer.h>

Key::Key(): key_Renderer_(nullptr), radiant_Renderer_(nullptr), keyPickingSound_Player_(nullptr)
{
}

Key::~Key()
{
}

void Key::Start()
{
	key_Renderer_ = CreateRenderer("key.bmp", "key_Renderer");
	if (true == key_Renderer_->GetActorImage()->IsCuttingSizesEmpty())
	{
		key_Renderer_->GetActorImage()->CutImage({ 100, 100 });
	}
	key_Renderer_->CreateAnimation("idle", "key.bmp", 0, 11, true, 0.05f, RENDERPIVOT::BOT);
	key_Renderer_->ChangeAnimation("idle");

	radiant_Renderer_ = CreateRenderer("radiant.bmp", "radiant_Renderer");
	if (true == radiant_Renderer_->GetActorImage()->IsCuttingSizesEmpty())
	{
		radiant_Renderer_->GetActorImage()->CutImage({ 340, 340 });
	}
	radiant_Renderer_->CreateAnimation("shine", "radiant.bmp", 0, 8, false, 0.05f, RENDERPIVOT::CENTER);
	radiant_Renderer_->ChangeAnimation("shine");
	radiant_Renderer_->SetPivotPos({ 0, -50 });

	if (nullptr == J_SoundManager::GetInstance().FindPlayer("keyPickingSound_Player"))
	{
		keyPickingSound_Player_ = J_SoundManager::GetInstance().CreatePlayer("keyPickingSound_Player", "key_pick_up_01.wav");
	}
	if (nullptr == keyPickingSound_Player_)
	{
		keyPickingSound_Player_ = J_SoundManager::GetInstance().FindPlayer("keyPickingSound_Player");
	}


	SetUpdateOrder(3);
	SetRenderOrder(5);
}

void Key::Update()
{
	if (curTileIndex_ == parentChapter_->GetHeroCurTileIndex())
	{
		curState_ = HellActorState::DEAD;
	}

	this->actorPos_;
	this->curTileIndex_;
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

void Key::Render()
{
	if (HellActorState::DEAD == curState_)
	{
		radiant_Renderer_->UpdateAnimation();
		keyPickingSound_Player_->PlayCurSound();
		return;
	}

	key_Renderer_->UpdateAnimation();
}

void Key::Die()
{	
	if (true == radiant_Renderer_->IsCurAnimationFinish())
	{
		curTile_->SetHellActor(nullptr);	
		parentChapter_->GiveKey();
		isDestroyed_ = true;
		return;
	}
	
}


