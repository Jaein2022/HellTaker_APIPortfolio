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

	if (float4::ZERO != this->direction_)	//�ൿ ������ ���������Ƿ� ���� �ൿ�� ���� ���Ѵ�.
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
	if (1.00f <= movedDistanceRatio_)	//�̵� ��.
	{
		if (destTile_ == parentChapter_->leftTopTile_)			
			//�̵��� ������ ���� ��ġ�� Ÿ�� ������Ʈ ������ ������ �ٽ� �����ϴ°��� ���´�.
		{
			if (true == this->IsActorAnimationFinish())			//�ش� ������ �̵� �ִϸ��̼��� ���������� ���ͽ�����Ʈ ��ȯ�� �̷��.
			{												
				movedDistanceRatio_ = 0.0f;					//�̵��Ÿ� ���� �ʱ�ȭ�� ������ �̵� ������ ������.
				this->curState_ = HellActorState::IDLE;		//��� ó���� �������Ƿ� IDLE�� ������Ʈ ����.
			}
			return;
		}

		direction_ = float4::ZERO;							//���� �ʱ�ȭ.

		this->SetActorPos(destTile_->GetActorPos());		//���� ������ ��ġ�� ���� destTile�� ������ ��ġ�� �ְ� �Ѵ�.
		if (ActorType::HERO == myType_)
		{
			this->parentChapter_->SetCameraPos({0, this->actorPos_.IntY() - parentChapter_->GetChapter8CamPosY() });
		}

		curTile_->SetHellActor(nullptr);					//���Ͱ� curTile�� ���̻� ���� �����Ƿ� curTile�� HellActorOnTile_�� ����.

		SetTile(destTileIndex_);							//destTile�� curTile�� ����.						
		destTile_ = parentChapter_->leftTopTile_;			//destTile�� �ʱ�ȭ�Ѵ�.
		destTileIndex_ = float4::ZERO;						//destTileIndex �ʱ�ȭ.
	}
	else if(0.00f >= movedDistanceRatio_)	//�̵� ����.
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
		//�̵� ��.
		if (true == isRight_)
		{
			this->ChangeAnimation("moveR");
		}
		else
		{
			this->ChangeAnimation("moveL");
		}

		movedDistanceRatio_ += J_GameEngineTime::GetInstance().GetDeltaTimeF() * 10.0f/*�ӵ�*/;
		this->SetActorPos(
			curTile_->GetActorPos()
			+ (direction_ * 100.0f/*�̵��Ÿ�*/ * movedDistanceRatio_)
		);

		if (ActorType::HERO == myType_)
		{
			this->parentChapter_->SetCameraPos({ 0, this->actorPos_.IntY() - parentChapter_->GetChapter8CamPosY() });
		}
	}
}

void HellActor::SetTile(int _x, int _y)	//Ÿ�� ������ �� ������ ��.
{
	if (true == parentChapter_->IsAllTilesEmpty())
	{
		//Ÿ�� ���� ����.
		J_GameEngineDebug::AssertFalse("Create tiles before place actor.");
		return;
	}

	if (0 > _x || 0 > _y)	//x�� y�� 0���� ū �����θ�.
	{
		J_GameEngineDebug::AssertFalse("x and y must be bigger than ZERO.");
		return;
	}

	if (parentChapter_->GetAllTilesSize().IntY() <= _y || parentChapter_->GetAllTilesSize().IntX() <= _x)
	{
		//���ʹ� allTiles_�ȿ����� ������ ��.
		J_GameEngineDebug::AssertFalse("x and y must be smaller than size of allTiles.");
		return;
	}

	if (TileState::WALL == parentChapter_->FindTile(_x, _y)->GetTileState())
	{
		//TileState::WALL�� �ƹ��͵� ��ġ�� �� ���� Ÿ��.
		J_GameEngineDebug::AssertFalse("Actor cannot be placed on the wall.");
		return;
	}

	if (nullptr != parentChapter_->FindTile(_x, _y)->GetHellActor())
	{
		//���Ͱ� �̹� �ִ� Ÿ�Ͽ� �ٸ� ���͸� �� ��ġ�ϴ°� �Ұ���.
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


