//=============================================================================
//
// �}�l�[�W���[���� [manager.cpp]
// Author : takahashi shota
//
//=============================================================================

//=============================================================================
//�C���N���[�h�ǂݍ���
//=============================================================================
#include "manager.h"
#include "scene.h"
#include "scene2D.h"
#include "sound.h"
#include "score.h"
#include "number.h"
#include "gamepad.h"
#include "fade.h"
#include "texture.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
CRenderer		*CManager::m_pRenderer = NULL;
CInputKeyboard	*CManager::m_pInputKeyboard = NULL;
CInput			*CManager::m_pInput = NULL;
CSound			*CManager::m_pSound = NULL;
CScene			*CManager::m_pScene = NULL;
CScore			*CManager::m_pScore = NULL;
CNumber			*CManager::m_pNumber = NULL;
CGamepad		*CManager::m_pGamepad = NULL;
CGame			*CManager::m_pGame = NULL;
CCamera			*CManager::m_pCamera = NULL;
CLight			*CManager::m_pLight = NULL;
CSceneX			*CManager::m_pSceneX = NULL;
CTexture		*CManager::m_pTexture = NULL;

//�����̉��
CManager::MODE	CManager::m_mode = MODE_GAME;

//�O���[�o���ϐ��錾
bool	CManager::m_bEndGame = false;		//�o�ߎ��Ԃ�\��������
bool	g_bPause = false;					//�|�[�Y���

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CManager::CManager()
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CManager::~CManager()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	//�����_���[�쐬
	if (m_pRenderer == NULL)
	{
		m_pRenderer = new CRenderer;
		m_pRenderer->Init(hWnd, bWindow);
	}

	//�L�[�{�[�h����
	m_pInputKeyboard = new CInputKeyboard;
	m_pInputKeyboard->Init(hInstance, hWnd);

	m_pGamepad = new CGamepad;
	m_pGamepad->Init(hInstance, hWnd);

	//�T�E���h����
	m_pSound = new CSound;
	m_pSound->Init(hWnd);

	//�J��������
	m_pCamera = new CCamera;
	m_pCamera->Init();

	//���C�g����
	m_pLight = new CLight;
	m_pLight->Init();

	//�ԍ��̃e�N�X�`���ǂݍ���
	CNumber::Load();

	//�e�N�X�`���N���X�𐶐�
	m_pTexture = new CTexture;
	m_pTexture->Load();

	//���[�h�ݒ�
	SetMode(m_mode);

	return S_OK;
}

//==============================================================================
// ���[�h�I��
//==============================================================================
void CManager::SetMode(MODE mode)
{
	//�I������
	CScene::ReleaseAll();

	//�t�F�[�h���N���G�C�g
	CFade::Create(m_mode);

	//��ʑJ�ڎ��ɏ�����
	g_bPause = false;

	switch (mode)
	{
	case MODE_GAME:

		//�Q�[����ʂ̏���������
		m_pGame->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f);
		break;
	}

	m_mode = mode;
}

//=============================================================================
// �I������
//=============================================================================
void CManager::Uninit(void)
{
	//�I�u�W�F�N�g�N���X�̔j��
	CScene::ReleaseAll();

	// �e�N�X�`���̊J��
	CNumber::Unload();

	//�e�N�X�`���N���X�̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Unload();
		delete m_pTexture;
		m_pTexture = NULL;
	}

	//���͏����̔j��
	if (m_pInput != NULL)
	{
		m_pInput->Uninit();
		delete m_pInput;
		m_pInput = NULL;
	}

	//�T�E���h�̔j��
	if (m_pSound != NULL)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}

	//�����_�����O�N���X�̔j��
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CManager::Update(void)
{
	//�Q�[���p�b�h�̃|�C���^�錾
	CGamepad *pGamepad;
	pGamepad = CManager::GetGamepad();

	//�J�����̍X�V
	m_pCamera->Update();

	//�L�[�{�[�h�̍X�V����
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}

	//�Q�[���p�b�h�̍X�V����
	if (m_pGamepad != NULL)
	{
		m_pGamepad->Update();
	}

	//�����_���[�̍X�V
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CManager::Draw(void)
{
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}

//=============================================================================
// �L�[�{�[�h��Get�֐�
//=============================================================================
CInputKeyboard * CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//=============================================================================
// �����_���[��Get�֐�
//=============================================================================
CRenderer * CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//=============================================================================
// �T�E���h��Get�֐�
//=============================================================================
CSound * CManager::GetSound(void)
{
	return m_pSound;
}

//=============================================================================
// �J������Get�֐�
//=============================================================================
CCamera * CManager::GetCamera(void)
{
	return m_pCamera;
}

//=============================================================================
// �e�N�X�`����Get�֐�
//=============================================================================
CTexture * CManager::GetTexture(void)
{
	return m_pTexture;
}
