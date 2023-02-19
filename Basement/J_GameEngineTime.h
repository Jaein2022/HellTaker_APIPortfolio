#pragma once
#include <Windows.h>
#include <assert.h>

class J_GameEngineTime
{
	static J_GameEngineTime* instance_;

	LARGE_INTEGER frequency_;		//�ʴ� CPU ���ļ�(�ʴ� Ŭ�� �ݺ� ȸ��). �������̹Ƿ� ó�� �ѹ��� ���.
	LARGE_INTEGER beginningCheck_;	//���� ���۽����� ���� Ŭ�� ��.
	LARGE_INTEGER finishingCheck_;	//���� ���������� ���� Ŭ�� ��.
	double deltaTime_;				//���� ������ �ѹ� ���� �� �� �ɸ� �ð� = ���� �ѹ��� �����Ǵ� Ŭ�� �� / �ʴ� CPU Ŭ�� �ݺ� ȸ��.
	//��ǻ���� ������ �������� ��ŸŸ���� ��ġ�� ��������, ��ǻ�� ���� ������ ���� ���� �ٸ� �ӵ��� ������ �����Ѵٰ� �ص� 
	//���ɿ� �ݺ���ؼ� ��ŸŸ�� ���� �۰� ������ ������, ��ǻ�� ���� ������� ���� �ð� ���� ���� ����ӵ��� �����ְ� �ȴ�.	


	J_GameEngineTime();		//����Ʈ ������.
	~J_GameEngineTime();		//����Ʈ �Ҹ���.

public:
	J_GameEngineTime(const J_GameEngineTime& _other) = delete;		//����Ʈ ���������.
	J_GameEngineTime(J_GameEngineTime&& _other) = delete;		//����Ʈ rvalue ���������.

	J_GameEngineTime& operator=(const J_GameEngineTime& _other) = delete;		//����Ʈ ���Կ�����.
	J_GameEngineTime& operator=(const J_GameEngineTime&& _other) = delete;		//����Ʈ rvalue ���Կ�����.

public:
	void ResetTimer();			//�ð� ���� �غ� �Լ�.
	void UpdateDeltaTime();	//�ð� ���� �Լ�.

	static J_GameEngineTime& GetInstance()
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

	double GetDeltaTimeD() const
	{
		return deltaTime_;
	}

	float GetDeltaTimeF() const
	{
		return static_cast<float>(deltaTime_);
	}
};

