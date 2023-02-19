#pragma once
#include <FMOD/fmod.hpp>
#pragma comment(lib, "FMOD\\fmod_vc.lib")		//����������� ����� �ڵ�.
#include "J_GameEngineDebug.h"
#include <string>
#include <map>

class J_SoundPlayer;
class J_SoundFile;
class J_SoundManager
{
	friend J_SoundFile;
	friend J_SoundPlayer;

	FMOD::System* soundSystem_;		//fmod�� �����ϴ� �������̽�.
	//�������� �� ��ü�� �ƴ϶� ���带 �����ϴ� �⺻ �������̽�.

	static J_SoundManager* instance_;
	std::map<std::string, J_SoundFile*> allSounds_;
	std::map<std::string, J_SoundPlayer*> allPlayers_;

private:
	J_SoundManager();		//����Ʈ ������.
	~J_SoundManager();		//����Ʈ �Ҹ���.

public:
	J_SoundManager(const J_SoundManager& _other) = delete;		//����Ʈ ���������.
	J_SoundManager(J_SoundManager&& _other) = delete;				//����Ʈ rvalue ���������.

	J_SoundManager& operator=(const J_SoundManager& _other) = delete;		//����Ʈ ���Կ�����.
	J_SoundManager& operator=(const J_SoundManager&& _other) = delete;		//����Ʈ rvalue ���Կ�����.

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

