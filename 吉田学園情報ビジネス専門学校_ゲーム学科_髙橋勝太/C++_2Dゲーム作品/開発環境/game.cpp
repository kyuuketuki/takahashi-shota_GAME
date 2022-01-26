//=============================================================================
//
// �Q�[����ʏ��� [game.cpp]
// Author : takahashi shota
//
//=============================================================================

//=============================================================================
// �C���N���[�h�ǂݍ���
//=============================================================================
#include "game.h"
#include "bg.h"
#include "player.h"
#include "score.h"
#include "enemy.h"
#include "polygon.h"
#include "life.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "item.h"
#include "fade.h"
#include "logo.h"
#include "object3D.h"

//�}�N����`	
#define WAVE_1		(3)		//�G�̏o���^�C��
#define WAVE_2		(12)	//�G�̏o���^�C��
#define WAVE_3		(33)	//�G�̏o���^�C��
#define WAVE_4		(50)	//�G�̏o���^�C��

//����
int nTimeGame = 0;
int nTimeCounter = 0;

//�G��|������
int g_nDaed = 0;		//�ۑ��p
bool g_bDead = false;	//����p

//��ʑJ�ڗp
bool g_bMigrate = false;	

//���S�t���O�����p
bool g_bDeathFlagGame = false;

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CGame::CGame()
{
	//������
	nTimeGame = 0;					//����
	nTimeCounter = 0;				//���ԃJ�E���^�[

	g_bMigrate = false;				//��ʑJ�ڗp
	g_bDeathFlagGame = false;		//���S�t���O�����p
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CGame::~CGame()
{

}

//==============================================================================
// ����������
//==============================================================================
HRESULT CGame::Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�T�E���h���擾
	CSound *pSound;
	pSound = CManager::GetSound();

	//�T�E���hBGM
	pSound->Play(CSound::SOUND_LABEL_BGM003);

	// �t�H���g�I�u�W�F�N�g�̐���
	D3DXCreateFont(pDevice, 36, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pTimeFontGame);

	//���݂̃X�e�[�W��Manaager�ɋL��������
	CManager::SetGameStage(1);

	//�N���A����������
	CManager::SetEnemyDead(0);

	//����U�����I�t�ɂ���
	CEnemy::NextAttack(0);

	//�v���C���[�̐���
	CPlayer::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), MAX_LIFE, PLAYER_SIZE, PLAYER_SIZE);

	//�w�i��\��
	CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	//HP�o�[
	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		CLife::Create(D3DXVECTOR3(40.0f + (80.0f * nCnt), 100.0f, 0.0f), 30.0f, 30.0f);
	}

	//�X�R�A
	CScore::Create(D3DXVECTOR3(1800.0f, 50.0f, 0.0f), 100.0f, 100.0f);

	//�I�u�W�F�N�g�̐���
	CObject3D::Create(D3DXVECTOR3(60, 80.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(-0.005f, -0.05f, 0.0f), 0);

	return S_OK;
}

//==============================================================================
// �I������
//==============================================================================
void CGame::Uninit(void)
{
	//�T�E���h���擾
	CSound *pSound;
	pSound = CManager::GetSound();

	//�T�E���h�ݒu
	pSound->Stop(CSound::SOUND_LABEL_BGM003);

	// �I�u�W�F�N�g�j��
	Release();
}

