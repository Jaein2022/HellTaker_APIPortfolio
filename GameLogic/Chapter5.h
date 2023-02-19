#pragma once
#include "Chapter.h"


class Demon;
class Chapter5: public Chapter
{
	Demon* zdrada_;

public:
	Chapter5();		//디폴트 생성자.
	~Chapter5();		//디폴트 소멸자.

public:
	Chapter5(const Chapter5& _other) = delete;		//디폴트 복사생성자.
	Chapter5(Chapter5&& _other) = delete;		//디폴트 rvalue 복사생성자.

	Chapter5& operator=(const Chapter5& _other) = delete;		//디폴트 대입연산자.
	Chapter5& operator=(const Chapter5&& _other) = delete;		//디폴트 rvalue 대입연산자.

public:
	void LoadLevel() override;
	void UpdateLevel() override;

private:
	void RespondSelection(int _index) override;
};

