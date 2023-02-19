#include "Chapter0_BG.h"
#include <J_GameEngineTime.h>
#include <J_ImageManager.h>
#include <J_Window.h>
#include <J_ImageFile.h>
#include <J_Renderer.h>
#include <J_SoundManager.h>
#include <J_SoundPlayer.h>
#include "Button.h"
#include <J_Input.h>


Chapter0_BG::Chapter0_BG()
	: allButtons_Chapter0_(),
	buttonIndex_(0),
	justBlackBoard_(nullptr),
	Chapter0_BG01_(nullptr),
	Chapter0_BG02_(nullptr),
	Chapter0_BG03_(nullptr),
	Chapter0_BG04_(nullptr),
	beelFly_Renderer_(nullptr),
	/*booper_Renderer_(nullptr),*/
	distanceFromAbyss01_(1215.0f),
	distanceFromAbyss02_(815.0f),
	BG01PivotPosX_(0.0f), 
	BG02PivotPosX_(0.0f),
	BG03PivotPosX_(0.0f),
	BG04PivotPosX_(0.0f),
	BGsPivotPosY_(-105.0f),
	Chapter0_BGSound_Player_(nullptr),
	backBufferHDC_(nullptr),
	introductionFont_(nullptr), 
	introduction_(), 
	lineFont_(nullptr),
	line0_(), 
	line1_()
{

}

Chapter0_BG::~Chapter0_BG()
{
	for (size_t i = 0; i < allButtons_Chapter0_.size(); i++)
	{
		delete allButtons_Chapter0_[i];
		allButtons_Chapter0_[i] = nullptr;
	}
	allButtons_Chapter0_.clear();
}

void Chapter0_BG::Start()
{
	SetActorPos(J_Window::GetInstance().GetWindowSize().DivideHalf());


	justBlackBoard_ = CreateRenderer("JustBlackBoard.bmp", "justBlackBoard");
	justBlackBoard_->SetActorImagePivot(RENDERPIVOT::CENTER);

	Chapter0_BG01_ = CreateRenderer("dialogueBG_abyss01.bmp", "Chapter0_BG01_");
	Chapter0_BG02_ = CreateRenderer("dialogueBG_abyss02.bmp", "Chapter0_BG02_");
	Chapter0_BG03_ = CreateRenderer("dialogueBG_abyss01.bmp", "Chapter0_BG03_");
	Chapter0_BG04_ = CreateRenderer("dialogueBG_abyss02.bmp", "Chapter0_BG04_");

	Chapter0_BG01_->SetActorImagePivot(RENDERPIVOT::CENTER);
	Chapter0_BG02_->SetActorImagePivot(RENDERPIVOT::CENTER);
	Chapter0_BG03_->SetActorImagePivot(RENDERPIVOT::CENTER);
	Chapter0_BG04_->SetActorImagePivot(RENDERPIVOT::CENTER);

	Chapter0_BG01_->SetPivotPos({ BG01PivotPosX_, BGsPivotPosY_ });

	BG02PivotPosX_ = BG01PivotPosX_ - distanceFromAbyss01_;
	Chapter0_BG02_->SetPivotPos({ BG02PivotPosX_, BGsPivotPosY_ });

	BG03PivotPosX_ = BG02PivotPosX_ - distanceFromAbyss02_;
	Chapter0_BG03_->SetPivotPos({ BG03PivotPosX_, BGsPivotPosY_ });

	BG04PivotPosX_ = BG03PivotPosX_ - distanceFromAbyss01_;
	Chapter0_BG04_->SetPivotPos({ BG04PivotPosX_, BGsPivotPosY_ });

	beelFly_Renderer_ = CreateRenderer("beel_fly.bmp", "beelFly_Renderer");
	beelFly_Renderer_->SetActorImagePivot(RENDERPIVOT::BOT);
	beelFly_Renderer_->SetPivotPos({-8, 200});
	//beelFly_Renderer_->SetActorImagePivot(RENDERPIVOT::CENTER);
	//beelFly_Renderer_->SetPivotPos({ 960, 415 });

	//booper_Renderer_ = CreateRenderer("booper.bmp", "booper_Renderer");
	//if (true == booper_Renderer_->GetActorImage()->IsCuttingSizesEmpty())
	//{
	//	booper_Renderer_->GetActorImage()->CutImage({ 100, 100 });
	//}
	//booper_Renderer_->CreateAnimation("booper_idle", "booper.bmp", 0, 18, true, 0.03f, RENDERPIVOT::CENTER);
	//booper_Renderer_->ChangeAnimation("booper_idle");
	//booper_Renderer_->SetPivotPos({ 0, 400 });


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
		CLEARTYPE_QUALITY,			//글씨 디테일 퀄리티. 
		FIXED_PITCH,				//????
		"Crimson Pro"				//폰트 이름.
	);
	if (NULL == lineFont_)	//폰트 생성 실패. 폭파.
	{
		J_GameEngineDebug::AssertFalse();
		return;
	}

	introduction_ = "· Beelzebub, The Great Fly ·";
	line0_ = "Greating little one. Please don't mind me.";
	line1_ = "It's just I, good old Beelzebub.";


	CreateButtons(960, 920, 2);
	allButtons_Chapter0_[0]->SetButtonText("NEW GAME");
	allButtons_Chapter0_[1]->SetButtonText("EXIT");






	if (nullptr == J_SoundManager::GetInstance().FindPlayer("Chapter0_BGSound_Player"))
	{
		Chapter0_BGSound_Player_ = J_SoundManager::GetInstance().CreatePlayer("Chapter0_BGSound_Player", "Apropos.wav");
	}
	if (nullptr == Chapter0_BGSound_Player_)
	{
		Chapter0_BGSound_Player_ = J_SoundManager::GetInstance().FindPlayer("Chapter0_BGSound_Player");
	}

}

