#include "Chapter.h"
#include <vector>
#include "Tile.h"
#include "Hero.h"
#include "Skeleton.h"
#include "Stone.h"
#include "Demon.h"
#include "ChapterBG.h"
#include "Key.h"
#include "Lock.h"
#include <J_ImageFile.h>
#include <J_GameEngineMath.h>
#include <J_LevelManager.h>
#include <J_ImageManager.h>
#include <J_GameEngineTime.h>
#include <J_Input.h>
#include <J_SoundManager.h>
#include <J_SoundPlayer.h>
#include <J_Renderer.h>
#include "Dialogue.h"




Chapter::Chapter()
	: chapterNumber_(-1),
	allTiles_(),
	goalTileIndex00_(float4::ZERO),
	goalTileIndex01_(float4::ZERO), 
	allSkeletons_(),
	allStones_(),
	allDialogues_(), 
	backBufferImage_(nullptr),
	transition_(),
	transitionDelay_(0.045f),
	curFrameDelay_(0.0f),
	curFrameIndex_(0),
	transitionSound_Player1_(nullptr),
	transitionSound_Player2_(nullptr),
	transitionSoundChangeDelay_(0.0f),
	chapter8CamPosY_(850),
	hero_(nullptr), 
	defaultBG_(nullptr),
	key_(nullptr), 
	lock_(nullptr), 
	curDialogue_(nullptr),
	isTransitionOn_(false),
	leftTopTile_(nullptr), 
	isInDialogue_(false)
{
	allSkeletons_.reserve(20);
	allStones_.reserve(20);
	allDialogues_.reserve(5);
}

Chapter::~Chapter()
{
	ClearChapter();
}

Tile* Chapter::FindTile(int _x, int _y)
{
	if (0 > _y || static_cast<int>(allTiles_.size()) <= _y)
	{
		J_GameEngineDebug::AssertFalse("allTiles size out.");
		return nullptr;
	}
	if (0 > _x || static_cast<int>(allTiles_[_y].size()) <= _x)
	{
		J_GameEngineDebug::AssertFalse("allTiles size out.");
		return nullptr;
	}

	return allTiles_[_y][_x];
}

Tile* Chapter::FindTile(const float4& _tilePos)
{
	return FindTile(_tilePos.IntX(), _tilePos.IntY());
}

bool Chapter::IsHeroGoal()
{
	return (goalTileIndex00_ == hero_->curTileIndex_ || goalTileIndex01_ == hero_->curTileIndex_);
}

float4 Chapter::GetHeroCurTileIndex()
{
	return hero_->curTileIndex_;
}

void Chapter::GiveKey()
{
	hero_->isGotKey_ = true;
}

bool Chapter::IsHeroGotKey()
{
	return hero_->isGotKey_;
}

void Chapter::RespondSelection(int _index)
{
}

void Chapter::CreateTiles(const float4& _leftTopTilePos, const int _allTilesSizeX , const int _allTilesSizeY )
{
	if (0 == _allTilesSizeX || 0 == _allTilesSizeY)
	{
		J_GameEngineDebug::AssertFalse("Size cannot be ZERO");
		return;
	}
	allTiles_.resize(_allTilesSizeY, std::vector<Tile*>(_allTilesSizeX, nullptr));

	//leftTopTile 생성.
	leftTopTile_ = CreateActor<Tile>("leftTopTile");
	if (nullptr == leftTopTile_)
	{
		J_GameEngineDebug::AssertFalse();
		return;
	}
	leftTopTile_->SetParentChapter(this);
	leftTopTile_->InitTileState(TileState::WALL);		
	leftTopTile_->SetActorPos(_leftTopTilePos);

	allTiles_[0][0] = leftTopTile_;


	//일반 타일들 생성.
	for (int y = 0; y < _allTilesSizeY; y++)
	{
		for (int x = 0; x < _allTilesSizeX; x++)
		{
			if (0 == x && 0 == y)
			{
				continue;
			}

			Tile* NewTile = CreateActor<Tile>("(" + std::to_string(x) + ", " + std::to_string(y) + ") tile");
			if (nullptr == NewTile)
			{
				J_GameEngineDebug::AssertFalse();
				return;
			}
			NewTile->SetParentChapter(this);
			NewTile->SetActorPos(					//initTile_기준으로 타일크기인 100 * x, 100 * y만큼 멀어진다.
				{ (leftTopTile_->GetActorPos().IntX() + (100 * x)) ,
				(leftTopTile_->GetActorPos().IntY() + (100 * y)) }
			);

			if (0 == x || 0 == y || _allTilesSizeX - 1 == x || _allTilesSizeY - 1 == y)
			{
				//따로 지정하지 않아도 가장 외곽의 타일들은 WALL타입 타일로 선언해서 벽을 친다.
				NewTile->InitTileState(TileState::WALL);
			}
			else
			{
				NewTile->InitTileState(TileState::NONE);
			}
			allTiles_[y][x] = NewTile;
		}
	}

	if (8 == chapterNumber_)
	{
		for (int y = 0; y < _allTilesSizeY; y++)
		{
			for (int x = 0; x < _allTilesSizeX; x++)
			{
				allTiles_[y][x]->tile_Renderer_->SetCameraEffectOn();
			}
		}
	}
}

