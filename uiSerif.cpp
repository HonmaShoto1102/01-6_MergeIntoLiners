/*---------------------------------------------------------------------------*/
//  FILE : uiSerif.cpp
//
//         　　　　　　吹き出しとセリフの演出
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


// グローバル変数は、このように「namespace + (好きな名前)」の中に定義して
// 自分だけが使えるようにカプセル化します。
// (自分なりのスタイルに合わせた組み方を自由に行えます)
namespace Serif
{
}


LPD3DXFONT myD3DFont;

//LPD3DXFONT myD3DFont = myD3DDevice;	//フォントのインターフェース	// フォントオブジェクト




void UiSerif_Load(void)
{

}
bool UiSerif_Init(void)
{
	LPDIRECT3DDEVICE9 g_pDevice = MyDirect3D_GetDevice();	//	MyDirect3Dから持ってくる
	myD3DFont = NULL;

	//HRESULT	hr;

	if (FAILED(D3DXCreateFont(
		g_pDevice,                /* デバイス */
		40,                            /* 文字の高さ */
		32,                            /* 文字幅 */
		FW_NORMAL,                    /* フォントの太さ */
		1,                            /* MIPMAPのレベル */
		FALSE,                        /* イタリックか？ */
		DEFAULT_CHARSET,            /* 文字セット */
		OUT_DEFAULT_PRECIS,            /* 出力精度 */
		DEFAULT_QUALITY,            /* 出力品質 */
		DEFAULT_PITCH | FF_SWISS,    /* フォントピッチとファミリ */
		"メイリオ",                    /* フォント名 */
		&myD3DFont)))
	{
		return false;

	}


	D3DXFONT_DESC logFont;
	/*logFont.Height = 30;
	logFont.Width = 22;
	logFont.Weight = FW_NORMAL;
	logFont.MipLevels = 0;
	logFont.Italic = FALSE;								//文字斜めにするかどうか
	logFont.CharSet = SHIFTJIS_CHARSET;					//文字コード
	logFont.OutputPrecision = OUT_TT_ONLY_PRECIS;			//出力制度
	logFont.Quality = DEFAULT_QUALITY;						//出力品質
	logFont.PitchAndFamily = DEFAULT_PITCH || FF_DONTCARE;	//FIXED_PITCH | FF_MODERN
	//strcpy(logFont.FaceName, "ＭＳ ゴシック");				//使用するフォント
	lstrcpy(logFont.FaceName, "メイリオ");				//使用するフォント*/


	D3DXCreateFontIndirect(g_pDevice, &logFont, &myD3DFont);


	return true;
}
void UiSerif_Update(void)
{
	int cnt = 0;
	char d[64];	//	"文字:"	と	%d	分必要
	sprintf(d, "Score：%d", cnt);

	RECT rect = { 1100,30,50,50 };	//	座標 起点X 起点Y 高さ 幅
	myD3DFont->DrawTextA(			//	DrawTextA
		NULL,						//	NULL
		d,							//	文字	""でも可能
		-1, &rect,					//	-1
		DT_LEFT | DT_NOCLIP,		//	座標 文字をどっちに寄せるか
		D3DCOLOR_RGBA(255, 5, 5, 255)); //	色

	//myD3DFont->DrawText(NULL, "表示したい文字列", -1, &rect, DT_LEFT | DT_NOCLIP, D3DCOLOR_ARGB(255, 255, 255, 255));


}

void UiSerif_Unload(void)
{
	myD3DFont->Release();	//	解放必須
}