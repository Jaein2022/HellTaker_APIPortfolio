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

void J_GameEngineDebug::AssertFalse(const char* _message)	//���� �Ʒ� �Լ��� ���� ��ü�� ��.
{
	MessageBoxA(nullptr, _message, "Error!", MB_OK);
	assert(false);
}

void J_GameEngineDebug::DisplayManual()
{
	std::string manual("WASD: �̵�. \n");
	manual = manual + "R: é�� ����. \n";
	manual = manual + "I: ����� �̵� 666���� ����. \n";
	manual = manual + "K: ����� ��� ���. \n";
	manual = manual + "J: ����ΰ� 0����Ÿ�Ϸ� ��� �̵�. \n";
	manual = manual + "V: Ÿ�� ���̰�/�Ⱥ��̰� �ϱ�. \n";
	manual = manual + "N: �ٷ� ���� é�ͷ� �Ѿ.";
	
	MessageBoxA(nullptr, manual.c_str(), "Manual", MB_OK | MB_ICONINFORMATION);
}
