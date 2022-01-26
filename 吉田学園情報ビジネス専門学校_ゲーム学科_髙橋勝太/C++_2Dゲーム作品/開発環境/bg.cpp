//=============================================================================
//
// �o�b�N�e�N�X�`������ [bg.cpp]
// Author : takahashi shota
//
//=============================================================================

//=============================================================================
//�C���N���[�h�ǂݍ���
//=============================================================================
#include "bg.h"
#include "manager.h"
#include "scene2D.h"
#include "scene.h"

// �ÓI�����o�ϐ��錾
LPDIRECT3DTEXTURE9 CBg::m_apTexture[MAX_BG] = {};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CBg::CBg(int nPriority) : CScene(nPriority)
{
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		m_apScene2D[nCnt] = NULL;
	}
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CBg::~CBg()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBg::Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	// �ϐ��̏�����
	m_pos = pos;

	//�ꖇ�ڂ̔w�i
	m_apScene2D[0] = new CScene2D;
	m_apScene2D[0]->Init(pos , fSizeX, fSizeY);
	m_apScene2D[0]->BindTexture(m_apTexture[0]);

	//�񖇖ڂ̔w�i
	m_apScene2D[1] = new CScene2D;
	m_apScene2D[1]->Init(pos, fSizeX, fSizeY);
	m_apScene2D[1]->BindTexture(m_apTexture[1]);

	//�O���ڂ̔w�i
	m_apScene2D[2] = new CScene2D;
	m_apScene2D[2]->Init(pos, fSizeX, fSizeY);
	m_apScene2D[2]->BindTexture(m_apTexture[2]);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBg::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		m_apScene2D[nCnt]->Uninit();
		m_apScene2D[nCnt] = NULL;
	}

	// �I�u�W�F�N�g�j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CBg::Update(void)
{
	for (int nCntBg = 0; nCntBg < MAX_BG; nCntBg++)
	{
		//�w�i�𓮂������x
		m_nCntAnime -= 0.0005f;

		//����
		if (m_nCntAnime <= -1.0f)
		{
			m_nCntAnime = 0.0f;
		}

		//�w�i�𓮂�������
		m_apScene2D[nCntBg]->SetBg(m_nCntAnime * (nCntBg + 1));
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CBg::Draw(void)
{
	for (int nCntBg = 0; nCntBg < MAX_BG; nCntBg++)
	{
		// CScene2D�̕`�揈��
		m_apScene2D[nCntBg]->Draw();
	}
}

//=============================================================================
// ��������
//=============================================================================
CBg * CBg::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	// �|�C���^�ϐ��̐���
	CBg *pBg;
	pBg = new CBg;

	// NULL�`�F�b�N
	if (pBg != NULL)
	{
		//�w�i�̐���
		pBg->Init(pos, fSizeX, fSizeY);
	}

	return pBg;
}

//=============================================================================
// �e�N�X�`���ǂݍ���
//=============================================================================
HRESULT CBg::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg101.png", &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg101.png", &m_apTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg102.png", &m_apTexture[2]);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���j��
//=============================================================================
void CBg::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		if (m_apTexture != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}
