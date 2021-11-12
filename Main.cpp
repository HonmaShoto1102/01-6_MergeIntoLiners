#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>

#include "Main.h"
#include<stdio.h>
#include"debugPrintf.h"
#include"config.h"
#include"myDirect3D.h"
//#include"myD3D.h"
#include"sprite.h"
#include"texture.h"
#include"System_Timer.h"
#include"keyboard.h"
#include"keyloger.h"
#include"sound.h"
//#include"GameManager.h"
#include"GM.h"
#include "loadingScene.h"

#define CLASS_NAME "GameWindow"
#define WINDOW_CAPTION "Merge Into Liners"
#define FPS_MEASUREMENT_TIME (1.0f)


static HWND hWnd;

LRESULT CALLBACK WndPoc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg)
	{
	case WM_ACTIVATEAPP:
	//case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		//Keyboard_ProcessMessage(uMsg, wParam, lParam);
		break;
	case WM_KEYUP:
		Keyboard_ProcessMessage(uMsg, wParam, lParam);
	case WM_SYSKEYUP:
		 //Keyboard_ProcessMessage(uMsg, wParam, lParam);
		 break;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			SendMessage(hwnd, WM_CLOSE, 0, 0);//WM_CLOSE�Ƀ��b�Z�[�W
		}
		Keyboard_ProcessMessage(uMsg, wParam, lParam);
		//DefWindowProc(hwnd, uMsg, wParam, lParam);
		break;
	case WM_CLOSE:
		if (MessageBox(hwnd, "�{���ɏI�����Ă�낵���ł����H", "�m�F", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK) {
			DestroyWindow(hwnd);//�w��̃E�C���h�E��WM_DESTROY���b�Z�[�W���܂�
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);//WM_QUIT���b�Z�[�W���܂�
		return 0;
	default:
		break;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

//�Q�[���̏�����
static bool Initialize(HWND hWnd);
static void Update();
static void Draw();
static void Finalize();

//�O���[�o���ϐ��錾
static int g_FrameCount = 0;                   //�t���[���v��
static int g_FPSBaseFrameCount = 0;
static double g_FPSBaseTime = 0.0;
static double g_StaticFrameTime = 0.0;
static double g_FPS = 0.0f;

//�t���[�����[�N����
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpCmdLine, int nCmdShow) {
	

	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(IpCmdLine);
	

	//int a = 123;
	WNDCLASS wndex;
	ZeroMemory(&wndex, sizeof(wndex));
	wndex.lpfnWndProc = WndPoc;
	wndex.lpszClassName = CLASS_NAME;
	wndex.hInstance = hInstance;
	wndex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndex.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);

	RegisterClass(&wndex);

	const DWORD WINDOW_STYLE = WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX);
	// WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME | WS_MAXIMIZEBOX)

	//�s���̗ǂ��E�C���h�E�T�C�Y���Z�o
	RECT window_rect = {0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
	AdjustWindowRect(&window_rect, WINDOW_STYLE, FALSE);
	
	//���ƍ��������߂�
	int window_width = window_rect.right - window_rect.left;
	int window_height = window_rect.bottom - window_rect.top;

	//�f�X�N�g�b�v�̃T�C�Y���擾
	//RECT desktop_rect;
	//GetWindowRect(GetDesktopWindow(), &desktop_rect);
	//int desktop_width = desktop_rect.right - desktop_rect.left;
	//int desktop_height = desktop_rect.bottom - desktop_rect.top;

	int desktop_width = GetSystemMetrics(SM_CXSCREEN);
	int desktop_height = GetSystemMetrics(SM_CYSCREEN);



	//���z��ʂ̉𑜓x�擾
	//int virtual_desktop_with = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	//int virtual_desktop_height = GetSystemMetrics(SM_CYVIRTUALSCREEN);

	//���z��ʂ̍�����W�擾
	//int virtual_desktop_with = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	//int virtual_desktop_height = GetSystemMetrics(SM_CYVIRTUALSCREEN);

	//�E�C���h�E�̐���
	hWnd = CreateWindow(
		CLASS_NAME,				//�E�C���h�E�@�N���X
		WINDOW_CAPTION,			//�E�C���h�E�@�e�L�X�g
		WINDOW_STYLE,    //�E�C���h�E�@�X�^�C��
		//�T�C�Y�ƈʒu
		max((desktop_width-window_width)/2,0), max((desktop_height-window_height)/2,0), window_width, window_height,

		NULL,                   //�e�E�C���h�E�n���h��
		NULL,                   //���j���[�n���h��
		hInstance,				//�C���X�^���X�n���h��
		NULL					//�ǉ��̃A�v���P�[�V�����f�[�^
	);

	if (hWnd == NULL) {
		return 0;
	}

	ShowWindow(hWnd, nCmdShow);

	SystemTimer_Initialize();
	SystemTimer_Start();
	
	g_FrameCount = g_FPSBaseFrameCount = 0;
	g_FPSBaseTime = SystemTimer_GetTime();
	g_FPS = 0.0f;

	g_StaticFrameTime = g_FPSBaseTime;

	MSG msg = {}; 

	if (!Initialize(hWnd)) {
		MessageBox(NULL, "���s����������", "errror", MB_OK);
		return 0;
	}

	

	while (WM_QUIT!=msg.message) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			double time = SystemTimer_GetTime();
			if ((time - g_StaticFrameTime) < 1.0f / 60.f) {
				Sleep(0);
			}
			else
			{
				g_StaticFrameTime = time;
				g_FrameCount++;
				//double time = SystemTimer_GetTime();
				if (time - g_FPSBaseTime >= FPS_MEASUREMENT_TIME) {
					g_FPS = (float)((g_FrameCount - g_FPSBaseFrameCount) / (float)(time - g_FPSBaseTime));
					g_FPSBaseTime = time;
					g_FPSBaseFrameCount = g_FrameCount;
				}

				
				//�Q�[������
				Update();
				
				
				
				//FpsDraw_(g_FPS, 0, 0, 3);
				Draw();
				//LoadingScene_Draw();
				
			}		
			
		}
		
	}
	Finalize();
	return (int)msg.wParam;
}

