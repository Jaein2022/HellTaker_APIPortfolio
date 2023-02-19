#pragma once
#include <J_GameEngineMath.h>
#include <Windows.h>

class Chapter0_BG;
class Dialogue;
class J_SoundPlayer;
class J_ImageFile;
class Button
{
	friend Dialogue;
	friend Chapter0_BG;

	bool isHighlighted_;
	bool isConfirmed_;

	J_ImageFile* normalButton_Image_;
	J_ImageFile* highlightedButton_Image_;
	float4 normalButtonCenter_;
	float4 highlightedButtonCenter_;

	float4 buttonPos_;

	J_SoundPlayer* highlight_SoundPlayer_;
	J_SoundPlayer* confirm_SoundPlayer_;

	HFONT buttonFont_;
	HDC backBufferHDC_;

	std::string buttonText_;

public:
	Button();		//디폴트 생성자.
	~Button();		//디폴트 소멸자.

public:
	Button(const Button& _other) = delete;		//디폴트 복사생성자.
	Button(Button&& _other) = delete;		//디폴트 rvalue 복사생성자.

	Button& operator=(const Button& _other) = delete;		//디폴트 대입연산자.
	Button& operator=(const Button&& _other) = delete;		//디폴트 rvalue 대입연산자.

public:
	void InitButton();

public:
	void SetButtonText(const std::string& _buttonText)
	{
		buttonText_ = _buttonText;
	}
	bool GetIsConfirmed()
	{
		return isConfirmed_;
	}


private:
	void UpdateButton();
	void RenderButton();
	void SetIsHighlighted(bool _isHighlighted);

private:
	void SetButtonPos(const float4& _pos)
	{
		buttonPos_ = _pos;
	}
	void SetButtonPos(int _x, int _y)
	{
		buttonPos_ = { _x, _y };
	}
};

