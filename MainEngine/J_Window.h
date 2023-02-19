#pragma once
#include <Windows.h>
#include <string>
#include <J_GameEngineDebug.h>
#include <J_GameEngineMath.h>

class J_Window
{
	static J_Window* instance_;

	HINSTANCE hInstance_;
	HWND hWnd_;
	std::string windowClassName_;
	std::string windowTitle_;
	float4 windowPos_;
	float4 windowSize_;


private:
	// 윈도우를 아무나 생성할수 없게 하기 위해 기본생성자를 private으로 막는다.
	J_Window();			//디폴트 생성자.
	~J_Window();		//디폴트 소멸자.

public:
	J_Window(const J_Window& _other) = delete;		//디폴트 복사생성자.
	J_Window(J_Window&& _other) = delete;		//디폴트 rvalue 복사생성자.

	J_Window& operator=(const J_Window& _other) = delete;		//디폴트 대입연산자.
	J_Window& operator=(const J_Window&& _other) = delete;		//디폴트 rvalue 대입연산자.

public:
	void CreateMainWindowClass(HINSTANCE _hInstance, const std::string& _windowClassName);
	void CreateMainWindow(const std::string& _windowTitle, const float4& _windowPos, const float4& _windowSize);
	void SetWindowPosAndSize(const float4& _windowPos, const float4& _windowSize);
	void Update(void (*UpdateFunctions)());
	void TurnOff();

	static J_Window& GetInstance()
	{
		return *instance_;
	}

	float4 GetWindowPos()
	{
		return windowPos_;
	}

	float4 GetWindowSize()
	{
		return windowSize_;
	}

	static void DestroyInstance()
	{
		if (nullptr == instance_)
		{
			assert(false && "J_Window::DestroyInstance()->nullptr == instance_");
		}
		delete instance_;
		instance_ = nullptr;
	}

	
};
