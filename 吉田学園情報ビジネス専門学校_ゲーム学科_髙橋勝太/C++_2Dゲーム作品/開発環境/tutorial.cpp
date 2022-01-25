//=============================================================================
//
// �`���[�g���A����ʏ��� [tutorial.cpp]
// Author : takahashi shota
//
//=============================================================================
#include "tutorial.h"
#include "manager.h"
#include "animation.h"
#include "item.h"
#include "life.h"
#include "enemy.h"
#include "logo.h"
#include "fade.h"

//�O���[�o���錾
int nPointer_Tutorial = 0;		//�v���X�J�E���g
bool g_bPressTutorial = false;	//���������Ɏg�p

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CTutorial::CTutorial()
{
	//����������
	nPointer_Tutorial = 0;
	g_bPressTutorial = false;
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CTutorial::~CTutorial()
{

}

//==============================================================================
// ����������
//==============================================================================
HRESULT CTutorial::Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	return S_OK;
}


//==============================================================================
// �I������
//==============================================================================
void CTutorial::Uninit(void)
{
	// �I�u�W�F�N�g�j��
	Release();
}

//==============================================================================
// �X�V����
//==============================================================================
void CTutorial::Update(void)
{
	//�L�[�{�[�h�擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�Q�[���p�b�h�̃|�C���^�錾
	CGamepad *pGamepad;
	pGamepad = CManager::GetGamepad();

	//�J�[�\���ړ�
	//��ʐ؂�ւ�
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pGamepad->IsButtonDown(CInput::UP) == true || pGamepad->IsButtonDown(CInput::B) == true)
	{
		nPointer_Tutorial += 1;
		g_bPressTutorial = false;
	}

	if (nPointer_Tutorial == 0)
	{
		if (g_bPressTutorial == false)
		{
			//���S�̈ړ�
			CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 25);

			g_bPressTutorial = true;
		}
	}

	if (nPointer_Tutorial == 1)
	{
		if (g_bPressTutorial == false)
		{
			//���S�̈ړ�
			CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 26);

			g_bPressTutorial = true;
		}
	}

	if (nPointer_Tutorial == 2)
	{
		if (g_bPressTutorial == false)
		{
			//���[�h�ݒ�
			CFade::SetFade(CFade::FADE_OUT, CManager::MODE_MENU, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	// �V�[���J��

			g_bPressTutorial = true;
		}
	}
}

//==============================================================================
// �`�揈��
//==============================================================================
void CTutorial::Draw(void)
{
}

//==============================================================================
// ��������
//==============================================================================
CTutorial * CTutorial::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	// �`���[�g���A����ʂ̐���
	CTutorial *pTutorial;
	pTutorial = new CTutorial;

	// NULL�`�F�b�N
	if (pTutorial != NULL)
	{
		pTutorial->Init(pos, fSizeX, fSizeY);
	}

	return pTutorial;
}
