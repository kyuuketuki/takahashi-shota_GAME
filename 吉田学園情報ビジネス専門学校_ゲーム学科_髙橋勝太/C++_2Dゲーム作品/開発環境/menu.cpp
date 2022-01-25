//=============================================================================
//
// ���j���[���� [menu.cpp]
// Author : takahashi shota
//
//=============================================================================

//=============================================================================
//�C���N���[�h�ǂݍ���
//=============================================================================
#include "menu.h"
#include "bg.h"
#include "input.h"
#include "manager.h"
#include "scene2D.h"
#include "logo.h"
#include "animation.h"
#include "polygon.h"
#include "fade.h"

//�O���[�o���ϐ��錾
int g_nPointerMenuX = 0;
bool g_bButtonDownMenu = false;

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CMenu::CMenu()
{
	g_nPointerMenuX = 0;
	g_bButtonDownMenu = false;
}

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CMenu::~CMenu()
{

}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
HRESULT CMenu::Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	//�w�i�𐶐�
	CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	//UI�𐶐�
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 200.0f, 0.0f), 210, 60, FRAME);
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 200.0f, 0.0f), 200, 50, TITLE_UI_GAMESTART);
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), 200, 50, TITLE_UI_TUTORIAL);
	CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), 200, 50, TITLE_UI_END);

	//�A�j���[�V�����I�u�W�F�N�g�𐶐�
	CAnimasion::Create(D3DXVECTOR3(300.0f, 200.0f, 0.0f), 300, 300, 10, 15);
	CAnimasion::Create(D3DXVECTOR3(SCREEN_WIDTH - 300.0f, SCREEN_HEIGHT - 200.0f, 0.0f), 300, 300, 10, 16);

	return S_OK;
}

//==============================================================================
// �I������
//==============================================================================
void CMenu::Uninit(void)
{
	// �I�u�W�F�N�g�j��
	Release();
}

//==============================================================================
// �X�V����
//==============================================================================
void CMenu::Update(void)
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
	//S�������������ꍇ
	if (pInputKeyboard->GetTrigger(DIK_S) == true || pGamepad->IsButtonDown(CInput::DOWN))
	{
		if (g_nPointerMenuX == 0)
		{
			g_nPointerMenuX = 1;
			CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), FRAME);					//�ʒu��ς���
		}

		else if (g_nPointerMenuX == 1)
		{
			g_nPointerMenuX = 2;
			CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), FRAME);		//�ʒu��ς���
		}

		else if (g_nPointerMenuX == 2)
		{
			g_nPointerMenuX = 0;
			CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 200.0f, 0.0f), FRAME);		//�ʒu��ς���
		}

		//�T�E���hSE
		pSound->Play(CSound::SOUND_LABEL_SE_MIGRATION);
	}

	//�J�[�\���ړ�
	//W�������������ꍇ
	if (pInputKeyboard->GetTrigger(DIK_W) == true || pGamepad->IsButtonDown(CInput::UP))
	{
		if (g_nPointerMenuX == 0)
		{
			g_nPointerMenuX = 2;
			CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), FRAME);		//�ʒu��ς���
		}

		else if (g_nPointerMenuX == 1)
		{
			g_nPointerMenuX = 0;
			CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 200.0f, 0.0f), FRAME);		//�ʒu��ς���
		}

		else if (g_nPointerMenuX == 2)
		{
			g_nPointerMenuX = 1;
			CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), FRAME);					//�ʒu��ς���
		}

		//�T�E���hSE
		pSound->Play(CSound::SOUND_LABEL_SE_MIGRATION);
	}

	//���߂ĉ������ꍇ
	if (g_bButtonDownMenu == false)
	{
		//��ʑJ��	����{�^�����������ꍇ
		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pGamepad->IsButtonDown(CInput::A) || pGamepad->IsButtonDown(CInput::B) == true)
		{
			if (g_nPointerMenuX == 0)
			{
				//���[�h�ݒ�
				CFade::SetFade(CFade::FADE_OUT, CManager::MODE_SELECT, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));	// �V�[���J��
			}

			if (g_nPointerMenuX == 1)
			{
				//���[�h�ݒ�
				CFade::SetFade(CFade::FADE_OUT, CManager::MODE_TUTORIAL, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	// �V�[���J��
			}

			if (g_nPointerMenuX == 2)
			{
				//���[�h�ݒ�
				CFade::SetFade(CFade::FADE_OUT, CManager::MODE_TITLE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	// �V�[���J��
			}

			//�A�Ŗh�~
			g_bButtonDownMenu = true;

			//�T�E���hSE
			pSound->Play(CSound::SOUND_LABEL_SE_DECISION);
		}
	}
}

//==============================================================================
// �`�揈��
//==============================================================================
void CMenu::Draw(void)
{

}

//==============================================================================
// ��������
//==============================================================================
CMenu * CMenu::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	// �|�C���^�ϐ��̐���
	CMenu *pMenu;
	pMenu = new CMenu;

	// NULL�`�F�b�N
	if (pMenu != NULL)
	{
		pMenu->Init(pos, fSizeX, fSizeY);
	}

	return pMenu;
}
