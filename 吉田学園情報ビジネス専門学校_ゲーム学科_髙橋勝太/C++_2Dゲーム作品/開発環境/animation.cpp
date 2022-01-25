//=============================================================================
//
// �A�j���[�V�������� [animasion.cpp]
// Author : takahashi shota
//
//=============================================================================

//=============================================================================
//�C���N���[�h�ǂݍ���
//=============================================================================
#include "animation.h"
#include "manager.h"

// �ÓI�����o�ϐ��錾
LPDIRECT3DTEXTURE9 CAnimasion::m_pTexture[MAX_ANIME] = {};
int g_nUninitType;												//�����������^�C�v

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CAnimasion::CAnimasion(int nPriority, int nType) : CScene2D(nPriority, nType)
{
	m_nAnime = 0;
	m_nPatternAnime = 0;
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CAnimasion::~CAnimasion()
{

}

//==============================================================================
// ����������
//==============================================================================
HRESULT CAnimasion::Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nAnime, int nType)
{
	CScene2D::Init(pos, fSizeX, fSizeY);

	//�����o�ϐ��ɑ��
	m_pos = pos;
	m_nType = nType;

	//�A�j���[�V�����̏�����
	CScene2D::SetTex(1, 0, 0);

	//�A�j���[�V�����X�s�[�h
	m_nAnime = nAnime;

	//�e�N�X�`�������󂯓n��
	CAnimasion::Texture(nType);

	//�F�ύX
	if (m_nType == 6 || m_nType == 9 || m_nType == 11 || m_nType == 5 || m_nType == 13)
	{
		//�F�ύX
		CScene2D::SetCollar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	}

	return S_OK;
}

//==============================================================================
// �I������
//==============================================================================
void CAnimasion::Uninit(void)
{
	CScene2D::Uninit();
}

//==============================================================================
// �X�V����
//==============================================================================
void CAnimasion::Update(void)
{
	//�v���C���[�p�A�j���[�V����
	if (m_nType == 6 || m_nType == 9 || m_nType == 11 || m_nType == 5 || m_nType == 13)
	{
		// ���݂̈ʒu�̎擾
		D3DXVECTOR3 pos = CPlayer::GetPlayer();
		D3DXVECTOR3 objective = D3DXVECTOR3(pos.x + m_pos.x, pos.y + m_pos.y, pos.z);

		//�ړ�������
		SetPosition(objective);
	}

	//�r���ύXUninit
	if (m_nType == g_nUninitType)
	{
		m_fCriss = 0;
		m_nAnime = 1;
	}

	//�A�C�e���擾���̃G�t�F�N�g�A�j���[�V����
	if (m_nType == 7 || m_nType == 8)
	{
		// ���݂̈ʒu�̎擾
		D3DXVECTOR3 pos = CPlayer::GetPlayer();

		//�ړ�������
		SetPosition(D3DXVECTOR3(pos.x, pos.y, pos.z));
	}

	//�A�j���[�V�����̍X�V����
	if ((m_nCounterAnime % m_nAnime) == 0)
	{
		//�A�j���[�V�����p�^�[���̍X�V
		m_nPatternAnime = (m_nPatternAnime + 1);

		//�A�j���[�V�����̍X�V
		CScene2D::SetAnime(m_fAnimeX, m_fAnimeY, m_nX, m_nY, m_nPatternAnime);
	}

	//�J�E���^�[��i�߂�
	m_nCounterAnime++;

	//�X�V
	CScene2D::Update();

	//�A�j���[�V�������I�����Z�b�g
	if (m_nPatternAnime == m_nX * m_nY)
	{
		//�J�E���^�[�̃��Z�b�g
		m_nPatternAnime = 0;

		//���[�v�����Ȃ��Ƃ�
		if (m_fCriss == 0)
		{
			//�I�������
			Uninit();
		}
	}
}

//==============================================================================
// �`�揈��
//==============================================================================
void CAnimasion::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	////�A���t�@�e�X�g
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, 0);

	CScene2D::Draw();

	////�A���t�@�e�X�g
	//pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	//pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_ALWAYS);
	//pDevice->SetRenderState(D3DRS_ALPHAREF, 0x00);
}

//==============================================================================
// ��������
//==============================================================================
CAnimasion * CAnimasion::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nAnime, int nType)
{
	//�A�j���[�V�����𐶐�
	CAnimasion *pAnimasion = NULL;
	pAnimasion = new CAnimasion;

	// NULL�`�F�b�N
	if (pAnimasion != NULL)
	{
		pAnimasion->Init(pos, fSizeX, fSizeY, nAnime, nType);
	}

	//�e�N�X�`��������
	pAnimasion->BindTexture(m_pTexture[nType]);

	return pAnimasion;
}

