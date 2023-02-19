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
	Demon();		//디폴트 생성자.
	~Demon();		//디폴트 소멸자.

public:
	Demon(const Demon& _other) = delete;		//디폴트 복사생성자.
	Demon(Demon&& _other) = delete;		//디폴트 rvalue 복사생성자.

	Demon& operator=(const Demon& _other) = delete;		//디폴트 대입연산자.
	Demon& operator=(const Demon&& _other) = delete;		//디폴트 rvalue 대입연산자.

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

