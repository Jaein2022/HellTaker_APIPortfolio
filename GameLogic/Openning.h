#pragma once
#include "Chapter.h"

class OpenningBG;
class Openning: public Chapter
{
	OpenningBG* openningBG_;

public:
	Openning();		//����Ʈ ������.
	~Openning();		//����Ʈ �Ҹ���.

public:
	Openning(const Openning& _other) = delete;		//����Ʈ ���������.
	Openning(Openning&& _other) = delete;		//����Ʈ rvalue ���������.

	Openning& operator=(const Openning& _other) = delete;		//����Ʈ ���Կ�����.
	Openning& operator=(const Openning&& _other) = delete;		//����Ʈ rvalue ���Կ�����.

public:
	void LoadLevel() override;
	void UpdateLevel() override;
};

