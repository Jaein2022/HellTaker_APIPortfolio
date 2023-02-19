#include "J_GameEnginePath.h"
#include <Windows.h>
#include <io.h>

//���ã�� ��� �ٲٱ�. 

J_GameEnginePath::J_GameEnginePath(): path_(MAX_PATH, '\0')
{
	//MAX_PATH: ��������� �����ϴ� ��� �ִ� ���ڼ� 260�� #define. windows.h�� �̹� ����Ǿ� �ִ�.

	size_t pathSize = static_cast<size_t>(GetCurrentDirectoryA(MAX_PATH, &(path_[0])));
	//������ ���ÿ� ���� �۾� ��θ� path_�� �����Ѵ�.

	if (0 == pathSize)	//���� �۾� ��θ� ��µ� �����ߴٸ� ����.
	{
		J_GameEngineDebug::AssertFalse("J_GameEnginePath::J_GameEnginePath()-> 0 == GetCurrentDirectoryA()");
		return;
	}
	else
	{
		path_[pathSize] = '\\';		//���� �۾���ο� '\\'�� �߰��ϰ� �ʿ���� �޺κ��� �߶󳽴�.
		path_ = path_.substr(0, pathSize + 1);
	}
}

J_GameEnginePath::J_GameEnginePath(const J_GameEnginePath& _other): path_(_other.path_)
{
}

J_GameEnginePath::J_GameEnginePath(const std::string& _str): path_(_str)
{
}

J_GameEnginePath::~J_GameEnginePath()
{
	path_.clear();
}

bool J_GameEnginePath::FindParent(const std::string& _directoryName)
{

	J_GameEnginePath tempCurPath = *this;

	do
	{
		tempCurPath.MoveToParent();
		if (-1 != _access((tempCurPath.path_ + _directoryName + "\\").c_str(), 0))
		{
			path_ = tempCurPath.path_ + _directoryName + "\\";
			return true;
		}
		
	} while (false == tempCurPath.IsRoot());	//��Ʈ��� Ż��

	J_GameEngineDebug::AssertFalse();
	return false;
}

bool J_GameEnginePath::FindChild(const std::string& _path)
{
	if (true == _path.empty())
	{
		J_GameEngineDebug::AssertFalse("J_GameEnginePath::FindChild()-> true == _directoryName.empty()");
		return false;
	}

	J_GameEnginePath tempPath = J_GameEnginePath(_path);
	if ('\\' == tempPath.path_.front())
	{
		tempPath.path_ = tempPath.path_.substr(1, tempPath.path_.size() - 1);
	}
	if ('\\' == tempPath.path_.back())
	{
		tempPath.path_.pop_back();
	}

	this->path_ += tempPath.path_ + "\\";

	if (false == this->CheckExistence())
	{
		J_GameEngineDebug::AssertFalse();
		return false;
	}
	else
	{
		return true;
	}
}

std::string J_GameEnginePath::CreatePath(const std::string& _fileName)
{
//C:\Users\J\Desktop\AR38\API\Student\Resources\Lee_Jaein\Texture2D_bmp
	J_GameEnginePath ReturnValue = J_GameEnginePath(this->path_ + _fileName);
	if (false == ReturnValue.CheckExistence())
	{
		J_GameEngineDebug::AssertFalse();
		ReturnValue.path_.clear();
		return ReturnValue.path_;
	}
	return ReturnValue.path_;
}

std::string J_GameEnginePath::ExtractDirectoryName()
{
	size_t nameStartIndex = path_.rfind('\\', path_.size() - 2);
	if (std::string::npos == nameStartIndex)	//'\\'�� ���ٸ� ��ΰ� �߸��� ���̹Ƿ� ����.
	{
		J_GameEngineDebug::AssertFalse();

		return "";
	}
	std::string directoryName = path_.substr(nameStartIndex + 1, path_.size() - nameStartIndex - 2);

	return directoryName;
}

void J_GameEnginePath::MoveToParent()
{
	size_t nameStartIndex = path_.rfind('\\', path_.size() - 2);
	if (std::string::npos == nameStartIndex)	//'\\'�� ���ٸ� ��ΰ� �߸��� ���̹Ƿ� ����.
	{
		J_GameEngineDebug::AssertFalse();
		return;
	}
	path_ = path_.substr(0, ++nameStartIndex);	//
}

bool J_GameEnginePath::CheckExistence()
{
	if (-1 == _access(path_.c_str(), 0))
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool J_GameEnginePath::IsRoot()
{
	int distanceToRoot = 0;
	for (size_t i = 0; i < path_.length(); i++)
	{
		if ('\\' == path_[i])
		{
			++distanceToRoot;
		}
	}

	if (1 >= distanceToRoot)
	{
		return true;
	}
	else
	{
		return false;
	}
}
