#pragma once
#include "J_SoundManager.h"
#include <vector>
#include "J_GameEngineNameBase.h"



class J_SoundFile;
class J_SoundPlayer: public J_GameEngineNameBase
{
	friend J_SoundManager;
	J_SoundFile* curSound_;
	FMOD::Channel* playChannel_;
	int playCount_;

	std::vector<J_SoundFile*> album_;

private:
	J_SoundPlayer();		//����Ʈ ������.
	~J_SoundPlayer();		//����Ʈ �Ҹ���.

public:
	J_SoundPlayer(const J_SoundPlayer& _other) = delete;		//����Ʈ ���������.
	J_SoundPlayer(J_SoundPlayer&& _other) = delete;		//����Ʈ rvalue ���������.

	J_SoundPlayer& operator=(const J_SoundPlayer& _other) = delete;		//����Ʈ ���Կ�����.
	J_SoundPlayer& operator=(const J_SoundPlayer&& _other) = delete;		//����Ʈ rvalue ���Կ�����.

public:
	bool IsPlaying();
	void ResetPlayCount(int _count = -1);
	void PlayOverlap(const std::string& _name, int _loopCount = 1);	// ���ļ� ��� ������ ���尡 ����ǰ� �־ �׳� ����Ѵ�.
	void PlayAlone(const std::string& _name, int _loopCount = 1);	// ������ ���尡 ����� �����߸� ���� ���带 ����Ѵ�.
	void Stop();

	void PushBackInAlbum(const std::string& _name);
	bool IsCurSoundName(const std::string& _soundName);
	int GetAlbumSize();
	void PlayCurSound(int _loopCount = 1, bool _isOverlap = false);	
	void ChangeCurSound(int _albumIndex);
	
	bool IsPlayChannelEmpty()
	{
		return nullptr == playChannel_;
	}
};

