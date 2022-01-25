//=============================================================================
//
// �p�[�e�B�N������ [particl.cpp]
// Author : takahashi shota
//
//=============================================================================

//=============================================================================
//�C���N���[�h�ǂݍ���
//=============================================================================
#include "particle.h"
#include "effect.h"
#include "manager.h"

// �ÓI�����o�ϐ��錾
LPDIRECT3DTEXTURE9 CParticl::m_pTexture = NULL;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CParticl::CParticl(int nPriority)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CParticl::~CParticl()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CParticl::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int nLife, float fSpeed, float fSizeX, float fSizeY, float fAngle)
{
	// CScene2D�̏���������
	CScene2D::Init(pos, fSizeX, fSizeY);

	//�����o�ϐ��ɑ��
	m_move = move;
	m_nLife = nLife;
	m_fSizeX = fSizeX;
	m_fSizeY = fSizeY;

	//�F��������
	SetEffect(col, 1);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CParticl::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CParticl::Update(void)
{
	//�X�V
	CScene2D::Update();

	// ���݂̈ʒu�̎擾
	D3DXVECTOR3 pos = GetPosition();

	//�ړ�����
	pos += m_move;

	//�ړ�������
	SetPosition(pos);

	//�e�̃��C�t��0�ȉ��ɂȂ����Ƃ�
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

	//�̗͌���
	m_nLife -= 1;
}

//=============================================================================
// �`�揈��
//=============================================================================
void CParticl::Draw(void)
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
CParticl * CParticl::Create(D3DXVECTOR3 pos, D3DXCOLOR col, int nLife, float fSpeed, float fSizeX, float fSizeY, float fAngle)
{
	//�p�[�e�B�N�𐶐�
	CParticl *pParticl = NULL;
	pParticl = new CParticl;

	//�p�[�e�B�N�̗���
	D3DXVECTOR3 move;
	float fA;
	fA = (float)(fAngle) / 100.0f;
	move.x = sinf(fA) * fSpeed;
	move.y = cosf(fA) * fSpeed;

	//�e�N�X�`��������
	pParticl->BindTexture(m_pTexture);

	//�������̈ړ�
	pParticl->Init(pos, move, col, nLife, fSpeed, fSizeX, fSizeY, fAngle);

	return pParticl;
}

//=============================================================================
// �e�N�X�`���̐���
//=============================================================================
HRESULT CParticl::Load(void)
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
void CParticl::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}