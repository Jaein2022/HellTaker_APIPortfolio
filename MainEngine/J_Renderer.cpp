#include <J_GameEngineTime.h>
#include "J_ImageManager.h"
#include "J_Renderer.h"
#include "J_ImageFile.h"
#include "J_Actor.h"

J_Renderer::Animation::Animation()
	: startIndex_(-1),
	finishIndex_(-1),
	curIndex_(-1),
	curDelay_(0.0f),
	parentRenderer_(nullptr),
	animationImage_(nullptr),
	pivot_(RENDERPIVOT::BOT),
	isLoopAnim_(false),
	isFinished_(false),
	delayEachFrame_()
{
}

void J_Renderer::Animation::Update()
{
	isFinished_ = false;

	curDelay_ -= J_GameEngineTime::GetInstance().GetDeltaTimeF();
	if (0.0f >= curDelay_)
	{
		//curDelay_ = delayPerFrame_;
		++curIndex_;
		if (finishIndex_ < curIndex_)
		{
			isFinished_ = true;
			if (true == isLoopAnim_)
			{
				curIndex_ = startIndex_;
			}
			else
			{
				--curIndex_;
			}
		}
		curDelay_ = delayEachFrame_[curIndex_ - startIndex_];
	}
	parentRenderer_->SetFrameIndex(static_cast<int>(curIndex_), pivot_);
	parentRenderer_->Render();
}

J_Renderer::J_Renderer()
	: parentActor_(nullptr),
	renderSize_(float4::ZERO),
	pivotPos_(float4::ZERO),
	actorImage_(nullptr),
	actorImagePos_(float4::ZERO), 
	actorImageSize_(float4::ZERO),
	actorImagePivot_(float4::ZERO),
	curAnimation_(nullptr),
	allAnimations_(),
	isCameraEffect_(false)
{
}

J_Renderer::~J_Renderer()
{
	for (std::map<std::string, Animation*>::iterator it = allAnimations_.begin();
		it != allAnimations_.end(); it++)
	{
		if (nullptr == it->second)
		{
			J_GameEngineDebug::AssertFalse();
			continue;
		}
		delete it->second;
		it->second = nullptr;
	}
	allAnimations_.clear();
}

void J_Renderer::Render()
{
	J_ImageFile* backBufferImage = J_ImageManager::GetInstance().GetBackBufferImage();

	if (nullptr == backBufferImage)
	{
		J_GameEngineDebug::AssertFalse("J_Renderer::Render()-> nullptr == backBufferImage");
		return;
	}

	if (nullptr == actorImage_)
	{
		J_GameEngineDebug::AssertFalse("J_Renderer::Render()-> nullptr == actorImage_");
		return;
	}

	if (0 >= renderSize_.x_ || 0 >= renderSize_.y_)
	{
		J_GameEngineDebug::AssertFalse("J_Renderer::Render()-> 0 >= renderSize_");
		return;
	}

	if (0 >= actorImageSize_.x_ || 0 >= actorImageSize_.y_)
	{
		J_GameEngineDebug::AssertFalse("J_Renderer::Render()-> 0 >= actorImageSize_");
		return;
	}

	float4 renderPos = float4::ZERO;	//렌더할 이미지의 왼쪽 상단이 윈도우 원점(0, 0) 기준 얼마나 떨어져있는지 보여주는 좌표.

	if (true == isCameraEffect_)
	{
		renderPos = parentActor_->GetCameraPos() + pivotPos_ - actorImagePivot_;
	}
	else
	{
		renderPos = parentActor_->GetActorPos() + pivotPos_ - actorImagePivot_;
	}

	backBufferImage->PasteOnBackBuffer(
		actorImage_,
		renderPos,
		renderSize_,
		actorImagePos_,
		actorImageSize_
	);
}

void J_Renderer::SetActorImagePivot(RENDERPIVOT _pivot)
{
	switch (_pivot)
	{
	case RENDERPIVOT::CENTER:
		actorImagePivot_ = actorImage_->GetImageSize().DivideHalf();
		break;
	case RENDERPIVOT::BOT:
		actorImagePivot_ = actorImage_->GetImageSize().DivideHalf();
		actorImagePivot_.y_ = actorImage_->GetImageSize().y_;
		break;
	case RENDERPIVOT::LEFTTOP:
		actorImagePivot_ = float4::ZERO;
		break;

	default:
		J_GameEngineDebug::AssertFalse();
		break;
	}
}

void J_Renderer::SetFrameIndex(int _index, RENDERPIVOT _pivot)
{
	if (true == actorImage_->IsCuttingSizesEmpty())	//이미지가 아직 안잘림.
	{
		J_GameEngineDebug::AssertFalse();
		return;
	}

	actorImagePos_ = actorImage_->GetCuttingPos(_index);
	actorImageSize_ = actorImage_->GetCuttingSizes(_index);
	renderSize_ = actorImageSize_;

	switch (_pivot)
	{
	case RENDERPIVOT::CENTER:
		actorImagePivot_ = renderSize_.DivideHalf();
		break;
	case RENDERPIVOT::BOT:
		actorImagePivot_ = renderSize_.DivideHalf();
		actorImagePivot_.y_ += renderSize_.DivideHalf().y_;
		break;
	case RENDERPIVOT::LEFTTOP:
		actorImagePivot_ = float4::ZERO;
		break;

	default:
		J_GameEngineDebug::AssertFalse();
		return;
	}
}

