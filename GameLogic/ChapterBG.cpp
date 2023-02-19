#include "ChapterBG.h"
#include "Chapter.h"
#include <J_Renderer.h>
#include <string>
#include <J_ImageManager.h>
#include <J_ImageFile.h>
#include <J_SoundPlayer.h>
#include <J_SoundManager.h>

ChapterBG::ChapterBG()
	: defaultBG_Renderer_(nullptr),
	UI_Renderer_(nullptr),
	bgm_Player_(nullptr),
	parentChapter_(nullptr),
	parentChapterNumber_(-1),
	levelNumberStr_(),
	levelNumberFont_(NULL),
	backBufferHDC_(NULL)
{
	levelNumberStr_.reserve(5);
}

ChapterBG::~ChapterBG()
{
}

void ChapterBG::Start()
{
	SetActorPos(float4::ZERO);
	SetUpdateOrder(10);
	SetRenderOrder(1);


	std::string BGName = std::string(GetName());
	int cutStartIndex = 0;
	while ('0' > BGName[cutStartIndex] || '9' < BGName[cutStartIndex])
	{
		++cutStartIndex;
	}
	parentChapterNumber_ = std::stoi(BGName.substr(cutStartIndex));

	if (0 == parentChapterNumber_)	//챕터0은 전용 배경 사용.
	{
		return;
	}


	defaultBG_Renderer_ = CreateRenderer("chapterBG"+ std::to_string(parentChapterNumber_) + ".bmp", "defaultBG_Renderer");
	defaultBG_Renderer_->SetActorImagePivot(RENDERPIVOT::LEFTTOP);

	UI_Renderer_ = CreateRenderer("UI_InPlay.bmp", "UI_Renderer");
	UI_Renderer_->SetActorImagePivot(RENDERPIVOT::LEFTTOP);

	if (nullptr == J_SoundManager::GetInstance().FindPlayer("bgm_Player"))
	{
		bgm_Player_ = J_SoundManager::GetInstance().CreatePlayer("bgm_Player", "Vitality.wav");
		bgm_Player_->PushBackInAlbum("Luminescent.wav");
	}
	if (nullptr == bgm_Player_)
	{
		bgm_Player_ = J_SoundManager::GetInstance().FindPlayer("bgm_Player");
	}




	levelNumberFont_ = CreateFontA(	//폰트 생성 함수.
		500,						//폰트 세로길이
		87,							//폰트 폭. 
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
		"Amiri Regular"				//폰트 이름.
	);
	if (NULL == levelNumberFont_)	//폰트 생성 실패. 폭파.
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

	SelectObject(backBufferHDC_, levelNumberFont_);			//백버퍼HDC에 폰트 입력.
	SetTextColor(backBufferHDC_, RGB(255, 255, 255));		//글씨 색 지정. 
	SetTextAlign(backBufferHDC_, TA_CENTER);				//글씨 정렬 세팅. TA_CENTER: 가로로 중앙 정렬.
	//SetBkMode(backBufferHDC_, TRANSPARENT);				//글씨 배경모드 설정.
	//SetBkColor(backBufferHDC_, RGB(255, 0, 255));			//글씨 배경색 지정.

	int quotient = parentChapterNumber_ / 5;
	int remainder = parentChapterNumber_ % 5;
	
	if (4 == remainder)
	{
		levelNumberStr_.push_back('I');
		++quotient;
		levelNumberStr_.push_back( (1 == quotient % 2) ? 'V' : 'X' );
	}
	else
	{
		if (0 < quotient)
		{
			levelNumberStr_.push_back( (1 == quotient % 2) ? 'V' : 'X');
		}

		while (0 < remainder)
		{
			--remainder;
			levelNumberStr_.push_back('I');
		}
	}
}

void ChapterBG::Update()
{
	if (true == parentChapter_->isInDialogue_ && 9 == parentChapterNumber_ )
	{
		if (false == bgm_Player_->IsCurSoundName("Luminescent.wav"))
		{
			bgm_Player_->Stop();
			bgm_Player_->ChangeCurSound(1);
			bgm_Player_->PlayCurSound();
		}
	}
	else
	{
		bgm_Player_->ChangeCurSound(0);
	}
}

void ChapterBG::Render()
{
	defaultBG_Renderer_->Render();
	UI_Renderer_->Render();

	if (true == bgm_Player_->IsPlayChannelEmpty() || false == bgm_Player_->IsPlaying())
	{
		J_SoundPlayer* tempPlayer = J_SoundManager::GetInstance().FindPlayer("Chapter0_BGSound_Player");
		if (false == tempPlayer->IsPlayChannelEmpty() && true == tempPlayer->IsPlaying())
		{
			tempPlayer->Stop();
		}
		bgm_Player_->PlayCurSound(30);
	}

	TextOutA(
		backBufferHDC_,
		1715,
		650,
		levelNumberStr_.c_str(),
		static_cast<int>( levelNumberStr_.size() )
	);
}
