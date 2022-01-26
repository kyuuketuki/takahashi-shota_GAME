//=============================================================================
//
// ���U���g��ʏ��� [game2.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _RESULT_H_
#define _RESULT_H_

//==============================================================================
//�C���N���[�h
//==============================================================================
#include "main.h"
#include "scene.h"
#include "scene2D.h"
#include "player.h"

//=============================================================================
// ���U���g��ʃN���X�̒�`
//=============================================================================
class CResult : public CScene
{
public:
	CResult();									//�R���X�g���N�^
	~CResult();									//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY);		//����������
	void Uninit(void);												//�I������
	void Update(void);												//�X�V����
	void Draw(void);												//�`�揈��

	static CResult *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY);	//��������

private:
	static CPlayer				*m_pPlayer;			//�v���C���[�ւ̃|�C���^	�z�[�~���O���Ɏg�p
	LPD3DXFONT					m_pTimeFontGame;	// �\���p�t�H���g
};

#endif