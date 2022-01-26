//=============================================================================
//
// �|�[�Y���� [pause.cpp]
// Author : takahashi shota
//
//=============================================================================

//=============================================================================
//�C���N���[�h�ǂݍ���
//=============================================================================
#include "pause.h"
#include "logo.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "animation.h"
#include "fade.h"

//�O���[�o���ϐ��錾
int nTimeGamePause = 0;			//����
int nTimeCounterPause = 0;		//���ԃJ�E���^�[
int g_nPointerPauseX = 0;		//�|�C���^�[�ʒu
bool g_bButtonDownPause = false;	//�A�Ŗh�~

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CPause::CPause(int nPriority, int nType) : CScene(nPriority, nType)
{
	//������
	g_nPointerPauseX = 0;
	g_bButtonDownPause = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPause::~CPause()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CPause::Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�w�i�𐶐�
	CLogoPause::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, PAUSE01);

	//�t���[���𐶐�
	CLogoPause::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 0.0f, 0.0f), 210, 60, FRAME);

	//���S(�I��p)�𐶐�
	CLogoPause::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 0.0f, 0.0f), 200, 50, GAMEOVER_RESTART);
	CLogoPause::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), 200, 50, GAMEOVER_START);
	CLogoPause::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 400.0f, 0.0f), 200, 50, GAMEOVER_END);//�w�i��\��

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPause::Uninit(void)
{
	// �I�u�W�F�N�g�j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPause::Update(void)
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

	//��ʑJ�ڂ��n�܂��ĂȂ��ꍇ
	if (g_bButtonDownPause == false)
	{
		//S�������������ꍇ
		if (pInputKeyboard->GetTrigger(DIK_S) == true || pGamepad->IsButtonDown(CInput::DOWN))
		{
			if (g_nPointerPauseX == 0)
			{
				g_nPointerPauseX = 1;
				CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), FRAME);
			}

			else if (g_nPointerPauseX == 1)
			{
				g_nPointerPauseX = 2;
				CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 400.0f, 0.0f), FRAME);
			}

			else if (g_nPointerPauseX == 2)
			{
				g_nPointerPauseX = 0;
				CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), FRAME);
			}

			//�T�E���hSE
			pSound->Play(CSound::SOUND_LABEL_SE_MIGRATION);
		}

		//W�������������ꍇ
		if (pInputKeyboard->GetTrigger(DIK_W) == true || pGamepad->IsButtonDown(CInput::UP))
		{
			if (g_nPointerPauseX == 0)
			{
				g_nPointerPauseX = 2;
				CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 400.0f, 0.0f), FRAME);
			}

			else if (g_nPointerPauseX == 1)
			{
				g_nPointerPauseX = 0;
				CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 0.0f, 0.0f), FRAME);
			}

			else if (g_nPointerPauseX == 2)
			{
				g_nPointerPauseX = 1;
				CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), FRAME);
			}

			//�T�E���hSE
			pSound->Play(CSound::SOUND_LABEL_SE_MIGRATION);
		}

		//��ʑJ��
		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pGamepad->IsButtonDown(CInput::A) || pGamepad->IsButtonDown(CInput::B) == true)
		{
			if (g_nPointerPauseX == 0)
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
					CFade::SetFade(CFade::FADE_OUT, CManager::MODE_GAME2, D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.0f));	// �V�[���J��
				}
			}

			if (g_nPointerPauseX == 1)
			{
				//���[�h�ݒ�
				CFade::SetFade(CFade::FADE_OUT, CManager::MODE_SELECT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	// �V�[���J��
			}

			if (g_nPointerPauseX == 2)
			{
				//���[�h�ݒ�
				CFade::SetFade(CFade::FADE_OUT, CManager::MODE_TITLE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	// �V�[���J��
			}

			//��ʑJ�ڂ��n�܂���
			g_bButtonDownPause = true;

			//�T�E���hSE
			pSound->Play(CSound::SOUND_LABEL_SE_DECISION);
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPause::Draw(void)
{

}

//=============================================================================
// ��������
//=============================================================================
CPause * CPause::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	// �|�C���^�ϐ��̐���
	CPause *pPause;
	pPause = new CPause;

	// NULL�`�F�b�N
	if (pPause != NULL)
	{
		//�|�[�Y��ʂ̐���
		pPause->Init(pos, fSizeX, fSizeY);
	}

	return pPause;
}
