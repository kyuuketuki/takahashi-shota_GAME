//=============================================================================
//
// 爆発処理 [map.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _MAP_H_
#define _MAP_H_

#include "main.h"
#include "scene3D.h"

//=============================================================================
// マップクラスの定義
//=============================================================================

//継承先描画クラス
class CMap : public CScene3D
{
public:
	CMap();									//コンストラクタ
	virtual ~CMap();						//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY);							//初期化処理
	void Uninit(void);																	//終了処理
	void Update(void);																	//更新処理
	void Draw(void);																	//描画処理

	static CMap *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY);				//生成処理
	static HRESULT Load(void);															//テクスチャ読み込み
	static void Unload(void);															//テクスチャ破棄

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャのポインタ
	int m_nCounterAnime;					//アニメーションカウンター
	int m_nPatternAnime;					//アニメーションパターン
};

#endif