void Chapter::CreateHero(unsigned int _moveLimit, int _x, int _y)
{
	hero_ = CreateActor<Hero>("hero");
	if (nullptr == hero_)
	{
		J_GameEngineDebug::AssertFalse();
		return;
	}
	hero_->SetParentChapter(this);
	hero_->SetMyType(ActorType::HERO);
	hero_->SetMoveLimit(_moveLimit);
	hero_->SetTile(_x, _y);
	if (8 == this->chapterNumber_)
	{
		hero_->SetCamEffectOn();
		this->SetCameraPos({0, hero_->actorPos_.IntY() - chapter8CamPosY_});
	}
	else
	{
		hero_->SetCamEffectOff();
		this->SetCameraPos(float4::ZERO);
	}

	FindTile(_x, _y)->SetHellActor(hero_);
}

void Chapter::CreateSkeleton(int _x, int _y)
{
	Skeleton* NewSkeleton = CreateActor<Skeleton>("skeleton" + std::to_string(allSkeletons_.size()));
	if (NewSkeleton == nullptr)
	{
		J_GameEngineDebug::AssertFalse();
		return;
	}
	NewSkeleton->SetParentChapter(this);
	NewSkeleton->SetMyType(ActorType::SKELETON);
	NewSkeleton->SetTile(_x, _y);
	if (8 == this->chapterNumber_)
	{
		NewSkeleton->SetCamEffectOn();
	}
	else
	{
		NewSkeleton->SetCamEffectOff();
	}
	allSkeletons_.push_back(NewSkeleton);
}

void Chapter::CreateStone(int _x, int _y)
{
	Stone* NewStone = CreateActor<Stone>("stone" + std::to_string(allStones_.size()));
	if (nullptr == NewStone)
	{
		J_GameEngineDebug::AssertFalse();
		return;
	}
	NewStone->SetParentChapter(this);
	NewStone->SetMyType(ActorType::STONE);
	NewStone->SetTile(_x, _y);
	if (8 == this->chapterNumber_)
	{
		NewStone->SetCamEffectOn();
	}
	else
	{
		NewStone->SetCamEffectOff();
	}

	allStones_.push_back(NewStone);
}

Demon* Chapter::CreateDemon(const std::string& _actorName, int _x, int _y)
{
	Demon* NewDemon = CreateActor<Demon>(_actorName);
	if (nullptr == NewDemon)
	{
		J_GameEngineDebug::AssertFalse();
		return nullptr;
	}
	NewDemon->SetParentChapter(this);
	NewDemon->SetMyType(ActorType::DEMON);
	NewDemon->SetTile(_x, _y);
	if (8 == this->chapterNumber_)
	{
		NewDemon->SetCamEffectOn();
	}
	else
	{
		NewDemon->SetCamEffectOff();
	}
	return NewDemon;
}

void Chapter::CreateDefaultBG()
{
	defaultBG_ = CreateActor<ChapterBG>("Chapter" + std::to_string(chapterNumber_) + "defaultBG");
	if (nullptr == defaultBG_)
	{
		J_GameEngineDebug::AssertFalse();
		return;
	}
	defaultBG_->SetParentChapter(this);

	if (8 == this->chapterNumber_)
	{
		defaultBG_->defaultBG_Renderer_->SetCameraEffectOn();
	}
}

