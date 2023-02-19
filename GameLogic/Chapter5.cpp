#include "Chapter5.h"
#include "Demon.h"
#include "Skeleton.h"
#include "Stone.h"
#include "Tile.h"
#include "Dialogue.h"
#include "Button.h"
#include "Hero.h"

Chapter5::Chapter5(): zdrada_(nullptr)
{
}

Chapter5::~Chapter5()
{
}

void Chapter5::LoadLevel()
{
	ClearChapter();
	SetChapterNumber();
	CreateTransition();
	CreateDefaultBG();

	CreateTiles({ 510, 155 }, 9, 9);
	FindTile(1, 1)->InitTileState(TileState::WALL);
	FindTile(1, 2)->InitTileState(TileState::WALL);
	FindTile(1, 3)->InitTileState(TileState::WALL);
	FindTile(1, 4)->InitTileState(TileState::WALL);
	FindTile(1, 5)->InitTileState(TileState::WALL);
	FindTile(1, 6)->InitTileState(TileState::WALL);
	FindTile(1, 7)->InitTileState(TileState::WALL);
	FindTile(2, 7)->InitTileState(TileState::WALL);
	FindTile(3, 7)->InitTileState(TileState::WALL);
	FindTile(4, 7)->InitTileState(TileState::WALL);
	FindTile(5, 7)->InitTileState(TileState::WALL);
	FindTile(6, 7)->InitTileState(TileState::WALL);
	FindTile(2, 1)->InitTileState(TileState::WALL);
	FindTile(2, 2)->InitTileState(TileState::WALL);
	FindTile(3, 1)->InitTileState(TileState::WALL);
	FindTile(3, 2)->InitTileState(TileState::WALL);
	FindTile(3, 3)->InitTileState(TileState::WALL);
	FindTile(3, 4)->InitTileState(TileState::WALL);
	FindTile(3, 5)->InitTileState(TileState::WALL);
	FindTile(4, 1)->InitTileState(TileState::WALL);
	FindTile(7, 1)->InitTileState(TileState::WALL);

	FindTile(2, 6)->InitTileState(TileState::THORN_DOWN);
	FindTile(4, 6)->InitTileState(TileState::THORN_DOWN);
	FindTile(7, 6)->InitTileState(TileState::THORN_DOWN);
	FindTile(4, 3)->InitTileState(TileState::THORN_DOWN);
	FindTile(5, 4)->InitTileState(TileState::THORN_DOWN);
	FindTile(7, 4)->InitTileState(TileState::THORN_DOWN);

	CreateHero(23, 2, 3);
	zdrada_ = CreateDemon("zdrada", 6, 1);
	SetGoalTileIndex({ 5, 1 }, { 6, 2 });

	CreateKey(7, 7);
	CreateLock(5, 2);

	CreateSkeleton(2, 5);

	CreateStone(4, 5);
	CreateStone(5, 5);
	CreateStone(6, 5);
	CreateStone(7, 5);
	CreateStone(6, 2);
	CreateStone(6, 3);

	//CreateDialogue("");
//FindDialogue(0)->SetIntroduction("，  ，");
//FindDialogue(0)->SetLine0("");
//FindDialogue(0)->SetLine1("");
//FindDialogue(0)->FindButton(0)->SetButtonText("");
//FindDialogue(0)->FindButton(1)->SetButtonText("");
//SetCurDialogue(0);

//CreateDialogue("", "", 0, -1);
//FindDialogue(1)->SetIntroduction("，  ，");
//FindDialogue(1)->SetLine0("");
//FindDialogue(1)->SetLine1("");

//CreateDialogue("", "", 0, 1);
//FindDialogue(2)->SetIntroduction("，  ，");
//FindDialogue(2)->SetLine0("");
//FindDialogue(2)->SetLine1("");

	CreateDialogue("z_idle.bmp");
	FindDialogue(0)->SetIntroduction("， Zdrada, the Bitch Demon ，");
	FindDialogue(0)->SetLine0("Yo. I've heard about your harem. I'm in.");
	FindDialogue(0)->SetLine1("");
	FindDialogue(0)->FindButton(0)->SetButtonText("Wait. I have a feeling I'll regret it.");
	FindDialogue(0)->FindButton(1)->SetButtonText("It's not really a harem anymore. We just play turn based strategies.");
	SetCurDialogue(0);
	
	CreateDialogue("z_idle.bmp", "", "", 0, -1);
	FindDialogue(1)->SetIntroduction("， Zdrada, the Bitch Demon ，");
	FindDialogue(1)->SetLine0("Holy shit. Let me put you out of your misery.");
	FindDialogue(1)->SetLine1("");
	
	CreateDialogue("z_laugh.bmp", "", "", 0, 1);
	FindDialogue(2)->SetIntroduction("， Zdrada, the Bitch Demon ，");
	FindDialogue(2)->SetLine0("Too bad, I'm coming anyway. Go ahead, try to stop me.");
	FindDialogue(2)->SetLine1("");
}

void Chapter5::UpdateLevel()
{
	ManageInput();
}

void Chapter5::RespondSelection(int _index)
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
		zdrada_->SetIsWin();
		SetCurDialogue(_index);
	}
}
