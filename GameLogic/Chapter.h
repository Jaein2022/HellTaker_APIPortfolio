#pragma once
#include <J_Level.h>
#include "LogicEnum.h"

class J_SoundPlayer;
class J_ImageFile;
class Hero;
class Tile;
class Stone;
class Skeleton;
class Demon;
class Key;
class Lock;
class ChapterBG;
class Dialogue;
class Chapter: public J_Level
{
	friend Hero;


	//������ȣ ��� ����.
	int chapterNumber_;				//������ȣ. �̰ɷ� Ư�� ���� ã�ư� �� �ְ� �� ��.

	//Ÿ�� ���� ����.
	std::vector<std::vector<Tile*>> allTiles_;
	float4 goalTileIndex00_;	//�÷��̾� ��������.
	float4 goalTileIndex01_;	//�÷��̾� ��������.

	std::vector<Skeleton*> allSkeletons_;	//��� �ذ� ����.
	std::vector<Stone*> allStones_;			//��� �� ����.
	std::vector<Dialogue*> allDialogues_;

	//transition �ִϸ��̼� ���� ����.
	J_ImageFile* backBufferImage_;				//����� �̹���.
	std::vector<J_ImageFile*> transition_;		//transition �̹����� ��Ƶ� ����.
	const float transitionDelay_;			//transition �� �����Ӻ� ������.
	float curFrameDelay_;					//���� ������ ������.
	int curFrameIndex_;		//���� transition�����ӹ�ȣ. 0 <= curFrameIndex_ <= 30.
	J_SoundPlayer* transitionSound_Player1_;
	J_SoundPlayer* transitionSound_Player2_;
	float transitionSoundChangeDelay_;

	const int chapter8CamPosY_;

protected:
	Hero* hero_;
	ChapterBG* defaultBG_;
	Key* key_;
	Lock* lock_;
	Dialogue* curDialogue_;


public:
	bool isTransitionOn_;
	Tile* leftTopTile_;
	bool isInDialogue_;


public:
	Chapter();
	~Chapter();		//����Ʈ �Ҹ���.

public:
	Chapter(const Chapter& _other) = delete;		//����Ʈ ���������.
	Chapter(Chapter&& _other) = delete;		//����Ʈ rvalue ���������.

	Chapter& operator=(const Chapter& _other) = delete;		//����Ʈ ���Կ�����.
	Chapter& operator=(const Chapter&& _other) = delete;		//����Ʈ rvalue ���Կ�����.

public:
	Tile* FindTile(int _x, int _y);						//allTiles���� Ư���� Ÿ�� ã��.
	Tile* FindTile(const float4& _tilePos);		//allTiles���� Ư���� Ÿ�� ã��.
	bool IsHeroGoal();							//����ΰ� ��Ÿ�Ͽ� �����ߴ°� ���� ���Ͱ� �Ǵ�.
	float4 GetHeroCurTileIndex();
	void GiveKey();
	bool IsHeroGotKey();
	virtual void RespondSelection(int _index);


public:
	float4 GetAllTilesSize()	//allTiles ũ�� ��ȯ.
	{
		return { static_cast<int>(allTiles_[0].size()),
			static_cast<int>(allTiles_.size()) };
	}
	bool IsAllTilesEmpty()		//allTiles�� ����°�.
	{
		return allTiles_.empty();
	}
	bool IsGoal(const float4& _heroCurTileIndex)	//����ΰ� ��Ÿ�Ͽ� �����ߴ°� ����� ������ �Ǵ�.
	{
		return (goalTileIndex00_ == _heroCurTileIndex || goalTileIndex01_ == _heroCurTileIndex);
	}
	int GetChapter8CamPosY() const
	{
		return chapter8CamPosY_;
	}
	void SetIsInDialogue(bool _isInDialogue)
	{
		isInDialogue_ = _isInDialogue;
	}
	bool GetIsInDialogue()
	{
		return isInDialogue_;
	}





protected:
	//é���� ���͵� ���� �Լ���.
	void CreateTiles(const float4& _leftTopTilePos, const int _allTilesSizeX, const int _allTilesSizeY);
	void CreateHero(unsigned int _moveLimit, int _startIndexX, int _startIndexY);
	void CreateSkeleton(int _x, int _y);
	void CreateStone(int _x, int _y);
	Demon* CreateDemon(const std::string& _actorName, int _x, int _y);	//�����̸��� �ݵ�� �̹������ϸ��� Ȯ���ڸ� ������ ���·� �� ��.
	void CreateDefaultBG();
	void CreateKey(int _x, int _y);
	void CreateLock(int _x, int _y);
	void CreateDialogue(const std::string& _imageName0, const std::string& _imageName1 = "",
		const std::string& _imageName2 = "", int _buttonCount = 2, int _successOrFail = 0);
	//_buttonCount�� 2 �̻��̸� _successOrFail�� 0���� �� ��.

	void SetGoalTileIndex(const float4& _goalTileIndex0, const float4& _goalTileIndex1 = float4::ZERO);	//�÷��̾� �������� �� Ÿ�� ����.
	
	void CreateTransition();	//Ʈ������ �̹��� �غ� �� isTransition�� ������ ����.

	void ManageInput();			//Ű�� �Է� ���� �Լ�.
	void SetChapterNumber();	//�̸����� é�� ��ȣ ���� �Լ�.
	Dialogue* FindDialogue(int _index);
	void PushBackSpecialDialogue(Dialogue* _dialogue);
	void SetCurDialogue(int _index);
	void ClearChapter();
	void ChangeToNextChapter();

protected:



private:
	void SwitchThornUpDown();
	void SetIsTileVisible(bool _isTileVisible);
	void RenderTransition();
	void LevelRender() override;
	
private:


};

