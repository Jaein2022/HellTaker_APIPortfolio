#pragma once
#include <string>
#include <map>
#include <J_GameEngineDebug.h>
#include <J_GameEngineMath.h>
#include <J_GameEngineNameBase.h>

class J_Renderer;
class J_Level;
class J_Actor: public J_GameEngineNameBase
{
	friend J_Level;

protected:
	J_Level* parentLevel_;					//이 액터를 생성한 레벨.
	float4 actorPos_;						//이 액터의 위치.
	int renderOrder_;						//이 액터의 렌더링 우선순위. 낮을수록 빠르다.
	int updateOrder_;						//이 액터의 업데이트 우선순위. 낮을수록 빠르다.
	std::map<std::string, J_Renderer*> allRenderers_;	//이 액터가 가진 렌더러들.
	bool isDestroyed_;						//이 액터가 파괴되었는지 여부.

protected:
	J_Actor();
	virtual ~J_Actor();

public:
	J_Actor(J_Actor&& _other) = delete;
	J_Actor(const J_Actor& _other) = delete;		//디폴트 복사생성자.

	J_Actor& operator=(const J_Actor& _other) = delete;		//디폴트 대입연산자.
	J_Actor& operator=(const J_Actor&& _other) = delete;		//디폴트 rvalue 대입연산자.

public:
	float4 GetCameraPos();

public:
	const J_Level* GetParentLevel() const
	{
		if (nullptr == parentLevel_)	
			//액터 생성은 반드시 레벨만이 할 수 있는데, 그 생성한 레벨이 없다는것 자체가 뭔가 잘못된 것이므로 프로그램 폭파. 
		{
			J_GameEngineDebug::AssertFalse();
			return nullptr;
		}
		else
		{
			return parentLevel_;
		}
	}

	const float4 GetActorPos() const	
	{
		return actorPos_;
	}

	void SetActorPos(float4 _pos)	//액터의 위치를 특정 지점으로 재설정.
	{
		actorPos_ = _pos;
	}


	void SetActorMovement(const float4& _direction)	//액터의 이동 방향과 속도 설정.
	{
		actorPos_ += _direction;
	}


	J_Renderer* CreateRenderer(const std::string& _imageName, const std::string& _rendererName);

protected:


	virtual void Start();			//각 액터들의 준비 함수.
	virtual	void PreUpdate() {};	//업데이트 함수 실행 전 해야 할 과정을 담당하는 함수. 
	virtual void Update();			//게임 진행에 따른 각종 변동사항을 저장해서 Render()함수를 통해 고쳐 그리게 하는 함수. 
	virtual void PostUpdate() {};	//업데이트 함수 실행 후 해야 할 처리를 담당하는 함수.
	virtual void Render();			//레벨과 그에 딸린 각종 액터들을 화면에 그리는 함수. 

protected:
	void SetUpdateOrder(int _updateOrder)		//업데이트 순서 설정. 번호가 낮을수록 먼저 업데이트.
	{
		updateOrder_ = _updateOrder;
	}

	void SetRenderOrder(int _renderOrder)		//렌더링 순서 설정. 번호가 높을수록 다른 액터를 가리고 앞에 그려진다.
	{
		renderOrder_ = _renderOrder;
	}


private:
	void SetParentLevel(J_Level* _parentLevel)	//이 액터를 생성한 레벨을 parentLevel_로 등록하는 함수.
		//이 액터를 생성하는 레벨 전용 함수이므로 private로 다른 곳으로부터의 접근을 막는다.
	{
		parentLevel_ = _parentLevel;
	}
};

