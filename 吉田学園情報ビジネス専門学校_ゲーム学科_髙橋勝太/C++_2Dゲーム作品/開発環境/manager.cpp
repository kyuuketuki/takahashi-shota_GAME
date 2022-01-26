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
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "explosion.h"
#include "sound.h"
#include "bg.h"
#include "effect.h"
#include "polygon.h"
#include "score.h"
#include "number.h"
#include "logo.h"
#include "life.h"
#include "animation.h"
#include "item.h"
#include "menu.h"
#include "gamepad.h"
#include "fade.h"
#include "result.h"
#include "particle.h"

//=============================================================================
// �ÓI�����o�ϐ�
//=============================================================================
CRenderer		*CManager::m_pRenderer = NULL;
CInputKeyboard	*CManager::m_pInputKeyboard = NULL;
CInput			*CManager::m_pInput = NULL;
CPlayer			*CManager::m_pPlayer = NULL;
CSound			*CManager::m_pSound = NULL;
CScene			*CManager::m_pScene = NULL;
CScore			*CManager::m_pScore = NULL;
CNumber			*CManager::m_pNumber = NULL;
CGamepad		*CManager::m_pGamepad = NULL;
CTitle			*CManager::m_pTitle = NULL;
CMenu			*CManager::m_pMenu = NULL;
CSelect			*CManager::m_pSelect = NULL;
CTutorial		*CManager::m_pTutorial = NULL;
CGame			*CManager::m_pGame = NULL;
CGame2			*CManager::m_pGame2 = NULL;
CResult			*CManager::m_pResult = NULL;
CPause			*CManager::m_pPause = NULL;
CCamera			*CManager::m_pCamera = NULL;
CLight			*CManager::m_pLight = NULL;
CSceneX			*CManager::m_pSceneX = NULL;

//�����̉��
CManager::MODE	CManager::m_mode = MODE_TITLE;

//�o�ߎ��Ԃ�\��������
bool	CManager::m_bEndGame = false;

int		g_nPlayerType = 0;			//�v���C���[�̃^�C�v���L�^
int		g_nPlayerLife = 0;			//�v���C���[�̗̑͂��L�^
int		g_nMaxPlayerLife = 5;		//�ő�̗�

int		nTimeManagr = 0;			//�Q�[���I�[�o�[���ɃJ�E���g����ϐ�
int		g_EnemyDead = 0;			//���{�X��|���������L�^

int		g_nGameStage = 0;			//���݂̃X�e�[�W���

bool	g_bGameOver = false;		//�Q�[���I�[�o�[���g�p
bool	g_bGameOverLogo = false;	//�Q�[���I�[�o�[���g�p

bool	g_bPause = false;			//�|�[�Y���

bool	g_bGameClear = false;		//�N���A����

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CManager::CManager()
{
	//������
	m_pTimeFont = NULL;
	m_dwGameStartTime = 0;
	m_dwGameTime = 0;
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
	
	//�A�j���[�V�����e�N�X�`���̓ǂݍ���
	CAnimasion::Load();

	//�G�t�F�N�g�e�N�X�`���̓ǂݍ���
	CEffect::Load();

	// �e�e�N�X�`���ǂݍ���
	CBullet::Load();

	// �v���C���[�e�N�X�`���ǂݍ���
	CPlayer::Load();

	//�G�̃e�N�X�`��
	CEnemy::Load();

	// ���j�e�N�X�`���̓ǂݍ���
	CExplosion::Load();
	
	// �w�i�e�N�X�`���̓ǂݍ���
	CBg::Load();

	//���S�̃e�N�X�`���̓ǂݍ���
	CLogo::Load();

	//�ԍ��̃e�N�X�`���ǂݍ���
	CNumber::Load();

	//���C�t�̃e�N�X�`���̓ǂݍ���
	CLife::Load();

	//�A�C�e���e�N�X�`���̓ǂݍ���
	CItem::Load();

	//�p�[�e�B�N���̃e�N�X�`���̓ǂݍ���
	CParticl::Load();

	//m_pPause->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f);

	//���[�h�ݒ�
	SetMode(m_mode);

	// �^�C�}�[�̏�����
	InitTime();

	return S_OK;
}

