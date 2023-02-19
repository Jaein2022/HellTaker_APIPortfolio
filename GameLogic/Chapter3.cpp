#include "Chapter3.h"
#include "Demon.h"
#include "Skeleton.h"
#include "Stone.h"
#include "Tile.h"
#include "Dialogue.h"
#include "Button.h"
#include "Hero.h"

Chapter3::Chapter3(): cerberus0_(nullptr), cerberus1_(nullptr), cerberus2_(nullptr)
{
}

Chapter3::~Chapter3()
{
}

void Chapter3::LoadLevel()
{
	ClearChapter();
	SetChapterNumber();
	CreateTransition();
	CreateDefaultBG();
	
	CreateTiles({ 510, 155 }, 10, 9);
	FindTile(1, 1)->InitTileState(TileState::WALL);
	FindTile(2, 1)->InitTileState(TileState::WALL);
	FindTile(3, 1)->InitTileState(TileState::WALL);
	FindTile(1, 2)->InitTileState(TileState::WALL);
	FindTile(2, 2)->InitTileState(TileState::WALL);
	FindTile(3, 2)->InitTileState(TileState::WALL);
	FindTile(4, 2)->InitTileState(TileState::WALL);
	FindTile(5, 2)->InitTileState(TileState::WALL);
	FindTile(6, 2)->InitTileState(TileState::WALL);
	FindTile(1, 3)->InitTileState(TileState::WALL);
	FindTile(2, 3)->InitTileState(TileState::WALL);
	FindTile(1, 4)->InitTileState(TileState::WALL);
	FindTile(2, 4)->InitTileState(TileState::WALL);
	FindTile(1, 5)->InitTileState(TileState::WALL);
	FindTile(2, 5)->InitTileState(TileState::WALL);
	FindTile(2, 6)->InitTileState(TileState::WALL);
	FindTile(4, 4)->InitTileState(TileState::WALL);
	FindTile(6, 4)->InitTileState(TileState::WALL);
	FindTile(4, 6)->InitTileState(TileState::WALL);
	FindTile(6, 6)->InitTileState(TileState::WALL);
	FindTile(8, 1)->InitTileState(TileState::WALL);
	FindTile(8, 2)->InitTileState(TileState::WALL);
	FindTile(8, 5)->InitTileState(TileState::WALL);
	FindTile(8, 6)->InitTileState(TileState::WALL);
	FindTile(8, 7)->InitTileState(TileState::WALL);


	FindTile(4, 3)->InitTileState(TileState::THORN_FIXED);
	FindTile(5, 3)->InitTileState(TileState::THORN_FIXED);									   
	FindTile(6, 5)->InitTileState(TileState::THORN_FIXED);
	FindTile(7, 5)->InitTileState(TileState::THORN_FIXED);
	FindTile(3, 4)->InitTileState(TileState::THORN_FIXED);
	FindTile(5, 4)->InitTileState(TileState::THORN_FIXED);
	FindTile(3, 6)->InitTileState(TileState::THORN_FIXED);
	FindTile(5, 6)->InitTileState(TileState::THORN_FIXED);


	CreateHero(32, 8, 3);
	CreateKey(1, 6);
	CreateLock(7, 2);


	cerberus0_ = CreateDemon("cerberus0", 4, 1);
	cerberus1_ = CreateDemon("cerberus1", 5, 1);
	cerberus2_ = CreateDemon("cerberus2", 6, 1);
	SetGoalTileIndex({ 7, 1 });

	CreateSkeleton(5, 5);
	CreateSkeleton(6, 7);

	CreateDialogue("cer_idle.bmp");
	FindDialogue(0)->SetIntroduction("， Cerberus, the Triple Demon ，");
	FindDialogue(0)->SetLine0("Are you a human? A real human? Please, take us with you.");
	FindDialogue(0)->SetLine1();
	FindDialogue(0)->FindButton(0)->SetButtonText("Deal. No question asked.");
	FindDialogue(0)->FindButton(1)->SetButtonText("This is getting too easy. I have questions.");
	SetCurDialogue(0);

	CreateDialogue("cer_idle.bmp", "", "", 0, -1);
	FindDialogue(1)->SetIntroduction("， Cerberus, the Triple Demon ，");
	FindDialogue(1)->SetLine0("We need a human to cross the hell's gate. You don't have to be in");
	FindDialogue(1)->SetLine1("one piece, though.");

	CreateDialogue("cer_happy.bmp", "", "", 0, 1);
	FindDialogue(2)->SetIntroduction("， Cerberus, the Triple Demon ，");
	FindDialogue(2)->SetLine0("Yes! At last! It's time to corrupt the mortal realm!");
	FindDialogue(2)->SetLine1();
}

void Chapter3::UpdateLevel()
{
	ManageInput();
}

void Chapter3::RespondSelection(int _index)
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
		cerberus0_->SetIsWin();
		cerberus1_->SetIsWin();
		cerberus2_->SetIsWin();
		SetCurDialogue(_index);
	}
}

