#pragma once
#include <J_GameEngineDebug.h>
#include <J_GameEngineNameBase.h>

enum class ACTORTYPE
{
	NONE = -1,	//����Ÿ���� �������� ���� ������ �ʱⰪ. �� ����Ÿ���� ����ϰ� �Ǹ� �� ���� ���ʹ� ������.
	INPLAY_UI,
	INPLAY_PLAYER,
	INPLAY_BACKGROUND,
	INPLAY_OBSTACLE,
	DIALOGUE_CHARACTER,
	DIALOGUE_BACKGROUND,
	DIALOGUE_QUOTE,
	DIALOGUE_UI,
	MAX
};

class J_ActorTag: public J_GameEngineNameBase
{
	ACTORTYPE actorType_;
	int updateOrder_;
	int renderOrder_;

public:
	J_ActorTag();	
	J_ActorTag(ACTORTYPE _actorType);
	~J_ActorTag();	

public:
	J_ActorTag(const J_ActorTag& _other) = delete;		//����Ʈ ���������.
	J_ActorTag(J_ActorTag&& _other) = delete;		//����Ʈ rvalue ���������.

	J_ActorTag& operator=(const J_ActorTag& _other) = delete;		//����Ʈ ���Կ�����.
	J_ActorTag& operator=(const J_ActorTag&& _other) = delete;		//����Ʈ rvalue ���Կ�����.

public:

	int GetUpdateOrder()
	{
		return updateOrder_;
	}
	int GetRenderOrder()
	{
		return renderOrder_;
	}
	ACTORTYPE GetActorType()
	{
		return actorType_;
	}
	void SetActorType(ACTORTYPE _actorType)
	{
		actorType_ = _actorType;
		SetOrdersAsActorType();
	}

private:
	void SetOrdersAsActorType();
};