//==============================================================================
// 
//==============================================================================
void CManager::SetMode(MODE mode)
{
	//�I������
	CScene::ReleaseAll();

	//�t�F�[�h���N���G�C�g
	CFade::Create(m_mode);

	//��ʑJ�ڎ��ɏ�����
	nTimeManagr = 0;
	g_nPlayerLife = 0;
	g_bGameOver = false;
	g_bGameOverLogo = false;
	g_bPause = false;

	g_EnemyDead = 0;		//Clear�����̏�����

	switch (mode)
	{
	case MODE_TITLE:

		//�^�C�g����ʂ̏���������
		g_nPlayerLife = 1;		//�Q�[���I�[�o�[�̃��S���o�������Ȃ�
		m_pTitle->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f);
		break;

	case MODE_MENU:

		//�^�C�g����ʂ̏���������
		g_nPlayerLife = 1;		//�Q�[���I�[�o�[�̃��S���o�������Ȃ�
		m_pMenu->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f);
		break;

	case MODE_SELECT:

		//�^�C�g����ʂ̏���������
		g_nPlayerLife = 1;		//�Q�[���I�[�o�[�̃��S���o�������Ȃ�
		m_pSelect->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f);
		break;

	case MODE_TUTORIAL:

		//�^�C�g����ʂ̏���������
		g_nPlayerLife = 1;		//�Q�[���I�[�o�[�̃��S���o�������Ȃ�
		m_pTutorial->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f);
		break;

	case MODE_GAME:
		g_bGameClear = false;

		//�Q�[����ʂ̏���������
		m_pGame->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f);
		m_pPause->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f);
		break;

	case MODE_GAME2:
		g_bGameClear = false;

		//�Q�[����ʂ̏���������
		m_pGame2->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f);
		m_pPause->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f);
		break;

	case MODE_RESULT:

		//�Q�[����ʂ̏���������
		g_nPlayerLife = 1;
		m_pResult->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f);
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
	CBullet::Unload();
	CEffect::Unload();
	CPlayer::Unload();
	CEnemy::Unload();
	CExplosion::Unload();
	CBg::Unload();
	CLogo::Unload();
	CNumber::Unload();
	CLife::Unload();
	CAnimasion::Unload();
	CItem::Unload();
	CParticl::Unload();

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

	// �^�C�}�[�t�H���g�̔j��
	UninitTime();
}

