#include "J_Input.h"
#include "J_Window.h"

J_Input* J_Input::instance_ = new J_Input();

J_Input::J_Key::J_Key()
	: isDown_(false), 
	isPressed_(false), 
	isUp_(false),
	isFree_(true),
	keyValue_(-1)
{
}

J_Input::J_Key::~J_Key()
{
}

J_Input::J_Input() : allKeys_()
{
}

J_Input::~J_Input()
{
	for (std::map<std::string, J_Key*>::iterator it = allKeys_.begin();
		it != allKeys_.end(); it++)
	{
		if (nullptr == it->second)
		{
			J_GameEngineDebug::AssertFalse();
			continue;
		}

		delete it->second;
		it->second = nullptr;
	}
	allKeys_.clear();
}

void J_Input::J_Key::Update()
{
	if (0 != GetAsyncKeyState(keyValue_))
	{
		if (false == isPressed_)
		{
			isDown_ = true;
			isPressed_ = true;
			isUp_ = false;
			isFree_ = false;
		}
		else if (true == isPressed_)
		{
			isDown_ = false;
			isPressed_ = true;
			isUp_ = false;
			isFree_ = false;
		}
	}
	else
	{
		if (true == isPressed_)
		{
			isDown_ = false;
			isPressed_ = false;
			isUp_ = true;
			isFree_ = true;
		}
		else if (false == isPressed_)
		{
			isDown_ = false;
			isPressed_ = false;
			isUp_ = false;
			isFree_ = true;
		}
	}
}

bool J_Input::CreateKey(const std::string& _name, int _keyValue)
{
	if (true == _name.empty())
	{
		J_GameEngineDebug::AssertFalse("J_Input::CreateKey()-> true == _name.empty()");
		return false;
	}

	if ('a' <= _keyValue && 'z' >= _keyValue)
	{
		_keyValue = toupper(_keyValue);
	}

	J_Key* NewKey = new J_Key();
	NewKey->SetName(_name);
	NewKey->keyValue_ = _keyValue;

	allKeys_.insert(std::map<std::string, J_Key*>::value_type(_name, NewKey));

	return true;
}

bool J_Input::CheckKeyExistence(const std::string& _name)
{
	if (nullptr == FindKey(_name))
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool J_Input::GetIsDown(const std::string& _name)
{
	J_Key* ReturnKey = FindKey(_name);

	if (nullptr == ReturnKey)
	{
		J_GameEngineDebug::AssertFalse();
		return false;
	}
	else
	{
		return ReturnKey->isDown_;
	}
}

bool J_Input::GetIsUp(const std::string& _name)
{
	J_Key* ReturnKey = FindKey(_name);

	if (nullptr == ReturnKey)
	{
		J_GameEngineDebug::AssertFalse();
		return false;
	}
	else
	{
		return ReturnKey->isUp_;
	}
}

bool J_Input::GetIsPressed(const std::string& _name)
{
	J_Key* ReturnKey = FindKey(_name);

	if (nullptr == ReturnKey)
	{
		J_GameEngineDebug::AssertFalse();
		return false;
	}
	else
	{
		return ReturnKey->isPressed_;
	}
}

bool J_Input::GetIsFree(const std::string& _name)
{
	J_Key* ReturnKey = FindKey(_name);

	if (nullptr == ReturnKey)
	{
		J_GameEngineDebug::AssertFalse();
		return false;
	}
	else
	{
		return ReturnKey->isFree_;
	}
}

void J_Input::Update()
{
	for (std::map<std::string, J_Key*>::iterator it = allKeys_.begin();
		it != allKeys_.end(); it++)
	{
		it->second->Update();
	}
}

