#pragma once
#include <J_Actor.h>
#include "LogicEnum.h"


class HellActor;
class Chapter;
class J_Renderer;
class Tile: public J_Actor
{
	friend Chapter;

	Chapter* parentChapter_;
	J_Renderer* tile_Renderer_;				//타일 기본 렌더러.
	const float4 tileSize_;					//한개 타일 크기. 손 댈 필요 없음.  
	TileState tileState_;					//이 타일의 속성. 
	HellActor* ActorOnTile_;				//이 타일 위의 액터.

	J_Renderer* thorn_Renderer_;
	
	
	

	J_Renderer* dust_Renderer_;			//이동시 먼지 이펙트.
	


	bool isVisible_;					//true == 타일 렌더함/ false == 타일 렌더 안함.





public:
	Tile();			//디폴트 생성자.
	~Tile();		//디폴트 소멸자.

public:
	Tile(const Tile& _other) = delete;		//디폴트 복사생성자.
	Tile(Tile&& _other) = delete;			//디폴트 rvalue 복사생성자.

	Tile& operator=(const Tile& _other) = delete;		//디폴트 대입연산자.
	Tile& operator=(const Tile&& _other) = delete;		//디폴트 rvalue 대입연산자.

public:

	void Start() override;
	void InitTileState(TileState _tileState);	//챕터들만 사용할 것.

private:
	void Update() override;
	void Render() override;


public:

	TileState GetTileState()
	{
		return tileState_;
	}

	bool GetIsVisible()
	{
		return isVisible_;
	}

	void SetIsVisible(bool _isVisible)
	{
		isVisible_ = _isVisible;
	}

	//Chapter* GetParentChapter()
	//{
	//	return parentChapter_;
	//}

	void SetHellActor(HellActor* _HellActor)
	{
		ActorOnTile_ = _HellActor;
	}

	HellActor* GetHellActor()
	{
		return ActorOnTile_;
	}

private:
	

private:
	void SetParentChapter(Chapter* _parentChapter)
	{
		parentChapter_ = _parentChapter;
	}
};

