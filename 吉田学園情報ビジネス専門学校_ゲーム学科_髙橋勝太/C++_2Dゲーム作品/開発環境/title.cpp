 //=============================================================================
//
// タイトル画面処理 [title.cpp]
// Author : takahashi shota
//
//=============================================================================

//=============================================================================
//インクルード読み込み
//=============================================================================
#include "title.h"
#include "bg.h"
#include "input.h"
#include "manager.h"
#include "scene2D.h"
#include "logo.h"
#include "animation.h"
#include "polygon.h"
#include "gamepad.h"
#include "fade.h"
#include "object3D.h"
#include "scene3D.h"

//グローバル変数宣言
int nTimeTitle = 0;					//時間
int nTimeCounterTitle = 0;			//時間カウンター
int nNexEnterCount = 0;				//ロゴEnterの色変化に使用
int nSaveTime = -1;					//アニメーション用時間管理用
int nSaveTime2 = -1;				//アニメーション用時間管理用
int nFlashing = 30;					//PressEnterの点滅させる速度　途中で速度変更
bool g_bPressEnter = false;			//ロゴの表示条件
bool g_bNextEnter = false;			//ロゴEnterの色変化に使用
bool g_bButtonDownTitle = false;	//連打防止用

//==============================================================================
// コンストラクタ
//==============================================================================
CTitle::CTitle()
{
	//初期化
	nTimeTitle = 0;					//時間
	nTimeCounterTitle = 0;			//時間カウンター
	nNexEnterCount = 0;				//ロゴEnterの色変化に使用
	nSaveTime = -1;					//アニメーション用時間管理用
	nSaveTime2 = -1;				//アニメーション用時間管理用
	nFlashing = 30;					//PressEnterの点滅させる速度　途中で速度変更
	g_bPressEnter = false;			//ロゴの表示条件
	g_bNextEnter = false;			//ロゴEnterの色変化に使用
	g_bButtonDownTitle = false;		//連打防止用
}

//==============================================================================
// デストラクタ
//==============================================================================
CTitle::~CTitle()
{

}

//==============================================================================
// 初期化処理
//==============================================================================
HRESULT CTitle::Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	//背景を表示
	CBg::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	//アニメーションを表示	
	CAnimasion::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 10, 4);		//フレーム

	//オブジェクトの生成(惑星)
	CObject3D::Create(D3DXVECTOR3(30, 30.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);

	return S_OK;
}

//==============================================================================
// 終了処理
//==============================================================================
void CTitle::Uninit(void)
{
	// オブジェクト破棄
	Release();
}

//==============================================================================
// 更新処理
//==============================================================================
void CTitle::Update(void)
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

	//タイトルロゴが表示された状態
	if (nTimeTitle >= 2 && nTimeCounterTitle >= 0)
	{
		//Enterロゴの表示
		if (g_bPressEnter == false)
		{
			CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 400.0f, 0.0f), 150, 50, TITLE_UI_PRESS_ENTER);		//Enterロゴ
			g_bPressEnter = true;
		}

		//点滅処理　NextEnter
		if (g_bPressEnter == true)
		{
			//カウントアップ
			nNexEnterCount++;
			if (nNexEnterCount == nFlashing)
			{
				//透明にする
				if (g_bNextEnter == true)
				{
					CLogo::TypeChangeCollar(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f), TITLE_UI_PRESS_ENTER);		//色変化
					g_bNextEnter = false;
				}
				//不透明にする
				else if (g_bNextEnter == false)
				{
					CLogo::TypeChangeCollar(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), TITLE_UI_PRESS_ENTER);		//色変化
					g_bNextEnter = true;
				}

				//リセット
				nNexEnterCount = 0;
			}
		}

		//初めて押した場合のみ
		if (g_bButtonDownTitle == false)
		{
			//画面遷移
			if (pGamepad->IsButtonDown(CInput::A) == true || pGamepad->IsButtonDown(CInput::B) == true || pInputKeyboard->GetTrigger(DIK_RETURN) == true)
			{
				//アニメーション
				CAnimasion::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 5, 10);		//画面遷移アニメーション

				//サウンドSE
				pSound->Play(CSound::SOUND_LABEL_SE_METEOR);

				//画面遷移に関する変数
				nTimeCounterTitle = 0;

				//点滅に関する変数
				nFlashing = 5;
				nNexEnterCount = 0;

				//ボタンを押したタイムを保存
				nSaveTime = nTimeTitle;
				nSaveTime2 = 30;

				//連打防止
				g_bButtonDownTitle = true;
			}
		}

		//遷移条件アニメーションが終了後
		if ((nSaveTime + 1) == nTimeTitle && nSaveTime2 == nTimeCounterTitle)
		{
			//モード設定
			CFade::SetFade(CFade::FADE_OUT, CManager::MODE_MENU, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));	// シーン遷移
		}
	}

	//タイムを進める
	nTimeCounterTitle++;

	//カウンターが60以上になったら
	if (nTimeCounterTitle >= 60)
	{
		//秒数を進める
		nTimeTitle++;

		//カウンターを戻す
		nTimeCounterTitle = 0;
	}

	//タイムに合わせて生成
	if (nTimeTitle == 1 && nTimeCounterTitle == 10)
	{
		CAnimasion::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 5, 1);		//星を降らせるアニメーション

		//サウンドSE
		pSound->Play(CSound::SOUND_LABEL_SE_STER);
	}

	//タイムに合わせて生成
	if (nTimeTitle == 1 && nTimeCounterTitle == 20)
	{
		CLogo::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f), 500, 200, TITLE_UI);		//タイトル
	}
}

//==============================================================================
// 描画処理
//==============================================================================
void CTitle::Draw(void)
{

}

//==============================================================================
// 生成処理
//==============================================================================
CTitle * CTitle::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	// ポインタ変数の生成
	CTitle *pTitle;
	pTitle = new CTitle;

	// NULLチェック
	if (pTitle != NULL)
	{
		//タイトル画面の生成
		pTitle->Init(pos, fSizeX, fSizeY);
	}

	return pTitle;
}
