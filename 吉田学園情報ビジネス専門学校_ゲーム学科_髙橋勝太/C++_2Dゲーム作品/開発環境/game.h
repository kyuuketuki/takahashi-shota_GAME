//=============================================================================
//
// �Q�[����ʏ��� [game.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _GAME_H_
#define _GAME_H_

//=============================================================================
//�C���N���[�h�ǂݍ���
//=============================================================================
#include "main.h"
#include "scene.h"
#include "scene2D.h"

//=============================================================================
// �Q�[����ʃN���X�̒�`
//=============================================================================
class CGame : public CScene
{
public:
	CGame();									//�R���X�g���N�^
	~CGame();									//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY);	//����������
	void Uninit(void);											//�I������
	void Update(void);											//�X�V����
	void Draw(void);											//�`�揈��

	//�U���Ǘ�
	void Attack(void);											
	void Attack2(void);										
				
	//����Get
	static int GetTime(void);

	//��������
	static CGame *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY);

private:
	LPD3DXFONT	m_pTimeFontGame;					// �\���p�t�H���g
};

#endif