void Chapter0_BG::Update()
{

	BG01PivotPosX_ += J_GameEngineTime::GetInstance().GetDeltaTimeF() * 75.0f;
	BG02PivotPosX_ += J_GameEngineTime::GetInstance().GetDeltaTimeF() * 75.0f;
	BG03PivotPosX_ += J_GameEngineTime::GetInstance().GetDeltaTimeF() * 75.0f;
	BG04PivotPosX_ += J_GameEngineTime::GetInstance().GetDeltaTimeF() * 75.0f;

	Chapter0_BG01_->SetPivotPos({ BG01PivotPosX_, BGsPivotPosY_ });
	Chapter0_BG02_->SetPivotPos({ BG02PivotPosX_, BGsPivotPosY_ });
	Chapter0_BG03_->SetPivotPos({ BG03PivotPosX_, BGsPivotPosY_ });
	Chapter0_BG04_->SetPivotPos({ BG04PivotPosX_, BGsPivotPosY_ });

	if (1500.0f <= BG01PivotPosX_)
	{
		BG01PivotPosX_ = BG04PivotPosX_ - distanceFromAbyss02_;
	}
	if (1500.0f <= BG02PivotPosX_)
	{
		BG02PivotPosX_ = BG01PivotPosX_ - distanceFromAbyss01_;
	}
	if (1500.0f <= BG03PivotPosX_)
	{
		BG03PivotPosX_ = BG02PivotPosX_ - distanceFromAbyss02_;
	}
	if (1500.0f <= BG04PivotPosX_)
	{
		BG04PivotPosX_ = BG03PivotPosX_ - distanceFromAbyss01_;
	}	

	if (true == J_Input::GetInstance().GetIsUp("W"))
	{
		allButtons_Chapter0_[buttonIndex_]->SetIsHighlighted(false);
		--buttonIndex_;
		if (0 > buttonIndex_)
		{
			buttonIndex_ = static_cast<int>(allButtons_Chapter0_.size()) - 1;
		}
		allButtons_Chapter0_[buttonIndex_]->SetIsHighlighted(true);
	}
	else if (true == J_Input::GetInstance().GetIsUp("S"))
	{
		allButtons_Chapter0_[buttonIndex_]->SetIsHighlighted(false);
		++buttonIndex_;
		if (static_cast<int>(allButtons_Chapter0_.size()) - 1 < buttonIndex_)
		{
			buttonIndex_ = 0;
		}
		allButtons_Chapter0_[buttonIndex_]->SetIsHighlighted(true);
	}

	for (size_t i = 0; i < allButtons_Chapter0_.size(); i++)
	{
		allButtons_Chapter0_[i]->UpdateButton();
	}

	if (false == allButtons_Chapter0_.empty() && true == allButtons_Chapter0_[buttonIndex_]->GetIsConfirmed())
	{
		parentChapter_->RespondSelection(buttonIndex_);
	}

}

void Chapter0_BG::Render()
{

	justBlackBoard_->Render();

	Chapter0_BG01_->Render();
	Chapter0_BG02_->Render();
	Chapter0_BG03_->Render();
	Chapter0_BG04_->Render();
	beelFly_Renderer_->Render();
	//booper_Renderer_->UpdateAnimation();

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

	for (size_t i = 0; i < allButtons_Chapter0_.size(); i++)
	{
		allButtons_Chapter0_[i]->RenderButton();
	}

	if (true == Chapter0_BGSound_Player_->IsPlayChannelEmpty())
	{
		J_SoundPlayer* tempPlayer = J_SoundManager::GetInstance().FindPlayer("bgm_Player");
		if (false == tempPlayer->IsPlayChannelEmpty() && true == tempPlayer->IsPlaying())
		{
			tempPlayer->Stop();
		}
		Chapter0_BGSound_Player_->PlayCurSound(5);
	}

}

void Chapter0_BG::CreateButtons(int _firstButtonPosX, int firstButtonPosY, int _count)
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
		allButtons_Chapter0_.push_back(NewButton);
	}
}
