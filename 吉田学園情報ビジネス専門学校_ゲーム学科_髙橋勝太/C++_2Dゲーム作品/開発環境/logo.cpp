//=============================================================================
//
// ���S���� [logo.cpp]
// Author : takahashi shota
//
//=============================================================================

//=============================================================================
//�C���N���[�h�ǂݍ���
//=============================================================================
#include "logo.h"
#include "manager.h"
#include "scene2D.h"
#include "scene.h"

// �ÓI�����o�ϐ��錾
LPDIRECT3DTEXTURE9 CLogo::m_apTextureLogo[MAX_LOGO] = {};
CPlayer *CLogo::m_pPlayer = NULL;

//�O���[�o���錾
int g_nTypeLogo = -1;			//���ꏈ��������^�C�v������
int g_nTypeMoveLogo = -1;		//���ꏈ��������^�C�v������
int g_nTypeCollarLogo = -1;		//���ꏈ��������^�C�v������
D3DXVECTOR3 g_posLogo;			//�ʒu
D3DXCOLOR g_col;				//�F���

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLogo::CLogo(int nPriority, int nType) : CScene2D(nPriority, nType)
{
	
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLogo::~CLogo()
{
	g_nTypeLogo = -1;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CLogo::Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nType)
{
	// CScene2D�̏���������
	CScene2D::Init(pos, fSizeX, fSizeY);

	//�^�C�v����
	m_nType = nType;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CLogo::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CLogo::Update(void)
{	
	//����X�V
	//�^�C�g���ړ�
	if (m_nType == TITLE_UI)
	{
		// ���݂̈ʒu�̎擾
		D3DXVECTOR3 pos = GetPosition();

		//�ړ�������
		SetPosition(pos);

		//�X�V
		CScene2D::Update();
	}

	//�v���C���[�����蔻��̈ړ�
	if (m_nType == PLAYER_COLLISION_PINTER)
	{
		//�F��ς���
		CScene2D::SetCollar(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));

		//�v���C���[�̈ʒu���擾
		D3DXVECTOR3 posPlayer = m_pPlayer->GetPlayer();

		//�ړ�������
		SetPosition(posPlayer);

		//�X�V
		CScene2D::Update();
	}

	//����X�V
	if (m_nType == FRAME)
	{
		//�F��ς���
		CScene2D::SetCollar(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	}

	//�r���F�ύX
	if (m_nType == g_nTypeCollarLogo)
	{
		//�F��ς���
		CScene2D::SetCollar(g_col);
	}

	//�r���ړ�
	if (m_nType == g_nTypeMoveLogo)
	{
		//������
		g_nTypeMoveLogo = -1;

		//�ړ�������
		SetPosition(g_posLogo);

		//�X�V
		CScene2D::Update();
	}
	
	//�r���j��
	if (g_nTypeLogo == m_nType)
	{
		Uninit();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CLogo::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// ��������
//=============================================================================
CLogo * CLogo::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nType)
{
	// ���[�J���ϐ��錾
	CLogo *pLogo = NULL;
	pLogo = new CLogo;

	// ������
	if (pLogo != NULL)
	{
		//���S����
		pLogo->Init(pos, fSizeX, fSizeY , nType);
	}

	// �e�N�X�`�����蓖��
	pLogo->BindTexture(m_apTextureLogo[nType]);

	return pLogo;
}

//=============================================================================
// �e�N�X�`���̓ǂݍ���
//=============================================================================
HRESULT CLogo::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���	
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/frame001a.png", &m_apTextureLogo[FRAME]);

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg100.png", &m_apTextureLogo[BG01]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg101.png", &m_apTextureLogo[BG02]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg102.png", &m_apTextureLogo[BG03]);

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/title01.png", &m_apTextureLogo[TITLE_UI]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/press_enter.png", &m_apTextureLogo[TITLE_UI_PRESS_ENTER]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/logo_game.jpg", &m_apTextureLogo[TITLE_UI_GAMESTART]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/logo_�������.jpg", &m_apTextureLogo[TITLE_UI_TUTORIAL]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/logo_�I��.jpg", &m_apTextureLogo[TITLE_UI_END]);

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bullet000.png", &m_apTextureLogo[PLAYER_COLLISION_PINTER]);

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_01.png", &m_apTextureLogo[PLAYER01]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_02.png", &m_apTextureLogo[PLAYER02]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_03.png", &m_apTextureLogo[PLAYER03]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_04.png", &m_apTextureLogo[PLAYER04]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_05.png", &m_apTextureLogo[PLAYER05]);

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/status1.jpg", &m_apTextureLogo[SELECT_PLAYER01_STATUS]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/status2.jpg", &m_apTextureLogo[SELECT_PLAYER02_STATUS]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/status3.jpg", &m_apTextureLogo[SELECT_PLAYER03_STATUS]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/status4.jpg", &m_apTextureLogo[SELECT_PLAYER04_STATUS]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/status5.jpg", &m_apTextureLogo[SELECT_PLAYER05_STATUS]);
	
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_04_status.png", &m_apTextureLogo[SELECT_PLAYER01_STATUS2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_02_status.png", &m_apTextureLogo[SELECT_PLAYER02_STATUS2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_04_status.png", &m_apTextureLogo[SELECT_PLAYER03_STATUS2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_04_status.png", &m_apTextureLogo[SELECT_PLAYER04_STATUS2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_05_status.png", &m_apTextureLogo[SELECT_PLAYER05_STATUS2]);

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/keyboard.jpg", &m_apTextureLogo[TUTORIAL_KEYBOARD]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/gamepad.jpg", &m_apTextureLogo[TUTORIAL_GAMEPAD]);

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/gemeclear.png", &m_apTextureLogo[GAMECLEAR01]);

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/gameover.png", &m_apTextureLogo[GAMEOVER01]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/gameover1.jpg", &m_apTextureLogo[GAMEOVER_RESTART]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/gameover2.jpg", &m_apTextureLogo[GAMEOVER_START]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/gameover3.jpg", &m_apTextureLogo[GAMEOVER_END]);

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pause.png", &m_apTextureLogo[PAUSE01]);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̔j��
//=============================================================================
void CLogo::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_LOGO; nCnt++)
	{
		if (m_apTextureLogo != NULL)
		{
			m_apTextureLogo[nCnt]->Release();
			m_apTextureLogo[nCnt] = NULL;
		}
	}
}

//=============================================================================
// �j���������^�C�v
//=============================================================================
void CLogo::TypeUninit(int nType)
{
	g_nTypeLogo = nType;
}

//=============================================================================
// �ʒu�����炵�����^�C�v
//=============================================================================
void CLogo::TypeMove(D3DXVECTOR3 pos, int nTypeMove)
{
	g_posLogo = pos;
	g_nTypeMoveLogo = nTypeMove;
}

//=============================================================================
// �w�肵���^�C�v�̐F��ς���
//=============================================================================
void CLogo::TypeChangeCollar(D3DXCOLOR col, int nTypeCollar)
{
	g_nTypeCollarLogo = nTypeCollar;
	g_col = col;
}

//=============================================================================
//
// ���C������ [logopause.cpp]
// Author : takahashi shota
//
//=============================================================================

//�|�[�Y��ʂɕ\�����������ꍇ

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CLogoPause::CLogoPause(int nPriority, int nType) : CLogo(nPriority, nType)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLogoPause::~CLogoPause()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CLogoPause::Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nType)
{
	CScene2D::Init(pos, fSizeX, fSizeY);

	CLogoPause::m_nType = nType;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CLogoPause::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CLogoPause::Update(void)
{
	//����X�V
	//�^�C�g���ړ�
	if (m_nType == 0)
	{
		// ���݂̈ʒu�̎擾
		D3DXVECTOR3 pos = GetPosition();

		//�ړ�������
		SetPosition(pos);

		//�X�V
		CScene2D::Update();
	}

	//�v���C���[������|�C���^�[����̈ړ�
	if (m_nType == 5)
	{
		//�F��ς���
		CScene2D::SetCollar(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));

		//�v���C���[�̈ʒu���擾
		D3DXVECTOR3 posPlayer = m_pPlayer->GetPlayer();

		//�ړ�������
		SetPosition(posPlayer);

		//�X�V
		CScene2D::Update();
	}

	if (m_nType == 9)
	{
		//�F��ς���
		CScene2D::SetCollar(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	}

	if (m_nType == g_nTypeCollarLogo)
	{
		//�F��ς���
		CScene2D::SetCollar(g_col);
	}

	//�r���ړ�
	if (m_nType == g_nTypeMoveLogo)
	{
		//������
		g_nTypeMoveLogo = -1;

		//�ړ�������
		SetPosition(g_posLogo);

		//�X�V
		CScene2D::Update();
	}

	//�r���I��
	if (g_nTypeLogo == m_nType)
	{
		Uninit();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CLogoPause::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// ��������
//=============================================================================
CLogoPause * CLogoPause::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nType)
{
	// ���[�J���ϐ��錾
	CLogoPause *pLogoPause = NULL;
	pLogoPause = new CLogoPause;

	// ������
	if (pLogoPause != NULL)
	{
		pLogoPause->Init(pos, fSizeX, fSizeY, nType);
	}

	// �e�N�X�`�����蓖��
	pLogoPause->BindTexture(m_apTextureLogo[nType]);

	return pLogoPause;
}

//=============================================================================
// �e�N�X�`���̔j��
//=============================================================================
void CLogoPause::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_LOGO; nCnt++)
	{
		if (m_apTextureLogo != NULL)
		{
			m_apTextureLogo[nCnt]->Release();
			m_apTextureLogo[nCnt] = NULL;
		}
	}
}

//=============================================================================
// �j���������^�C�v
//=============================================================================
void CLogoPause::TypeUninit(int nType)
{
	g_nTypeLogo = nType;
}

//=============================================================================
// �ʒu�����炵�����^�C�v
//=============================================================================
void CLogoPause::TypeMove(D3DXVECTOR3 pos, int nTypeMove)
{
	g_posLogo = pos;
	g_nTypeMoveLogo = nTypeMove;
}

//=============================================================================
// �F��ς������^�C�v
//=============================================================================
void CLogoPause::TypeChangeCollar(D3DXCOLOR col, int nTypeCollar)
{
	g_nTypeCollarLogo = nTypeCollar;
	g_col = col;
}
