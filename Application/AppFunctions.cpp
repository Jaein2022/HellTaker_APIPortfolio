#include "AppFunctions.h"
#include <J_GameEnginePath.h>
#include <J_ImageManager.h>
#include <J_Input.h>
#include <J_LevelManager.h>
#include <J_Window.h>
#include <J_GameEngineTime.h>
#include <J_SoundManager.h>

AppFunctions::AppFunctions()
{
}

AppFunctions::~AppFunctions()
{
}

void AppFunctions::InitializeApp()
{
	std::string directoryName("HellTaker_APIPortfolio");	//�� �̸��� ���丮�� �ڽ����� ���� �θ� ���ö����� ���� ���丮�� ã���鼭 �ö󰣴�.
	std::string imageDirectoryName("\\Images\\");			//�̹����� �ִ� ���丮 �̸��� �� ���.
	std::string soundDirectoryName("\\Sounds\\");			//�̹����� �ִ� ���丮 �̸��� �� ���.
	std::vector<std::string> allImageFileNames;					//�ҷ��� ��� �̹��� ���� �̸� ���. 
	std::vector<std::string> allSoundFileNames;					//�ҷ��� ��� ���� ���� �̸� ���. 


	//�̹������� �̸� ���.
	allImageFileNames.reserve(150);		//�ε��� ���� ���� �������� ������ �뷮 ������ ��.
	allImageFileNames.push_back("Openning.bmp");
	allImageFileNames.push_back("beel_fly.bmp");
	allImageFileNames.push_back("dialogueBG_abyss01.bmp");
	allImageFileNames.push_back("dialogueBG_abyss02.bmp");
	allImageFileNames.push_back("booper.bmp");
	allImageFileNames.push_back("success.bmp");
	allImageFileNames.push_back("button_Unselected.bmp");
	allImageFileNames.push_back("button_Selected.bmp");
	allImageFileNames.push_back("dialogueDeath0.bmp");
	allImageFileNames.push_back("dialogueDeath1.bmp");
	allImageFileNames.push_back("dialogueDeath2.bmp");
	allImageFileNames.push_back("dialogueDeath3.bmp");
	allImageFileNames.push_back("dialogueDeath4.bmp");
	allImageFileNames.push_back("dialogueDeath5.bmp");
	allImageFileNames.push_back("dialogueDeath6.bmp");
	allImageFileNames.push_back("dialogueDeath7.bmp");
	allImageFileNames.push_back("dialogueDeath8.bmp");

	allImageFileNames.push_back("transition0.bmp");
	allImageFileNames.push_back("transition1.bmp");
	allImageFileNames.push_back("transition2.bmp");
	allImageFileNames.push_back("transition3.bmp");
	allImageFileNames.push_back("transition4.bmp");
	allImageFileNames.push_back("transition5.bmp");
	allImageFileNames.push_back("transition6.bmp");
	allImageFileNames.push_back("transition7.bmp");
	allImageFileNames.push_back("transition8.bmp");
	allImageFileNames.push_back("transition9.bmp");
	allImageFileNames.push_back("transition10.bmp");
	allImageFileNames.push_back("transition11.bmp");
	allImageFileNames.push_back("transition12.bmp");
	allImageFileNames.push_back("transition13.bmp");
	allImageFileNames.push_back("transition14.bmp");
	allImageFileNames.push_back("transition15.bmp");
	allImageFileNames.push_back("transition16.bmp");
	allImageFileNames.push_back("transition17.bmp");
	allImageFileNames.push_back("transition18.bmp");
	allImageFileNames.push_back("transition19.bmp");
	allImageFileNames.push_back("transition20.bmp");
	allImageFileNames.push_back("transition21.bmp");
	allImageFileNames.push_back("transition22.bmp");
	allImageFileNames.push_back("transition23.bmp");
	allImageFileNames.push_back("transition24.bmp");
	allImageFileNames.push_back("transition25.bmp");
	allImageFileNames.push_back("transition26.bmp");
	allImageFileNames.push_back("transition27.bmp");
	allImageFileNames.push_back("transition28.bmp");
	allImageFileNames.push_back("transition29.bmp");
	allImageFileNames.push_back("transition30.bmp");

	allImageFileNames.push_back("death0.bmp");
	allImageFileNames.push_back("death1.bmp");
	allImageFileNames.push_back("death2.bmp");
	allImageFileNames.push_back("death3.bmp");
	allImageFileNames.push_back("death4.bmp");
	allImageFileNames.push_back("death5.bmp");
	allImageFileNames.push_back("death6.bmp");
	allImageFileNames.push_back("death7.bmp");
	allImageFileNames.push_back("death8.bmp");
	allImageFileNames.push_back("death9.bmp");
	allImageFileNames.push_back("death10.bmp");
	allImageFileNames.push_back("death11.bmp");
	allImageFileNames.push_back("death12.bmp");
	allImageFileNames.push_back("death13.bmp");
	allImageFileNames.push_back("death14.bmp");
	allImageFileNames.push_back("death15.bmp");
	allImageFileNames.push_back("death16.bmp");
	allImageFileNames.push_back("death17.bmp");

	allImageFileNames.push_back("100tile.bmp");
	allImageFileNames.push_back("hero.bmp");
	allImageFileNames.push_back("skeleton.bmp");

	allImageFileNames.push_back("UI_InPlay.bmp");
	allImageFileNames.push_back("JustBlackBoard.bmp");
	allImageFileNames.push_back("loveSign.bmp");
	allImageFileNames.push_back("spark.bmp");
	allImageFileNames.push_back("blood.bmp");
	allImageFileNames.push_back("dust.bmp");
	allImageFileNames.push_back("smallSpark.bmp");
	allImageFileNames.push_back("key.bmp");
	allImageFileNames.push_back("radiant.bmp");
	allImageFileNames.push_back("lockbox.bmp");
	allImageFileNames.push_back("stone0.bmp");
	allImageFileNames.push_back("stone1.bmp");
	allImageFileNames.push_back("stone2.bmp");
	allImageFileNames.push_back("stone3.bmp");
	allImageFileNames.push_back("stone4.bmp");
	allImageFileNames.push_back("stone5.bmp");
	allImageFileNames.push_back("stone6.bmp");
	allImageFileNames.push_back("stone7.bmp");
	allImageFileNames.push_back("stone8.bmp");

	allImageFileNames.push_back("chapterBG1.bmp");
	allImageFileNames.push_back("pandemonica.bmp");
	allImageFileNames.push_back("pand_idle.bmp");
	allImageFileNames.push_back("pand_flust.bmp");
	allImageFileNames.push_back("dialogueBG_hell.bmp");

	allImageFileNames.push_back("chapterBG2.bmp");
	allImageFileNames.push_back("modeus.bmp");
	allImageFileNames.push_back("mod_idle.bmp");
	allImageFileNames.push_back("mod_close.bmp");
	allImageFileNames.push_back("thorn.bmp");

	allImageFileNames.push_back("chapterBG3.bmp");
	allImageFileNames.push_back("cerberus0.bmp");
	allImageFileNames.push_back("cerberus1.bmp");
	allImageFileNames.push_back("cerberus2.bmp");
	allImageFileNames.push_back("cer_idle.bmp");
	allImageFileNames.push_back("cer_happy.bmp");

	allImageFileNames.push_back("chapterBG4.bmp");
	allImageFileNames.push_back("malina.bmp");
	allImageFileNames.push_back("mal_idle.bmp");
	allImageFileNames.push_back("mal_puzzled.bmp");

	allImageFileNames.push_back("chapterBG5.bmp");
	allImageFileNames.push_back("zdrada.bmp");
	allImageFileNames.push_back("z_idle.bmp");
	allImageFileNames.push_back("z_laugh.bmp");

	allImageFileNames.push_back("chapterBG6.bmp");
	allImageFileNames.push_back("azazel.bmp");
	allImageFileNames.push_back("az_idle.bmp");
	allImageFileNames.push_back("az_note.bmp");
	allImageFileNames.push_back("chapter6_Badend.bmp");

	allImageFileNames.push_back("chapterBG7.bmp");
	allImageFileNames.push_back("justice.bmp");
	allImageFileNames.push_back("jus_curious.bmp");
	allImageFileNames.push_back("jus_idle.bmp");

	allImageFileNames.push_back("chapterBG8.bmp");
	allImageFileNames.push_back("lucifer.bmp");
	allImageFileNames.push_back("LH_angry.bmp");
	allImageFileNames.push_back("LH_face.bmp");
	allImageFileNames.push_back("LH_happy.bmp");
	allImageFileNames.push_back("LH_idle.bmp");
	allImageFileNames.push_back("LH_swirl.bmp");
	allImageFileNames.push_back("man_skele.bmp");
	allImageFileNames.push_back("dialogueBG_throne2.bmp");


	allImageFileNames.push_back("chapterBG9.bmp");
	allImageFileNames.push_back("epilogue.bmp");
	allImageFileNames.push_back("ending.bmp");


	//�������� �̸� ���.
	allSoundFileNames.reserve(50);
	allSoundFileNames.push_back("Vitality.wav");
	allSoundFileNames.push_back("Apropos.wav");
	allSoundFileNames.push_back("character_move_01.wav");
	allSoundFileNames.push_back("door_opening_01.wav");			//�ڹ��� ������ �Ҹ�.
	allSoundFileNames.push_back("door_closed_kick_01.wav");		//��� �ڹ��� ���� �Ҹ�.
	allSoundFileNames.push_back("door_closed_kick_02.wav");		//��� �ڹ��� ���� �Ҹ�.
	allSoundFileNames.push_back("door_closed_kick_03.wav");		//��� �ڹ��� ���� �Ҹ�.
	allSoundFileNames.push_back("enemy_die_01.wav");
	allSoundFileNames.push_back("enemy_die_02.wav");
	allSoundFileNames.push_back("enemy_die_03.wav");
	allSoundFileNames.push_back("enemy_kick_01.wav");
	allSoundFileNames.push_back("enemy_kick_02.wav");
	allSoundFileNames.push_back("enemy_kick_03.wav");
	allSoundFileNames.push_back("key_pick_up_01.wav");
	allSoundFileNames.push_back("Luminescent.wav");
	allSoundFileNames.push_back("player_death_01.wav");
	allSoundFileNames.push_back("screen_changer_part1_01.wav");				//transition ȿ����1.
	allSoundFileNames.push_back("screen_changer_part2_01.wav");				//transition ȿ����2.
	allSoundFileNames.push_back("spikes_damage_01.wav");
	allSoundFileNames.push_back("spikes_damage_02.wav");
	allSoundFileNames.push_back("stone_kick_01.wav");
	allSoundFileNames.push_back("stone_kick_02.wav");
	allSoundFileNames.push_back("stone_kick_03.wav");
	allSoundFileNames.push_back("stone_move_01.wav");
	allSoundFileNames.push_back("stone_move_02.wav");
	allSoundFileNames.push_back("stone_move_03.wav");
	allSoundFileNames.push_back("dialogue_start_01.wav");
	allSoundFileNames.push_back("dialogue_success_01.wav");
	allSoundFileNames.push_back("succub_capture_01.wav");
	allSoundFileNames.push_back("bad_end_screen_01.wav");
	allSoundFileNames.push_back("button_dialogue_confirm_01.wav");
	allSoundFileNames.push_back("button_dialogue_highlight_01.wav");
	allSoundFileNames.push_back("dialogue_text_end_01.wav");



	J_GameEnginePath curPath = J_GameEnginePath();
	curPath.FindParent(directoryName);
	if (false == curPath.FindChild(imageDirectoryName))
	{
		J_GameEngineDebug::AssertFalse("curPath is wrong path.");
		return;
	}

	for (size_t i = 0; i < allImageFileNames.size(); i++)
	{
		if (nullptr != J_ImageManager::GetInstance().FindImage(allImageFileNames.at(i)))
		{
			continue;
		}
		J_ImageManager::GetInstance().LoadInGameImage(allImageFileNames.at(i), curPath.CreatePath(allImageFileNames.at(i)));
	}

	J_SoundManager::GetInstance().InitSoundSystem();
	curPath.FindParent(directoryName);
	if (false == curPath.FindChild(soundDirectoryName))
	{
		J_GameEngineDebug::AssertFalse("curPath is wrong path.");
		return;
	}
	for (size_t i = 0; i < allSoundFileNames.size(); i++)
	{
		if (nullptr != J_SoundManager::GetInstance().FindSound(allSoundFileNames.at(i)))
		{
			continue;
		}
		J_SoundManager::GetInstance().LoadIngameSound(allSoundFileNames.at(i), curPath.CreatePath(allSoundFileNames.at(i)));
	}


	//�⺻ �÷��� Ű.
	J_Input::GetInstance().CreateKey("A", 'A');	//��.
	J_Input::GetInstance().CreateKey("D", 'D');	//��.
	J_Input::GetInstance().CreateKey("W", 'W');	//��.
	J_Input::GetInstance().CreateKey("S", 'S');	//��.
	J_Input::GetInstance().CreateKey("Space", ' ');	//����.

	//����� Ű.
	J_Input::GetInstance().CreateKey("N", 'N');	//���� ������ �̵�.
	J_Input::GetInstance().CreateKey("V", 'V');	//Ÿ�� ���̰�/�Ⱥ��̰�
	J_Input::GetInstance().CreateKey("R", 'R');	//���� ����.
	J_Input::GetInstance().CreateKey("K", 'K');	//����� ��� ���.
	J_Input::GetInstance().CreateKey("I", 'I');	//����� �̵�Ƚ�� 666.
	J_Input::GetInstance().CreateKey("M", 'M');	//�Ŵ��� ����.

	J_Input::GetInstance().CreateKey("T", 'T');	//��ȭâ.
}

void AppFunctions::ReleaseApp()
{
	//level1
	J_Input::GetInstance().DestroyInstance();
	J_LevelManager::GetInstance().DestroyInstance();
	J_ImageManager::GetInstance().DestroyInstance();
	J_Window::GetInstance().DestroyInstance();
	//level0
	J_SoundManager::GetInstance().DestroyInstance();
	J_GameEngineTime::GetInstance().DestroyInstance();
}
