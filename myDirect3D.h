#pragma once
#ifndef MY_DIRECT3D_H
#define MY_DIRECT3D_H

#include<Windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include"config.h"


//Direct3D�֘A�̏�����
bool MyDirect3D_Initialize(HWND hwnd);


//Direct3D�֘A�̏I������
void MyDirect3D_Finalize(void);


//Direct3D�f�C�o�X�̎擾
LPDIRECT3DDEVICE9 MyDirect3D_GetDevice(void);

#endif // !MY_DIRECT3D_H
