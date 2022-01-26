//==============================================================================
//
// �V�[��3D����[Scene3D.h]
// Author; takahashi syota
//
//==============================================================================

#ifndef _SCENE3D_H_
#define _SCENE3D_H_

//==============================================================================
// �}�N����`
//==============================================================================
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)

//==============================================================================
//�C���N���[�h�ǂݍ���
//==============================================================================
#include "main.h"
#include "Scene.h"

//==============================================================================
//�V�[��3D�N���X�̒�`
//==============================================================================
class CScene3D : public CScene
{
public:
	CScene3D(); //�R���X�g���N�^
	~CScene3D();//�f�X�g���N�^
	
	HRESULT Init(D3DXVECTOR3 pos, float fHight, float fWidth);       //����������
	void Uninit(void);												//�I������
	void Update(void);												//�X�V����
	void Draw(void);												//�`�揈��
	
	D3DXVECTOR3 GetPosition(void) { return m_pos; }
	static CScene3D *Create(D3DXVECTOR3 pos);

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;  //���_���
	LPDIRECT3DTEXTURE9 m_pTexture;		 //�e�N�X�`�����
	D3DXMATRIX m_mtxWorld;               //���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;                   //�ʒu���
	D3DXVECTOR3 m_Rot;                   //��]���
	D3DXCOLOR m_col;                     //�J���[�ݒ�
};
#endif
