#pragma once
#include "Chapter.h"

class Demon;
class Chapter8: public Chapter
{
	Demon* lucifer_;

public:
	Chapter8();		//디폴트 생성자.
	~Chapter8();		//디폴트 소멸자.

public:
	Chapter8(const Chapter8& _other) = delete;		//디폴트 복사생성자.
	Chapter8(Chapter8&& _other) = delete;		//디폴트 rvalue 복사생성자.

	Chapter8& operator=(const Chapter8& _other) = delete;		//디폴트 대입연산자.
	Chapter8& operator=(const Chapter8&& _other) = delete;		//디폴트 rvalue 대입연산자.

public:
	void LoadLevel() override;
	void UpdateLevel() override;

private:
	void RespondSelection(int _index) override;
};

