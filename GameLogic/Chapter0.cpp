#include "Chapter0.h"
#include "Chapter0_BG.h"
#include <J_GameEnginePath.h>
#include <J_Input.h>
#include <J_ImageFile.h>
#include <J_Window.h>


Chapter0::Chapter0(): Chapter0_BG_(nullptr)
{

}

Chapter0::~Chapter0()
{
}

void Chapter0::LoadLevel()
{
	Chapter0_BG_ = CreateActor<Chapter0_BG>("Chapter0_BG");	
	Chapter0_BG_->SetParentChapter(this);
	SetChapterNumber();
}

void Chapter0::UpdateLevel()
{
	ManageInput();
}

void Chapter0::RespondSelection(int _index)
{
	if (0 == _index)
	{
		ChangeToNextChapter();
	}
	else if (1 == _index)
	{
		J_Window::GetInstance().TurnOff();
	}
}
