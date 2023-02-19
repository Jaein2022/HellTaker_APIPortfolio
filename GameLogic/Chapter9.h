#pragma once
#include "Chapter.h"



class Chapter9: public Chapter
{

public:
	Chapter9();		//����Ʈ ������.
	~Chapter9();		//����Ʈ �Ҹ���.

public:
	Chapter9(const Chapter9& _other) = delete;		//����Ʈ ���������.
	Chapter9(Chapter9&& _other) = delete;		//����Ʈ rvalue ���������.

	Chapter9& operator=(const Chapter9& _other) = delete;		//����Ʈ ���Կ�����.
	Chapter9& operator=(const Chapter9&& _other) = delete;		//����Ʈ rvalue ���Կ�����.

public:
	void LoadLevel() override;
	void UpdateLevel() override;

private:
	void RespondSelection(int _index) override;
};

