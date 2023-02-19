#pragma once
#include "HellActor.h"

class J_SoundPlayer;
class J_Renderer;
class Stone: public HellActor
{
	J_Renderer* stone_Renderer_;
	float shakingTime_;
	J_Renderer* spark_Renderer_;		//큰 섬광 이펙트
	J_Renderer* smallSpark_Renderer_;	//작은 섬광 이펙트

	J_SoundPlayer* stoneKickSound_Player_;
	J_SoundPlayer* stoneMoveSound_Player_;

public:
	Stone();		//디폴트 생성자.
	~Stone();		//디폴트 소멸자.

public:
	Stone(const Stone& _other) = delete;		//디폴트 복사생성자.
	Stone(Stone&& _other) = delete;		//디폴트 rvalue 복사생성자.

	Stone& operator=(const Stone& _other) = delete;		//디폴트 대입연산자.
	Stone& operator=(const Stone&& _other) = delete;		//디폴트 rvalue 대입연산자.

public:
	void Start() override;
	void Update() override;
	void Render() override;
	void BeginMoving() override;
	void ChangeState() override;





};

