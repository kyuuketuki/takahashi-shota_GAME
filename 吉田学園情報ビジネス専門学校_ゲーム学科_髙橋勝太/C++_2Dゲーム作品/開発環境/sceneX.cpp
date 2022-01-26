//=============================================================================
//
// �V�[��X���� [sceneX.cpp]
// Author : takahashi shota
//=============================================================================
#include "sceneX.h"
#include "manager.h"

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CSceneX::CSceneX(int nPriority, int nType) : CScene(nPriority, nType)
{

}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSceneX::~CSceneX()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CSceneX::Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//model�ǂݍ���
	D3DXLoadMeshFromX("data/MODEL/model.x", D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat, NULL, &m_nNumMat, &m_pMesh);

	int nNumVtx;			//���_��
	DWORD sizeFVF;			//���_�t�H�[�}�b�g�̃T�C�Y

	D3DXMATERIAL *pMat;		//�}�e���A���ւ̃|�C���^

	//���_�����擾
	nNumVtx = m_pMesh->GetNumVertices();
	m_nNumVtx = nNumVtx;

	//�}�e���A���f�[�^�ւ̃|�C���^�擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	//���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//�ʒu
	m_pos = D3DXVECTOR3(40.0f, 60.0f, 0.0f);

	//����
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.02f);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CSceneX::Uninit(void)
{
	// �I�u�W�F�N�g�j��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CSceneX::Update(void)
{
	m_fRot += 0.01f;
	m_rot.y = m_fRot;
}

//=============================================================================
// �`�揈��
//=============================================================================
void CSceneX::Draw(void)
{
	//���[�J��
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ�
	D3DXMATERIAL *pMat;				//�}�e���A���ւ̃|�C���^

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
CSceneX *CSceneX::Create()
{
	//�V�[��X�𐶐�
	CSceneX *pSceneX = NULL;
	pSceneX = new CSceneX;

	//NULL�`�F�b�N
	if (pSceneX != NULL)
	{
		pSceneX->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f);
	}

	return pSceneX;
}
