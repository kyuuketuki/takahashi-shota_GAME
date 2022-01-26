//=============================================================================
//
// �Q�[����ʏ��� [game.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _GAME_H_
#define _GAME_H_

//=============================================================================
//�C���N���[�h�ǂݍ���
//=============================================================================
#include "main.h"
#include "scene.h"
#include "scene2D.h"
#include "debugproc.h"
#include "object3D.h"

//�O���錾
class CVertex;
class CObject3D;
class CScene3D;

//=============================================================================
// �Q�[����ʃN���X�̒�`
//=============================================================================
class CGame : public CScene
{
public:
	CGame();									//�R���X�g���N�^
	~CGame();									//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY);	//����������
	void Uninit(void);											//�I������
	void Update(void);											//�X�V����
	void Draw(void);											//�`�揈��

	void Switch(void);											//�؂�ւ�����

	//�A�h���X�ۑ�
	static CVertex		*GetVertex(void) { return m_pVertex; }
	static CObject3D	*GetObject(int nCnt) { return m_pObject3D[nCnt]; }

	//����������X�t�@�C�������点��
	static int GetObjectType3D(void);

	//�������������_�������点��
	static int GetVecter(void);
				
	//����Get
	static int GetTime(void);

	//�I���I�t�̐؂�ւ�
	static bool GetSwitchScene3D(void);
	static bool GetSwitchCollision(void);

	//�V���ɐ��������I�u�W�F�N�g3D�̐����L��
	static int GetMaxObject3D(void);

	//��������
	static CGame *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY);

	//�e�L�X�g��ǂݍ���
	void FailObject();
	void FailObject3D();

private:
	LPD3DXFONT	m_pTimeFontGame;						//�\���p�t�H���g
	CScene3D	*m_pScene3D[256];						//�������������A�h���X���L��

	//�ÓI�����o�ϐ�
	static CDebugProc	*m_pDebug;						//�f�o�b�N�\���̃����o�ϐ�
	static CVertex		*m_pVertex;						//�A�h���X�ۑ��p�|�C���^
	static CObject3D	*m_pObject3D[MAX_OBJECT_3D];	//�A�h���X�ۑ��p�|�C���^
};

#endif