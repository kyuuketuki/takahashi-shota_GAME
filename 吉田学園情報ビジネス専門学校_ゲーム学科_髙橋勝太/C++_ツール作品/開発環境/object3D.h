//=============================================================================
//
// オブジェクト3D処理 [object3D.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _OBJECT3D_H_
#define _OBJECT3D_H_

//=============================================================================
//インクルード読み込み
//=============================================================================
#include "scene.h"

//前方宣言
class CScene3D;

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_OBJECT_3D	(256)		// 最大数

//=============================================================================
// オブジェクト3Dクラスの定義
//=============================================================================
class CObject3D : public CScene
{
public:
	CObject3D(int nPriority = 0, int nType = 0);								//コンストラクタ
	virtual ~CObject3D();														//デストラクタ

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY);					//初期化処理
	void Uninit(void);															//終了処理
	void Update(void);															//更新処理
	void Draw(void);															//描画処理

	static CObject3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);		//生成処理

	//当たり判定
	bool CollisionVec(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidthMax, float fWidthMin, float fDepthMax, float fDepthMin, float fHeightMax, float fHeightMin);
	
	//ワールドマトリックス受け渡し
	D3DXMATRIX GetMtxWorld(void);

	//アドレスの受け渡し
	static CScene3D *GetScene3D(int nCnt) { return m_pScene3D[nCnt]; }

	//受け渡し用
	static int		GetNumberObject3D(void);
	static int		GetNumber2Object3D(void);
	static float	GetAtan2Object3D(void);

private:
	LPD3DXMESH		m_pMesh;				//メッシュ
	LPD3DXBUFFER	m_pBuffMat;				//バッファ
	DWORD			m_nNumMat;				//マトリックス
	D3DXVECTOR3		m_pos;					//位置
	D3DXVECTOR3		m_posold;				//位置フレーム前の位置
	D3DXVECTOR3		m_CollisionVecPos[4];	//当てり判定用ベクトル
	D3DXVECTOR3		m_move;					//位置
	D3DXVECTOR3		m_rot;					//位置
	D3DXVECTOR3     m_vtx;					//頂点座標の代入
	D3DXVECTOR3		m_MaxSize;				//最大値を記憶
	D3DXVECTOR3		m_MinSize;				//最小値を記憶
	D3DXVECTOR3		m_aPos[4];				//位置情報の計算用
	D3DXVECTOR3		m_Vec[4];				//ベクトルの計算用
	int				m_nNumVtx;				//頂点数
	int				m_nCntNumber;			//生成カウント
	int				m_nCnt;					//計算後に可視化する用
	float			m_fLength;				//対角線の長さ
	float			m_fAngle;				//対角線の角度
	float			m_fLength2;				//対角線の長さ
	bool			m_bUse;					//可視化計算後に表示させるよう

	//静的変数
	static D3DXMATRIX		m_mtxWorld;						//ワールドマトリックス
	static D3DXVECTOR3		m_rotStatic;					//静的メンバ変数　向き
	static D3DXVECTOR3		m_moveStatic;					//静的メンバ変数　移動量
	static int				m_nType;						//静的メンバ変数　タイプ
	static CScene3D			*m_pScene3D[256];				//アドレス保存用ポインタ
	static char				*m_pTextName;					//テクスチャ読み込み
};

#endif