//==============================================================================
// �e�N�X�`���̓ǂݍ���
//==============================================================================
HRESULT CAnimasion::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/hoshihikari.png", &m_pTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/btleffect01.png", &m_pTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/btleffect02.png", &m_pTexture[2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pipo-btleffect120e.png", &m_pTexture[3]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/frame.png", &m_pTexture[4]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/mapeffect01.png", &m_pTexture[5]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect01.png", &m_pTexture[6]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect04.png", &m_pTexture[7]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect02.png", &m_pTexture[8]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/mapeffect02.png", &m_pTexture[9]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg01_title.png", &m_pTexture[10]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect03.png", &m_pTexture[11]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/mapeffect02.png", &m_pTexture[12]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect05.png", &m_pTexture[13]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg01_title.png", &m_pTexture[14]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/mapeffect02.png", &m_pTexture[15]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/mapeffect01.png", &m_pTexture[16]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg02_boss.jpg", &m_pTexture[17]);

	return S_OK;
}

//==============================================================================
// �e�N�X�`���̔j��
//==============================================================================
void CAnimasion::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_ANIME; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

//==============================================================================
// �e�N�X�`�����̊Ǘ�
//==============================================================================
void CAnimasion::Texture(int nType)
{
	//�ǂݍ��񂾃e�N�X�`���̏����L��
	if (nType == 0)
	{
		m_fAnimeX = 1.0f;			//�e�N�X�`������
		m_fAnimeY = 0.05f;			//�e�N�X�`������
		m_nX = 1;
		m_nY = 20;
		m_fCriss = 0;				//���[�v�Ȃ�
	}

	if (nType == 1)
	{
		m_fAnimeX = 0.333f;			//�e�N�X�`������
		m_fAnimeY = 0.333f;			//�e�N�X�`������
		m_nX = 3;
		m_nY = 3;
		m_fCriss = 0;				//���[�v�Ȃ�
	}

	if (nType == 2)
	{
		m_fAnimeX = 1.0f;			//�e�N�X�`������
		m_fAnimeY = 0.1f;			//�e�N�X�`������
		m_nX = 1;
		m_nY = 10;
		m_fCriss = 0;				//���[�v�Ȃ�
	}

	if (nType == 3)
	{
		m_fAnimeX = 0.2f;			//�e�N�X�`������
		m_fAnimeY = 0.166f;			//�e�N�X�`������
		m_nX = 5;
		m_nY = 6;
		m_fCriss = 0;				//���[�v�Ȃ�
	}

	if (nType == 4)
	{
		m_fAnimeX = 0.5f;			//�e�N�X�`������
		m_fAnimeY = 0.2f;			//�e�N�X�`������
		m_nX = 2;
		m_nY = 5;
		m_fCriss = 1;				//���[�v����

									//�F�ύX
		CScene2D::SetCollar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
	}

	if (nType == 5)
	{
		m_fAnimeX = 0.2f;			//�e�N�X�`������
		m_fAnimeY = 0.5f;			//�e�N�X�`������
		m_nX = 5;
		m_nY = 2;
		m_fCriss = 1;				//���[�v����
	}

	if (nType == 6)
	{
		m_fAnimeX = 0.2f;			//�e�N�X�`������
		m_fAnimeY = 0.1666f;		//�e�N�X�`������
		m_nX = 5;
		m_nY = 2;
		m_fCriss = 1;				//���[�v����
	}

	if (nType == 7)
	{
		m_fAnimeX = 0.2f;			//�e�N�X�`������
		m_fAnimeY = 0.3333f;		//�e�N�X�`������
		m_nX = 5;
		m_nY = 3;
		m_fCriss = 0;				//���[�v�Ȃ�
	}

	if (nType == 8)
	{
		m_fAnimeX = 0.2f;			//�e�N�X�`������
		m_fAnimeY = 0.3333f;		//�e�N�X�`������
		m_nX = 5;
		m_nY = 3;
		m_fCriss = 0;				//���[�v�Ȃ�
	}

	if (nType == 9)
	{
		m_fAnimeX = 0.2f;			//�e�N�X�`������
		m_fAnimeY = 0.5f;			//�e�N�X�`������
		m_nX = 5;
		m_nY = 2;
		m_fCriss = 1;				//���[�v����
	}

	if (nType == 10)
	{
		m_fAnimeX = 0.2f;			//�e�N�X�`������
		m_fAnimeY = 0.25f;			//�e�N�X�`������
		m_nX = 5;
		m_nY = 4;
		m_fCriss = 0;				//���[�v�Ȃ�
	}

	if (nType == 11)
	{
		m_fAnimeX = 0.20f;			//�e�N�X�`������
		m_fAnimeY = 0.3333f;			//�e�N�X�`������
		m_nX = 5;
		m_nY = 3;
		m_fCriss = 1;				//���[�v�Ȃ�
	}

	if (nType == 12)
	{
		m_fAnimeX = 0.2f;			//�e�N�X�`������
		m_fAnimeY = 0.5f;			//�e�N�X�`������
		m_nX = 5;
		m_nY = 2;
		m_fCriss = 0;				//���[�v�Ȃ�
	}

	if (nType == 13)
	{
		m_fAnimeX = 0.2f;			//�e�N�X�`������
		m_fAnimeY = 0.1666f;			//�e�N�X�`������
		m_nX = 5;
		m_nY = 6;
		m_fCriss = 1;				//���[�v�Ȃ�
	}

	if (nType == 14)
	{
		m_fAnimeX = 0.2f;			//�e�N�X�`������
		m_fAnimeY = 0.25f;			//�e�N�X�`������
		m_nX = 5;
		m_nY = 4;
		m_fCriss = 0;				//���[�v�Ȃ�
	}

	if (nType == 15)
	{
		m_fAnimeX = 0.2f;			//�e�N�X�`������
		m_fAnimeY = 0.5f;			//�e�N�X�`������
		m_nX = 5;
		m_nY = 2;
		m_fCriss = 1;				//���[�v����
	}

	if (nType == 16)
	{
		m_fAnimeX = 0.2f;			//�e�N�X�`������
		m_fAnimeY = 0.5f;			//�e�N�X�`������
		m_nX = 5;
		m_nY = 2;
		m_fCriss = 1;				//���[�v����
	}

	if (nType == 17)
	{
		m_fAnimeX = 0.5f;			//�e�N�X�`������
		m_fAnimeY = 0.1f;			//�e�N�X�`������
		m_nX = 2;
		m_nY = 10;
		m_fCriss = 1;				//���[�v����
	}
}

