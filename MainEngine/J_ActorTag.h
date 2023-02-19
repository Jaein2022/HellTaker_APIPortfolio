#pragma once
#include <J_GameEngineDebug.h>
#include <J_GameEngineNameBase.h>

enum class ACTORTYPE
{
	NONE = -1,	//액터타입이 설정되지 않은 액터의 초기값. 이 액터타입을 사용하게 되면 이 값의 액터는 사용금지.
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
	J_ActorTag(const J_ActorTag& _other) = delete;		//디폴트 복사생성자.
	J_ActorTag(J_ActorTag&& _other) = delete;		//디폴트 rvalue 복사생성자.

	J_ActorTag& operator=(const J_ActorTag& _other) = delete;		//디폴트 대입연산자.
	J_ActorTag& operator=(const J_ActorTag&& _other) = delete;		//디폴트 rvalue 대입연산자.

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

