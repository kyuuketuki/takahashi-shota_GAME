//=============================================================================
//
// プレイヤー3D処理 [player3D.cpp]
// Author : takahashi shota
//
//=============================================================================

//=============================================================================
//インクルード読み込み
//=============================================================================
#include "player3D.h"
#include "manager.h"
#include "model.h"
#include "vertex.h"
#include "camera.h"
#include "object3D.h"
#include "shadowS.h"
#include "textobject.h"
#include "meshfield.h"
#include "game.h"

//静的メンバ変数宣言
D3DXVECTOR3		CPlayer3D::m_pos;
D3DXVECTOR3		CPlayer3D::m_rot;

//==============================================================================
// コンストラクタ
//==============================================================================
CPlayer3D::CPlayer3D(int nPriority, int nType)
{
	//変数初期化
	m_bMotionChange = false;
	m_nBrendFrame = 5;
}

//==============================================================================
// デストラクタ
//==============================================================================
CPlayer3D::~CPlayer3D()
{

}

//==============================================================================
// 初期化処理
//==============================================================================
HRESULT CPlayer3D::Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	//モーション読み込み
	LoadMotion();

	for (int nCntModel = 0; nCntModel < (int)m_nNumModel; nCntModel++)
	{
		//モデルを生成
		m_apModel[nCntModel] = CModel::Create(D3DXVECTOR3(m_aOffset[nCntModel][0], m_aOffset[nCntModel][1], m_aOffset[nCntModel][2]),
			D3DXVECTOR3(m_aOffset[nCntModel][3], m_aOffset[nCntModel][4], m_aOffset[nCntModel][5]), &m_pModelName[nCntModel][0]);

		//親子関係を付ける
		m_apModel[nCntModel]->SetParent(m_apModel[m_aIndexParent[nCntModel]]);
	}

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ローカル変数宣言
	int nNumVtx;			    // 頂点数
	DWORD sizeFVF;				// 頂点フォーマットのサイズ
	BYTE *pVtxBuff;				// 頂点バッファへのポインタ
	D3DXMATERIAL *pMat;			// マテリアルへのポインタ

	// マテリアル情報に対するポインタを取得
	pMat = (D3DXMATERIAL*)m_apModel[0]->GetBuff()->GetBufferPointer();

	for (int nCntMat = 13; nCntMat < (int)m_nNumModel; nCntMat++)
	{
		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			// ファイル名を使用してテクスチャを読み込む
			//D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/negromate_baseColor.jpeg", &m_pTexture);
		}
		//テクスチャ情報を受け渡す
		m_apModel[nCntMat]->SetTexture(m_pTexture);
	}

	// 頂点数を取得
	nNumVtx = m_apModel[0]->GetMash()->GetNumVertices();

	// 頂点フォーマットのサイズの取得
	sizeFVF = D3DXGetFVFVertexSize(m_apModel[0]->GetMash()->GetFVF());

	// 頂点バッファをロック
	m_apModel[0]->GetMash()->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	// 頂点座標の比較と更新
	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	// 頂点座標の代入

		// 各座標の最大値の比較
		if (m_MaxPlayer.x < vtx.x)
		{
			m_MaxPlayer.x = vtx.x;
		}
		if (m_MaxPlayer.y < vtx.y)
		{
			m_MaxPlayer.y = vtx.y;
		}
		if (m_MaxPlayer.z < vtx.z)
		{
			m_MaxPlayer.z = vtx.z;
		}

		// 各座標の最小値の比較
		if (m_MinPlayer.x > vtx.x)
		{
			m_MinPlayer.x = vtx.x;
		}
		if (m_MinPlayer.y > vtx.y)
		{
			m_MinPlayer.y = vtx.y;
		}
		if (m_MinPlayer.z > vtx.z)
		{
			m_MinPlayer.z = vtx.z;
		}

		pVtxBuff += sizeFVF;	// 頂点フォーマットのサイズ分ポインタを進める
	}

	// 頂点バッファをアンロック
	m_apModel[0]->GetMash()->UnlockVertexBuffer();

	//位置
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//向き
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	//影をクリエイト
	//CShadowS::Create();

	return S_OK;
}

//==============================================================================
// 終了処理
//==============================================================================
void CPlayer3D::Uninit(void)
{
	//オブジェクトの破棄
	Release();
}

