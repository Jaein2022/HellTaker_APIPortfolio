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
	J_Level* parentLevel_;					//�� ���͸� ������ ����.
	float4 actorPos_;						//�� ������ ��ġ.
	int renderOrder_;						//�� ������ ������ �켱����. �������� ������.
	int updateOrder_;						//�� ������ ������Ʈ �켱����. �������� ������.
	std::map<std::string, J_Renderer*> allRenderers_;	//�� ���Ͱ� ���� ��������.
	bool isDestroyed_;						//�� ���Ͱ� �ı��Ǿ����� ����.

protected:
	J_Actor();
	virtual ~J_Actor();

public:
	J_Actor(J_Actor&& _other) = delete;
	J_Actor(const J_Actor& _other) = delete;		//����Ʈ ���������.

	J_Actor& operator=(const J_Actor& _other) = delete;		//����Ʈ ���Կ�����.
	J_Actor& operator=(const J_Actor&& _other) = delete;		//����Ʈ rvalue ���Կ�����.

public:
	float4 GetCameraPos();

public:
	const J_Level* GetParentLevel() const
	{
		if (nullptr == parentLevel_)	
			//���� ������ �ݵ�� �������� �� �� �ִµ�, �� ������ ������ ���ٴ°� ��ü�� ���� �߸��� ���̹Ƿ� ���α׷� ����. 
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

	void SetActorPos(float4 _pos)	//������ ��ġ�� Ư�� �������� �缳��.
	{
		actorPos_ = _pos;
	}


	void SetActorMovement(const float4& _direction)	//������ �̵� ����� �ӵ� ����.
	{
		actorPos_ += _direction;
	}


	J_Renderer* CreateRenderer(const std::string& _imageName, const std::string& _rendererName);

protected:


	virtual void Start();			//�� ���͵��� �غ� �Լ�.
	virtual	void PreUpdate() {};	//������Ʈ �Լ� ���� �� �ؾ� �� ������ ����ϴ� �Լ�. 
	virtual void Update();			//���� ���࿡ ���� ���� ���������� �����ؼ� Render()�Լ��� ���� ���� �׸��� �ϴ� �Լ�. 
	virtual void PostUpdate() {};	//������Ʈ �Լ� ���� �� �ؾ� �� ó���� ����ϴ� �Լ�.
	virtual void Render();			//������ �׿� ���� ���� ���͵��� ȭ�鿡 �׸��� �Լ�. 

protected:
	void SetUpdateOrder(int _updateOrder)		//������Ʈ ���� ����. ��ȣ�� �������� ���� ������Ʈ.
	{
		updateOrder_ = _updateOrder;
	}

	void SetRenderOrder(int _renderOrder)		//������ ���� ����. ��ȣ�� �������� �ٸ� ���͸� ������ �տ� �׷�����.
	{
		renderOrder_ = _renderOrder;
	}


private:
	void SetParentLevel(J_Level* _parentLevel)	//�� ���͸� ������ ������ parentLevel_�� ����ϴ� �Լ�.
		//�� ���͸� �����ϴ� ���� ���� �Լ��̹Ƿ� private�� �ٸ� �����κ����� ������ ���´�.
	{
		parentLevel_ = _parentLevel;
	}
};

