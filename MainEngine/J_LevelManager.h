#pragma once
#include <J_GameEngineDebug.h>
#include <map>
#include <string>
#include "J_Level.h"

class J_LevelManager
{
	static J_LevelManager* instance_;

	J_Level* curLevel_;
	J_Level* nextLevel_;
	std::map<std::string, J_Level*> allLevels_;

private:
	J_LevelManager();		//����Ʈ ������.
	~J_LevelManager();		//����Ʈ �Ҹ���.

public:
	J_LevelManager(const J_LevelManager& _other) = delete;		//����Ʈ ���������.
	J_LevelManager(J_LevelManager&& _other) = delete;			//����Ʈ rvalue ���������.

	J_LevelManager& operator=(const J_LevelManager& _other) = delete;		//����Ʈ ���Կ�����.
	J_LevelManager& operator=(const J_LevelManager&& _other) = delete;		//����Ʈ rvalue ���Կ�����.

public:
	void ChangeCurLevel(const std::string& _levelName);
	void Update();

public:
	template<typename LevelType>
	void CreateLevel(const std::string& _levelName)
	{
		if (allLevels_.end() != allLevels_.find(_levelName))	//������ �ߺ��˻�.
		{
			J_GameEngineDebug::AssertFalse();
			return;
		}

		J_Level* NewLevel = new LevelType();
		NewLevel->SetName(_levelName);
		NewLevel->Load();
		allLevels_.insert(std::map<std::string, J_Level*>::value_type(_levelName, NewLevel));
	}

	static J_LevelManager& GetInstance()
	{
		return *instance_;
	}

	static void DestroyInstance()
	{
		if (nullptr == instance_)
		{
			J_GameEngineDebug::AssertFalse();
			return;
		}
		delete instance_;
		instance_ = nullptr;
	}


};

