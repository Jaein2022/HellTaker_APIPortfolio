#pragma once
#include <string>
class J_GameEngineNameBase
{
	std::string name_;

public:
	J_GameEngineNameBase();		//����Ʈ ������.
	~J_GameEngineNameBase();		//����Ʈ �Ҹ���.

public:
	J_GameEngineNameBase(const J_GameEngineNameBase& _other) = delete;		//����Ʈ ���������.
	J_GameEngineNameBase(J_GameEngineNameBase&& _other) noexcept;		//����Ʈ rvalue ���������.

	J_GameEngineNameBase& operator=(const J_GameEngineNameBase& _other) = delete;		//����Ʈ ���Կ�����.
	J_GameEngineNameBase& operator=(const J_GameEngineNameBase&& _other) = delete;		//����Ʈ rvalue ���Կ�����.

public:
	const std::string& GetName() const
	{
		return name_;
	}

	void SetName(const std::string& _name)
	{
		name_ = _name;
	}

};

