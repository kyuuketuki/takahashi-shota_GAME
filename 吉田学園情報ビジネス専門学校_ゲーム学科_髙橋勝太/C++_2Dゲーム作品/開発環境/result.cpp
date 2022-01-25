//=============================================================================
//
// ���U���g���� [game2.cpp]
// Author : takahashi shota
//
//=============================================================================

//=============================================================================
//�C���N���[�h�ǂݍ���
//=============================================================================
#include "game2.h"
#include "bg.h"
#include "player.h"
#include "score.h"
#include "enemy.h"
#include "polygon.h"
#include "life.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "bullet.h"
#include "animation.h"
#include "result.h"
#include "item.h"
#include "logo.h"
#include "fade.h"

int nTimeGameResult = 0;			//����
int nTimeCounterResult = 0;			//���ԃJ�E���^�[
int g_nPointerResultX = 0;			//���݂̈ʒu���L��
bool g_bButtonDownResult = false;	//�A�Ŗh�~�p

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CResult::CResult()
{
	//������
	g_nPointerResultX = 0;
	g_bButtonDownResult = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CResult::~CResult()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CResult::Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �t�H���g�I�u�W�F�N�g�̐���
	D3DXCreateFont(pDevice, 36, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pTimeFontGame);

	//�w�i��\��
	CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	
	//�G��|����������
	int nDeatCnt = CManager::GetEnemyDead();
	
	//Stage2�Ń��U���g��ʂɑJ�ڂ����Ƃ�
	if (CManager::GetGameStage() == 2)
	{
		//�N���A����
		if (CManager::GetGameClear() == true)
		{

			//�Q�[���I�[�o�[��
			CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 200.0f, 0.0f), 400.0f, 150.0f, GAMECLEAR01);
		}

		else
		{
			//�Q�[���I�[�o�[��
			CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 200.0f, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, GAMEOVER01);
		}
	}

	if (CManager::GetGameStage() == 1)
	{
		//�Q�[���I�[�o�[��
		CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 200.0f, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, GAMEOVER01);
	}

	//�t���[��
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 0.0f, 0.0f), 210, 60, FRAME);

	//���S�@�I�����S
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 0.0f, 0.0f), 200, 50, GAMEOVER_RESTART);
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), 200, 50, GAMEOVER_START);
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 400.0f, 0.0f), 200, 50, GAMEOVER_END);	//�w�i��\��

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CResult::Uninit(void)
{
	// �I�u�W�F�N�g�j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CResult::Update(void)
{
	//�L�[�{�[�h�擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�Q�[���p�b�h�̃|�C���^�錾
	CGamepad *pGamepad;
	pGamepad = CManager::GetGamepad();

	//�T�E���h���擾
	CSound *pSound;
	pSound = CManager::GetSound();

	//�J�[�\���ړ�
	//��ʑJ�ڂ��n�܂��ĂȂ��ꍇ
	if (g_bButtonDownResult == false)
	{
		if (pInputKeyboard->GetTrigger(DIK_S) == true || pGamepad->IsButtonDown(CInput::DOWN))
		{
			if (g_nPointerResultX == 0)
			{
				g_nPointerResultX = 1;
				CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), FRAME);
			}

			else if (g_nPointerResultX == 1)
			{
				g_nPointerResultX = 2;
				CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 400.0f, 0.0f), FRAME);
			}

			else if (g_nPointerResultX == 2)
			{
				g_nPointerResultX = 0;
				CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), FRAME);
			}

			//�T�E���hSE
			pSound->Play(CSound::SOUND_LABEL_SE_MIGRATION);
		}

		if (pInputKeyboard->GetTrigger(DIK_W) == true || pGamepad->IsButtonDown(CInput::UP))
		{
			if (g_nPointerResultX == 0)
			{
				g_nPointerResultX = 2;
				CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 400.0f, 0.0f), FRAME);
			}

			else if (g_nPointerResultX == 1)
			{
				g_nPointerResultX = 0;
				CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 0.0f, 0.0f), FRAME);
			}

			else if (g_nPointerResultX == 2)
			{
				g_nPointerResultX = 1;
				CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), FRAME);
			}

			//�T�E���hSE
			pSound->Play(CSound::SOUND_LABEL_SE_MIGRATION);
		}

		//�J�[�\���ړ�
		//��ʑJ��
		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pGamepad->IsButtonDown(CInput::A) || pGamepad->IsButtonDown(CInput::B) == true)
		{
			if (g_nPointerResultX == 0)
			{
				//Stage1�ŃQ�[���I�[�o�[�ɂȂ����ꍇ
				if (CManager::GetGameStage() == 1)
				{
					//Stage1�ɑJ�ڂ���
					CFade::SetFade(CFade::FADE_OUT, CManager::MODE_GAME, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));	// �V�[���J��
				}

				//Stage1�ŃQ�[���I�[�o�[�ɂȂ����ꍇ
				if (CManager::GetGameStage() == 2)
				{
					//Stage2�ɑJ�ڂ���
					CFade::SetFade(CFade::FADE_OUT, CManager::MODE_GAME2, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));	// �V�[���J��
				}
			}

			if (g_nPointerResultX == 1)
			{
				//���[�h�ݒ�
				CFade::SetFade(CFade::FADE_OUT, CManager::MODE_SELECT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	// �V�[���J��
			}

			if (g_nPointerResultX == 2)
			{
				//���[�h�ݒ�
				//CManager::SetMode(CManager::MODE_TITLE);
				CFade::SetFade(CFade::FADE_OUT, CManager::MODE_TITLE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	// �V�[���J��
			}

			//��ʑJ�ڂ��n�܂���
			g_bButtonDownResult = true;

			//�T�E���hSE
			pSound->Play(CSound::SOUND_LABEL_SE_DECISION);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CResult::Draw(void)
{
}

//=============================================================================
// ��������
//=============================================================================
CResult * CResult::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	// ���U���g��ʂ̐���
	CResult *pResult;
	pResult = new CResult;

	// NULL�`�F�b�N
	if (pResult != NULL)
	{
		pResult->Init(pos, fSizeX, fSizeY);
	}

	return pResult;
}
