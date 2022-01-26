//=============================================================================
//
// �J�������� [camera.cpp]
// Author :  takahashi syota
//
//=============================================================================

//=============================================================================
//�C���N���[�h�ǂݍ���
//=============================================================================
#include "camera.h"
#include "player3D.h"

//=============================================================================
//�}�N����`
//=============================================================================
#define DISTANCE			(600.0f)	// �v���C���[(�����_)�ƃJ�����̋���
#define MOUSE_SENSITIVITY	(0.0008f)	// �}�E�X����̃J������]���x
#define MOVE_CAMERA_ROT		(0.3f)		// �ړI�p�x�ɒǂ������x
#define MOVE_SPEED			(0.2f)		// �J�����̒Ǐ]���x
#define POSR_Y				(50)		// �����_�������ߗp
#define ROT_X_MIN_ANGLE		(0.1f)		// �c��]�̍ŏ��l
#define ROT_X_MAX_ANGLE		(1.40f)		// �c��]�̍ő�l

//=============================================================================
//�ÓI�����o�ϐ�
//=============================================================================
D3DXVECTOR3 CCamera::m_rot = {};
D3DXVECTOR3 CCamera::m_posV = {};
D3DXVECTOR3 CCamera::m_posR = {};

//=============================================================================
//�O���[�o���ϐ�
//=============================================================================
int nCameraType = 0;

//=============================================================================
// �R���X�^�N�^
//=============================================================================
CCamera::CCamera()
{
	m_fDistance = DISTANCE;									// �J�����ƒ����_�̋���
	m_posV = D3DXVECTOR3(0.0f, 300.0f, 0.0f);				// ���_
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);					// �����_
	m_vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);					// �@���x�N�g��
	m_rot = D3DXVECTOR3(0.0f, 1.0f, 1.0f);					// ��]�p�x
	int m_Rpos = 0;											// �����_���ߗp�̂͂�������
	m_fMouseSpeed = MOUSE_SENSITIVITY;						// �}�E�X���x
	m_fhorizontalAngle = 0.0f;								// �����A���O��
	m_fverticalAngle = 0.0f;								// �����A���O��
	SetCursorPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);		// �}�E�X�J�[�\���̈ʒu�Œ�
	m_Mousepoint = { 0,0 };									// �}�E�X�ʒu
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCamera::~CCamera()
{

}

