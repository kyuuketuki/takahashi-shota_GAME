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
	CCamera();								//�R���X�g���N�^
	virtual ~CCamera();						//�f�X�g���N�^

	HRESULT Init(void);						//����������
	void Uninit(void);						//�I������
	void Update(void);						//�X�V����
	void Draw(void);						//�`�揈��

	void SetCamera(void);					//��������

private:
	D3DXMATRIX m_mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX m_mtxView;			// �r���[�}�g���b�N�X
	D3DXVECTOR3 m_posV;			// ���݂̎��_
	D3DXVECTOR3 m_posR;			// ���݂̒����_
	D3DXVECTOR3 m_vecU;			// ������x�N�g��
	D3DXVECTOR3 m_rot;			// �J�����̊p�x
};

#endif