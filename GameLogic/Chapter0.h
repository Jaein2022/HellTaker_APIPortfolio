#pragma once
#include "Chapter.h"

class Chapter0_BG;
class Chapter0: public Chapter
{
	Chapter0_BG* Chapter0_BG_;

public:
	Chapter0();		//����Ʈ ������.
	~Chapter0() override;		//����Ʈ �Ҹ���.

public:
	Chapter0(const Chapter0& _other) = delete;		//����Ʈ ���������.
	Chapter0(Chapter0&& _other) = delete;		//����Ʈ rvalue ���������.

	Chapter0& operator=(const Chapter0& _other) = delete;		//����Ʈ ���Կ�����.
	Chapter0& operator=(const Chapter0&& _other) = delete;		//����Ʈ rvalue ���Կ�����.

public:
	void LoadLevel() override;
	void UpdateLevel() override;
private:
	void RespondSelection(int _index) override;
};

