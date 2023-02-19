#pragma once
#include "HellActor.h"


class J_Renderer;
class OpenningBG: public HellActor
{
	J_Renderer* openning_Renderer_;
	float4 openningRenderSize_;
	double openningFinishTime_;		//�������� ���������� ���� �ð�.
	float enlargementRatio_;		//������ �̹��� Ȯ�� ����. 1.0f�� �⺻��.
	bool isOpenningFinished_;		//�������� �������� ����.

public:
	OpenningBG();		//����Ʈ ������.
	~OpenningBG();		//����Ʈ �Ҹ���.

public:
	OpenningBG(const OpenningBG& _other) = delete;		//����Ʈ ���������.
	OpenningBG(OpenningBG&& _other) = delete;		//����Ʈ rvalue ���������.

	OpenningBG& operator=(const OpenningBG& _other) = delete;		//����Ʈ ���Կ�����.
	OpenningBG& operator=(const OpenningBG&& _other) = delete;		//����Ʈ rvalue ���Կ�����.

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

