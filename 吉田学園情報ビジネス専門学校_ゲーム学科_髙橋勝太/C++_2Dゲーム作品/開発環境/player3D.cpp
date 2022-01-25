//=============================================================================
//
// �v���C���[3D���� [player3D.cpp]
// Author : takahashi shota
//
//=============================================================================

//=============================================================================
//�C���N���[�h�ǂݍ���
//=============================================================================
#include "player3D.h"
#include "manager.h"
#include "model.h"
#include "vertex.h"
#include "camera.h"
#include "object3D.h"
#include "shadowS.h"
#include "textobject.h"
#include "meshfield.h"
#include "game.h"

//�ÓI�����o�ϐ��錾
D3DXVECTOR3		CPlayer3D::m_pos;
D3DXVECTOR3		CPlayer3D::m_rot;

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CPlayer3D::CPlayer3D(int nPriority, int nType)
{
	//�ϐ�������
	m_bMotionChange = false;
	m_nBrendFrame = 5;
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CPlayer3D::~CPlayer3D()
{

}

//==============================================================================
// ����������
//==============================================================================
HRESULT CPlayer3D::Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	//���[�V�����ǂݍ���
	LoadMotion();

	for (int nCntModel = 0; nCntModel < (int)m_nNumModel; nCntModel++)
	{
		//���f���𐶐�
		m_apModel[nCntModel] = CModel::Create(D3DXVECTOR3(m_aOffset[nCntModel][0], m_aOffset[nCntModel][1], m_aOffset[nCntModel][2]),
			D3DXVECTOR3(m_aOffset[nCntModel][3], m_aOffset[nCntModel][4], m_aOffset[nCntModel][5]), &m_pModelName[nCntModel][0]);

		//�e�q�֌W��t����
		m_apModel[nCntModel]->SetParent(m_apModel[m_aIndexParent[nCntModel]]);
	}

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���[�J���ϐ��錾
	int nNumVtx;			    // ���_��
	DWORD sizeFVF;				// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;				// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATERIAL *pMat;			// �}�e���A���ւ̃|�C���^

	// �}�e���A�����ɑ΂���|�C���^���擾
	pMat = (D3DXMATERIAL*)m_apModel[0]->GetBuff()->GetBufferPointer();

	for (int nCntMat = 13; nCntMat < (int)m_nNumModel; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			// �t�@�C�������g�p���ăe�N�X�`����ǂݍ���
			//D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/negromate_baseColor.jpeg", &m_pTexture);
		}
		//�e�N�X�`�������󂯓n��
		m_apModel[nCntMat]->SetTexture(m_pTexture);
	}

	// ���_�����擾
	nNumVtx = m_apModel[0]->GetMash()->GetNumVertices();

	// ���_�t�H�[�}�b�g�̃T�C�Y�̎擾
	sizeFVF = D3DXGetFVFVertexSize(m_apModel[0]->GetMash()->GetFVF());

	// ���_�o�b�t�@�����b�N
	m_apModel[0]->GetMash()->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	// ���_���W�̔�r�ƍX�V
	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	// ���_���W�̑��

		// �e���W�̍ő�l�̔�r
		if (m_MaxPlayer.x < vtx.x)
		{
			m_MaxPlayer.x = vtx.x;
		}
		if (m_MaxPlayer.y < vtx.y)
		{
			m_MaxPlayer.y = vtx.y;
		}
		if (m_MaxPlayer.z < vtx.z)
		{
			m_MaxPlayer.z = vtx.z;
		}

		// �e���W�̍ŏ��l�̔�r
		if (m_MinPlayer.x > vtx.x)
		{
			m_MinPlayer.x = vtx.x;
		}
		if (m_MinPlayer.y > vtx.y)
		{
			m_MinPlayer.y = vtx.y;
		}
		if (m_MinPlayer.z > vtx.z)
		{
			m_MinPlayer.z = vtx.z;
		}

		pVtxBuff += sizeFVF;	// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
	}

	// ���_�o�b�t�@���A�����b�N
	m_apModel[0]->GetMash()->UnlockVertexBuffer();

	//�ʒu
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//����
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//�e���N���G�C�g
	//CShadowS::Create();

	return S_OK;
}

//==============================================================================
// �I������
//==============================================================================
void CPlayer3D::Uninit(void)
{
	//�I�u�W�F�N�g�̔j��
	Release();
}

