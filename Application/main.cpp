#include <J_Window.h> 
#include <J_Input.h>
#include <J_GameEngineDebug.h>
#include <J_GameEngineTime.h>
#include <J_LevelManager.h>
#include <J_SoundManager.h>
#include <Openning.h>
#include <Chapter0.h>
#include <Chapter1.h>
#include <Chapter2.h>
#include <Chapter3.h>
#include <Chapter4.h>
#include <Chapter5.h>
#include <Chapter6.h>
#include <Chapter7.h>
#include <Chapter8.h>
#include <Chapter9.h>
#include "AppFunctions.h"





void UpdateFunctions();

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    J_GameEngineDebug::CheckLeak();
    AppFunctions::InitializeApp();

    J_Window::GetInstance().CreateMainWindowClass(hInstance, "API_Portfolio");
    J_Window::GetInstance().CreateMainWindow("HellTaker", float4::ZERO, { 1920, 1080 });  

    J_LevelManager::GetInstance().CreateLevel<Openning>("Openning");
    J_LevelManager::GetInstance().CreateLevel<Chapter0>("Chapter0");
    J_LevelManager::GetInstance().CreateLevel<Chapter1>("Chapter1");
    J_LevelManager::GetInstance().CreateLevel<Chapter2>("Chapter2");
    J_LevelManager::GetInstance().CreateLevel<Chapter3>("Chapter3");
    J_LevelManager::GetInstance().CreateLevel<Chapter4>("Chapter4");
    J_LevelManager::GetInstance().CreateLevel<Chapter5>("Chapter5");
    J_LevelManager::GetInstance().CreateLevel<Chapter6>("Chapter6");
    J_LevelManager::GetInstance().CreateLevel<Chapter7>("Chapter7");
    J_LevelManager::GetInstance().CreateLevel<Chapter8>("Chapter8");
    J_LevelManager::GetInstance().CreateLevel<Chapter9>("Chapter9");
    
    J_LevelManager::GetInstance().ChangeCurLevel("Openning");
    //J_LevelManager::GetInstance().ChangeCurLevel("Chapter9");


    J_Window::GetInstance().Update(UpdateFunctions);

    
    AppFunctions::ReleaseApp();
}


void UpdateFunctions()
{
    J_GameEngineTime::GetInstance().UpdateDeltaTime();
    J_Input::GetInstance().Update();
    J_SoundManager::GetInstance().UpdateSound();
    J_LevelManager::GetInstance().Update();
}