void Chapter::CreateKey(int _x, int _y)
{
	key_ = CreateActor<Key>("key");	
	if (nullptr == key_)		//생성 실패하면 폭파.
	{
		J_GameEngineDebug::AssertFalse();
		return;
	}
	key_->SetParentChapter(this);
	key_->SetMyType(ActorType::KEY);
	key_->SetTile(_x, _y);
	FindTile(_x, _y)->SetHellActor(nullptr);	//키가 있는 타일에게는 액터 정보를 비워서 언제든지 히어로가 이동할 수 있게 한다.
}

void Chapter::CreateLock(int _x, int _y)
{
	lock_ = CreateActor<Lock>("lock");
	if (nullptr == lock_)		//생성 실패하면 폭파.
	{
		J_GameEngineDebug::AssertFalse();
		return;
	}
	lock_->SetParentChapter(this);
	lock_->SetMyType(ActorType::LOCK);
	lock_->SetTile(_x, _y);
	FindTile(_x, _y)->SetHellActor(lock_);
}

void Chapter::CreateDialogue(const std::string& _imageName0, const std::string& _imageName1 /*= ""*/,
	const std::string& _imageName2 /*= ""*/, int _buttonCount /*= 2*/, int _successOrFail /*= 0*/)
{
	Dialogue* NewDialogue = CreateActor<Dialogue>("chapter" + std::to_string(chapterNumber_) +
		"_Dialogue" + std::to_string(allDialogues_.size()));
	if (nullptr == NewDialogue)
	{
		J_GameEngineDebug::AssertFalse();
		return ;
	}

	NewDialogue->SetImage(_imageName0, _imageName1, _imageName2);
	if (0 == allDialogues_.size())
	{
		NewDialogue->SetIsDialogueStart(true);
	}
	else
	{
		NewDialogue->SetIsDialogueStart();
	}
	NewDialogue->SetParentChapter(this);
	NewDialogue->CreateButtons(960, 920, _buttonCount);
	NewDialogue->SetSuccessOrFail(_successOrFail);
	allDialogues_.push_back(NewDialogue);
}

void Chapter::ClearChapter()
{
	leftTopTile_ = nullptr;
	for (size_t y = 0; y < allTiles_.size(); y++)
	{
		allTiles_[y].clear();
	}
	allTiles_.clear();
	allSkeletons_.clear();
	allStones_.clear();
	transition_.clear();
	allDialogues_.clear();

	hero_ = nullptr;
	defaultBG_ = nullptr;
	key_ = nullptr;
	lock_ = nullptr;
	isInDialogue_ = false;
}

void Chapter::ChangeToNextChapter()
{
	int nextChapterNumber = ++chapterNumber_;
	if (10 <= nextChapterNumber)
	{
		nextChapterNumber = 0;
	}

	J_LevelManager::GetInstance().ChangeCurLevel("Chapter" + std::to_string(nextChapterNumber));
}

void Chapter::SetGoalTileIndex(const float4& _goalTileIndex0, const float4& _goalTileIndex1 /*= float4::ZERO*/)
{
	if (0 > _goalTileIndex0.IntY() || static_cast<int>(allTiles_.size()) - 1 <= _goalTileIndex0.IntY())
	{
		J_GameEngineDebug::AssertFalse();
		return;
	}
	if (0 > _goalTileIndex0.IntX() || static_cast<int>(allTiles_[_goalTileIndex0.IntY()].size()) - 1 <= _goalTileIndex0.IntX())
	{
		J_GameEngineDebug::AssertFalse();
		return;
	}
	if (TileState::WALL == FindTile(_goalTileIndex0)->GetTileState())
	{
		J_GameEngineDebug::AssertFalse();
		return;
	}
	goalTileIndex00_ = _goalTileIndex0;



	if ( (1 > _goalTileIndex1.IntY() || static_cast<int>(allTiles_.size()) - 1 <= _goalTileIndex1.IntY()) &&
		leftTopTile_ != FindTile(_goalTileIndex1))
	{
		J_GameEngineDebug::AssertFalse();
		return;
	}
	if ( (1 > _goalTileIndex1.IntX() || static_cast<int>(allTiles_[_goalTileIndex1.IntY()].size()) - 1 <= _goalTileIndex1.IntX()) &&
		leftTopTile_ != FindTile(_goalTileIndex1))
	{
		J_GameEngineDebug::AssertFalse();
		return;
	}
	goalTileIndex01_ = _goalTileIndex1;
}

