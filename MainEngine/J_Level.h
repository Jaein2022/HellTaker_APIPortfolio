#pragma once
#include <map>
#include <string>
#include <vector>
#include <list>
#include <J_GameEngineDebug.h>
#include <J_GameEngineMath.h>
#include <J_GameEngineNameBase.h>

class J_Actor;
class J_LevelManager;
class J_Level: public J_GameEngineNameBase
{
	friend J_LevelManager;

	std::map<std::string, J_Actor*> allActors_;					//각 레벨별 액터들을 저장한 맵.
	std::map<int, std::list<J_Actor*>> allActors_UpdateOrder_;	//각 레벨별 액터들을 업데이트 순서대로 정리한 맵.
	std::map<int, std::list<J_Actor*>> allActors_RenderOrder_;	//각 레벨별 액터들을 렌더링 순서대로 정리한 맵.
	
	bool isReset_;												//이 변수가 true면 레벨매니저가 curLevel을 리셋한다.
	bool isLoaded_;												//레벨 중복 로드 방지.
	float4 cameraPos_;											//카메라 위치. 
	//따라다니는 플레이어의 이동량만큼 같이 변화하고, 그 변화량이 카메라의 영향을 받는 액터들의 윈도우 내 위치에 역산되서,
	//플레이어는 계속 움직여서 좌표가 바뀌지만 윈도우 내에서는 고정된 자리에 계속 렌더링되고
	//배경은 움직이지 않았지만 플레이어의 반대로 움직인것처럼 렌더링되어, 결과적으로 플레이어가 배경 위를 움직이는 것처럼 보인다.

protected:
	J_Level();		//디폴트 생성자.
	virtual ~J_Level();		//디폴트 소멸자.

public:
	J_Level(const J_Level& _other) = delete;		//디폴트 복사생성자.
	J_Level(J_Level&& _other) = delete;				//디폴트 rvalue 복사생성자.

	J_Level& operator=(const J_Level& _other) = delete;		//디폴트 대입연산자.
	J_Level& operator=(const J_Level&& _other) = delete;		//디폴트 rvalue 대입연산자.

public:
	void ResetLevel();	//현재 레벨을 리셋하는 함수.
	J_Actor* FindActor(const std::string& _actorName);

public:
	float4 GetCameraPos() const
	{
		return cameraPos_;
	}

	void SetCameraPos(const float4& _pos)
	{
		cameraPos_ = _pos;
	}

	void SetCameraMove(const float4& _pos)
	{
		cameraPos_ += _pos;
	}


protected:
	virtual void LoadLevel() = 0;		//아래 Load함수가 호출하는, 레벨 구성요소들을 불러오는 함수.
	virtual void PreUpdateLevel() {}
	virtual void UpdateLevel() = 0;		//액터들을 제외한 나머지 레벨 구성요소들을 업데이트 하는 함수.
	virtual void PostUpdateLevel() {}
	virtual void LevelRender() {};		//액터가 아닌 디버깅 요소들을 렌더링하는 함수. 자동적으로 렌더오더 최후순위처럼 된다. 
	//이 함수들 모두 가상함수로 선언해서 실질적인 내용은 각각의 레벨들이 직접 채우게 한다.

	template<typename actorType>
	actorType* CreateActor(const std::string& _actorName)
		//해당 레벨에서 쓸 액터들을 생성하는 함수.
	{
		if (true == _actorName.empty())	//_actorName이 없다면 폭파.
		{
			J_GameEngineDebug::AssertFalse();
			return nullptr;
		}

		if (allActors_.end() != allActors_.find(_actorName))	//같은 이름의 액터가 또 있다면 폭파.
		{
			J_GameEngineDebug::AssertFalse();
			return nullptr;
		}

		std::map<int, std::list<J_Actor*>>::iterator it_Update = allActors_UpdateOrder_.find(0);
		if (allActors_UpdateOrder_.end() == it_Update)	//기본적으로 있어야 할 0번리스트가 없다면 폭파.
		{
			J_GameEngineDebug::AssertFalse();
			return nullptr;
		}

		std::map<int, std::list<J_Actor*>>::iterator it_Render = allActors_RenderOrder_.find(0);
		if (allActors_RenderOrder_.end() == it_Render)	//기본적으로 있어야 할 0번리스트가 없다면 폭파.
		{
			J_GameEngineDebug::AssertFalse();
			return nullptr;
		}

		//여기까지 아무 문제 없다면 본격적으로 새 액터 생성.
		actorType* NewActor = new actorType();
		NewActor->SetParentLevel(this);
		NewActor->SetName(_actorName);
		NewActor->Start();

		//생성한 NewActor를 allActors 컨테이너들에 넣어서 관리 대상으로 등록한다.
		allActors_.insert(std::map<std::string, J_Actor*>::value_type(_actorName, NewActor));
		it_Update->second.push_back(NewActor);
		it_Render->second.push_back(NewActor);
		return NewActor;	
	}

private:
	void Load();					//레벨 구성요소 로드. 레벨매니저는 이 함수만 사용.
	void SortUpdateOrder();			//업데이트 순서 정렬 함수.
	void PreUpdateActors() {};		
	void UpdateActors();			//액터들만 업데이트하는 함수.
	void PostUpdateActors() {};		
	void SortRenderOrder();			//렌더링 순서 정렬 함수.
	void Render();					//레벨매니저의 curLevel_로 지정된 레벨에 포함된 모든 요소들을 렌더하는 함수.
	void RemoveActors();			//삭제된 액터들을 제거한다.
	void ClearLevel();				//리셋이나 종료하기 전에 레벨의 모든 요소들을 정리하는 함수.
};