//==============================================================================
// 更新処理
//==============================================================================
void CPlayer3D::Update(void)
{
	//キーボード取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//位置更新
	m_posold = m_pos;

	//モーションの更新
	UpdateMotion(m_MotionType);

	// 移動量の加算
	m_pos += m_move;

	//カメラ角度取得
	D3DXVECTOR3 RotationCamera = CManager::GetCamera()->GetRot();
	float RotCameraY = RotationCamera.y;

	// 角度修正
	if (RotCameraY > D3DX_PI) { RotCameraY -= D3DX_PI * 2; }
	if (RotCameraY < -D3DX_PI) { RotCameraY += D3DX_PI * 2; }

	// Wキーのモデルの移動
	if (pInputKeyboard->GetPress(DIK_UP) == true || pInputKeyboard->GetPress(DIK_W) == true)
	{
		if (m_nMoveCnt < 10)
		{
			m_nMoveCnt++;
		}

		//モーションの変化
		m_MotionType = MOTIONTYPE_MOVE;

		//移動量計算
		if (pInputKeyboard->GetPress(DIK_A) == true)
		{
			// 左上方向
			m_move.x -= cosf(RotCameraY + D3DX_PI / 4) * PLAYER_SPEED;
			m_move.z += sinf(RotCameraY + D3DX_PI / 4) * PLAYER_SPEED;
			m_rotDest.y = RotCameraY + (D3DX_PI * 3 / 4);
		}
		else if (pInputKeyboard->GetPress(DIK_D) == true)
		{
			// 右上方向
			m_move.x += cosf(RotCameraY - D3DX_PI / 4) * PLAYER_SPEED;
			m_move.z -= sinf(RotCameraY - D3DX_PI / 4) * PLAYER_SPEED;
			m_rotDest.y = RotCameraY - (D3DX_PI * 3 / 4);
		}
		else
		{
			// 上方向
			m_move.x += sinf(RotCameraY) * PLAYER_SPEED;
			m_move.z += cosf(RotCameraY) * PLAYER_SPEED;
			m_rotDest.y = RotCameraY + D3DX_PI;
		}
	}

	// Wキーのモデルの移動
	else if (pInputKeyboard->GetPress(DIK_DOWN) == true || pInputKeyboard->GetPress(DIK_S) == true)
	{
		if (m_nMoveCnt < 10)
		{
			m_nMoveCnt++;
		}

		//モーションの変化
		m_MotionType = MOTIONTYPE_MOVE;

		if (pInputKeyboard->GetPress(DIK_A) == true)
		{
			// 左下方向
			//移動量計算
			m_move.x -= cosf(RotCameraY - D3DX_PI / 4) * PLAYER_SPEED;
			m_move.z += sinf(RotCameraY - D3DX_PI / 4) * PLAYER_SPEED;
			m_rotDest.y = RotCameraY - D3DX_PI / -4;
		}
		else if (pInputKeyboard->GetPress(DIK_D) == true)
		{
			// 右下方向
			//移動量計算
			m_move.x += cosf(RotCameraY + D3DX_PI / 4) * PLAYER_SPEED;
			m_move.z -= sinf(RotCameraY + D3DX_PI / 4) * PLAYER_SPEED;
			m_rotDest.y = RotCameraY - D3DX_PI / 4;
		}
		else
		{
			// 下方向
			m_move.x -= sinf(RotCameraY) * PLAYER_SPEED;
			m_move.z -= cosf(RotCameraY) * PLAYER_SPEED;
			m_rotDest.y = RotCameraY;
		}
	}

	else if (pInputKeyboard->GetPress(DIK_A) == true)
	{
		//モーションの変化
		m_MotionType = MOTIONTYPE_MOVE;

		// 左方向
		if (m_nMoveCnt < 10)
		{
			m_nMoveCnt++;
		}
		m_move.x -= cosf(RotCameraY) * PLAYER_SPEED;
		m_move.z += sinf(RotCameraY) * PLAYER_SPEED;
		m_rotDest.y = RotCameraY + (D3DX_PI / 2);
	}
	else if (pInputKeyboard->GetPress(DIK_D) == true)
	{
		//モーションの変化
		m_MotionType = MOTIONTYPE_MOVE;

		// 右方向
		if (m_nMoveCnt < 10)
		{
			m_nMoveCnt++;
		}
		m_move.x += cosf(RotCameraY) * PLAYER_SPEED;
		m_move.z -= sinf(RotCameraY) * PLAYER_SPEED;
		m_rotDest.y = RotCameraY + (D3DX_PI / -2);
	}

	else
	{
		if (m_nMoveCnt > 5)
		{
			m_nMoveCnt--;
		}
	}

	// 移動モーションから待機モーションへ
	if (m_MotionType == MOTIONTYPE_MOVE && m_nMoveCnt == 5)
	{
		m_fCounterMotion = 0;
		m_Key = 0;
		m_MotionType = MOTIONTYPE_NEUTRAL;
	}

	//各パーツの更新処理
	for (int nCnt = 0; nCnt < (int)m_nNumModel; nCnt++)
	{
		m_apModel[nCnt]->MotionPos(D3DXVECTOR3(m_aOffset[nCnt][0], m_aOffset[nCnt][1], m_aOffset[nCnt][2]));
		m_apModel[nCnt]->MotionRot(D3DXVECTOR3(m_aOffset[nCnt][3], m_aOffset[nCnt][4], m_aOffset[nCnt][5]));
	}

	// 目的の回転角の上限
	if (m_rotDest.y - m_rot.y < -D3DX_PI)
	{
		m_rotDest.y += D3DX_PI * 2.0f;
	}
	else if (m_rotDest.y - m_rot.y > D3DX_PI)
	{
		m_rotDest.y -= D3DX_PI * 2.0f;
	}

	// 向きの更新
	m_rot.y += (m_rotDest.y - m_rot.y) * 0.1f;

	// 現在の回転角の上限
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}
	else if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}

	// 加速後の減速処理
	m_move.x += (0.0f - m_move.x) * 0.7f;
	m_move.z += (0.0f - m_move.z) * 0.7f;

	//当たり判定のオンオフ 　注意falseスタート
	if (CGame::GetSwitchCollision() == false)
	{
		int n1 = CGame::GetMaxObject3D();					//ゲームで生成したオブジェクト3Dの数
		int n2 = CTextobject::GetTextObject3D();			//テキストで生成したオブジェクト3Dの数

		//当てり判定
		for (int nCount = 0; nCount < n1 + n2; nCount++)
		{
			CObject3D *pObj;

			//テキストで生成した回数分以外で生成したテキストで生成した
			if (n2 <= nCount)
			{
				pObj = CGame::GetObject(nCount - CTextobject::GetTextObject3D());
			}

			//テキストで生成したテキストで生成した
			else
			{
				pObj = CTextobject::GetObject(nCount);
			}

			if (pObj != NULL)
			{
				//オブジェクト3Dの当たり判定
				pObj->CollisionVec(&m_pos, &m_posold, &m_move, m_MaxPlayer.x, m_MinPlayer.x, m_MaxPlayer.z, m_MinPlayer.z, m_MaxPlayer.y, m_MinPlayer.y);
			}
		}

		//オブジェクトへのポインタ生成
		CVertex *pVer;
		pVer = CGame::GetVertex();

		//頂点オブジェクトの当たり判定
		pVer->CollisionVec(&m_pos, &m_posold, &m_move, m_MaxPlayer.x - 0.0f, m_MinPlayer.x + 0.0f, m_MaxPlayer.z - 0.0f, m_MinPlayer.z + 0.0f, m_MaxPlayer.y, m_MinPlayer.y);
	}

	//メッシュフィールド範囲外の場合の移動制限
	if (CMeshfield::GetMeshFildX() <= m_pos.x || -CMeshfield::GetMeshFildX() >= m_pos.x)
	{
		m_pos.x = m_posold.x;
	}

	if (CMeshfield::GetMeshFildZ() <= m_pos.z || -CMeshfield::GetMeshFildZ() >= m_pos.z)
	{
		m_pos.z = m_posold.z;
	}
}

