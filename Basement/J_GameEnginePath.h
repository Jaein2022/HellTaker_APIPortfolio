#pragma once
#include <string>
#include "J_GameEngineDebug.h"


class J_GameEnginePath
{
	std::string path_;


public:
	J_GameEnginePath();		
	J_GameEnginePath(const J_GameEnginePath& _other);		
	J_GameEnginePath(const std::string& __str);
	~J_GameEnginePath();		

	J_GameEnginePath& operator=(const J_GameEnginePath& _other) = delete;		//디폴트 대입연산자.
	J_GameEnginePath& operator=(const J_GameEnginePath&& _other) = delete;		//디폴트 rvalue 대입연산자.

public:
	bool FindParent(const std::string& _directoryName);
	//지정된 이름을 가진 디렉토리가 나올 때까지 현재 작업 경로에서부터 상위 디렉토리로 거슬러 올라가는 함수. 없으면 false 반환.

	bool FindChild(const std::string& _directoryName);		
	//거슬러 올라간 디렉토리에 입력된 경로를 붙여 지정된 이름을 가진 디렉토리가 나오는지 확인하고 있다면 true, 없다면 false를 반환하는 함수.
	
	std::string CreatePath(const std::string& _fileName);
	//기존 경로에 입력한 경로를 붙여서 하나의 경로로 만드는 함수.


private:
	std::string ExtractDirectoryName();	//path_에서 가장 하위 디렉토리 이름을 추출해내는 함수.
	void MoveToParent();	//현재 작업 경로에서부터 상위 디렉토리로 한단계씩 거슬러 올라가는 함수.
	bool CheckExistence();	//path_에 입력된 경로가 실제로 존재하는지 확인하는 함수.
	bool IsRoot();			//현재 경로가 루트(C:\, D:\ 등의 더이상의 상위 디렉토리가 없는 디렉토리)인 경우인지를 반환하는 함수.
	


};

