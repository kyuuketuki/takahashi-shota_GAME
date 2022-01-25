//=============================================================================
//
// バックテクスチャ処理 [bg.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _BG_H_
#define _BG_H_

//=============================================================================
//インクルード読み込み
//=============================================================================
#include "main.h"
#include "scene.h"
#include "scene2D.h"

//マクロ定義
#define MAX_BG (3)		//背景の最大数

//=============================================================================
// 背景クラスの定義
//=============================================================================
class CBg : public CScene
{
public:
	CBg(int nPriority = 0);				//コンストラクタ
	~CBg();								//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY);				//初期化処理
	void Uninit(void);														//終了処理
	void Update(void);														//更新処理
	void Draw(void);														//描画処理

	static CBg *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY);		//生成処理
	static HRESULT Load(void);												//テクスチャ読み込み
	static void Unload(void);												//テクスチャ破棄
																			
	D3DXVECTOR3 GetPosition(void) { return m_pos; }

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BG];			// 用意するテクスチャの数
	CScene2D *m_apScene2D[MAX_BG];							// シーン2Dへのポインタ
	D3DXVECTOR3 m_pos;										// 位置情報
	float m_nCntAnime;										// テクスチャをずらす
};

#endif