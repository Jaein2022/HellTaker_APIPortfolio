#pragma once
#include "Chapter.h"


class Demon;
class Chapter2: public Chapter
{
	
	Demon* modeus_;

public:
	Chapter2();		//디폴트 생성자.
	~Chapter2();		//디폴트 소멸자.

public:
	Chapter2(const Chapter2& _other) = delete;		//디폴트 복사생성자.
	Chapter2(Chapter2&& _other) = delete;		//디폴트 rvalue 복사생성자.

	Chapter2& operator=(const Chapter2& _other) = delete;		//디폴트 대입연산자.
	Chapter2& operator=(const Chapter2&& _other) = delete;		//디폴트 rvalue 대입연산자.

public:
	void LoadLevel() override;
	void UpdateLevel() override;

private:
	void RespondSelection(int _index) override;
};

