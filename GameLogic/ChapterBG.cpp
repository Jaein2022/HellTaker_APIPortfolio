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

	if (0 == parentChapterNumber_)	//é��0�� ���� ��� ���.
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




	levelNumberFont_ = CreateFontA(	//��Ʈ ���� �Լ�.
		500,						//��Ʈ ���α���
		87,							//��Ʈ ��. 
		GM_ADVANCED,				//??
		0,							//??
		FW_REGULAR,					//�۾� ȹ �β�.
		false,						//true�� �۾� �����.
		false,						//true�� �۾� ����.
		false,						//true�� �۾� �߰���(��Ҽ�).
		DEFAULT_CHARSET,			//�⺻ ���� ���ڸ���.
		OUT_DEFAULT_PRECIS,			//??
		CLIP_DEFAULT_PRECIS,		//??
		ANTIALIASED_QUALITY,		//�۾� ������ ����Ƽ.
		DEFAULT_PITCH,				//????
		"Amiri Regular"				//��Ʈ �̸�.
	);
	if (NULL == levelNumberFont_)	//��Ʈ ���� ����. ����.
	{
		J_GameEngineDebug::AssertFalse();
		return;
	}

	backBufferHDC_ = J_ImageManager::GetInstance().GetBackBufferImage()->GetDC();	//�����HDC�� �����´�.
	if (NULL == backBufferHDC_)	//�������µ� �����ϸ� ����.
	{
		J_GameEngineDebug::AssertFalse();
		return;
	}

	SelectObject(backBufferHDC_, levelNumberFont_);			//�����HDC�� ��Ʈ �Է�.
	SetTextColor(backBufferHDC_, RGB(255, 255, 255));		//�۾� �� ����. 
	SetTextAlign(backBufferHDC_, TA_CENTER);				//�۾� ���� ����. TA_CENTER: ���η� �߾� ����.
	//SetBkMode(backBufferHDC_, TRANSPARENT);				//�۾� ����� ����.
	//SetBkColor(backBufferHDC_, RGB(255, 0, 255));			//�۾� ���� ����.

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
