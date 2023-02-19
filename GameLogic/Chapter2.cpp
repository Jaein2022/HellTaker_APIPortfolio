#include "Chapter2.h"
#include "Demon.h"
#include "Skeleton.h"
#include "Stone.h"
#include "Tile.h"
#include "Dialogue.h"
#include "Button.h"
#include "Hero.h"

Chapter2::Chapter2(): modeus_(nullptr)
{
}

Chapter2::~Chapter2()
{
}

void Chapter2::LoadLevel()
{
	ClearChapter();
	SetChapterNumber();
	CreateTransition();
	CreateDefaultBG();

	CreateTiles({ 560, 205 }, 9, 8);
	FindTile(1, 6)->InitTileState(TileState::WALL);
	FindTile(2, 6)->InitTileState(TileState::WALL);
	FindTile(3, 6)->InitTileState(TileState::WALL);
	FindTile(4, 6)->InitTileState(TileState::WALL);
	FindTile(3, 2)->InitTileState(TileState::WALL);
	FindTile(3, 3)->InitTileState(TileState::WALL);
	FindTile(3, 4)->InitTileState(TileState::WALL);
	FindTile(3, 5)->InitTileState(TileState::WALL);
	FindTile(4, 3)->InitTileState(TileState::WALL);
	FindTile(4, 4)->InitTileState(TileState::WALL);
	FindTile(4, 5)->InitTileState(TileState::WALL);
	FindTile(1, 1)->InitTileState(TileState::WALL);
	FindTile(1, 2)->InitTileState(TileState::WALL);
	FindTile(6, 1)->InitTileState(TileState::WALL);
	FindTile(7, 1)->InitTileState(TileState::WALL);

	FindTile(2, 3)->InitTileState(TileState::THORN_FIXED);
	FindTile(4, 2)->InitTileState(TileState::THORN_FIXED);
	FindTile(5, 2)->InitTileState(TileState::THORN_FIXED);
	FindTile(5, 3)->InitTileState(TileState::THORN_FIXED);
	FindTile(6, 3)->InitTileState(TileState::THORN_FIXED);
	FindTile(6, 4)->InitTileState(TileState::THORN_FIXED);



	

	//나머지 액터들 생성과 설정.
	CreateHero(24 /*24*/, 1, 5);
	modeus_ = CreateDemon("modeus", 5, 6);
	SetGoalTileIndex({ 5, 5 }, { 6, 6 });		//히어로 도착점 설정. 

	CreateSkeleton(2, 2);
	CreateSkeleton(6, 5);
	CreateSkeleton(7, 6);
	CreateStone(5, 3);
	CreateStone(6, 3);
	CreateStone(7, 3);

	CreateDialogue("mod_idle.bmp");
	FindDialogue(0)->SetIntroduction("· Modeus, the Lustful Demon ·");
	FindDialogue(0)->SetLine0("You and me. Now.");
	FindDialogue(0)->SetLine1();
	FindDialogue(0)->FindButton(0)->SetButtonText("Deal. No question asked.");
	FindDialogue(0)->FindButton(1)->SetButtonText("No time. Busy gathering girls.");
	SetCurDialogue(0);

	CreateDialogue("mod_idle.bmp", "", "", 0, -1);
	FindDialogue(1)->SetIntroduction("· Modeus, the Lustful Demon ·");
	FindDialogue(1)->SetLine0("They always said that... and they always try to run away.");
	FindDialogue(1)->SetLine1("I'll have to break your knees, just in case.");

	CreateDialogue("mod_close.bmp", "", "", 0, 1);
	FindDialogue(2)->SetIntroduction("· Modeus, the Lustful Demon ·");
	FindDialogue(2)->SetLine0("Demon harem? You poor fool... They will rip you to shreds, and I");
	FindDialogue(2)->SetLine1("HAVE to see this.");

}

void Chapter2::UpdateLevel()
{
	ManageInput();
}

void Chapter2::RespondSelection(int _index)
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
		ResetLevel();
	}
	else if (curDialogue_ == FindDialogue(2))
	{
		hero_->SetIsWin();
		modeus_->SetIsWin();
		SetCurDialogue(_index);
	}
}
