//=============================================================================
//
// ���͏��� [input.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _INPUT_H_
#define _INPUT_H_

//=============================================================================
//�C���N���[�h�ǂݍ���
//=============================================================================
#include "main.h"

//=============================================================================
//�C���v�b�g�N���X�̒�`
//=============================================================================
class CInput
{
public:
	//�񋓌^�i�{�^���̎��)
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

	CInput();														//�R���X�g���N�^
	virtual ~CInput();												//�f�X�g���N�^
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);			//����������
	virtual void Uninit(void);										//�I������
	virtual void Update(void) = 0;									//�X�V����
protected:
	LPDIRECTINPUTDEVICE8		m_pDeviceKey;						//�L�[�f�o�C�X
	static LPDIRECTINPUTDEVICE8 m_pDevice;							//�f�o�C�X�ւ̃|�C���^
	static LPDIRECTINPUT8		m_pInput;							//���͏����ւ̃|�C���^
};

//=============================================================================
//�C���v�b�g�L�[�{�[�h�N���X�̒�`
//=============================================================================
class CInputKeyboard : CInput
{
public:
	CInputKeyboard();									//�R���X�g���N
	~CInputKeyboard();									//�f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);		//����������
	void Uninit(void);									//�I������
	void Update(void);									//�X�V����
	bool GetPress(int nKey);							//�v���X����
	bool GetTrigger(int nKey);							//�g���K�[����
private:
	BYTE m_aKeyState[256];								//�v���X���
	BYTE m_aKeyStateTrigger[256];						//�g���K�[���
};
#endif