//==============================================================================
// �X�V����
//==============================================================================
void CPlayer3D::Update(void)
{
	//�L�[�{�[�h�擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�ʒu�X�V
	m_posold = m_pos;

	//���[�V�����̍X�V
	UpdateMotion(m_MotionType);

	// �ړ��ʂ̉��Z
	m_pos += m_move;

	//�J�����p�x�擾
	D3DXVECTOR3 RotationCamera = CManager::GetCamera()->GetRot();
	float RotCameraY = RotationCamera.y;

	// �p�x�C��
	if (RotCameraY > D3DX_PI) { RotCameraY -= D3DX_PI * 2; }
	if (RotCameraY < -D3DX_PI) { RotCameraY += D3DX_PI * 2; }

	// W�L�[�̃��f���̈ړ�
	if (pInputKeyboard->GetPress(DIK_UP) == true || pInputKeyboard->GetPress(DIK_W) == true)
	{
		if (m_nMoveCnt < 10)
		{
			m_nMoveCnt++;
		}

		//���[�V�����̕ω�
		m_MotionType = MOTIONTYPE_MOVE;

		//�ړ��ʌv�Z
		if (pInputKeyboard->GetPress(DIK_A) == true)
		{
			// �������
			m_move.x -= cosf(RotCameraY + D3DX_PI / 4) * PLAYER_SPEED;
			m_move.z += sinf(RotCameraY + D3DX_PI / 4) * PLAYER_SPEED;
			m_rotDest.y = RotCameraY + (D3DX_PI * 3 / 4);
		}
		else if (pInputKeyboard->GetPress(DIK_D) == true)
		{
			// �E�����
			m_move.x += cosf(RotCameraY - D3DX_PI / 4) * PLAYER_SPEED;
			m_move.z -= sinf(RotCameraY - D3DX_PI / 4) * PLAYER_SPEED;
			m_rotDest.y = RotCameraY - (D3DX_PI * 3 / 4);
		}
		else
		{
			// �����
			m_move.x += sinf(RotCameraY) * PLAYER_SPEED;
			m_move.z += cosf(RotCameraY) * PLAYER_SPEED;
			m_rotDest.y = RotCameraY + D3DX_PI;
		}
	}

	// W�L�[�̃��f���̈ړ�
	else if (pInputKeyboard->GetPress(DIK_DOWN) == true || pInputKeyboard->GetPress(DIK_S) == true)
	{
		if (m_nMoveCnt < 10)
		{
			m_nMoveCnt++;
		}

		//���[�V�����̕ω�
		m_MotionType = MOTIONTYPE_MOVE;

		if (pInputKeyboard->GetPress(DIK_A) == true)
		{
			// ��������
			//�ړ��ʌv�Z
			m_move.x -= cosf(RotCameraY - D3DX_PI / 4) * PLAYER_SPEED;
			m_move.z += sinf(RotCameraY - D3DX_PI / 4) * PLAYER_SPEED;
			m_rotDest.y = RotCameraY - D3DX_PI / -4;
		}
		else if (pInputKeyboard->GetPress(DIK_D) == true)
		{
			// �E������
			//�ړ��ʌv�Z
			m_move.x += cosf(RotCameraY + D3DX_PI / 4) * PLAYER_SPEED;
			m_move.z -= sinf(RotCameraY + D3DX_PI / 4) * PLAYER_SPEED;
			m_rotDest.y = RotCameraY - D3DX_PI / 4;
		}
		else
		{
			// ������
			m_move.x -= sinf(RotCameraY) * PLAYER_SPEED;
			m_move.z -= cosf(RotCameraY) * PLAYER_SPEED;
			m_rotDest.y = RotCameraY;
		}
	}

	else if (pInputKeyboard->GetPress(DIK_A) == true)
	{
		//���[�V�����̕ω�
		m_MotionType = MOTIONTYPE_MOVE;

		// ������
		if (m_nMoveCnt < 10)
		{
			m_nMoveCnt++;
		}
		m_move.x -= cosf(RotCameraY) * PLAYER_SPEED;
		m_move.z += sinf(RotCameraY) * PLAYER_SPEED;
		m_rotDest.y = RotCameraY + (D3DX_PI / 2);
	}
	else if (pInputKeyboard->GetPress(DIK_D) == true)
	{
		//���[�V�����̕ω�
		m_MotionType = MOTIONTYPE_MOVE;

		// �E����
		if (m_nMoveCnt < 10)
		{
			m_nMoveCnt++;
		}
		m_move.x += cosf(RotCameraY) * PLAYER_SPEED;
		m_move.z -= sinf(RotCameraY) * PLAYER_SPEED;
		m_rotDest.y = RotCameraY + (D3DX_PI / -2);
	}

	else
	{
		if (m_nMoveCnt > 5)
		{
			m_nMoveCnt--;
		}
	}

	// �ړ����[�V��������ҋ@���[�V������
	if (m_MotionType == MOTIONTYPE_MOVE && m_nMoveCnt == 5)
	{
		m_fCounterMotion = 0;
		m_Key = 0;
		m_MotionType = MOTIONTYPE_NEUTRAL;
	}

	//�e�p�[�c�̍X�V����
	for (int nCnt = 0; nCnt < (int)m_nNumModel; nCnt++)
	{
		m_apModel[nCnt]->MotionPos(D3DXVECTOR3(m_aOffset[nCnt][0], m_aOffset[nCnt][1], m_aOffset[nCnt][2]));
		m_apModel[nCnt]->MotionRot(D3DXVECTOR3(m_aOffset[nCnt][3], m_aOffset[nCnt][4], m_aOffset[nCnt][5]));
	}

	// �ړI�̉�]�p�̏��
	if (m_rotDest.y - m_rot.y < -D3DX_PI)
	{
		m_rotDest.y += D3DX_PI * 2.0f;
	}
	else if (m_rotDest.y - m_rot.y > D3DX_PI)
	{
		m_rotDest.y -= D3DX_PI * 2.0f;
	}

	// �����̍X�V
	m_rot.y += (m_rotDest.y - m_rot.y) * 0.1f;

	// ���݂̉�]�p�̏��
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}
	else if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}

	// ������̌�������
	m_move.x += (0.0f - m_move.x) * 0.7f;
	m_move.z += (0.0f - m_move.z) * 0.7f;

	//�����蔻��̃I���I�t �@����false�X�^�[�g
	if (CGame::GetSwitchCollision() == false)
	{
		int n1 = CGame::GetMaxObject3D();					//�Q�[���Ő��������I�u�W�F�N�g3D�̐�
		int n2 = CTextobject::GetTextObject3D();			//�e�L�X�g�Ő��������I�u�W�F�N�g3D�̐�

		//���Ă蔻��
		for (int nCount = 0; nCount < n1 + n2; nCount++)
		{
			CObject3D *pObj;

			//�e�L�X�g�Ő��������񐔕��ȊO�Ő��������e�L�X�g�Ő�������
			if (n2 <= nCount)
			{
				pObj = CGame::GetObject(nCount - CTextobject::GetTextObject3D());
			}

			//�e�L�X�g�Ő��������e�L�X�g�Ő�������
			else
			{
				pObj = CTextobject::GetObject(nCount);
			}

			if (pObj != NULL)
			{
				//�I�u�W�F�N�g3D�̓����蔻��
				pObj->CollisionVec(&m_pos, &m_posold, &m_move, m_MaxPlayer.x, m_MinPlayer.x, m_MaxPlayer.z, m_MinPlayer.z, m_MaxPlayer.y, m_MinPlayer.y);
			}
		}

		//�I�u�W�F�N�g�ւ̃|�C���^����
		CVertex *pVer;
		pVer = CGame::GetVertex();

		//���_�I�u�W�F�N�g�̓����蔻��
		pVer->CollisionVec(&m_pos, &m_posold, &m_move, m_MaxPlayer.x - 0.0f, m_MinPlayer.x + 0.0f, m_MaxPlayer.z - 0.0f, m_MinPlayer.z + 0.0f, m_MaxPlayer.y, m_MinPlayer.y);
	}

	//���b�V���t�B�[���h�͈͊O�̏ꍇ�̈ړ�����
	if (CMeshfield::GetMeshFildX() <= m_pos.x || -CMeshfield::GetMeshFildX() >= m_pos.x)
	{
		m_pos.x = m_posold.x;
	}

	if (CMeshfield::GetMeshFildZ() <= m_pos.z || -CMeshfield::GetMeshFildZ() >= m_pos.z)
	{
		m_pos.z = m_posold.z;
	}
}

