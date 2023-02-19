#pragma once
#include <Windows.h>
#include <assert.h>

class J_Timer
{
	static J_Timer* instance_;

	LARGE_INTEGER frequency_;		//�ʴ� CPU ���ļ�(�ʴ� Ŭ�� �ݺ� ȸ��). �������̹Ƿ� ó�� �ѹ��� ���.
	LARGE_INTEGER beginningCheck_;	//���� ���۽����� ���� Ŭ�� ��.
	LARGE_INTEGER finishingCheck_;	//���� ���������� ���� Ŭ�� ��.
	double deltaTime_;				//���� ������ �ѹ� ���� �� �� �ɸ� �ð� = ���� �ѹ��� �����Ǵ� Ŭ�� �� / �ʴ� CPU Ŭ�� �ݺ� ȸ��.
	//��ǻ���� ������ �������� ��ŸŸ���� ��ġ�� ��������, ��ǻ�� ���� ������ ���� ���� �ٸ� �ӵ��� ������ �����Ѵٰ� �ص� 
	//���ɿ� �ݺ���ؼ� ��ŸŸ�� ���� �۰� ������ ������, ��ǻ�� ���� ������� ���� �ð� ���� ���� ����ӵ��� �����ְ� �ȴ�.	


	J_Timer();		//����Ʈ ������.
	~J_Timer();		//����Ʈ �Ҹ���.

public:
	J_Timer(const J_Timer& _other) = delete;		//����Ʈ ���������.
	J_Timer(J_Timer&& _other) = delete;		//����Ʈ rvalue ���������.

	J_Timer& operator=(const J_Timer& _other) = delete;		//����Ʈ ���Կ�����.
	J_Timer& operator=(const J_Timer&& _other) = delete;		//����Ʈ rvalue ���Կ�����.

public:
	void ResetTimer();			//�ð� ���� �غ� �Լ�.
	void MeasureDeltaTime();	//�ð� ���� �Լ�.

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

