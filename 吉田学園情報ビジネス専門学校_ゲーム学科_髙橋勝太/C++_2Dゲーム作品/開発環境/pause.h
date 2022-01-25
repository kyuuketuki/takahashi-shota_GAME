//=============================================================================
//
// ポーズ処理 [pause.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _PAUSE_H_
#define _PAUSE_H_

//==============================================================================
//インクルード
//==============================================================================
#include "main.h"
#include "scene.h"
#include "scene2D.h"

//=============================================================================
// ポーズ画面クラスの定義
//=============================================================================
class CPause : public CScene
{
public:
	CPause(int nPriority = 0, int nType = 2);				//コンストラクタ;									
	~CPause();												//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY);			//初期化処理
	void Uninit(void);													//終了処理
	void Update(void);													//更新処理
	void Draw(void);													//描画処理

	//生成処理
	static CPause *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY);	
};																		
																		
#endif