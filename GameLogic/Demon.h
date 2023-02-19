#pragma once
#include "HellActor.h"

class J_SoundPlayer;
class J_Renderer;
class Demon: public HellActor
{
	J_Renderer* demon_Renderer_;
	J_Renderer* loveSign_Renderer_;
	J_SoundPlayer* demonDeadSound_Player_;
	bool isWin_;

public:
	Demon();		//����Ʈ ������.
	~Demon();		//����Ʈ �Ҹ���.

public:
	Demon(const Demon& _other) = delete;		//����Ʈ ���������.
	Demon(Demon&& _other) = delete;		//����Ʈ rvalue ���������.

	Demon& operator=(const Demon& _other) = delete;		//����Ʈ ���Կ�����.
	Demon& operator=(const Demon&& _other) = delete;		//����Ʈ rvalue ���Կ�����.

public:
	void Start() override;
	void SetIsWin();
	void SetCamEffectOn() override;
	void SetCamEffectOff() override;

private:
	void Update() override;
	void Render() override;
	void Die() override;

};

