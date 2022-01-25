//=============================================================================
//
// ゲーム画面処理 [game.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _GAME_H_
#define _GAME_H_

//=============================================================================
//インクルード読み込み
//=============================================================================
#include "main.h"
#include "scene.h"
#include "scene2D.h"

//=============================================================================
// ゲーム画面クラスの定義
//=============================================================================
class CGame : public CScene
{
public:
	CGame();									//コンストラクタ
	~CGame();									//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY);	//初期化処理
	void Uninit(void);											//終了処理
	void Update(void);											//更新処理
	void Draw(void);											//描画処理

	//攻撃管理
	void Attack(void);											
	void Attack2(void);										
				
	//時間Get
	static int GetTime(void);

	//生成処理
	static CGame *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY);

private:
	LPD3DXFONT	m_pTimeFontGame;					// 表示用フォント
};

#endif