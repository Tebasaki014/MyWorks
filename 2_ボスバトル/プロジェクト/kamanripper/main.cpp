const char TITLE[] = "01_Step1";

#include<string>
#include "DxLib.h"
#include "Player.h"
#include "Boss.h"
#include "Window.h"
#include "Bullet.h"
#include "BossBullet.h"
#include "Dice.h"
#include "CheckHitSquare.h"
#include "Thunder.h"
int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
)
{
	Window window;

	//�E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(FALSE);//FAlSE�őS���
	const int WIN_WIDTH =window.windowWidth();
	const int WIN_HEIGHT = window.windowHight();

	//�E�B���h�E�T�C�Y���蓮�ł͕ύX�ł����A
	//���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���



	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	//�ő�T�C�Y
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);
	//��ʃT�C�Y
	SetWindowSizeExtendRate(1.0);
	//�w�i�F
	SetBackgroundColor(0, 0, 0);
	//Dx���C�u������������

	if (DxLib_Init() == -1)//�|�P�̓G���[
	{
		//�G���[���o����}�C�i�X�l��Ԃ��ďI��
		return -1;
	}

	//�_�u���o�b�t�@�̃A��
	SetDrawScreen(DX_SCREEN_BACK);

	//�t�B�[���h
	int white = GetColor(255, 255, 255);
	int chage;
	int bossAct;
	int actintr;
	int shotWait;
	int dadgewait;
	int overwait;
	int thtimer;

	int bossHP;

	int titleg = LoadGraph("Resources/title.jpg");
	int overg = LoadGraph("Resources/gover.jpg");
	int clear = LoadGraph("Resources/execution.png");
	int ryuma = LoadGraph("Resources/ryuma.mp4");
	int pan = LoadSoundMem("Resources/pan.wav");
	int ban = LoadSoundMem("Resources/ban.wav");
	int nnyapi = LoadSoundMem("Resources/nnyapi.wav");
	int warai = LoadSoundMem("Resources/warai.wav");

	bool ovrgfl = false;

	char keys[256], prev[256];

	enum GameState {
		Title,
		Play,
		Over,
		Clear,
	};
	enum PlayerState {
		Normal,
		Dadge,
		Shot,
	};
	enum BossState {
		Interval,
		Move,
		Move2,
		Gun,
		Thu,
	};

	GameState gsta;
	PlayerState psta;
	BossState bsta;

	Player player;
	Boss boss;
	Bullet bullet;
	BossBullet bblt;
	Dice dice;
	CheckHitSquare hit;
	Thunder thunder;

	chage = 0;
	bossAct = 0;
	actintr = 0;
	shotWait = 0;
	dadgewait = 0;
	thtimer = 0;

	bossHP = 100;
	
	//Initialize

	gsta = GameState::Title;
	psta = PlayerState::Normal;
	bsta = BossState::Interval;

	PlayMusic("Resources/title.mp3", DX_PLAYTYPE_BACK);
	while (1)//�Q�[�����[�v�X�^�[�g
	{
		ClearDrawScreen();
		//Update
		for (int i = 0; i < 256; i++) {
			prev[i] = keys[i];
		}
		////�g���K�[
		//GetHitKeyStateAll(keys);
		//if (keys[KEY_INPUT_SPACE] == 1 && prev[KEY_INPUT_SPACE] == 0) {
		//	
		//}
		if (gsta == GameState::Title) {

			//DrawString(30, 50, "Press Space key", white);
			DrawExtendGraph(0, 0, window.windowWidth(), window.windowHight(), titleg, 0);

			GetHitKeyStateAll(keys);
			if (keys[KEY_INPUT_SPACE] == 1 && prev[KEY_INPUT_SPACE] == 0) {
				gsta = GameState::Play;
				StopMusic();
				PlayMusic("Resources/artcorej.mp3", DX_PLAYTYPE_BACK);
			}
		}

		

		if (gsta == GameState::Play) {

			if (bsta == BossState::Interval) {
				boss.Update();
				if (GetNowCount() - actintr > 800) {
					bossAct = GetRand(3) + 1;

					if (bossAct == 1) {
						bsta = BossState::Move;
						boss.Boost();
						PlaySoundMem(nnyapi, DX_PLAYTYPE_BACK, 1);
					}
					if (bossAct == 2) {
						bsta = BossState::Gun;
						PlaySoundMem(ban, DX_PLAYTYPE_BACK, 1);
						shotWait = GetNowCount();
						bblt.Direc();
					}
					if (bossAct == 3) {
						bsta = BossState::Gun;
						shotWait = GetNowCount();
						PlaySoundMem(ban, DX_PLAYTYPE_BACK, 1);
						bblt.Direc();
					}
					if (bossAct == 4) {
						bsta = BossState::Gun;
						shotWait = GetNowCount();
						PlaySoundMem(ban, DX_PLAYTYPE_BACK, 1);
						bblt.Direc();
						/*bsta = BossState::Thu;
						thtimer = GetNowCount();
						thunder.Start();*/
					}
					/*if (bossAct == 5) {
						bsta = BossState::Move2;
						boss.Boost();
					}*/
				}
			}

			if (bsta == BossState::Move) {
				boss.Update();
				boss.Move();

				if (boss.BossPositionY() >= 479) {
					PlaySoundMem(warai, DX_PLAYTYPE_BACK, 1);
					bsta = BossState::Interval;
					bossAct = 0;
					actintr = GetNowCount();
				}
			}

			/*if (bsta == BossState::Move2) {
				boss.Update();
				boss.Move2();

				if (boss.BossPositionY() >= 479) {

					bsta = BossState::Interval;
					bossAct = 0;
					actintr = GetNowCount();
				}
			}*/

			if (bsta == BossState::Gun) {
				bblt.Update();
				boss.Update();

				if (GetNowCount() - shotWait > 1050) {
					bsta = BossState::Interval;
				}
			}

			if (bsta == BossState::Thu) {
				boss.Update();
				thunder.Early();

				if (GetNowCount() - thtimer > 2000) {
					thunder.Main();
				}

				if (GetNowCount() - thtimer > 4000) {
					bsta = BossState::Interval;
					thunder.End();
				}

			}

			if (psta == PlayerState::Normal) {
				player.Update();
				player.Bunshin();

				//�W�����v�o����Ƃ��ɃX�y�[�X�ŃW�����v
				if (player.Jflag()) {
					GetHitKeyStateAll(keys);
					if (keys[KEY_INPUT_SPACE] == 1 && prev[KEY_INPUT_SPACE] == 0) {
						player.Jump();
					}
				}

				//L�L�[�ŉ�����[�V����
				GetHitKeyStateAll(keys);
				if (keys[KEY_INPUT_L] == 1 && prev[KEY_INPUT_L] == 0 &&
					hit.result(player.PLayerJDX(), player.PlayerJDY(),
						player.PlayerJDX2(), player.PlayerJDY2(),
						bblt.JDX1(), bblt.JDY1(), bblt.JDX2(), bblt.JDY2())) {

					psta = PlayerState::Dadge;
					player.Dodge();
					dadgewait = GetNowCount();
				}

				//K�L�[�Ń`���[�W�J�n
				if (CheckHitKey(KEY_INPUT_K) == 1) {
					if (chage <= 100) {
						chage += 4;
					}
				}

				if (CheckHitKey(KEY_INPUT_K) == 0) {
					if (chage > 0) {
						chage -= 4;
					}
				}

				//�`���[�W100%����K�L�[�𗣂��Ďˌ����[�V����
				if (CheckHitKey(KEY_INPUT_K) == 0 && chage >= 100) {
					psta = PlayerState::Shot;
					PlaySoundMem(pan, DX_PLAYTYPE_BACK, 1);
					bullet.Direc();
					player.Sstart();
					chage = 0;
				}

				if (hit.result(player.PlayerPosX(), player.PlayerPosY(),
					player.PlayerPosX2(), player.PlayerPosY2(),
					bblt.HX1(), bblt.HY1(), bblt.HX2(), bblt.HY2())) {
					//PlayMovie("ryuma.avi", 1, DX_MOVIEPLAYTYPE_NORMAL);
					PlayMusic("Resources/over.mp3", DX_PLAYTYPE_BACK);
					gsta = GameState::Over;
					overwait = GetNowCount();
				}

				if (hit.result(player.PlayerPosX(), player.PlayerPosY(),
					player.PlayerPosX2(), player.PlayerPosY2(),
					boss.BossPositionX(), boss.BossPositionY(),
					boss.BossPositionX() + boss.BossWidh() , boss.BossPositionY() + boss.BossHight())) {
					PlayMusic("Resources/over.mp3", DX_PLAYTYPE_BACK);
					gsta = GameState::Over;
					overwait = GetNowCount();
				}
			}

			//������[�V����
			if (psta == PlayerState::Dadge) {
				player.Bunshin();

				if (GetNowCount() - dadgewait > 500) {
					psta = PlayerState::Normal;
				}
			}

			//�ˌ����[�V����
			if (psta == PlayerState::Shot) {
				bullet.Update();
				player.Shot();
				player.Update();
				player.Bunshin();

				if (hit.result(bullet.BulletX1(), bullet.BulletY1(),
					bullet.BulletX2(), bullet.BulletY2(),
					boss.BossPositionX(), boss.BossPositionY(),
					boss.BossPositionX() + boss.BossWidh(), boss.BossPositionY() + boss.BossSenter())) {

					bossHP -= 2;
				}

				if (bossHP <= 0) {
					gsta = GameState::Clear;
					StopMusic();
					PlayMusic("Resources/hakusyu.mp3", DX_PLAYTYPE_BACK);
				}

				if (player.Sflag()) {
					psta = PlayerState::Normal;
				}
			}
		}

		player.Draw();

		if (gsta == GameState::Clear) {
			player.Bunshin();

			DrawExtendGraph(0, 0, window.windowWidth(), window.windowHight(), clear, 0);

			if (CheckHitKey(KEY_INPUT_R)) {
				gsta = GameState::Title;
				bsta = BossState::Interval;
				psta = PlayerState::Normal;
				bblt.out();
				player.Initialize();
				boss.Initialize();
				shotWait = 2000;
				bossHP = 100;
				StopMusic();
				PlayMusic("Resources/title.mp3", DX_PLAYTYPE_BACK);
			}
		}

		if (gsta == GameState::Over) {
			player.Bunshin();

			if (GetNowCount() - overwait > 750) {
				DrawExtendGraph(0, 0, window.windowWidth(), window.windowHight(), overg, 0);
			}

			if (CheckHitKey(KEY_INPUT_R)) {
				gsta = GameState::Title;
				bsta = BossState::Interval;
				psta = PlayerState::Normal;
				bblt.out();
				boss.Initialize();
				player.Initialize();
				shotWait = 2000;
				bossHP = 100;
				StopMusic();
				PlayMusic("Resources/title.mp3", DX_PLAYTYPE_BACK);
			}

			/*if (CheckHitKeyAll()) {
				gsta = GameState::Title;
				bsta = BossState::Interval;
				psta = PlayerState::Normal;
				bblt.out();
				shotWait = 2000;
				player.Initialize();
			}*/
		}


		
		if (gsta == GameState::Play) {
			DrawBox(600, 10, 1600, 40, white, 0);
			DrawBox(600, 10, bossHP * 10 + 600, 40, white, 1);

			DrawBox(10, 10, 100 * 2 + 10, 40, white, 0);
			DrawBox(10, 10, chage * 2 + 10, 40, white, 1);
			if (chage >= 100) {
				DrawString(30, 50, "Rady", white);
			}
			DrawString(550, 15, "Teki", white);
		}

		ScreenFlip();

		WaitTimer(20);
		if (ProcessMessage() == -1)//WindowsAPI�̃G���[���m
			break;
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)//F12
			break;

	}//�I���

	//Dx���C�u�����I������
	DxLib_End();
	return 0;
}