//==============================================================================
// �`�揈��
//==============================================================================
void CPlayer3D::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���[�J��
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

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

	for (int nCnt = 0; nCnt < (int)m_nNumModel; nCnt++)
	{
		//���������p�[�c����`�悷��
		m_apModel[nCnt]->Draw();
	}
}

//==============================================================================
// ��������
//==============================================================================
CPlayer3D * CPlayer3D::Create()
{
	//�v���C���[�𐶐�
	CPlayer3D *pPlayer3D = NULL;
	pPlayer3D = new CPlayer3D;

	//NULL�`�F�b�N
	if (pPlayer3D != NULL)
	{
		pPlayer3D->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f);
	}

	return pPlayer3D;
}

//==============================================================================
// .txt�t�H���_�̓ǂݍ���
//==============================================================================
void CPlayer3D::LoadMotion(void)
{
	// ���[�J���ϐ��錾
	FILE *pFile = NULL;
	char aEqual[2] = { NULL };					// �u=�v�ǂݎ��p�ϐ�
	bool bComment = false;						// �R�����g�A�E�g���邩
	char aText[TEXT_LENGTH] = { NULL };			// �e�L�X�g�ǂݎ��p�ϐ�
	char aCharaSet[DATA_LENGTH] = { NULL };		// �L�����f�[�^�ǂݎ��p�ϐ�
	char aPartsSet[DATA_LENGTH] = { NULL };		// �p�[�c�f�[�^�ǂݎ��p�ϐ�
	char aMotionSet[DATA_LENGTH] = { NULL };	// ���[�V�����ǂݎ��p�ϐ�
	char aKeySet[DATA_LENGTH] = { NULL };		// �L�[�ݒ���ǂݎ��p�ϐ�
	char aKey[DATA_LENGTH] = { NULL };			// �L�[���ǂݎ��p�ϐ�

	// strcmp�ǂݎ��p�|�C���^
	char *pText = &aText[0];
	char *pCharaSet = &aCharaSet[0];
	char *pPartsSet = &aPartsSet[0];
	char *pMotionSet = &aMotionSet[0];
	char *pKeySet = &aKeySet[0];
	char *pKey = &aKey[0];

	// �f�[�^�̓ǂݍ���
	pFile = fopen("data/TEXT/motion_player00.txt", "r");

	if (pFile != NULL)
	{ 
		//�t�@�C���W�J�\
		aText[0] = { NULL };
		aCharaSet[0] = { NULL };
		aPartsSet[0] = { NULL };
		aMotionSet[0] = { NULL };
		aKeySet[0] = { NULL };
		aKey[0] = { NULL };
		int nIdxParts = 0;			// �p�[�c��
		int nMotion = 0;			// ���[�V�����̐�
		int nCntFile = 0;			// X�f�[�^�̐�
		int nAs = 0;

		while (strcmp("END_SCRIPT", pText) != 0)
		{
			aText[0] = { NULL };
			if (bComment == false)
			{
				// �R�����g�A�E�g���Ă��Ȃ�
				fscanf(pFile, "%s", &aText[0]);

				if (aText[0] == '#')
				{
					// ������̐擪���u#�v�Ȃ�΃R�����g�A�E�g��
					bComment = true;
				}
				else
				{
					// �ʏ펞
					if (strcmp("NUM_MODEL", pText) == 0)
					{
						// ���f���̐�
						fscanf(pFile, "%s", &aEqual[0]);
						fscanf(pFile, "%d", &m_nNumModel);
					}
					else if (strcmp("MODEL_FILENAME", pText) == 0)
					{
						// X�t�@�C�����̓ǂݍ���
						fscanf(pFile, "%s", &aEqual[0]);
						fscanf(pFile, "%s", &m_pModelName[nCntFile][0]);
						nCntFile++;
					}
					else if (strcmp("CHARACTERSET", pText) == 0)
					{
						// �L�����̏��
						while (strcmp("END_CHARACTERSET", pCharaSet) != 0)
						{
							// �L�������̓ǂݎ��
							fscanf(pFile, "%s", &aCharaSet[0]);
							if (strcmp("NUM_PARTS", pCharaSet) == 0)
							{

							}
							else if (strcmp("PARTSSET", pCharaSet) == 0)
							{
								// �p�[�c���
								aPartsSet[0] = { NULL };

								while (strcmp("END_PARTSSET", pPartsSet) != 0)
								{
									fscanf(pFile, "%s", &aPartsSet[0]);
									if (strcmp("INDEX", pPartsSet) == 0)
									{
										// �p�[�c���̓ǂݎ��
										fscanf(pFile, "%s", &aEqual[0]);
										fscanf(pFile, "%d", &nIdxParts);
									}
									else if (strcmp("PARENT", pPartsSet) == 0)
									{
										// �p�[�c�̐e���
										fscanf(pFile, "%s", &aEqual[0]);
										fscanf(pFile, "%d", &m_aIndexParent[nIdxParts]);
									}
									else if (strcmp("POS", pPartsSet) == 0)
									{
										// �p�[�c�̈ʒu���
										fscanf(pFile, "%s", &aEqual[0]);
										fscanf(pFile, "%f", &m_aOffset[nIdxParts][0]);
										fscanf(pFile, "%f", &m_aOffset[nIdxParts][1]);
										fscanf(pFile, "%f", &m_aOffset[nIdxParts][2]);
										//g_player.aModel[nIdxParts].posReset = g_player.aModel[nIdxParts].pos;
									}
									else if (strcmp("ROT", pPartsSet) == 0)
									{
										// �p�[�c�̊p�x���
										fscanf(pFile, "%s", &aEqual[0]);
										fscanf(pFile, "%f", &m_aOffset[nIdxParts][3]);
										fscanf(pFile, "%f", &m_aOffset[nIdxParts][4]);
										fscanf(pFile, "%f", &m_aOffset[nIdxParts][5]);
									}
								}
							}
						}
					}
					else if (strcmp("MOTIONSET", pText) == 0)
					{
						// �ϐ��̏�����
						aMotionSet[0] = { NULL };

						// ���[�J���ϐ��錾
						int nLoop = 0;
						int nKeySet = 0;

						while (strcmp("END_MOTIONSET", pMotionSet) != 0)
						{
							// ���[�V�����̓ǂݍ���
							fscanf(pFile, "%s", &aMotionSet[0]);
							if (strcmp("LOOP", pMotionSet) == 0)
							{
								// ���[�v���邩
								fscanf(pFile, "%s", &aEqual[0]);
								fscanf(pFile, "%d", &nLoop);
								if (nLoop == 1)
								{
									// �P�̏ꍇ���[�v����
									m_bLoopKeep = true;
									m_Loop[nMotion] = true;
								}
							}
							else if (strcmp("NUM_KEY", pMotionSet) == 0)
							{
								// �L�[���̓ǂݍ���
								fscanf(pFile, "%s", &aEqual[0]);
								fscanf(pFile, "%d", &m_nNumKeyKeep);
							}
							else if (strcmp("KEYSET", pMotionSet) == 0)
							{
								// �L�[�̓ǂݍ���
								// ���[�J���ϐ��錾
								int nKey = 0;

								// �ϐ��̏�����
								aKeySet[0] = { NULL };

								while (strcmp("END_KEYSET", pKeySet) != 0)
								{
									// �L�[��񍀖ڂ̓ǂݍ���
									fscanf(pFile, "%s", &aKeySet[0]);

									if (aKeySet[0] == '#')
									{
										// �R�����g�A�E�g
										// ���[�J���ϐ��錾
										char c = NULL;
										char d = NULL;

										fscanf(pFile, "%c", &c);

										while (c != '\n' && d != '\n')
										{
											fscanf(pFile, "%s", &aKey[0]);
											fscanf(pFile, "%c", &d);
										}
									}

									if (strcmp("KEY", pKeySet) == 0)
									{
										// �L�[���̓ǂݍ���
										aKey[0] = { NULL };
										while (strcmp("END_KEY", pKey) != 0)
										{
											// �ʒu�E�p�x�̓ǂݍ���
											fscanf(pFile, "%s", &aKey[0]);

											if (strcmp("POS", pKey) == 0)
											{
												// �ʒu���̓ǂݍ���
												fscanf(pFile, "%s", &aEqual[0]);

												// �ʒu���̓ǂݍ���
												fscanf(pFile, "%f", &m_Player3D[nMotion][nKeySet][nKey][0]);
												fscanf(pFile, "%f", &m_Player3D[nMotion][nKeySet][nKey][1]);
												fscanf(pFile, "%f", &m_Player3D[nMotion][nKeySet][nKey][2]);
												m_Player3D[nMotion][nKeySet][nKey][0] += m_aOffset[nKey][0];
												m_Player3D[nMotion][nKeySet][nKey][1] += m_aOffset[nKey][1];
												m_Player3D[nMotion][nKeySet][nKey][2] += m_aOffset[nKey][2];
											}
											else if (strcmp("ROT", pKey) == 0)
											{
												// �p�x���̓ǂݍ���
												fscanf(pFile, "%s", &aEqual[0]);
												fscanf(pFile, "%f", &m_Player3D[nMotion][nKeySet][nKey][3]);
												fscanf(pFile, "%f", &m_Player3D[nMotion][nKeySet][nKey][4]);
												fscanf(pFile, "%f", &m_Player3D[nMotion][nKeySet][nKey][5]);
											}
										}
										nKey++;
									}
									else if (strcmp("FRAME", pKeySet) == 0)
									{
										// �L�[�t���[�����̓ǂݍ���
										fscanf(pFile, "%s", &aEqual[0]);

										fscanf(pFile, "%d", &m_nFrame[nMotion][nKeySet]);
										m_nFrameTotal[nMotion] += m_nFrame[nMotion][nKeySet];

										if (m_Loop[nMotion] == false && nKeySet == (m_NumKey[nMotion] - 1))
										{
											m_nFrameTotal[nMotion] -= m_nFrame[nMotion][nKeySet];
										}
									}
								}

								nKeySet++;
							}
						}

						m_NumKey[nMotion] = nKeySet;	// �L�[���̐ݒ�
						nMotion++;
					}
				}
			}
			else if (bComment == true)
			{
				// �R�����g�A�E�g����
				// ���[�J���ϐ��錾
				char a = NULL;
				char b = NULL;

				fscanf(pFile, "%c", &a);

				while (a != '\n' && b != '\n')
				{
					fscanf(pFile, "%s", &aText[0]);
					fscanf(pFile, "%c", &b);
				}
				bComment = false;
			}
		}

		//�e�L�X�g�����
		fclose(pFile);
	}

	else
	{ 
		// �t�@�C���W�J�s��
	}
}