void LoadingSceneUpdate() {
	/*MSG msg = {};
	while (WM_QUIT != msg.message) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{*/

			MyDirect3D_GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);
			//MyDirect3D_GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(100, 80, 200, 255), 1.0f, 0);
			//�`��o�b�`���߂̊J�n
			MyDirect3D_GetDevice()->BeginScene();


			LoadingScene_Draw();

			MyDirect3D_GetDevice()->EndScene();
			//�o�b�N�o�b�t�@���t���b�v�i�^�C�~���O��D3DPRESENT_PARAMETERS�̐ݒ�ɂ���
			MyDirect3D_GetDevice()->Present(NULL, NULL, NULL, NULL);
			return;
		//}
		//if (LoadingScene_Getflag())return;
	//}
	//Finalize();
}



bool Initialize(HWND hWnd) {

	Keyboard_Initialize();
	Keylogger_Initialize();
	//Direct3D�̏�����
	if (!MyDirect3D_Initialize(hWnd)) {
		MessageBox(NULL, "Direct3D�̏������Ɏ��s����", "�G���[", MB_OK);
		return false;
	}

	InitSound(hWnd);
	//�e�N�X�`���̂��傫��
	Texture_Initialize();

	//sprite������
	Spirte_Initialize();

	//FpsDraw_Initialize();
	//if (!gm.Init()) {
	//	MessageBox(NULL, "game�̏������Ɏ��s����", "�G���[", MB_OK);
	//	return false;
	//}

	//gm()->Init();
	//gm()->Scene_Rejest();

	GM_Init();

	 return true;
}
 void Update() {
	 
	 Keylogger_Update();
	 //gm()->Update();
	 
	// double time = SystemTimer_GetTime();
	// if (time - g_BaseTime > 1.0f) {
	//	 g_FPS = (g_FrameCount - g_BaseFrame) / (time - g_BaseTime);
	// }
	 GM_Update();
 }
 void Draw() {
	 //��ʃN���A       //�����N���A
	 MyDirect3D_GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);
	 //MyDirect3D_GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(100, 80, 200, 255), 1.0f, 0);
	 //�`��o�b�`���߂̊J�n
	 MyDirect3D_GetDevice()->BeginScene();

	 //gm()->Draw();
	 GM_DrawLayer();
	 GM_Draw();
	
	 //�`��o�b�`���߂̏I��
	 MyDirect3D_GetDevice()->EndScene();
	 //�o�b�N�o�b�t�@���t���b�v�i�^�C�~���O��D3DPRESENT_PARAMETERS�̐ݒ�ɂ���
	 MyDirect3D_GetDevice()->Present(NULL, NULL, NULL, NULL);
 }
 //�Q�[���I������
 void Finalize() {
	 //gm()->Final();

	 GM_Final();

	 UninitSound();

	 Sprite_Finalaize();

	 Texture_Finalize();

	 MyDirect3D_Finalize();

	 Keylogger_Finalize();
 }

 
