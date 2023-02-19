#include "J_Level.h"
#include "J_LevelManager.h"
#include "J_Actor.h"

J_Level::J_Level(): allActors_(), allActors_UpdateOrder_(), allActors_RenderOrder_(), isReset_(false), isLoaded_(false), cameraPos_(float4::ZERO)
{
	allActors_RenderOrder_.insert(std::map<int, std::list<J_Actor*>>::value_type(0, std::list<J_Actor*>()));
	allActors_UpdateOrder_.insert(std::map<int, std::list<J_Actor*>>::value_type(0, std::list<J_Actor*>()));
	//0번 리스트는 일단 생성, 삽입해 놓는다.
}

J_Level::~J_Level()
{
	//allActors_UpdateOrder_ 정리.
	for (std::map<int, std::list<J_Actor*>>::iterator it = allActors_UpdateOrder_.begin(); 
		it != allActors_UpdateOrder_.end(); ++it)
	{
		it->second.clear();	
	}
	allActors_UpdateOrder_.clear();

	//allActors_RenderOrder_ 정리, 해제.
	for (std::map<int, std::list<J_Actor*>>::iterator it = allActors_RenderOrder_.begin();
		it != allActors_RenderOrder_.end(); ++it)
	{
		it->second.clear();
	}
	allActors_RenderOrder_.clear();

	//allActors_ 정리.
	for (std::map<std::string, J_Actor*>::iterator it = allActors_.begin();
		it != allActors_.end(); ++it)
	{
		if (nullptr == it->second)
			//정식 삭제 절차를 거치지 않고 사라진 액터가 있다는 것은 문제 요소이므로 폭파.
		{
			J_GameEngineDebug::AssertFalse();
			continue;
		}
		else
		{
			delete it->second;
			it->second = nullptr;
		}
	}
	allActors_.clear();
}

void J_Level::ResetLevel()
{
	isReset_ = true;
}

J_Actor* J_Level::FindActor(const std::string& _actorName)
{
	std::map<std::string, J_Actor*>::iterator it = allActors_.find(_actorName);
	if (allActors_.end() == it)
	{
		J_GameEngineDebug::AssertFalse();
		return nullptr;
	}
	else
	{
		return it->second;
	}
}

void J_Level::Load()
{
	if (true == isLoaded_)	//이미 로드된 레벨을 또 로드하려고 하면 폭파.
	{
		J_GameEngineDebug::AssertFalse("J_Level::Load()-> true == isLoaded_");
		return;
	}
	else
	{
		LoadLevel();
		isLoaded_ = true;
	}
}

void J_Level::SortUpdateOrder()
{
	for (std::map<int, std::list<J_Actor*>>::iterator mapIt = allActors_UpdateOrder_.begin();
		mapIt != allActors_UpdateOrder_.end(); ++mapIt)
	{
		for (std::list<J_Actor*>::iterator listIt = mapIt->second.begin();
			listIt != mapIt->second.end(); ++listIt)
		{
			if (mapIt->first == (*listIt)->updateOrder_)
			{
				continue;	//순서가 맞다면 통과.
			}

			//순서가 안맞다면 여기선 일단 삽입만.
			if (allActors_UpdateOrder_.end() == allActors_UpdateOrder_.find((*listIt)->updateOrder_))
			{
				allActors_UpdateOrder_.insert(
					std::map<int, std::list<J_Actor*>>::value_type((*listIt)->updateOrder_, std::list<J_Actor*>()));
			}

			std::map<int, std::list<J_Actor*>>::iterator mapIt_inserted = allActors_UpdateOrder_.find((*listIt)->updateOrder_);
			mapIt_inserted->second.push_back((*listIt));
			//listIt-- = mapIt->second.erase(listIt);

		}
	}

	for (std::map<int, std::list<J_Actor*>>::iterator mapIt = allActors_UpdateOrder_.begin();
		mapIt != allActors_UpdateOrder_.end(); ++mapIt)
	{
		for (std::list<J_Actor*>::iterator listIt = mapIt->second.begin();
			listIt != mapIt->second.end(); )
		{
			if (mapIt->first == (*listIt)->updateOrder_)
			{
				++listIt;
				continue;	//순서가 맞다면 listIt를 다음으로 넘기고 통과.
			}

			//겹치는 것은 지운다.
			listIt = mapIt->second.erase(listIt);

		}
	}
}

void J_Level::UpdateActors()
{
	for (std::map<int, std::list<J_Actor*>>::iterator mapIt =  allActors_UpdateOrder_.begin();
		mapIt != allActors_UpdateOrder_.end(); ++mapIt)
	{
		for (std::list<J_Actor*>::iterator listIt = mapIt->second.begin();
			listIt != mapIt->second.end(); ++listIt)
		{
			(*listIt)->Update();
		}
	}
}

