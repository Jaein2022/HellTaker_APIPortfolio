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
	Skeleton();		//����Ʈ ������.
	~Skeleton();		//����Ʈ �Ҹ���.

public:
	Skeleton(const Skeleton& _other) = delete;		//����Ʈ ���������.
	Skeleton(Skeleton&& _other) = delete;		//����Ʈ rvalue ���������.

	Skeleton& operator=(const Skeleton& _other) = delete;		//����Ʈ ���Կ�����.
	Skeleton& operator=(const Skeleton&& _other) = delete;		//����Ʈ rvalue ���Կ�����.

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

