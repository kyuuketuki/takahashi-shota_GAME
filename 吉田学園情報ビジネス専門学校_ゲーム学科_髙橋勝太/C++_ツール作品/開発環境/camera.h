//=============================================================================
//
// �J�������� [camera.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _CAMERA_H_
#define _CAMERA_H_

//=============================================================================
//�C���N���[�h�ǂݍ���
//=============================================================================
#include "main.h"
#include "manager.h"

//=============================================================================
// �J�����N���X�̒�`
//=============================================================================
class CCamera
{
public:
	CCamera();								// �R���X�g���N�^
	virtual ~CCamera();						// �f�X�g���N�^

	HRESULT Init(void);						// ����������
	void Uninit(void);						// �I������
	void Update(void);						// �X�V����
	void Draw(void);						// �`�揈��

	void SetCamera(void);					// ��������
	void Mouseoperation(void);				// �}�E�X���쏈��


	static D3DXVECTOR3 GetRot(void) { return m_rot; }		// �����擾�p
	static D3DXVECTOR3 GetposV(void) { return m_posV; }		// ���_�擾
	static D3DXVECTOR3 GetposR(void) { return m_posR; }		// �����_�擾

private:
	D3DXMATRIX m_mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;		// �r���[�}�g���b�N�X	
	D3DXVECTOR3 m_posVDest;		// �ړI�̎��_	
	D3DXVECTOR3 m_posRDest;		// �ړI�̒����_
	D3DXVECTOR3 m_vecU;			// ������x�N�g��
	POINT m_Mousepoint;			// �}�E�X���W
	int m_Rpos;					// ���f���̑O
	float m_fDistance;			// �J�����Ƃ̋���
	float m_fMouseSpeed;		// �J������]���x�i�}�E�X����j
	float m_fhorizontalAngle;	// ����
	float m_fverticalAngle;		// ����

	//�ÓI�����o�ϐ�
	static D3DXVECTOR3 m_posV;	// ���݂̎��_
	static D3DXVECTOR3 m_posR;	// ���݂̒����_
	static D3DXVECTOR3 m_rot;	// �J�����̊p�x
};

#endif