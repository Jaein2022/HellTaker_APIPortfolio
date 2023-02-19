#include "J_ActorTag.h"

J_ActorTag::J_ActorTag(): actorType_(ACTORTYPE::NONE), updateOrder_(0), renderOrder_(0)
{
}

J_ActorTag::J_ActorTag(ACTORTYPE _actorType): actorType_(_actorType), updateOrder_(0), renderOrder_(0)
{
	SetOrdersAsActorType();
}

J_ActorTag::~J_ActorTag()
{
}

void J_ActorTag::SetOrdersAsActorType()
{
	switch (actorType_)
	{
	case ACTORTYPE::NONE:
		J_GameEngineDebug::AssertFalse("NONE is actortype which is impossible to use.");
		return;
	case ACTORTYPE::INPLAY_UI:
		//renderOrder_ = n;
		//updateOrder_ = n;
		break;
	case ACTORTYPE::INPLAY_PLAYER:
		//renderOrder_ = n;
		//updateOrder_ = n;
		break;
	case ACTORTYPE::INPLAY_BACKGROUND:
		//renderOrder_ = n;
		//updateOrder_ = n;
		break;
	case ACTORTYPE::INPLAY_OBSTACLE:
		//renderOrder_ = n;
		//updateOrder_ = n;
		break;
	case ACTORTYPE::DIALOGUE_CHARACTER:
		//renderOrder_ = n;
		//updateOrder_ = n;
		break;
	case ACTORTYPE::DIALOGUE_BACKGROUND:
		//renderOrder_ = n;
		//updateOrder_ = n;
		break;
	case ACTORTYPE::DIALOGUE_QUOTE:
		//renderOrder_ = n;
		//updateOrder_ = n;
		break;
	case ACTORTYPE::DIALOGUE_UI:
		//renderOrder_ = n;
		//updateOrder_ = n;
		break;

	default:
		J_GameEngineDebug::AssertFalse("This is Wrong ActorType.");
		return;
	}
}
