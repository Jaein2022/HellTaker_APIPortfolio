#include "J_GameEngineDebug.h"
#include "windows.h"
#include <string>

J_GameEngineDebug::J_GameEngineDebug()
{
}

J_GameEngineDebug::J_GameEngineDebug(J_GameEngineDebug&& _other) noexcept
{
}

J_GameEngineDebug::~J_GameEngineDebug()
{
}

void J_GameEngineDebug::CheckLeak()
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
}

void J_GameEngineDebug::AssertFalse()
{
	assert(false);
}

void J_GameEngineDebug::AssertFalse(const char* _message)	//차차 아래 함수로 전부 대체할 것.
{
	MessageBoxA(nullptr, _message, "Error!", MB_OK);
	assert(false);
}

void J_GameEngineDebug::DisplayManual()
{
	std::string manual("WASD: 이동. \n");
	manual = manual + "R: 챕터 리셋. \n";
	manual = manual + "I: 히어로 이동 666으로 변경. \n";
	manual = manual + "K: 히어로 즉시 사망. \n";
	manual = manual + "J: 히어로가 0번골타일로 즉시 이동. \n";
	manual = manual + "V: 타일 보이게/안보이게 하기. \n";
	manual = manual + "N: 바로 다음 챕터로 넘어감.";
	
	MessageBoxA(nullptr, manual.c_str(), "Manual", MB_OK | MB_ICONINFORMATION);
}
