#pragma once
#include "Chapter.h"

class Demon;
class Chapter6: public Chapter
{
	Demon* azazel_;

public:
	Chapter6();		//디폴트 생성자.
	~Chapter6();		//디폴트 소멸자.

public:
	Chapter6(const Chapter6& _other) = delete;		//디폴트 복사생성자.
	Chapter6(Chapter6&& _other) = delete;		//디폴트 rvalue 복사생성자.

	Chapter6& operator=(const Chapter6& _other) = delete;		//디폴트 대입연산자.
	Chapter6& operator=(const Chapter6&& _other) = delete;		//디폴트 rvalue 대입연산자.

public:
	void LoadLevel() override;
	void UpdateLevel() override;

private:
	void RespondSelection(int _index) override;
};

