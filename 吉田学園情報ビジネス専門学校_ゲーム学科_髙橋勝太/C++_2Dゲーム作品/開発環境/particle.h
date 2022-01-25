//=============================================================================
//
// �p�[�e�B�N���� [particl.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _PARTICL_H_
#define _PARTICL_H_

//==============================================================================
//�C���N���[�h
//==============================================================================
#include "main.h"
#include "scene2D.h"

//�}�N����`
#define PARTICL_SIZE (10)

//=============================================================================
// �p�[�e�B�N���N���X�̒�`
//=============================================================================
class CParticl : public CScene2D
{
public:
	CParticl(int nPriority = 4);				//�R���X�g���N�^
	virtual ~CParticl();						//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int nLife, float fSpeed, float fSizeX, float fSizeY, float fAngle);	//����������
	void Uninit(void);																													//�I������
	void Update(void);																													//�X�V����
	void Draw(void);																													//�`�揈��

	static CParticl *Create(D3DXVECTOR3 pos, D3DXCOLOR col, int nLife, float fSpeed, float fSizeX, float fSizeY, float fAngle);			//��������
	static HRESULT Load(void);																											//�e�N�X�`���ǂݍ���
	static void Unload(void);																											//�e�N�X�`���j��

private:
	D3DXVECTOR3 m_pos;							//�ʒu
	D3DXVECTOR3 m_move;							//�ړ���
	D3DXCOLOR	m_col;							//�J���[
	int			m_nLife;						//���C�t
	float		m_fSpeed;						//���x
	float		m_fSizeX;						//�T�C�Y
	float		m_fSizeY;						//�T�C�Y

	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���̃|�C���^
};

#endif