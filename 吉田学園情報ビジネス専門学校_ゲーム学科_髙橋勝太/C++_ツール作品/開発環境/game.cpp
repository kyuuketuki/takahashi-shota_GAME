//=============================================================================
//
// ゲーム画面処理 [game.cpp]
// Author : takahashi shota
//
//=============================================================================

//=============================================================================
//インクルード読み込み
//=============================================================================
#include "game.h"
#include "score.h"
#include "input.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "vertex.h"
#include "player3D.h"
#include "meshfield.h"
#include "scene3D.h"
#include "debugproc.h"
#include "object3D.h"
#include "textobject.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CDebugProc *CGame::m_pDebug = NULL;
CVertex *CGame::m_pVertex = NULL;					//アドレス保存　頂点当たり判定
CObject3D *CGame::m_pObject3D[MAX_OBJECT_3D] = {};	//アドレス保存　オブジェクト3D

//グローバル変数宣言
D3DXVECTOR3		g_posfile[256][4];					//テキストに書き出す情報　頂点当たり判定用　pos
D3DXVECTOR3		g_posfileObject3D[256];				//テキストに書き出す情報　オブジェクト3D用　pos
D3DXVECTOR3		g_rotfileObject3D[256];				//テキストに書き出す情報　オブジェクト3D用　rot
int				g_nTypefileObject3D[256];			//テキストに書き出す情報　オブジェクト3D用　type
int				nTimeGame = 0;						//時間
int				nTimeCounter = 0;					//時間カウンター
int				g_FileCnt = 0;						//頂点当たり判定生成カウント　TEXT用
int				g_FileCntObject3D = 0;				//オブジェクト3D生成カウント　TEXT用
int				g_nPointerGameY = 0;				//UI位置情報
int				g_nObject3DType = 0;				//オブジェクト3Dタイプ
int				g_VecCnt = 0;						//頂点当たり判定生成カウント
bool			g_bMigrate = false;					//画面遷移用
bool			g_bDeathFlagGame = false;			//死亡フラグ解除用
bool			g_bSwitchScene3D = false;			//可視化切り替えスイッチ
bool			g_bSwitchCollision = false;			//可視化切り替えスイッチ

//==============================================================================
// コンストラクタ
//==============================================================================
CGame::CGame()
{
	//初期化
	nTimeGame = 0;					//時間
	nTimeCounter = 0;				//時間カウンター
	g_bDeathFlagGame = false;		//死亡フラグ解除用
}

//==============================================================================
// デストラクタ
//==============================================================================
CGame::~CGame()
{

}

//==============================================================================
// 初期化処理
//==============================================================================
HRESULT CGame::Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//デバックの設定
	m_pDebug = new CDebugProc;
	m_pDebug->Init();

	// フォントオブジェクトの生成
	D3DXCreateFont(pDevice, 36, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pTimeFontGame);

	//メッシュフィールド
	CMeshfield::Create();

	//頂点当たり判定の生成
	m_pVertex = new CVertex;
	m_pVertex->LoadObject();
	
	//オブジェクトの生成
	CTextobject::Create();

	//3Dプレイヤーの生成
	CPlayer3D::Create();

	return S_OK;
}

//==============================================================================
// 終了処理
//==============================================================================
void CGame::Uninit(void)
{
	// オブジェクト破棄
	Release();
}

//==============================================================================
// 更新処理
//==============================================================================
void CGame::Update(void)
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

	//スイッチ処理
	Switch();
}

//==============================================================================
// 描画処理
//==============================================================================
void CGame::Draw(void)
{

}

