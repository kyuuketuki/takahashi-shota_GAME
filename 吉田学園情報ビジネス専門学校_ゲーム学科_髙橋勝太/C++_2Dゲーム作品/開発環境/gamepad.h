//==============================================================================
//
// �Q�[���p�b�h����[gamepad.h]
// Author; takahashi shota
//
//==============================================================================

#ifndef _GAMEPAD_H_
#define _GAMEPAD_H_

//==============================================================================
//�C���N���[�h
//==============================================================================
#include "main.h"
#include "input.h"

//=============================================================================
// �Q�[���p�b�h�N���X�̒�`
//=============================================================================
class CGamepad : CInput
{
public:

	//�񋓌^�i�{�^���̎�ށj
	typedef enum
	{
		ButtonStateNone = 0,
		ButtonStateDown,
		ButtonStatePush,
		ButtonStateUp,
		ButtonStateMax,
	} ButtonState;

	CGamepad();
	~CGamepad();

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);

	void ButtonSet(DIJOYSTATE pad_data);			//�{�^�����X�e�B�b�N����
	bool IsButtonPush(KEYINFO button);				//�v���X
	bool IsButtonUp(KEYINFO button);				//�����[�X
	bool IsButtonDown(KEYINFO button);				//�g���K�[
	bool BuPu(KEYINFO button, int nCnt);			//�v���X(����)
	bool BuUp(KEYINFO button, int nCnt);			//�����[�X(����)
	bool BuDo(KEYINFO button, int nCnt);			//�g���K�[(����)

	static BOOL CALLBACK EnumJoysticksCallback(
		const DIDEVICEINSTANCE *pdidoi, VOID *pContext);		// �R�[���o�b�N�֐�
	int GetNumControl(void) { return m_nController; }			// �R���g���[���[�̐����擾
private:
	ButtonState m_ButtonStates[KEYINFO::KEYINFO_MAX];
	static int m_nController;
};
#endif

