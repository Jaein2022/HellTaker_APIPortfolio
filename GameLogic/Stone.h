#pragma once
#include "HellActor.h"

class J_SoundPlayer;
class J_Renderer;
class Stone: public HellActor
{
	J_Renderer* stone_Renderer_;
	float shakingTime_;
	J_Renderer* spark_Renderer_;		//ū ���� ����Ʈ
	J_Renderer* smallSpark_Renderer_;	//���� ���� ����Ʈ

	J_SoundPlayer* stoneKickSound_Player_;
	J_SoundPlayer* stoneMoveSound_Player_;

public:
	Stone();		//����Ʈ ������.
	~Stone();		//����Ʈ �Ҹ���.

public:
	Stone(const Stone& _other) = delete;		//����Ʈ ���������.
	Stone(Stone&& _other) = delete;		//����Ʈ rvalue ���������.

	Stone& operator=(const Stone& _other) = delete;		//����Ʈ ���Կ�����.
	Stone& operator=(const Stone&& _other) = delete;		//����Ʈ rvalue ���Կ�����.

public:
	void Start() override;
	void Update() override;
	void Render() override;
	void BeginMoving() override;
	void ChangeState() override;





};

