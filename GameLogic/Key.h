#pragma once
#include "HellActor.h"

class J_SoundPlayer;
class J_Renderer;
class Key: public HellActor
{
	J_Renderer* key_Renderer_;
	J_Renderer* radiant_Renderer_;
	J_SoundPlayer* keyPickingSound_Player_;

public:
	Key();		//����Ʈ ������.
	~Key();		//����Ʈ �Ҹ���.

public:
	Key(const Key& _other) = delete;		//����Ʈ ���������.
	Key(Key&& _other) = delete;		//����Ʈ rvalue ���������.

	Key& operator=(const Key& _other) = delete;		//����Ʈ ���Կ�����.
	Key& operator=(const Key&& _other) = delete;		//����Ʈ rvalue ���Կ�����.

public:
	void Start() override;

private:
	void Update() override;
	void Render() override;
	void Die() override;


};

