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
	Lock();		//����Ʈ ������.
	~Lock();		//����Ʈ �Ҹ���.

public:
	Lock(const Lock& _other) = delete;		//����Ʈ ���������.
	Lock(Lock&& _other) = delete;		//����Ʈ rvalue ���������.

	Lock& operator=(const Lock& _other) = delete;		//����Ʈ ���Կ�����.
	Lock& operator=(const Lock&& _other) = delete;		//����Ʈ rvalue ���Կ�����.

public:
	void Start() override;

private:
	void Update() override;
	void Render() override;
	void ChangeState() override;
	void Die() override;
};

