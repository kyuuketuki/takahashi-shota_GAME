//=============================================================================
//
// タイトル画面処理 [title.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _TITLE_H_
#define _TITLE_H_

//==============================================================================
//インクルード
//==============================================================================
#include "main.h"
#include "scene.h"
#include "scene2D.h"

//=============================================================================
// タイトルクラスの定義
//=============================================================================
class CTitle : public CScene
{
public:
	CTitle();								//コンストラクタ
	~CTitle();								//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY);				//初期化処理
	void Uninit(void);														//終了処理
	void Update(void);														//更新処理
	void Draw(void);														//描画処理

	static CTitle *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY);		//生成処理
};
#endif
