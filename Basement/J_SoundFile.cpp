#include "J_SoundFile.h"

J_SoundFile::J_SoundFile(): sound_(nullptr)
{
}

J_SoundFile::~J_SoundFile()
{
}

bool J_SoundFile::LoadSoundFile(const std::string& _path)
{
	if (FMOD_RESULT::FMOD_OK != J_SoundManager::GetInstance().soundSystem_->createSound(
			_path.c_str(),
			FMOD_DEFAULT,
			nullptr,
			&sound_)
		)
	{
		J_GameEngineDebug::AssertFalse();
		return false;
	}

	if (nullptr == sound_)
	{
		J_GameEngineDebug::AssertFalse();
		return false;
	}

	return true;
	
}


