#include "Dialogue.h"
#include <J_ImageFile.h>
#include <J_ImageManager.h>
#include <J_Renderer.h>
#include <J_SoundPlayer.h>
#include <J_SoundManager.h>
#include "Button.h"
#include "Chapter.h"
#include <J_Input.h>
#include <J_GameEngineTime.h>
#include <J_GameEngineMath.h>

Dialogue::Dialogue() 
	: parentChapter_(nullptr),
	buttonIndex_(0),
	justBlackBoard_(nullptr),
	demon_Renderer0_(nullptr),
	demon_Renderer1_(nullptr),
	demon_Renderer2_(nullptr),
	background_Renderer_(nullptr),
	dialogueSuccess_Renderer_(nullptr),
	booper_Renderer_(nullptr),
	dialogue_Start_SoundPlayer_(nullptr),
	dialogue_Success_SoundPlayer_(nullptr),
	dialogue_Fail_SoundPlayer_(nullptr), 
	dialogue_TextEnd_SoundPlayer_(nullptr),
	backBufferImage_(nullptr),
	badendDelay_(0.05f),
	curFrameDelay_(0.0f),
	curFrameIndex_(0), 
	badend_ImageCenterPos_({ 784, 240 }),
	badend_PivotPos_({ 960, 500 }),
	isBadendFinish_(false),
	introductionFont_(nullptr),
	lineFont_(nullptr),
	backBufferHDC_(nullptr),
	introduction_(),
	isCurDialogue_(false),
	successOrFail_(0),
	successRenderNow_(false),
	failRenderNow_(false),
	isDialogueStart_(false), 
	isReadyToGetInput_(false)
{
}

Dialogue::~Dialogue()
{
	justBlackBoard_ = nullptr;
	demon_Renderer0_ = nullptr;
	demon_Renderer1_ = nullptr;
	demon_Renderer2_ = nullptr;
	background_Renderer_ = nullptr;
	dialogueSuccess_Renderer_ = nullptr;

	dialogue_Success_SoundPlayer_ = nullptr;
	dialogue_Fail_SoundPlayer_ = nullptr;

	badend_Animation_.clear();

	for (size_t i = 0; i < allButtons_.size(); i++)
	{
		if (nullptr == allButtons_[i])
		{
			J_GameEngineDebug::AssertFalse();
			continue;
		}
		delete allButtons_[i];
		allButtons_[i] = nullptr;
	}
	allButtons_.clear();
}

Button* Dialogue::FindButton(int _index)
{
	if (true == allButtons_.empty())
	{
		J_GameEngineDebug::AssertFalse();
		return nullptr;
	}
	if (allButtons_.size() - 1 < _index || 0 > _index)
	{
		J_GameEngineDebug::AssertFalse();
		return nullptr;
	}

	return allButtons_[_index];
}

void Dialogue::SetImage(const std::string& _imageName0, const std::string& _imageName1 /*= ""*/, const std::string& _imageName2 /*= ""*/)
{
	if (_imageName0 == _imageName1)
	{
		J_GameEngineDebug::AssertFalse("Both image names are same.");
		return;
	}
	if ("" == _imageName0)
	{
		J_GameEngineDebug::AssertFalse("At least one image is required.");
		return;
	}

	if ("" != _imageName1 && "" != _imageName2)
	{
		background_Renderer_ = CreateRenderer("dialogueBG_throne2.bmp", "background_Renderer");
		background_Renderer_->SetActorImagePivot(RENDERPIVOT::CENTER);
		background_Renderer_->SetPivotPos({ 960, 460 });
	}
	else
	{
		background_Renderer_ = CreateRenderer("dialogueBG_hell.bmp", "background_Renderer");
		background_Renderer_->SetActorImagePivot(RENDERPIVOT::CENTER);
		background_Renderer_->SetPivotPos({ 960, 460 });
	}

	demon_Renderer0_ = CreateRenderer(_imageName0, "demon_Renderer0");
	demon_Renderer0_->SetActorImagePivot(RENDERPIVOT::CENTER);
	if (demon_Renderer0_->GetActorImage()->GetImageSize() == float4{1920, 1080})
	{
		demon_Renderer0_->SetPivotPos({ 960, 540 });
	}
	else
	{
		demon_Renderer0_->SetPivotPos({ 960, 395 });	
	}

	if ("" == _imageName1)		//_imageName1이 없으면 렌더러 생성 금지.
	{
		return;
	}
	demon_Renderer1_ = CreateRenderer(_imageName1, "demon_Renderer1");
	demon_Renderer1_->SetActorImagePivot(RENDERPIVOT::CENTER);
	demon_Renderer1_->SetPivotPos({ 960 - 400, 395 });	

	if ("" == _imageName2)		//_imageName2가 없으면 렌더러 생성 금지.
	{
		return;
	}
	demon_Renderer2_ = CreateRenderer(_imageName2, "demon_Renderer2");
	demon_Renderer2_->SetActorImagePivot(RENDERPIVOT::CENTER);
	demon_Renderer2_->SetPivotPos({ 960 + 400, 395 });



}

