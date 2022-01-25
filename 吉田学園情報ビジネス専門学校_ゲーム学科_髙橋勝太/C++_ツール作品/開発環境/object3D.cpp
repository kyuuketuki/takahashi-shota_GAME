//=============================================================================
//
// �I�u�W�F�N�g3D�̏��� [object3D.cpp]
// Author : takahashi shota
//
//=============================================================================

//=============================================================================
//�C���N���[�h�ǂݍ���
//=============================================================================
#include "object3D.h"
#include "manager.h"
#include "scene3D.h"
#include "textobject.h"

//�ÓI�����o�ϐ��錾
D3DXVECTOR3		CObject3D::m_rotStatic = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//��]��
D3DXMATRIX      CObject3D::m_mtxWorld;										//�󂯓n���p���[���h�}�g���b�N�X
CScene3D		*CObject3D::m_pScene3D[256] = {};							//�󂯓n���p�A�h���X
int				CObject3D::m_nType;											//X�t�@�C��Type�Ő؂�ւ�

//�󂯓n���\���p
int g_nCntObject3D;									//�����ԍ��̕\���p
int g_FailCntObject3D;								//�����J�E���g
int g_nCntVecObject3D;								//�x�N�g���ԍ��̕\���p
float g_fAtan2Object3D;								//�p�x�\���̕\���p

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CObject3D::CObject3D(int nPriority, int nType)
{
	//�����ԍ�
	m_nCntNumber = g_FailCntObject3D;
	g_FailCntObject3D++;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CObject3D::~CObject3D()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CObject3D::Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(CTextobject::GetTextName(m_nType), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat, NULL, &m_nNumMat, &m_pMesh);

	//�ʒu
	m_pos = pos;
	
	//����
	m_rot = m_rotStatic;
	
	int nNumVtx;			//���_��
	BYTE *pVtxBuff;			//���_�o�b�t�@�ւ̃|�C���^
	DWORD sizeFVF;			//���_�t�H�[�}�b�g�̃T�C�Y

	//���_�����L��
	nNumVtx = m_pMesh->GetNumVertices();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//���_�o�b�t�@�̃��b�N
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		m_vtx = *(D3DXVECTOR3*)pVtxBuff;			//���_���W�̑��

		if (m_vtx.x > m_MaxSize.x)
		{
			m_MaxSize.x = m_vtx.x;
		}

		if (m_vtx.x < m_MinSize.x)
		{
			m_MinSize.x = m_vtx.x;
		}

		if (m_vtx.y > m_MaxSize.y)
		{
			m_MaxSize.y = m_vtx.y;
		}

		if (m_vtx.y < m_MinSize.y)
		{
			m_MinSize.y = m_vtx.y;
		}

		if (m_vtx.z > m_MaxSize.z)
		{
			m_MaxSize.z = m_vtx.z;
		}

		if (m_vtx.z < m_MinSize.z)
		{
			m_MinSize.z = m_vtx.z;
		}

		pVtxBuff += sizeFVF;			//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
	}
	
	m_pMesh->UnlockVertexBuffer();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CObject3D::Uninit(void)
{
	//�����ԍ������炷
	g_FailCntObject3D--;

	//NULL�`�F�b�N
	if (m_pScene3D[m_nCntNumber] != NULL)
	{
		//�������I�������
		m_pScene3D[m_nCntNumber]->Uninit();
	}

	//�I�u�W�F�N�g�̔j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CObject3D::Update(void)
{
	
}

//=============================================================================
// �`�揈��
//=============================================================================
void CObject3D::Draw(void)
{
	//���[�J��
	D3DXMATRIX mtxRot, mtxTrans, revmat;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;					//���݂̃}�e���A���ۑ�
	D3DXMATERIAL *pMat;						//�}�e���A���ւ̃|�C���^

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����̔��]
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�̔��]
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	if (m_MaxSize.x < 0.0f)
	{
		m_MaxSize.x *= -1.0f;
	}
	if (m_MaxSize.y < 0.0f)
	{
		m_MaxSize.y *= -1.0f;
	}
	if (m_MaxSize.z < 0.0f)
	{
		m_MaxSize.z *= -1.0f;
	}

	if (m_MinSize.x < 0.0f)
	{
		m_MinSize.x *= -1.0f;
	}
	if (m_MinSize.y < 0.0f)
	{
		m_MinSize.y *= -1.0f;
	}
	if (m_MinSize.z < 0.0f)
	{
		m_MinSize.z *= -1.0f;
	}

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���݂̃}�e���A���̎擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^�擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);

		//���f���p�[�c�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	//�ۑ������}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// ��������
