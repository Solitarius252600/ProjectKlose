/**
* @file Common.h
* @brief 標準のシステム インクルード ファイルのインクルード ファイル、または参照回数が多く、
*		 かつあまり変更されない、プロジェクト共通で使うインクルード ファイルを記述します。
* @author EtuCho
* @date 2019/04/14
* @details
*/

#pragma once
#ifndef INCLUDE_COMMON
#define INCLUDE_COMMON

#define  _WIN32_WINNT   0x0A00

#include <stdio.h>
#include <windows.h>
#include <string>
#include <memory>

#include <d3d11_1.h>
#include <directxcolors.h>
#include <d3dcompiler.h>
#include <directxmath.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "Xinput9_1_0.lib")

using namespace std;
using namespace DirectX;

//! 定数
// 16:9	1080 × 640(HD)(ウィンドモード)
#define WINDOW_WIDTH					1080//! ウィンドウ幅
#define WINDOW_HEIGHT					640//! ウィンドウ高さ


/**
* @fn void SafeRelease(Interface **ppInterfaceToRelease)
* @brief セーフリリース
* @param[tmp] *&pInterfaceToRelease 解放するテンプレートクラス（ポインタ）
* @details 安全に解放するテンプレート関数
*/
template<class Interface>
inline void SafeRelease(
	Interface **ppInterfaceToRelease
)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();

		(*ppInterfaceToRelease) = NULL;
	}
}

#endif
