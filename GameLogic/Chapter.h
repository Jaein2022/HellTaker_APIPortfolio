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


	//레벨번호 출력 변수.
	int chapterNumber_;				//레벨번호. 이걸로 특정 레벨 찾아갈 수 있게 할 것.

	//타일 관련 변수.
	std::vector<std::vector<Tile*>> allTiles_;
	float4 goalTileIndex00_;	//플레이어 도착지점.
	float4 goalTileIndex01_;	//플레이어 도착지점.

	std::vector<Skeleton*> allSkeletons_;	//모든 해골 모음.
	std::vector<Stone*> allStones_;			//모든 돌 모음.
	std::vector<Dialogue*> allDialogues_;

	//transition 애니메이션 관련 변수.
	J_ImageFile* backBufferImage_;				//백버퍼 이미지.
	std::vector<J_ImageFile*> transition_;		//transition 이미지를 모아둔 벡터.
	const float transitionDelay_;			//transition 각 프레임별 딜레이.
	float curFrameDelay_;					//현재 프레임 딜레이.
	int curFrameIndex_;		//현재 transition프레임번호. 0 <= curFrameIndex_ <= 30.
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
	~Chapter();		//디폴트 소멸자.

public:
	Chapter(const Chapter& _other) = delete;		//디폴트 복사생성자.
	Chapter(Chapter&& _other) = delete;		//디폴트 rvalue 복사생성자.

	Chapter& operator=(const Chapter& _other) = delete;		//디폴트 대입연산자.
	Chapter& operator=(const Chapter&& _other) = delete;		//디폴트 rvalue 대입연산자.

public:
	Tile* FindTile(int _x, int _y);						//allTiles에서 특정한 타일 찾기.
	Tile* FindTile(const float4& _tilePos);		//allTiles에서 특정한 타일 찾기.
	bool IsHeroGoal();							//히어로가 골타일에 도착했는가 데몬 액터가 판단.
	float4 GetHeroCurTileIndex();
	void GiveKey();
	bool IsHeroGotKey();
	virtual void RespondSelection(int _index);


public:
	float4 GetAllTilesSize()	//allTiles 크기 반환.
	{
		return { static_cast<int>(allTiles_[0].size()),
			static_cast<int>(allTiles_.size()) };
	}
	bool IsAllTilesEmpty()		//allTiles가 비었는가.
	{
		return allTiles_.empty();
	}
	bool IsGoal(const float4& _heroCurTileIndex)	//히어로가 골타일에 도착했는가 히어로 스스로 판단.
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
	//챕터의 액터들 생성 함수들.
	void CreateTiles(const float4& _leftTopTilePos, const int _allTilesSizeX, const int _allTilesSizeY);
	void CreateHero(unsigned int _moveLimit, int _startIndexX, int _startIndexY);
	void CreateSkeleton(int _x, int _y);
	void CreateStone(int _x, int _y);
	Demon* CreateDemon(const std::string& _actorName, int _x, int _y);	//액터이름을 반드시 이미지파일명에서 확장자만 제거한 형태로 줄 것.
	void CreateDefaultBG();
	void CreateKey(int _x, int _y);
	void CreateLock(int _x, int _y);
	void CreateDialogue(const std::string& _imageName0, const std::string& _imageName1 = "",
		const std::string& _imageName2 = "", int _buttonCount = 2, int _successOrFail = 0);
	//_buttonCount가 2 이상이면 _successOrFail은 0으로 할 것.

	void SetGoalTileIndex(const float4& _goalTileIndex0, const float4& _goalTileIndex1 = float4::ZERO);	//플레이어 도착점이 될 타일 지정.
	
	void CreateTransition();	//트랜지션 이미지 준비 및 isTransition을 참으로 설정.

	void ManageInput();			//키와 입력 관리 함수.
	void SetChapterNumber();	//이름에서 챕터 번호 얻어내는 함수.
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

