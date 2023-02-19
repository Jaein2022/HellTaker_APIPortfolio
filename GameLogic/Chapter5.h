#pragma once
#include "Chapter.h"


class Demon;
class Chapter5: public Chapter
{
	Demon* zdrada_;

public:
	Chapter5();		//����Ʈ ������.
	~Chapter5();		//����Ʈ �Ҹ���.

public:
	Chapter5(const Chapter5& _other) = delete;		//����Ʈ ���������.
	Chapter5(Chapter5&& _other) = delete;		//����Ʈ rvalue ���������.

	Chapter5& operator=(const Chapter5& _other) = delete;		//����Ʈ ���Կ�����.
	Chapter5& operator=(const Chapter5&& _other) = delete;		//����Ʈ rvalue ���Կ�����.

public:
	void LoadLevel() override;
	void UpdateLevel() override;

private:
	void RespondSelection(int _index) override;
};

