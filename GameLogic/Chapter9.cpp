#include "Chapter9.h"
#include "Demon.h"
#include "Skeleton.h"
#include "Stone.h"
#include "Tile.h"
#include "Dialogue.h"
#include "Button.h"
#include "Hero.h"
#include <J_Window.h>

Chapter9::Chapter9()
{
}

Chapter9::~Chapter9()
{
}

void Chapter9::LoadLevel()
{
	ClearChapter();
	SetChapterNumber();
	CreateTransition();
	CreateDefaultBG();

	CreateTiles({ 460, 300 }, 11, 8);
	FindTile(1, 1)->InitTileState(TileState::WALL);
	FindTile(2, 1)->InitTileState(TileState::WALL);
	FindTile(3, 1)->InitTileState(TileState::WALL);
	FindTile(1, 2)->InitTileState(TileState::WALL);
	FindTile(2, 2)->InitTileState(TileState::WALL);
	FindTile(3, 2)->InitTileState(TileState::WALL);
	FindTile(1, 3)->InitTileState(TileState::WALL);
	FindTile(3, 3)->InitTileState(TileState::WALL);
	FindTile(1, 6)->InitTileState(TileState::WALL);
	FindTile(9, 6)->InitTileState(TileState::WALL);
	FindTile(7, 1)->InitTileState(TileState::WALL);
	FindTile(8, 1)->InitTileState(TileState::WALL);
	FindTile(9, 1)->InitTileState(TileState::WALL);
	FindTile(7, 2)->InitTileState(TileState::WALL);
	FindTile(8, 2)->InitTileState(TileState::WALL);
	FindTile(9, 2)->InitTileState(TileState::WALL);
	FindTile(7, 3)->InitTileState(TileState::WALL);
	FindTile(9, 3)->InitTileState(TileState::WALL);
	
	CreateHero(33, 2, 6);

	SetGoalTileIndex({ 5, 1 });

	CreateStone(1, 4);
	CreateStone(2, 3);
	CreateStone(2, 5);
	CreateStone(3, 5);
	CreateStone(4, 2);
	CreateStone(4, 3);
	CreateStone(4, 4);
	CreateStone(4, 5);
	CreateStone(4, 6);
	CreateStone(5, 4);
	CreateStone(6, 4);
	CreateStone(7, 5);
	CreateStone(6, 2);
	CreateStone(8, 5);
	CreateStone(7, 6);


	CreateKey(9, 4);
	CreateLock(5, 2);

	CreateDialogue("epilogue.bmp", "", "", 0, 0);
	FindDialogue(0)->SetIntroduction("");
	FindDialogue(0)->SetLine0("And that was the story of the Helltaker.");
	FindDialogue(0)->SetLine1("");
	SetCurDialogue(0);

	CreateDialogue("epilogue.bmp", "", "", 0, 0);
	FindDialogue(1)->SetIntroduction("");
	FindDialogue(1)->SetLine0("Until next.");
	FindDialogue(1)->SetLine1("");

	CreateDialogue("epilogue.bmp", "", "", 0, 0);
	FindDialogue(2)->SetIntroduction("");
	FindDialogue(2)->SetLine0("THE END.");
	FindDialogue(2)->SetLine1("");

	CreateDialogue("ending.bmp", "", "", 0, 0);
	FindDialogue(3)->SetIntroduction("");
	FindDialogue(3)->SetLine0("Thank you for watching.");
	FindDialogue(3)->SetLine1("");




}

void Chapter9::UpdateLevel()
{
	ManageInput();
}

void Chapter9::RespondSelection(int _index)
{
	if (curDialogue_ == FindDialogue(0))
	{
		SetCurDialogue(1);
	}
	else if (curDialogue_ == FindDialogue(1))
	{
		SetCurDialogue(2);
	}	
	else if (curDialogue_ == FindDialogue(2))
	{
		SetCurDialogue(3);
	}	
	else if (curDialogue_ == FindDialogue(3))
	{
		ChangeToNextChapter();
	}
}
