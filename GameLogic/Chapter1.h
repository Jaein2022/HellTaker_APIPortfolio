#pragma once
#include "Chapter.h"

class Demon;
class Chapter1: public Chapter
{
	Demon* pandemonica_;


public:
	Chapter1();				
	~Chapter1() override;		

public:
	Chapter1(const Chapter1& _other) = delete;		//디폴트 복사생성자.
	Chapter1(Chapter1&& _other) = delete;		//디폴트 rvalue 복사생성자.

	Chapter1& operator=(const Chapter1& _other) = delete;		//디폴트 대입연산자.
	Chapter1& operator=(const Chapter1&& _other) = delete;		//디폴트 rvalue 대입연산자.

public:
	void LoadLevel() override;
	void UpdateLevel() override;

private:
	void RespondSelection(int _index) override;
	
};

