#include "Chapter6.h"
#include "Demon.h"
#include "Skeleton.h"
#include "Stone.h"
#include "Tile.h"
#include "Dialogue.h"
#include "Button.h"
#include "Hero.h"

Chapter6::Chapter6(): azazel_(nullptr)
{
}

Chapter6::~Chapter6()
{
}

void Chapter6::LoadLevel()
{
	ClearChapter();
	SetChapterNumber();
	CreateTransition();
	CreateDefaultBG();

	CreateTiles({ 555, 100 }, 9, 10);
	FindTile(1, 1)->InitTileState(TileState::WALL);
	FindTile(1, 2)->InitTileState(TileState::WALL);
	FindTile(1, 4)->InitTileState(TileState::WALL);
	FindTile(1, 5)->InitTileState(TileState::WALL);
	FindTile(1, 6)->InitTileState(TileState::WALL);
	FindTile(1, 7)->InitTileState(TileState::WALL);
	FindTile(1, 8)->InitTileState(TileState::WALL);
	FindTile(2, 7)->InitTileState(TileState::WALL);
	FindTile(2, 8)->InitTileState(TileState::WALL);
	FindTile(3, 7)->InitTileState(TileState::WALL);
	FindTile(3, 8)->InitTileState(TileState::WALL);
	FindTile(4, 7)->InitTileState(TileState::WALL);
	FindTile(4, 8)->InitTileState(TileState::WALL);
	FindTile(7, 8)->InitTileState(TileState::WALL);
	FindTile(7, 6)->InitTileState(TileState::WALL);
	FindTile(3, 5)->InitTileState(TileState::WALL);
	FindTile(5, 1)->InitTileState(TileState::WALL);
	FindTile(5, 2)->InitTileState(TileState::WALL);
	FindTile(5, 3)->InitTileState(TileState::WALL);
	FindTile(6, 1)->InitTileState(TileState::WALL);
	FindTile(6, 2)->InitTileState(TileState::WALL);
	FindTile(6, 3)->InitTileState(TileState::WALL);
	FindTile(7, 1)->InitTileState(TileState::WALL);
	FindTile(7, 2)->InitTileState(TileState::WALL);
	FindTile(7, 3)->InitTileState(TileState::WALL);
	FindTile(6, 4)->InitTileState(TileState::WALL);
	FindTile(7, 4)->InitTileState(TileState::WALL);

	FindTile(2, 4)->InitTileState(TileState::THORN_DOWN);
	FindTile(3, 4)->InitTileState(TileState::THORN_DOWN);

	CreateHero(43, 3, 1);
	azazel_ = CreateDemon("azazel", 6, 8);
	SetGoalTileIndex({ 5, 8 }, { 6, 7 });
	CreateKey(4, 3);
	CreateLock(5, 7);

	CreateSkeleton(2, 5);
	CreateSkeleton(6, 6);

	CreateStone(6, 7);
	CreateStone(2, 2);
	CreateStone(3, 2);
	CreateStone(4, 2);
	CreateStone(3, 4);
	CreateStone(4, 5);
	CreateStone(5, 5);
	CreateStone(4, 6);

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

	CreateDialogue("az_idle.bmp");
	FindDialogue(0)->SetIntroduction("， Azazel, the Curious Angel ，");
	FindDialogue(0)->SetLine0("Oh my heavens! What would a living human be doing in hell?");
	FindDialogue(0)->SetLine1("Most unusual.");
	FindDialogue(0)->FindButton(0)->SetButtonText("Looking for demons.");
	FindDialogue(0)->FindButton(1)->SetButtonText("Looking for angels.");
	SetCurDialogue(0);
	
	CreateDialogue("az_note.bmp", "", "", 0, 1);
	FindDialogue(1)->SetIntroduction("， Azazel, the Curious Angel ，");
	FindDialogue(1)->SetLine0("Oh, you too? Let me guess, thesis on Modern sin? Or is it");
	FindDialogue(1)->SetLine1("Demonology? We should join forces.");
	
	CreateDialogue("az_idle.bmp", "", "", 0, 0);
	FindDialogue(2)->SetIntroduction("， Azazel, the Curious Angel ，");
	FindDialogue(2)->SetLine0("You won't find many here. Lucky for you, I know the better place.");
	FindDialogue(2)->SetLine1("Please, hold my hand.");

	CreateDialogue("JustBlackBoard.bmp", "", "", 0, 0);
	FindDialogue(3)->SetIntroduction("");
	FindDialogue(3)->SetLine0("Who would've guessed that lying will get you into heaven.");
	FindDialogue(3)->SetLine1("");

	CreateDialogue("chapter6_Badend.bmp", "", "", 0, 0);
	FindDialogue(4)->SetIntroduction("");
	FindDialogue(4)->SetLine0("Say goodbye to your demon harem, though.");
	FindDialogue(4)->SetLine1("");
}

void Chapter6::UpdateLevel()
{
	ManageInput();
}

void Chapter6::RespondSelection(int _index)
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
		azazel_->SetIsWin();
		SetCurDialogue(_index);
	}
	else if (curDialogue_ == FindDialogue(2))
	{
		SetCurDialogue(3);
	}
	else if (curDialogue_ == FindDialogue(3))
	{
		SetCurDialogue(4);
	}
	else if (curDialogue_ == FindDialogue(4))
	{
		ResetLevel();
	}
}
