//=============================================================================
//
// マネージャー処理 [manager.cpp]
// Author : takahashi shota
//
//=============================================================================

//=============================================================================
//インクルード読み込み
//=============================================================================
#include "manager.h"
#include "scene.h"
#include "scene2D.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "explosion.h"
#include "sound.h"
#include "bg.h"
#include "effect.h"
#include "polygon.h"
#include "score.h"
#include "number.h"
#include "logo.h"
#include "life.h"
#include "animation.h"
#include "item.h"
#include "menu.h"
#include "gamepad.h"
#include "fade.h"
#include "result.h"
#include "particle.h"

//=============================================================================
// 静的メンバ変数
//=============================================================================
CRenderer		*CManager::m_pRenderer = NULL;
CInputKeyboard	*CManager::m_pInputKeyboard = NULL;
CInput			*CManager::m_pInput = NULL;
CPlayer			*CManager::m_pPlayer = NULL;
CSound			*CManager::m_pSound = NULL;
CScene			*CManager::m_pScene = NULL;
CScore			*CManager::m_pScore = NULL;
CNumber			*CManager::m_pNumber = NULL;
CGamepad		*CManager::m_pGamepad = NULL;
CTitle			*CManager::m_pTitle = NULL;
CMenu			*CManager::m_pMenu = NULL;
CSelect			*CManager::m_pSelect = NULL;
CTutorial		*CManager::m_pTutorial = NULL;
CGame			*CManager::m_pGame = NULL;
CGame2			*CManager::m_pGame2 = NULL;
CResult			*CManager::m_pResult = NULL;
CPause			*CManager::m_pPause = NULL;
CCamera			*CManager::m_pCamera = NULL;
CLight			*CManager::m_pLight = NULL;
CSceneX			*CManager::m_pSceneX = NULL;

//初期の画面
CManager::MODE	CManager::m_mode = MODE_TITLE;

//経過時間を表示させる
bool	CManager::m_bEndGame = false;

int		g_nPlayerType = 0;			//プレイヤーのタイプを記録
int		g_nPlayerLife = 0;			//プレイヤーの体力を記録
int		g_nMaxPlayerLife = 5;		//最大体力

int		nTimeManagr = 0;			//ゲームオーバー時にカウントする変数
int		g_EnemyDead = 0;			//中ボスを倒した数を記録

int		g_nGameStage = 0;			//現在のステージ情報

bool	g_bGameOver = false;		//ゲームオーバー時使用
bool	g_bGameOverLogo = false;	//ゲームオーバー時使用

bool	g_bPause = false;			//ポーズ状態

bool	g_bGameClear = false;		//クリア条件

//=============================================================================
// コンストラクタ
//=============================================================================
CManager::CManager()
{
	//初期化
	m_pTimeFont = NULL;
	m_dwGameStartTime = 0;
	m_dwGameTime = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CManager::~CManager()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	//レンダラー作成
	if (m_pRenderer == NULL)
	{
		m_pRenderer = new CRenderer;
		m_pRenderer->Init(hWnd, bWindow);
	}

	//キーボード生成
	m_pInputKeyboard = new CInputKeyboard;
	m_pInputKeyboard->Init(hInstance, hWnd);

	m_pGamepad = new CGamepad;
	m_pGamepad->Init(hInstance, hWnd);

	//サウンド生成
	m_pSound = new CSound;
	m_pSound->Init(hWnd);

	//カメラ生成
	m_pCamera = new CCamera;
	m_pCamera->Init();

	//ライト生成
	m_pLight = new CLight;
	m_pLight->Init();
	
	//アニメーションテクスチャの読み込み
	CAnimasion::Load();

	//エフェクトテクスチャの読み込み
	CEffect::Load();

	// 弾テクスチャ読み込み
	CBullet::Load();

	// プレイヤーテクスチャ読み込み
	CPlayer::Load();

	//敵のテクスチャ
	CEnemy::Load();

	// 爆破テクスチャの読み込み
	CExplosion::Load();
	
	// 背景テクスチャの読み込み
	CBg::Load();

	//ロゴのテクスチャの読み込み
	CLogo::Load();

	//番号のテクスチャ読み込み
	CNumber::Load();

	//ライフのテクスチャの読み込み
	CLife::Load();

	//アイテムテクスチャの読み込み
	CItem::Load();

	//パーティクルのテクスチャの読み込み
	CParticl::Load();

	//m_pPause->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f);

	//モード設定
	SetMode(m_mode);

	// タイマーの初期化
	InitTime();

	return S_OK;
}

