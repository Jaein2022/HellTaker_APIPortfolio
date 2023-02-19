#include "J_ImageManager.h"
#include "J_ImageFile.h"
#include "J_Window.h"

J_ImageManager* J_ImageManager::instance_ = new J_ImageManager();

J_ImageManager::J_ImageManager() : allImages_(), curWindowImage_(nullptr), backBufferImage_(nullptr)
{
}

J_ImageManager::~J_ImageManager()
{
	for (std::map<std::string, J_ImageFile*>::iterator it = allImages_.begin(); it != allImages_.end(); it++)
	{
		if (nullptr == it->second)
		{
			J_GameEngineDebug::AssertFalse();
		}
		else
		{
			delete it->second;
			it->second = nullptr;
		}
	}
	allImages_.clear();

	if (nullptr == curWindowImage_)
	{
		J_GameEngineDebug::AssertFalse();
		return;
	}

	if (nullptr == backBufferImage_)
	{
		J_GameEngineDebug::AssertFalse();
		return;
	}

	delete curWindowImage_;
	delete backBufferImage_;
	curWindowImage_ = nullptr;
	backBufferImage_ = nullptr;
}

J_ImageFile* J_ImageManager::FindImage(const std::string& _name)
{
	std::map<std::string, J_ImageFile*>::iterator it = allImages_.find(_name);
	if (allImages_.end() == it)
	{
		return nullptr;
	}
	else
	{
		return it->second;
	}
}

void J_ImageManager::LoadInGameImage(const std::string& _name, const std::string& _path)
{
	if (nullptr != FindImage(_name))
	{
		J_GameEngineDebug::AssertFalse("J_ImageManager::LoadInGameImage()-> nullptr != FindImage(_name)");
		return;
	}

	J_ImageFile* NewImage = new J_ImageFile();
	if (false == NewImage->LoadBMPImage(_path))
	{
		delete NewImage;
		J_GameEngineDebug::AssertFalse("J_ImageManager::LoadInGameImage()-> false == NewImage->LoadBMPImage(_path)");
		return;
	}

	NewImage->SetName(_name);
	allImages_.insert(std::map<std::string, J_ImageFile*>::value_type(_name, NewImage));

	return;
}

void J_ImageManager::InitializeWindow(const HDC& _windowHDC)
{
	if (nullptr == _windowHDC)
	{
		J_GameEngineDebug::AssertFalse("J_ImageManager::InitializeWindow()-> nullptr == _windowHDC");
		return;
	}

	backBufferImage_ = new J_ImageFile();
	backBufferImage_->CreateBackBufferImage(_windowHDC, J_Window::GetInstance().GetWindowSize());

	curWindowImage_ = new J_ImageFile();
	curWindowImage_->CreateCurWindowImage(_windowHDC);
}

void J_ImageManager::ChangeToBackBufferImage()
{
	curWindowImage_->Bitcopy(backBufferImage_, J_Window::GetInstance().GetWindowSize());
}
