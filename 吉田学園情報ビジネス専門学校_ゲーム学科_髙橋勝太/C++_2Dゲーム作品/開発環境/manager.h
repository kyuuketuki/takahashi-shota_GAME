//=============================================================================
//
// �}�l�[�W���[���� [manager.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _MANAGER_H_
#define _MANAGER_H_

//==============================================================================
//�C���N���[�h
//==============================================================================
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "player.h"
#include "sound.h"
#include "score.h"
#include "title.h"
#include "tutorial.h"
#include "menu.h"
#include "select.h"
#include "game.h"
#include "game2.h"
#include "gamepad.h"
#include "result.h"
#include "pause.h"
#include "camera.h"
#include "light.h"
#include "sceneX.h"
#include <stdio.h>

//�O���錾
class CLight;
class CCamera;

//=============================================================================
// �}�l�[�W���[�N���X�̒�`
//=============================================================================
class CManager
{
public:
	typedef enum
	{
		MODE_TITLE = 0,
		MODE_MENU,
		MODE_SELECT,
		MODE_TUTORIAL,
		MODE_GAME,
		MODE_GAME2,
		MODE_RESULT,
		MODE_PAUSE,
		MODE_MAX
	}MODE;

	CManager();								//�R���X�g���N�^
	~CManager();							//�f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);		//����������
	static void SetMode(MODE mode);									//�I������
	void Uninit(void);												//�X�V����
	void Update(void);												//�`�揈��
	void Draw(void);
	
	//�ÓI�����o�錾
	static CInputKeyboard	*GetInputKeyboard(void);				
	static CRenderer		*GetRenderer(void);
	static CSound			*GetSound(void);
	static CCamera			*GetCamera(void);

	//���[�h���
	static MODE GetMode(void) { return m_mode; }

	//�Q�[���p�b�h���
	static CGamepad *GetGamepad(void) { return m_pGamepad; }
	static CGamepad *m_pGamePad;

	//�v���C���[HP�֌W
	static int GetPlayerLife(void);
	static void SetMaxPlayerLife(int nLife);
	static int GetMaxPlayerLife(void);
	static void SetPlayerLife(int nLife);
	static void DamagePlayerLife(int nLife);
	static void RecoveryPlayerLife(int nLife);

	//�v���C���[�^�C�v�֌W
	static int GetPlayerType(void);
	static void SetPlayerType(int nType);

	//�G��|�����J�E���g
	static int GetEnemyDead(void);
	static void SetEnemyDead(int nData);
	static void AddEnemyDead(int nData);

	//�Q�[���X�e�[�W
	static int GetGameStage(void);
	static void SetGameStage(int nData);

	//Pause���
	static bool GetPause();

	//�N���A���
	static bool GetGameClear(void);
	static void SetGameClear(bool bData);

	// �^�C�}�[�\��
	HRESULT InitTime(void);
	void UninitTime(void);
	void UpdateTime(void);
	void DrawTime(void);

private:
	//�N���X�ւ̃|�C���^
	static CRenderer		*m_pRenderer;
	static CInputKeyboard	*m_pInputKeyboard;
	static CInput			*m_pInput;
	static CPlayer			*m_pPlayer;
	static CSound			*m_pSound;
	static CScene			*m_pScene;
	static CScore			*m_pScore;
	static CNumber			*m_pNumber;
	static CGamepad			*m_pGamepad;
	static CTitle			*m_pTitle;
	static CMenu			*m_pMenu;
	static CSelect			*m_pSelect;
	static CTutorial		*m_pTutorial;
	static CGame			*m_pGame;
	static CGame2			*m_pGame2;
	static CResult			*m_pResult;
	static CPause			*m_pPause;
	static CCamera			*m_pCamera;
	static CLight			*m_pLight;
	static CSceneX			*m_pSceneX;
	static MODE				m_mode;

	LPD3DXFONT	m_pTimeFont;					// �\���p�t�H���g
	DWORD		m_dwGameStartTime;				// �Q�[���J�n����
	DWORD		m_dwGameTime;					// �Q�[���o�ߎ���
	static bool m_bEndGame;						// �I���t���O
	float		m_fTime;						// ����
};

#endif
