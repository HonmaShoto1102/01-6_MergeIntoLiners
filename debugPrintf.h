#pragma once
#ifndef _DEBUG_PRINTF_H
#define _DEBUG_PRINTF_H

#include<Windows.h>

#include<stdio.h>

#define DEBUG_PRINTF_BUFFER_MAX (256)

inline void DebugPrintf(const char* pFormat, ...) {
	//����ȕ��ɏ�����Release�r���h���̓r���h����Ȃ��͈͂�ݒ�ł���

#if defined(_DEBUG)||defined(DEBUG)
	va_list argp;
	char buf[256];//�o�b�t�@�͑傫�߂Ɏ��܂��傤
	va_start(argp, pFormat);
	vsprintf_s(buf, 256, pFormat, argp); //�o�b�t�@�ʂƑ�Q���������킹�邱��
	va_end(argp);
	OutputDebugString(buf);
#else
	UNREFERENCED_PARAMETER(pFormat);
#endif // defined(_DEBUG)||defined(DEBUG)

}



#endif // !_DEBUG_PRINTF_H
