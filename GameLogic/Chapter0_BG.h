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
	//double openningFinishTime_;		//�������� ���������� ���� �ð�.
	//float enlargementRatio_;		//������ �̹��� Ȯ�� ����. 1.0f�� �⺻��.
	//bool isOpenningFinished_;		//�������� �������� ����.

	friend Chapter0;
	std::vector<Button*> allButtons_Chapter0_;
	int buttonIndex_;

	J_Renderer* justBlackBoard_;		//���� �� ���� ���. 
	J_Renderer* Chapter0_BG01_;			//�����̴� ��� 01��.
	J_Renderer* Chapter0_BG02_;			//�����̴� ��� 02��.
	J_Renderer* Chapter0_BG03_;			//�����̴� ��� 03��.
	J_Renderer* Chapter0_BG04_;			//�����̴� ��� 04��.
	J_Renderer* beelFly_Renderer_;
	//J_Renderer* booper_Renderer_;

	const float distanceFromAbyss01_;	//abyss02�� �̹����� ���� �������� abyss01�� �̹����� ���� ���������� �ڷ� ������ �־�� �ϴ� �Ÿ�. 
	const float distanceFromAbyss02_;	//abyss01�� �̹����� ���� �������� abyss02�� �̹����� ���� ���������� �ڷ� ������ �־�� �ϴ� �Ÿ�.
	float BG01PivotPosX_;				//BG01 ���� x��ǥ.
	float BG02PivotPosX_;				//BG02 ���� x��ǥ.
	float BG03PivotPosX_;				//BG03 ���� x��ǥ.
	float BG04PivotPosX_;				//BG04 ���� x��ǥ.
	const float BGsPivotPosY_;			//BG01, 02, 03, 04�� ���� y��ǥ��. 

	J_SoundPlayer* Chapter0_BGSound_Player_;

	HDC backBufferHDC_;

	HFONT introductionFont_;
	std::string introduction_;

	HFONT lineFont_;
	std::string line0_;
	std::string line1_;

public:
	Chapter0_BG();		//����Ʈ ������.
	~Chapter0_BG();		//����Ʈ �Ҹ���.

public:
	Chapter0_BG(const Chapter0_BG& _other) = delete;		//����Ʈ ���������.
	Chapter0_BG(Chapter0_BG&& _other) = delete;		//����Ʈ rvalue ���������.

	Chapter0_BG& operator=(const Chapter0_BG& _other) = delete;		//����Ʈ ���Կ�����.
	Chapter0_BG& operator=(const Chapter0_BG&& _other) = delete;		//����Ʈ rvalue ���Կ�����.

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

