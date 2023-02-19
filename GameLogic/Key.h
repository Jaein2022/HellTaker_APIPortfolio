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
	Key();		//디폴트 생성자.
	~Key();		//디폴트 소멸자.

public:
	Key(const Key& _other) = delete;		//디폴트 복사생성자.
	Key(Key&& _other) = delete;		//디폴트 rvalue 복사생성자.

	Key& operator=(const Key& _other) = delete;		//디폴트 대입연산자.
	Key& operator=(const Key&& _other) = delete;		//디폴트 rvalue 대입연산자.

public:
	void Start() override;

private:
	void Update() override;
	void Render() override;
	void Die() override;


};

