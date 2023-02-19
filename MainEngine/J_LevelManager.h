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
	J_LevelManager();		//디폴트 생성자.
	~J_LevelManager();		//디폴트 소멸자.

public:
	J_LevelManager(const J_LevelManager& _other) = delete;		//디폴트 복사생성자.
	J_LevelManager(J_LevelManager&& _other) = delete;			//디폴트 rvalue 복사생성자.

	J_LevelManager& operator=(const J_LevelManager& _other) = delete;		//디폴트 대입연산자.
	J_LevelManager& operator=(const J_LevelManager&& _other) = delete;		//디폴트 rvalue 대입연산자.

public:
	void ChangeCurLevel(const std::string& _levelName);
	void Update();

public:
	template<typename LevelType>
	void CreateLevel(const std::string& _levelName)
	{
		if (allLevels_.end() != allLevels_.find(_levelName))	//레벨명 중복검사.
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

