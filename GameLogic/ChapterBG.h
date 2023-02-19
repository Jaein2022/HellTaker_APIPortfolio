#pragma once
#include <J_Actor.h>
#include <Windows.h>

class Chapter;
class J_SoundPlayer;
class J_Renderer;
class ChapterBG: public J_Actor
{
	friend Chapter;

	J_Renderer* defaultBG_Renderer_;
	J_Renderer* UI_Renderer_;
	J_SoundPlayer* bgm_Player_;

	Chapter* parentChapter_;
	int parentChapterNumber_;
	std::string levelNumberStr_;	//������ȣ�� ġȯ�� ���ڿ�.
	HFONT levelNumberFont_;			//������ȣ ǥ�ÿ� ��Ʈ.
	HDC backBufferHDC_;				//����� HDC.

public:
	ChapterBG();		//����Ʈ ������.
	~ChapterBG();		//����Ʈ �Ҹ���.

public:
	ChapterBG(const ChapterBG& _other) = delete;		//����Ʈ ���������.
	ChapterBG(ChapterBG&& _other) = delete;		//����Ʈ rvalue ���������.

	ChapterBG& operator=(const ChapterBG& _other) = delete;		//����Ʈ ���Կ�����.
	ChapterBG& operator=(const ChapterBG&& _other) = delete;		//����Ʈ rvalue ���Կ�����.

public:
	void Start() override;
	void Update() override;
	void Render() override;

private:
	void SetParentChapter(Chapter* _parentChapter)
	{
		parentChapter_ = _parentChapter;
	}
};

