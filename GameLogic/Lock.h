#pragma once
#include "HellActor.h"

class J_SoundPlayer;
class J_Renderer;
class Lock: public HellActor
{
	J_Renderer* lock_Renderer_;
	J_Renderer* radiant_Renderer_;
	float shakingTime_;
	J_SoundPlayer* closedLockSound_Player_;
	J_SoundPlayer* lockOpenningSound_Player_;

public:
	Lock();		//디폴트 생성자.
	~Lock();		//디폴트 소멸자.

public:
	Lock(const Lock& _other) = delete;		//디폴트 복사생성자.
	Lock(Lock&& _other) = delete;		//디폴트 rvalue 복사생성자.

	Lock& operator=(const Lock& _other) = delete;		//디폴트 대입연산자.
	Lock& operator=(const Lock&& _other) = delete;		//디폴트 rvalue 대입연산자.

public:
	void Start() override;

private:
	void Update() override;
	void Render() override;
	void ChangeState() override;
	void Die() override;
};

