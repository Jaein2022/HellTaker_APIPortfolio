#pragma once
#include "HellActor.h"
#include <Windows.h>

class J_SoundPlayer;
class J_ImageFile;
class J_Renderer;
class Hero: public HellActor
{
	friend Chapter;
	
	int moveLimit_;						//남은 이동 횟수. 
	const float4 fontSize_;				//폰트 크기.
	HFONT moveLimitFont_;				//폰트 핸들.
	HDC backBufferHDC_;					//백버퍼의 HDC.

	J_Renderer* hero_Renderer_;			//사망과 각종 이펙트 제외한 히어로의 모든 애니메이션을 담담하는 렌더러.
	J_Renderer* blood_Renderer_;		//출혈 이펙트.

	//출혈 여부. 가시타일 위에서 움직이면 true가 되고 출혈 애니메이션이 재생된다.
	bool isBleeding_;

	J_SoundPlayer* thornDamageSound_Player_;	//가시타일 밟을때 나는 소리.
	J_SoundPlayer* heroMoveSound_Player_;		//히어로 움직이는 소리.


	bool isGotKey_;	//히어로가 열쇠 가짐 여부. 열쇠 가짐 상태에서만 자물쇠를 열 수 있다.

	bool isWin_;

	//heroDeath_Animation 관련 변수.
	J_ImageFile* justBlackBoard_;					//검은색 배경. rgb(2, 2, 27).
	std::vector<J_ImageFile*> heroDeath_Animation_;	//히어로 사망 애니메이션(720 x 1232).
	const float heroDeathDelay_;				//히어로 사망 애니메이션 프레임 별 딜레이.
	float curFrameDelay_;						//현재 프레임 딜레이.	
	int curFrameIndex_;							//현재 프레임 번호. 0 <= curFrameDelay <= 17.
	bool isHeroDeathFinish_;
	const float4 heroDeath_ImagePivot_;			//heroDeath 애니메이션의 기준점(360, 975). 이 위치를 히어로의 위치와 동일하게 맞춘다.
	bool isHeroDeathCameffectOn_;
	J_SoundPlayer* heroDeath_Player_;



public:
	Hero();		//디폴트 생성자.
	~Hero();		//디폴트 소멸자.

public:
	Hero(const Hero& _other) = delete;		//디폴트 복사생성자.
	Hero(Hero&& _other) = delete;		//디폴트 rvalue 복사생성자.

	Hero& operator=(const Hero& _other) = delete;		//디폴트 대입연산자.
	Hero& operator=(const Hero&& _other) = delete;		//디폴트 rvalue 대입연산자.

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
	void Update_HeroDeath();	//heroDeath 애니메이션 업데이트. 
	void Render_HeroDeath();	

private:
	void SetMoveLimit(unsigned int _moveLimit)
	{
		moveLimit_ = static_cast<int>(_moveLimit);
	}
};