//==============================================================================
// �X�V����
//==============================================================================
void CGame::Update(void)
{
	//�L�[�{�[�h�擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//���S�t���O���O��
	if (g_bDeathFlagGame == false)
	{
		g_bDeathFlagGame = true;

		//�N���A����������
		CManager::SetEnemyDead(0);
	}

	//�J�E���g
	nTimeCounter++;

	//�J�E���^�[��60�ȏ�ɂȂ�����
	if (nTimeCounter >= 60)
	{
		nTimeGame++;

		//�J�E���^�[��߂�
		nTimeCounter = 0;
	}

	//�G�̏o�����U���̊֐�
	Attack(); 

	//���{�X��1�̓|�����ꍇ
	if (CManager::GetEnemyDead() == 19)		//�����𖞂����Ă���ꍇ
	{
		//��ʑJ�ڏ���
		if (g_bMigrate == false)
		{
			g_bMigrate = true;
			nTimeGame = 100;
			nTimeCounter = 0;
		}
	}

	//�G��|���Ă���2�b�o�ߌ�ɉ�ʑJ��
	if (g_bMigrate == true)
	{
		if (nTimeGame == 103 && nTimeCounter == 0)
		{
			//��ʑJ��
			CFade::SetFade(CFade::FADE_OUT, CManager::MODE_GAME2, D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.0f));	// �V�[���J��
		}
	}

	//�G��|���؂����ꍇ�Ƀ^�C���X�L�b�v
	if (g_bDead == false)
	{
		if (CManager::GetEnemyDead() == 8)		//�����𖞂����Ă���ꍇ
		{
			if (nTimeGame < WAVE_2 - 1)
			{
				g_nDaed = CManager::GetEnemyDead();
				g_bDead = true;
				nTimeGame = WAVE_2 - 1;		//12�b�܂Ń^�C���X�L�b�v
			}
		}

		if (CManager::GetEnemyDead() == 16)		//�����𖞂����Ă���ꍇ
		{
			if (nTimeGame < WAVE_3 - 1)
			{
				g_nDaed = CManager::GetEnemyDead();
				g_bDead = true;
				nTimeGame = WAVE_3 - 1;		//12�b�܂Ń^�C���X�L�b�v
			}
		}

		if (CManager::GetEnemyDead() == 18)		//�����𖞂����Ă���ꍇ
		{
			if (nTimeGame < WAVE_4 - 1)
			{
				g_nDaed = CManager::GetEnemyDead();
				g_bDead = true;
				nTimeGame = WAVE_4 - 1;		//12�b�܂Ń^�C���X�L�b�v
			}
		}
	}

	//�l���ω������ꍇ�ɏ���������
	if (g_nDaed != CManager::GetEnemyDead())
	{
		g_bDead = false;
	}
}

//==============================================================================
// �`�揈��
//==============================================================================
void CGame::Draw(void)
{
#ifdef _DEBUG
	// ���[�J���ϐ��錾
	RECT rect = { -1500,30,SCREEN_WIDTH,SCREEN_HEIGHT };
	RECT rect2 = { -1500,110,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];
	char aStr2[256];

	//��ʂɕ\��������
	sprintf(&aStr[0], "�f�b�g�J�E���g : %d\n", CManager::GetEnemyDead());
	sprintf(&aStr2[0], "�o�ߎ��� : %d\n", nTimeGame);

	// �e�L�X�g�̕`��
	m_pTimeFontGame->DrawText(NULL, &aStr[0], -1, &rect, DT_CENTER, D3DCOLOR_RGBA(255, 255, 255, 255));
	m_pTimeFontGame->DrawText(NULL, &aStr2[0], -1, &rect2, DT_CENTER, D3DCOLOR_RGBA(255, 255, 255, 255));
#endif
}

