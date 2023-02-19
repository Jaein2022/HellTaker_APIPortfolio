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
	J_Renderer* tile_Renderer_;				//Ÿ�� �⺻ ������.
	const float4 tileSize_;					//�Ѱ� Ÿ�� ũ��. �� �� �ʿ� ����.  
	TileState tileState_;					//�� Ÿ���� �Ӽ�. 
	HellActor* ActorOnTile_;				//�� Ÿ�� ���� ����.

	J_Renderer* thorn_Renderer_;
	
	
	

	J_Renderer* dust_Renderer_;			//�̵��� ���� ����Ʈ.
	


	bool isVisible_;					//true == Ÿ�� ������/ false == Ÿ�� ���� ����.





public:
	Tile();			//����Ʈ ������.
	~Tile();		//����Ʈ �Ҹ���.

public:
	Tile(const Tile& _other) = delete;		//����Ʈ ���������.
	Tile(Tile&& _other) = delete;			//����Ʈ rvalue ���������.

	Tile& operator=(const Tile& _other) = delete;		//����Ʈ ���Կ�����.
	Tile& operator=(const Tile&& _other) = delete;		//����Ʈ rvalue ���Կ�����.

public:

	void Start() override;
	void InitTileState(TileState _tileState);	//é�͵鸸 ����� ��.

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

