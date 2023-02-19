#pragma once
#include "Chapter.h"


class Demon;
class Chapter2: public Chapter
{
	
	Demon* modeus_;

public:
	Chapter2();		//����Ʈ ������.
	~Chapter2();		//����Ʈ �Ҹ���.

public:
	Chapter2(const Chapter2& _other) = delete;		//����Ʈ ���������.
	Chapter2(Chapter2&& _other) = delete;		//����Ʈ rvalue ���������.

	Chapter2& operator=(const Chapter2& _other) = delete;		//����Ʈ ���Կ�����.
	Chapter2& operator=(const Chapter2&& _other) = delete;		//����Ʈ rvalue ���Կ�����.

public:
	void LoadLevel() override;
	void UpdateLevel() override;

private:
	void RespondSelection(int _index) override;
};

