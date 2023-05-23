#pragma once
#include <map>
#include <string>
#include <vector>
#include <J_GameEngineDebug.h>
#include <J_GameEngineNameBase.h>
#include <J_GameEngineMath.h>


enum class RENDERPIVOT
{
	CENTER,
	BOT,
	LEFTTOP,
	MAX
};

class J_Actor;
class J_ImageFile;
class J_Renderer: public J_GameEngineNameBase
{

	class Animation : public J_GameEngineNameBase
	{
		friend J_Renderer;

		size_t startIndex_;				//�ִϸ��̼� ���� �ε���.
		size_t finishIndex_;				//�ִϸ��̼� ���� �ε���.
		size_t curIndex_;					//���� �������� �ε���.
		float curDelay_;				//
		J_Renderer* parentRenderer_;	//�� �ִϸ��̼��� ������ �θ� ������.
		J_ImageFile* animationImage_;		//�ִϸ��̼��� �����ϴ� �̹���.
		RENDERPIVOT pivot_;				//�����̹��� �Ǻ�.
		bool isLoopAnim_;				//�ִϸ��̼��� ���ѹݺ�/1ȸ�� ����.
		bool isFinished_;				//�ִϸ��̼��� �������� ����.
		std::vector<float> delayEachFrame_;

	private:
		Animation();
		void Update();
		void Reset()
		{
			curIndex_ = startIndex_;
			curDelay_ = delayEachFrame_[0];
			isFinished_ = false;
		}
	};

private:
	friend J_Actor;
	
	J_Actor* parentActor_;		//�� �������� ���� ����.
	float4 renderSize_;			//�ڸ� �����̹����� ����� ���� �������� ũ��. �����ϸ� actorImageSize_�� �����ϰ� �� ��.
	float4 pivotPos_;
	//���������� ��� ������ ���͸� ����ٴϴ� �̹���/�ִϸ��̼��� ��ġ�Ҷ�, ��� �������� �󸶳� ������ ������ ��ġ���� ���ϴ� ����.
	//������������ ���� ����� �ʴ´ٸ� {0, 0}.

	J_ImageFile* actorImage_;		//�� �������� ���� ������ �̹���. 
	float4 actorImagePos_;		//�����̹��� ������ �������� ������ ������(���� ���).
	float4 actorImageSize_;		//�����̹������� �������� �� ũ��.
	float4 actorImagePivot_;	//�������ϴ� �̹����� ������. �� ���� �������� ���������� �ǹ������� �̹���/�ִϸ��̼��� ��ġ�Ѵ�.

	Animation* curAnimation_;	//���� �������� �ִϸ��̼�.
	std::map<std::string, Animation*> allAnimations_;	//��� �ִϸ��̼��� ����.

	//�ִϸ��̼� ���� ��������� ���߿� �߰�.
	bool isCameraEffect_;		//ī�޶� ȿ���� ��������� ����. ����8���� ����.

	//bool isAnimation_;			//������ ������ �̹�������, �ִϸ��̼����� ����.
public:
	J_Renderer();		//����Ʈ ������.
	~J_Renderer();		//����Ʈ �Ҹ���.

public:
	J_Renderer(J_Renderer&& _other) = delete;		//����Ʈ rvalue ���������.
	J_Renderer(const J_Renderer& _other) = delete;		//����Ʈ ���������.

	J_Renderer& operator=(const J_Renderer& _other) = delete;		//����Ʈ ���Կ�����.
	J_Renderer& operator=(const J_Renderer&& _other) = delete;		//����Ʈ rvalue ���Կ�����.

public:
	void Render();
	void SetActorImagePivot(RENDERPIVOT _pivot);	
	void SetFrameIndex(int _index, RENDERPIVOT _pivot);
	void CreateAnimation(
		const std::string& _animationName,
		const std::string& _imageName,
		int _startIndex,
		int _finishIndex,
		bool _isLoopAnim = false,
		float _delayPerFrame = 0.065f,
		RENDERPIVOT _pivot = RENDERPIVOT::BOT
	);
	void ChangeAnimation(const std::string& _animationName, bool _isForceChange = false);
	void UpdateAnimation();
	bool IsCurAnimationFinish();
	bool IsCurAnimationName(const std::string& _animationName);
	void SetFrameDelay(const std::string& _animationName, int _index, float _delay);
	int GetCurFrame();

public:
	J_ImageFile* const GetActorImage() const
	{
		return actorImage_;
	}

	void SetRenderSize(const float4& _size)
	{
		renderSize_ = _size;
	}

	void SetPivotPos(const float4& _pos)
	{
		pivotPos_ = _pos;
	}

	void SetActorImagePos(const float4& _pos = float4::ZERO)
	{
		actorImagePos_ = _pos;
	}

	void SetActorImageSize(const float4& _size)
	{
		actorImageSize_ = _size;
	}

	void SetActorImagePivot(const float4& _pos)
	{
		actorImagePivot_ = _pos;
	}

	void SetCameraEffectOn()
	{
		isCameraEffect_ = true;
	}

	void SetCameraEffectOff()
	{
		isCameraEffect_ = false;
	}



private:
	void SetActorImage(const std::string& _imageName);

private:
	void SetParentActor(J_Actor* const _parentActor)
	{
		parentActor_ = _parentActor;
	}

	Animation* FindAnimation(const std::string& _animationName)
	{
		std::map<std::string, Animation*>::iterator it = allAnimations_.find(_animationName);
		if (allAnimations_.end() == it)
		{
			return nullptr;
		}
		else
		{
			return it->second;
		}
	}
	
};

