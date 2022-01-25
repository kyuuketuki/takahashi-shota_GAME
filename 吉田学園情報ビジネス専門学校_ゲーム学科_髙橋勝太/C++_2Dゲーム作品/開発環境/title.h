//=============================================================================
//
// �^�C�g����ʏ��� [title.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _TITLE_H_
#define _TITLE_H_

//==============================================================================
//�C���N���[�h
//==============================================================================
#include "main.h"
#include "scene.h"
#include "scene2D.h"

//=============================================================================
// �^�C�g���N���X�̒�`
//=============================================================================
class CTitle : public CScene
{
public:
	CTitle();								//�R���X�g���N�^
	~CTitle();								//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY);				//����������
	void Uninit(void);														//�I������
	void Update(void);														//�X�V����
	void Draw(void);														//�`�揈��

	static CTitle *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY);		//��������
};
#endif
