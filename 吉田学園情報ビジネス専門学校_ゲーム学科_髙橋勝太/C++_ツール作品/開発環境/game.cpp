//=============================================================================
//
// �Q�[����ʏ��� [game.cpp]
// Author : takahashi shota
//
//=============================================================================

//=============================================================================
//�C���N���[�h�ǂݍ���
//=============================================================================
#include "game.h"
#include "score.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "vertex.h"
#include "player3D.h"
#include "meshfield.h"
#include "scene3D.h"
#include "debugproc.h"
#include "object3D.h"
#include "textobject.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CDebugProc *CGame::m_pDebug = NULL;
CVertex *CGame::m_pVertex = NULL;					//�A�h���X�ۑ��@���_�����蔻��
CObject3D *CGame::m_pObject3D[MAX_OBJECT_3D] = {};	//�A�h���X�ۑ��@�I�u�W�F�N�g3D

//�O���[�o���ϐ��錾
D3DXVECTOR3		g_posfile[256][4];					//�e�L�X�g�ɏ����o�����@���_�����蔻��p�@pos
D3DXVECTOR3		g_posfileObject3D[256];				//�e�L�X�g�ɏ����o�����@�I�u�W�F�N�g3D�p�@pos
D3DXVECTOR3		g_rotfileObject3D[256];				//�e�L�X�g�ɏ����o�����@�I�u�W�F�N�g3D�p�@rot
int				g_nTypefileObject3D[256];			//�e�L�X�g�ɏ����o�����@�I�u�W�F�N�g3D�p�@type
int				nTimeGame = 0;						//����
int				nTimeCounter = 0;					//���ԃJ�E���^�[
int				g_FileCnt = 0;						//���_�����蔻�萶���J�E���g�@TEXT�p
int				g_FileCntObject3D = 0;				//�I�u�W�F�N�g3D�����J�E���g�@TEXT�p
int				g_nPointerGameY = 0;				//UI�ʒu���
int				g_nObject3DType = 0;				//�I�u�W�F�N�g3D�^�C�v
int				g_VecCnt = 0;						//���_�����蔻�萶���J�E���g
bool			g_bMigrate = false;					//��ʑJ�ڗp
bool			g_bDeathFlagGame = false;			//���S�t���O�����p
bool			g_bSwitchScene3D = false;			//�����؂�ւ��X�C�b�`
bool			g_bSwitchCollision = false;			//�����؂�ւ��X�C�b�`

//==============================================================================
// �R���X�g���N�^
//==============================================================================
CGame::CGame()
{
	//������
	nTimeGame = 0;					//����
	nTimeCounter = 0;				//���ԃJ�E���^�[
	g_bDeathFlagGame = false;		//���S�t���O�����p
}

//==============================================================================
// �f�X�g���N�^
//==============================================================================
CGame::~CGame()
{

}

//==============================================================================
// ����������
//==============================================================================
HRESULT CGame::Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�f�o�b�N�̐ݒ�
	m_pDebug = new CDebugProc;
	m_pDebug->Init();

	// �t�H���g�I�u�W�F�N�g�̐���
	D3DXCreateFont(pDevice, 36, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pTimeFontGame);

	//���b�V���t�B�[���h
	CMeshfield::Create();

	//���_�����蔻��̐���
	m_pVertex = new CVertex;
	m_pVertex->LoadObject();
	
	//�I�u�W�F�N�g�̐���
	CTextobject::Create();

	//3D�v���C���[�̐���
	CPlayer3D::Create();

	return S_OK;
}

//==============================================================================
// �I������
//==============================================================================
void CGame::Uninit(void)
{
	// �I�u�W�F�N�g�j��
	Release();
}

//==============================================================================
// �X�V����
//==============================================================================
void CGame::Update(void)
{
	//�L�[�{�[�h�擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�Q�[���p�b�h�̃|�C���^�錾
	CGamepad *pGamepad;
	pGamepad = CManager::GetGamepad();

	//�T�E���h���擾
	CSound *pSound;
	pSound = CManager::GetSound();

	//�X�C�b�`����
	Switch();
}

//==============================================================================
// �`�揈��
//==============================================================================
void CGame::Draw(void)
{

}

