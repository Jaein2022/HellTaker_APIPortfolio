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
	J_SoundFile();		//����Ʈ ������.
	~J_SoundFile();		//����Ʈ �Ҹ���.

public:
	J_SoundFile(const J_SoundFile& _other) = delete;		//����Ʈ ���������.
	J_SoundFile(J_SoundFile&& _other) = delete;		//����Ʈ rvalue ���������.

	J_SoundFile& operator=(const J_SoundFile& _other) = delete;		//����Ʈ ���Կ�����.
	J_SoundFile& operator=(const J_SoundFile&& _other) = delete;		//����Ʈ rvalue ���Կ�����.

public:
	bool LoadSoundFile(const std::string& _path);
};

