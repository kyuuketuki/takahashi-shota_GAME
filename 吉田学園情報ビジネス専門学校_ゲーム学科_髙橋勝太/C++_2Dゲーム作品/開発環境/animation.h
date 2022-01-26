//=============================================================================
//
// アニメーション処理 [animasion.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _ANIMASION_H_
#define _ANIMASION_H_

//=============================================================================
//インクルード読み込み
//=============================================================================
#include "main.h"
#include "scene2D.h"

//マクロ定義
#define MAX_ANIME (18)

//=============================================================================
// アニメーションクラスの定義
//=============================================================================
class CAnimasion : public CScene2D
{
public:
	CAnimasion(int nPriority = 3, int nType = 0);			//コンストラクタ
	virtual ~CAnimasion();									//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nAnime, int nType);	//初期化処理
	void Uninit(void);																	//終了処理
	void Update(void);																	//更新処理
	void Draw(void);																	//描画処理

	//生成処理
	static CAnimasion *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nAnime, int nType);

	//テクスチャの読み込み＆消去
	static HRESULT Load(void);
	static void Unload(void);

	//テクスチャ情報の管理
	void Texture(int nType);

	//タイプ別で消去
	static void UninitType(int nUninitType);
	static void UninitTypeClear(void);

protected:
	D3DXVECTOR3 m_pos;									//移動量
	int m_nType;										//タイプ　テクスチャ識別
	int m_nTypeBuulet;									//特殊移動時に使用
	int m_nCounterAnime;								//アニメーションカウンター
	int m_nPatternAnime;								//アニメーションパターン
	int m_fCriss;										//ループ判定
	int m_nX;											//画像分割
	int m_nY;											//画像分割
	int m_nAnime;										//アニメーションスピード
	float m_fAnimeX;									//画像分割X
	float m_fAnimeY;									//画像分割Y
	float m_fColorFa = 1.0f;							//アルファ値

	//静的メンバ変数
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_ANIME];	//テクスチャのポインタ
};

//=============================================================================
// アニメーションクラスの定義(背景)
//=============================================================================
class CAnimasionBg : public CAnimasion
{
public:
	CAnimasionBg(int nPriority = 1, int nType = 0);		//コンストラクタ
	virtual ~CAnimasionBg();							//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nAnime, int nType);					   //初期化処理
	void Uninit(void);																					   //終了処理
	void Update(void);																					   //更新処理
	void Draw(void);																					   //描画処理

	static CAnimasionBg *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nAnime, int nType);	   //生成処理
	static void UninitTypeClear(void);																	   //途中破棄
};

#endif