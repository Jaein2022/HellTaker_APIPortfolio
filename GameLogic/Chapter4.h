#pragma once
#include "Chapter.h"

class Skeleton;
class Stone;
class Demon;
class Chapter4: public Chapter
{
	Demon* malina_;
public:
	Chapter4();		//����Ʈ ������.
	~Chapter4();		//����Ʈ �Ҹ���.

public:
	Chapter4(const Chapter4& _other) = delete;		//����Ʈ ���������.
	Chapter4(Chapter4&& _other) = delete;		//����Ʈ rvalue ���������.

	Chapter4& operator=(const Chapter4& _other) = delete;		//����Ʈ ���Կ�����.
	Chapter4& operator=(const Chapter4&& _other) = delete;		//����Ʈ rvalue ���Կ�����.

public:
	void LoadLevel() override;
	void UpdateLevel() override;

private:
	void RespondSelection(int _index) override;
};

