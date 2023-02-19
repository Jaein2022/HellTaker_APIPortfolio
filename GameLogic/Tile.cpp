#include "Tile.h"
#include <J_ImageFile.h>
#include <J_Renderer.h>
#include <J_ImageManager.h>

Tile::Tile()
	: parentChapter_(nullptr),
	tile_Renderer_(nullptr),
	tileSize_({ 100, 100 }),  
	tileState_(TileState::NONE),
	ActorOnTile_(nullptr), 
	thorn_Renderer_(nullptr),
	dust_Renderer_(nullptr),
	isVisible_(false)
{
}

Tile::~Tile()
{
}

void Tile::Start()
{
	tile_Renderer_ = CreateRenderer("100tile.bmp", "tile_Renderer");
	tile_Renderer_->SetActorImagePivot(RENDERPIVOT::CENTER);

	thorn_Renderer_ = CreateRenderer("thorn.bmp", "thorn_Renderer");
	thorn_Renderer_->SetActorImagePivot(RENDERPIVOT::BOT);
	if (true == thorn_Renderer_->GetActorImage()->IsCuttingSizesEmpty())
	{
		thorn_Renderer_->GetActorImage()->CutImage({ 100, 100 });
	}
	thorn_Renderer_->CreateAnimation("thornDownAnimation", "thorn.bmp", 0, 3, false, 0.05f);
	thorn_Renderer_->CreateAnimation("thornUpAnimation", "thorn.bmp", 4, 7, false, 0.05f);
	thorn_Renderer_->SetPivotPos({ 0, 30 });
	thorn_Renderer_->ChangeAnimation("thornDownAnimation");
	


	dust_Renderer_ = CreateRenderer("dust.bmp", "dust_Renderer");
	if (true == dust_Renderer_->GetActorImage()->IsCuttingSizesEmpty())
	{
		dust_Renderer_->GetActorImage()->CutImage({ 100, 100 });
	}
	dust_Renderer_->CreateAnimation("dustEffect0L", "dust.bmp", 0, 2, false, 0.01f, RENDERPIVOT::CENTER);
	dust_Renderer_->CreateAnimation("dustEffect0R", "dust.bmp", 3, 5, false, 0.01f, RENDERPIVOT::CENTER);
	dust_Renderer_->CreateAnimation("dustEffect1L", "dust.bmp", 6, 8, false, 0.01f, RENDERPIVOT::CENTER);
	dust_Renderer_->CreateAnimation("dustEffect1R", "dust.bmp", 9, 11, false, 0.01f, RENDERPIVOT::CENTER);
	dust_Renderer_->CreateAnimation("dustEffect2L", "dust.bmp", 12, 14, false, 0.01f, RENDERPIVOT::CENTER);
	dust_Renderer_->CreateAnimation("dustEffect2R", "dust.bmp", 15, 17, false, 0.01f, RENDERPIVOT::CENTER);
	dust_Renderer_->SetPivotPos(float4::ZERO);

	SetUpdateOrder(1);
	SetRenderOrder(2);

}

void Tile::Update()
{

}

void Tile::Render()
{
	switch (tileState_)
	{
	case TileState::THORN_UP:
		if (true == thorn_Renderer_->IsCurAnimationFinish() && true == thorn_Renderer_->IsCurAnimationName("thornUpAnimation"))
		{
			thorn_Renderer_->SetFrameIndex(0, RENDERPIVOT::BOT);
			thorn_Renderer_->Render();
		}
		else
		{
			thorn_Renderer_->ChangeAnimation("thornUpAnimation");
			thorn_Renderer_->UpdateAnimation();
		}
		break;
	case TileState::THORN_DOWN:
		if (true == thorn_Renderer_->IsCurAnimationFinish() && true == thorn_Renderer_->IsCurAnimationName("thornDownAnimation"))
		{
			thorn_Renderer_->SetFrameIndex(4, RENDERPIVOT::BOT);
			thorn_Renderer_->Render();
		}
		else
		{
			thorn_Renderer_->ChangeAnimation("thornDownAnimation");
			thorn_Renderer_->UpdateAnimation();
		}
		break;
	case TileState::THORN_FIXED:
		thorn_Renderer_->SetFrameIndex(0, RENDERPIVOT::BOT);
		thorn_Renderer_->Render();
		break;

	case TileState::WALL:
	case TileState::NONE:
		break;

	default:
		J_GameEngineDebug::AssertFalse();
		return;
	}

	if (false == isVisible_)
	{
		return;
	}
	else
	{
		tile_Renderer_->Render();
	}
}

void Tile::InitTileState(TileState _tileState)
{
	tileState_ = _tileState;
}

