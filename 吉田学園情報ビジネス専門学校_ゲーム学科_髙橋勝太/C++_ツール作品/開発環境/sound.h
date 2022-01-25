//=============================================================================
//
// サウンド処理 [sound.h]
// Author : takahashi syota
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"
#include "renderer.h"

//=============================================================================
// サウンドファイル
//=============================================================================
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// BGM0
	SOUND_LABEL_SE_SHOT,		// 弾発射音
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
class CSound
{
public:
	CSound();								//コンストラクタ
	virtual ~CSound();						//デストラクタ

	typedef enum
	{
		SOUND_LABEL_BGM000 = 0,		// BGM0
		SOUND_LABEL_SE_SHOT,		// 弾発射音
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	HRESULT Init(HWND hWnd);
	void	Uninit(void);
	HRESULT Play(SOUND_LABEL label);
	void	Stop(SOUND_LABEL label);

private:
	//パラメータ構造体定義
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント
	} SOUNDPARAM;

	HRESULT ChekChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunk(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
	
	IXAudio2 *m_pXAudio2 = NULL;
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// ソースボイス
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// オーディオデータサイズ

	// 各音素材のパラメータ
	SOUNDPARAM m_aParam[SOUND_LABEL_MAX] =
	{
		{ "data/BGM/bgm000.wav", -1 },						// BGM0
		{ "data/SE/shot000.wav", 0 },						// SE0_弾発射音
	};
};

#endif