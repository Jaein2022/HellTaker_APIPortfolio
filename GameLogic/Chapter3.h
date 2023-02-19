#pragma once
#include "Chapter.h"

class Skeleton;
class Stone;
class Demon;
class Chapter3: public Chapter
{
	Demon* cerberus0_;
	Demon* cerberus1_;
	Demon* cerberus2_;

public:
	Chapter3();		//디폴트 생성자.
	~Chapter3();		//디폴트 소멸자.

public:
	Chapter3(const Chapter3& _other) = delete;		//디폴트 복사생성자.
	Chapter3(Chapter3&& _other) = delete;		//디폴트 rvalue 복사생성자.

	Chapter3& operator=(const Chapter3& _other) = delete;		//디폴트 대입연산자.
	Chapter3& operator=(const Chapter3&& _other) = delete;		//디폴트 rvalue 대입연산자.

public:
	void LoadLevel() override;
	void UpdateLevel() override;

private: 
	void RespondSelection(int _index) override;
};