//==============================================================================
// 
//==============================================================================
void CManager::SetMode(MODE mode)
{
	//終了処理
	CScene::ReleaseAll();

	//フェードをクリエイト
	CFade::Create(m_mode);

	//画面遷移時に初期化
	nTimeManagr = 0;
	g_nPlayerLife = 0;
	g_bGameOver = false;
	g_bGameOverLogo = false;
	g_bPause = false;

	g_EnemyDead = 0;		//Clear条件の初期化

	switch (mode)
	{
	case MODE_TITLE:

		//タイトル画面の初期化処理
		g_nPlayerLife = 1;		//ゲームオーバーのロゴを出現させない
		m_pTitle->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f);
		break;

	case MODE_MENU:

		//タイトル画面の初期化処理
		g_nPlayerLife = 1;		//ゲームオーバーのロゴを出現させない
		m_pMenu->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f);
		break;

	case MODE_SELECT:

		//タイトル画面の初期化処理
		g_nPlayerLife = 1;		//ゲームオーバーのロゴを出現させない
		m_pSelect->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f);
		break;

	case MODE_TUTORIAL:

		//タイトル画面の初期化処理
		g_nPlayerLife = 1;		//ゲームオーバーのロゴを出現させない
		m_pTutorial->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f);
		break;

	case MODE_GAME:
		g_bGameClear = false;

		//ゲーム画面の初期化処理
		m_pGame->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f);
		m_pPause->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f);
		break;

	case MODE_GAME2:
		g_bGameClear = false;

		//ゲーム画面の初期化処理
		m_pGame2->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f);
		m_pPause->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f);
		break;

	case MODE_RESULT:

		//ゲーム画面の初期化処理
		g_nPlayerLife = 1;
		m_pResult->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f);
		break;
	}

	m_mode = mode;
}

//=============================================================================
// 終了処理
//=============================================================================
void CManager::Uninit(void)
{
	//オブジェクトクラスの破棄
	CScene::ReleaseAll();

	// テクスチャの開放
	CBullet::Unload();
	CEffect::Unload();
	CPlayer::Unload();
	CEnemy::Unload();
	CExplosion::Unload();
	CBg::Unload();
	CLogo::Unload();
	CNumber::Unload();
	CLife::Unload();
	CAnimasion::Unload();
	CItem::Unload();
	CParticl::Unload();

	//入力処理の破棄
	if (m_pInput != NULL)
	{
		m_pInput->Uninit();
		delete m_pInput;
		m_pInput = NULL;
	}

	//サウンドの破棄
	if (m_pSound != NULL)
	{
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = NULL;
	}

	//レンダリングクラスの破棄
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	// タイマーフォントの破棄
	UninitTime();
}

