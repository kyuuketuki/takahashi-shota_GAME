//=============================================================================
//
// シーン処理 [scene.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _SCENE_H_
#define _SCENE_H_

//=============================================================================
//インクルード読み込み
//=============================================================================
#include "main.h"

//VERTEX_3Dの宣言
typedef struct
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 nor;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
}VERTEX_3D;

//=============================================================================
// シーンクラスの定義
//=============================================================================
class CScene
{
public:

	//UIのtypedef enum
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

		LIST,
	}UI;

	CScene(int nPriority = 1, int nType = 0);				//コンストラクタ
	virtual ~CScene();										//デストラクタ

	virtual HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY) = 0;	//初期化処理
	virtual void Uninit(void) = 0;											//終了処理
	virtual void Update(void) = 0;											//更新処理
	virtual void Draw(void) = 0;											//描画処理

	static void ReleaseAll(void);											//すべての終了処理
	static void UpdateAll(void);											//すべての更新処理
	static void DrawAll(void);												//すべての描画処理

	//優先順位の設定
	static CScene *GetScene(int nIdx, int nPriority);

	//サイズ
	float GetSizeX(void) { return m_fSizeX; }
	void SetSizeXScene(float nSize) { m_fSizeX = nSize; }
	float GetSizeY(void) { return m_fSizeY; }
	void SetSizeYScene(float nSize) { m_fSizeY = nSize; }

	//位置管理
	virtual D3DXVECTOR3 GetPosition(void);

protected:
	void Release(void);

private:
	int				m_nID;					//格納先の番号
	int				m_nPriority;			// 優先順位
	int				m_nType;				//タイプ
	float			m_fSizeX;				//サイズ
	float			m_fSizeY;				//サイズ
											
	//静的メンバ変数						 
	static int		m_NumAll;				//生成番号

	//リスト化用変数
	static CScene *m_pTop[6][3];			//最前列
	static CScene *m_pCur[6][3];			//最後尾
	CScene *m_pPrev;						//前のポインター
	CScene *m_pNext;						//後のポインター
	bool m_bDeath  = false;					//死亡フラグ
};

#endif
