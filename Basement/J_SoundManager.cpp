#include "J_SoundManager.h"
#include "J_SoundFile.h"
#include "J_SoundPlayer.h"

J_SoundManager* J_SoundManager::instance_ = new J_SoundManager();

J_SoundManager::J_SoundManager(): soundSystem_(nullptr), allSounds_(), allPlayers_()
{
}

J_SoundManager::~J_SoundManager()
{
	for (std::map<std::string, J_SoundFile*>::iterator it = allSounds_.begin();
		it != allSounds_.end(); it++)
	{
		if (nullptr == it->second)
		{
			J_GameEngineDebug::AssertFalse("It is already removed");
		}
		else
		{
			delete it->second;
			it->second = nullptr;
		}
	}
	allSounds_.clear();


	for (std::map<std::string, J_SoundPlayer*>::iterator it = allPlayers_.begin();
		it != allPlayers_.end(); it++)
	{
		if (nullptr == it->second)
		{
			J_GameEngineDebug::AssertFalse("It is already removed");
		}
		else
		{
			delete it->second;
			it->second = nullptr;
		}
	}
	allPlayers_.clear();


	if (nullptr != soundSystem_)
	{
		soundSystem_->release();
		soundSystem_ = nullptr;
	}
}

void J_SoundManager::InitSoundSystem()
{
	FMOD::System_Create(&soundSystem_);
	if (nullptr == soundSystem_)
	{
		J_GameEngineDebug::AssertFalse("It is failed to create sound system.");
		return;
	}

	if (soundSystem_->init(32, FMOD_DEFAULT, nullptr))
	{
		J_GameEngineDebug::AssertFalse("It is failed to initialize sound system.");
		return;
	}
}

void J_SoundManager::LoadIngameSound(const std::string& _name, const std::string& _path)
{
	if (nullptr == soundSystem_)
	{
		J_GameEngineDebug::AssertFalse("The soundsystem is not initialized yet.");
		return;
	}

	if (nullptr != FindSound(_name))
	{
		J_GameEngineDebug::AssertFalse("The soundfile already exists.");
		return;
	}

	J_SoundFile* NewSoundFile = new J_SoundFile();
	if (nullptr == NewSoundFile)
	{
		J_GameEngineDebug::AssertFalse("It is failed to construct a soundfile.");
		return;
	}

	if (false == NewSoundFile->LoadSoundFile(_path))
	{
		delete NewSoundFile;
		J_GameEngineDebug::AssertFalse("It is failed to load a soundfile.");
		return;
	}

	NewSoundFile->SetName(_name);
	allSounds_.insert(std::map<std::string, J_SoundFile*>::value_type(_name, NewSoundFile));
}

J_SoundFile* J_SoundManager::FindSound(const std::string& _name)
{
	std::map<std::string, J_SoundFile*>::iterator it = allSounds_.find(_name);
	if (allSounds_.end() == it)
	{
		return nullptr;
	}
	return it->second;
}

void J_SoundManager::PlaySoundOnce(const std::string& _name)
{
	J_SoundFile* tempSound = J_SoundManager::GetInstance().FindSound(_name);
	if (nullptr == tempSound)
	{
		J_GameEngineDebug::AssertFalse("It is failed to construct a soundfile.");
		return;
	}

	soundSystem_->playSound(tempSound->sound_, nullptr, false, nullptr);
}

J_SoundPlayer* J_SoundManager::CreatePlayer(const std::string& _playerName)
{
	if (nullptr != FindPlayer(_playerName))
	{
		J_GameEngineDebug::AssertFalse("The sound player already exists.");
		return nullptr;
	}

	J_SoundPlayer* NewPlayer = new J_SoundPlayer();
	if (nullptr == NewPlayer)
	{
		J_GameEngineDebug::AssertFalse("It is failed to construct a sound player.");
		return nullptr;
	}
	NewPlayer->SetName(_playerName);
	allPlayers_.insert(std::map<std::string, J_SoundPlayer*>::value_type(_playerName, NewPlayer));
	return NewPlayer;
}

J_SoundPlayer* J_SoundManager::CreatePlayer(const std::string& _playerName, const std::string& _soundName)
{
	if (nullptr != FindPlayer(_playerName))
	{
		J_GameEngineDebug::AssertFalse("The sound player already exists.");
		return nullptr;
	}

	J_SoundPlayer* NewPlayer = new J_SoundPlayer();
	if (nullptr == NewPlayer)
	{
		J_GameEngineDebug::AssertFalse("It is failed to construct a sound player.");
		return nullptr;
	}
	NewPlayer->SetName(_playerName);
	NewPlayer->curSound_ = J_SoundManager::GetInstance().FindSound(_soundName);
	NewPlayer->album_.push_back(J_SoundManager::GetInstance().FindSound(_soundName));
	allPlayers_.insert(std::map<std::string, J_SoundPlayer*>::value_type(_playerName, NewPlayer));
	return NewPlayer;
}

J_SoundPlayer* J_SoundManager::FindPlayer(const std::string& _playerName)
{
	std::map<std::string, J_SoundPlayer*>::iterator it = allPlayers_.find(_playerName);
	if (allPlayers_.end() == it)
	{
		return nullptr;
	}
	return it->second;
}

void J_SoundManager::UpdateSound()
{
	if (nullptr == soundSystem_)
	{
		J_GameEngineDebug::AssertFalse("The soundsystem does not exist.");
		return;
	}

	soundSystem_->update();
}