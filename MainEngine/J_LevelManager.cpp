#include "J_LevelManager.h"
#include "J_Level.h"
#include "J_ImageManager.h"
#include <J_GameEngineTime.h>

J_LevelManager* J_LevelManager::instance_ = new J_LevelManager();

J_LevelManager::J_LevelManager() 
	: curLevel_(nullptr),
	nextLevel_(nullptr),
	allLevels_()
{
}

J_LevelManager::~J_LevelManager()
{
	for (std::map<std::string, J_Level*>::iterator it = allLevels_.begin(); it != allLevels_.end(); ++it)
	{
		if (nullptr == it->second)	//레벨매니저의 소멸자 호출 이전에 사라진 레벨이 있다는것 자체가 문제이므로 폭파.
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
	allLevels_.clear();
}

void J_LevelManager::ChangeCurLevel(const std::string& _levelName)
{
	std::map<std::string, J_Level*>::iterator it = allLevels_.find(_levelName);
	if (allLevels_.end() == it)	//바꾸려는 레벨이 allLevels_에 없다면 폭파.
	{
		J_GameEngineDebug::AssertFalse("J_LevelManager::ChangeCurLevel()-> allLevels_.end() == allLevels_.find(_levelName)");
		return;
	}
	else
	{
		nextLevel_ = it->second;
	}
}

void J_LevelManager::Update()
{
	if (nullptr != nextLevel_)	//nextLevel_이 있다면 이 시점에서 curLevel_로 교체한다.
	{
		if (nullptr != curLevel_)
		{
			//curLevel_->ClearLevel();
			//curLevel_->Load();
			//여기서 이렇게 리셋을 하면 이유는 모르겠지만 메모리 릭이 남는다. 

			curLevel_->isReset_ = true;
		}
		curLevel_ = nextLevel_;
		nextLevel_ = nullptr;
		J_GameEngineTime::GetInstance().ResetTimer();
	}

	if (nullptr == curLevel_)
	{
		J_GameEngineDebug::AssertFalse("J_LevelManager::Update()-> nullptr == curLevel_");
		return;
	}

	if (true == curLevel_->isReset_)
	{
		curLevel_->ClearLevel();
		curLevel_->Load();
		curLevel_->isReset_ = false;	//다시 리셋 방지.

		J_GameEngineTime::GetInstance().ResetTimer();	
	}

	//업데이트 순서, 렌더링 순서 정렬.
	curLevel_->SortUpdateOrder();
	curLevel_->SortRenderOrder();

	//현재 레벨의 업데이트 함수들을 호출한다.
	curLevel_->PreUpdateLevel();	
	curLevel_->UpdateLevel();
	curLevel_->PostUpdateLevel();	

	curLevel_->PreUpdateActors();	
	curLevel_->UpdateActors();
	curLevel_->PostUpdateActors();	


	curLevel_->Render();
	curLevel_->LevelRender();
	J_ImageManager::GetInstance().ChangeToBackBufferImage();
	curLevel_->RemoveActors();

}