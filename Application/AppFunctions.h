#pragma once
#include <string>
#include <vector>

class AppFunctions
{


public:
	AppFunctions();		//����Ʈ ������.
	~AppFunctions();		//����Ʈ �Ҹ���.

public:
	AppFunctions(const AppFunctions& _other) = delete;		//����Ʈ ���������.
	AppFunctions(AppFunctions&& _other) = delete;		//����Ʈ rvalue ���������.

	AppFunctions& operator=(const AppFunctions& _other) = delete;		//����Ʈ ���Կ�����.
	AppFunctions& operator=(const AppFunctions&& _other) = delete;		//����Ʈ rvalue ���Կ�����.

public:
	static void InitializeApp();
	static void ReleaseApp();
};

