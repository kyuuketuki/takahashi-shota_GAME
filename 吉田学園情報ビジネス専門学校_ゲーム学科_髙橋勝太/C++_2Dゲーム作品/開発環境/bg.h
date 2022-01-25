//=============================================================================
//
// �o�b�N�e�N�X�`������ [bg.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _BG_H_
#define _BG_H_

//=============================================================================
//�C���N���[�h�ǂݍ���
//=============================================================================
#include "main.h"
#include "scene.h"
#include "scene2D.h"

//�}�N����`
#define MAX_BG (3)		//�w�i�̍ő吔

//=============================================================================
// �w�i�N���X�̒�`
//=============================================================================
class CBg : public CScene
{
public:
	CBg(int nPriority = 0);				//�R���X�g���N�^
	~CBg();								//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY);				//����������
	void Uninit(void);														//�I������
	void Update(void);														//�X�V����
	void Draw(void);														//�`�揈��

	static CBg *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY);		//��������
	static HRESULT Load(void);												//�e�N�X�`���ǂݍ���
	static void Unload(void);												//�e�N�X�`���j��
																			
	D3DXVECTOR3 GetPosition(void) { return m_pos; }

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_BG];			// �p�ӂ���e�N�X�`���̐�
	CScene2D *m_apScene2D[MAX_BG];							// �V�[��2D�ւ̃|�C���^
	D3DXVECTOR3 m_pos;										// �ʒu���
	float m_nCntAnime;										// �e�N�X�`�������炷
};

#endif