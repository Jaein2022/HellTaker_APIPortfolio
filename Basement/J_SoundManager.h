#pragma once
#include <FMOD/fmod.hpp>
#pragma comment(lib, "FMOD\\fmod_vc.lib")		//릴리즈용으로 빌드된 코드.
#include "J_GameEngineDebug.h"
#include <string>
#include <map>

class J_SoundPlayer;
class J_SoundFile;
class J_SoundManager
{
	friend J_SoundFile;
	friend J_SoundPlayer;

	FMOD::System* soundSystem_;		//fmod가 제공하는 인터페이스.
	//사운드파일 그 자체가 아니라 사운드를 통제하는 기본 인터페이스.

	static J_SoundManager* instance_;
	std::map<std::string, J_SoundFile*> allSounds_;
	std::map<std::string, J_SoundPlayer*> allPlayers_;

private:
	J_SoundManager();		//디폴트 생성자.
	~J_SoundManager();		//디폴트 소멸자.

public:
	J_SoundManager(const J_SoundManager& _other) = delete;		//디폴트 복사생성자.
	J_SoundManager(J_SoundManager&& _other) = delete;				//디폴트 rvalue 복사생성자.

	J_SoundManager& operator=(const J_SoundManager& _other) = delete;		//디폴트 대입연산자.
	J_SoundManager& operator=(const J_SoundManager&& _other) = delete;		//디폴트 rvalue 대입연산자.

public: 
	void InitSoundSystem();
	void LoadIngameSound(const std::string& _name, const std::string& _path);
	J_SoundFile* FindSound(const std::string& _name);
	void PlaySoundOnce(const std::string& _name);
	J_SoundPlayer* CreatePlayer(const std::string& _playerName);
	J_SoundPlayer* CreatePlayer(const std::string& _playerName, const std::string& _soundName);
	J_SoundPlayer* FindPlayer(const std::string& _playerName);
	void UpdateSound();

public:
	static J_SoundManager& GetInstance()
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

