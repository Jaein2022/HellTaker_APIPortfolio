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

	std::map<std::string, J_ImageFile*> allImages_;		//��� �ҷ��� �̹�����.
	J_ImageFile* curWindowImage_;						//���� ������ �̹���.
	J_ImageFile* backBufferImage_;						//������� ����� �̹���.
	

private:
	J_ImageManager();		//����Ʈ ������.
	~J_ImageManager();		//����Ʈ �Ҹ���.

public:
	J_ImageManager(const J_ImageManager& _other) = delete;		//����Ʈ ���������.
	J_ImageManager(J_ImageManager&& _other) = delete;		

	J_ImageManager& operator=(const J_ImageManager& _other) = delete;		//����Ʈ ���Կ�����.
	J_ImageManager& operator=(const J_ImageManager&& _other) = delete;		//����Ʈ rvalue ���Կ�����.

public:
	J_ImageFile* FindImage(const std::string& _name);
	void LoadInGameImage(const std::string& _name, const std::string& _path);	//������ ��ο��� bmp�̹����� �ҷ��� allImages_�� �ִ´�.

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


	void InitializeWindow(const HDC& _windowHDC);		//���� �����Ҷ� �������� DC�� �޾Ƽ� �̹����� �ϳ� �����.
	void ChangeToBackBufferImage();						//�ϼ��� backBufferImage_�� �̹����� windowImage_�� �ѱ�� �Լ�. 

};

