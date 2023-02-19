#pragma once
#include "Chapter.h"



class Chapter9: public Chapter
{

public:
	Chapter9();		//디폴트 생성자.
	~Chapter9();		//디폴트 소멸자.

public:
	Chapter9(const Chapter9& _other) = delete;		//디폴트 복사생성자.
	Chapter9(Chapter9&& _other) = delete;		//디폴트 rvalue 복사생성자.

	Chapter9& operator=(const Chapter9& _other) = delete;		//디폴트 대입연산자.
	Chapter9& operator=(const Chapter9&& _other) = delete;		//디폴트 rvalue 대입연산자.

public:
	void LoadLevel() override;
	void UpdateLevel() override;

private:
	void RespondSelection(int _index) override;
};

