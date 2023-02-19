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
	J_SoundPlayer();		//디폴트 생성자.
	~J_SoundPlayer();		//디폴트 소멸자.

public:
	J_SoundPlayer(const J_SoundPlayer& _other) = delete;		//디폴트 복사생성자.
	J_SoundPlayer(J_SoundPlayer&& _other) = delete;		//디폴트 rvalue 복사생성자.

	J_SoundPlayer& operator=(const J_SoundPlayer& _other) = delete;		//디폴트 대입연산자.
	J_SoundPlayer& operator=(const J_SoundPlayer&& _other) = delete;		//디폴트 rvalue 대입연산자.

public:
	bool IsPlaying();
	void ResetPlayCount(int _count = -1);
	void PlayOverlap(const std::string& _name, int _loopCount = 1);	// 겹쳐서 재생 기존의 사운드가 재생되고 있어도 그냥 재생한다.
	void PlayAlone(const std::string& _name, int _loopCount = 1);	// 기존의 사운드가 재생이 끝나야만 다음 사운드를 재생한다.
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

