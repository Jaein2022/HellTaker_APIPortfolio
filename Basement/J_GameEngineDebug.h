#pragma once
#include <crtdbg.h>
#include <assert.h>


class J_GameEngineDebug
{


public:
	J_GameEngineDebug();		//디폴트 생성자.
	~J_GameEngineDebug();		//디폴트 소멸자.

public:
	J_GameEngineDebug(const J_GameEngineDebug& _other) = delete;		//디폴트 복사생성자.
	J_GameEngineDebug(J_GameEngineDebug&& _other) noexcept;		//디폴트 rvalue 복사생성자.

	J_GameEngineDebug& operator=(const J_GameEngineDebug& _other) = delete;		//디폴트 대입연산자.
	J_GameEngineDebug& operator=(const J_GameEngineDebug&& _other) = delete;		//디폴트 rvalue 대입연산자.

public:
	static void CheckLeak();
	static void AssertFalse();
	static void AssertFalse(const char* _message);
	static void DisplayManual();

};