//==============================================================================
// �؂�ւ������@(�{�^��)
//==============================================================================
void CGame::Switch(void)
{
	//�L�[�{�[�h�擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�v���C���[�̏���ǂݍ���
	D3DXVECTOR3 posPlayer3D = CPlayer3D::GetPosition();
	D3DXVECTOR3 rotPlayer3D = CPlayer3D::GetRotation();

	//�L�[�{�[�hQ���������ꍇ
	if (pInputKeyboard->GetTrigger(DIK_Q) == true)
	{
		//�����X�C�b�`�؂�ւ�
		if (g_bSwitchScene3D == false)
		{
			g_bSwitchScene3D = true;
		}

		else if (g_bSwitchScene3D == true)
		{
			g_bSwitchScene3D = false;
		}
	}

	//�L�[�{�[�hE���������ꍇ
	if (pInputKeyboard->GetTrigger(DIK_E) == true)
	{
		//�����蔻��X�C�b�`�؂�ւ�
		if (g_bSwitchCollision == false)
		{
			g_bSwitchCollision = true;
		}

		else if (g_bSwitchCollision == true)
		{
			g_bSwitchCollision = false;
		}
	}

	//�L�[�{�[�hL���������ꍇ
	//�e�N�X�g�ɏ������ށ@����
	if (pInputKeyboard->GetTrigger(DIK_L) == true)
	{
		if (g_FileCnt > 0)			//��������I�u�W�F�N�g������ꍇ
		{
			//�J�E���g���炷
			g_FileCnt--;

			//����
			CVertex::Release();
			m_pScene3D[g_FileCnt]->Uninit();

			FailObject();			//�e�L�X�g������������
		}
	}

	//�L�[�{�[�hP���������ꍇ
	//�����������_�������Z�b�g
	else if (pInputKeyboard->GetTrigger(DIK_P) == true)
	{
		g_VecCnt = 0;			//���_�ݒu���Z�b�g
	}

	//�L�[�{�[�hO���������ꍇ
	//�e�N�X�g�ɏ������ށ@����
	else if (pInputKeyboard->GetTrigger(DIK_O) == true)
	{
		//�I�u�W�F�N�g�̈ʒu���L��
		g_posfile[g_FileCnt][g_VecCnt].x = posPlayer3D.x;
		g_posfile[g_FileCnt][g_VecCnt].y = posPlayer3D.y;
		g_posfile[g_FileCnt][g_VecCnt].z = posPlayer3D.z;
		g_VecCnt++;

		//�l�̒��_�����܂�����
		if (g_VecCnt >= 4)
		{
			m_pScene3D[g_FileCnt] = CScene3D::Create(D3DXVECTOR3(0, 0, 0), g_posfile[g_FileCnt][0], g_posfile[g_FileCnt][1], g_posfile[g_FileCnt][3], g_posfile[g_FileCnt][2]);
			CVertex::Create(D3DXVECTOR3(0, 0, 0), g_posfile[g_FileCnt][0], g_posfile[g_FileCnt][1], g_posfile[g_FileCnt][2], g_posfile[g_FileCnt][3]);

			g_FileCnt++;			//���̓����蔻���
			FailObject();			//�e�L�X�g������������
			g_VecCnt = 0;			//���_�ݒu���Z�b�g
		}
	}

	//�L�[�{�[�hF���������ꍇ
	if (pInputKeyboard->GetTrigger(DIK_F) == true)
	{
		g_nObject3DType--;

		//�ŏ���菬�����ꍇ�ɂȂ�����ő�ɂ���
		if (g_nObject3DType < 0)
		{
			//�ő�ɂ���
			g_nObject3DType = CTextobject::GetMaxFileX() - 1;
		}
	}

	//�L�[�{�[�hR���������ꍇ
	//��������Ƃ��̃I�u�W�F�N�g�^�C�v��ς���
	else if (pInputKeyboard->GetTrigger(DIK_R) == true)
	{
		g_nObject3DType++;

		//�ő���傫���ꍇ�ɂȂ�����ŏ��ɂ���
		if (g_nObject3DType >= CTextobject::GetMaxFileX())
		{
			//�ŏ�
			g_nObject3DType = 0;
		}
	}

	//�L�[�{�[�hK���������ꍇ
	//�e�N�X�g�ɏ������ށ@����
	if (pInputKeyboard->GetTrigger(DIK_K) == true)
	{
		if (g_FileCntObject3D > 0)		//��������I�u�W�F�N�g3D������ꍇ
		{
			g_FileCntObject3D--;		//�ő吔�����炷

										//�I�u�W�F�N�g�̏���
			m_pObject3D[g_FileCntObject3D]->Uninit();

			FailObject3D();				//�e�L�X�g������������
		}
	}

	//�L�[�{�[�hI���������ꍇ
	//�e�N�X�g�ɏ������� ����
	else if (pInputKeyboard->GetTrigger(DIK_I) == true)
	{
		//�I�u�W�F�N�g�̐���
		m_pObject3D[g_FileCntObject3D] = CObject3D::Create(posPlayer3D, D3DXVECTOR3(0.0f, rotPlayer3D.y, 0.0f), g_nObject3DType);

		//�I�u�W�F�N�g�̈ʒu���L��(CAR)
		g_posfileObject3D[g_FileCntObject3D].x = posPlayer3D.x;
		g_posfileObject3D[g_FileCntObject3D].y = posPlayer3D.y;
		g_posfileObject3D[g_FileCntObject3D].z = posPlayer3D.z;

		g_rotfileObject3D[g_FileCntObject3D].y = rotPlayer3D.y;

		g_nTypefileObject3D[g_FileCntObject3D] = g_nObject3DType;

		g_FileCntObject3D++;	//�ő吔�𑝂₷
		FailObject3D();			//�e�L�X�g������������	
	}
}

