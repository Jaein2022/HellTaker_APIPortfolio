#pragma once
#include <string>
#include <vector>

class AppFunctions
{


public:
	AppFunctions();		//디폴트 생성자.
	~AppFunctions();		//디폴트 소멸자.

public:
	AppFunctions(const AppFunctions& _other) = delete;		//디폴트 복사생성자.
	AppFunctions(AppFunctions&& _other) = delete;		//디폴트 rvalue 복사생성자.

	AppFunctions& operator=(const AppFunctions& _other) = delete;		//디폴트 대입연산자.
	AppFunctions& operator=(const AppFunctions&& _other) = delete;		//디폴트 rvalue 대입연산자.

public:
	static void InitializeApp();
	static void ReleaseApp();
};

