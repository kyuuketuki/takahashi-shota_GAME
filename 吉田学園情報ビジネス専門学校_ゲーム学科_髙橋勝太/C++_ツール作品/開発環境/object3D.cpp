//=============================================================================
//
// オブジェクト3Dの処理 [object3D.cpp]
// Author : takahashi shota
//
//=============================================================================

//=============================================================================
//インクルード読み込み
//=============================================================================
#include "object3D.h"
#include "manager.h"
#include "scene3D.h"
#include "textobject.h"

//静的メンバ変数宣言
D3DXVECTOR3		CObject3D::m_rotStatic = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//回転量
D3DXMATRIX      CObject3D::m_mtxWorld;										//受け渡す用ワールドマトリックス
CScene3D		*CObject3D::m_pScene3D[256] = {};							//受け渡し用アドレス
int				CObject3D::m_nType;											//XファイルTypeで切り替え

//受け渡し表示用
int g_nCntObject3D;									//生成番号の表示用
int g_FailCntObject3D;								//生成カウント
int g_nCntVecObject3D;								//ベクトル番号の表示用
float g_fAtan2Object3D;								//角度表示の表示用

//=============================================================================
// コンストラクタ
//=============================================================================
CObject3D::CObject3D(int nPriority, int nType)
{
	//生成番号
	m_nCntNumber = g_FailCntObject3D;
	g_FailCntObject3D++;
}

//=============================================================================
// デストラクタ
//=============================================================================
CObject3D::~CObject3D()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CObject3D::Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//Xファイルの読み込み
	D3DXLoadMeshFromX(CTextobject::GetTextName(m_nType), D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_pBuffMat, NULL, &m_nNumMat, &m_pMesh);

	//位置
	m_pos = pos;
	
	//向き
	m_rot = m_rotStatic;
	
	int nNumVtx;			//頂点数
	BYTE *pVtxBuff;			//頂点バッファへのポインタ
	DWORD sizeFVF;			//頂点フォーマットのサイズ

	//頂点数を記憶
	nNumVtx = m_pMesh->GetNumVertices();

	//頂点フォーマットのサイズを取得
	sizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//頂点バッファのロック
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		m_vtx = *(D3DXVECTOR3*)pVtxBuff;			//頂点座標の代入

		if (m_vtx.x > m_MaxSize.x)
		{
			m_MaxSize.x = m_vtx.x;
		}

		if (m_vtx.x < m_MinSize.x)
		{
			m_MinSize.x = m_vtx.x;
		}

		if (m_vtx.y > m_MaxSize.y)
		{
			m_MaxSize.y = m_vtx.y;
		}

		if (m_vtx.y < m_MinSize.y)
		{
			m_MinSize.y = m_vtx.y;
		}

		if (m_vtx.z > m_MaxSize.z)
		{
			m_MaxSize.z = m_vtx.z;
		}

		if (m_vtx.z < m_MinSize.z)
		{
			m_MinSize.z = m_vtx.z;
		}

		pVtxBuff += sizeFVF;			//頂点フォーマットのサイズ分ポインタを進める
	}
	
	m_pMesh->UnlockVertexBuffer();

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CObject3D::Uninit(void)
{
	//生成番号を減らす
	g_FailCntObject3D--;

	//NULLチェック
	if (m_pScene3D[m_nCntNumber] != NULL)
	{
		//可視化を終了される
		m_pScene3D[m_nCntNumber]->Uninit();
	}

	//オブジェクトの破棄
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CObject3D::Update(void)
{
	
}

//=============================================================================
// 描画処理
//=============================================================================
void CObject3D::Draw(void)
{
	//ローカル
	D3DXMATRIX mtxRot, mtxTrans, revmat;	//計算用マトリックス
	D3DMATERIAL9 matDef;					//現在のマテリアル保存
	D3DXMATERIAL *pMat;						//マテリアルへのポインタ

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きの反転
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置の反転
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	if (m_MaxSize.x < 0.0f)
	{
		m_MaxSize.x *= -1.0f;
	}
	if (m_MaxSize.y < 0.0f)
	{
		m_MaxSize.y *= -1.0f;
	}
	if (m_MaxSize.z < 0.0f)
	{
		m_MaxSize.z *= -1.0f;
	}

	if (m_MinSize.x < 0.0f)
	{
		m_MinSize.x *= -1.0f;
	}
	if (m_MinSize.y < 0.0f)
	{
		m_MinSize.y *= -1.0f;
	}
	if (m_MinSize.z < 0.0f)
	{
		m_MinSize.z *= -1.0f;
	}

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//現在のマテリアルの取得
	pDevice->GetMaterial(&matDef);

	//マテリアルデータへのポインタ取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		//マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//テクスチャの設定
		pDevice->SetTexture(0, NULL);

		//モデルパーツの描画
		m_pMesh->DrawSubset(nCntMat);
	}

	//保存したマテリアルを戻す
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// 生成処理
//=============================================================================
CObject3D * CObject3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)
{
	//モデルを生成
	CObject3D *pObject3D = NULL;
	pObject3D = new CObject3D;

	//NULLチェック
	if (pObject3D != NULL)
	{
		m_nType = nType;
		m_rotStatic = rot;
		pObject3D->Init(pos, 0.0f, 0.0f);
	}

	return pObject3D;
}

