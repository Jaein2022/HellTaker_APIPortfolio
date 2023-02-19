#pragma once
enum class TileState
{
	WALL,				//벽. 
	NONE,				//타일 위에 아무것도 없음.
	THORN_UP,			//가시 올라옴.
	THORN_DOWN,			//가시 내려감.
	THORN_FIXED,		//고정 가시 타일. 여기까지 타일 기본 상태.
	MAX
};

enum class ActorType
{
	NONE,
	HERO,
	SKELETON,
	STONE,
	DEMON,
	KEY,
	LOCK,
	MAX
};