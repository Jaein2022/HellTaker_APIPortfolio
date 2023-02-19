#pragma once
#include "HellActor.h"
#include <Windows.h>

class J_SoundPlayer;
class J_ImageFile;
class J_Renderer;
class Hero: public HellActor
{
	friend Chapter;
	
	int moveLimit_;						//���� �̵� Ƚ��. 
	const float4 fontSize_;				//��Ʈ ũ��.
	HFONT moveLimitFont_;				//��Ʈ �ڵ�.
	HDC backBufferHDC_;					//������� HDC.

	J_Renderer* hero_Renderer_;			//����� ���� ����Ʈ ������ ������� ��� �ִϸ��̼��� ����ϴ� ������.
	J_Renderer* blood_Renderer_;		//���� ����Ʈ.

	//���� ����. ����Ÿ�� ������ �����̸� true�� �ǰ� ���� �ִϸ��̼��� ����ȴ�.
	bool isBleeding_;

	J_SoundPlayer* thornDamageSound_Player_;	//����Ÿ�� ������ ���� �Ҹ�.
	J_SoundPlayer* heroMoveSound_Player_;		//����� �����̴� �Ҹ�.


	bool isGotKey_;	//����ΰ� ���� ���� ����. ���� ���� ���¿����� �ڹ��踦 �� �� �ִ�.

	bool isWin_;

	//heroDeath_Animation ���� ����.
	J_ImageFile* justBlackBoard_;					//������ ���. rgb(2, 2, 27).
	std::vector<J_ImageFile*> heroDeath_Animation_;	//����� ��� �ִϸ��̼�(720 x 1232).
	const float heroDeathDelay_;				//����� ��� �ִϸ��̼� ������ �� ������.
	float curFrameDelay_;						//���� ������ ������.	
	int curFrameIndex_;							//���� ������ ��ȣ. 0 <= curFrameDelay <= 17.
	bool isHeroDeathFinish_;
	const float4 heroDeath_ImagePivot_;			//heroDeath �ִϸ��̼��� ������(360, 975). �� ��ġ�� ������� ��ġ�� �����ϰ� �����.
	bool isHeroDeathCameffectOn_;
	J_SoundPlayer* heroDeath_Player_;



public:
	Hero();		//����Ʈ ������.
	~Hero();		//����Ʈ �Ҹ���.

public:
	Hero(const Hero& _other) = delete;		//����Ʈ ���������.
	Hero(Hero&& _other) = delete;		//����Ʈ rvalue ���������.

	Hero& operator=(const Hero& _other) = delete;		//����Ʈ ���Կ�����.
	Hero& operator=(const Hero&& _other) = delete;		//����Ʈ rvalue ���Կ�����.

public:

	void Start() override;


public:
	void SetIsWin()
	{
		isWin_ = true;
	}

private:
	void Update() override;
	void Render() override;

	void SetCamEffectOn() override;
	void SetCamEffectOff() override;
	void ChangeState() override;
	void ChangeAnimation(const std::string& _animationName, bool _isForceChange = false);
	bool IsActorAnimationFinish();
	void BeginMoving() override;
	void FinishMoving() override;
	void Die() override;

	void Push();
	void Win();
	void Update_HeroDeath();	//heroDeath �ִϸ��̼� ������Ʈ. 
	void Render_HeroDeath();	

private:
	void SetMoveLimit(unsigned int _moveLimit)
	{
		moveLimit_ = static_cast<int>(_moveLimit);
	}
};

