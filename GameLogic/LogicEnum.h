#pragma once
enum class TileState
{
	WALL,				//��. 
	NONE,				//Ÿ�� ���� �ƹ��͵� ����.
	THORN_UP,			//���� �ö��.
	THORN_DOWN,			//���� ������.
	THORN_FIXED,		//���� ���� Ÿ��. ������� Ÿ�� �⺻ ����.
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