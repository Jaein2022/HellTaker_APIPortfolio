#pragma once
#include <string>
class J_GameEngineNameBase
{
	std::string name_;

public:
	J_GameEngineNameBase();		//디폴트 생성자.
	~J_GameEngineNameBase();		//디폴트 소멸자.

public:
	J_GameEngineNameBase(const J_GameEngineNameBase& _other) = delete;		//디폴트 복사생성자.
	J_GameEngineNameBase(J_GameEngineNameBase&& _other) noexcept;		//디폴트 rvalue 복사생성자.

	J_GameEngineNameBase& operator=(const J_GameEngineNameBase& _other) = delete;		//디폴트 대입연산자.
	J_GameEngineNameBase& operator=(const J_GameEngineNameBase&& _other) = delete;		//디폴트 rvalue 대입연산자.

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

