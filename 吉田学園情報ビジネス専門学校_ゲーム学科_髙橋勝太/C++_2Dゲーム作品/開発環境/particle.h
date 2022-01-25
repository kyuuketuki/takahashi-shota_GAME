//=============================================================================
//
// パーティク処理 [particl.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _PARTICL_H_
#define _PARTICL_H_

//==============================================================================
//インクルード
//==============================================================================
#include "main.h"
#include "scene2D.h"

//マクロ定義
#define PARTICL_SIZE (10)

//=============================================================================
// パーティクルクラスの定義
//=============================================================================
class CParticl : public CScene2D
{
public:
	CParticl(int nPriority = 4);				//コンストラクタ
	virtual ~CParticl();						//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int nLife, float fSpeed, float fSizeX, float fSizeY, float fAngle);	//初期化処理
	void Uninit(void);																													//終了処理
	void Update(void);																													//更新処理
	void Draw(void);																													//描画処理

	static CParticl *Create(D3DXVECTOR3 pos, D3DXCOLOR col, int nLife, float fSpeed, float fSizeX, float fSizeY, float fAngle);			//生成処理
	static HRESULT Load(void);																											//テクスチャ読み込み
	static void Unload(void);																											//テクスチャ破棄

private:
	D3DXVECTOR3 m_pos;							//位置
	D3DXVECTOR3 m_move;							//移動量
	D3DXCOLOR	m_col;							//カラー
	int			m_nLife;						//ライフ
	float		m_fSpeed;						//速度
	float		m_fSizeX;						//サイズ
	float		m_fSizeY;						//サイズ

	static LPDIRECT3DTEXTURE9 m_pTexture;	//テクスチャのポインタ
};

#endif