#pragma once
#include "HellActor.h"

class J_SoundPlayer;
class J_Renderer;
class Skeleton: public HellActor
{
	J_Renderer* skeleton_Renderer_;

	J_SoundPlayer* skeletonMoveSound_Player_;
	J_SoundPlayer* skeletonDeadSound_Player_;

public:
	Skeleton();		//디폴트 생성자.
	~Skeleton();		//디폴트 소멸자.

public:
	Skeleton(const Skeleton& _other) = delete;		//디폴트 복사생성자.
	Skeleton(Skeleton&& _other) = delete;		//디폴트 rvalue 복사생성자.

	Skeleton& operator=(const Skeleton& _other) = delete;		//디폴트 대입연산자.
	Skeleton& operator=(const Skeleton&& _other) = delete;		//디폴트 rvalue 대입연산자.

public:
	void Start() override;
	void SetCamEffectOn() override;
	void SetCamEffectOff() override;

private:
	void Update() override;
	void Render() override;


	void ChangeState() override;
	void ChangeAnimation(const std::string& _animationName, bool _isForceChange = true);
	bool IsActorAnimationFinish();
	void BeginMoving() override;
	void FinishMoving() override;
	void Die() override;



};

