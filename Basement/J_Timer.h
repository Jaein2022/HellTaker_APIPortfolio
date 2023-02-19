#pragma once
#include <Windows.h>
#include <assert.h>

class J_Timer
{
	static J_Timer* instance_;

	LARGE_INTEGER frequency_;		//초당 CPU 주파수(초당 클럭 반복 회수). 고정값이므로 처음 한번만 잰다.
	LARGE_INTEGER beginningCheck_;	//루프 시작시점의 누적 클럭 수.
	LARGE_INTEGER finishingCheck_;	//루프 종료지점의 누적 클럭 수.
	double deltaTime_;				//지난 루프를 한번 수행 할 때 걸린 시간 = 루프 한번당 누적되는 클럭 수 / 초당 CPU 클럭 반복 회수.
	//컴퓨터의 성능이 좋을수록 델타타임의 수치가 낮아지고, 컴퓨터 성능 격차로 인해 각자 다른 속도로 루프를 수행한다고 해도 
	//성능에 반비례해서 델타타임 값이 작게 잡히기 때문에, 컴퓨터 성능 상관없이 같은 시간 같은 게임 진행속도를 보여주게 된다.	


	J_Timer();		//디폴트 생성자.
	~J_Timer();		//디폴트 소멸자.

public:
	J_Timer(const J_Timer& _other) = delete;		//디폴트 복사생성자.
	J_Timer(J_Timer&& _other) = delete;		//디폴트 rvalue 복사생성자.

	J_Timer& operator=(const J_Timer& _other) = delete;		//디폴트 대입연산자.
	J_Timer& operator=(const J_Timer&& _other) = delete;		//디폴트 rvalue 대입연산자.

public:
	void ResetTimer();			//시간 측정 준비 함수.
	void MeasureDeltaTime();	//시간 측정 함수.

	static J_Timer& GetInstance()
	{
		return *instance_;
	}

	static void DestroyInstance()
	{
		if (nullptr == instance_)
		{
			assert(false && "nullptr == instance_");
			return;
		}
		delete instance_;
		instance_ = nullptr;
	}

	double GetDeltaTime_Double() const
	{
		return deltaTime_;
	}

	float GetDeltaTime_Float() const
	{
		return static_cast<float>(deltaTime_);
	}
};

