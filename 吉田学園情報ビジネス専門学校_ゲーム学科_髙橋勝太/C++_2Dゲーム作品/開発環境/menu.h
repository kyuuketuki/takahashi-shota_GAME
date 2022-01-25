//=============================================================================
//
// ���j���[���� [menu.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _MENU_H_
#define _MENU_H_

//==============================================================================
//�C���N���[�h
//==============================================================================
#include "main.h"
#include "scene.h"
#include "scene2D.h"

//=============================================================================
// ���j���[�N���X�̒�`
//=============================================================================
class CMenu : public CScene
{
public:
	CMenu();								//�R���X�g���N�^
	~CMenu();								//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY);			//����������
	void Uninit(void);													//�I������
	void Update(void);													//�X�V����
	void Draw(void);													//�`�揈��

	static CMenu *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY);	//��������
																		
private:
	
};
#endif
