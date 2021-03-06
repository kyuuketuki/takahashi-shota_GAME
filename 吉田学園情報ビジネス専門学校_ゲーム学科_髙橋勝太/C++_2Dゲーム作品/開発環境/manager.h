//=============================================================================
//
// マネージャー処理 [manager.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _MANAGER_H_
#define _MANAGER_H_

//==============================================================================
//インクルード
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

//前方宣言
class CLight;
class CCamera;

//=============================================================================
// マネージャークラスの定義
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

	CManager();								//コンストラクタ
	~CManager();							//デストラクタ

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);		//初期化処理
	static void SetMode(MODE mode);									//終了処理
	void Uninit(void);												//更新処理
	void Update(void);												//描画処理
	void Draw(void);
	
	//静的メンバ宣言
	static CInputKeyboard	*GetInputKeyboard(void);				
	static CRenderer		*GetRenderer(void);
	static CSound			*GetSound(void);
	static CCamera			*GetCamera(void);

	//モード情報
	static MODE GetMode(void) { return m_mode; }

	//ゲームパッド情報
	static CGamepad *GetGamepad(void) { return m_pGamepad; }
	static CGamepad *m_pGamePad;

	//プレイヤーHP関係
	static int GetPlayerLife(void);
	static void SetMaxPlayerLife(int nLife);
	static int GetMaxPlayerLife(void);
	static void SetPlayerLife(int nLife);
	static void DamagePlayerLife(int nLife);
	static void RecoveryPlayerLife(int nLife);

	//プレイヤータイプ関係
	static int GetPlayerType(void);
	static void SetPlayerType(int nType);

	//敵を倒したカウント
	static int GetEnemyDead(void);
	static void SetEnemyDead(int nData);
	static void AddEnemyDead(int nData);

	//ゲームステージ
	static int GetGameStage(void);
	static void SetGameStage(int nData);

	//Pause状態
	static bool GetPause();

	//クリア常態
	static bool GetGameClear(void);
	static void SetGameClear(bool bData);

	// タイマー表示
	HRESULT InitTime(void);
	void UninitTime(void);
	void UpdateTime(void);
	void DrawTime(void);

private:
	//クラスへのポインタ
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

	LPD3DXFONT	m_pTimeFont;					// 表示用フォント
	DWORD		m_dwGameStartTime;				// ゲーム開始時刻
	DWORD		m_dwGameTime;					// ゲーム経過時間
	static bool m_bEndGame;						// 終了フラグ
	float		m_fTime;						// 時間
};

#endif