void J_Renderer::CreateAnimation(
	const std::string& _animationName,
	const std::string& _imageName,
	int _startIndex, 
	int _finishIndex,
	bool _isLoopAnim /*= false*/,
	float _delayPerFrame /*= 0.065f*/,
	RENDERPIVOT _pivot /*= RENDERPIVOT::BOT*/
)
{
	if (nullptr != FindAnimation(_animationName))	//같은 이름의 애니메이션 중복생성 금지.
	{
		J_GameEngineDebug::AssertFalse();
		return;
	}

	J_ImageFile* tempAnimationImage = J_ImageManager::GetInstance().FindImage(_imageName);

	if (nullptr == tempAnimationImage)
	{
		J_GameEngineDebug::AssertFalse();
		return;
	}

	if (true == tempAnimationImage->IsCuttingSizesEmpty())
	{
		J_GameEngineDebug::AssertFalse();
		return;
	}

	Animation* NewAnimation = new Animation();
	NewAnimation->SetName(_animationName);
	NewAnimation->startIndex_ = _startIndex;
	NewAnimation->curIndex_ = _startIndex;
	NewAnimation->finishIndex_ = _finishIndex;
	NewAnimation->curDelay_ = _delayPerFrame;

	NewAnimation->delayEachFrame_.reserve(NewAnimation->finishIndex_ - NewAnimation->startIndex_);
	for (int i = 0; i <= (NewAnimation->finishIndex_ - NewAnimation->startIndex_); i++)
	{
		NewAnimation->delayEachFrame_.push_back(_delayPerFrame);
	}
	//NewAnimation->delayPerFrame_ = _delayPerFrame;

	NewAnimation->parentRenderer_ = this;
	NewAnimation->animationImage_ = tempAnimationImage;
	NewAnimation->pivot_ = _pivot;
	NewAnimation->isLoopAnim_ = _isLoopAnim;

	allAnimations_.insert(std::map<std::string, Animation*>::value_type(_animationName, NewAnimation));
}

void J_Renderer::ChangeAnimation(const std::string& _animationName, bool _isForceChange /*= false*/)
{
	if (nullptr != curAnimation_ && curAnimation_->GetName() == _animationName && false == _isForceChange)
	{
		return;
	}

	curAnimation_ = FindAnimation(_animationName);
	if (nullptr == curAnimation_)
	{
		J_GameEngineDebug::AssertFalse("An animation of this name doesn't exist.");
		return;
	}

	curAnimation_->Reset();
}

void J_Renderer::UpdateAnimation()
{
	if (nullptr == curAnimation_)
	{
		J_GameEngineDebug::AssertFalse();
		return;
	}
	curAnimation_->Update();
}

bool J_Renderer::IsCurAnimationFinish()
{
	if (nullptr == curAnimation_)
	{
		J_GameEngineDebug::AssertFalse();
		return false;
	}
	return curAnimation_->isFinished_;
}

bool J_Renderer::IsCurAnimationName(const std::string& _animationName)
{
	if (nullptr == curAnimation_)
	{
		J_GameEngineDebug::AssertFalse();
		return false;
	}

	return _animationName == curAnimation_->GetName();
}

void J_Renderer::SetFrameDelay(const std::string& _animationName, int _index, float _delay)
{
	Animation* tempAnimation = FindAnimation(_animationName);
	if (nullptr == tempAnimation)
	{
		J_GameEngineDebug::AssertFalse("An animation of this name doesn't exist.");
		return;
	}
	if ( 0 > _index - tempAnimation->startIndex_)
	{
		J_GameEngineDebug::AssertFalse("_index cannot be smaller than startIndex.");
		return;
	}
	tempAnimation->delayEachFrame_[_index - tempAnimation->startIndex_] = _delay;
}

int J_Renderer::GetCurFrame()
{
	if (nullptr == curAnimation_)
	{
		J_GameEngineDebug::AssertFalse("curAnimation is nullptr.");
		return 0;
	}
	return static_cast<int>(curAnimation_->curIndex_);
}

void J_Renderer::SetActorImage(const std::string& _imageName)
{
	actorImage_ = J_ImageManager::GetInstance().FindImage(_imageName);
	if (nullptr == actorImage_)
	{
		J_GameEngineDebug::AssertFalse("J_Renderer::SetActorImage()-> nullptr == actorImage_");
		return;
	}

	renderSize_ = actorImage_->GetImageSize();
	actorImageSize_ = actorImage_->GetImageSize();
}


