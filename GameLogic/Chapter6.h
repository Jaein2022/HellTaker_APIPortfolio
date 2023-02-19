#pragma once
#include "Chapter.h"

class Demon;
class Chapter6: public Chapter
{
	Demon* azazel_;

public:
	Chapter6();		//����Ʈ ������.
	~Chapter6();		//����Ʈ �Ҹ���.

public:
	Chapter6(const Chapter6& _other) = delete;		//����Ʈ ���������.
	Chapter6(Chapter6&& _other) = delete;		//����Ʈ rvalue ���������.

	Chapter6& operator=(const Chapter6& _other) = delete;		//����Ʈ ���Կ�����.
	Chapter6& operator=(const Chapter6&& _other) = delete;		//����Ʈ rvalue ���Կ�����.

public:
	void LoadLevel() override;
	void UpdateLevel() override;

private:
	void RespondSelection(int _index) override;
};

