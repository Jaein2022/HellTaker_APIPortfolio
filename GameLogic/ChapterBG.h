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
	std::string levelNumberStr_;	//레벨번호를 치환한 문자열.
	HFONT levelNumberFont_;			//레벨번호 표시용 폰트.
	HDC backBufferHDC_;				//백버퍼 HDC.

public:
	ChapterBG();		//디폴트 생성자.
	~ChapterBG();		//디폴트 소멸자.

public:
	ChapterBG(const ChapterBG& _other) = delete;		//디폴트 복사생성자.
	ChapterBG(ChapterBG&& _other) = delete;		//디폴트 rvalue 복사생성자.

	ChapterBG& operator=(const ChapterBG& _other) = delete;		//디폴트 대입연산자.
	ChapterBG& operator=(const ChapterBG&& _other) = delete;		//디폴트 rvalue 대입연산자.

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

