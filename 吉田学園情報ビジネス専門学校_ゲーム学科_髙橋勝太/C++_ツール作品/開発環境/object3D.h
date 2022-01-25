//=============================================================================
//
// �I�u�W�F�N�g3D���� [object3D.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

//=============================================================================
//�C���N���[�h�ǂݍ���
//=============================================================================
#include "scene.h"

//�O���錾
class CScene3D;

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_OBJECT_3D	(256)		// �ő吔

//=============================================================================
// �I�u�W�F�N�g3D�N���X�̒�`
//=============================================================================
class CObject3D : public CScene
{
public:
	CObject3D(int nPriority = 0, int nType = 0);								//�R���X�g���N�^
	virtual ~CObject3D();														//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY);					//����������
	void Uninit(void);															//�I������
	void Update(void);															//�X�V����
	void Draw(void);															//�`�揈��

	static CObject3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);		//��������

	//�����蔻��
	bool CollisionVec(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidthMax, float fWidthMin, float fDepthMax, float fDepthMin, float fHeightMax, float fHeightMin);
	
	//���[���h�}�g���b�N�X�󂯓n��
	D3DXMATRIX GetMtxWorld(void);

	//�A�h���X�̎󂯓n��
	static CScene3D *GetScene3D(int nCnt) { return m_pScene3D[nCnt]; }

	//�󂯓n���p
	static int		GetNumberObject3D(void);
	static int		GetNumber2Object3D(void);
	static float	GetAtan2Object3D(void);

private:
	LPD3DXMESH		m_pMesh;				//���b�V��
	LPD3DXBUFFER	m_pBuffMat;				//�o�b�t�@
	DWORD			m_nNumMat;				//�}�g���b�N�X
	D3DXVECTOR3		m_pos;					//�ʒu
	D3DXVECTOR3		m_posold;				//�ʒu�t���[���O�̈ʒu
	D3DXVECTOR3		m_CollisionVecPos[4];	//���Ă蔻��p�x�N�g��
	D3DXVECTOR3		m_move;					//�ʒu
	D3DXVECTOR3		m_rot;					//�ʒu
	D3DXVECTOR3     m_vtx;					//���_���W�̑��
	D3DXVECTOR3		m_MaxSize;				//�ő�l���L��
	D3DXVECTOR3		m_MinSize;				//�ŏ��l���L��
	D3DXVECTOR3		m_aPos[4];				//�ʒu���̌v�Z�p
	D3DXVECTOR3		m_Vec[4];				//�x�N�g���̌v�Z�p
	int				m_nNumVtx;				//���_��
	int				m_nCntNumber;			//�����J�E���g
	int				m_nCnt;					//�v�Z��ɉ�������p
	float			m_fLength;				//�Ίp���̒���
	float			m_fAngle;				//�Ίp���̊p�x
	float			m_fLength2;				//�Ίp���̒���
	bool			m_bUse;					//�����v�Z��ɕ\��������悤

	//�ÓI�ϐ�
	static D3DXMATRIX		m_mtxWorld;						//���[���h�}�g���b�N�X
	static D3DXVECTOR3		m_rotStatic;					//�ÓI�����o�ϐ��@����
	static D3DXVECTOR3		m_moveStatic;					//�ÓI�����o�ϐ��@�ړ���
	static int				m_nType;						//�ÓI�����o�ϐ��@�^�C�v
	static CScene3D			*m_pScene3D[256];				//�A�h���X�ۑ��p�|�C���^
	static char				*m_pTextName;					//�e�N�X�`���ǂݍ���
};

#endif