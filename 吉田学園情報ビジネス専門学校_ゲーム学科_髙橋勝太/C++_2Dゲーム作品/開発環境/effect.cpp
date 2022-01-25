//=============================================================================
//
// エフェクト処理 [effect.cpp]
// Author : takahashi shota
//
//=============================================================================

//=============================================================================
//インクルード読み込み
//=============================================================================
#include "effect.h"
#include "manager.h"

// 静的メンバ変数宣言
LPDIRECT3DTEXTURE9 CEffect::m_pTexture = NULL;

//=============================================================================
// インストラクタ
//=============================================================================
CEffect::CEffect(int nPriority) : CScene2D(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nLife = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CEffect::~CEffect()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CEffect::Init(D3DXVECTOR3 pos, int nLife, float fSizeX, float fSizeY, D3DXCOLOR col)
{
	// CScene2Dの初期化処理
	CScene2D::Init(pos, fSizeX, fSizeY);

	//メンバ変数に代入
	m_nLife = nLife;
	m_col = col;

	//色情報を伝える
	SetEffect(col,1);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CEffect::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CEffect::Update(void)
{
	// 現在の位置の取得
	D3DXVECTOR3 pos = GetPosition();

	//更新
	CScene2D::Update();

	//エフェクトをだんだん透明にする
	SetEffect(m_col, m_nLife);
	
	//エフェクトのライフを減らす
	m_nLife--;

	//エフェクトライフが0以下になったとき
	if (m_nLife <= 0)
	{
		Uninit();
	}

	//範囲外の場合
	else if (pos.y <= 0)
	{
		Uninit();
	}
	else if (pos.y >= SCREEN_HEIGHT)
	{
		Uninit();
	}
	else if (pos.x <= 0)
	{
		Uninit();
	}
	else if (pos.x >= SCREEN_WIDTH)
	{
		Uninit();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CEffect::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice;
	pDevice = CManager::GetRenderer()->GetDevice();

	//加算合成
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	CScene2D::Draw();

	//加算合成を外す
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// 生成処理
//=============================================================================
CEffect * CEffect::Create(D3DXVECTOR3 pos, int nLife, float fSizeX, float fSizeY, D3DXCOLOR col)
{
	//エフェクトを生成
	CEffect *pEffect = NULL;
	pEffect = new CEffect;

	pEffect->Init(pos, nLife, fSizeX, fSizeY , col);

	//テクスチャを入れる
	pEffect->BindTexture(m_pTexture);

	return pEffect;
}

//=============================================================================
// テクスチャの生成
//=============================================================================
HRESULT CEffect::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/effect000.jpg", &m_pTexture);

	return S_OK;
}

//=============================================================================
// テクスチャの破棄
//=============================================================================
void CEffect::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}