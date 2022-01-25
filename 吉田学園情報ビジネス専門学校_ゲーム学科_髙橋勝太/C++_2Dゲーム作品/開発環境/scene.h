//=============================================================================
//
// �V�[������ [scene.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _SCENE_H_
#define _SCENE_H_

//==============================================================================
//�C���N���[�h
//==============================================================================
#include "main.h"

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 nor;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
}VERTEX_3D;

//=============================================================================
// �V�[���N���X�̒�`
//=============================================================================
class CScene
{
public:
	//�I�u�W�F�N�g�̎��
	typedef enum
	{
		OBJTYPE_NONE = 0,
		OBJTYPE_PLAYER,				// �v���C���[
		OBJTYPE_ENEMY,				// �G
		OBJTYPE_ENEMY2,				// ���{�X
		OBJTYPE_ENEMY3,				// �{�X
		OBJTYPE_BULET_PLAYER,		// �v���C���[���甭�˂��ꂽ�e
		OBJTYPE_BULET_ENEMY,		// �G���甭�˂��ꂽ�e	(�ʏ�e)
		OBJTYPE_BULET_ENEMY2,		// �G���甭�˂��ꂽ�e2	(�_���e)
		OBJTYPE_BULET_ENEMY3,		// �G���甭�˂��ꂽ�e3	(�����e)
		OBJECT_MAX
	}OBJTYPE;

	//�G�̎��
	typedef enum
	{
		ENEMY_01 = 0,
		ENEMY_02,
		ENEMY_03,
		ENEMY_04,
		ENEMY_05,
		ENEMY_06,
		ENEMY_07,
		ENEMY_99,
		ENEMY_BOSS_01,
		ENEMY_BOSS_02,
		ENEMY_BOSS_03,
		ENEMY_MAX
	}ENEMY_TYPE;

	//�e�̎��
	typedef enum
	{
		BULLET_NORMAL = 0,			//�ʏ�e
		BULLET_AIMING,				//�e�̃z�[�~���O
		BULLET_MAX					//�ő���
	}BULLET;

	//�e�N�X�`���̎��
	typedef enum
	{
		FRAME = 0,

		BG01,
		BG02,
		BG03,

		TITLE_UI,
		TITLE_UI_PRESS_ENTER,
		TITLE_UI_GAMESTART,
		TITLE_UI_TUTORIAL,
		TITLE_UI_END,

		PLAYER_COLLISION_PINTER,

		PLAYER01,
		PLAYER02,
		PLAYER03,
		PLAYER04,
		PLAYER05,

		SELECT_PLAYER01_STATUS,
		SELECT_PLAYER02_STATUS,
		SELECT_PLAYER03_STATUS,
		SELECT_PLAYER04_STATUS,
		SELECT_PLAYER05_STATUS,

		SELECT_PLAYER01_STATUS2,
		SELECT_PLAYER02_STATUS2,
		SELECT_PLAYER03_STATUS2,
		SELECT_PLAYER04_STATUS2,
		SELECT_PLAYER05_STATUS2,

		TUTORIAL_KEYBOARD,
		TUTORIAL_GAMEPAD,

		GAMECLEAR01,

		GAMEOVER01,
		GAMEOVER_RESTART,
		GAMEOVER_START,
		GAMEOVER_END,

		PAUSE01,
	}UI;

	CScene(int nPriority = 1, int nType = 0);				//�R���X�g���N�^
	virtual ~CScene();										//�f�X�g���N�^

	virtual HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY) = 0;	//����������
	virtual void Uninit(void) = 0;											//�I������
	virtual void Update(void) = 0;											//�X�V����
	virtual void Draw(void) = 0;											//�`�揈��

	static void ReleaseAll(void);											//���ׂĂ̏I������
	static void UpdateAll(void);											//���ׂĂ̍X�V����
	static void DrawAll(void);												//���ׂĂ̕`�揈��

	//�V�[�������󂯓n��
	static CScene *GetScene(int nIdx, int nPriority);
	
	//���C�t�Ǘ�
	void SetLife(int nLife);
	void Damage(int nDamage);
	int GetLife(void);

	//�^�C�v�Ǘ�
	OBJTYPE GetObjType(void) { return m_objType; }
	void SetObjType(OBJTYPE objType) { m_objType = objType; }

	//�T�C�Y
	float GetSizeX(void) { return m_fSizeX; }
	void SetSizeXScene(float nSize) { m_fSizeX = nSize; }
	float GetSizeY(void) { return m_fSizeY; }
	void SetSizeYScene(float nSize) { m_fSizeY = nSize; }

	//�F���
	D3DXCOLOR GetCollar(void) { return m_col; }
	void SetCollar(D3DXCOLOR col) { m_col = col; }

	//�ʒu�Ǘ�
	virtual D3DXVECTOR3 GetPosition(void);

protected:
	void Release(void);

private:
	static int		m_NumAll;								//�����ԍ�
	int				m_nID;									//�i�[��̔ԍ�
	OBJTYPE			m_objType;								//�I�u�W�F�N�g�̎��
	float			m_fSizeX;								//�T�C�Y
	float			m_fSizeY;								//�T�C�Y
	int				m_nPriority;							// �D�揇��
	int				m_nType;								//�^�C�v
	int				m_nLife;								//���C�t

	//�F���
	D3DXCOLOR		m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//���X�g���p�ϐ�
	static CScene *m_pTop[6][3];	//�őO��
	static CScene *m_pCur[6][3];	//�Ō��
	CScene *m_pPrev;				//�O�̃|�C���^�[
	CScene *m_pNext;				//��̃|�C���^�[
	bool m_bDeath  = false;			//���S�t���O
};

#endif
