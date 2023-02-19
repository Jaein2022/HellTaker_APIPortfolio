#pragma once
#include "Chapter.h"

class Skeleton;
class Stone;
class Demon;
class Chapter4: public Chapter
{
	Demon* malina_;
public:
	Chapter4();		//디폴트 생성자.
	~Chapter4();		//디폴트 소멸자.

public:
	Chapter4(const Chapter4& _other) = delete;		//디폴트 복사생성자.
	Chapter4(Chapter4&& _other) = delete;		//디폴트 rvalue 복사생성자.

	Chapter4& operator=(const Chapter4& _other) = delete;		//디폴트 대입연산자.
	Chapter4& operator=(const Chapter4&& _other) = delete;		//디폴트 rvalue 대입연산자.

public:
	void LoadLevel() override;
	void UpdateLevel() override;

private:
	void RespondSelection(int _index) override;
};

