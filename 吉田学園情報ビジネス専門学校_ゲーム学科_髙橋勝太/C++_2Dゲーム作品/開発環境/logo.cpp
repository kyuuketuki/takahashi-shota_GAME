//=============================================================================
//
// ロゴ処理 [logo.cpp]
// Author : takahashi shota
//
//=============================================================================

//=============================================================================
//インクルード読み込み
//=============================================================================
#include "logo.h"
#include "manager.h"
#include "scene2D.h"
#include "scene.h"

// 静的メンバ変数宣言
LPDIRECT3DTEXTURE9 CLogo::m_apTextureLogo[MAX_LOGO] = {};
CPlayer *CLogo::m_pPlayer = NULL;

//グローバル宣言
int g_nTypeLogo = -1;			//特殊処理をするタイプを入れる
int g_nTypeMoveLogo = -1;		//特殊処理をするタイプを入れる
int g_nTypeCollarLogo = -1;		//特殊処理をするタイプを入れる
D3DXVECTOR3 g_posLogo;			//位置
D3DXCOLOR g_col;				//色情報

//=============================================================================
// コンストラクタ
//=============================================================================
CLogo::CLogo(int nPriority, int nType) : CScene2D(nPriority, nType)
{
	
}

//=============================================================================
// デストラクタ
//=============================================================================
CLogo::~CLogo()
{
	g_nTypeLogo = -1;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CLogo::Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nType)
{
	// CScene2Dの初期化処理
	CScene2D::Init(pos, fSizeX, fSizeY);

	//タイプを代入
	m_nType = nType;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CLogo::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CLogo::Update(void)
{	
	//特殊更新
	//タイトル移動
	if (m_nType == TITLE_UI)
	{
		// 現在の位置の取得
		D3DXVECTOR3 pos = GetPosition();

		//移動させる
		SetPosition(pos);

		//更新
		CScene2D::Update();
	}

	//プレイヤー当たり判定の移動
	if (m_nType == PLAYER_COLLISION_PINTER)
	{
		//色を変える
		CScene2D::SetCollar(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));

		//プレイヤーの位置を取得
		D3DXVECTOR3 posPlayer = m_pPlayer->GetPlayer();

		//移動させる
		SetPosition(posPlayer);

		//更新
		CScene2D::Update();
	}

	//特殊更新
	if (m_nType == FRAME)
	{
		//色を変える
		CScene2D::SetCollar(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	}

	//途中色変更
	if (m_nType == g_nTypeCollarLogo)
	{
		//色を変える
		CScene2D::SetCollar(g_col);
	}

	//途中移動
	if (m_nType == g_nTypeMoveLogo)
	{
		//初期化
		g_nTypeMoveLogo = -1;

		//移動させる
		SetPosition(g_posLogo);

		//更新
		CScene2D::Update();
	}
	
	//途中破棄
	if (g_nTypeLogo == m_nType)
	{
		Uninit();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CLogo::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// 生成処理
//=============================================================================
CLogo * CLogo::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nType)
{
	// ローカル変数宣言
	CLogo *pLogo = NULL;
	pLogo = new CLogo;

	// 初期化
	if (pLogo != NULL)
	{
		//ロゴ生成
		pLogo->Init(pos, fSizeX, fSizeY , nType);
	}

	// テクスチャ割り当て
	pLogo->BindTexture(m_apTextureLogo[nType]);

	return pLogo;
}

//=============================================================================
// テクスチャの読み込み
//=============================================================================
HRESULT CLogo::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// テクスチャの読み込み	
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/frame001a.png", &m_apTextureLogo[FRAME]);

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg100.png", &m_apTextureLogo[BG01]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg101.png", &m_apTextureLogo[BG02]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg102.png", &m_apTextureLogo[BG03]);

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/title01.png", &m_apTextureLogo[TITLE_UI]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/press_enter.png", &m_apTextureLogo[TITLE_UI_PRESS_ENTER]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/logo_game.jpg", &m_apTextureLogo[TITLE_UI_GAMESTART]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/logo_操作説明.jpg", &m_apTextureLogo[TITLE_UI_TUTORIAL]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/logo_終了.jpg", &m_apTextureLogo[TITLE_UI_END]);

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bullet000.png", &m_apTextureLogo[PLAYER_COLLISION_PINTER]);

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_01.png", &m_apTextureLogo[PLAYER01]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_02.png", &m_apTextureLogo[PLAYER02]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_03.png", &m_apTextureLogo[PLAYER03]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_04.png", &m_apTextureLogo[PLAYER04]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_05.png", &m_apTextureLogo[PLAYER05]);

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/status1.jpg", &m_apTextureLogo[SELECT_PLAYER01_STATUS]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/status2.jpg", &m_apTextureLogo[SELECT_PLAYER02_STATUS]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/status3.jpg", &m_apTextureLogo[SELECT_PLAYER03_STATUS]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/status4.jpg", &m_apTextureLogo[SELECT_PLAYER04_STATUS]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/status5.jpg", &m_apTextureLogo[SELECT_PLAYER05_STATUS]);
	
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_04_status.png", &m_apTextureLogo[SELECT_PLAYER01_STATUS2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_02_status.png", &m_apTextureLogo[SELECT_PLAYER02_STATUS2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_04_status.png", &m_apTextureLogo[SELECT_PLAYER03_STATUS2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_04_status.png", &m_apTextureLogo[SELECT_PLAYER04_STATUS2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/player_05_status.png", &m_apTextureLogo[SELECT_PLAYER05_STATUS2]);

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/keyboard.jpg", &m_apTextureLogo[TUTORIAL_KEYBOARD]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/gamepad.jpg", &m_apTextureLogo[TUTORIAL_GAMEPAD]);

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/gemeclear.png", &m_apTextureLogo[GAMECLEAR01]);

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/gameover.png", &m_apTextureLogo[GAMEOVER01]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/gameover1.jpg", &m_apTextureLogo[GAMEOVER_RESTART]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/gameover2.jpg", &m_apTextureLogo[GAMEOVER_START]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/gameover3.jpg", &m_apTextureLogo[GAMEOVER_END]);

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pause.png", &m_apTextureLogo[PAUSE01]);

	return S_OK;
}

//=============================================================================
// テクスチャの破棄
//=============================================================================
void CLogo::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_LOGO; nCnt++)
	{
		if (m_apTextureLogo != NULL)
		{
			m_apTextureLogo[nCnt]->Release();
			m_apTextureLogo[nCnt] = NULL;
		}
	}
}