//==============================================================================
// �j������^�C�v
//==============================================================================
void CAnimasion::UninitType(int nUninitType)
{
	g_nUninitType = nUninitType;
}

//==============================================================================
// �p�������O���[�o����������
//==============================================================================
void CAnimasion::UninitTypeClear(void)
{
	g_nUninitType = 0;
}

//=============================================================================
//
// ���C������ [animasionbg.cpp]
// Author : takahashi shota
//
//=============================================================================

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CAnimasionBg::CAnimasionBg(int nPriority, int nType) : CAnimasion(nPriority, nType)
{
	m_nAnime = 0;
	m_nPatternAnime = 0;
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CAnimasionBg::~CAnimasionBg()
{

}

//==============================================================================
// ����������
//==============================================================================
HRESULT CAnimasionBg::Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nAnime, int nType)
{
	CScene2D::Init(pos, fSizeX, fSizeY);

	//�����o�ϐ��ɑ��
	m_pos = pos;
	m_nType = nType;

	//�A�j���[�V�����̏�����
	CScene2D::SetTex(1, 0, 0);

	//�A�j���[�V�����X�s�[�h
	m_nAnime = nAnime;

	//�e�N�X�`�������󂯓n��
	CAnimasion::Texture(nType);

	return S_OK;
}

//==============================================================================
// �I������
//==============================================================================
void CAnimasionBg::Uninit(void)
{
	CScene2D::Uninit();
}

//==============================================================================
// �X�V����
//==============================================================================
void CAnimasionBg::Update(void)
{
	//�A���t�@�l�v�Z
	if (m_fColorFa <= 1.0f)
	{
		m_fColorFa += 0.005f;
		CScene2D::SetCollar(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_fColorFa));
	}

	//�A�j���[�V�����̍X�V����
	if ((m_nCounterAnime % m_nAnime) == 0)
	{
		//�A�j���[�V�����p�^�[���̍X�V
		m_nPatternAnime = (m_nPatternAnime + 1);

		//�A�j���[�V�����̍X�V
		CScene2D::SetAnime(m_fAnimeX, m_fAnimeY, m_nX, m_nY, m_nPatternAnime);
	}

	//�J�E���^�[��i�߂�
	m_nCounterAnime++;

	//�X�V
	CScene2D::Update();

	//�A�j���[�V�������I�����Z�b�g
	if (m_nPatternAnime == m_nX * m_nY)
	{
		//�J�E���^�[�̃��Z�b�g
		m_nPatternAnime = 0;

		//���[�v�����Ȃ��Ƃ�
		if (m_fCriss == 0)
		{
			//�I�������
			Uninit();
		}
	}
}

//==============================================================================
// �`�揈��
//==============================================================================
void CAnimasionBg::Draw(void)
{
	CScene2D::Draw();
}

//==============================================================================
// ��������
//==============================================================================
CAnimasionBg * CAnimasionBg::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nAnime, int nType)
{
	//�A�j���[�V�����𐶐�
	CAnimasionBg *pAnimasionBg = NULL;
	pAnimasionBg = new CAnimasionBg;

	// NULL�`�F�b�N
	if (pAnimasionBg != NULL)
	{
		pAnimasionBg->Init(pos, fSizeX, fSizeY, nAnime, nType);
	}

	//�e�N�X�`��������
	pAnimasionBg->BindTexture(m_pTexture[nType]);

	return pAnimasionBg;
}

//==============================================================================
// �r���j������
//==============================================================================
void CAnimasionBg::UninitTypeClear(void)
{
	for (int nCnt = 0; nCnt < MAX_ANIME; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}
