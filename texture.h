#ifndef TEXTURE_H
#define TEXTURE_H
#include <d3d9.h>
#define TEXTURE_FILENAME_MAX (64) //�e�N�X�`���t�@�C�����ő啶����
#define INVALID_TEXTURE_ID (-1)   //�����ȃe�N�X�`���Ǘ��ԍ�

void Texture_Initialize(void);
void Texture_Finalize(void);

//�e�N�X�`���t�@�C���̓ǂݍ��ݗ\��
int Texture_SetTextureLoadFile(const char* pFileName);

//�e�N�X�`���̓ǂݍ���
//�߂�l�@�ǂݍ��߂Ȃ������t�@�C����
int Texture_Load(void);


//�e�N�X�`���̕������
//�����FtextureIds[] ... ���������textureId��������int�^�z��̐擪�A�h���X
//count     �������e�N�X�`���̐�.
void Texture_Release(int textureIds[], int count);

//�e�N�X�`���̑S���
void Texture_AllRelease(void);

unsigned long Texture_GetTextureWidth(int textureId);
unsigned long Texture_GetTextureHeight(int textureId);
LPDIRECT3DTEXTURE9 Texture_GetTexture(int textureId);

//*************************************loading��ʕ\��**********************************
void LoadingTexture_Init();
void LoadingTexture_Final();
void LoadingTexture_Active(bool active);
void LoadingTexture_SetGoValue(int value);
int LoadingTexture_SetTextureLoadFile(const char* pFileName);
int LoadTexture_Load(void);
void LoadingTexture_AllRelease();
void LoadingTexture_Release(int textureIds[], int count);
LPDIRECT3DTEXTURE9 LoadTexture_GetTexture(int textureId);
void LoadingTexture_SetZeroCount();

#endif // !TEXTURE_H
