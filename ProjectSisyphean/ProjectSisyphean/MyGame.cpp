/**
* @file MyGame.cpp
* @brief アプリケーションのエントリ ポイントを定義します。
* @author EtuCho
* @date 作成日2018_02_01
*/

#include "stdafx.h"
#include "SisypheanApp.h"

//! グローバル変数:
std::unique_ptr<CSisypheanApp> g_pApp = NULL;

/**
* @fn LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
* @brief OSから見たウィンドウプロシージャー（実際の処理はMAINクラスのプロシージャーで処理）
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/**
* @fn INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, INT)
* @brief アプリケーションのエントリー関数 
*/
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, INT)
{
	//! XNA Mathライブラリのサポート チェック
	if (XMVerifyCPUSupport() != TRUE)
	{
		MessageBox(0, L"XNA Mathライブラリがサポートされていない。", NULL, MB_OK);
		return 0;
	}

	//! 乱数タイム生成
	srand((unsigned int)time(NULL));

	g_pApp = unique_ptr<CSisypheanApp>(new CSisypheanApp());
	if (g_pApp != NULL)
	{
		if (SUCCEEDED(g_pApp->initWindow(hInstance, WndProc, 0, 0, WINDOW_WIDTH,
			WINDOW_HEIGHT, APP_NAME)))
		{
			if (SUCCEEDED(g_pApp->initD3D()))
			{
				g_pApp->loop();
			}
		}
		//! アプリ終了
		g_pApp->release();
	}
	return 0;
}


//! 実装
LRESULT CALLBACK WndProc(HWND hWnd_, UINT uMsg_, WPARAM wParam_, LPARAM lParam_)
{
	return g_pApp->msgProc(hWnd_, uMsg_, wParam_, lParam_);
}