//==============================================================================
// 切り替え処理　(ボタン)
//==============================================================================
void CGame::Switch(void)
{
	//キーボード取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//プレイヤーの情報を読み込む
	D3DXVECTOR3 posPlayer3D = CPlayer3D::GetPosition();
	D3DXVECTOR3 rotPlayer3D = CPlayer3D::GetRotation();

	//キーボードQを押した場合
	if (pInputKeyboard->GetTrigger(DIK_Q) == true)
	{
		//可視化スイッチ切り替え
		if (g_bSwitchScene3D == false)
		{
			g_bSwitchScene3D = true;
		}

		else if (g_bSwitchScene3D == true)
		{
			g_bSwitchScene3D = false;
		}
	}

	//キーボードEを押した場合
	if (pInputKeyboard->GetTrigger(DIK_E) == true)
	{
		//当たり判定スイッチ切り替え
		if (g_bSwitchCollision == false)
		{
			g_bSwitchCollision = true;
		}

		else if (g_bSwitchCollision == true)
		{
			g_bSwitchCollision = false;
		}
	}

	//キーボードLを押した場合
	//テクストに書き込む　消去
	if (pInputKeyboard->GetTrigger(DIK_L) == true)
	{
		if (g_FileCnt > 0)			//消去するオブジェクトがある場合
		{
			//カウント減らす
			g_FileCnt--;

			//消去
			CVertex::Release();
			m_pScene3D[g_FileCnt]->Uninit();

			FailObject();			//テキストを書き換える
		}
	}

	//キーボードPを押した場合
	//生成した頂点情報をリセット
	else if (pInputKeyboard->GetTrigger(DIK_P) == true)
	{
		g_VecCnt = 0;			//頂点設置リセット
	}

	//キーボードOを押した場合
	//テクストに書き込む　生成
	else if (pInputKeyboard->GetTrigger(DIK_O) == true)
	{
		//オブジェクトの位置を記憶
		g_posfile[g_FileCnt][g_VecCnt].x = posPlayer3D.x;
		g_posfile[g_FileCnt][g_VecCnt].y = posPlayer3D.y;
		g_posfile[g_FileCnt][g_VecCnt].z = posPlayer3D.z;
		g_VecCnt++;

		//四つの頂点が決まったら
		if (g_VecCnt >= 4)
		{
			m_pScene3D[g_FileCnt] = CScene3D::Create(D3DXVECTOR3(0, 0, 0), g_posfile[g_FileCnt][0], g_posfile[g_FileCnt][1], g_posfile[g_FileCnt][3], g_posfile[g_FileCnt][2]);
			CVertex::Create(D3DXVECTOR3(0, 0, 0), g_posfile[g_FileCnt][0], g_posfile[g_FileCnt][1], g_posfile[g_FileCnt][2], g_posfile[g_FileCnt][3]);

			g_FileCnt++;			//次の当たり判定へ
			FailObject();			//テキストを書き換える
			g_VecCnt = 0;			//頂点設置リセット
		}
	}

	//キーボードFを押した場合
	if (pInputKeyboard->GetTrigger(DIK_F) == true)
	{
		g_nObject3DType--;

		//最小より小さい場合になったら最大にする
		if (g_nObject3DType < 0)
		{
			//最大にする
			g_nObject3DType = CTextobject::GetMaxFileX() - 1;
		}
	}

	//キーボードRを押した場合
	//生成するときのオブジェクトタイプを変える
	else if (pInputKeyboard->GetTrigger(DIK_R) == true)
	{
		g_nObject3DType++;

		//最大より大きい場合になったら最小にする
		if (g_nObject3DType >= CTextobject::GetMaxFileX())
		{
			//最小
			g_nObject3DType = 0;
		}
	}

	//キーボードKを押した場合
	//テクストに書き込む　消去
	if (pInputKeyboard->GetTrigger(DIK_K) == true)
	{
		if (g_FileCntObject3D > 0)		//消去するオブジェクト3Dがある場合
		{
			g_FileCntObject3D--;		//最大数を減らす

										//オブジェクトの消去
			m_pObject3D[g_FileCntObject3D]->Uninit();

			FailObject3D();				//テキストを書き換える
		}
	}

	//キーボードIを押した場合
	//テクストに書き込む 生成
	else if (pInputKeyboard->GetTrigger(DIK_I) == true)
	{
		//オブジェクトの生成
		m_pObject3D[g_FileCntObject3D] = CObject3D::Create(posPlayer3D, D3DXVECTOR3(0.0f, rotPlayer3D.y, 0.0f), g_nObject3DType);

		//オブジェクトの位置を記憶(CAR)
		g_posfileObject3D[g_FileCntObject3D].x = posPlayer3D.x;
		g_posfileObject3D[g_FileCntObject3D].y = posPlayer3D.y;
		g_posfileObject3D[g_FileCntObject3D].z = posPlayer3D.z;

		g_rotfileObject3D[g_FileCntObject3D].y = rotPlayer3D.y;

		g_nTypefileObject3D[g_FileCntObject3D] = g_nObject3DType;

		g_FileCntObject3D++;	//最大数を増やす
		FailObject3D();			//テキストを書き換える	
	}
}