void Dialogue::CreateButtons(int _firstButtonPosX, int firstButtonPosY, int _count)
{
	if (2 > _count)	//_count가 2보다 작으면 버튼 만드는 의미가 없으므로 무시한다.
	{
		return;
	}

	for (int i = 0; i < _count; i++)
	{
		Button* NewButton = new Button();
		if (nullptr == NewButton)
		{
			J_GameEngineDebug::AssertFalse();
			return;
		}

		NewButton->SetButtonPos(_firstButtonPosX, firstButtonPosY + (i * 80));
		NewButton->InitButton();
		allButtons_.push_back(NewButton);
	}
}

void Dialogue::Start()
{
	justBlackBoard_ = CreateRenderer("JustBlackBoard.bmp", "justBlackBoard");
	justBlackBoard_->SetActorImagePivot(RENDERPIVOT::CENTER);	
	justBlackBoard_->SetPivotPos({ 960, 480 });									

	dialogueSuccess_Renderer_ = CreateRenderer("success.bmp", "dialogueSuccess_Renderer");
	if (true == dialogueSuccess_Renderer_->GetActorImage()->IsCuttingSizesEmpty())
	{
		dialogueSuccess_Renderer_->GetActorImage()->CutImage({1100, 200});
	}
	dialogueSuccess_Renderer_->CreateAnimation("success", "success.bmp", 0, 7, false, 0.05f, RENDERPIVOT::CENTER);
	dialogueSuccess_Renderer_->ChangeAnimation("success");
	dialogueSuccess_Renderer_->SetPivotPos({ 960, 975 });	

	booper_Renderer_ = CreateRenderer("booper.bmp", "booper_Renderer");
	if (true == booper_Renderer_->GetActorImage()->IsCuttingSizesEmpty())
	{
		booper_Renderer_->GetActorImage()->CutImage({ 100, 100 });
	}
	booper_Renderer_->CreateAnimation("booper_idle", "booper.bmp", 0, 18, true, 0.03f, RENDERPIVOT::CENTER);
	booper_Renderer_->ChangeAnimation("booper_idle");
	booper_Renderer_->SetPivotPos({ 960, 950 });				

	if (nullptr == J_SoundManager::GetInstance().FindPlayer("dialogue_Start_SoundPlayer"))
	{
		dialogue_Start_SoundPlayer_ = J_SoundManager::GetInstance().CreatePlayer("dialogue_Start_SoundPlayer",
			"dialogue_start_01.wav");
	}
	if (nullptr == dialogue_Start_SoundPlayer_)
	{
		dialogue_Start_SoundPlayer_ = J_SoundManager::GetInstance().FindPlayer("dialogue_Start_SoundPlayer");
	}

	if (nullptr == J_SoundManager::GetInstance().FindPlayer("dialogue_Success_SoundPlayer"))
	{
		dialogue_Success_SoundPlayer_ = J_SoundManager::GetInstance().CreatePlayer("dialogue_Success_SoundPlayer",
			"dialogue_success_01.wav");
	}
	if (nullptr == dialogue_Success_SoundPlayer_)
	{
		dialogue_Success_SoundPlayer_ = J_SoundManager::GetInstance().FindPlayer("dialogue_Success_SoundPlayer");
	}

	if (nullptr == J_SoundManager::GetInstance().FindPlayer("dialogue_Fail_SoundPlayer"))
	{
		dialogue_Fail_SoundPlayer_ = J_SoundManager::GetInstance().CreatePlayer("dialogue_Fail_SoundPlayer",
			"bad_end_screen_01.wav");
	}
	if (nullptr == dialogue_Fail_SoundPlayer_)
	{
		dialogue_Fail_SoundPlayer_ = J_SoundManager::GetInstance().FindPlayer("dialogue_Fail_SoundPlayer");
	}

	if (nullptr == J_SoundManager::GetInstance().FindPlayer("dialogue_TextEnd_SoundPlayer"))
	{
		dialogue_TextEnd_SoundPlayer_ = J_SoundManager::GetInstance().CreatePlayer("dialogue_TextEnd_SoundPlayer",
			"dialogue_text_end_01.wav");
	}
	if (nullptr == dialogue_TextEnd_SoundPlayer_)
	{
		dialogue_TextEnd_SoundPlayer_ = J_SoundManager::GetInstance().FindPlayer("dialogue_TextEnd_SoundPlayer");
	}

	backBufferImage_ = J_ImageManager::GetInstance().GetBackBufferImage();
	if (nullptr == backBufferImage_)
	{
		J_GameEngineDebug::AssertFalse();
		return;
	}
	if (true == badend_Animation_.empty())
	{
		badend_Animation_.reserve(9);
		for (int i = 0; i < 9; i++)
		{
			badend_Animation_.push_back(J_ImageManager::GetInstance().FindImage(
				"dialogueDeath" + std::to_string(i) + ".bmp"));
		}
	}
	isBadendFinish_ = false;
	curFrameIndex_ = 0;


	backBufferHDC_ = J_ImageManager::GetInstance().GetBackBufferImage()->GetDC();	//백버퍼HDC를 가져온다.
	if (NULL == backBufferHDC_)	//가져오는데 실패하면 폭파.
	{
		J_GameEngineDebug::AssertFalse();
		return;
	}

	introductionFont_ = CreateFontA(	//폰트 생성 함수.
		50,							//폰트 세로길이
		20,							//폰트 폭. 
		GM_ADVANCED,				//??
		0,							//??
		FW_ULTRABOLD,				//글씨 획 두께.
		false,						//true면 글씨 기울임.
		false,						//true면 글씨 밑줄.
		false,						//true면 글씨 중간선(취소선).
		DEFAULT_CHARSET,			//기본 영어 글자모음.
		OUT_DEFAULT_PRECIS,			//??
		CLIP_DEFAULT_PRECIS,		//??
		CLEARTYPE_QUALITY,		//글씨 디테일 퀄리티. 
		FIXED_PITCH,				//????
		"Crimson Pro"				//폰트 이름.
	);
	if (NULL == introductionFont_)	//폰트 생성 실패. 폭파.
	{
		J_GameEngineDebug::AssertFalse();
		return;
	}

	lineFont_ = CreateFontA(	//폰트 생성 함수.
		42,						//폰트 세로길이
		17,							//폰트 폭. 
		GM_ADVANCED,				//??
		0,							//??
		FW_DEMIBOLD,				//글씨 획 두께.
		false,						//true면 글씨 기울임.
		false,						//true면 글씨 밑줄.
		false,						//true면 글씨 중간선(취소선).
		DEFAULT_CHARSET,			//기본 영어 글자모음.
		OUT_DEFAULT_PRECIS,			//??
		CLIP_DEFAULT_PRECIS,		//??
		CLEARTYPE_QUALITY,		//글씨 디테일 퀄리티. 
		FIXED_PITCH,				//????
		"Crimson Pro"				//폰트 이름.
	);
	if (NULL == lineFont_)	//폰트 생성 실패. 폭파.
	{
		J_GameEngineDebug::AssertFalse();
		return;
	}

	SetUpdateOrder(9);
	SetRenderOrder(10);
}

