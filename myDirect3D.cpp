#include "myDirect3D.h"

static LPDIRECT3D9 g_pD3D = NULL;        //Direct3Dインターフェース
static LPDIRECT3DDEVICE9 g_pDevice = NULL;//Direct3Dデイバスインターフェース
bool MyDirect3D_Initialize(HWND hWnd)
{
	//Direct3Dインターフェースの取得
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL) {
		MessageBox(NULL, "Direct3Dインターフェースの作成に失敗した", "error", MB_OK);
		return false;
	}
	//Direct3Dデイバスの取得
	//デバイスの取得に必要な情報構造体の作成
	D3DPRESENT_PARAMETERS d3dpp = {};
	d3dpp.BackBufferWidth = SCREEN_WIDTH; //バックバッファの横幅
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;//バックバッファの縦幅
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;//スワップ方法の設定
	d3dpp.Windowed = TRUE;      //ウインドウ　OR　フルスクリーン
	d3dpp.EnableAutoDepthStencil = TRUE; //深度バッファ。ステンシルバッファの使用
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//フルスクリーン時のリフレッシュレートの指定
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;//リフレッシュレートとPrensent処理の関係

	HRESULT hr;

	hr = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &g_pDevice);
	if (FAILED(hr)) {
		MessageBox(NULL, "Direct3Dデイバスの取得に失敗した", "Errra", MB_OK);
		return false;

	}

	

	g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);//CLAMP,,BORDER,,WRAP,MIRROR
	g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	g_pDevice->SetSamplerState(0, D3DSAMP_BORDERCOLOR, D3DCOLOR_RGBA(255, 120, 120, 255));

	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);//alpha設定

	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);//色を取るが頂点カラー影響を排除

   // g_pDevice->SetTextureStageState(0, D3DTSS_COLORARG0, D3DTA_CURRENT);
   // g_pDevice->SetTextureStageState(0,D3DTSS_COLORARG1,D3DTA_)

	return true;
}

void MyDirect3D_Finalize(void)
{
	if (g_pDevice) {
		g_pDevice->Release();
		g_pDevice = NULL;
	}

	if (g_pD3D) {
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

LPDIRECT3DDEVICE9 MyDirect3D_GetDevice(void)
{
	return g_pDevice;
}
