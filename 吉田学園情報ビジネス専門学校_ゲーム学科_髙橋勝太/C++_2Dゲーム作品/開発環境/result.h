//=============================================================================
//
// リザルト画面処理 [game2.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _RESULT_H_
#define _RESULT_H_

//==============================================================================
//インクルード
//==============================================================================
#include "main.h"
#include "scene.h"
#include "scene2D.h"
#include "player.h"

//=============================================================================
// リザルト画面クラスの定義
//=============================================================================
class CResult : public CScene
{
public:
	CResult();									//コンストラクタ
	~CResult();									//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY);		//初期化処理
	void Uninit(void);												//終了処理
	void Update(void);												//更新処理
	void Draw(void);												//描画処理

	static CResult *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY);	//生成処理

private:
	static CPlayer				*m_pPlayer;			//プレイヤーへのポインタ	ホーミング時に使用
	LPD3DXFONT					m_pTimeFontGame;	// 表示用フォント
};

#endif