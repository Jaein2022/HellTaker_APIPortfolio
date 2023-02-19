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
	Chapter1(const Chapter1& _other) = delete;		//����Ʈ ���������.
	Chapter1(Chapter1&& _other) = delete;		//����Ʈ rvalue ���������.

	Chapter1& operator=(const Chapter1& _other) = delete;		//����Ʈ ���Կ�����.
	Chapter1& operator=(const Chapter1&& _other) = delete;		//����Ʈ rvalue ���Կ�����.

public:
	void LoadLevel() override;
	void UpdateLevel() override;

private:
	void RespondSelection(int _index) override;
	
};