//=============================================================================
// ����������
//=============================================================================
HRESULT CCamera::Init(void)
{
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CCamera::Uninit(void)
{

}

//=============================================================================
// �X�V����
//=============================================================================
void CCamera::Update(void)
{
	// �L�[�{�[�h�擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// �v���C���[�̈ʒu�擾
	D3DXVECTOR3 pos = CPlayer3D::GetPosition();
	D3DXVECTOR3 rot = CPlayer3D::GetRotation();

	//5���������Ƃ�
	//�J�������[�h�؂�ւ�
	if (pInputKeyboard->GetTrigger(DIK_7) == true)
	{
		//�L�[�{�[�h���[�h��
		if (nCameraType == 0)
		{
			nCameraType = 1;
		}

		//�J�������[�h��
		else if (nCameraType == 1)
		{
			nCameraType = 0;
		}
	}

	//�}�E�X���[�h��
	if (nCameraType == 0)
	{
		// �}�E�X����
		Mouseoperation();

		//W���������Ƃ�
		if (pInputKeyboard->GetPress(DIK_U) == true)
		{
			m_fDistance += 30.0f;
		}

		//S���������Ƃ�
		if (pInputKeyboard->GetPress(DIK_J) == true)
		{
			//�ړ������@�n�ʂ��100��
			if (m_fDistance >= 100.0f)
			{
				m_fDistance -= 30.0f;
			}
		}

		// ���_
		m_posV.x = pos.x + sinf(m_rot.y) *-m_fDistance;
		m_posV.z = pos.z + cosf(m_rot.y) *-m_fDistance;
		m_posV.y = pos.y + sinf(m_rot.x) + cosf(m_rot.x) * m_fDistance;

		// �����_�@�v���C���[
		m_posRDest.x = pos.x;
		m_posRDest.z = pos.z;
		m_posRDest.y = pos.y;

		// �ړI�̎��_�ɒ����_����
		m_posVDest.x = m_posR.x;
		m_posVDest.z = m_posR.z;
		m_posVDest.y = m_posR.y;

		// �J�����ʒu�X�V
		m_posV += (m_posVDest - m_posV)			* MOVE_SPEED;
		m_posR.x += (m_posRDest.x - m_posR.x)	* MOVE_SPEED;
		m_posR.y += (m_posRDest.y - m_posR.y)	* MOVE_SPEED;
		m_posR.z += (m_posRDest.z - m_posR.z)	* MOVE_SPEED;

		// ��]�p�x��3.14�ȏ�A-3.14�ȉ��ɂȂ�Ȃ��悤��
		if (m_rot.y >= D3DX_PI)
		{
			m_rot.y -= D3DX_PI * 2.0f;
		}
		if (m_rot.y <= -D3DX_PI)
		{
			m_rot.y += D3DX_PI * 2.0f;
		}

		// ��]�p�x��1.57����A-0.1��艺�ɂȂ�Ȃ��悤��
		if (m_rot.x >= ROT_X_MAX_ANGLE)
		{
			m_rot.x = ROT_X_MAX_ANGLE;
		}
		if (m_rot.x <= ROT_X_MIN_ANGLE)
		{
			m_rot.x = ROT_X_MIN_ANGLE;
		}
	}

	//�}�E�X������I�t��
	if (nCameraType == 1)
	{
		//W���������Ƃ�
		if (pInputKeyboard->GetPress(DIK_U) == true)
		{
			m_posV.y += 30.0f;
		}

		//S���������Ƃ�
		if (pInputKeyboard->GetPress(DIK_J) == true)
		{
			m_posV.y -= 30.0f;
		}
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CCamera::Draw(void)
{

}

//=============================================================================
// �}�E�X���쏈��
//=============================================================================
void CCamera::Mouseoperation(void)
{
	// �}�E�X�ʒu�擾
	GetCursorPos(&m_Mousepoint);

	// �}�E�X�J�[�\���̈ʒu�Œ�
	SetCursorPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	//�J�[�\���̔�\��
	ShowCursor(false);

	// �L�[�{�[�h�擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//�J�������Z�b�g
	if (pInputKeyboard->GetPress(DIK_M) == true)
	{
		//�p�x��0�ɂ���
		m_fverticalAngle = 0.0f;
		m_fhorizontalAngle = 0.0f;
	}

	// �}�E�X���ǂꂾ�����������v�Z (��������) m_fMouseSpeed�͔��f���鑬�x
	m_fhorizontalAngle -= m_fMouseSpeed * float(SCREEN_WIDTH / 2 - m_Mousepoint.x);

	// �}�E�X���ǂꂾ�����������v�Z (��������) m_fMouseSpeed�͔��f���鑬�x
	m_fverticalAngle += m_fMouseSpeed * float(SCREEN_HEIGHT / 2 - m_Mousepoint.y);

	//�J�n���̃J�����̊p�x�����߂�
	m_rot.y = (m_fhorizontalAngle);
	m_rot.x = m_fverticalAngle;

	// �����A���O����3.14����A-3.14��艺�ɂȂ�Ȃ��悤��
	if (m_fhorizontalAngle >= D3DX_PI)
	{
		m_fhorizontalAngle -= D3DX_PI * 2.0f;
	}
	if (m_fhorizontalAngle <= -D3DX_PI)
	{
		m_fhorizontalAngle += D3DX_PI * 2.0f;
	}

	// �����A���O����1.57����A-0.1��艺�ɂȂ�Ȃ��悤��
	if (m_fverticalAngle >= ROT_X_MAX_ANGLE)
	{
		m_fverticalAngle = ROT_X_MAX_ANGLE;
	}
	if (m_fverticalAngle <= ROT_X_MIN_ANGLE)
	{
		m_fverticalAngle = ROT_X_MIN_ANGLE;
	}
}

//=============================================================================
// �J�����ݒu
//=============================================================================
void CCamera::SetCamera(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���ʈȏ㎞�Ɏg�p
	//for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		// �r���[�|�[�g���擾
		//pDevice->SetViewport(&g_camera[nIdx].viewport);

		// �v���W�F�N�V�����}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxProjection);

		// �v���W�F�N�V�����}�g���b�N�X�̍쐬
		D3DXMatrixPerspectiveFovLH(
			&m_mtxProjection,
			D3DXToRadian(45.0f),									// ��p�̐ݒ�
			(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,				// ��ʔ䗦�̐ݒ� �r���[�|�[�g�̕�����
			10.0f,													// ��O���E�̕`�拗��
			50000.0f);												// �����E�̕`�拗��

		// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

		// �r���[�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&m_mtxView);

		// �r���[�}�g���b�N�X�̍쐬
		D3DXMatrixLookAtLH(&m_mtxView, &m_posV, &m_posR, &m_vecU);

		// �r���[�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
	}
}
