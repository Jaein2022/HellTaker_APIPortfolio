#include "J_Actor.h"
#include "J_Renderer.h"
#include "J_Level.h"

J_Actor::J_Actor()
	: parentLevel_(nullptr),
	actorPos_(float4::ZERO),
	updateOrder_(0),
	renderOrder_(0), 
	allRenderers_(), 
	isDestroyed_(false)
{
}

J_Actor::~J_Actor()
{
	for (std::map<std::string, J_Renderer*>::iterator it = allRenderers_.begin(); it != allRenderers_.end(); ++it)
	{
		delete it->second;
		it->second = nullptr;
	}
	allRenderers_.clear();
}

float4 J_Actor::GetCameraPos()
{
	return this->GetActorPos() - parentLevel_->GetCameraPos();
}

J_Renderer* J_Actor::CreateRenderer(const std::string& _imageName, const std::string& _rendererName)
{
	std::map<std::string, J_Renderer*>::iterator it = allRenderers_.find(_rendererName);
	if (allRenderers_.end() != it)
	{
		J_GameEngineDebug::AssertFalse("The renderer already exists.");
		return nullptr;
	}

	J_Renderer* NewRenderer = new J_Renderer();
	if (nullptr == NewRenderer)
	{
		J_GameEngineDebug::AssertFalse("It is failed to construct a renderer.");
		return nullptr;
	}

	NewRenderer->SetName(_rendererName);
	NewRenderer->SetParentActor(this);
	NewRenderer->SetActorImage(_imageName);

	allRenderers_.insert(std::map<std::string, J_Renderer*>::value_type(_rendererName, NewRenderer));

	return NewRenderer;
}

void J_Actor::Start()
{
}

void J_Actor::Update()
{
}

void J_Actor::Render()
{
}
