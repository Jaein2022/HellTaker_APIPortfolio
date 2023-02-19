#pragma once
#include "Chapter.h"

class J_SoundPlayer;
class Demon;
class Chapter7: public Chapter
{
	Demon* justice_;
	//J_SoundPlayer* bgm_Player_;

public:
	Chapter7();		//디폴트 생성자.
	~Chapter7();		//디폴트 소멸자.

public:
	Chapter7(const Chapter7& _other) = delete;		//디폴트 복사생성자.
	Chapter7(Chapter7&& _other) = delete;		//디폴트 rvalue 복사생성자.

	Chapter7& operator=(const Chapter7& _other) = delete;		//디폴트 대입연산자.
	Chapter7& operator=(const Chapter7&& _other) = delete;		//디폴트 rvalue 대입연산자.

public:
	void LoadLevel() override;
	void UpdateLevel() override;

private:
	void RespondSelection(int _index) override;
};

