//=============================================================================
//
// パーティクル処理 [particl.cpp]
// Author : takahashi shota
//
//=============================================================================

//=============================================================================
//インクルード読み込み
//=============================================================================
#include "particle.h"
#include "effect.h"
#include "manager.h"

// 静的メンバ変数宣言
LPDIRECT3DTEXTURE9 CParticl::m_pTexture = NULL;

//=============================================================================
// コンストラクタ
//=============================================================================
CParticl::CParticl(int nPriority)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CParticl::~CParticl()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CParticl::Init(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, int nLife, float fSpeed, float fSizeX, float fSizeY, float fAngle)
{
	// CScene2Dの初期化処理
	CScene2D::Init(pos, fSizeX, fSizeY);

	//メンバ変数に代入
	m_move = move;
	m_nLife = nLife;
	m_fSizeX = fSizeX;
	m_fSizeY = fSizeY;

	//色情報を入れる
	SetEffect(col, 1);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CParticl::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CParticl::Update(void)
{
	//更新
	CScene2D::Update();

	// 現在の位置の取得
	D3DXVECTOR3 pos = GetPosition();

	//移動処理
	pos += m_move;

	//移動させる
	SetPosition(pos);

	//弾のライフが0以下になったとき
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

	//体力減少
	m_nLife -= 1;
}

//=============================================================================
// 描画処理
//=============================================================================
void CParticl::Draw(void)
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
CParticl * CParticl::Create(D3DXVECTOR3 pos, D3DXCOLOR col, int nLife, float fSpeed, float fSizeX, float fSizeY, float fAngle)
{
	//パーティクを生成
	CParticl *pParticl = NULL;
	pParticl = new CParticl;

	//パーティクの乱射
	D3DXVECTOR3 move;
	float fA;
	fA = (float)(fAngle) / 100.0f;
	move.x = sinf(fA) * fSpeed;
	move.y = cosf(fA) * fSpeed;

	//テクスチャを入れる
	pParticl->BindTexture(m_pTexture);

	//初期化の移動
	pParticl->Init(pos, move, col, nLife, fSpeed, fSizeX, fSizeY, fAngle);

	return pParticl;
}

//=============================================================================
// テクスチャの生成
//=============================================================================
HRESULT CParticl::Load(void)
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
void CParticl::Unload(void)
{
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}