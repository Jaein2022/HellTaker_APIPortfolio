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

	std::map<std::string, J_Actor*> allActors_;					//�� ������ ���͵��� ������ ��.
	std::map<int, std::list<J_Actor*>> allActors_UpdateOrder_;	//�� ������ ���͵��� ������Ʈ ������� ������ ��.
	std::map<int, std::list<J_Actor*>> allActors_RenderOrder_;	//�� ������ ���͵��� ������ ������� ������ ��.
	
	bool isReset_;												//�� ������ true�� �����Ŵ����� curLevel�� �����Ѵ�.
	bool isLoaded_;												//���� �ߺ� �ε� ����.
	float4 cameraPos_;											//ī�޶� ��ġ. 
	//����ٴϴ� �÷��̾��� �̵�����ŭ ���� ��ȭ�ϰ�, �� ��ȭ���� ī�޶��� ������ �޴� ���͵��� ������ �� ��ġ�� ����Ǽ�,
	//�÷��̾�� ��� �������� ��ǥ�� �ٲ����� ������ �������� ������ �ڸ��� ��� �������ǰ�
	//����� �������� �ʾ����� �÷��̾��� �ݴ�� �����ΰ�ó�� �������Ǿ�, ��������� �÷��̾ ��� ���� �����̴� ��ó�� ���δ�.

protected:
	J_Level();		//����Ʈ ������.
	virtual ~J_Level();		//����Ʈ �Ҹ���.

public:
	J_Level(const J_Level& _other) = delete;		//����Ʈ ���������.
	J_Level(J_Level&& _other) = delete;				//����Ʈ rvalue ���������.

	J_Level& operator=(const J_Level& _other) = delete;		//����Ʈ ���Կ�����.
	J_Level& operator=(const J_Level&& _other) = delete;		//����Ʈ rvalue ���Կ�����.

public:
	void ResetLevel();	//���� ������ �����ϴ� �Լ�.
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
	virtual void LoadLevel() = 0;		//�Ʒ� Load�Լ��� ȣ���ϴ�, ���� ������ҵ��� �ҷ����� �Լ�.
	virtual void PreUpdateLevel() {}
	virtual void UpdateLevel() = 0;		//���͵��� ������ ������ ���� ������ҵ��� ������Ʈ �ϴ� �Լ�.
	virtual void PostUpdateLevel() {}
	virtual void LevelRender() {};		//���Ͱ� �ƴ� ����� ��ҵ��� �������ϴ� �Լ�. �ڵ������� �������� ���ļ���ó�� �ȴ�. 
	//�� �Լ��� ��� �����Լ��� �����ؼ� �������� ������ ������ �������� ���� ä��� �Ѵ�.

	template<typename actorType>
	actorType* CreateActor(const std::string& _actorName)
		//�ش� �������� �� ���͵��� �����ϴ� �Լ�.
	{
		if (true == _actorName.empty())	//_actorName�� ���ٸ� ����.
		{
			J_GameEngineDebug::AssertFalse();
			return nullptr;
		}

		if (allActors_.end() != allActors_.find(_actorName))	//���� �̸��� ���Ͱ� �� �ִٸ� ����.
		{
			J_GameEngineDebug::AssertFalse();
			return nullptr;
		}

		std::map<int, std::list<J_Actor*>>::iterator it_Update = allActors_UpdateOrder_.find(0);
		if (allActors_UpdateOrder_.end() == it_Update)	//�⺻������ �־�� �� 0������Ʈ�� ���ٸ� ����.
		{
			J_GameEngineDebug::AssertFalse();
			return nullptr;
		}

		std::map<int, std::list<J_Actor*>>::iterator it_Render = allActors_RenderOrder_.find(0);
		if (allActors_RenderOrder_.end() == it_Render)	//�⺻������ �־�� �� 0������Ʈ�� ���ٸ� ����.
		{
			J_GameEngineDebug::AssertFalse();
			return nullptr;
		}

		//������� �ƹ� ���� ���ٸ� ���������� �� ���� ����.
		actorType* NewActor = new actorType();
		NewActor->SetParentLevel(this);
		NewActor->SetName(_actorName);
		NewActor->Start();

		//������ NewActor�� allActors �����̳ʵ鿡 �־ ���� ������� ����Ѵ�.
		allActors_.insert(std::map<std::string, J_Actor*>::value_type(_actorName, NewActor));
		it_Update->second.push_back(NewActor);
		it_Render->second.push_back(NewActor);
		return NewActor;	
	}

private:
	void Load();					//���� ������� �ε�. �����Ŵ����� �� �Լ��� ���.
	void SortUpdateOrder();			//������Ʈ ���� ���� �Լ�.
	void PreUpdateActors() {};		
	void UpdateActors();			//���͵鸸 ������Ʈ�ϴ� �Լ�.
	void PostUpdateActors() {};		
	void SortRenderOrder();			//������ ���� ���� �Լ�.
	void Render();					//�����Ŵ����� curLevel_�� ������ ������ ���Ե� ��� ��ҵ��� �����ϴ� �Լ�.
	void RemoveActors();			//������ ���͵��� �����Ѵ�.
	void ClearLevel();				//�����̳� �����ϱ� ���� ������ ��� ��ҵ��� �����ϴ� �Լ�.
};