//==============================================================================
//�G�̈ړ��Ǘ�
//==============================================================================
void CGame::Attack(void)
{
	///�����_���ɃA�C�e���𐶐�
	int nRand = rand() % 1000;
	int nRandX = rand() % SCREEN_WIDTH;

	if (nRand == 1)
	{
		//�A�C�e������
		CItem::Create(D3DXVECTOR3((float)nRandX, 0.0f, 0.0f), 2.0f, 50.0f, 50.0f, 0);
	}

	else if (nRand == 2 || nRand == 3)
	{
		//�A�C�e������
		CItem::Create(D3DXVECTOR3((float)nRandX, 0.0f, 0.0f), 2.0f, 50.0f, 50.0f, 1);
	}

	//1
	{
		if (nTimeGame == WAVE_1 && nTimeCounter == 0)
		{
			CEnemy::Create(D3DXVECTOR3(800.0f, -100.0f, 0.0f), 15.0f, D3DXVECTOR3(300.0f, 400.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, WAVE_2, ENEMY_01, 1);
			CEnemy::Create(D3DXVECTOR3(800.0f, -200.0f, 0.0f), 15.0f, D3DXVECTOR3(300.0f, 300.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, WAVE_2, ENEMY_01, 2);
			CEnemy::Create(D3DXVECTOR3(800.0f, -300.0f, 0.0f), 15.0f, D3DXVECTOR3(300.0f, 200.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, WAVE_2, ENEMY_01, 3);
			CEnemy::Create(D3DXVECTOR3(800.0f, -400.0f, 0.0f), 15.0f, D3DXVECTOR3(300.0f, 100.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, WAVE_2, ENEMY_01, 4);
		}

		if (nTimeGame == WAVE_1 + 3 && nTimeCounter == 0)
		{
			for (int nCnt = 0; nCnt < 4; nCnt++)
			{
				int nRnadXPos = rand() % SCREEN_WIDTH;
				int nRnadXOjective = rand() % SCREEN_WIDTH - 200;
				int nRnadYOjective = rand() % 400;
				CEnemy::Create(D3DXVECTOR3((float)nRnadXPos, -100.0f, 0.0f), 10.0f, D3DXVECTOR3((float)nRnadXOjective + 100.0f, (float)nRnadYOjective + 100.0f, 0.0f), 100, ENEMY_SIZE, ENEMY_SIZE, 8, ENEMY_01, 0);
			}
		}

		if (nTimeGame == WAVE_1 + 2 && nTimeCounter == 0)
		{
			CEnemy::NextMove(D3DXVECTOR3(1000.0f, 800.0f, 0.0f), 15.0f, 1);
		}

		if (nTimeGame == WAVE_1 + 2 && nTimeCounter == 1)
		{
			CEnemy::NextMove(D3DXVECTOR3(1000.0f, 700.0f, 0.0f), 15.0f, 2);
		}

		if (nTimeGame == WAVE_1 + 2 && nTimeCounter == 2)
		{
			CEnemy::NextMove(D3DXVECTOR3(1000.0f, 600.0f, 0.0f), 15.0f, 3);
		}

		if (nTimeGame == WAVE_1 + 2 && nTimeCounter == 3)
		{
			CEnemy::NextMove(D3DXVECTOR3(1000.0f, 500.0f, 0.0f), 15.0f, 4);
		}

		if (nTimeGame == WAVE_1 + 4 && nTimeCounter == 0)
		{
			CEnemy::NextMove(D3DXVECTOR3(1800.0f, 400.0f, 0.0f), 15.0f, 1);
		}

		if (nTimeGame == WAVE_1 + 4 && nTimeCounter == 1)
		{
			CEnemy::NextMove(D3DXVECTOR3(1700.0f, 300.0f, 0.0f), 15.0f, 2);
		}

		if (nTimeGame == WAVE_1 + 4 && nTimeCounter == 2)
		{
			CEnemy::NextMove(D3DXVECTOR3(1600.0f, 200.0f, 0.0f), 15.0f, 3);
		}

		if (nTimeGame == WAVE_1 + 4 && nTimeCounter == 3)
		{
			CEnemy::NextMove(D3DXVECTOR3(1500.0f, 100.0f, 0.0f), 15.0f, 4);
		}
	}

	//2
	{
		if (nTimeGame == WAVE_2 && nTimeCounter == 0)
		{
			CEnemy::NextAttack(0);		//����U���ɕύX
			CEnemy::Create(D3DXVECTOR3(1000.0f, -100.0f, 0.0f), 8.0f, D3DXVECTOR3(200.0f, 400.0f, 0.0f), 300, ENEMY_SIZE, ENEMY_SIZE, WAVE_3, ENEMY_04, 1);
			CEnemy::Create(D3DXVECTOR3(1000.0f, -200.0f, 0.0f), 8.0f, D3DXVECTOR3(200.0f, 300.0f, 0.0f), 300, ENEMY_SIZE, ENEMY_SIZE, WAVE_3, ENEMY_04, 2);
			CEnemy::Create(D3DXVECTOR3(1000.0f, -300.0f, 0.0f), 8.0f, D3DXVECTOR3(200.0f, 200.0f, 0.0f), 300, ENEMY_SIZE, ENEMY_SIZE, WAVE_3, ENEMY_04, 3);
			CEnemy::Create(D3DXVECTOR3(1000.0f, -400.0f, 0.0f), 8.0f, D3DXVECTOR3(200.0f, 100.0f, 0.0f), 300, ENEMY_SIZE, ENEMY_SIZE, WAVE_3, ENEMY_04, 4);
			CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 1000.0f, -100.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 1000.0f, 0.0f), 300, ENEMY_SIZE, ENEMY_SIZE, WAVE_3, ENEMY_04, 5);
			CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 1000.0f, -200.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 900.0f, 0.0f), 300, ENEMY_SIZE, ENEMY_SIZE, WAVE_3, ENEMY_04, 6);
			CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 1000.0f, -300.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 800.0f, 0.0f), 300, ENEMY_SIZE, ENEMY_SIZE, WAVE_3, ENEMY_04, 7);
			CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 1000.0f, -400.0f, 0.0f), 8.0f, D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 700.0f, 0.0f), 300, ENEMY_SIZE, ENEMY_SIZE, WAVE_3, ENEMY_04, 8);
		}

		//����U���ɕύX
		if (nTimeGame == WAVE_2 + 1 && nTimeCounter == 0)
		{
			CEnemy::NextAttack(2);
		}

		if (nTimeGame == WAVE_2 + 3 && nTimeCounter == 0)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 400.0f, 0.0f), 10.0f, 1);
		}

		if (nTimeGame == WAVE_2 + 3 && nTimeCounter == 1)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 300.0f, 0.0f), 10.0f, 2);
		}

		if (nTimeGame == WAVE_2 + 3 && nTimeCounter == 2)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 200.0f, 0.0f), 10.0f, 3);
		}

		if (nTimeGame == WAVE_2 + 3 && nTimeCounter == 3)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 100.0f, 0.0f), 10.0f, 4);
		}

		if (nTimeGame == WAVE_2 + 3 && nTimeCounter == 4)
		{
			CEnemy::NextMove(D3DXVECTOR3(200.0f, 1000.0f, 0.0f), 10.0f, 5);
		}

		if (nTimeGame == WAVE_2 + 3 && nTimeCounter == 5)
		{
			CEnemy::NextMove(D3DXVECTOR3(200.0f, 900.0f, 0.0f), 10.0f, 6);
		}

		if (nTimeGame == WAVE_2 + 3 && nTimeCounter == 6)
		{
			CEnemy::NextMove(D3DXVECTOR3(200.0f, 800.0f, 0.0f), 10.0f, 7);
		}

		if (nTimeGame == WAVE_2 + 3 && nTimeCounter == 7)
		{
			CEnemy::NextMove(D3DXVECTOR3(200.0f, 700.0f, 0.0f), 10.0f, 8);
		}

		//�ړ�
		if (nTimeGame == WAVE_2 + 6 && nTimeCounter == 0)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 700.0f, 0.0f), 10.0f, 1);
		}

		if (nTimeGame == WAVE_2 + 6 && nTimeCounter == 1)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 800.0f, 0.0f), 10.0f, 2);
		}

		if (nTimeGame == WAVE_2 + 6 && nTimeCounter == 2)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 900.0f, 0.0f), 10.0f, 3);
		}

		if (nTimeGame == WAVE_2 + 6 && nTimeCounter == 3)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 1000.0f, 0.0f), 10.0f, 4);
		}

		if (nTimeGame == WAVE_2 + 6 && nTimeCounter == 4)
		{
			CEnemy::NextMove(D3DXVECTOR3(200.0f, 100.0f, 0.0f), 10.0f, 5);
		}

		if (nTimeGame == WAVE_2 + 6 && nTimeCounter == 5)
		{
			CEnemy::NextMove(D3DXVECTOR3(200.0f, 200.0f, 0.0f), 10.0f, 6);
		}

		if (nTimeGame == WAVE_2 + 6 && nTimeCounter == 6)
		{
			CEnemy::NextMove(D3DXVECTOR3(200.0f, 300.0f, 0.0f), 10.0f, 7);
		}

		if (nTimeGame == WAVE_2 + 6 && nTimeCounter == 7)
		{
			CEnemy::NextMove(D3DXVECTOR3(200.0f, 400.0f, 0.0f), 10.0f, 8);
		}

		//����U���ɕύX
		if (nTimeGame == WAVE_2 + 8 && nTimeCounter == 0)
		{
			CEnemy::NextAttack(3);
		}

		//�ړ�
		if (nTimeGame == WAVE_2 + 8 && nTimeCounter == 0)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 1000.0f, 0.0f), 10.0f, 1);
		}

		if (nTimeGame == WAVE_2 + 8 && nTimeCounter == 1)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 400.0f, 1000.0f, 0.0f), 10.0f, 2);
		}

		if (nTimeGame == WAVE_2 + 8 && nTimeCounter == 2)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 600.0f, 1000.0f, 0.0f), 10.0f, 3);
		}

		if (nTimeGame == WAVE_2 + 8 && nTimeCounter == 3)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 800.0f, 1000.0f, 0.0f), 10.0f, 4);
		}

		if (nTimeGame == WAVE_2 + 8 && nTimeCounter == 4)
		{
			CEnemy::NextMove(D3DXVECTOR3(800.0f, 100.0f, 0.0f), 10.0f, 5);
		}

		if (nTimeGame == WAVE_2 + 8 && nTimeCounter == 5)
		{
			CEnemy::NextMove(D3DXVECTOR3(600.0f, 100.0f, 0.0f), 10.0f, 6);
		}

		if (nTimeGame == WAVE_2 + 8 && nTimeCounter == 6)
		{
			CEnemy::NextMove(D3DXVECTOR3(400.0f, 100.0f, 0.0f), 10.0f, 7);
		}

		if (nTimeGame == WAVE_2 + 8 && nTimeCounter == 7)
		{
			CEnemy::NextMove(D3DXVECTOR3(200.0f, 100.0f, 0.0f), 10.0f, 8);
		}

		//����U���ɕύX
		if (nTimeGame == WAVE_2 + 10 && nTimeCounter == 0)
		{
			CEnemy::NextAttack(10);
		}

		//�ړ�
		if (nTimeGame == WAVE_2 + 10 && nTimeCounter == 0)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 800.0f, 600.0f, 0.0f), 10.0f, 1);
		}

		if (nTimeGame == WAVE_2 + 10 && nTimeCounter == 1)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 600.0f, 400.0f, 0.0f), 10.0f, 2);
		}

		if (nTimeGame == WAVE_2 + 10 && nTimeCounter == 2)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 400.0f, 200.0f, 0.0f), 10.0f, 3);
		}

		if (nTimeGame == WAVE_2 + 10 && nTimeCounter == 3)
		{
			CEnemy::NextMove(D3DXVECTOR3(SCREEN_WIDTH - 200.0f, 100.0f, 0.0f), 10.0f, 4);
		}

		if (nTimeGame == WAVE_2 + 10 && nTimeCounter == 4)
		{
			CEnemy::NextMove(D3DXVECTOR3(200.0f, 200.0f, 0.0f), 10.0f, 5);
		}

		if (nTimeGame == WAVE_2 + 10 && nTimeCounter == 5)
		{
			CEnemy::NextMove(D3DXVECTOR3(400.0f, 400.0f, 0.0f), 10.0f, 6);
		}

		if (nTimeGame == WAVE_2 + 10 && nTimeCounter == 6)
		{
			CEnemy::NextMove(D3DXVECTOR3(600.0f, 600.0f, 0.0f), 10.0f, 7);
		}

		if (nTimeGame == WAVE_2 + 10 && nTimeCounter == 7)
		{
			CEnemy::NextMove(D3DXVECTOR3(800.0f, 100.0f, 0.0f), 10.0f, 8);
		}
	}

	//2
	{
		if (nTimeGame == WAVE_3 && nTimeCounter == 0)
		{
			CEnemy::Create(D3DXVECTOR3(800.0f, -100.0f, 0.0f), 5.0f, D3DXVECTOR3(700.0f, 200.0f, 0.0f), 800, ENEMY_SIZE, ENEMY_SIZE, WAVE_4, ENEMY_06, 0);
			CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH - 800.0f, -100.0f, 0.0f), 5.0f, D3DXVECTOR3(SCREEN_WIDTH - 700.0f, 200.0f, 0.0f), 800, ENEMY_SIZE, ENEMY_SIZE, WAVE_4, ENEMY_07, 0);
		}

		//����U���ɕύX
		if (nTimeGame == WAVE_3 + 1 && nTimeCounter == 0)
		{
			CEnemy::NextAttack(8);
		}
	}

	//3
	{
		//�A�C�e������
		if (nTimeGame == WAVE_4 && nTimeCounter == 0)
		{
			CItem::Heart2(D3DXVECTOR3(SCREEN_WIDTH / 2, 0.0f, 0.0f), 2.0f, 50, 50, 1, 0);
		}


		if (nTimeGame == WAVE_4 + 2 && nTimeCounter == 0)
		{
			CEnemy::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, -100.0f, 0.0f), 5.0f, D3DXVECTOR3(SCREEN_WIDTH / 2, 200.0f, 0.0f), 5000, ENEMY_SIZE + 50, ENEMY_SIZE + 50, 999, ENEMY_05, 1);
		}

		//����U���ɕύX
		if (nTimeGame == WAVE_4 + 4 && nTimeCounter == 0)
		{
			CEnemy::NextAttack(9);
		}

		//����U���ɕύX
		if (nTimeGame == WAVE_4 + 10 && nTimeCounter == 0)
		{
			CEnemy::NextAttack2(11);
		}
	}
}

//==============================================================================
// Get�֐��^�C��
//==============================================================================
int CGame::GetTime(void)
{
	return nTimeGame;
}

//==============================================================================
// ��������
//==============================================================================
CGame * CGame::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	// �|�C���^�ϐ��̐���
	CGame *pGame;
	pGame = new CGame;

	// NULL�`�F�b�N
	if (pGame != NULL)
	{
		pGame->Init(pos, fSizeX, fSizeY);
	}

	return pGame;
}
