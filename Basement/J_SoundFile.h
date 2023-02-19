#pragma once
#include "J_SoundManager.h"
#include "J_GameEngineNameBase.h"
#include <string>

class J_SoundPlayer;
class J_SoundManager;
class J_SoundFile: public J_GameEngineNameBase
{
	friend J_SoundManager;
	friend J_SoundPlayer;
	FMOD::Sound* sound_;


public:
	J_SoundFile();		//디폴트 생성자.
	~J_SoundFile();		//디폴트 소멸자.

public:
	J_SoundFile(const J_SoundFile& _other) = delete;		//디폴트 복사생성자.
	J_SoundFile(J_SoundFile&& _other) = delete;		//디폴트 rvalue 복사생성자.

	J_SoundFile& operator=(const J_SoundFile& _other) = delete;		//디폴트 대입연산자.
	J_SoundFile& operator=(const J_SoundFile&& _other) = delete;		//디폴트 rvalue 대입연산자.

public:
	bool LoadSoundFile(const std::string& _path);
};