//==============================================================================
// 外積を利用した当たり判定
//==============================================================================
bool CObject3D::CollisionVec(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidthMax, float fWidthMin, float fDepthMax, float fDepthMin, float fHeightMax, float fHeightMin)
{
	// ローカル変数
	CCamera *pCamera = CManager::GetCamera();	// カメラ情報の取得
	D3DXVECTOR3 rot = pCamera->GetRot();		// カメラ角度
	D3DXVECTOR3 CameraPos = pCamera->GetposV();	// カメラの位置
	bool bLand = false;

	D3DXVECTOR3		g_Vec[4];			// ベクトル
	D3DXVECTOR3		g_oldVec[4];		// 前のベクトル
	D3DXVECTOR3		posold;				// 前の位置
	float			PlayerVec[4];		// プレイヤーベクトル
	float			oldPlayerVec[4];	// 前のプレイヤーベクトル

	D3DXVECTOR3 pos = *pPos;			// 判定対象の位置
	posold = *pPosOld;					// 判定対象の位置

	//壁ずりベクトル計算用
	D3DXVECTOR3 VecP = *pPos - *pPosOld;						// 進行ベクトル
	fabsf(VecP.x);												// 絶対値
	fabsf(VecP.z);												// 絶対値
	D3DXVec3Normalize(&VecP, &VecP);

	//aPosの値設定
	m_aPos[0] = D3DXVECTOR3(m_pos.x - m_MinSize.x, 0.0f, m_pos.z - m_MinSize.z);
	m_aPos[1] = D3DXVECTOR3(m_pos.x - m_MinSize.x, 0.0f, m_pos.z + m_MaxSize.z);
	m_aPos[2] = D3DXVECTOR3(m_pos.x + m_MaxSize.x, 0.0f, m_pos.z + m_MaxSize.z);
	m_aPos[3] = D3DXVECTOR3(m_pos.x + m_MaxSize.x, 0.0f, m_pos.z - m_MinSize.z);

	// 対角線の設定
	float fLength[4];
	fLength[0] = sqrtf(m_MinSize.x * m_MinSize.x + m_MinSize.z * m_MinSize.z);
	fLength[1] = sqrtf(m_MinSize.x * m_MinSize.x + m_MaxSize.z * m_MaxSize.z);
	fLength[2] = sqrtf(m_MaxSize.x * m_MaxSize.x + m_MaxSize.z * m_MaxSize.z);
	fLength[3] = sqrtf(m_MaxSize.x * m_MaxSize.x + m_MinSize.z * m_MinSize.z);

	float fAngle[4];
	fAngle[0] = atan2f(m_MinSize.x, m_MinSize.z);
	fAngle[1] = atan2f(m_MinSize.x, m_MaxSize.z);
	fAngle[2] = atan2f(m_MaxSize.x, m_MaxSize.z);
	fAngle[3] = atan2f(m_MaxSize.x, m_MinSize.z);

	//頂点の座標
	m_aPos[0].x = (m_pos.x + sinf(fAngle[1] + m_rot.y) * fLength[2]);
	m_aPos[0].z = (m_pos.z + cosf(fAngle[1] + m_rot.y) * fLength[2]);

	m_aPos[1].x = (m_pos.x + sinf(fAngle[2] - m_rot.y) * fLength[3]);
	m_aPos[1].z = (m_pos.z - cosf(fAngle[2] - m_rot.y) * fLength[3]);

	m_aPos[2].x = (m_pos.x - sinf(fAngle[3] + m_rot.y) * fLength[0]);
	m_aPos[2].z = (m_pos.z - cosf(fAngle[3] + m_rot.y) * fLength[0]);

	m_aPos[3].x = (m_pos.x - sinf(fAngle[0] - m_rot.y) * fLength[1]);
	m_aPos[3].z = (m_pos.z + cosf(fAngle[0] - m_rot.y) * fLength[1]);

	//並び方をただす
	//90ずれている場合
	if (m_aPos[0].x > m_aPos[2].x && m_aPos[0].z < m_aPos[2].z)
	{
		D3DXVECTOR3 vecold;
		vecold = m_aPos[0];

		m_aPos[0] = m_aPos[3];
		m_aPos[3] = m_aPos[2];
		m_aPos[2] = m_aPos[1];
		m_aPos[1] = vecold;
	}
	//180ずれている場合
	else if (m_aPos[0].x < m_aPos[2].x && m_aPos[0].z < m_aPos[2].z)
	{
		D3DXVECTOR3 vecold;
		vecold = m_aPos[0];

		D3DXVECTOR3 vecold2;
		vecold2 = m_aPos[1];

		m_aPos[0] = m_aPos[2];
		m_aPos[2] = vecold;
		m_aPos[1] = m_aPos[3];
		m_aPos[3] = vecold2;
	}
	//270ずれている場合
	else if (m_aPos[0].x < m_aPos[2].x && m_aPos[0].z > m_aPos[2].z)
	{
		D3DXVECTOR3 vecold;
		vecold = m_aPos[0];

		m_aPos[0] = m_aPos[1];
		m_aPos[1] = m_aPos[2];
		m_aPos[2] = m_aPos[3];
		m_aPos[3] = vecold;
	}

	//外積の式
	m_Vec[0] = m_aPos[1] - m_aPos[0];	// 右
	m_Vec[1] = m_aPos[2] - m_aPos[1];	// 下								 
	m_Vec[2] = m_aPos[3] - m_aPos[2];	// 左
	m_Vec[3] = m_aPos[0] - m_aPos[3];	// 上

	for (int nCount = 0; nCount < 4; nCount++)
	{
		// プレイヤーベクトル保存
		if (nCount == 0)
		{
			g_oldVec[nCount] = posold + D3DXVECTOR3(fWidthMin, 0.0f, 0.0f) - m_aPos[nCount];
		}
		else if (nCount == 1)
		{
			g_oldVec[nCount] = posold + D3DXVECTOR3(0.0f, 0.0f, fDepthMax) - m_aPos[nCount];
		}
		else if (nCount == 2)
		{
			g_oldVec[nCount] = posold + D3DXVECTOR3(fWidthMax, 0.0f, 0.0f) - m_aPos[nCount];
		}
		else if (nCount == 3)
		{
			g_oldVec[nCount] = posold + D3DXVECTOR3(0.0f, 0.0f, fDepthMin) - m_aPos[nCount];
		}


		// プレイヤーがm_Vecより右にいるかどうかの判定用
		oldPlayerVec[nCount] = (m_Vec[nCount].z * g_oldVec[nCount].x) - (m_Vec[nCount].x * g_oldVec[nCount].z);
	}
	for (int nCount = 0; nCount < 4; nCount++)
	{
		//外積の式2		
		if (nCount == 0)
		{
			// 右上からプレイヤーのベクトル
			g_Vec[nCount] = pos + D3DXVECTOR3(fWidthMin, 0.0f, 0.0f) - m_aPos[nCount];
		}
		else if (nCount == 1)
		{
			// 右下プレイヤーのベクトル
			g_Vec[nCount] = pos + D3DXVECTOR3(0.0f, 0.0f, fDepthMax) - m_aPos[nCount];
		}
		else if (nCount == 2)
		{
			// 左下プレイヤーのベクトル
			g_Vec[nCount] = pos + D3DXVECTOR3(fWidthMax, 0.0f, 0.0f) - m_aPos[nCount];
		}
		else if (nCount == 3)
		{
			// 左上プレイヤーのベクトル
			g_Vec[nCount] = pos + D3DXVECTOR3(0.0f, 0.0f, fDepthMin) - m_aPos[nCount];
		}

		// プレイヤーがm_Vecより右にいるかどうかの判定用
		PlayerVec[nCount] = (m_Vec[nCount].z * g_Vec[nCount].x) - (m_Vec[nCount].x * g_Vec[nCount].z);
	}

	//上下の当たり判定(Y)
	if (pPos->y <= m_pos.y + m_MaxSize.y - fHeightMin && pPos->y > m_pos.y - m_MinSize.y - fHeightMax)
	{
		if (PlayerVec[0] > 0.0f && PlayerVec[1] > 0.0f && PlayerVec[2] > 0.0f && PlayerVec[3] > 0.0f)
		{
			// 上下の判定　（間にいるかどうか）
			if (PlayerVec[3] > 0.0f || PlayerVec[1] > 0.0f)
			{
				// 前のベクトルが0より下の時
				if (oldPlayerVec[0] < 0.0f)
				{
					// 右の当たり判定			
					if (PlayerVec[0] > 0.0f)
					{
						g_nCntVecObject3D = 0;

						//2頂点差を計算
						D3DXVECTOR3 a = m_aPos[0] - m_aPos[1];

						//角度を計算
						float fA = atan2f(a.z, a.x);

						//壁ずりベクトル計算用
						D3DXVECTOR3 norVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 法線ベクトル
						D3DXVec3Cross(&norVec, &a, &m_rot);
						D3DXVec3Normalize(&norVec, &norVec);
						fabsf(norVec.x);											// 絶対値
						fabsf(norVec.z);											// 絶対値

						D3DXVECTOR3 Wvec;											// 壁ずりベクトル
						Wvec = VecP - (D3DXVec3Dot(&VecP, &norVec) * norVec);

						if (m_rot.y == 0.0f)
						{
							pPos->x = pPosOld->x;				// 1フレーム前の位置に戻す
						}
						else
						{
							pPos->x = pPosOld->x;				// 1フレーム前の位置に戻す
							pPos->z = pPosOld->z;
							pMove->x = (Wvec.x) * 5;
							pMove->z = (Wvec.z) * 5;
						}

						g_fAtan2Object3D = fA;
						bLand = true;

					}
				}

				// 左の当たり判定
				if (oldPlayerVec[2] < 0.0f)
				{
					if (PlayerVec[2] > 0.0f)
					{
						// 左
						g_nCntVecObject3D = 2;

						//2頂点差を計算
						D3DXVECTOR3 a = m_aPos[2] - m_aPos[3];

						//角度を計算
						float fAtan2 = atan2f(a.z, a.x);

						//壁ずりベクトル計算用
						D3DXVECTOR3 norVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 法線ベクトル
						D3DXVec3Cross(&norVec, &a, &m_rot);
						
						D3DXVec3Normalize(&norVec, &norVec);
						fabsf(norVec.x);											// 絶対値
						fabsf(norVec.z);											// 絶対値
																					//norVec.y = 0;
						D3DXVECTOR3 Wvec;											// 壁ずりベクトル
						Wvec = VecP - (D3DXVec3Dot(&VecP, &norVec) * norVec);

						if (m_rot.y == 0.0f)
						{
							pPos->x = pPosOld->x;				// 1フレーム前の位置に戻す
							pMove->x = 0.0f;
						}
						else
						{
							pPos->x = pPosOld->x;				// 1フレーム前の位置に戻す
							pPos->z = pPosOld->z;
							pMove->x = (Wvec.x) * 5;
							pMove->z = (Wvec.z) * 5;
						}

						bLand = true;
						g_fAtan2Object3D = fAtan2;
					}
				}

				// 左右に触れていないとき
				if (PlayerVec[0] > 0.0f || PlayerVec[2] > 0.0f)
				{
					if (oldPlayerVec[3] < 0.0f)
					{
						// 上の当たり判定			
						if (PlayerVec[3] > 0.0f)
						{
							g_nCntVecObject3D = 3;

							//2頂点差を計算
							D3DXVECTOR3 a = m_aPos[3] - m_aPos[0];

							//角度を計算
							float fAtan2 = (float)atan2(a.z, a.x);

							//壁ずりベクトル計算用
							D3DXVECTOR3 norVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 法線ベクトル
							
							D3DXVec3Cross(&norVec, &a, &D3DXVECTOR3(0.0f, 0.1f, 0.0f));
							D3DXVec3Normalize(&norVec, &norVec);
							//fabsf(norVec.x);											// 絶対値
							//fabsf(norVec.z);											// 絶対値
							//norVec.y = 0;
							D3DXVECTOR3 Wvec;											// 壁ずりベクトル
							Wvec = VecP - (D3DXVec3Dot(&VecP, &norVec) * norVec);

							if (m_rot.y == 0.0f)
							{
								pPos->z = pPosOld->z;				// 1フレーム前の位置に戻す
								pMove->z = 0.0f;
							}
							else
							{

								pPos->x = pPosOld->x;				// 1フレーム前の位置に戻す
								pPos->z = pPosOld->z;
								pMove->x = (Wvec.x) * 5;
								pMove->z = (Wvec.z) * 5;
							}

							g_fAtan2Object3D = fAtan2;
							bLand = true;
						}
					}
					if (oldPlayerVec[1] < 0.0f)
					{
						// 下の当たり判定			
						if (PlayerVec[1] > 0.0f)
						{
							// 下
							g_nCntVecObject3D = 1;

							//2頂点差を計算
							D3DXVECTOR3 a = m_aPos[2] - m_aPos[1];

							//角度を計算
							float fAtan2 = (float)atan2(a.z, a.x);

							//壁ずりベクトル計算用
							D3DXVECTOR3 norVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 法線ベクトル
							D3DXVec3Cross(&norVec, &a, &m_rot);							// 2つの3Dベクトルの積間を決定
							D3DXVec3Normalize(&norVec, &norVec);						// 3Dベクターの正規化
							fabsf(norVec.x);											// 絶対値
							fabsf(norVec.z);											// 絶対値

							D3DXVECTOR3 Wvec;											// 壁ずりベクトル
							Wvec = VecP - (D3DXVec3Dot(&VecP, &norVec) * norVec);		// 壁ずりベクトル計算

							if (m_rot.y == 0.0f)
							{
								pPos->z = pPosOld->z;				// 1フレーム前の位置に戻す
								pMove->z = 0.0f;
							}
							else
							{
								pPos->x = pPosOld->x;				// 1フレーム前の位置に戻す
								pPos->z = pPosOld->z;
								pMove->x = (Wvec.x) * 5;
								pMove->z = (Wvec.z) * 5;
							}
							bLand = true;
							g_fAtan2Object3D = fAtan2;
						}
					}
				}
				g_nCntObject3D = m_nCntNumber;
			}
		}
	}

	//可視化　計算後
	if (m_bUse == false)
	{
		if (m_nCnt == 2)		//位置フレーム後に可視化
		{
			//可視化
			m_pScene3D[m_nCntNumber] = CScene3D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_aPos[0], m_aPos[1], m_aPos[3], m_aPos[2]);
			m_bUse = true;
		}

		m_nCnt++;
	}

	return bLand;
}

//=============================================================================
// ワールドマトリックス情報をわたす
//=============================================================================
D3DXMATRIX CObject3D::GetMtxWorld(void)
{
	return m_mtxWorld;
}

//=============================================================================
//  当たっている生成番号を表示用
//=============================================================================
int CObject3D::GetNumberObject3D(void)
{
	return g_nCntObject3D;
}

//=============================================================================
// 当たっているベクトルの向きを表示用
//=============================================================================
int CObject3D::GetNumber2Object3D(void)
{
	return g_nCntVecObject3D;
}

//=============================================================================
// 当たっているベクトルの角度を表示用
//=============================================================================
float CObject3D::GetAtan2Object3D(void)
{
	return g_fAtan2Object3D;
}
