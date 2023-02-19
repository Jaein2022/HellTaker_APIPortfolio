#include "Chapter4.h"
#include "Demon.h"
#include "Skeleton.h"
#include "Stone.h"
#include "Tile.h"
#include "Dialogue.h"
#include "Button.h"
#include "Hero.h"

Chapter4::Chapter4(): malina_(nullptr)
{
}

Chapter4::~Chapter4()
{
}

void Chapter4::LoadLevel()
{
	ClearChapter();
	SetChapterNumber();
	CreateTransition();
	CreateDefaultBG();

	CreateTiles({510, 255}, 10, 7);
	FindTile(2, 1)->InitTileState(TileState::WALL);
	FindTile(6, 1)->InitTileState(TileState::WALL);
	FindTile(7, 1)->InitTileState(TileState::WALL);
	FindTile(8, 1)->InitTileState(TileState::WALL);
	FindTile(8, 2)->InitTileState(TileState::WALL);
	FindTile(1, 5)->InitTileState(TileState::WALL);
	FindTile(7, 5)->InitTileState(TileState::WALL);
	FindTile(8, 5)->InitTileState(TileState::WALL);

	FindTile(3, 2)->InitTileState(TileState::THORN_FIXED);
	FindTile(4, 2)->InitTileState(TileState::THORN_FIXED);


	CreateHero(23, 1, 1);
	malina_ = CreateDemon("malina", 8, 3);
	SetGoalTileIndex({ 7, 3 }, { 8, 4 });

	CreateKey(3, 1);
	CreateLock(6, 2);

	CreateStone(5, 1);
	CreateStone(2, 2);
	CreateStone(4, 2);
	CreateStone(1, 3);
	CreateStone(3, 3);
	CreateStone(5, 3);
	CreateStone(6, 3);
	CreateStone(2, 4);
	CreateStone(4, 4);
	CreateStone(6, 4);
	CreateStone(7, 4);
	CreateStone(3, 5);
	CreateStone(5, 5);

	CreateDialogue("mal_idle.bmp");
	FindDialogue(0)->SetIntroduction("， Malina, the Sour Demon ，");
	FindDialogue(0)->SetLine0("Great, more braindead idiots... Never seen your ugly face before.");
	FindDialogue(0)->SetLine1("What are you playing at?");
	FindDialogue(0)->FindButton(0)->SetButtonText("I'd sure love to play with you.");
	FindDialogue(0)->FindButton(1)->SetButtonText("This is delicious. Please, insult me more.");
	SetCurDialogue(0);

	CreateDialogue("mal_idle.bmp", "", "", 0, -1);
	FindDialogue(1)->SetIntroduction("， Malina, the Sour Demon ，");
	FindDialogue(1)->SetLine0("FanTastic. Just my luck to find another masochist creep.");
	FindDialogue(1)->SetLine1("");

	CreateDialogue("mal_puzzled.bmp", "", "", 0, 1);
	FindDialogue(2)->SetIntroduction("， Malina, the Sour Demon ，");
	FindDialogue(2)->SetLine0("Like what... video games? Sure, why not. As long as you're okay");
	FindDialogue(2)->SetLine1("with turn base strategies.");
}

void Chapter4::UpdateLevel()
{
	ManageInput();
}

void Chapter4::RespondSelection(int _index)
{
	if (curDialogue_ == FindDialogue(0))
	{
		if (0 == _index)
		{
			SetCurDialogue(2);
		}
		else if (1 == _index)
		{
			SetCurDialogue(1);
		}
	}
	else if (curDialogue_ == FindDialogue(1))
	{
		ResetLevel();
	}
	else if (curDialogue_ == FindDialogue(2))
	{
		hero_->SetIsWin();
		malina_->SetIsWin();
		SetCurDialogue(_index);
	}
}

