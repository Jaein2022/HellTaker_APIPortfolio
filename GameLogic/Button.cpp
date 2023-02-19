#include "Button.h"
#include <J_SoundManager.h>
#include <J_SoundPlayer.h>
#include <J_ImageFile.h>
#include <J_ImageManager.h>
#include <J_Input.h>

Button::Button()
	: isHighlighted_(false),
	isConfirmed_(false),
	normalButton_Image_(nullptr),
	highlightedButton_Image_(nullptr),
	normalButtonCenter_(float4::ZERO),
	highlightedButtonCenter_(float4::ZERO),
	buttonPos_(float4::ZERO),
	highlight_SoundPlayer_(nullptr),
	confirm_SoundPlayer_(nullptr),
	buttonFont_(nullptr),
	backBufferHDC_(nullptr)
{
}

Button::~Button()
{
}


void Button::InitButton()
{
	normalButton_Image_ = J_ImageManager::GetInstance().FindImage("button_Unselected.bmp");
	normalButtonCenter_ = normalButton_Image_->GetImageSize().DivideHalf();

	highlightedButton_Image_ = J_ImageManager::GetInstance().FindImage("button_Selected.bmp");
	highlightedButtonCenter_ = highlightedButton_Image_->GetImageSize().DivideHalf();

	if (nullptr == J_SoundManager::GetInstance().FindPlayer("highlight_SoundPlayer"))
	{
		highlight_SoundPlayer_ = J_SoundManager::GetInstance().CreatePlayer(
			"highlight_SoundPlayer",
			"button_dialogue_highlight_01.wav"
		);
	}
	if (nullptr == highlight_SoundPlayer_)
	{
		highlight_SoundPlayer_ = J_SoundManager::GetInstance().FindPlayer(
			"highlight_SoundPlayer"
		);
	}

	if (nullptr == J_SoundManager::GetInstance().FindPlayer("confirm_SoundPlayer"))
	{
		confirm_SoundPlayer_ = J_SoundManager::GetInstance().CreatePlayer(
			"confirm_SoundPlayer",
			"button_dialogue_confirm_01.wav"
		);
	}
	if (nullptr == confirm_SoundPlayer_)
	{
		confirm_SoundPlayer_ = J_SoundManager::GetInstance().FindPlayer("confirm_SoundPlayer");
	}

	buttonFont_ = CreateFontA(	//폰트 생성 함수.
		40,							//폰트 세로길이
		16,							//폰트 폭. 
		GM_ADVANCED,				//??
		0,							//??
		FW_REGULAR,					//글씨 획 두께.
		false,						//true면 글씨 기울임.
		false,						//true면 글씨 밑줄.
		false,						//true면 글씨 중간선(취소선).
		DEFAULT_CHARSET,			//기본 영어 글자모음.
		OUT_DEFAULT_PRECIS,			//??
		CLIP_DEFAULT_PRECIS,		//??
		ANTIALIASED_QUALITY,		//글씨 디테일 퀄리티.
		DEFAULT_PITCH,				//????
		"Crimson Pro"				//폰트 이름.
	);
	if (NULL == buttonFont_)	//폰트 생성 실패. 폭파.
	{
		J_GameEngineDebug::AssertFalse();
		return;
	}

	backBufferHDC_ = J_ImageManager::GetInstance().GetBackBufferImage()->GetDC();	//백버퍼HDC를 가져온다.
	if (NULL == backBufferHDC_)	//가져오는데 실패하면 폭파.
	{
		J_GameEngineDebug::AssertFalse();
		return;
	}
}

void Button::UpdateButton()
{
	if (true == isHighlighted_)
	{
		if (true == J_Input::GetInstance().GetIsUp("Space"))
		{
			isConfirmed_ = true;
			confirm_SoundPlayer_->PlayCurSound();
		}
	}
}

void Button::RenderButton()
{
	J_ImageFile* backBufferImage = J_ImageManager::GetInstance().GetBackBufferImage();
	if (true == this->isHighlighted_)
	{
		backBufferImage->PasteOnBackBuffer(
			highlightedButton_Image_,
			buttonPos_ - highlightedButtonCenter_,
			highlightedButton_Image_->GetImageSize(),
			float4::ZERO,
			highlightedButton_Image_->GetImageSize()
		);

		HGDIOBJ tempHandle = SelectObject(backBufferHDC_, buttonFont_);
		SetTextColor(backBufferHDC_, RGB(255, 255, 255));		//폰트 색 지정. 
		TextOutA(
			backBufferHDC_,
			buttonPos_.IntX(),
			buttonPos_.IntY() - 24,
			buttonText_.c_str(),
			static_cast<int>(buttonText_.size())
		);
		SelectObject(backBufferHDC_, tempHandle);
	}
	else
	{
		backBufferImage->PasteOnBackBuffer(
			normalButton_Image_,
			buttonPos_ - normalButtonCenter_,
			normalButton_Image_->GetImageSize(),
			float4::ZERO,
			normalButton_Image_->GetImageSize()
		);

		HGDIOBJ tempHandle = SelectObject(backBufferHDC_, buttonFont_);
		SetTextColor(backBufferHDC_, RGB(212, 185, 191));		//폰트 색 지정. 
		TextOutA(
			backBufferHDC_,
			buttonPos_.IntX(),
			buttonPos_.IntY() - 24,
			buttonText_.c_str(),
			static_cast<int>(buttonText_.size())
		);
		SelectObject(backBufferHDC_, tempHandle);
	}
}

void Button::SetIsHighlighted(bool _isHighlighted)
{
	isHighlighted_ = _isHighlighted;
	if (true == isHighlighted_)
	{
		highlight_SoundPlayer_->PlayCurSound();
		
	}
	else
	{
		highlight_SoundPlayer_->Stop();
	}
}

