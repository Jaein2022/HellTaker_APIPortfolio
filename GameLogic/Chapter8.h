#pragma once
#include "Chapter.h"

class Demon;
class Chapter8: public Chapter
{
	Demon* lucifer_;

public:
	Chapter8();		//����Ʈ ������.
	~Chapter8();		//����Ʈ �Ҹ���.

public:
	Chapter8(const Chapter8& _other) = delete;		//����Ʈ ���������.
	Chapter8(Chapter8&& _other) = delete;		//����Ʈ rvalue ���������.

	Chapter8& operator=(const Chapter8& _other) = delete;		//����Ʈ ���Կ�����.
	Chapter8& operator=(const Chapter8&& _other) = delete;		//����Ʈ rvalue ���Կ�����.

public:
	void LoadLevel() override;
	void UpdateLevel() override;

private:
	void RespondSelection(int _index) override;
};

