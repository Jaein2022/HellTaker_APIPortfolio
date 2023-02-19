#pragma once
#include <crtdbg.h>
#include <assert.h>


class J_GameEngineDebug
{


public:
	J_GameEngineDebug();		//����Ʈ ������.
	~J_GameEngineDebug();		//����Ʈ �Ҹ���.

public:
	J_GameEngineDebug(const J_GameEngineDebug& _other) = delete;		//����Ʈ ���������.
	J_GameEngineDebug(J_GameEngineDebug&& _other) noexcept;		//����Ʈ rvalue ���������.

	J_GameEngineDebug& operator=(const J_GameEngineDebug& _other) = delete;		//����Ʈ ���Կ�����.
	J_GameEngineDebug& operator=(const J_GameEngineDebug&& _other) = delete;		//����Ʈ rvalue ���Կ�����.

public:
	static void CheckLeak();
	static void AssertFalse();
	static void AssertFalse(const char* _message);
	static void DisplayManual();

};

