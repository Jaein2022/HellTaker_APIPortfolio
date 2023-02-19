#pragma once
#include <J_Actor.h>
#include <Windows.h>

class J_ImageFile;
class Chapter;
class J_SoundPlayer;
class J_Renderer;
class Button;
class Dialogue: public J_Actor
{
	friend Chapter;
protected:

	Chapter* parentChapter_;
	std::vector<Button*> allButtons_;
	int buttonIndex_;

	J_Renderer* justBlackBoard_;
	J_Renderer* demon_Renderer0_;
	J_Renderer* demon_Renderer1_;
	J_Renderer* demon_Renderer2_;
	J_Renderer* background_Renderer_;
	J_Renderer* dialogueSuccess_Renderer_;

	J_Renderer* booper_Renderer_;

	J_SoundPlayer* dialogue_Start_SoundPlayer_;
	J_SoundPlayer* dialogue_Success_SoundPlayer_;
	J_SoundPlayer* dialogue_Fail_SoundPlayer_;
	J_SoundPlayer* dialogue_TextEnd_SoundPlayer_;

	std::vector<J_ImageFile*> badend_Animation_;
	J_ImageFile* backBufferImage_;
	const float badendDelay_;
	float curFrameDelay_;
	int curFrameIndex_;
	const float4 badend_ImageCenterPos_;
	const float4 badend_PivotPos_;
	bool isBadendFinish_;

	HDC backBufferHDC_;

	HFONT introductionFont_;
	std::string introduction_;

	HFONT lineFont_;
	std::string line0_;
	std::string line1_;

	bool isCurDialogue_;
	int successOrFail_;
	bool successRenderNow_;
	bool failRenderNow_;

	bool isDialogueStart_;
	bool isReadyToGetInput_;

public:
	Dialogue();		//디폴트 생성자.
	~Dialogue();		//디폴트 소멸자.

public:
	Dialogue(const Dialogue& _other) = delete;		//디폴트 복사생성자.
	Dialogue(Dialogue&& _other) = delete;		//디폴트 rvalue 복사생성자.

	Dialogue& operator=(const Dialogue& _other) = delete;		//디폴트 대입연산자.
	Dialogue& operator=(const Dialogue&& _other) = delete;		//디폴트 rvalue 대입연산자.



	Button* FindButton(int _index);
	void SetImage(const std::string& _imageName0, const std::string& _imageName1 = "", const std::string& _imageName2 = "");
	void CreateButtons(int _firstButtonPosX, int firstButtonPosY, int _count);	
	void Start() override;
protected:
	void Update() override;
	void Render() override;
	void SetSuccessOrFail(int _successOrFail);
	void Render_Badend();


public:


	void SetIntroduction(const std::string& _introduction)
	{
		introduction_ = _introduction;
	}

	void SetLine0(const std::string& _line)
	{
		line0_ = _line;
	}
	void SetLine1(const std::string& _line = "")
	{
		line1_ = _line;
	}
	void SetIsCurDialogue(bool _isCurDialogue)
	{
		isCurDialogue_ = _isCurDialogue;
	}


private:
	void SetParentChapter(Chapter* _parentChapter)
	{
		parentChapter_ = _parentChapter;
	}
	void SetIsDialogueStart(bool _isDialogueStart = false)
	{
		isDialogueStart_ = _isDialogueStart;
	}




};

