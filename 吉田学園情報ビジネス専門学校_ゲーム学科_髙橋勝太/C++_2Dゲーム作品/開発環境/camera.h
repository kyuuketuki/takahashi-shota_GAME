//=============================================================================
//
// カメラ処理 [camera.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _CAMERA_H_
#define _CAMERA_H_

//=============================================================================
//インクルード読み込み
//=============================================================================
#include "main.h"
#include "manager.h"

//=============================================================================
// カメラクラスの定義
//=============================================================================
class CCamera
{
public:
	CCamera();								//コンストラクタ
	virtual ~CCamera();						//デストラクタ

	HRESULT Init(void);						//初期化処理
	void Uninit(void);						//終了処理
	void Update(void);						//更新処理
	void Draw(void);						//描画処理

	void SetCamera(void);					//生成処理

private:
	D3DXMATRIX m_mtxProjection;	// プロジェクションマトリックス
	D3DXMATRIX m_mtxView;			// ビューマトリックス
	D3DXVECTOR3 m_posV;			// 現在の視点
	D3DXVECTOR3 m_posR;			// 現在の注視点
	D3DXVECTOR3 m_vecU;			// 上方向ベクトル
	D3DXVECTOR3 m_rot;			// カメラの角度
};

#endif