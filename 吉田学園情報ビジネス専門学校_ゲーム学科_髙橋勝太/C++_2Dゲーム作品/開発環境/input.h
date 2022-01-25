//=============================================================================
//
// 入力処理 [input.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _INPUT_H_
#define _INPUT_H_

//=============================================================================
//インクルード読み込み
//=============================================================================
#include "main.h"

//=============================================================================
//インプットクラスの定義
//=============================================================================
class CInput
{
public:
	//列挙型（ボタンの種類)
	typedef enum
	{
		RETURN = 0,
		X,
		W,
		S,
		A,
		D,
		SPACE,
		BACKSPACE,
		F,
		T,
		B,
		LEFT,
		RIGHT,
		UP,
		DOWN,
		P,
		KEYINFO_MAX
	} KEYINFO;

	CInput();														//コンストラクタ
	virtual ~CInput();												//デストラクタ
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);			//初期化処理
	virtual void Uninit(void);										//終了処理
	virtual void Update(void) = 0;									//更新処理
protected:
	LPDIRECTINPUTDEVICE8		m_pDeviceKey;						//キーデバイス
	static LPDIRECTINPUTDEVICE8 m_pDevice;							//デバイスへのポインタ
	static LPDIRECTINPUT8		m_pInput;							//入力処理へのポインタ
};

//=============================================================================
//インプットキーボードクラスの定義
//=============================================================================
class CInputKeyboard : CInput
{
public:
	CInputKeyboard();									//コンストラク
	~CInputKeyboard();									//デストラクタ
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//初期化処理
	void Uninit(void);									//終了処理
	void Update(void);									//更新処理
	bool GetPress(int nKey);							//プレス処理
	bool GetTrigger(int nKey);							//トリガー処理
private:
	BYTE m_aKeyState[256];								//プレス状態
	BYTE m_aKeyStateTrigger[256];						//トリガー状態
};
#endif
