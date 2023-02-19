#pragma once
#include "Chapter.h"

class Skeleton;
class Stone;
class Demon;
class Chapter3: public Chapter
{
	Demon* cerberus0_;
	Demon* cerberus1_;
	Demon* cerberus2_;

public:
	Chapter3();		//����Ʈ ������.
	~Chapter3();		//����Ʈ �Ҹ���.

public:
	Chapter3(const Chapter3& _other) = delete;		//����Ʈ ���������.
	Chapter3(Chapter3&& _other) = delete;		//����Ʈ rvalue ���������.

	Chapter3& operator=(const Chapter3& _other) = delete;		//����Ʈ ���Կ�����.
	Chapter3& operator=(const Chapter3&& _other) = delete;		//����Ʈ rvalue ���Կ�����.

public:
	void LoadLevel() override;
	void UpdateLevel() override;

private: 
	void RespondSelection(int _index) override;
};

