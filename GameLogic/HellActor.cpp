#include "HellActor.h"
#include <J_GameEngineTime.h>
#include "Tile.h"
#include "Chapter.h"

//#include "HellActorTag.h"


HellActor::HellActor()
	: parentChapter_(nullptr), 
	curTile_(nullptr),
	curTileIndex_(float4::ZERO),
	destTile_(nullptr),
	destTileIndex_(float4::ZERO),
	movedDistanceRatio_(0.0f),
	direction_(float4::ZERO),
	isRight_(false),
	curState_(HellActorState::IDLE),
	myType_(ActorType::NONE)
{
}

HellActor::~HellActor()
{
}

void HellActor::ChangeDirection(const float4& _direction)
{
	if (HellActorState::IDLE != this->curState_)
	{
		return;
	}
	direction_ = _direction;
}

void HellActor::Idle()
{
	if (true == this->isRight_)
	{
		this->ChangeAnimation("idleR");
	}
	else
	{
		this->ChangeAnimation("idleL");
	}

	if (float4::ZERO != this->direction_)	//행동 방향이 정해졌으므로 무슨 행동을 할지 정한다.
	{
		ChangeState();
	}
	else
	{
		HellActorState::IDLE;
	}
}

void HellActor::Move()
{
	if (1.00f <= movedDistanceRatio_)	//이동 끝.
	{
		if (destTile_ == parentChapter_->leftTopTile_)			
			//이동이 끝나고 액터 위치와 타일 스테이트 리셋이 끝나면 다시 리셋하는것을 막는다.
		{
			if (true == this->IsActorAnimationFinish())			//해당 액터의 이동 애니메이션이 끝날때까지 액터스테이트 전환을 미룬다.
			{												
				movedDistanceRatio_ = 0.0f;					//이동거리 비율 초기화로 완전히 이동 절차를 끝낸다.
				this->curState_ = HellActorState::IDLE;		//모든 처리가 끝났으므로 IDLE로 스테이트 변경.
			}
			return;
		}

		direction_ = float4::ZERO;							//방향 초기화.

		this->SetActorPos(destTile_->GetActorPos());		//현재 액터의 위치가 어디든 destTile과 동일한 위치에 있게 한다.
		if (ActorType::HERO == myType_)
		{
			this->parentChapter_->SetCameraPos({0, this->actorPos_.IntY() - parentChapter_->GetChapter8CamPosY() });
		}

		curTile_->SetHellActor(nullptr);					//액터가 curTile에 더이상 있지 않으므로 curTile의 HellActorOnTile_를 비운다.

		SetTile(destTileIndex_);							//destTile을 curTile로 변경.						
		destTile_ = parentChapter_->leftTopTile_;			//destTile을 초기화한다.
		destTileIndex_ = float4::ZERO;						//destTileIndex 초기화.
	}
	else if(0.00f >= movedDistanceRatio_)	//이동 시작.
	{
		BeginMoving();

		movedDistanceRatio_ += J_GameEngineTime::GetInstance().GetDeltaTimeF() * 10.0f;
		this->SetActorPos(
			curTile_->GetActorPos() 
			+ (direction_ * 100.0f * movedDistanceRatio_)
		);

		if (ActorType::HERO == myType_)
		{
			this->parentChapter_->SetCameraPos({ 0, this->actorPos_.IntY() - parentChapter_->GetChapter8CamPosY() });
		}
	}
	else
	{
		//이동 중.
		if (true == isRight_)
		{
			this->ChangeAnimation("moveR");
		}
		else
		{
			this->ChangeAnimation("moveL");
		}

		movedDistanceRatio_ += J_GameEngineTime::GetInstance().GetDeltaTimeF() * 10.0f/*속도*/;
		this->SetActorPos(
			curTile_->GetActorPos()
			+ (direction_ * 100.0f/*이동거리*/ * movedDistanceRatio_)
		);

		if (ActorType::HERO == myType_)
		{
			this->parentChapter_->SetCameraPos({ 0, this->actorPos_.IntY() - parentChapter_->GetChapter8CamPosY() });
		}
	}
}

void HellActor::SetTile(int _x, int _y)	//타일 생성한 후 실행할 것.
{
	if (true == parentChapter_->IsAllTilesEmpty())
	{
		//타일 생성 먼저.
		J_GameEngineDebug::AssertFalse("Create tiles before place actor.");
		return;
	}

	if (0 > _x || 0 > _y)	//x와 y는 0보다 큰 정수로만.
	{
		J_GameEngineDebug::AssertFalse("x and y must be bigger than ZERO.");
		return;
	}

	if (parentChapter_->GetAllTilesSize().IntY() <= _y || parentChapter_->GetAllTilesSize().IntX() <= _x)
	{
		//액터는 allTiles_안에서만 존재할 것.
		J_GameEngineDebug::AssertFalse("x and y must be smaller than size of allTiles.");
		return;
	}

	if (TileState::WALL == parentChapter_->FindTile(_x, _y)->GetTileState())
	{
		//TileState::WALL은 아무것도 배치할 수 없는 타일.
		J_GameEngineDebug::AssertFalse("Actor cannot be placed on the wall.");
		return;
	}

	if (nullptr != parentChapter_->FindTile(_x, _y)->GetHellActor())
	{
		//액터가 이미 있는 타일에 다른 액터를 또 배치하는건 불가능.
		J_GameEngineDebug::AssertFalse("Other Actor already exists on this tile.");
		return;
	}

	curTile_ = parentChapter_->FindTile(_x, _y);
	curTileIndex_ = { _x, _y };
	SetActorPos(curTile_->GetActorPos());
	curTile_->SetHellActor(this);

	FinishMoving();
}

void HellActor::SetTile(const float4& _tileCoordinate)
{
	SetTile(_tileCoordinate.IntX(), _tileCoordinate.IntY());
}

void HellActor::SetCamEffectOn()
{
}

void HellActor::SetCamEffectOff()
{
}

void HellActor::ChangeState()
{
}

void HellActor::ChangeAnimation(const std::string& _anmationName, bool _isForceChange /*= true*/)
{
}

bool HellActor::IsActorAnimationFinish()
{
	return true;
}

void HellActor::BeginMoving()
{
}

void HellActor::FinishMoving()
{
	curTile_->SetHellActor(this);
}

void HellActor::Die()
{
}