//==============================================================================
// Get�֐� ���������I�u�W�F�N�g3D�@�\���p
//==============================================================================
int CGame::GetObjectType3D(void)
{
	return g_nObject3DType;
}

//==============================================================================
// Get�֐� �����������_���@�\���p
//==============================================================================
int CGame::GetVecter(void)
{
	return g_VecCnt;
}

//==============================================================================
// Get�֐��^�C��
//==============================================================================
int CGame::GetTime(void)
{
	return nTimeGame;
}

//==============================================================================
// Get�֐� �����؂�ւ��X�C�b�`
//==============================================================================
bool CGame::GetSwitchScene3D(void)
{
	return g_bSwitchScene3D;
}

//==============================================================================
// Get�֐� �����蔻��؂�ւ��X�C�b�`
//==============================================================================
bool CGame::GetSwitchCollision(void)
{
	return g_bSwitchCollision;
}

//==============================================================================
// Get�֐� �V�ɐݒu�����I�u�W�F�N�g3D�̐�
//==============================================================================
int CGame::GetMaxObject3D(void)
{
	return g_FileCntObject3D;
}

//==============================================================================
// ��������
//==============================================================================
CGame * CGame::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	// �|�C���^�ϐ��̐���
	CGame *pGame;
	pGame = new CGame;

	// NULL�`�F�b�N
	if (pGame != NULL)
	{
		pGame->Init(pos, fSizeX, fSizeY);
	}

	return pGame;
}

//==============================================================================
//�����o�� ���_�����蔻��p
//==============================================================================
void CGame::FailObject()
{
	FILE *fp;

	fp = fopen("data/TEXT/�����o���e�L�X�g/vectorset.txt", "w");

	for (int nCnt = 0; nCnt < g_FileCnt; nCnt++)
	{
		//�������ޓ��e
		fprintf(fp, "VECTORSET\n");

		fprintf(fp, "	Vec1POSX = %.1f\n", g_posfile[nCnt][0].x);
		fprintf(fp, "	Vec1POSY = %.1f\n", g_posfile[nCnt][0].y);
		fprintf(fp, "	Vec1POSZ = %.1f\n", g_posfile[nCnt][0].z);

		fprintf(fp, "	Vec2POSX = %.1f\n", g_posfile[nCnt][1].x);
		fprintf(fp, "	Vec2POSY = %.1f\n", g_posfile[nCnt][1].y);
		fprintf(fp, "	Vec2POSZ = %.1f\n", g_posfile[nCnt][1].z);

		fprintf(fp, "	Vec3POSX = %.1f\n", g_posfile[nCnt][2].x);
		fprintf(fp, "	Vec3POSY = %.1f\n", g_posfile[nCnt][2].y);
		fprintf(fp, "	Vec3POSZ = %.1f\n", g_posfile[nCnt][2].z);

		fprintf(fp, "	Vec4POSX = %.1f\n", g_posfile[nCnt][3].x);
		fprintf(fp, "	Vec4POSY = %.1f\n", g_posfile[nCnt][3].y);
		fprintf(fp, "	Vec4POSZ = %.1f\n", g_posfile[nCnt][3].z);

		fprintf(fp, "END_VECTORSET\n\n");
	}

	//�utxt�v�̃t�@�C�������
	fclose(fp);
}

//==============================================================================
//�����o�� �I�u�W�F�N�g3D�����蔻��p
//==============================================================================
void CGame::FailObject3D()
{
	FILE *fp;

	fp = fopen("data/TEXT/�����o���e�L�X�g/object3Dset.txt", "w");

	for (int nCnt = 0; nCnt < g_FileCntObject3D; nCnt++)
	{
		//�������ޓ��e
		fprintf(fp, "OBJECTSET\n");

		fprintf(fp, "	POSX = %.1f\n", g_posfileObject3D[nCnt].x);
		fprintf(fp, "	POSY = %.1f\n", g_posfileObject3D[nCnt].y);
		fprintf(fp, "	POSZ = %.1f\n", g_posfileObject3D[nCnt].z);
		fprintf(fp, "	ROTX = %.1f\n", g_rotfileObject3D[nCnt].x);
		fprintf(fp, "	ROTY = %.1f\n", g_rotfileObject3D[nCnt].y);
		fprintf(fp, "	ROTZ = %.1f\n", g_rotfileObject3D[nCnt].z);
		fprintf(fp, "	TYPE = %d\n", g_nTypefileObject3D[nCnt]);

		fprintf(fp, "END_OBJECTSET\n\n");
	}

	//�utxt�v�̃t�@�C�������
	fclose(fp);
}