void Dialogue::Update()
{
	if (false == parentChapter_->GetIsInDialogue())
	{
		return;
	}
	
	if (false == isCurDialogue_)
	{
		return;
	}

	if ( (true == successRenderNow_ && true == dialogueSuccess_Renderer_->IsCurAnimationFinish()) ||
		(true == failRenderNow_ && true == isBadendFinish_) )
	{
		if (true == J_Input::GetInstance().GetIsUp("Space") &&
			true == J_Input::GetInstance().GetIsFree("Space"))
		{
 			parentChapter_->RespondSelection(-1);
		}
		return;
	}

	if (true == allButtons_.empty() && (false == failRenderNow_ && false == successRenderNow_))
	{
		if (1 == successOrFail_)
		{
			dialogue_Success_SoundPlayer_->PlayCurSound();
			successRenderNow_ = true;
		}
		else if (-1 == successOrFail_)
		{
			if (true == isReadyToGetInput_ && true == J_Input::GetInstance().GetIsUp("Space"))
			{
				dialogue_Fail_SoundPlayer_->PlayCurSound();
				failRenderNow_ = true;
			}

			if (true == J_Input::GetInstance().GetIsUp("Space"))
			{
				isReadyToGetInput_ = true;
			}
		}
		else
		{
			if (true == isReadyToGetInput_ && true == J_Input::GetInstance().GetIsUp("Space"))
			{
				dialogue_TextEnd_SoundPlayer_->PlayCurSound();
				parentChapter_->RespondSelection(-1);
			}

			if (true == J_Input::GetInstance().GetIsUp("Space"))
			{
				isReadyToGetInput_ = true;
			}
		}
		return;
	}


	if (true == J_Input::GetInstance().GetIsUp("W"))
	{
		allButtons_[buttonIndex_]->SetIsHighlighted(false);
		--buttonIndex_;
		if (0 > buttonIndex_)
		{
			buttonIndex_ = static_cast<int>(allButtons_.size()) - 1;
		}
		allButtons_[buttonIndex_]->SetIsHighlighted(true);
	}
	else if (true == J_Input::GetInstance().GetIsUp("S"))
	{
		allButtons_[buttonIndex_]->SetIsHighlighted(false);
		++buttonIndex_;
		if (static_cast<int>(allButtons_.size()) - 1 < buttonIndex_)
		{
			buttonIndex_ = 0;
		}
		allButtons_[buttonIndex_]->SetIsHighlighted(true);
	}

	for (size_t i = 0; i < allButtons_.size(); i++)
	{
		allButtons_[i]->UpdateButton();
	}

	if (false == allButtons_.empty() && true == allButtons_[buttonIndex_]->GetIsConfirmed())
	{
		parentChapter_->RespondSelection(buttonIndex_);
	}
}

