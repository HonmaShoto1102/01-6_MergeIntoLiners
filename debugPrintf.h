#pragma once
#ifndef _DEBUG_PRINTF_H
#define _DEBUG_PRINTF_H

#include<Windows.h>

#include<stdio.h>

#define DEBUG_PRINTF_BUFFER_MAX (256)

inline void DebugPrintf(const char* pFormat, ...) {
	//こんな風に書くとReleaseビルド時はビルドされない範囲を設定できる

#if defined(_DEBUG)||defined(DEBUG)
	va_list argp;
	char buf[256];//バッファは大きめに取りましょう
	va_start(argp, pFormat);
	vsprintf_s(buf, 256, pFormat, argp); //バッファ量と第２引数を合わせること
	va_end(argp);
	OutputDebugString(buf);
#else
	UNREFERENCED_PARAMETER(pFormat);
#endif // defined(_DEBUG)||defined(DEBUG)

}



#endif // !_DEBUG_PRINTF_H
