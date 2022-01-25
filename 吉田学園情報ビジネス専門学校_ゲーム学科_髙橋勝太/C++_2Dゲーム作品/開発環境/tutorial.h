//=============================================================================
//
// �`���[�g���A����ʏ��� [tutorial.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

//==============================================================================
//�C���N���[�h
//==============================================================================
#include "main.h"
#include "scene.h"
#include "scene2D.h"
#include "player.h"

//=============================================================================
// �`���[�g���A����ʃN���X�̒�`
//=============================================================================
class CTutorial : public CScene
{
public:
	CTutorial();									//�R���X�g���N�^
	~CTutorial();									//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY);			//����������
	void Uninit(void);													//�I������
	void Update(void);													//�X�V����
	void Draw(void);													//�`�揈��

	//��������
	static CTutorial *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY);

private:
	static CPlayer				*m_pPlayer;			//�v���C���[�ւ̃|�C���^	�z�[�~���O���Ɏg�p
	LPD3DXFONT					m_pTimeFontGame;	// �\���p�t�H���g
};

#endif