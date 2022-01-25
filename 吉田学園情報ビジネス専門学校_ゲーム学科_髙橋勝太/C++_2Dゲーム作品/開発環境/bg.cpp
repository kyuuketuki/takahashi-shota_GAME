//=============================================================================
//
// バックテクスチャ処理 [bg.cpp]
// Author : takahashi shota
//
//=============================================================================

//=============================================================================
//インクルード読み込み
//=============================================================================
#include "bg.h"
#include "manager.h"
#include "scene2D.h"
#include "scene.h"

// 静的メンバ変数宣言
LPDIRECT3DTEXTURE9 CBg::m_apTexture[MAX_BG] = {};

//=============================================================================
// コンストラクタ
//=============================================================================
CBg::CBg(int nPriority) : CScene(nPriority)
{
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		m_apScene2D[nCnt] = NULL;
	}
}

//=============================================================================
// デストラクタ
//=============================================================================
CBg::~CBg()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBg::Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	// 変数の初期化
	m_pos = pos;

	//一枚目の背景
	m_apScene2D[0] = new CScene2D;
	m_apScene2D[0]->Init(pos , fSizeX, fSizeY);
	m_apScene2D[0]->BindTexture(m_apTexture[0]);

	//二枚目の背景
	m_apScene2D[1] = new CScene2D;
	m_apScene2D[1]->Init(pos, fSizeX, fSizeY);
	m_apScene2D[1]->BindTexture(m_apTexture[1]);

	//三枚目の背景
	m_apScene2D[2] = new CScene2D;
	m_apScene2D[2]->Init(pos, fSizeX, fSizeY);
	m_apScene2D[2]->BindTexture(m_apTexture[2]);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBg::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		m_apScene2D[nCnt]->Uninit();
		m_apScene2D[nCnt] = NULL;
	}

	// オブジェクト破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBg::Update(void)
{
	for (int nCntBg = 0; nCntBg < MAX_BG; nCntBg++)
	{
		//背景を動かす速度
		m_nCntAnime -= 0.0005f;

		//制限
		if (m_nCntAnime <= -1.0f)
		{
			m_nCntAnime = 0.0f;
		}

		//背景を動かす処理
		m_apScene2D[nCntBg]->SetBg(m_nCntAnime * (nCntBg + 1));
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CBg::Draw(void)
{
	for (int nCntBg = 0; nCntBg < MAX_BG; nCntBg++)
	{
		// CScene2Dの描画処理
		m_apScene2D[nCntBg]->Draw();
	}
}

//=============================================================================
// 生成処理
//=============================================================================
CBg * CBg::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	// ポインタ変数の生成
	CBg *pBg;
	pBg = new CBg;

	// NULLチェック
	if (pBg != NULL)
	{
		//背景の生成
		pBg->Init(pos, fSizeX, fSizeY);
	}

	return pBg;
}

//=============================================================================
// テクスチャ読み込み
//=============================================================================
HRESULT CBg::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg101.png", &m_apTexture[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg101.png", &m_apTexture[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg102.png", &m_apTexture[2]);

	return S_OK;
}

//=============================================================================
// テクスチャ破棄
//=============================================================================
void CBg::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_BG; nCnt++)
	{
		if (m_apTexture != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}
