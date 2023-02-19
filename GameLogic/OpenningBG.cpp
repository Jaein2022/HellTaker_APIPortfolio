#include "OpenningBG.h"
#include <J_LevelManager.h>
#include <J_Renderer.h>
#include <J_ImageFile.h>
#include <J_GameEngineTime.h>

OpenningBG::OpenningBG()
	: openning_Renderer_(nullptr),
	openningRenderSize_(float4::ZERO),
	openningFinishTime_(1.50),
	enlargementRatio_(1.0f),
	isOpenningFinished_(false)
{
}

OpenningBG::~OpenningBG()
{

}

void OpenningBG::Start()
{
	SetActorPos({ 960, 540 });
	openning_Renderer_ = CreateRenderer("Openning.bmp", "Openning");
	openning_Renderer_->SetActorImagePivot(RENDERPIVOT::CENTER);
	openningRenderSize_ = openning_Renderer_->GetActorImage()->GetImageSize();
}

void OpenningBG::Update()
{
	if (0.0 >= openningFinishTime_)
	{
		isOpenningFinished_ = true;
	}
	else
	{
		openning_Renderer_->SetRenderSize(openningRenderSize_);
		openning_Renderer_->SetActorImagePivot(openningRenderSize_.DivideHalf());
		openningFinishTime_ -= J_GameEngineTime::GetInstance().GetDeltaTimeD();
		enlargementRatio_ += J_GameEngineTime::GetInstance().GetDeltaTimeF() * 0.0005f;
		openningRenderSize_ *= (float4{ enlargementRatio_,  enlargementRatio_ });
	}
}

void OpenningBG::Render()
{
	openning_Renderer_->Render();
}
