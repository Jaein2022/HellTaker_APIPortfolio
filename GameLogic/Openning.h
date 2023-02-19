#pragma once
#include "Chapter.h"

class OpenningBG;
class Openning: public Chapter
{
	OpenningBG* openningBG_;

public:
	Openning();		//디폴트 생성자.
	~Openning();		//디폴트 소멸자.

public:
	Openning(const Openning& _other) = delete;		//디폴트 복사생성자.
	Openning(Openning&& _other) = delete;		//디폴트 rvalue 복사생성자.

	Openning& operator=(const Openning& _other) = delete;		//디폴트 대입연산자.
	Openning& operator=(const Openning&& _other) = delete;		//디폴트 rvalue 대입연산자.

public:
	void LoadLevel() override;
	void UpdateLevel() override;
};

