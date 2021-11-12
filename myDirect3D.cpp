#include "myDirect3D.h"

static LPDIRECT3D9 g_pD3D = NULL;        //Direct3D�C���^�[�t�F�[�X
static LPDIRECT3DDEVICE9 g_pDevice = NULL;//Direct3D�f�C�o�X�C���^�[�t�F�[�X
bool MyDirect3D_Initialize(HWND hWnd)
{
	//Direct3D�C���^�[�t�F�[�X�̎擾
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL) {
		MessageBox(NULL, "Direct3D�C���^�[�t�F�[�X�̍쐬�Ɏ��s����", "error", MB_OK);
		return false;
	}
	//Direct3D�f�C�o�X�̎擾
	//�f�o�C�X�̎擾�ɕK�v�ȏ��\���̂̍쐬
	D3DPRESENT_PARAMETERS d3dpp = {};
	d3dpp.BackBufferWidth = SCREEN_WIDTH; //�o�b�N�o�b�t�@�̉���
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;//�o�b�N�o�b�t�@�̏c��
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;//�X���b�v���@�̐ݒ�
	d3dpp.Windowed = TRUE;      //�E�C���h�E�@OR�@�t���X�N���[��
	d3dpp.EnableAutoDepthStencil = TRUE; //�[�x�o�b�t�@�B�X�e���V���o�b�t�@�̎g�p
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//�t���X�N���[�����̃��t���b�V�����[�g�̎w��
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;//���t���b�V�����[�g��Prensent�����̊֌W

	HRESULT hr;

	hr = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &g_pDevice);
	if (FAILED(hr)) {
		MessageBox(NULL, "Direct3D�f�C�o�X�̎擾�Ɏ��s����", "Errra", MB_OK);
		return false;

	}

	

	g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);//CLAMP,,BORDER,,WRAP,MIRROR
	g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	g_pDevice->SetSamplerState(0, D3DSAMP_BORDERCOLOR, D3DCOLOR_RGBA(255, 120, 120, 255));

	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);//alpha�ݒ�

	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);//�F����邪���_�J���[�e����r��

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
