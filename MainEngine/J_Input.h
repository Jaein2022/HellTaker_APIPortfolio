#pragma once
#include <J_GameEngineDebug.h>
#include <J_GameEngineNameBase.h>
#include <map>

class J_Window;
class J_Input
{
	friend J_Window;
	static J_Input* instance_;


	class J_Key: public J_GameEngineNameBase
	{
		friend J_Input;

		bool isDown_;
		bool isUp_;
		bool isPressed_;
		bool isFree_;
		int keyValue_;

		J_Key();
		~J_Key();
	public:
		void Update();

	};

private:
	std::map<std::string, J_Key*> allKeys_;


private:
	J_Input();		//디폴트 생성자.
	~J_Input();		//디폴트 소멸자.

public:
	J_Input(const J_Input& _other) = delete;		//디폴트 복사생성자.
	J_Input(J_Input&& _other) = delete;		//디폴트 rvalue 복사생성자.
	J_Input& operator=(const J_Input& _other) = delete;		//디폴트 대입연산자.
	J_Input& operator=(const J_Input&& _other) = delete;		//디폴트 rvalue 대입연산자.

public:
	bool CreateKey(const std::string& _name, int _key);
	bool CheckKeyExistence(const std::string& _name);
	bool GetIsDown(const std::string& _name);
	bool GetIsUp(const std::string& _name);
	bool GetIsPressed(const std::string& _name);
	bool GetIsFree(const std::string& _name);
	void Update();

public:
	static J_Input& GetInstance()
	{
		return *instance_;
	}

	static void DestroyInstance()
	{
		if (nullptr == instance_)
		{
			J_GameEngineDebug::AssertFalse("J_Input::DestroyInstance()-> nullptr == instance_");
			return;
		}
		
		delete instance_;
		instance_ = nullptr;
	}





private:
	J_Key* FindKey(const std::string& _name)
	{
		std::map<std::string, J_Key*>::iterator it = allKeys_.find(_name);
		if (allKeys_.end() == it)
		{
			return nullptr;
		}
		else
		{
			return it->second;
		}
	}
};