//=============================================================================
// 更新処理
//=============================================================================
void CManager::Update(void)
{
	//プレイヤーのライフを記憶
	int nLifePlayer = CManager::GetPlayerLife();

	//ゲームパッドのポインタ宣言
	CGamepad *pGamepad;
	pGamepad = CManager::GetGamepad();

	//カメラの更新
	m_pCamera->Update();

	//ゲームオーバー時
	if (nLifePlayer <= 0)
	{
		if (g_bGameOverLogo == false)
		{
			CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, CScene::GAMEOVER01);
			g_bGameOverLogo = true;
		}

		nTimeManagr++;

		if (nTimeManagr >= 150)
		{
			if (g_bGameOver == false)
			{
				//モード設定
				CFade::SetFade(CFade::FADE_OUT, CManager::MODE_RESULT, D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.0f));	// シーン遷移

				g_bGameOver = true;
			}
		}
	}

	//キーボードの更新処理
	if (m_pInputKeyboard != NULL)
	{
		m_pInputKeyboard->Update();
	}

	//ゲームパッドの更新処理
	if (m_pGamepad != NULL)
	{
		m_pGamepad->Update();
	}

	//レンダラーの更新
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Update();
	}

	// タイマー更新
	UpdateTime();

	////画面遷移　スキップ機能
	//if (m_pInputKeyboard->GetTrigger(DIK_0) == true)
	//{
	//	//モード設定
	//	CFade::SetFade(CFade::FADE_OUT, CManager::MODE_TITLE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	// シーン遷移
	//}

	////ステージスキップ
	//if (m_pInputKeyboard->GetTrigger(DIK_1) == true)
	//{
	//	CFade::SetFade(CFade::FADE_OUT, CManager::MODE_GAME, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	// シーン遷移
	//}

	//if (m_pInputKeyboard->GetTrigger(DIK_2) == true)
	//{
	//	CFade::SetFade(CFade::FADE_OUT, CManager::MODE_GAME2, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	// シーン遷移
	//}

	//ゲーム画面時のみにポーズを描画＆更新できる
	if (CManager::m_mode == MODE_GAME || CManager::m_mode == MODE_GAME2)
	{
		//ポーズの切り替えオン
		if (g_bPause == false)
		{
			if (m_pInputKeyboard->GetTrigger(DIK_P) == true || pGamepad->IsButtonDown(CInput::P))
			{
				g_bPause = true;
			}
		}

		//ポーズの切り替えオフ
		else if (g_bPause == true)
		{
			if (m_pInputKeyboard->GetTrigger(DIK_P) == true || pGamepad->IsButtonDown(CInput::P))
			{
				g_bPause = false;
			}
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CManager::Draw(void)
{
	if (m_pRenderer != NULL)
	{
		m_pRenderer->Draw();
	}
}

//==============================================================================
// タイマー初期化
//==============================================================================
HRESULT CManager::InitTime(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetRenderer()->GetDevice();

	// フォントオブジェクトの生成
	D3DXCreateFont(
		pDevice, 36, 0, 0, 0, FALSE,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		"Terminal",
		&m_pTimeFont);

	// 開始時刻取得
	m_dwGameStartTime = timeGetTime();

	return S_OK;
}

//==============================================================================
// タイマー更新
//==============================================================================
void CManager::UninitTime(void)
{
	if (m_pTimeFont != NULL)
	{
		m_pTimeFont->Release();
		m_pTimeFont = NULL;
	}
}

//==============================================================================
// タイマー更新
//==============================================================================
void CManager::UpdateTime(void)
{
	if (m_bEndGame == false)
	{
		// 経過時間更新
		m_dwGameTime = timeGetTime() - m_dwGameStartTime;
	}
}

//==============================================================================
// タイマー描画
//==============================================================================
void CManager::DrawTime(void)
{
#ifdef _DEBUG
	// ローカル変数宣言
	RECT rect = { 0,30,SCREEN_WIDTH,SCREEN_HEIGHT };
	char aStr[256];

	if (m_bEndGame == false)
	{
		//経過時間をメンバ関数に入れる
		m_fTime = (float)m_dwGameTime / 1000;
		
		//画面に表示させる
		sprintf(&aStr[0], "経過時間 : %.3f\n", m_fTime);

		// テキストの描画
		m_pTimeFont->DrawText(NULL, &aStr[0], -1, &rect, DT_CENTER, D3DCOLOR_RGBA(255, 255, 255, 255));
	}
#endif
}

//=============================================================================
// キーボードのGet関数
//=============================================================================
CInputKeyboard * CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//=============================================================================
// レンダラーのGet関数
//=============================================================================
CRenderer * CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//=============================================================================
// サウンドのGet関数
//=============================================================================
CSound * CManager::GetSound(void)
{
	return m_pSound;
}

//=============================================================================
// カメラポインターのGet関数
//=============================================================================
CCamera * CManager::GetCamera(void)
{
	return m_pCamera;
}

//=============================================================================
// Get関数 & 変数の値保存
//=============================================================================
int CManager::GetPlayerLife(void)				//プレイヤーの体力をGet
{
	return g_nPlayerLife;
}

void CManager::SetPlayerLife(int nLife)			//プレイヤーの体力をSet
{
	g_nPlayerLife = nLife;
}

void CManager::SetMaxPlayerLife(int nLife)		//最大体力をSet
{
	g_nMaxPlayerLife = nLife;
}

int CManager::GetMaxPlayerLife(void)			//最大体力をGet
{
	return g_nMaxPlayerLife;
}

void CManager::DamagePlayerLife(int nLife)		//体力を減らす
{
	g_nPlayerLife -= nLife;
}

void CManager::RecoveryPlayerLife(int nLife)	//体力を回復させる
{
	g_nPlayerLife += nLife;
}

int CManager::GetPlayerType(void)				//選択されたプレイヤー知らせる
{
	return g_nPlayerType;
}

void CManager::SetPlayerType(int nType)			//選択されたプレイヤーを記憶
{
	g_nPlayerType = nType;
}

int CManager::GetEnemyDead(void)				//敵を倒した数を知らせる
{
	return g_EnemyDead;
}

void CManager::SetEnemyDead(int nData)			//敵を倒した数を代入
{
	g_EnemyDead = nData;
}

void CManager::AddEnemyDead(int nData)			//敵を倒した数を加算
{
	g_EnemyDead += nData;
}

int CManager::GetGameStage(void)				//現在プレイ中をステージを記憶
{
	return g_nGameStage;
}

void CManager::SetGameStage(int nData)			//現在プレイ中のステージを知らせる
{
	g_nGameStage = nData;
}

bool CManager::GetPause()						//ポーズ常態を知らせる
{
	return g_bPause;
}

bool CManager::GetGameClear(void)				//クリア状態か知らせる
{
	return g_bGameClear;
}

void CManager::SetGameClear(bool bData)			//クリア状態にする
{
	g_bGameClear = bData;
}
