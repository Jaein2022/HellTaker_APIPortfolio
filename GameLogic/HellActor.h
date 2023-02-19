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

	Tile* curTile_;					//���� �ִ� Ÿ��.
	float4 curTileIndex_;

	Tile* destTile_;				//�̵��� Ÿ��.
	float4 destTileIndex_;

	float movedDistanceRatio_;		//��ü �Ÿ��� 1�� ������� �̵��� �Ÿ�.

	float4 direction_;				//�̵��� ����.
	bool isRight_;					//true == right, false == left.


	HellActorState curState_;		//���� ���� ����.
	ActorType myType_;				//����Ÿ��. ���� ��� �Ⱦ��� ����.

public:
	HellActor();		//����Ʈ ������.
	~HellActor() override;		//����Ʈ �Ҹ���.

public:
	HellActor(const HellActor& _other) = delete;		//����Ʈ ���������.
	HellActor(HellActor&& _other) = delete;		//����Ʈ rvalue ���������.

	HellActor& operator=(const HellActor& _other) = delete;		//����Ʈ ���Կ�����.
	HellActor& operator=(const HellActor&& _other) = delete;		//����Ʈ rvalue ���Կ�����.

public:
	void ChangeDirection(const float4& _direction);	//HellActor�鿡�� ������ �����ؼ� �̵��ϰ� �ϴ� �Լ�.
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
	void SetTile(int _x, int _y);					//Ÿ�� ������ �� ������ ��.
	void SetTile(const float4& _tileCoordinate);	//Ÿ�� ������ �� ������ ��.

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

