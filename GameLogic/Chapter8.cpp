#include "Chapter8.h"
#include "Tile.h"
#include "Dialogue.h"
#include "Button.h"
#include "Hero.h"
#include "Demon.h"

Chapter8::Chapter8(): lucifer_(nullptr)
{
}

Chapter8::~Chapter8()
{
}

void Chapter8::LoadLevel()
{
	ClearChapter();
	SetChapterNumber();
	CreateTransition();
	CreateDefaultBG();

	CreateTiles({ 460, 560 }, 11, 15);
	FindTile(1, 2)->InitTileState(TileState::WALL);
	FindTile(2, 2)->InitTileState(TileState::WALL);
	FindTile(3, 2)->InitTileState(TileState::WALL);
	FindTile(4, 2)->InitTileState(TileState::WALL);
	FindTile(5, 2)->InitTileState(TileState::WALL);
	FindTile(6, 2)->InitTileState(TileState::WALL);
	FindTile(7, 2)->InitTileState(TileState::WALL);
	FindTile(8, 2)->InitTileState(TileState::WALL);
	FindTile(9, 2)->InitTileState(TileState::WALL);

	FindTile(3, 11)->InitTileState(TileState::WALL);
	FindTile(7, 11)->InitTileState(TileState::WALL);
	FindTile(3, 9)->InitTileState(TileState::WALL);
	FindTile(7, 9)->InitTileState(TileState::WALL);
	FindTile(3, 7)->InitTileState(TileState::WALL);
	FindTile(7, 7)->InitTileState(TileState::WALL);
	FindTile(3, 5)->InitTileState(TileState::WALL);
	FindTile(7, 5)->InitTileState(TileState::WALL);

	
	CreateHero(12, 5, 12);
	lucifer_ = CreateDemon("lucifer", 5, 1);
	SetGoalTileIndex({ 5, 3 });

	CreateSkeleton(5, 10);
	CreateSkeleton(5, 9);
	CreateSkeleton(5, 8);
	CreateSkeleton(5, 7);
	CreateSkeleton(5, 6);
	CreateSkeleton(5, 5);
	CreateSkeleton(5, 4);
	CreateSkeleton(5, 3);
	
	CreateDialogue("LH_idle.bmp", "man_skele.bmp", "man_skele.bmp", 0, 0);
	FindDialogue(0)->SetIntroduction("， Lucifer, the CEO of Hell ，");
	FindDialogue(0)->SetLine0("We meet at last. You proved yourself worthy to by passing all my");
	FindDialogue(0)->SetLine1("trials.");
	SetCurDialogue(0);

	CreateDialogue("LH_idle.bmp", "man_skele.bmp", "man_skele.bmp", 2, 0);
	FindDialogue(1)->SetIntroduction("， Lucifer, the CEO of Hell ，");
	FindDialogue(1)->SetLine0("Pledge your soul to me and I'll make you my most treasured slave.");
	FindDialogue(1)->SetLine1("");
	FindDialogue(1)->FindButton(0)->SetButtonText("Yes, my queen!");
	FindDialogue(1)->FindButton(1)->SetButtonText("No, thanks. But you can join my harem.");

	CreateDialogue("LH_idle.bmp", "man_skele.bmp", "man_skele.bmp", 0, -1);
	FindDialogue(2)->SetIntroduction("， Lucifer, the CEO of Hell ，");
	FindDialogue(2)->SetLine0("Eager little soul...");
	FindDialogue(2)->SetLine1("");

	CreateDialogue("LH_angry.bmp", "man_skele.bmp", "man_skele.bmp", 2, 0);
	FindDialogue(3)->SetIntroduction("， Lucifer, the CEO of Hell ，");
	FindDialogue(3)->SetLine0("What are you trying to accomplish? You think you can enslave");
	FindDialogue(3)->SetLine1("demons yo your will?");
	FindDialogue(3)->FindButton(0)->SetButtonText("Call me master. And ask for permision before you speak.");
	FindDialogue(3)->FindButton(1)->SetButtonText("I can offer coffee, turn based strategies and chocolate pancakes.");

	CreateDialogue("LH_angry.bmp", "man_skele.bmp", "man_skele.bmp", 0, -1);
	FindDialogue(4)->SetIntroduction("， Lucifer, the CEO of Hell ，");
	FindDialogue(4)->SetLine0("I see I have to teach you your place.");
	FindDialogue(4)->SetLine1("");

	CreateDialogue("LH_angry.bmp", "man_skele.bmp", "man_skele.bmp", 0, 0);
	FindDialogue(5)->SetIntroduction("， Lucifer, the CEO of Hell ，");
	FindDialogue(5)->SetLine0("Really? Is that it? You come here, and try to buy me over with");
	FindDialogue(5)->SetLine1("pancakes?");

	CreateDialogue("LH_happy.bmp", "man_skele.bmp", "man_skele.bmp", 0, 1);
	FindDialogue(6)->SetIntroduction("， Lucifer, the CEO of Hell ，");
	FindDialogue(6)->SetLine0("You're lucky I have a thing for pancakes.");
	FindDialogue(6)->SetLine1("");

	CreateDialogue("LH_happy.bmp", "man_skele.bmp", "man_skele.bmp", 0, 0);
	FindDialogue(7)->SetIntroduction("， Lucifer, the CEO of Hell ，");
	FindDialogue(7)->SetLine0("I think you've convinced me. That harem of yours may prove to be");
	FindDialogue(7)->SetLine1("entertaining after all.");
}

void Chapter8::UpdateLevel()
{
	ManageInput();
}

void Chapter8::RespondSelection(int _index)
{
	if (curDialogue_ == FindDialogue(0))
	{
		SetCurDialogue(1);
	}
	else if (curDialogue_ == FindDialogue(1))
	{
		if (0 == _index)
		{
			SetCurDialogue(2);
		}
		else if (1 == _index)
		{
			SetCurDialogue(3);
		}
	}
	else if (curDialogue_ == FindDialogue(2))
	{
		ResetLevel();
	}	
	else if (curDialogue_ == FindDialogue(3))
	{
		if (0 == _index)
		{
			SetCurDialogue(4);
		}
		else if (1 == _index)
		{
			SetCurDialogue(5);
		}
	}	
	else if (curDialogue_ == FindDialogue(4))
	{
		ResetLevel();
	}	
	else if (curDialogue_ == FindDialogue(5))
	{
		SetCurDialogue(6);
	}	
	else if (curDialogue_ == FindDialogue(6))
	{
		SetCurDialogue(7);
	}	
	else if (curDialogue_ == FindDialogue(7))
	{
		hero_->SetIsWin();
		lucifer_->SetIsWin();
		SetCurDialogue(_index);
	}
}
