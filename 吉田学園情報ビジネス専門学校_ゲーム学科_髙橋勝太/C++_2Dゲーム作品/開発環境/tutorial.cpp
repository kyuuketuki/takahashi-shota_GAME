//=============================================================================
//
// チュートリアル画面処理 [tutorial.cpp]
// Author : takahashi shota
//
//=============================================================================
#include "tutorial.h"
#include "manager.h"
#include "animation.h"
#include "item.h"
#include "life.h"
#include "enemy.h"
#include "logo.h"
#include "fade.h"

//グローバル宣言
int nPointer_Tutorial = 0;		//プレスカウント
bool g_bPressTutorial = false;	//生成処理に使用

//==============================================================================
// コンストラクタ
//==============================================================================
CTutorial::CTutorial()
{
	//初期化処理
	nPointer_Tutorial = 0;
	g_bPressTutorial = false;
}

//==============================================================================
// デストラクタ
//==============================================================================
CTutorial::~CTutorial()
{

}

//==============================================================================
// 初期化処理
//==============================================================================
HRESULT CTutorial::Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	return S_OK;
}


//==============================================================================
// 終了処理
//==============================================================================
void CTutorial::Uninit(void)
{
	// オブジェクト破棄
	Release();
}

//==============================================================================
// 更新処理
//==============================================================================
void CTutorial::Update(void)
{
	//キーボード取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//ゲームパッドのポインタ宣言
	CGamepad *pGamepad;
	pGamepad = CManager::GetGamepad();

	//カーソル移動
	//画面切り替え
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pGamepad->IsButtonDown(CInput::UP) == true || pGamepad->IsButtonDown(CInput::B) == true)
	{
		nPointer_Tutorial += 1;
		g_bPressTutorial = false;
	}

	if (nPointer_Tutorial == 0)
	{
		if (g_bPressTutorial == false)
		{
			//ロゴの移動
			CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 25);

			g_bPressTutorial = true;
		}
	}

	if (nPointer_Tutorial == 1)
	{
		if (g_bPressTutorial == false)
		{
			//ロゴの移動
			CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 26);

			g_bPressTutorial = true;
		}
	}

	if (nPointer_Tutorial == 2)
	{
		if (g_bPressTutorial == false)
		{
			//モード設定
			CFade::SetFade(CFade::FADE_OUT, CManager::MODE_MENU, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	// シーン遷移

			g_bPressTutorial = true;
		}
	}
}

//==============================================================================
// 描画処理
//==============================================================================
void CTutorial::Draw(void)
{
}

//==============================================================================
// 生成処理
//==============================================================================
CTutorial * CTutorial::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	// チュートリアル画面の生成
	CTutorial *pTutorial;
	pTutorial = new CTutorial;

	// NULLチェック
	if (pTutorial != NULL)
	{
		pTutorial->Init(pos, fSizeX, fSizeY);
	}

	return pTutorial;
}
