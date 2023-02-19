#include "Openning.h"
#include <J_LevelManager.h>
#include "OpenningBG.h"

Openning::Openning(): openningBG_(nullptr)
{
}

Openning::~Openning()
{
}

void Openning::LoadLevel()
{
	openningBG_ = CreateActor<OpenningBG>("OpenningBG");

}

void Openning::UpdateLevel()
{
	if (true == openningBG_->GetIsOpenningFinished())
	{
		J_LevelManager::GetInstance().ChangeCurLevel("Chapter0");
	}
}
