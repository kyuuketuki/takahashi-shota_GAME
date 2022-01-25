//=============================================================================
//
// �G�t�F�N�g���� [effect.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"
#include "scene2D.h"

//�}�N����`
#define EFFECT_SIZE (10)

//=============================================================================
// �G�t�F�N�g�N���X�̒�`
//=============================================================================
class CEffect : public CScene2D
{
public:
	CEffect(int nPriority = 3);				//�R���X�g���N�^
	virtual ~CEffect();						//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, int nLife, float fSizeX, float fSizeY, D3DXCOLOR col);				  //����������
	void Uninit(void);																					  //�I������
	void Update(void);																					  //�X�V����
	void Draw(void);																					  //�`�揈��

	static CEffect *Create(D3DXVECTOR3 pos, int nLife, float fSizeX, float fSizeY, D3DXCOLOR col);		  //��������
	static HRESULT Load(void);																			  //�e�N�X�`���ǂݍ���
	static void Unload(void);																			  //�e�N�X�`���j��

private:
	D3DXVECTOR3 m_move;						//�ړ���
	D3DXCOLOR	m_col;						//�F
	int			m_nLife;					//���C�t
	float		m_fSizeX;					//�T�C�Y
	float		m_fSizeY;					//�T�C�Y

	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���̃|�C���^
};

#endif