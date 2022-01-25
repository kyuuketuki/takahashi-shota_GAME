//=============================================================================
//
// �������� [map.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _MAP_H_
#define _MAP_H_

#include "main.h"
#include "scene3D.h"

//=============================================================================
// �}�b�v�N���X�̒�`
//=============================================================================

//�p����`��N���X
class CMap : public CScene3D
{
public:
	CMap();									//�R���X�g���N�^
	virtual ~CMap();						//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY);							//����������
	void Uninit(void);																	//�I������
	void Update(void);																	//�X�V����
	void Draw(void);																	//�`�揈��

	static CMap *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY);				//��������
	static HRESULT Load(void);															//�e�N�X�`���ǂݍ���
	static void Unload(void);															//�e�N�X�`���j��

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;	//�e�N�X�`���̃|�C���^
	int m_nCounterAnime;					//�A�j���[�V�����J�E���^�[
	int m_nPatternAnime;					//�A�j���[�V�����p�^�[��
};

#endif