//==============================================================================
// ���[�V�����̍X�V
//==============================================================================
void CPlayer3D::UpdateMotion(MOTIONTYPE MOTIONTYPE)
{
	// �L�[���ƃ��[�v���̑��
	m_nNumKeyKeep = m_NumKey[MOTIONTYPE];
	m_bLoopKeep = m_Loop[MOTIONTYPE];

	// ���[�V�����J�E���^�[�̉��Z
	if (m_bMotionChange == true)
	{
		// ���[�V�����u�����h���s��
		if (m_fCounterMotion < m_nBrendFrame)
		{
			// �J�E���g���
			m_fCounterMotion++;
		}
	}
	else
	{
		// �ʏ펞
		if (m_fCounterMotion < m_nFrame[MOTIONTYPE][m_Key])
		{
			// �J�E���g���
			m_fCounterMotion++;
		}
	}

	// ���f���p�[�c���Ƃ̃��[�V�����A�j���[�V����
	for (int nCnt = 0; nCnt < MAX_PLAYER_PARTS; nCnt++)
	{
		if (m_Key == m_nNumKeyKeep - 1 && m_bLoopKeep == true)
		{
			// ���[�v���čŏ��ɖ߂�Ƃ�
			m_aOffset[nCnt][0] = m_Player3D[MOTIONTYPE][m_Key][nCnt][0] + (m_Player3D[MOTIONTYPE][0][nCnt][0] - m_Player3D[MOTIONTYPE][m_Key][nCnt][0]) * ((float)m_fCounterMotion / (float)m_nFrame[MOTIONTYPE][m_Key]);
			m_aOffset[nCnt][1] = m_Player3D[MOTIONTYPE][m_Key][nCnt][1] + (m_Player3D[MOTIONTYPE][0][nCnt][1] - m_Player3D[MOTIONTYPE][m_Key][nCnt][1]) * ((float)m_fCounterMotion / (float)m_nFrame[MOTIONTYPE][m_Key]);
			m_aOffset[nCnt][2] = m_Player3D[MOTIONTYPE][m_Key][nCnt][2] + (m_Player3D[MOTIONTYPE][0][nCnt][2] - m_Player3D[MOTIONTYPE][m_Key][nCnt][2]) * ((float)m_fCounterMotion / (float)m_nFrame[MOTIONTYPE][m_Key]);
			m_aOffset[nCnt][3] = m_Player3D[MOTIONTYPE][m_Key][nCnt][3] + (m_Player3D[MOTIONTYPE][0][nCnt][3] - m_Player3D[MOTIONTYPE][m_Key][nCnt][3]) * ((float)m_fCounterMotion / (float)m_nFrame[MOTIONTYPE][m_Key]);
			m_aOffset[nCnt][4] = m_Player3D[MOTIONTYPE][m_Key][nCnt][4] + (m_Player3D[MOTIONTYPE][0][nCnt][4] - m_Player3D[MOTIONTYPE][m_Key][nCnt][4]) * ((float)m_fCounterMotion / (float)m_nFrame[MOTIONTYPE][m_Key]);
			m_aOffset[nCnt][5] = m_Player3D[MOTIONTYPE][m_Key][nCnt][5] + (m_Player3D[MOTIONTYPE][0][nCnt][5] - m_Player3D[MOTIONTYPE][m_Key][nCnt][5]) * ((float)m_fCounterMotion / (float)m_nFrame[MOTIONTYPE][m_Key]);
			m_aOffsetMemo[nCnt][0] = m_aOffset[nCnt][0];
			m_aOffsetMemo[nCnt][1] = m_aOffset[nCnt][1];
			m_aOffsetMemo[nCnt][2] = m_aOffset[nCnt][2];
			m_aOffsetMemo[nCnt][3] = m_aOffset[nCnt][3];
			m_aOffsetMemo[nCnt][4] = m_aOffset[nCnt][4];
			m_aOffsetMemo[nCnt][5] = m_aOffset[nCnt][5];
		}
		else if (m_bMotionChange == true)
		{
			// ���[�V�����u�����h
			m_aOffset[nCnt][0] = m_aOffsetMemo[nCnt][0] + (m_Player3D[m_MotionType][0][nCnt][0] - m_aOffsetMemo[nCnt][0]) * ((float)m_fCounterMotion / (float)m_nBrendFrame);
			m_aOffset[nCnt][1] = m_aOffsetMemo[nCnt][1] + (m_Player3D[m_MotionType][0][nCnt][1] - m_aOffsetMemo[nCnt][1]) * ((float)m_fCounterMotion / (float)m_nBrendFrame);
			m_aOffset[nCnt][2] = m_aOffsetMemo[nCnt][2] + (m_Player3D[m_MotionType][0][nCnt][2] - m_aOffsetMemo[nCnt][2]) * ((float)m_fCounterMotion / (float)m_nBrendFrame);
			m_aOffset[nCnt][3] = m_aOffsetMemo[nCnt][3] + (m_Player3D[m_MotionType][0][nCnt][3] - m_aOffsetMemo[nCnt][3]) * ((float)m_fCounterMotion / (float)m_nBrendFrame);
			m_aOffset[nCnt][4] = m_aOffsetMemo[nCnt][4] + (m_Player3D[m_MotionType][0][nCnt][4] - m_aOffsetMemo[nCnt][4]) * ((float)m_fCounterMotion / (float)m_nBrendFrame);
			m_aOffset[nCnt][5] = m_aOffsetMemo[nCnt][5] + (m_Player3D[m_MotionType][0][nCnt][5] - m_aOffsetMemo[nCnt][5]) * ((float)m_fCounterMotion / (float)m_nBrendFrame);
			m_aOffsetMemo[nCnt][0] = m_aOffset[nCnt][0];
			m_aOffsetMemo[nCnt][1] = m_aOffset[nCnt][1];
			m_aOffsetMemo[nCnt][2] = m_aOffset[nCnt][2];
			m_aOffsetMemo[nCnt][3] = m_aOffset[nCnt][3];
			m_aOffsetMemo[nCnt][4] = m_aOffset[nCnt][4];
			m_aOffsetMemo[nCnt][5] = m_aOffset[nCnt][5];
		}
		else
		{
			// �ʏ펞
			m_aOffset[nCnt][0] = m_Player3D[MOTIONTYPE][m_Key][nCnt][0] + (m_Player3D[MOTIONTYPE][m_Key + 1][nCnt][0] - m_Player3D[MOTIONTYPE][m_Key][nCnt][0]) * ((float)m_fCounterMotion / (float)m_nFrame[MOTIONTYPE][m_Key]);
			m_aOffset[nCnt][1] = m_Player3D[MOTIONTYPE][m_Key][nCnt][1] + (m_Player3D[MOTIONTYPE][m_Key + 1][nCnt][1] - m_Player3D[MOTIONTYPE][m_Key][nCnt][1]) * ((float)m_fCounterMotion / (float)m_nFrame[MOTIONTYPE][m_Key]);
			m_aOffset[nCnt][2] = m_Player3D[MOTIONTYPE][m_Key][nCnt][2] + (m_Player3D[MOTIONTYPE][m_Key + 1][nCnt][2] - m_Player3D[MOTIONTYPE][m_Key][nCnt][2]) * ((float)m_fCounterMotion / (float)m_nFrame[MOTIONTYPE][m_Key]);
			m_aOffset[nCnt][3] = m_Player3D[MOTIONTYPE][m_Key][nCnt][3] + (m_Player3D[MOTIONTYPE][m_Key + 1][nCnt][3] - m_Player3D[MOTIONTYPE][m_Key][nCnt][3]) * ((float)m_fCounterMotion / (float)m_nFrame[MOTIONTYPE][m_Key]);
			m_aOffset[nCnt][4] = m_Player3D[MOTIONTYPE][m_Key][nCnt][4] + (m_Player3D[MOTIONTYPE][m_Key + 1][nCnt][4] - m_Player3D[MOTIONTYPE][m_Key][nCnt][4]) * ((float)m_fCounterMotion / (float)m_nFrame[MOTIONTYPE][m_Key]);
			m_aOffset[nCnt][5] = m_Player3D[MOTIONTYPE][m_Key][nCnt][5] + (m_Player3D[MOTIONTYPE][m_Key + 1][nCnt][5] - m_Player3D[MOTIONTYPE][m_Key][nCnt][5]) * ((float)m_fCounterMotion / (float)m_nFrame[MOTIONTYPE][m_Key]);
			m_aOffsetMemo[nCnt][0] = m_aOffset[nCnt][0];
			m_aOffsetMemo[nCnt][1] = m_aOffset[nCnt][1];
			m_aOffsetMemo[nCnt][2] = m_aOffset[nCnt][2];
			m_aOffsetMemo[nCnt][3] = m_aOffset[nCnt][3];
			m_aOffsetMemo[nCnt][4] = m_aOffset[nCnt][4];
			m_aOffsetMemo[nCnt][5] = m_aOffset[nCnt][5];
		}

		if (m_bMotionChange == false)
		{
			// ���[�V�����ω��Ȃ�
			if (m_fCounterMotion == m_nFrame[MOTIONTYPE][m_Key])
			{
				// �L�[�t���[���I����
			 
				//if (m_MotionType != MOTIONTYPE_JUMP || m_Key != m_nNumKeyKeep - 2)
				{
					// �W�����v�ȊO�ŃL�[�I�������Z�b�g
					m_fCounterMotion = 0;
				}

				if (m_Key == m_nNumKeyKeep - 1 && m_bLoopKeep == true)
				{
					// ���[�v����Ƃ�
					m_Key = 0;
				}
				else if (m_Key == m_nNumKeyKeep - 2 && m_bLoopKeep == false)
				{
					// ���[�v�����I������Ƃ�
				 
					//if (m_MotionTypeOld != MOTIONTYPE_JUMP)
					{
						// ���O���W�����v�ȊO�̎�
						m_MotionType = MOTIONTYPE_NEUTRAL;	// �j���[�g�����ֈڍs
						m_fCounterMotion = 0;
						break;
					}
				}
				else if (m_Key < m_nNumKeyKeep)
				{
					// �L�[�̃J�E���g
					m_Key++;
				}
			}
			else if (m_MotionTypeOld != m_MotionType)
			{
				// ���[�V�����ω���	
				m_Key = 0;
				m_fCounterMotion = 0;
				m_bMotionChange = true;

				if (m_MotionTypeOld == MOTIONTYPE_NEUTRAL && m_MotionType == MOTIONTYPE_MOVE)
				{
					// �ړ�����j���[�g������
					m_nBrendFrame = 20;
				}
				else if (m_MotionTypeOld == MOTIONTYPE_MOVE && m_MotionType == MOTIONTYPE_NEUTRAL)
				{
					// �j���[�g��������ړ���
					m_nBrendFrame = 40;
				}
				break;
			}
		}
		else if (m_bMotionChange == true)
		{
			// ���[�V�����u�����h���̃J�E���g���Z�b�g
			if (m_fCounterMotion == m_nBrendFrame || m_MotionTypeOld != m_MotionType)
			{
				m_Key = 0;
				m_fCounterMotion = 0;
				m_bMotionChange = false;
			}
		}
	}

	// ���O�̃��[�V������Ԃ̕ۑ�
	m_MotionTypeOld = m_MotionType;
}

//==============================================================================
// Get�֐��@pos
//==============================================================================
D3DXVECTOR3 CPlayer3D::GetPosition(void)
{
	return m_pos;
}

//==============================================================================
// Get�֐��@rot
//==============================================================================
D3DXVECTOR3 CPlayer3D::GetRotation(void)
{
	return m_rot;
}
