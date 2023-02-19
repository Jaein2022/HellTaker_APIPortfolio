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

	J_GameEnginePath& operator=(const J_GameEnginePath& _other) = delete;		//����Ʈ ���Կ�����.
	J_GameEnginePath& operator=(const J_GameEnginePath&& _other) = delete;		//����Ʈ rvalue ���Կ�����.

public:
	bool FindParent(const std::string& _directoryName);
	//������ �̸��� ���� ���丮�� ���� ������ ���� �۾� ��ο������� ���� ���丮�� �Ž��� �ö󰡴� �Լ�. ������ false ��ȯ.

	bool FindChild(const std::string& _directoryName);		
	//�Ž��� �ö� ���丮�� �Էµ� ��θ� �ٿ� ������ �̸��� ���� ���丮�� �������� Ȯ���ϰ� �ִٸ� true, ���ٸ� false�� ��ȯ�ϴ� �Լ�.
	
	std::string CreatePath(const std::string& _fileName);
	//���� ��ο� �Է��� ��θ� �ٿ��� �ϳ��� ��η� ����� �Լ�.


private:
	std::string ExtractDirectoryName();	//path_���� ���� ���� ���丮 �̸��� �����س��� �Լ�.
	void MoveToParent();	//���� �۾� ��ο������� ���� ���丮�� �Ѵܰ辿 �Ž��� �ö󰡴� �Լ�.
	bool CheckExistence();	//path_�� �Էµ� ��ΰ� ������ �����ϴ��� Ȯ���ϴ� �Լ�.
	bool IsRoot();			//���� ��ΰ� ��Ʈ(C:\, D:\ ���� ���̻��� ���� ���丮�� ���� ���丮)�� ��������� ��ȯ�ϴ� �Լ�.
	


};

