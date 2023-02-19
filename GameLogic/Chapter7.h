#pragma once
#include "Chapter.h"

class J_SoundPlayer;
class Demon;
class Chapter7: public Chapter
{
	Demon* justice_;
	//J_SoundPlayer* bgm_Player_;

public:
	Chapter7();		//����Ʈ ������.
	~Chapter7();		//����Ʈ �Ҹ���.

public:
	Chapter7(const Chapter7& _other) = delete;		//����Ʈ ���������.
	Chapter7(Chapter7&& _other) = delete;		//����Ʈ rvalue ���������.

	Chapter7& operator=(const Chapter7& _other) = delete;		//����Ʈ ���Կ�����.
	Chapter7& operator=(const Chapter7&& _other) = delete;		//����Ʈ rvalue ���Կ�����.

public:
	void LoadLevel() override;
	void UpdateLevel() override;

private:
	void RespondSelection(int _index) override;
};

