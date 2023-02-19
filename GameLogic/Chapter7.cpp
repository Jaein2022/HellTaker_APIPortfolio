#include "Chapter7.h"
#include "Demon.h"
#include "Skeleton.h"
#include "Stone.h"
#include "Tile.h"
#include "Dialogue.h"
#include "Button.h"
#include "Hero.h"

Chapter7::Chapter7(): justice_(nullptr)
{
}

Chapter7::~Chapter7()
{
}

void Chapter7::LoadLevel()
{
	ClearChapter();
	SetChapterNumber();
	CreateTransition();
	CreateDefaultBG();

	CreateTiles({ 610, 150 }, 8, 9);
	FindTile(1, 1)->InitTileState(TileState::WALL);
	FindTile(2, 1)->InitTileState(TileState::WALL);
	FindTile(3, 1)->InitTileState(TileState::WALL);
	FindTile(1, 2)->InitTileState(TileState::WALL);
	FindTile(2, 2)->InitTileState(TileState::WALL);
	FindTile(3, 2)->InitTileState(TileState::WALL);
	FindTile(3, 3)->InitTileState(TileState::WALL);
	FindTile(2, 5)->InitTileState(TileState::WALL);
	FindTile(2, 6)->InitTileState(TileState::WALL);
	FindTile(3, 6)->InitTileState(TileState::WALL);
	FindTile(6, 1)->InitTileState(TileState::WALL);
	FindTile(5, 6)->InitTileState(TileState::WALL);
	FindTile(6, 6)->InitTileState(TileState::WALL);
	FindTile(5, 7)->InitTileState(TileState::WALL);
	FindTile(6, 7)->InitTileState(TileState::WALL);

	FindTile(4, 6)->InitTileState(TileState::THORN_DOWN);
	FindTile(4, 7)->InitTileState(TileState::THORN_UP);
	FindTile(3, 7)->InitTileState(TileState::THORN_DOWN);
	FindTile(2, 7)->InitTileState(TileState::THORN_UP);
	FindTile(1, 7)->InitTileState(TileState::THORN_DOWN);
	FindTile(1, 6)->InitTileState(TileState::THORN_UP);


	CreateHero(32, 6, 5);
	justice_ = CreateDemon("justice", 4, 1);
	SetGoalTileIndex({ 5, 1 }, { 4, 2 });

	CreateSkeleton(3, 5);
	CreateSkeleton(4, 4);
	CreateSkeleton(1, 4);

	CreateStone(5, 4);
	CreateStone(4, 3);
	CreateStone(5, 3);
	CreateStone(6, 3);
	CreateStone(2, 4);

	CreateKey(2, 3);
	CreateLock(5, 2);

	CreateDialogue("jus_curious.bmp");
	FindDialogue(0)->SetIntroduction("， Justice, the Awesome Demon ，");
	FindDialogue(0)->SetLine0("Yo, did you just solve that puzzle? That's awesome!");
	FindDialogue(0)->SetLine1("");
	FindDialogue(0)->FindButton(0)->SetButtonText("I took some work. Wanna join my harem?");
	FindDialogue(0)->FindButton(1)->SetButtonText("I just skipped it in the menu. Wanna join my harem?");
	SetCurDialogue(0);
	
	CreateDialogue("jus_idle.bmp", "", "", 0, 1);
	FindDialogue(1)->SetIntroduction("， Justice, the Awesome Demon ，");
	FindDialogue(1)->SetLine0("You don't have to ask me. I'd never miss a party.");
	FindDialogue(1)->SetLine1("");
	
	CreateDialogue("jus_idle.bmp", "", "", 0, 1);
	FindDialogue(2)->SetIntroduction("， Justice, the Awesome Demon ，");
	FindDialogue(2)->SetLine0("That's totally sounds like something I would've done.");
	FindDialogue(2)->SetLine1("Sure, let's go. The more the merrier, right?");
}

void Chapter7::UpdateLevel()
{
	ManageInput();
}

void Chapter7::RespondSelection(int _index)
{
	if (curDialogue_ == FindDialogue(0))
	{
		if (0 == _index)
		{
			SetCurDialogue(1);
		}
		else if (1 == _index)
		{
			SetCurDialogue(2);
		}
	}
	else if (curDialogue_ == FindDialogue(1))
	{
		hero_->SetIsWin();
		justice_->SetIsWin();
		SetCurDialogue(_index);
	}
	else if (curDialogue_ == FindDialogue(2))
	{
		hero_->SetIsWin();
		justice_->SetIsWin();
		SetCurDialogue(_index);
	}
}
