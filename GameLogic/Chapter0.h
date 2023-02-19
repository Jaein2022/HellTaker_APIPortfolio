#pragma once
#include "Chapter.h"

class Chapter0_BG;
class Chapter0: public Chapter
{
	Chapter0_BG* Chapter0_BG_;

public:
	Chapter0();		//디폴트 생성자.
	~Chapter0() override;		//디폴트 소멸자.

public:
	Chapter0(const Chapter0& _other) = delete;		//디폴트 복사생성자.
	Chapter0(Chapter0&& _other) = delete;		//디폴트 rvalue 복사생성자.

	Chapter0& operator=(const Chapter0& _other) = delete;		//디폴트 대입연산자.
	Chapter0& operator=(const Chapter0&& _other) = delete;		//디폴트 rvalue 대입연산자.

public:
	void LoadLevel() override;
	void UpdateLevel() override;
private:
	void RespondSelection(int _index) override;
};

