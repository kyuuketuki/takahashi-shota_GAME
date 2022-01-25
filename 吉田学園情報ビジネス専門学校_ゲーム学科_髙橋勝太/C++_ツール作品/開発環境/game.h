//=============================================================================
//
// ゲーム画面処理 [game.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _GAME_H_
#define _GAME_H_

//=============================================================================
//インクルード読み込み
//=============================================================================
#include "main.h"
#include "scene.h"
#include "scene2D.h"
#include "debugproc.h"
#include "object3D.h"

//前方宣言
class CVertex;
class CObject3D;
class CScene3D;

//=============================================================================
// ゲーム画面クラスの定義
//=============================================================================
class CGame : public CScene
{
public:
	CGame();									//コンストラクタ
	~CGame();									//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY);	//初期化処理
	void Uninit(void);											//終了処理
	void Update(void);											//更新処理
	void Draw(void);											//描画処理

	void Switch(void);											//切り替え処理

	//アドレス保存
	static CVertex		*GetVertex(void) { return m_pVertex; }
	static CObject3D	*GetObject(int nCnt) { return m_pObject3D[nCnt]; }

	//生成したいXファイルをしらせる
	static int GetObjectType3D(void);

	//生成したい頂点数をしらせる
	static int GetVecter(void);
				
	//時間Get
	static int GetTime(void);

	//オンオフの切り替え
	static bool GetSwitchScene3D(void);
	static bool GetSwitchCollision(void);

	//新たに生成したオブジェクト3Dの数を記憶
	static int GetMaxObject3D(void);

	//生成処理
	static CGame *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY);

	//テキストを読み込む
	void FailObject();
	void FailObject3D();

private:
	LPD3DXFONT	m_pTimeFontGame;						//表示用フォント
	CScene3D	*m_pScene3D[256];						//可視化生成したアドレスを記憶

	//静的メンバ変数
	static CDebugProc	*m_pDebug;						//デバック表示のメンバ変数
	static CVertex		*m_pVertex;						//アドレス保存用ポインタ
	static CObject3D	*m_pObject3D[MAX_OBJECT_3D];	//アドレス保存用ポインタ
};

#endif