void Chapter::CreateTransition()
{
	backBufferImage_ = J_ImageManager::GetInstance().GetBackBufferImage();
	if (nullptr == backBufferImage_)
	{
		J_GameEngineDebug::AssertFalse("nullptr == backBufferImage_");
		return;
	}

	if (nullptr == J_SoundManager::GetInstance().FindPlayer("transitionSound_Player1"))
	{
		transitionSound_Player1_ = J_SoundManager::GetInstance().CreatePlayer("transitionSound_Player1", "screen_changer_part1_01.wav");
	}
	if (nullptr == transitionSound_Player1_)
	{
		transitionSound_Player1_ = J_SoundManager::GetInstance().FindPlayer("transitionSound_Player1");
	}

	if (nullptr == J_SoundManager::GetInstance().FindPlayer("transitionSound_Player2"))
	{
		transitionSound_Player2_ = J_SoundManager::GetInstance().CreatePlayer("transitionSound_Player2", "screen_changer_part2_01.wav");
	}
	if (nullptr == transitionSound_Player2_)
	{
		transitionSound_Player2_ = J_SoundManager::GetInstance().FindPlayer("transitionSound_Player2");
	}

	if (false == transitionSound_Player1_->IsPlayChannelEmpty() && true == transitionSound_Player1_->IsPlaying())
	{
		transitionSound_Player1_->Stop();
	}
	if (false == transitionSound_Player2_->IsPlayChannelEmpty() && true == transitionSound_Player2_->IsPlaying())
	{
		transitionSound_Player2_->Stop();
	}

	isTransitionOn_ = true;
	transitionSoundChangeDelay_ = 0.0f;
	if (false == transition_.empty())
	{
		return;
	}


	transition_.reserve(31);
	for (int i = 0; i < 31; ++i)
	{
		transition_.push_back(J_ImageManager::GetInstance().FindImage("transition" + std::to_string(i) + ".bmp"));
	}
}

void Chapter::ManageInput()
{


	if (true == isTransitionOn_)	//transition 재생중일때는 입력 차단.
	{
		return;
	}
	if (nullptr != hero_ && HellActorState::DEAD == hero_->curState_)		//heroDeath_Animation 재생중일때도 입력 차단.
	{
		return;
	}



	//시스템.

	if (true == J_Input::GetInstance().GetIsUp("N"))
	{
		ChangeToNextChapter();
	}
	if (true == J_Input::GetInstance().GetIsUp("R"))	//R키로 챕터 리셋.
	{
		this->ResetLevel();
	}
	if (true == J_Input::GetInstance().GetIsUp("M"))	//M키로 매뉴얼 보기. 
	{
		J_GameEngineDebug::DisplayManual();
	}
	if (true == J_Input::GetInstance().GetIsUp("T"))	//테스트. 
	{
		if (true == isInDialogue_)
		{
			isInDialogue_ = false;
		}
		else
		{
			isInDialogue_ = true;
		}
	}
	
	if (true == isInDialogue_)	//대화창 있는 동안은 히어로 조작 불가.
	{
		return;
	}

	if (nullptr == hero_)
	{
		return;
	}


	if (true == J_Input::GetInstance().GetIsUp("V"))	//V키로 타일 보이게/안보이게 하기.
	{
		if (nullptr == leftTopTile_)
		{
			return;
		}

		if (true == leftTopTile_->isVisible_)
		{
			SetIsTileVisible(false);
		}
		else
		{
			SetIsTileVisible(true);
		}
	}

	//치트키.
	if (true == J_Input::GetInstance().GetIsUp("I"))	//I키로 히어로 이동 횟수 증폭.
	{
		hero_->SetMoveLimit(666);
	}
	if (true == J_Input::GetInstance().GetIsUp("K"))	//K키로 히어로 이동회수-2 -> 즉시 사망.
	{
		hero_->SetMoveLimit(-2);
	}

	//플레이어 방향 제어.
	if (true == J_Input::GetInstance().GetIsUp("W"))		
	{
		hero_->ChangeDirection(float4::UP);
	}
	else if (true == J_Input::GetInstance().GetIsUp("S"))
	{
		hero_->ChangeDirection(float4::DOWN);
	}
	else if (true == J_Input::GetInstance().GetIsUp("A"))
	{
		hero_->ChangeDirection(float4::LEFT);
	}
	else if (true == J_Input::GetInstance().GetIsUp("D"))
	{
		hero_->ChangeDirection(float4::RIGHT);
	}
}