//=============================================================================
// �X�V����
//=============================================================================
void CManager::Update(void)
{
	//�v���C���[�̃��C�t���L��
	int nLifePlayer = CManager::GetPlayerLife();

	//�Q�[���p�b�h�̃|�C���^�錾
	CGamepad *pGamepad;
	pGamepad = CManager::GetGamepad();

	//�J�����̍X�V
	m_pCamera->Update();

	//�Q�[���I�[�o�[��
	if (nLifePlayer <= 0)
	{
		if (g_bGameOverLogo == false)
		{
			CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, CScene::GAMEOVER01);
			g_bGameOverLogo = true;
		}

		nTimeManagr++;

		if (nTimeManagr >= 150)
		{
			if (g_bGameOver == false)
			{
				//���[�h�ݒ�
				CFade::SetFade(CFade::FADE_OUT, CManager::MODE_RESULT, D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f));	// �V�[���J��

				g_bGameOver = true;
			}
		}
	}

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

	// �^�C�}�[�X�V
	UpdateTime();

	////��ʑJ�ځ@�X�L�b�v�@�\
	//if (m_pInputKeyboard->GetTrigger(DIK_0) == true)
	//{
	//	//���[�h�ݒ�
	//	CFade::SetFade(CFade::FADE_OUT, CManager::MODE_TITLE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	// �V�[���J��
	//}

	////�X�e�[�W�X�L�b�v
	//if (m_pInputKeyboard->GetTrigger(DIK_1) == true)
	//{
	//	CFade::SetFade(CFade::FADE_OUT, CManager::MODE_GAME, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	// �V�[���J��
	//}

	//if (m_pInputKeyboard->GetTrigger(DIK_2) == true)
	//{
	//	CFade::SetFade(CFade::FADE_OUT, CManager::MODE_GAME2, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	// �V�[���J��
	//}

	//�Q�[����ʎ��݂̂Ƀ|�[�Y��`�恕�X�V�ł���
	if (CManager::m_mode == MODE_GAME || CManager::m_mode == MODE_GAME2)
	{
		//�|�[�Y�̐؂�ւ��I��
		if (g_bPause == false)
		{
			if (m_pInputKeyboard->GetTrigger(DIK_P) == true || pGamepad->IsButtonDown(CInput::P))
			{
				g_bPause = true;
			}
		}

		//�|�[�Y�̐؂�ւ��I�t
		else if (g_bPause == true)
		{
			if (m_pInputKeyboard->GetTrigger(DIK_P) == true || pGamepad->IsButtonDown(CInput::P))
			{
				g_bPause = false;
			}
		}
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

//==============================================================================
// �^�C�}�[������
//==============================================================================
HRESULT CManager::InitTime(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetRenderer()->GetDevice();

	// �t�H���g�I�u�W�F�N�g�̐���
	D3DXCreateFont(
		pDevice, 36, 0, 0, 0, FALSE,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		"Terminal",
		&m_pTimeFont);

	// �J�n�����擾
	m_dwGameStartTime = timeGetTime();

	return S_OK;
}

//==============================================================================
// �^�C�}�[�X�V
//==============================================================================
void CManager::UninitTime(void)
{
	if (m_pTimeFont != NULL)
	{
		m_pTimeFont->Release();
		m_pTimeFont = NULL;
	}
}

//==============================================================================
// �^�C�}�[�X�V
//==============================================================================
void CManager::UpdateTime(void)
{
	if (m_bEndGame == false)
	{
		// �o�ߎ��ԍX�V
		m_dwGameTime = timeGetTime() - m_dwGameStartTime;
	}
}

//==============================================================================
// �^�C�}�[�`��
//==============================================================================
void CManager::DrawTime(void)
{
#ifdef _DEBUG
	// ���[�J���ϐ��錾
	RECT rect = { 0,30,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	if (m_bEndGame == false)
	{
		//�o�ߎ��Ԃ������o�֐��ɓ����
		m_fTime = (float)m_dwGameTime / 1000;
		
		//��ʂɕ\��������
		sprintf(&aStr[0], "�o�ߎ��� : %.3f\n", m_fTime);

		// �e�L�X�g�̕`��
		m_pTimeFont->DrawText(NULL, &aStr[0], -1, &rect, DT_CENTER, D3DCOLOR_RGBA(255, 255, 255, 255));
	}
#endif
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
// �J�����|�C���^�[��Get�֐�
//=============================================================================
CCamera * CManager::GetCamera(void)
{
	return m_pCamera;
}

//=============================================================================
// Get�֐� & �ϐ��̒l�ۑ�
//=============================================================================
int CManager::GetPlayerLife(void)				//�v���C���[�̗̑͂�Get
{
	return g_nPlayerLife;
}

void CManager::SetPlayerLife(int nLife)			//�v���C���[�̗̑͂�Set
{
	g_nPlayerLife = nLife;
}

void CManager::SetMaxPlayerLife(int nLife)		//�ő�̗͂�Set
{
	g_nMaxPlayerLife = nLife;
}

int CManager::GetMaxPlayerLife(void)			//�ő�̗͂�Get
{
	return g_nMaxPlayerLife;
}

void CManager::DamagePlayerLife(int nLife)		//�̗͂����炷
{
	g_nPlayerLife -= nLife;
}

void CManager::RecoveryPlayerLife(int nLife)	//�̗͂��񕜂�����
{
	g_nPlayerLife += nLife;
}

int CManager::GetPlayerType(void)				//�I�����ꂽ�v���C���[�m�点��
{
	return g_nPlayerType;
}

void CManager::SetPlayerType(int nType)			//�I�����ꂽ�v���C���[���L��
{
	g_nPlayerType = nType;
}

int CManager::GetEnemyDead(void)				//�G��|��������m�点��
{
	return g_EnemyDead;
}

void CManager::SetEnemyDead(int nData)			//�G��|����������
{
	g_EnemyDead = nData;
}

void CManager::AddEnemyDead(int nData)			//�G��|�����������Z
{
	g_EnemyDead += nData;
}

int CManager::GetGameStage(void)				//���݃v���C�����X�e�[�W���L��
{
	return g_nGameStage;
}

void CManager::SetGameStage(int nData)			//���݃v���C���̃X�e�[�W��m�点��
{
	g_nGameStage = nData;
}

bool CManager::GetPause()						//�|�[�Y��Ԃ�m�点��
{
	return g_bPause;
}

bool CManager::GetGameClear(void)				//�N���A��Ԃ��m�点��
{
	return g_bGameClear;
}

void CManager::SetGameClear(bool bData)			//�N���A��Ԃɂ���
{
	g_bGameClear = bData;
}
