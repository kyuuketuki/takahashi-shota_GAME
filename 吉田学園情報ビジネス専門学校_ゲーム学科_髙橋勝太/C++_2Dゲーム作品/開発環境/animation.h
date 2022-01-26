//=============================================================================
//
// �A�j���[�V�������� [animasion.h]
// Author : takahashi shota
//
//=============================================================================

#ifndef _ANIMASION_H_
#define _ANIMASION_H_

//=============================================================================
//�C���N���[�h�ǂݍ���
//=============================================================================
#include "main.h"
#include "scene2D.h"

//�}�N����`
#define MAX_ANIME (18)

//=============================================================================
// �A�j���[�V�����N���X�̒�`
//=============================================================================
class CAnimasion : public CScene2D
{
public:
	CAnimasion(int nPriority = 3, int nType = 0);			//�R���X�g���N�^
	virtual ~CAnimasion();									//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nAnime, int nType);	//����������
	void Uninit(void);																	//�I������
	void Update(void);																	//�X�V����
	void Draw(void);																	//�`�揈��

	//��������
	static CAnimasion *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nAnime, int nType);

	//�e�N�X�`���̓ǂݍ��݁�����
	static HRESULT Load(void);
	static void Unload(void);

	//�e�N�X�`�����̊Ǘ�
	void Texture(int nType);

	//�^�C�v�ʂŏ���
	static void UninitType(int nUninitType);
	static void UninitTypeClear(void);

protected:
	D3DXVECTOR3 m_pos;									//�ړ���
	int m_nType;										//�^�C�v�@�e�N�X�`������
	int m_nTypeBuulet;									//����ړ����Ɏg�p
	int m_nCounterAnime;								//�A�j���[�V�����J�E���^�[
	int m_nPatternAnime;								//�A�j���[�V�����p�^�[��
	int m_fCriss;										//���[�v����
	int m_nX;											//�摜����
	int m_nY;											//�摜����
	int m_nAnime;										//�A�j���[�V�����X�s�[�h
	float m_fAnimeX;									//�摜����X
	float m_fAnimeY;									//�摜����Y
	float m_fColorFa = 1.0f;							//�A���t�@�l

	//�ÓI�����o�ϐ�
	static LPDIRECT3DTEXTURE9 m_pTexture[MAX_ANIME];	//�e�N�X�`���̃|�C���^
};

//=============================================================================
// �A�j���[�V�����N���X�̒�`(�w�i)
//=============================================================================
class CAnimasionBg : public CAnimasion
{
public:
	CAnimasionBg(int nPriority = 1, int nType = 0);		//�R���X�g���N�^
	virtual ~CAnimasionBg();							//�f�X�g���N�^

	HRESULT Init(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nAnime, int nType);					   //����������
	void Uninit(void);																					   //�I������
	void Update(void);																					   //�X�V����
	void Draw(void);																					   //�`�揈��

	static CAnimasionBg *Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY, int nAnime, int nType);	   //��������
	static void UninitTypeClear(void);																	   //�r���j��
};

#endif