//==============================================================================
// 描画処理
//==============================================================================
void CPlayer3D::Draw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//ローカル
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きの反転
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置の反転
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int nCnt = 0; nCnt < (int)m_nNumModel; nCnt++)
	{
		//生成したパーツ分を描画する
		m_apModel[nCnt]->Draw();
	}
}

//==============================================================================
// 生成処理
//==============================================================================
CPlayer3D * CPlayer3D::Create()
{
	//プレイヤーを生成
	CPlayer3D *pPlayer3D = NULL;
	pPlayer3D = new CPlayer3D;

	//NULLチェック
	if (pPlayer3D != NULL)
	{
		pPlayer3D->Init(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0.0f, 0.0f);
	}

	return pPlayer3D;
}

//==============================================================================
// .txtフォルダの読み込み
//==============================================================================
void CPlayer3D::LoadMotion(void)
{
	// ローカル変数宣言
	FILE *pFile = NULL;
	char aEqual[2] = { NULL };					// 「=」読み取り用変数
	bool bComment = false;						// コメントアウトするか
	char aText[TEXT_LENGTH] = { NULL };			// テキスト読み取り用変数
	char aCharaSet[DATA_LENGTH] = { NULL };		// キャラデータ読み取り用変数
	char aPartsSet[DATA_LENGTH] = { NULL };		// パーツデータ読み取り用変数
	char aMotionSet[DATA_LENGTH] = { NULL };	// モーション読み取り用変数
	char aKeySet[DATA_LENGTH] = { NULL };		// キー設定情報読み取り用変数
	char aKey[DATA_LENGTH] = { NULL };			// キー情報読み取り用変数

	// strcmp読み取り用ポインタ
	char *pText = &aText[0];
	char *pCharaSet = &aCharaSet[0];
	char *pPartsSet = &aPartsSet[0];
	char *pMotionSet = &aMotionSet[0];
	char *pKeySet = &aKeySet[0];
	char *pKey = &aKey[0];

	// データの読み込み
	pFile = fopen("data/TEXT/motion_player00.txt", "r");

	if (pFile != NULL)
	{ 
		//ファイル展開可能
		aText[0] = { NULL };
		aCharaSet[0] = { NULL };
		aPartsSet[0] = { NULL };
		aMotionSet[0] = { NULL };
		aKeySet[0] = { NULL };
		aKey[0] = { NULL };
		int nIdxParts = 0;			// パーツ数
		int nMotion = 0;			// モーションの数
		int nCntFile = 0;			// Xデータの数
		int nAs = 0;

		while (strcmp("END_SCRIPT", pText) != 0)
		{
			aText[0] = { NULL };
			if (bComment == false)
			{
				// コメントアウトしていない
				fscanf(pFile, "%s", &aText[0]);

				if (aText[0] == '#')
				{
					// 文字列の先頭が「#」ならばコメントアウトへ
					bComment = true;
				}
				else
				{
					// 通常時
					if (strcmp("NUM_MODEL", pText) == 0)
					{
						// モデルの数
						fscanf(pFile, "%s", &aEqual[0]);
						fscanf(pFile, "%d", &m_nNumModel);
					}
					else if (strcmp("MODEL_FILENAME", pText) == 0)
					{
						// Xファイル名の読み込み
						fscanf(pFile, "%s", &aEqual[0]);
						fscanf(pFile, "%s", &m_pModelName[nCntFile][0]);
						nCntFile++;
					}
					else if (strcmp("CHARACTERSET", pText) == 0)
					{
						// キャラの情報
						while (strcmp("END_CHARACTERSET", pCharaSet) != 0)
						{
							// キャラ情報の読み取り
							fscanf(pFile, "%s", &aCharaSet[0]);
							if (strcmp("NUM_PARTS", pCharaSet) == 0)
							{

							}
							else if (strcmp("PARTSSET", pCharaSet) == 0)
							{
								// パーツ情報
								aPartsSet[0] = { NULL };

								while (strcmp("END_PARTSSET", pPartsSet) != 0)
								{
									fscanf(pFile, "%s", &aPartsSet[0]);
									if (strcmp("INDEX", pPartsSet) == 0)
									{
										// パーツ情報の読み取り
										fscanf(pFile, "%s", &aEqual[0]);
										fscanf(pFile, "%d", &nIdxParts);
									}
									else if (strcmp("PARENT", pPartsSet) == 0)
									{
										// パーツの親情報
										fscanf(pFile, "%s", &aEqual[0]);
										fscanf(pFile, "%d", &m_aIndexParent[nIdxParts]);
									}
									else if (strcmp("POS", pPartsSet) == 0)
									{
										// パーツの位置情報
										fscanf(pFile, "%s", &aEqual[0]);
										fscanf(pFile, "%f", &m_aOffset[nIdxParts][0]);
										fscanf(pFile, "%f", &m_aOffset[nIdxParts][1]);
										fscanf(pFile, "%f", &m_aOffset[nIdxParts][2]);
										//g_player.aModel[nIdxParts].posReset = g_player.aModel[nIdxParts].pos;
									}
									else if (strcmp("ROT", pPartsSet) == 0)
									{
										// パーツの角度情報
										fscanf(pFile, "%s", &aEqual[0]);
										fscanf(pFile, "%f", &m_aOffset[nIdxParts][3]);
										fscanf(pFile, "%f", &m_aOffset[nIdxParts][4]);
										fscanf(pFile, "%f", &m_aOffset[nIdxParts][5]);
									}
								}
							}
						}
					}
					else if (strcmp("MOTIONSET", pText) == 0)
					{
						// 変数の初期化
						aMotionSet[0] = { NULL };

						// ローカル変数宣言
						int nLoop = 0;
						int nKeySet = 0;

						while (strcmp("END_MOTIONSET", pMotionSet) != 0)
						{
							// モーションの読み込み
							fscanf(pFile, "%s", &aMotionSet[0]);
							if (strcmp("LOOP", pMotionSet) == 0)
							{
								// ループするか
								fscanf(pFile, "%s", &aEqual[0]);
								fscanf(pFile, "%d", &nLoop);
								if (nLoop == 1)
								{
									// １の場合ループする
									m_bLoopKeep = true;
									m_Loop[nMotion] = true;
								}
							}
							else if (strcmp("NUM_KEY", pMotionSet) == 0)
							{
								// キー数の読み込み
								fscanf(pFile, "%s", &aEqual[0]);
								fscanf(pFile, "%d", &m_nNumKeyKeep);
							}
							else if (strcmp("KEYSET", pMotionSet) == 0)
							{
								// キーの読み込み
								// ローカル変数宣言
								int nKey = 0;

								// 変数の初期化
								aKeySet[0] = { NULL };

								while (strcmp("END_KEYSET", pKeySet) != 0)
								{
									// キー情報項目の読み込み
									fscanf(pFile, "%s", &aKeySet[0]);

									if (aKeySet[0] == '#')
									{
										// コメントアウト
										// ローカル変数宣言
										char c = NULL;
										char d = NULL;

										fscanf(pFile, "%c", &c);

										while (c != '\n' && d != '\n')
										{
											fscanf(pFile, "%s", &aKey[0]);
											fscanf(pFile, "%c", &d);
										}
									}

									if (strcmp("KEY", pKeySet) == 0)
									{
										// キー情報の読み込み
										aKey[0] = { NULL };
										while (strcmp("END_KEY", pKey) != 0)
										{
											// 位置・角度の読み込み
											fscanf(pFile, "%s", &aKey[0]);

											if (strcmp("POS", pKey) == 0)
											{
												// 位置情報の読み込み
												fscanf(pFile, "%s", &aEqual[0]);

												// 位置情報の読み込み
												fscanf(pFile, "%f", &m_Player3D[nMotion][nKeySet][nKey][0]);
												fscanf(pFile, "%f", &m_Player3D[nMotion][nKeySet][nKey][1]);
												fscanf(pFile, "%f", &m_Player3D[nMotion][nKeySet][nKey][2]);
												m_Player3D[nMotion][nKeySet][nKey][0] += m_aOffset[nKey][0];
												m_Player3D[nMotion][nKeySet][nKey][1] += m_aOffset[nKey][1];
												m_Player3D[nMotion][nKeySet][nKey][2] += m_aOffset[nKey][2];
											}
											else if (strcmp("ROT", pKey) == 0)
											{
												// 角度情報の読み込み
												fscanf(pFile, "%s", &aEqual[0]);
												fscanf(pFile, "%f", &m_Player3D[nMotion][nKeySet][nKey][3]);
												fscanf(pFile, "%f", &m_Player3D[nMotion][nKeySet][nKey][4]);
												fscanf(pFile, "%f", &m_Player3D[nMotion][nKeySet][nKey][5]);
											}
										}
										nKey++;
									}
									else if (strcmp("FRAME", pKeySet) == 0)
									{
										// キーフレーム数の読み込み
										fscanf(pFile, "%s", &aEqual[0]);

										fscanf(pFile, "%d", &m_nFrame[nMotion][nKeySet]);
										m_nFrameTotal[nMotion] += m_nFrame[nMotion][nKeySet];

										if (m_Loop[nMotion] == false && nKeySet == (m_NumKey[nMotion] - 1))
										{
											m_nFrameTotal[nMotion] -= m_nFrame[nMotion][nKeySet];
										}
									}
								}

								nKeySet++;
							}
						}

						m_NumKey[nMotion] = nKeySet;	// キー数の設定
						nMotion++;
					}
				}
			}
			else if (bComment == true)
			{
				// コメントアウト処理
				// ローカル変数宣言
				char a = NULL;
				char b = NULL;

				fscanf(pFile, "%c", &a);

				while (a != '\n' && b != '\n')
				{
					fscanf(pFile, "%s", &aText[0]);
					fscanf(pFile, "%c", &b);
				}
				bComment = false;
			}
		}

		//テキストを閉じる
		fclose(pFile);
	}

	else
	{ 
		// ファイル展開不可
	}
}

