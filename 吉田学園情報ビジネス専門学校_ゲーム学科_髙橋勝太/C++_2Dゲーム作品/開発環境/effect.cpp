//=============================================================================
//
// �G�t�F�N�g���� [effect.cpp]
// Author : takahashi shota
//
//=============================================================================

//=============================================================================
//�C���N���[�h�ǂݍ���
//=============================================================================
#include "effect.h"
#include "manager.h"

// �ÓI�����o�ϐ��錾
LPDIRECT3DTEXTURE9 CEffect::m_pTexture = NULL;

//=============================================================================
// �C���X�g���N�^
//=============================================================================
CEffect::CEffect(int nPriority) : CScene2D(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CEffect::~CEffect()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CEffect::Init(D3DXVECTOR3 pos, int nLife, float fSizeX, float fSizeY, D3DXCOLOR col)
{
	// CScene2D�̏���������
	CScene2D::Init(pos, fSizeX, fSizeY);

	//�����o�ϐ��ɑ��
	m_nLife = nLife;
	m_col = col;

	//�F����`����
	SetEffect(col,1);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEffect::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CEffect::Update(void)
{
	// ���݂̈ʒu�̎擾
	D3DXVECTOR3 pos = GetPosition();

	//�X�V
	CScene2D::Update();

	//�G�t�F�N�g�����񂾂񓧖��ɂ���
	SetEffect(m_col, m_nLife);
	
	//�G�t�F�N�g�̃��C�t�����炷
	m_nLife--;

	//�G�t�F�N�g���C�t��0�ȉ��ɂȂ����Ƃ�
	if (m_nLife <= 0)
	{
		Uninit();
	}

	//�͈͊O�̏ꍇ
	else if (pos.y <= 0)
	{
		Uninit();
	}
	else if (pos.y >= SCREEN_HEIGHT)
	{
		Uninit();
	}
	else if (pos.x <= 0)
	{
		Uninit();
	}
	else if (pos.x >= SCREEN_WIDTH)
	{
		Uninit();
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CEffect::Draw(void)
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//���Z����
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CScene2D::Draw();

	//���Z�������O��
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// ��������
//=============================================================================
CEffect * CEffect::Create(D3DXVECTOR3 pos, int nLife, float fSizeX, float fSizeY, D3DXCOLOR col)
{
	//�G�t�F�N�g�𐶐�
	CEffect *pEffect = NULL;
	pEffect = new CEffect;

	pEffect->Init(pos, nLife, fSizeX, fSizeY , col);

	//�e�N�X�`��������
	pEffect->BindTexture(m_pTexture);

	return pEffect;
}

//=============================================================================
// �e�N�X�`���̐���
//=============================================================================
HRESULT CEffect::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect000.jpg", &m_pTexture);

	return S_OK;
}

//=============================================================================
// �e�N�X�`���̔j��
//=============================================================================
void CEffect::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}