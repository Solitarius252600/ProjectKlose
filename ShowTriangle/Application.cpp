/**
* @file Application.cpp
* @brief アプリケーションのエントリ ポイントを定義
* @author EtuCho
* @date 2019/04/14
* @details
*/
#include "MyApp.h"


/**
* @fn int WINAPI WinMain(
HINSTANCE hInstance,
HINSTANCE hPrevInstance,
LPSTR lpCmdLine,
int nCmdShow)
* @brief アプリケーションエントリーポイント
*/

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	::HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);
	if (SUCCEEDED(::CoInitialize(NULL)))
	{
		{
			MyApp app;
			if (SUCCEEDED(app.Initialize(hInstance, nCmdShow)))
			{
				app.RunMessageLoop();
			}
		}
		::CoUninitialize();
	}

	return 0;
}