void Dialogue::Render()
{
	if (false == parentChapter_->GetIsInDialogue())
	{
		return;
	}

	if (false == isCurDialogue_)
	{
		return;
	}

	if (true == isDialogueStart_)
	{
		isDialogueStart_ = false;
		dialogue_Start_SoundPlayer_->PlayCurSound();
	}

	justBlackBoard_->Render();
	background_Renderer_->Render();

	if (nullptr != demon_Renderer1_)
	{
		demon_Renderer1_->Render();
	}
	if (nullptr != demon_Renderer2_)
	{
		demon_Renderer2_->Render();
	}
	demon_Renderer0_->Render();


	HGDIOBJ tempHandle = SelectObject(backBufferHDC_, introductionFont_);
	SetTextColor(backBufferHDC_, RGB(230, 77, 81));		//폰트 색 지정. 
	TextOutA(
		backBufferHDC_,
		960,
		745,
		introduction_.c_str(),
		static_cast<int>(introduction_.size())
	);

	SelectObject(backBufferHDC_, lineFont_);
	SetTextColor(backBufferHDC_, RGB(255, 255, 255));		//폰트 색 지정. 
	TextOutA(
		backBufferHDC_,
		960,
		792,
		line0_.c_str(),
		static_cast<int>(line0_.size())
	);

	TextOutA(
		backBufferHDC_,
		960,
		827,
		line1_.c_str(),
		static_cast<int>(line1_.size())
	);

	SelectObject(backBufferHDC_, tempHandle);


	if (true == allButtons_.empty())
	{
		booper_Renderer_->UpdateAnimation();
	}
	else
	{
		for (size_t i = 0; i < allButtons_.size(); i++)
		{
			allButtons_[i]->RenderButton();
		}
	}

	if (true == successRenderNow_)
	{
		if (true == dialogueSuccess_Renderer_->IsCurAnimationFinish())
		{
			dialogueSuccess_Renderer_->SetFrameIndex(7, RENDERPIVOT::CENTER);
			dialogueSuccess_Renderer_->Render();
		}
		else
		{
			dialogueSuccess_Renderer_->UpdateAnimation();
		}
	}
	else if (true == failRenderNow_)
	{
		Render_Badend();
	}
}

void Dialogue::SetSuccessOrFail(int _successOrFail)
{
	if (false == allButtons_.empty() && 
		(0 != _successOrFail) )
	{
		J_GameEngineDebug::AssertFalse();
		return;
	}
	else if (true == allButtons_.empty() && 
		(1 != _successOrFail && -1 != _successOrFail && 0 != _successOrFail) )
	{
		J_GameEngineDebug::AssertFalse();
		return;
	}
	successOrFail_ = _successOrFail;
}

void Dialogue::Render_Badend()
{
	curFrameDelay_ -= J_GameEngineTime::GetInstance().GetDeltaTimeF();
	if (0.0f >= curFrameDelay_)
	{
		curFrameDelay_ = badendDelay_;
		if (8 <= curFrameIndex_)
		{
			curFrameIndex_ = 8;
			isBadendFinish_ = true;
		}
		else
		{
			++curFrameIndex_;
		}
	}
	justBlackBoard_->Render();
	float4 renderPos = badend_PivotPos_ - badend_ImageCenterPos_;

	backBufferImage_->PasteOnBackBuffer(
		badend_Animation_[curFrameIndex_],
		renderPos,
		badend_Animation_[curFrameIndex_]->GetImageSize(),
		float4::ZERO,
		badend_Animation_[curFrameIndex_]->GetImageSize()
	);
}