//==============================================================================
// Get関数 生成したオブジェクト3D　表示用
//==============================================================================
int CGame::GetObjectType3D(void)
{
	return g_nObject3DType;
}

//==============================================================================
// Get関数 生成した頂点数　表示用
//==============================================================================
int CGame::GetVecter(void)
{
	return g_VecCnt;
}

//==============================================================================
// Get関数タイム
//==============================================================================
int CGame::GetTime(void)
{
	return nTimeGame;
}

//==============================================================================
// Get関数 可視化切り替えスイッチ
//==============================================================================
bool CGame::GetSwitchScene3D(void)
{
	return g_bSwitchScene3D;
}

//==============================================================================
// Get関数 当たり判定切り替えスイッチ
//==============================================================================
bool CGame::GetSwitchCollision(void)
{
	return g_bSwitchCollision;
}

//==============================================================================
// Get関数 新に設置したオブジェクト3Dの数
//==============================================================================
int CGame::GetMaxObject3D(void)
{
	return g_FileCntObject3D;
}

//==============================================================================
// 生成処理
//==============================================================================
CGame * CGame::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	// ポインタ変数の生成
	CGame *pGame;
	pGame = new CGame;

	// NULLチェック
	if (pGame != NULL)
	{
		pGame->Init(pos, fSizeX, fSizeY);
	}

	return pGame;
}

//==============================================================================
//書き出し 頂点当たり判定用
//==============================================================================
void CGame::FailObject()
{
	FILE *fp;

	fp = fopen("data/TEXT/書き出しテキスト/vectorset.txt", "w");

	for (int nCnt = 0; nCnt < g_FileCnt; nCnt++)
	{
		//書き込む内容
		fprintf(fp, "VECTORSET\n");

		fprintf(fp, "	Vec1POSX = %.1f\n", g_posfile[nCnt][0].x);
		fprintf(fp, "	Vec1POSY = %.1f\n", g_posfile[nCnt][0].y);
		fprintf(fp, "	Vec1POSZ = %.1f\n", g_posfile[nCnt][0].z);

		fprintf(fp, "	Vec2POSX = %.1f\n", g_posfile[nCnt][1].x);
		fprintf(fp, "	Vec2POSY = %.1f\n", g_posfile[nCnt][1].y);
		fprintf(fp, "	Vec2POSZ = %.1f\n", g_posfile[nCnt][1].z);

		fprintf(fp, "	Vec3POSX = %.1f\n", g_posfile[nCnt][2].x);
		fprintf(fp, "	Vec3POSY = %.1f\n", g_posfile[nCnt][2].y);
		fprintf(fp, "	Vec3POSZ = %.1f\n", g_posfile[nCnt][2].z);

		fprintf(fp, "	Vec4POSX = %.1f\n", g_posfile[nCnt][3].x);
		fprintf(fp, "	Vec4POSY = %.1f\n", g_posfile[nCnt][3].y);
		fprintf(fp, "	Vec4POSZ = %.1f\n", g_posfile[nCnt][3].z);

		fprintf(fp, "END_VECTORSET\n\n");
	}

	//「txt」のファイルを閉じる
	fclose(fp);
}

//==============================================================================
//書き出し オブジェクト3D当たり判定用
//==============================================================================
void CGame::FailObject3D()
{
	FILE *fp;

	fp = fopen("data/TEXT/書き出しテキスト/object3Dset.txt", "w");

	for (int nCnt = 0; nCnt < g_FileCntObject3D; nCnt++)
	{
		//書き込む内容
		fprintf(fp, "OBJECTSET\n");

		fprintf(fp, "	POSX = %.1f\n", g_posfileObject3D[nCnt].x);
		fprintf(fp, "	POSY = %.1f\n", g_posfileObject3D[nCnt].y);
		fprintf(fp, "	POSZ = %.1f\n", g_posfileObject3D[nCnt].z);
		fprintf(fp, "	ROTX = %.1f\n", g_rotfileObject3D[nCnt].x);
		fprintf(fp, "	ROTY = %.1f\n", g_rotfileObject3D[nCnt].y);
		fprintf(fp, "	ROTZ = %.1f\n", g_rotfileObject3D[nCnt].z);
		fprintf(fp, "	TYPE = %d\n", g_nTypefileObject3D[nCnt]);

		fprintf(fp, "END_OBJECTSET\n\n");
	}

	//「txt」のファイルを閉じる
	fclose(fp);
}