void J_Level::SortRenderOrder()
{
	for (std::map<int, std::list<J_Actor*>>::iterator mapIt = allActors_RenderOrder_.begin();
		mapIt != allActors_RenderOrder_.end(); ++mapIt)
	{
		for (std::list<J_Actor*>::iterator listIt = mapIt->second.begin();
			listIt != mapIt->second.end(); ++listIt)
		{
			if (mapIt->first == (*listIt)->renderOrder_)
			{
				continue;	//순서가 맞다면 통과.
			}

			//순서가 안맞아도 여기선 일단 삽입만.
			if (allActors_RenderOrder_.end() == allActors_RenderOrder_.find((*listIt)->renderOrder_))
			{
				allActors_RenderOrder_.insert(
					std::map<int, std::list<J_Actor*>>::value_type((*listIt)->renderOrder_, std::list<J_Actor*>()));

			}
			std::map<int, std::list<J_Actor*>>::iterator mapIt_inserted = allActors_RenderOrder_.find((*listIt)->renderOrder_);
			mapIt_inserted->second.push_back((*listIt));

		}
	}

	for (std::map<int, std::list<J_Actor*>>::iterator mapIt = allActors_RenderOrder_.begin();
		mapIt != allActors_RenderOrder_.end(); ++mapIt)
	{
		for (std::list<J_Actor*>::iterator listIt = mapIt->second.begin();
			listIt != mapIt->second.end(); )
		{
			if (mapIt->first == (*listIt)->renderOrder_)
			{
				++listIt;
				continue;	//순서가 맞다면 listIt를 뒤로 넘기고 통과.
			}

			//겹치는 것은 지운다.
			listIt = mapIt->second.erase(listIt);
		}
	}
}

void J_Level::Render()
{
	for (std::map<int, std::list<J_Actor*>>::iterator mapIt = allActors_RenderOrder_.begin();
		mapIt != allActors_RenderOrder_.end(); ++mapIt)
	{
		for (std::list<J_Actor*>::iterator listIt = mapIt->second.begin();
			listIt != mapIt->second.end(); ++listIt)
		{
			(*listIt)->Render();
		}
	}
}

void J_Level::RemoveActors()
{
	for (std::map<int, std::list<J_Actor*>>::iterator mapIt = allActors_UpdateOrder_.begin();
		mapIt != allActors_UpdateOrder_.end(); ++mapIt)
	{
		for (std::list<J_Actor*>::iterator listIt = mapIt->second.begin();
			listIt != mapIt->second.end();)
		{
			if (false == (*listIt)->isDestroyed_)
			{
				++listIt;
				continue;
			}
			listIt = mapIt->second.erase(listIt);
		}
	}

	for (std::map<int, std::list<J_Actor*>>::iterator mapIt = allActors_RenderOrder_.begin();
		mapIt != allActors_RenderOrder_.end(); ++mapIt)
	{
		for (std::list<J_Actor*>::iterator listIt = mapIt->second.begin();
			listIt != mapIt->second.end(); )
		{
			if (false == (*listIt)->isDestroyed_)
			{
				++listIt;
				continue;
			}
			listIt = mapIt->second.erase(listIt);
		}
	}

	for (std::map<std::string, J_Actor*>::iterator it = allActors_.begin();
		it != allActors_.end(); )
	{
		if (false == it->second->isDestroyed_)
		{
			++it;
			continue;
		}
		delete it->second;
		it->second = nullptr;
		it = allActors_.erase(it);
	}
}

void J_Level::ClearLevel()
{
	for (std::map<int, std::list<J_Actor*>>::iterator it = allActors_UpdateOrder_.begin();
		it != allActors_UpdateOrder_.end(); ++it)
	{
		it->second.clear();
	}
	allActors_UpdateOrder_.clear();	


	for (std::map<int, std::list<J_Actor*>>::iterator it = allActors_RenderOrder_.begin();
		it != allActors_RenderOrder_.end(); ++it)
	{
		it->second.clear();
	}
	allActors_RenderOrder_.clear();	

	for (std::map<std::string, J_Actor*>::iterator it = allActors_.begin();
		it != allActors_.end(); ++it)
	{
		if (nullptr == it->second)
			//정식 삭제 절차를 거치지 않고 사라진 액터가 있다는 것은 문제 요소이므로 폭파.
		{
			J_GameEngineDebug::AssertFalse();
			continue;
		}
		else
		{
			delete it->second;
			it->second = nullptr;
		}
	}
	allActors_.clear();	

	//0번 리스트는 다시 삽입.
	allActors_RenderOrder_.insert(std::map<int, std::list<J_Actor*>>::value_type(0, std::list<J_Actor*>()));
	allActors_UpdateOrder_.insert(std::map<int, std::list<J_Actor*>>::value_type(0, std::list<J_Actor*>()));
	cameraPos_ = float4::ZERO;	//카메라포스 초기화.
	isLoaded_ = false;			//레벨을 다시 로드해야 하므로 초기화.
}
