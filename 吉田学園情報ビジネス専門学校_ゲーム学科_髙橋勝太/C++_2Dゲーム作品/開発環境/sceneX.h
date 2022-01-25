//=============================================================================
//
// �V�[��X���� [sceneX.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _SCENEX_H_
#define _SCENEX_H_

#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)

#include "main.h"
#include "scene.h"

//=============================================================================
// �V�[��X�N���X�̒�`
//=============================================================================
class CSceneX : public CScene
{
public:
	CSceneX(int nPriority = 5, int nType = 0);						//�R���X�g���N�^
	virtual ~CSceneX();					//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY);		//����������
	void Uninit(void);												//�I������
	void Update(void);												//�X�V����
	void Draw(void);												//�`�揈��

	static CSceneX *Create();										//��������
																	
private:															
	LPD3DXMESH		m_pMesh;			//���b�V��
	LPD3DXBUFFER	m_pBuffMat;			//�o�b�t�@
	DWORD			m_nNumMat;			//�}�g���b�N�X
	D3DXMATRIX		m_mtxWorld;			//���[���h�}�g���b�N�X
	D3DXVECTOR3		m_pos;				//�ʒu
	D3DXVECTOR3		m_rot;				//����
	int				m_nNumVtx;			//���_��
	float			m_fRot;				//��]��

};

#endif