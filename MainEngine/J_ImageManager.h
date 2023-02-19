#pragma once
#include <windows.h>
#include <string>
#include <map>
#include <J_GameEngineDebug.h>

class J_ImageFile;
class J_Window;
class J_LevelManager;
class J_ImageManager
{
	friend J_Window;
	friend J_LevelManager;

	static J_ImageManager* instance_;	

	std::map<std::string, J_ImageFile*> allImages_;		//모든 불러온 이미지들.
	J_ImageFile* curWindowImage_;						//현재 윈도우 이미지.
	J_ImageFile* backBufferImage_;						//대기중인 백버퍼 이미지.
	

private:
	J_ImageManager();		//디폴트 생성자.
	~J_ImageManager();		//디폴트 소멸자.

public:
	J_ImageManager(const J_ImageManager& _other) = delete;		//디폴트 복사생성자.
	J_ImageManager(J_ImageManager&& _other) = delete;		

	J_ImageManager& operator=(const J_ImageManager& _other) = delete;		//디폴트 대입연산자.
	J_ImageManager& operator=(const J_ImageManager&& _other) = delete;		//디폴트 rvalue 대입연산자.

public:
	J_ImageFile* FindImage(const std::string& _name);
	void LoadInGameImage(const std::string& _name, const std::string& _path);	//지정된 경로에서 bmp이미지를 불러와 allImages_에 넣는다.

public:
	J_ImageFile* GetBackBufferImage() const
	{
		return backBufferImage_;
	}

	static J_ImageManager& GetInstance()
	{
		return *instance_;
	}

	static void DestroyInstance()
	{
		if (nullptr == instance_)
		{
			J_GameEngineDebug::AssertFalse();
			return;
		}
		else
		{
			delete instance_;
			instance_ = nullptr;
		}
	}

private:


	void InitializeWindow(const HDC& _windowHDC);		//최초 시작할때 윈도우의 DC를 받아서 이미지를 하나 만든다.
	void ChangeToBackBufferImage();						//완성된 backBufferImage_의 이미지를 windowImage_로 넘기는 함수. 

};

