#pragma once
#include <J_Actor.h>
#include "Chapter.h"

enum class HellActorState
{
	IDLE,
	MOVE,
	DEAD,
	PUSH,			
	WIN,
	MAX
};

class Tile;
class HellActor: public J_Actor
{
	friend Chapter;

protected:

	Chapter* parentChapter_;

	Tile* curTile_;					//현재 있는 타일.
	float4 curTileIndex_;

	Tile* destTile_;				//이동할 타일.
	float4 destTileIndex_;

	float movedDistanceRatio_;		//전체 거리를 1로 잡았을때 이동한 거리.

	float4 direction_;				//이동할 방향.
	bool isRight_;					//true == right, false == left.


	HellActorState curState_;		//액터 현재 상태.
	ActorType myType_;				//액터타입. 봐서 계속 안쓰면 삭제.

public:
	HellActor();		//디폴트 생성자.
	~HellActor() override;		//디폴트 소멸자.

public:
	HellActor(const HellActor& _other) = delete;		//디폴트 복사생성자.
	HellActor(HellActor&& _other) = delete;		//디폴트 rvalue 복사생성자.

	HellActor& operator=(const HellActor& _other) = delete;		//디폴트 대입연산자.
	HellActor& operator=(const HellActor&& _other) = delete;		//디폴트 rvalue 대입연산자.

public:
	void ChangeDirection(const float4& _direction);	//HellActor들에게 방향을 지시해서 이동하게 하는 함수.
	virtual void SetCamEffectOn();
	virtual void SetCamEffectOff();

public:

	Tile* GetCurTile() const
	{
		return curTile_;
	}

	ActorType GetMyType() const
	{
		return myType_;
	}


protected:
	void Idle();
	void Move();
	void SetTile(int _x, int _y);					//타일 생성한 후 실행할 것.
	void SetTile(const float4& _tileCoordinate);	//타일 생성한 후 실행할 것.

protected:

	virtual void ChangeState();
	virtual void ChangeAnimation(const std::string& _anmationName, bool _isForceChange = true);
	virtual bool IsActorAnimationFinish();
	virtual void BeginMoving();
	virtual void FinishMoving();
	virtual void Die();

protected:
	void SetParentChapter(Chapter* _parentChapter)
	{
		parentChapter_ = _parentChapter;
	}

private:
	void SetMyType(ActorType _myType)
	{
		myType_ = _myType;
	}




};