//=============================================================================
CObject3D * CObject3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)
{
	//���f���𐶐�
	CObject3D *pObject3D = NULL;
	pObject3D = new CObject3D;

	//NULL�`�F�b�N
	if (pObject3D != NULL)
	{
		m_nType = nType;
		m_rotStatic = rot;
		pObject3D->Init(pos, 0.0f, 0.0f);
	}

	return pObject3D;
}

//==============================================================================
// �O�ς𗘗p���������蔻��
//==============================================================================
bool CObject3D::CollisionVec(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidthMax, float fWidthMin, float fDepthMax, float fDepthMin, float fHeightMax, float fHeightMin)
{
	// ���[�J���ϐ�
	CCamera *pCamera = CManager::GetCamera();	// �J�������̎擾
	D3DXVECTOR3 rot = pCamera->GetRot();		// �J�����p�x
	D3DXVECTOR3 CameraPos = pCamera->GetposV();	// �J�����̈ʒu
	bool bLand = false;

	D3DXVECTOR3		g_Vec[4];			// �x�N�g��
	D3DXVECTOR3		g_oldVec[4];		// �O�̃x�N�g��
	D3DXVECTOR3		posold;				// �O�̈ʒu
	float			PlayerVec[4];		// �v���C���[�x�N�g��
	float			oldPlayerVec[4];	// �O�̃v���C���[�x�N�g��

	D3DXVECTOR3 pos = *pPos;			// ����Ώۂ̈ʒu
	posold = *pPosOld;					// ����Ώۂ̈ʒu

	//�ǂ���x�N�g���v�Z�p
	D3DXVECTOR3 VecP = *pPos - *pPosOld;						// �i�s�x�N�g��
	fabsf(VecP.x);												// ��Βl
	fabsf(VecP.z);												// ��Βl
	D3DXVec3Normalize(&VecP, &VecP);

	//aPos�̒l�ݒ�
	m_aPos[0] = D3DXVECTOR3(m_pos.x - m_MinSize.x, 0.0f, m_pos.z - m_MinSize.z);
	m_aPos[1] = D3DXVECTOR3(m_pos.x - m_MinSize.x, 0.0f, m_pos.z + m_MaxSize.z);
	m_aPos[2] = D3DXVECTOR3(m_pos.x + m_MaxSize.x, 0.0f, m_pos.z + m_MaxSize.z);
	m_aPos[3] = D3DXVECTOR3(m_pos.x + m_MaxSize.x, 0.0f, m_pos.z - m_MinSize.z);

	// �Ίp���̐ݒ�
	float fLength[4];
	fLength[0] = sqrtf(m_MinSize.x * m_MinSize.x + m_MinSize.z * m_MinSize.z);
	fLength[1] = sqrtf(m_MinSize.x * m_MinSize.x + m_MaxSize.z * m_MaxSize.z);
	fLength[2] = sqrtf(m_MaxSize.x * m_MaxSize.x + m_MaxSize.z * m_MaxSize.z);
	fLength[3] = sqrtf(m_MaxSize.x * m_MaxSize.x + m_MinSize.z * m_MinSize.z);

	float fAngle[4];
	fAngle[0] = atan2f(m_MinSize.x, m_MinSize.z);
	fAngle[1] = atan2f(m_MinSize.x, m_MaxSize.z);
	fAngle[2] = atan2f(m_MaxSize.x, m_MaxSize.z);
	fAngle[3] = atan2f(m_MaxSize.x, m_MinSize.z);

	//���_�̍��W
	m_aPos[0].x = (m_pos.x + sinf(fAngle[1] + m_rot.y) * fLength[2]);
	m_aPos[0].z = (m_pos.z + cosf(fAngle[1] + m_rot.y) * fLength[2]);

	m_aPos[1].x = (m_pos.x + sinf(fAngle[2] - m_rot.y) * fLength[3]);
	m_aPos[1].z = (m_pos.z - cosf(fAngle[2] - m_rot.y) * fLength[3]);

	m_aPos[2].x = (m_pos.x - sinf(fAngle[3] + m_rot.y) * fLength[0]);
	m_aPos[2].z = (m_pos.z - cosf(fAngle[3] + m_rot.y) * fLength[0]);

	m_aPos[3].x = (m_pos.x - sinf(fAngle[0] - m_rot.y) * fLength[1]);
	m_aPos[3].z = (m_pos.z + cosf(fAngle[0] - m_rot.y) * fLength[1]);

	//���ѕ���������
	//90����Ă���ꍇ
	if (m_aPos[0].x > m_aPos[2].x && m_aPos[0].z < m_aPos[2].z)
	{
		D3DXVECTOR3 vecold;
		vecold = m_aPos[0];

		m_aPos[0] = m_aPos[3];
		m_aPos[3] = m_aPos[2];
		m_aPos[2] = m_aPos[1];
		m_aPos[1] = vecold;
	}
	//180����Ă���ꍇ
	else if (m_aPos[0].x < m_aPos[2].x && m_aPos[0].z < m_aPos[2].z)
	{
		D3DXVECTOR3 vecold;
		vecold = m_aPos[0];

		D3DXVECTOR3 vecold2;
		vecold2 = m_aPos[1];

		m_aPos[0] = m_aPos[2];
		m_aPos[2] = vecold;
		m_aPos[1] = m_aPos[3];
		m_aPos[3] = vecold2;
	}
	//270����Ă���ꍇ
	else if (m_aPos[0].x < m_aPos[2].x && m_aPos[0].z > m_aPos[2].z)
	{
		D3DXVECTOR3 vecold;
		vecold = m_aPos[0];

		m_aPos[0] = m_aPos[1];
		m_aPos[1] = m_aPos[2];
		m_aPos[2] = m_aPos[3];
		m_aPos[3] = vecold;
	}

	//�O�ς̎�
	m_Vec[0] = m_aPos[1] - m_aPos[0];	// �E
	m_Vec[1] = m_aPos[2] - m_aPos[1];	// ��								 
	m_Vec[2] = m_aPos[3] - m_aPos[2];	// ��
	m_Vec[3] = m_aPos[0] - m_aPos[3];	// ��

	for (int nCount = 0; nCount < 4; nCount++)
	{
		// �v���C���[�x�N�g���ۑ�
		if (nCount == 0)
		{
			g_oldVec[nCount] = posold + D3DXVECTOR3(fWidthMin, 0.0f, 0.0f) - m_aPos[nCount];
		}
		else if (nCount == 1)
		{
			g_oldVec[nCount] = posold + D3DXVECTOR3(0.0f, 0.0f, fDepthMax) - m_aPos[nCount];
		}
		else if (nCount == 2)
		{
			g_oldVec[nCount] = posold + D3DXVECTOR3(fWidthMax, 0.0f, 0.0f) - m_aPos[nCount];
		}
		else if (nCount == 3)
		{
			g_oldVec[nCount] = posold + D3DXVECTOR3(0.0f, 0.0f, fDepthMin) - m_aPos[nCount];
		}


		// �v���C���[��m_Vec���E�ɂ��邩�ǂ����̔���p
		oldPlayerVec[nCount] = (m_Vec[nCount].z * g_oldVec[nCount].x) - (m_Vec[nCount].x * g_oldVec[nCount].z);
	}
	for (int nCount = 0; nCount < 4; nCount++)
	{
		//�O�ς̎�2		
		if (nCount == 0)
		{
			// �E�ォ��v���C���[�̃x�N�g��
			g_Vec[nCount] = pos + D3DXVECTOR3(fWidthMin, 0.0f, 0.0f) - m_aPos[nCount];
		}
		else if (nCount == 1)
		{
			// �E���v���C���[�̃x�N�g��
			g_Vec[nCount] = pos + D3DXVECTOR3(0.0f, 0.0f, fDepthMax) - m_aPos[nCount];
		}
		else if (nCount == 2)
		{
			// �����v���C���[�̃x�N�g��
			g_Vec[nCount] = pos + D3DXVECTOR3(fWidthMax, 0.0f, 0.0f) - m_aPos[nCount];
		}
		else if (nCount == 3)
		{
			// ����v���C���[�̃x�N�g��
			g_Vec[nCount] = pos + D3DXVECTOR3(0.0f, 0.0f, fDepthMin) - m_aPos[nCount];
		}

		// �v���C���[��m_Vec���E�ɂ��邩�ǂ����̔���p
		PlayerVec[nCount] = (m_Vec[nCount].z * g_Vec[nCount].x) - (m_Vec[nCount].x * g_Vec[nCount].z);
	}

	//�㉺�̓����蔻��(Y)
	if (pPos->y <= m_pos.y + m_MaxSize.y - fHeightMin && pPos->y > m_pos.y - m_MinSize.y - fHeightMax)
	{
		if (PlayerVec[0] > 0.0f && PlayerVec[1] > 0.0f && PlayerVec[2] > 0.0f && PlayerVec[3] > 0.0f)
		{
			// �㉺�̔���@�i�Ԃɂ��邩�ǂ����j
			if (PlayerVec[3] > 0.0f || PlayerVec[1] > 0.0f)
			{
				// �O�̃x�N�g����0��艺�̎�
				if (oldPlayerVec[0] < 0.0f)
				{
					// �E�̓����蔻��			
					if (PlayerVec[0] > 0.0f)
					{
						g_nCntVecObject3D = 0;

						//2���_�����v�Z
						D3DXVECTOR3 a = m_aPos[0] - m_aPos[1];

						//�p�x���v�Z
						float fA = atan2f(a.z, a.x);

						//�ǂ���x�N�g���v�Z�p
						D3DXVECTOR3 norVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �@���x�N�g��
						D3DXVec3Cross(&norVec, &a, &m_rot);
						D3DXVec3Normalize(&norVec, &norVec);
						fabsf(norVec.x);											// ��Βl
						fabsf(norVec.z);											// ��Βl

						D3DXVECTOR3 Wvec;											// �ǂ���x�N�g��
						Wvec = VecP - (D3DXVec3Dot(&VecP, &norVec) * norVec);

						if (m_rot.y == 0.0f)
						{
							pPos->x = pPosOld->x;				// 1�t���[���O�̈ʒu�ɖ߂�
						}
						else
						{
							pPos->x = pPosOld->x;				// 1�t���[���O�̈ʒu�ɖ߂�
							pPos->z = pPosOld->z;
							pMove->x = (Wvec.x) * 5;
							pMove->z = (Wvec.z) * 5;
						}

						g_fAtan2Object3D = fA;
						bLand = true;

					}
				}

				// ���̓����蔻��
				if (oldPlayerVec[2] < 0.0f)
				{
					if (PlayerVec[2] > 0.0f)
					{
						// ��
						g_nCntVecObject3D = 2;

						//2���_�����v�Z
						D3DXVECTOR3 a = m_aPos[2] - m_aPos[3];

						//�p�x���v�Z
						float fAtan2 = atan2f(a.z, a.x);

						//�ǂ���x�N�g���v�Z�p
						D3DXVECTOR3 norVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �@���x�N�g��
						D3DXVec3Cross(&norVec, &a, &m_rot);
						
						D3DXVec3Normalize(&norVec, &norVec);
						fabsf(norVec.x);											// ��Βl
						fabsf(norVec.z);											// ��Βl
																					//norVec.y = 0;
						D3DXVECTOR3 Wvec;											// �ǂ���x�N�g��
						Wvec = VecP - (D3DXVec3Dot(&VecP, &norVec) * norVec);

						if (m_rot.y == 0.0f)
						{
							pPos->x = pPosOld->x;				// 1�t���[���O�̈ʒu�ɖ߂�
							pMove->x = 0.0f;
						}
						else
						{
							pPos->x = pPosOld->x;				// 1�t���[���O�̈ʒu�ɖ߂�
							pPos->z = pPosOld->z;
							pMove->x = (Wvec.x) * 5;
							pMove->z = (Wvec.z) * 5;
						}

						bLand = true;
						g_fAtan2Object3D = fAtan2;
					}
				}

				// ���E�ɐG��Ă��Ȃ��Ƃ�
				if (PlayerVec[0] > 0.0f || PlayerVec[2] > 0.0f)
				{
					if (oldPlayerVec[3] < 0.0f)
					{
						// ��̓����蔻��			
						if (PlayerVec[3] > 0.0f)
						{
							g_nCntVecObject3D = 3;

							//2���_�����v�Z
							D3DXVECTOR3 a = m_aPos[3] - m_aPos[0];

							//�p�x���v�Z
							float fAtan2 = (float)atan2(a.z, a.x);

							//�ǂ���x�N�g���v�Z�p
							D3DXVECTOR3 norVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �@���x�N�g��
							
							D3DXVec3Cross(&norVec, &a, &D3DXVECTOR3(0.0f, 0.1f, 0.0f));
							D3DXVec3Normalize(&norVec, &norVec);
							//fabsf(norVec.x);											// ��Βl
							//fabsf(norVec.z);											// ��Βl
							//norVec.y = 0;
							D3DXVECTOR3 Wvec;											// �ǂ���x�N�g��
							Wvec = VecP - (D3DXVec3Dot(&VecP, &norVec) * norVec);

							if (m_rot.y == 0.0f)
							{
								pPos->z = pPosOld->z;				// 1�t���[���O�̈ʒu�ɖ߂�
								pMove->z = 0.0f;
							}
							else
							{

								pPos->x = pPosOld->x;				// 1�t���[���O�̈ʒu�ɖ߂�
								pPos->z = pPosOld->z;
								pMove->x = (Wvec.x) * 5;
								pMove->z = (Wvec.z) * 5;
							}

							g_fAtan2Object3D = fAtan2;
							bLand = true;
						}
					}
					if (oldPlayerVec[1] < 0.0f)
					{
						// ���̓����蔻��			
						if (PlayerVec[1] > 0.0f)
						{
							// ��
							g_nCntVecObject3D = 1;

							//2���_�����v�Z
							D3DXVECTOR3 a = m_aPos[2] - m_aPos[1];

							//�p�x���v�Z
							float fAtan2 = (float)atan2(a.z, a.x);

							//�ǂ���x�N�g���v�Z�p
							D3DXVECTOR3 norVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �@���x�N�g��
							D3DXVec3Cross(&norVec, &a, &m_rot);							// 2��3D�x�N�g���̐ϊԂ�����
							D3DXVec3Normalize(&norVec, &norVec);						// 3D�x�N�^�[�̐��K��
							fabsf(norVec.x);											// ��Βl
							fabsf(norVec.z);											// ��Βl

							D3DXVECTOR3 Wvec;											// �ǂ���x�N�g��
							Wvec = VecP - (D3DXVec3Dot(&VecP, &norVec) * norVec);		// �ǂ���x�N�g���v�Z

							if (m_rot.y == 0.0f)
							{
								pPos->z = pPosOld->z;				// 1�t���[���O�̈ʒu�ɖ߂�
								pMove->z = 0.0f;
							}
							else
							{
								pPos->x = pPosOld->x;				// 1�t���[���O�̈ʒu�ɖ߂�
								pPos->z = pPosOld->z;
								pMove->x = (Wvec.x) * 5;
								pMove->z = (Wvec.z) * 5;
							}
							bLand = true;
							g_fAtan2Object3D = fAtan2;
						}
					}
				}
				g_nCntObject3D = m_nCntNumber;
			}
		}
	}

	//�����@�v�Z��
	if (m_bUse == false)
	{
		if (m_nCnt == 2)		//�ʒu�t���[����ɉ���
		{
			//����
			m_pScene3D[m_nCntNumber] = CScene3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_aPos[0], m_aPos[1], m_aPos[3], m_aPos[2]);
			m_bUse = true;
		}

		m_nCnt++;
	}

	return bLand;
}

//=============================================================================
// ���[���h�}�g���b�N�X�����킽��
//=============================================================================
D3DXMATRIX CObject3D::GetMtxWorld(void)
{
	return m_mtxWorld;
}

//=============================================================================
//  �������Ă��鐶���ԍ���\���p
//=============================================================================
int CObject3D::GetNumberObject3D(void)
{
	return g_nCntObject3D;
}

//=============================================================================
// �������Ă���x�N�g���̌�����\���p
//=============================================================================
int CObject3D::GetNumber2Object3D(void)
{
	return g_nCntVecObject3D;
}

//=============================================================================
// �������Ă���x�N�g���̊p�x��\���p
//=============================================================================
float CObject3D::GetAtan2Object3D(void)
{
	return g_fAtan2Object3D;
}
