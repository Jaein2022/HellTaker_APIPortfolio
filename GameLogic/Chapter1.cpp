#include "Chapter1.h"
#include "Skeleton.h"
#include "Stone.h"
#include "Demon.h"
#include "Tile.h"
#include "Dialogue.h"
#include "Button.h"
#include "Hero.h"

Chapter1::Chapter1(): pandemonica_(nullptr)
{
}

Chapter1::~Chapter1()
{
}

void Chapter1::LoadLevel()
{
	ClearChapter();
	SetChapterNumber();
	CreateTransition();
	CreateDefaultBG();

	//타일 생성과 설정.
	CreateTiles({ 555, 205 }, 9, 8);
	FindTile(1, 1)->InitTileState(TileState::WALL);
	FindTile(1, 2)->InitTileState(TileState::WALL);
	FindTile(1, 3)->InitTileState(TileState::WALL);
	FindTile(2, 1)->InitTileState(TileState::WALL);
	FindTile(3, 1)->InitTileState(TileState::WALL);
	FindTile(4, 1)->InitTileState(TileState::WALL);
	FindTile(7, 1)->InitTileState(TileState::WALL);
	FindTile(7, 2)->InitTileState(TileState::WALL);
	FindTile(7, 3)->InitTileState(TileState::WALL);
	FindTile(7, 4)->InitTileState(TileState::WALL);
	FindTile(7, 5)->InitTileState(TileState::WALL);
	FindTile(3, 4)->InitTileState(TileState::WALL);
	FindTile(4, 4)->InitTileState(TileState::WALL);
	FindTile(5, 4)->InitTileState(TileState::WALL);
	FindTile(6, 3)->InitTileState(TileState::WALL);

	
	//나머지 액터들 생성과 설정.

	CreateHero(23 /*23*/, 6, 1);
	pandemonica_ = CreateDemon("pandemonica", 7, 6);
	SetGoalTileIndex({ 6, 6 });		//플레이어 도착점 설정.


	CreateSkeleton(4, 2);
	CreateSkeleton(5, 3);
	CreateSkeleton(3, 3);
	CreateStone(2, 5);
	CreateStone(2, 6);
	CreateStone(5, 5);
	CreateStone(4, 6);

	CreateDialogue("pand_idle.bmp");
	FindDialogue(0)->SetIntroduction("· Pandemonica, the Tired Demon ·");
	FindDialogue(0)->SetLine0("Name's Pandemonica, Hell's Customer Service.");
	FindDialogue(0)->SetLine1("How may I serve you?");
	FindDialogue(0)->FindButton(0)->SetButtonText("We can figure something out at my place.");
	FindDialogue(0)->FindButton(1)->SetButtonText("Maybe I can serve YOU instead?");
	SetCurDialogue(0);

	CreateDialogue("pand_idle.bmp", "", "", 0, -1);
	FindDialogue(1)->SetIntroduction("· Pandemonica, the Tired Demon ·");
	FindDialogue(1)->SetLine0("You Thought you're leaving hell alive? How delusional.");

	CreateDialogue("pand_flust.bmp", "", "", 0, 1);
	FindDialogue(2)->SetIntroduction("· Pandemonica, the Tired Demon ·");
	FindDialogue(2)->SetLine0("Sweet of you to offer. I could really use some coffee.");
	FindDialogue(2)->SetLine1("I'm not myself without it.");

}

void Chapter1::UpdateLevel()
{
	ManageInput();
}

void Chapter1::RespondSelection(int _index)
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
	else if(curDialogue_ == FindDialogue(1))
	{
		ResetLevel();
	}
	else if(curDialogue_ == FindDialogue(2))
	{
		hero_->SetIsWin();
		pandemonica_->SetIsWin();
		SetCurDialogue(_index);
	}
}
