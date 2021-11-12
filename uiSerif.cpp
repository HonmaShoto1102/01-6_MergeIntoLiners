/*---------------------------------------------------------------------------*/
//  FILE : uiSerif.cpp
//
//         �@�@�@�@�@�@�����o���ƃZ���t�̉��o
//
/*===========================================================================*/
//
//                                                          Author : Honma Shoto
/*---------------------------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include <d3dx9.h>
#include "uiSerif.h"
#include "base_Sprite.h"
#include "myDirect3D.h"
#include <stdio.h>


// �O���[�o���ϐ��́A���̂悤�Ɂunamespace + (�D���Ȗ��O)�v�̒��ɒ�`����
// �����������g����悤�ɃJ�v�Z�������܂��B
// (�����Ȃ�̃X�^�C���ɍ��킹���g�ݕ������R�ɍs���܂�)
namespace Serif
{
}


LPD3DXFONT myD3DFont;

//LPD3DXFONT myD3DFont = myD3DDevice;	//�t�H���g�̃C���^�[�t�F�[�X	// �t�H���g�I�u�W�F�N�g




void UiSerif_Load(void)
{

}
bool UiSerif_Init(void)
{
	LPDIRECT3DDEVICE9 g_pDevice = MyDirect3D_GetDevice();	//	MyDirect3D���玝���Ă���
	myD3DFont = NULL;

	//HRESULT	hr;

	if (FAILED(D3DXCreateFont(
		g_pDevice,                /* �f�o�C�X */
		40,                            /* �����̍��� */
		32,                            /* ������ */
		FW_NORMAL,                    /* �t�H���g�̑��� */
		1,                            /* MIPMAP�̃��x�� */
		FALSE,                        /* �C�^���b�N���H */
		DEFAULT_CHARSET,            /* �����Z�b�g */
		OUT_DEFAULT_PRECIS,            /* �o�͐��x */
		DEFAULT_QUALITY,            /* �o�͕i�� */
		DEFAULT_PITCH | FF_SWISS,    /* �t�H���g�s�b�`�ƃt�@�~�� */
		"���C���I",                    /* �t�H���g�� */
		&myD3DFont)))
	{
		return false;

	}


	D3DXFONT_DESC logFont;
	/*logFont.Height = 30;
	logFont.Width = 22;
	logFont.Weight = FW_NORMAL;
	logFont.MipLevels = 0;
	logFont.Italic = FALSE;								//�����΂߂ɂ��邩�ǂ���
	logFont.CharSet = SHIFTJIS_CHARSET;					//�����R�[�h
	logFont.OutputPrecision = OUT_TT_ONLY_PRECIS;			//�o�͐��x
	logFont.Quality = DEFAULT_QUALITY;						//�o�͕i��
	logFont.PitchAndFamily = DEFAULT_PITCH || FF_DONTCARE;	//FIXED_PITCH | FF_MODERN
	//strcpy(logFont.FaceName, "�l�r �S�V�b�N");				//�g�p����t�H���g
	lstrcpy(logFont.FaceName, "���C���I");				//�g�p����t�H���g*/


	D3DXCreateFontIndirect(g_pDevice, &logFont, &myD3DFont);


	return true;
}
void UiSerif_Update(void)
{
	int cnt = 0;
	char d[64];	//	"����:"	��	%d	���K�v
	sprintf(d, "Score�F%d", cnt);

	RECT rect = { 1100,30,50,50 };	//	���W �N�_X �N�_Y ���� ��
	myD3DFont->DrawTextA(			//	DrawTextA
		NULL,						//	NULL
		d,							//	����	""�ł��\
		-1, &rect,					//	-1
		DT_LEFT | DT_NOCLIP,		//	���W �������ǂ����Ɋ񂹂邩
		D3DCOLOR_RGBA(255, 5, 5, 255)); //	�F

	//myD3DFont->DrawText(NULL, "�\��������������", -1, &rect, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));


}

void UiSerif_Unload(void)
{
	myD3DFont->Release();	//	����K�{
}