//==============================================================================
// モーションの更新
//==============================================================================
void CPlayer3D::UpdateMotion(MOTIONTYPE MOTIONTYPE)
{
	// キー数とループ情報の代入
	m_nNumKeyKeep = m_NumKey[MOTIONTYPE];
	m_bLoopKeep = m_Loop[MOTIONTYPE];

	// モーションカウンターの加算
	if (m_bMotionChange == true)
	{
		// モーションブレンド実行時
		if (m_fCounterMotion < m_nBrendFrame)
		{
			// カウント上限
			m_fCounterMotion++;
		}
	}
	else
	{
		// 通常時
		if (m_fCounterMotion < m_nFrame[MOTIONTYPE][m_Key])
		{
			// カウント上限
			m_fCounterMotion++;
		}
	}

	// モデルパーツごとのモーションアニメーション
	for (int nCnt = 0; nCnt < MAX_PLAYER_PARTS; nCnt++)
	{
		if (m_Key == m_nNumKeyKeep - 1 && m_bLoopKeep == true)
		{
			// ループして最初に戻るとき
			m_aOffset[nCnt][0] = m_Player3D[MOTIONTYPE][m_Key][nCnt][0] + (m_Player3D[MOTIONTYPE][0][nCnt][0] - m_Player3D[MOTIONTYPE][m_Key][nCnt][0]) * ((float)m_fCounterMotion / (float)m_nFrame[MOTIONTYPE][m_Key]);
			m_aOffset[nCnt][1] = m_Player3D[MOTIONTYPE][m_Key][nCnt][1] + (m_Player3D[MOTIONTYPE][0][nCnt][1] - m_Player3D[MOTIONTYPE][m_Key][nCnt][1]) * ((float)m_fCounterMotion / (float)m_nFrame[MOTIONTYPE][m_Key]);
			m_aOffset[nCnt][2] = m_Player3D[MOTIONTYPE][m_Key][nCnt][2] + (m_Player3D[MOTIONTYPE][0][nCnt][2] - m_Player3D[MOTIONTYPE][m_Key][nCnt][2]) * ((float)m_fCounterMotion / (float)m_nFrame[MOTIONTYPE][m_Key]);
			m_aOffset[nCnt][3] = m_Player3D[MOTIONTYPE][m_Key][nCnt][3] + (m_Player3D[MOTIONTYPE][0][nCnt][3] - m_Player3D[MOTIONTYPE][m_Key][nCnt][3]) * ((float)m_fCounterMotion / (float)m_nFrame[MOTIONTYPE][m_Key]);
			m_aOffset[nCnt][4] = m_Player3D[MOTIONTYPE][m_Key][nCnt][4] + (m_Player3D[MOTIONTYPE][0][nCnt][4] - m_Player3D[MOTIONTYPE][m_Key][nCnt][4]) * ((float)m_fCounterMotion / (float)m_nFrame[MOTIONTYPE][m_Key]);
			m_aOffset[nCnt][5] = m_Player3D[MOTIONTYPE][m_Key][nCnt][5] + (m_Player3D[MOTIONTYPE][0][nCnt][5] - m_Player3D[MOTIONTYPE][m_Key][nCnt][5]) * ((float)m_fCounterMotion / (float)m_nFrame[MOTIONTYPE][m_Key]);
			m_aOffsetMemo[nCnt][0] = m_aOffset[nCnt][0];
			m_aOffsetMemo[nCnt][1] = m_aOffset[nCnt][1];
			m_aOffsetMemo[nCnt][2] = m_aOffset[nCnt][2];
			m_aOffsetMemo[nCnt][3] = m_aOffset[nCnt][3];
			m_aOffsetMemo[nCnt][4] = m_aOffset[nCnt][4];
			m_aOffsetMemo[nCnt][5] = m_aOffset[nCnt][5];
		}
		else if (m_bMotionChange == true)
		{
			// モーションブレンド
			m_aOffset[nCnt][0] = m_aOffsetMemo[nCnt][0] + (m_Player3D[m_MotionType][0][nCnt][0] - m_aOffsetMemo[nCnt][0]) * ((float)m_fCounterMotion / (float)m_nBrendFrame);
			m_aOffset[nCnt][1] = m_aOffsetMemo[nCnt][1] + (m_Player3D[m_MotionType][0][nCnt][1] - m_aOffsetMemo[nCnt][1]) * ((float)m_fCounterMotion / (float)m_nBrendFrame);
			m_aOffset[nCnt][2] = m_aOffsetMemo[nCnt][2] + (m_Player3D[m_MotionType][0][nCnt][2] - m_aOffsetMemo[nCnt][2]) * ((float)m_fCounterMotion / (float)m_nBrendFrame);
			m_aOffset[nCnt][3] = m_aOffsetMemo[nCnt][3] + (m_Player3D[m_MotionType][0][nCnt][3] - m_aOffsetMemo[nCnt][3]) * ((float)m_fCounterMotion / (float)m_nBrendFrame);
			m_aOffset[nCnt][4] = m_aOffsetMemo[nCnt][4] + (m_Player3D[m_MotionType][0][nCnt][4] - m_aOffsetMemo[nCnt][4]) * ((float)m_fCounterMotion / (float)m_nBrendFrame);
			m_aOffset[nCnt][5] = m_aOffsetMemo[nCnt][5] + (m_Player3D[m_MotionType][0][nCnt][5] - m_aOffsetMemo[nCnt][5]) * ((float)m_fCounterMotion / (float)m_nBrendFrame);
			m_aOffsetMemo[nCnt][0] = m_aOffset[nCnt][0];
			m_aOffsetMemo[nCnt][1] = m_aOffset[nCnt][1];
			m_aOffsetMemo[nCnt][2] = m_aOffset[nCnt][2];
			m_aOffsetMemo[nCnt][3] = m_aOffset[nCnt][3];
			m_aOffsetMemo[nCnt][4] = m_aOffset[nCnt][4];
			m_aOffsetMemo[nCnt][5] = m_aOffset[nCnt][5];
		}
		else
		{
			// 通常時
			m_aOffset[nCnt][0] = m_Player3D[MOTIONTYPE][m_Key][nCnt][0] + (m_Player3D[MOTIONTYPE][m_Key + 1][nCnt][0] - m_Player3D[MOTIONTYPE][m_Key][nCnt][0]) * ((float)m_fCounterMotion / (float)m_nFrame[MOTIONTYPE][m_Key]);
			m_aOffset[nCnt][1] = m_Player3D[MOTIONTYPE][m_Key][nCnt][1] + (m_Player3D[MOTIONTYPE][m_Key + 1][nCnt][1] - m_Player3D[MOTIONTYPE][m_Key][nCnt][1]) * ((float)m_fCounterMotion / (float)m_nFrame[MOTIONTYPE][m_Key]);
			m_aOffset[nCnt][2] = m_Player3D[MOTIONTYPE][m_Key][nCnt][2] + (m_Player3D[MOTIONTYPE][m_Key + 1][nCnt][2] - m_Player3D[MOTIONTYPE][m_Key][nCnt][2]) * ((float)m_fCounterMotion / (float)m_nFrame[MOTIONTYPE][m_Key]);
			m_aOffset[nCnt][3] = m_Player3D[MOTIONTYPE][m_Key][nCnt][3] + (m_Player3D[MOTIONTYPE][m_Key + 1][nCnt][3] - m_Player3D[MOTIONTYPE][m_Key][nCnt][3]) * ((float)m_fCounterMotion / (float)m_nFrame[MOTIONTYPE][m_Key]);
			m_aOffset[nCnt][4] = m_Player3D[MOTIONTYPE][m_Key][nCnt][4] + (m_Player3D[MOTIONTYPE][m_Key + 1][nCnt][4] - m_Player3D[MOTIONTYPE][m_Key][nCnt][4]) * ((float)m_fCounterMotion / (float)m_nFrame[MOTIONTYPE][m_Key]);
			m_aOffset[nCnt][5] = m_Player3D[MOTIONTYPE][m_Key][nCnt][5] + (m_Player3D[MOTIONTYPE][m_Key + 1][nCnt][5] - m_Player3D[MOTIONTYPE][m_Key][nCnt][5]) * ((float)m_fCounterMotion / (float)m_nFrame[MOTIONTYPE][m_Key]);
			m_aOffsetMemo[nCnt][0] = m_aOffset[nCnt][0];
			m_aOffsetMemo[nCnt][1] = m_aOffset[nCnt][1];
			m_aOffsetMemo[nCnt][2] = m_aOffset[nCnt][2];
			m_aOffsetMemo[nCnt][3] = m_aOffset[nCnt][3];
			m_aOffsetMemo[nCnt][4] = m_aOffset[nCnt][4];
			m_aOffsetMemo[nCnt][5] = m_aOffset[nCnt][5];
		}

		if (m_bMotionChange == false)
		{
			// モーション変化なし
			if (m_fCounterMotion == m_nFrame[MOTIONTYPE][m_Key])
			{
				// キーフレーム終了時
			 
				//if (m_MotionType != MOTIONTYPE_JUMP || m_Key != m_nNumKeyKeep - 2)
				{
					// ジャンプ以外でキー終了時リセット
					m_fCounterMotion = 0;
				}

				if (m_Key == m_nNumKeyKeep - 1 && m_bLoopKeep == true)
				{
					// ループするとき
					m_Key = 0;
				}
				else if (m_Key == m_nNumKeyKeep - 2 && m_bLoopKeep == false)
				{
					// ループせず終了するとき
				 
					//if (m_MotionTypeOld != MOTIONTYPE_JUMP)
					{
						// 直前がジャンプ以外の時
						m_MotionType = MOTIONTYPE_NEUTRAL;	// ニュートラルへ移行
						m_fCounterMotion = 0;
						break;
					}
				}
				else if (m_Key < m_nNumKeyKeep)
				{
					// キーのカウント
					m_Key++;
				}
			}
			else if (m_MotionTypeOld != m_MotionType)
			{
				// モーション変化時	
				m_Key = 0;
				m_fCounterMotion = 0;
				m_bMotionChange = true;

				if (m_MotionTypeOld == MOTIONTYPE_NEUTRAL && m_MotionType == MOTIONTYPE_MOVE)
				{
					// 移動からニュートラル時
					m_nBrendFrame = 20;
				}
				else if (m_MotionTypeOld == MOTIONTYPE_MOVE && m_MotionType == MOTIONTYPE_NEUTRAL)
				{
					// ニュートラルから移動時
					m_nBrendFrame = 40;
				}
				break;
			}
		}
		else if (m_bMotionChange == true)
		{
			// モーションブレンド時のカウントリセット
			if (m_fCounterMotion == m_nBrendFrame || m_MotionTypeOld != m_MotionType)
			{
				m_Key = 0;
				m_fCounterMotion = 0;
				m_bMotionChange = false;
			}
		}
	}

	// 直前のモーション状態の保存
	m_MotionTypeOld = m_MotionType;
}

//==============================================================================
// Get関数　pos
//==============================================================================
D3DXVECTOR3 CPlayer3D::GetPosition(void)
{
	return m_pos;
}

//==============================================================================
// Get関数　rot
//==============================================================================
D3DXVECTOR3 CPlayer3D::GetRotation(void)
{
	return m_rot;
}
