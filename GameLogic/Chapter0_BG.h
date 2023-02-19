#pragma once
#include "HellActor.h"
#include <Windows.h>

class Chapter0;
class Button;
class Chapter;
class J_SoundPlayer;
class J_Renderer;
class Chapter0_BG: public HellActor
{
	//J_Renderer* openning_Renderer_;
	//float4 openningRenderSize_;
	//double openningFinishTime_;		//오프닝이 끝날때까지 남은 시간.
	//float enlargementRatio_;		//오프닝 이미지 확대 비율. 1.0f가 기본값.
	//bool isOpenningFinished_;		//오프닝이 끝났는지 여부.

	friend Chapter0;
	std::vector<Button*> allButtons_Chapter0_;
	int buttonIndex_;

	J_Renderer* justBlackBoard_;		//가장 뒤 검은 배경. 
	J_Renderer* Chapter0_BG01_;			//움직이는 배경 01번.
	J_Renderer* Chapter0_BG02_;			//움직이는 배경 02번.
	J_Renderer* Chapter0_BG03_;			//움직이는 배경 03번.
	J_Renderer* Chapter0_BG04_;			//움직이는 배경 04번.
	J_Renderer* beelFly_Renderer_;
	//J_Renderer* booper_Renderer_;

	const float distanceFromAbyss01_;	//abyss02번 이미지를 가진 렌더러가 abyss01번 이미지를 가진 렌더러에서 뒤로 떨어져 있어야 하는 거리. 
	const float distanceFromAbyss02_;	//abyss01번 이미지를 가진 렌더러가 abyss02번 이미지를 가진 렌더러에서 뒤로 떨어져 있어야 하는 거리.
	float BG01PivotPosX_;				//BG01 번의 x좌표.
	float BG02PivotPosX_;				//BG02 번의 x좌표.
	float BG03PivotPosX_;				//BG03 번의 x좌표.
	float BG04PivotPosX_;				//BG04 번의 x좌표.
	const float BGsPivotPosY_;			//BG01, 02, 03, 04의 공통 y좌표값. 

	J_SoundPlayer* Chapter0_BGSound_Player_;

	HDC backBufferHDC_;

	HFONT introductionFont_;
	std::string introduction_;

	HFONT lineFont_;
	std::string line0_;
	std::string line1_;

public:
	Chapter0_BG();		//디폴트 생성자.
	~Chapter0_BG();		//디폴트 소멸자.

public:
	Chapter0_BG(const Chapter0_BG& _other) = delete;		//디폴트 복사생성자.
	Chapter0_BG(Chapter0_BG&& _other) = delete;		//디폴트 rvalue 복사생성자.

	Chapter0_BG& operator=(const Chapter0_BG& _other) = delete;		//디폴트 대입연산자.
	Chapter0_BG& operator=(const Chapter0_BG&& _other) = delete;		//디폴트 rvalue 대입연산자.

public:
	void Start() override;

private:
	void Update() override;
	void Render() override;

public:


private: 
	void CreateButtons(int _firstButtonPosX, int firstButtonPosY, int _count);

private:
	//void SetParentChapter_Chapter0(Chapter* _parentChapter)
	//{
	//	parentChapter_ = _parentChapter;
	//}
};