//=============================================================================
// 破棄したいタイプ
//=============================================================================
void CLogo::TypeUninit(int nType)
{
	g_nTypeLogo = nType;
}

//=============================================================================
// 位置をずらしたいタイプ
//=============================================================================
void CLogo::TypeMove(D3DXVECTOR3 pos, int nTypeMove)
{
	g_posLogo = pos;
	g_nTypeMoveLogo = nTypeMove;
}

//=============================================================================
// 指定したタイプの色を変える
//=============================================================================
void CLogo::TypeChangeCollar(D3DXCOLOR col, int nTypeCollar)
{
	g_nTypeCollarLogo = nTypeCollar;
	g_col = col;
}

//=============================================================================
//
// メイン処理 [logopause.cpp]
// Author : takahashi shota
//
//=============================================================================

//ポーズ画面に表示させたい場合

//=============================================================================
// コンストラクタ
//=============================================================================
CLogoPause::CLogoPause(int nPriority, int nType) : CLogo(nPriority, nType)
{

}

//=============================================================================
// デストラクタ
//=============================================================================
CLogoPause::~CLogoPause()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CLogoPause::Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nType)
{
	CScene2D::Init(pos, fSizeX, fSizeY);

	CLogoPause::m_nType = nType;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CLogoPause::Uninit(void)
{
	CScene2D::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CLogoPause::Update(void)
{
	//特殊更新
	//タイトル移動
	if (m_nType == 0)
	{
		// 現在の位置の取得
		D3DXVECTOR3 pos = GetPosition();

		//移動させる
		SetPosition(pos);

		//更新
		CScene2D::Update();
	}

	//プレイヤー当たりポインター判定の移動
	if (m_nType == 5)
	{
		//色を変える
		CScene2D::SetCollar(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));

		//プレイヤーの位置を取得
		D3DXVECTOR3 posPlayer = m_pPlayer->GetPlayer();

		//移動させる
		SetPosition(posPlayer);

		//更新
		CScene2D::Update();
	}

	if (m_nType == 9)
	{
		//色を変える
		CScene2D::SetCollar(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	}

	if (m_nType == g_nTypeCollarLogo)
	{
		//色を変える
		CScene2D::SetCollar(g_col);
	}

	//途中移動
	if (m_nType == g_nTypeMoveLogo)
	{
		//初期化
		g_nTypeMoveLogo = -1;

		//移動させる
		SetPosition(g_posLogo);

		//更新
		CScene2D::Update();
	}

	//途中終了
	if (g_nTypeLogo == m_nType)
	{
		Uninit();
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CLogoPause::Draw(void)
{
	CScene2D::Draw();
}

//=============================================================================
// 生成処理
//=============================================================================
CLogoPause * CLogoPause::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nType)
{
	// ローカル変数宣言
	CLogoPause *pLogoPause = NULL;
	pLogoPause = new CLogoPause;

	// 初期化
	if (pLogoPause != NULL)
	{
		pLogoPause->Init(pos, fSizeX, fSizeY, nType);
	}

	// テクスチャ割り当て
	pLogoPause->BindTexture(m_apTextureLogo[nType]);

	return pLogoPause;
}

//=============================================================================
// テクスチャの破棄
//=============================================================================
void CLogoPause::Unload(void)
{
	for (int nCnt = 0; nCnt < MAX_LOGO; nCnt++)
	{
		if (m_apTextureLogo != NULL)
		{
			m_apTextureLogo[nCnt]->Release();
			m_apTextureLogo[nCnt] = NULL;
		}
	}
}

//=============================================================================
// 破棄したいタイプ
//=============================================================================
void CLogoPause::TypeUninit(int nType)
{
	g_nTypeLogo = nType;
}

//=============================================================================
// 位置をずらしたいタイプ
//=============================================================================
void CLogoPause::TypeMove(D3DXVECTOR3 pos, int nTypeMove)
{
	g_posLogo = pos;
	g_nTypeMoveLogo = nTypeMove;
}

//=============================================================================
// 色を変えたいタイプ
//=============================================================================
void CLogoPause::TypeChangeCollar(D3DXCOLOR col, int nTypeCollar)
{
	g_nTypeCollarLogo = nTypeCollar;
	g_col = col;
}
