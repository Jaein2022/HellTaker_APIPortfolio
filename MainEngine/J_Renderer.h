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

		size_t startIndex_;				//애니메이션 시작 인덱스.
		size_t finishIndex_;				//애니메이션 종료 인덱스.
		size_t curIndex_;					//현재 프레임의 인덱스.
		float curDelay_;				//
		J_Renderer* parentRenderer_;	//이 애니메이션을 생성한 부모 렌더러.
		J_ImageFile* animationImage_;		//애니메이션이 렌더하는 이미지.
		RENDERPIVOT pivot_;				//액터이미지 피봇.
		bool isLoopAnim_;				//애니메이션이 무한반복/1회로 종료.
		bool isFinished_;				//애니메이션이 끝났는지 여부.
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
	
	J_Actor* parentActor_;		//이 렌더러를 가진 액터.
	float4 renderSize_;			//자른 액터이미지를 백버퍼 위에 렌더링할 크기. 웬만하면 actorImageSize_와 동일하게 할 것.
	float4 pivotPos_;
	//액터포스를 벗어난 곳에서 액터를 따라다니는 이미지/애니메이션을 배치할때, 어느 방향으로 얼마나 떨어진 지점에 배치할지 정하는 지점.
	//액터포스에서 전혀 벗어나지 않는다면 {0, 0}.

	J_ImageFile* actorImage_;		//이 렌더러를 가진 액터의 이미지. 
	float4 actorImagePos_;		//액터이미지 내에서 렌더링을 시작할 시작점(왼쪽 상단).
	float4 actorImageSize_;		//액터이미지에서 렌더링을 할 크기.
	float4 actorImagePivot_;	//렌더링하는 이미지의 기준점. 이 점을 기준으로 액터포스나 피벗포스에 이미지/애니메이션을 배치한다.

	Animation* curAnimation_;	//현재 진행중인 애니메이션.
	std::map<std::string, Animation*> allAnimations_;	//모든 애니메이션을 저장.

	//애니메이션 관련 멤버변수는 나중에 추가.
	bool isCameraEffect_;		//카메라 효과를 적용받을지 여부. 레벨8에만 적용.

	//bool isAnimation_;			//고정된 한장의 이미지인지, 애니메이션인지 여부.
public:
	J_Renderer();		//디폴트 생성자.
	~J_Renderer();		//디폴트 소멸자.

public:
	J_Renderer(J_Renderer&& _other) = delete;		//디폴트 rvalue 복사생성자.
	J_Renderer(const J_Renderer& _other) = delete;		//디폴트 복사생성자.

	J_Renderer& operator=(const J_Renderer& _other) = delete;		//디폴트 대입연산자.
	J_Renderer& operator=(const J_Renderer&& _other) = delete;		//디폴트 rvalue 대입연산자.

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

