//=============================================================================
//
// ポーズ処理 [pause.cpp]
// Author : takahashi shota
//
//=============================================================================

//=============================================================================
//インクルード読み込み
//=============================================================================
#include "pause.h"
#include "logo.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "animation.h"
#include "fade.h"

//グローバル変数宣言
int nTimeGamePause = 0;			//時間
int nTimeCounterPause = 0;		//時間カウンター
int g_nPointerPauseX = 0;		//ポインター位置
bool g_bButtonDownPause = false;	//連打防止

//=============================================================================
// コンストラクタ
//=============================================================================
CPause::CPause(int nPriority, int nType) : CScene(nPriority, nType)
{
	//初期化
	g_nPointerPauseX = 0;
	g_bButtonDownPause = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CPause::~CPause()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CPause::Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//背景を生成
	CLogoPause::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, PAUSE01);

	//フレームを生成
	CLogoPause::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 0.0f, 0.0f), 210, 60, FRAME);

	//ロゴ(選択用)を生成
	CLogoPause::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 0.0f, 0.0f), 200, 50, GAMEOVER_RESTART);
	CLogoPause::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), 200, 50, GAMEOVER_START);
	CLogoPause::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 400.0f, 0.0f), 200, 50, GAMEOVER_END);//背景を表示

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CPause::Uninit(void)
{
	// オブジェクト破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CPause::Update(void)
{
	//キーボード取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//ゲームパッドのポインタ宣言
	CGamepad *pGamepad;
	pGamepad = CManager::GetGamepad();

	//サウンドを取得
	CSound *pSound;
	pSound = CManager::GetSound();

	//画面遷移が始まってない場合
	if (g_bButtonDownPause == false)
	{
		//S＆↓を押した場合
		if (pInputKeyboard->GetTrigger(DIK_S) == true || pGamepad->IsButtonDown(CInput::DOWN))
		{
			if (g_nPointerPauseX == 0)
			{
				g_nPointerPauseX = 1;
				CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), FRAME);
			}

			else if (g_nPointerPauseX == 1)
			{
				g_nPointerPauseX = 2;
				CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 400.0f, 0.0f), FRAME);
			}

			else if (g_nPointerPauseX == 2)
			{
				g_nPointerPauseX = 0;
				CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), FRAME);
			}

			//サウンドSE
			pSound->Play(CSound::SOUND_LABEL_SE_MIGRATION);
		}

		//W＆↑を押した場合
		if (pInputKeyboard->GetTrigger(DIK_W) == true || pGamepad->IsButtonDown(CInput::UP))
		{
			if (g_nPointerPauseX == 0)
			{
				g_nPointerPauseX = 2;
				CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 400.0f, 0.0f), FRAME);
			}

			else if (g_nPointerPauseX == 1)
			{
				g_nPointerPauseX = 0;
				CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 0.0f, 0.0f), FRAME);
			}

			else if (g_nPointerPauseX == 2)
			{
				g_nPointerPauseX = 1;
				CLogo::TypeMove(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 200.0f, 0.0f), FRAME);
			}

			//サウンドSE
			pSound->Play(CSound::SOUND_LABEL_SE_MIGRATION);
		}

		//画面遷移
		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pGamepad->IsButtonDown(CInput::A) || pGamepad->IsButtonDown(CInput::B) == true)
		{
			if (g_nPointerPauseX == 0)
			{
				//Stage1でゲームオーバーになった場合
				if (CManager::GetGameStage() == 1)
				{
					//Stage1に遷移する
					CFade::SetFade(CFade::FADE_OUT, CManager::MODE_GAME, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));	// シーン遷移
				}

				//Stage1でゲームオーバーになった場合
				if (CManager::GetGameStage() == 2)
				{
					//Stage2に遷移する
					CFade::SetFade(CFade::FADE_OUT, CManager::MODE_GAME2, D3DXCOLOR(1.0f, 0.0f, 1.0f, 0.0f));	// シーン遷移
				}
			}

			if (g_nPointerPauseX == 1)
			{
				//モード設定
				CFade::SetFade(CFade::FADE_OUT, CManager::MODE_SELECT, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	// シーン遷移
			}

			if (g_nPointerPauseX == 2)
			{
				//モード設定
				CFade::SetFade(CFade::FADE_OUT, CManager::MODE_TITLE, D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	// シーン遷移
			}

			//画面遷移が始まった
			g_bButtonDownPause = true;

			//サウンドSE
			pSound->Play(CSound::SOUND_LABEL_SE_DECISION);
		}
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void CPause::Draw(void)
{

}

//=============================================================================
// 生成処理
//=============================================================================
CPause * CPause::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	// ポインタ変数の生成
	CPause *pPause;
	pPause = new CPause;

	// NULLチェック
	if (pPause != NULL)
	{
		//ポーズ画面の生成
		pPause->Init(pos, fSizeX, fSizeY);
	}

	return pPause;
}