void Chapter::SetChapterNumber()
{	
	std::string chapterName = std::string(GetName());
	int cutStartIndex = 0;
	while ('0' > chapterName[cutStartIndex] || '9' < chapterName[cutStartIndex] )
	{
		++cutStartIndex;
	}
	chapterNumber_ = std::stoi(chapterName.substr(cutStartIndex));
}

Dialogue* Chapter::FindDialogue(int _index)
{
	if (0 > _index || allDialogues_.size() - 1 < _index)
	{
		J_GameEngineDebug::AssertFalse("allDialogues size out.");
		return nullptr;
	}
	return allDialogues_[_index];
}

void Chapter::PushBackSpecialDialogue(Dialogue* _dialogue)
{
	allDialogues_.push_back(_dialogue);
}

void Chapter::SetCurDialogue(int _index)
{
	if (true == allDialogues_.empty())
	{
		J_GameEngineDebug::AssertFalse();
		return;
	}

	if (-1 > _index && allDialogues_.size() - 1 < _index)
	{
		J_GameEngineDebug::AssertFalse();
		return;
	}

	if (-1 == _index)
	{
		for (size_t i = 0; i < allDialogues_.size(); i++)
		{
			allDialogues_[i]->SetIsCurDialogue(false);
		}
		curDialogue_ = nullptr;
	}
	else
	{
		for (size_t i = 0; i < allDialogues_.size(); i++)
		{
			if (i == _index)
			{
				allDialogues_[i]->SetIsCurDialogue(true);
				continue;
			}
			allDialogues_[i]->SetIsCurDialogue(false);
		}
		curDialogue_ = FindDialogue(_index);
	}
}

void Chapter::SetIsTileVisible(bool _isTileVisible)
{
	for (size_t y = 0; y < allTiles_.size(); y++)
	{
		for (size_t x = 0; x < allTiles_[y].size(); x++)
		{
			if (nullptr == allTiles_[y][x])
			{
				J_GameEngineDebug::AssertFalse("This tile is nullptr.");
				continue;
			}
			allTiles_[y][x]->SetIsVisible(_isTileVisible);
		}
	}
}

void Chapter::SwitchThornUpDown()
{
	for (size_t y = 0; y < allTiles_.size(); y++)
	{
		for (size_t x = 0; x < allTiles_[y].size(); x++)
		{
			if (TileState::THORN_UP == allTiles_[y][x]->tileState_)
			{
				allTiles_[y][x]->tileState_ = TileState::THORN_DOWN;
			}
			else if (TileState::THORN_DOWN == allTiles_[y][x]->tileState_)
			{
				allTiles_[y][x]->tileState_ = TileState::THORN_UP;
			}
		}
	}
}

void Chapter::RenderTransition()
{
	if (nullptr == backBufferImage_)
	{
		J_GameEngineDebug::AssertFalse("bakcBufferImage is null.");
		return;
	}

	transitionSoundChangeDelay_ += J_GameEngineTime::GetInstance().GetDeltaTimeF();
	curFrameDelay_ -= J_GameEngineTime::GetInstance().GetDeltaTimeF();
	if (0.0f >= curFrameDelay_)
	{
		curFrameDelay_ = transitionDelay_;
		if (30 <= curFrameIndex_)
		{
			curFrameIndex_ = 30;
			if (2.0f <= transitionSoundChangeDelay_)
			{
				isTransitionOn_ = false;
				curFrameIndex_ = 0;
			}
			return;
		}
		else
		{
			++curFrameIndex_;
		}
	}
	backBufferImage_->PasteOnBackBuffer(transition_[curFrameIndex_],
		{ -2, -2 },
		transition_[curFrameIndex_]->GetImageSize(),
		float4::ZERO,
		transition_[curFrameIndex_]->GetImageSize()
	);

	
	transitionSound_Player1_->PlayCurSound();

	if(1.0f <= transitionSoundChangeDelay_)
	{
		transitionSound_Player2_->PlayCurSound();
	}
}

void Chapter::LevelRender()
{
	if (true == isTransitionOn_)
	{
		RenderTransition();
	}
}

