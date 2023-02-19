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
		if (nullptr == it->second)	//�����Ŵ����� �Ҹ��� ȣ�� ������ ����� ������ �ִٴ°� ��ü�� �����̹Ƿ� ����.
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
	if (allLevels_.end() == it)	//�ٲٷ��� ������ allLevels_�� ���ٸ� ����.
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
	if (nullptr != nextLevel_)	//nextLevel_�� �ִٸ� �� �������� curLevel_�� ��ü�Ѵ�.
	{
		if (nullptr != curLevel_)
		{
			//curLevel_->ClearLevel();
			//curLevel_->Load();
			//���⼭ �̷��� ������ �ϸ� ������ �𸣰����� �޸� ���� ���´�. 

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
		curLevel_->isReset_ = false;	//�ٽ� ���� ����.

		J_GameEngineTime::GetInstance().ResetTimer();	
	}

	//������Ʈ ����, ������ ���� ����.
	curLevel_->SortUpdateOrder();
	curLevel_->SortRenderOrder();

	//���� ������ ������Ʈ �Լ����� ȣ���Ѵ�.
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