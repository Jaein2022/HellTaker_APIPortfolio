#pragma once
#include "HellActor.h"


class J_Renderer;
class OpenningBG: public HellActor
{
	J_Renderer* openning_Renderer_;
	float4 openningRenderSize_;
	double openningFinishTime_;		//오프닝이 끝날때까지 남은 시간.
	float enlargementRatio_;		//오프닝 이미지 확대 비율. 1.0f가 기본값.
	bool isOpenningFinished_;		//오프닝이 끝났는지 여부.

public:
	OpenningBG();		//디폴트 생성자.
	~OpenningBG();		//디폴트 소멸자.

public:
	OpenningBG(const OpenningBG& _other) = delete;		//디폴트 복사생성자.
	OpenningBG(OpenningBG&& _other) = delete;		//디폴트 rvalue 복사생성자.

	OpenningBG& operator=(const OpenningBG& _other) = delete;		//디폴트 대입연산자.
	OpenningBG& operator=(const OpenningBG&& _other) = delete;		//디폴트 rvalue 대입연산자.

public:
	void Start() override;
	
private:
	void Update() override;
	void Render() override;

public:

	bool GetIsOpenningFinished()
	{
		return isOpenningFinished_;
	}


};

