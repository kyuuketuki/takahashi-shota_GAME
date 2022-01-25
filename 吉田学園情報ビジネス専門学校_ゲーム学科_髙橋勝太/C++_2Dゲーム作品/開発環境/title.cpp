 //=============================================================================
//
// �^�C�g����ʏ��� [title.cpp]
// Author : takahashi shota
//
//=============================================================================

//=============================================================================
//�C���N���[�h�ǂݍ���
//=============================================================================
#include "title.h"
#include "bg.h"
#include "input.h"
#include "manager.h"
#include "scene2D.h"
#include "logo.h"
#include "animation.h"
#include "polygon.h"
#include "gamepad.h"
#include "fade.h"
#include "object3D.h"
#include "scene3D.h"

//�O���[�o���ϐ��錾
int nTimeTitle = 0;					//����
int nTimeCounterTitle = 0;			//���ԃJ�E���^�[
int nNexEnterCount = 0;				//���SEnter�̐F�ω��Ɏg�p
int nSaveTime = -1;					//�A�j���[�V�����p���ԊǗ��p
int nSaveTime2 = -1;				//�A�j���[�V�����p���ԊǗ��p
int nFlashing = 30;					//PressEnter�̓_�ł����鑬�x�@�r���ő��x�ύX
bool g_bPressEnter = false;			//���S�̕\������
bool g_bNextEnter = false;			//���SEnter�̐F�ω��Ɏg�p
bool g_bButtonDownTitle = false;	//�A�Ŗh�~�p

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CTitle::CTitle()
{
	//������
	nTimeTitle = 0;					//����
	nTimeCounterTitle = 0;			//���ԃJ�E���^�[
	nNexEnterCount = 0;				//���SEnter�̐F�ω��Ɏg�p
	nSaveTime = -1;					//�A�j���[�V�����p���ԊǗ��p
	nSaveTime2 = -1;				//�A�j���[�V�����p���ԊǗ��p
	nFlashing = 30;					//PressEnter�̓_�ł����鑬�x�@�r���ő��x�ύX
	g_bPressEnter = false;			//���S�̕\������
	g_bNextEnter = false;			//���SEnter�̐F�ω��Ɏg�p
	g_bButtonDownTitle = false;		//�A�Ŗh�~�p
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CTitle::~CTitle()
{

}

//==============================================================================
// ����������
//==============================================================================
HRESULT CTitle::Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	//�w�i��\��
	CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	//�A�j���[�V������\��	
	CAnimasion::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 10, 4);		//�t���[��

	//�I�u�W�F�N�g�̐���(�f��)
	CObject3D::Create(D3DXVECTOR3(30, 30.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);

	return S_OK;
}

//==============================================================================
// �I������
//==============================================================================
void CTitle::Uninit(void)
{
	// �I�u�W�F�N�g�j��
	Release();
}

//==============================================================================
// �X�V����
//==============================================================================
void CTitle::Update(void)
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

	//�^�C�g�����S���\�����ꂽ���
	if (nTimeTitle >= 2 && nTimeCounterTitle >= 0)
	{
		//Enter���S�̕\��
		if (g_bPressEnter == false)
		{
			CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 400.0f, 0.0f), 150, 50, TITLE_UI_PRESS_ENTER);		//Enter���S
			g_bPressEnter = true;
		}

		//�_�ŏ����@NextEnter
		if (g_bPressEnter == true)
		{
			//�J�E���g�A�b�v
			nNexEnterCount++;
			if (nNexEnterCount == nFlashing)
			{
				//�����ɂ���
				if (g_bNextEnter == true)
				{
					CLogo::TypeChangeCollar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), TITLE_UI_PRESS_ENTER);		//�F�ω�
					g_bNextEnter = false;
				}
				//�s�����ɂ���
				else if (g_bNextEnter == false)
				{
					CLogo::TypeChangeCollar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), TITLE_UI_PRESS_ENTER);		//�F�ω�
					g_bNextEnter = true;
				}

				//���Z�b�g
				nNexEnterCount = 0;
			}
		}

		//���߂ĉ������ꍇ�̂�
		if (g_bButtonDownTitle == false)
		{
			//��ʑJ��
			if (pGamepad->IsButtonDown(CInput::A) == true || pGamepad->IsButtonDown(CInput::B) == true || pInputKeyboard->GetTrigger(DIK_RETURN) == true)
			{
				//�A�j���[�V����
				CAnimasion::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 5, 10);		//��ʑJ�ڃA�j���[�V����

				//�T�E���hSE
				pSound->Play(CSound::SOUND_LABEL_SE_METEOR);

				//��ʑJ�ڂɊւ���ϐ�
				nTimeCounterTitle = 0;

				//�_�łɊւ���ϐ�
				nFlashing = 5;
				nNexEnterCount = 0;

				//�{�^�����������^�C����ۑ�
				nSaveTime = nTimeTitle;
				nSaveTime2 = 30;

				//�A�Ŗh�~
				g_bButtonDownTitle = true;
			}
		}

		//�J�ڏ����A�j���[�V�������I����
		if ((nSaveTime + 1) == nTimeTitle && nSaveTime2 == nTimeCounterTitle)
		{
			//���[�h�ݒ�
			CFade::SetFade(CFade::FADE_OUT, CManager::MODE_MENU, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	// �V�[���J��
		}
	}

	//�^�C����i�߂�
	nTimeCounterTitle++;

	//�J�E���^�[��60�ȏ�ɂȂ�����
	if (nTimeCounterTitle >= 60)
	{
		//�b����i�߂�
		nTimeTitle++;

		//�J�E���^�[��߂�
		nTimeCounterTitle = 0;
	}

	//�^�C���ɍ��킹�Đ���
	if (nTimeTitle == 1 && nTimeCounterTitle == 10)
	{
		CAnimasion::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 5, 1);		//�����~�点��A�j���[�V����

		//�T�E���hSE
		pSound->Play(CSound::SOUND_LABEL_SE_STER);
	}

	//�^�C���ɍ��킹�Đ���
	if (nTimeTitle == 1 && nTimeCounterTitle == 20)
	{
		CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), 500, 200, TITLE_UI);		//�^�C�g��
	}
}

//==============================================================================
// �`�揈��
//==============================================================================
void CTitle::Draw(void)
{

}

//==============================================================================
// ��������
//==============================================================================
CTitle * CTitle::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	// �|�C���^�ϐ��̐���
	CTitle *pTitle;
	pTitle = new CTitle;

	// NULL�`�F�b�N
	if (pTitle != NULL)
	{
		//�^�C�g����ʂ̐���
		pTitle->Init(pos, fSizeX, fSizeY);
	}

	return pTitle;
}
