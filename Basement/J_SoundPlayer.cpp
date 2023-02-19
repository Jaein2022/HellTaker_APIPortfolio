#include "J_SoundPlayer.h"
#include "J_SoundFile.h"
#include "J_SoundManager.h"

J_SoundPlayer::J_SoundPlayer(): curSound_(nullptr), playChannel_(nullptr), playCount_(-1), album_()
{
}

J_SoundPlayer::~J_SoundPlayer()
{
	album_.clear();
}

bool J_SoundPlayer::IsPlaying()
{
	if (nullptr == playChannel_)
	{
		J_GameEngineDebug::AssertFalse("Playchannel is nullptr.");
		return false;
	}

	bool ReturnValue;
	playChannel_->isPlaying(&ReturnValue);
	return ReturnValue;
}

void J_SoundPlayer::ResetPlayCount(int _count /*= -1*/)
{
	playCount_ = _count;
}

void J_SoundPlayer::PlayOverlap(const std::string& _name, int _loopCount /*= 1*/)
{
	J_SoundFile* tempSound = J_SoundManager::GetInstance().FindSound(_name);

	if (nullptr == tempSound)
	{
		J_GameEngineDebug::AssertFalse("PlaySound Error");
		return;
	}

	if (0 == playCount_)
	{
		return;
	}

	J_SoundManager::GetInstance().soundSystem_->playSound(
		tempSound->sound_
		, nullptr
		, false
		, &playChannel_);

	--playCount_;
	playChannel_->setLoopCount(_loopCount);
}

void J_SoundPlayer::PlayAlone(const std::string& _name, int _loopCount)
{
	J_SoundFile* tempSound = J_SoundManager::GetInstance().FindSound(_name);

	if (nullptr == tempSound)
	{
		J_GameEngineDebug::AssertFalse();
		return;
	}

	if (true == IsPlaying())
	{
		return;
	}

	if (0 == playCount_)
	{
		return;
	}

	J_SoundManager::GetInstance().soundSystem_->playSound(
		tempSound->sound_
		, nullptr
		, false
		, &playChannel_);

	--playCount_;
	playChannel_->setLoopCount(_loopCount);
}

void J_SoundPlayer::Stop()
{
	if (nullptr == playChannel_)
	{
		return;
	}

	playChannel_->stop();
	playChannel_ = nullptr;
}

void J_SoundPlayer::PushBackInAlbum(const std::string& _name)
{
	if (nullptr == J_SoundManager::GetInstance().FindSound(_name))
	{
		J_GameEngineDebug::AssertFalse();
		return;
	}

	album_.push_back(J_SoundManager::GetInstance().FindSound(_name));
}

bool J_SoundPlayer::IsCurSoundName(const std::string& _soundName)
{
	if (nullptr == curSound_)
	{
		J_GameEngineDebug::AssertFalse();
		return false;
	}
	return curSound_ == J_SoundManager::GetInstance().FindSound(_soundName);
}

int J_SoundPlayer::GetAlbumSize()
{
	return static_cast<int>(album_.size());
}

void J_SoundPlayer::PlayCurSound(int _loopCount /*= 1*/, bool _isOverlap /*= false*/)
{
	if (nullptr == curSound_)
	{
		J_GameEngineDebug::AssertFalse();
		return;
	}
	if (nullptr == curSound_->sound_)
	{
		J_GameEngineDebug::AssertFalse();
		return;
	}
	if (0 == playCount_)
	{
		return;
	}
	if (nullptr != playChannel_ && true == this->IsPlaying() && false == _isOverlap)
	{
		return;
	}

	J_SoundManager::GetInstance().soundSystem_->playSound(
		curSound_->sound_,
		nullptr,
		false,
		&playChannel_
	);
	--playCount_;
	playChannel_->setLoopCount(playCount_);
}

void J_SoundPlayer::ChangeCurSound(int _albumIndex)
{
	if (0 > _albumIndex || album_.size() - 1 < _albumIndex)
	{
		J_GameEngineDebug::AssertFalse("index is out of album size.");
		return;
	}
	curSound_ = album_[_albumIndex];
}


