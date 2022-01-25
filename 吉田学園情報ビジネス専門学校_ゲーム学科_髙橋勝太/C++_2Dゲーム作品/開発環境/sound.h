//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : takahashi syota
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

//==============================================================================
//�C���N���[�h
//==============================================================================
#include "main.h"
#include "renderer.h"

//=============================================================================
// �T�E���h�t�@�C��
//=============================================================================
typedef enum
{
	SOUND_LABEL_BGM000 = 0,		// BGM0
	SOUND_LABEL_BGM001,			// BGM1
	SOUND_LABEL_BGM002,			// BGM2
	SOUND_LABEL_BGM003,			// BGM3
	SOUND_LABEL_BGM004,			// BGM4
	SOUND_LABEL_SE_SHOT,		// �e���ˉ�
	SOUND_LABEL_SE_HIT,			// �q�b�g��
	SOUND_LABEL_SE_EXPLOSION,	// ������
	SOUND_LABEL_SE_MIGRATION,	// �ړ���
	SOUND_LABEL_SE_DECISION,	// ���艹
	SOUND_LABEL_SE_STER,		// ����
	SOUND_LABEL_SE_METEOR,		// ������
	SOUND_LABEL_SE_RECOVER,		// �񕜉�
	SOUND_LABEL_MAX,
} SOUND_LABEL;

//=============================================================================
// �T�E���h�N���X�̓K�X
//=============================================================================
class CSound
{
public:
	CSound();								//�R���X�g���N�^
	virtual ~CSound();						//�f�X�g���N�^

	typedef enum
	{
		SOUND_LABEL_BGM000 = 0,		// BGM0
		SOUND_LABEL_BGM001,			// BGM1
		SOUND_LABEL_BGM002,			// BGM2
		SOUND_LABEL_BGM003,			// BGM3
		SOUND_LABEL_BGM004,			// BGM4
		SOUND_LABEL_SE_SHOT,		// �e���ˉ�
		SOUND_LABEL_SE_HIT,			// �q�b�g��
		SOUND_LABEL_SE_EXPLOSION,	// ������
		SOUND_LABEL_SE_MIGRATION,	// �ړ���
		SOUND_LABEL_SE_DECISION,	// ���艹
		SOUND_LABEL_SE_STER,		// ����
		SOUND_LABEL_SE_METEOR,		// ������
		SOUND_LABEL_SE_RECOVER,		// �񕜉�
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	HRESULT Init(HWND hWnd);
	void	Uninit(void);
	HRESULT Play(SOUND_LABEL label);
	void	Stop(SOUND_LABEL label);

private:
	//�p�����[�^�\���̒�`
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���g
	} SOUNDPARAM;

	HRESULT ChekChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunk(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);
	
	IXAudio2 *m_pXAudio2 = NULL;
	IXAudio2MasteringVoice *m_pMasteringVoice = NULL;			// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^�T�C�Y

	// �e���f�ނ̃p�����[�^
	SOUNDPARAM m_aParam[SOUND_LABEL_MAX] =
	{
		{ "data/BGM/bgm000.wav", -1 },						// BGM0
		{ "data/BGM/bgm001.wav", -1 },						// BGM1
		{ "data/BGM/bgm002.wav", -1 },						// BGM2
		{ "data/BGM/BGM_01_���������ꂾ���̕���.wav", -1 },	// BGM3
		{ "data/BGM/BGM_02_��Ԃ�˂�����.wav", -1 },		// BGM4
		{ "data/SE/shot000.wav", 0 },						// �e���ˉ�
		{ "data/SE/hit000.wav", 0 },						// �q�b�g��
		{ "data/SE/explosion000.wav", 0 },					// ������
		{ "data/SE/migration.wav", 0 },						// �ړ���
		{ "data/SE/decision.wav", 0 },						// ���艹
		{ "data/SE/ster.wav", 0 },							// ����
		{ "data/SE/meteor.wav", 0 },						// ������
		{ "data/SE/recovery.wav", 0 },						// �񕜉�
	};
};

#endif