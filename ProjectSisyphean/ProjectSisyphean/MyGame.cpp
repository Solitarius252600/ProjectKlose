/**
* @file MyGame.cpp
* @brief �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
* @author EtuCho
* @date �쐬��2018_02_01
*/

#include "stdafx.h"
#include "SisypheanApp.h"

//! �O���[�o���ϐ�:
std::unique_ptr<CSisypheanApp> g_pApp = NULL;

/**
* @fn LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
* @brief OS���猩���E�B���h�E�v���V�[�W���[�i���ۂ̏�����MAIN�N���X�̃v���V�[�W���[�ŏ����j
*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

/**
* @fn INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, INT)
* @brief �A�v���P�[�V�����̃G���g���[�֐� 
*/
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, INT)
{
	//! XNA Math���C�u�����̃T�|�[�g �`�F�b�N
	if (XMVerifyCPUSupport() != TRUE)
	{
		MessageBox(0, L"XNA Math���C�u�������T�|�[�g����Ă��Ȃ��B", NULL, MB_OK);
		return 0;
	}

	//! �����^�C������
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
		//! �A�v���I��
		g_pApp->release();
	}
	return 0;
}


//! ����
LRESULT CALLBACK WndProc(HWND hWnd_, UINT uMsg_, WPARAM wParam_, LPARAM lParam_)
{
	return g_pApp->msgProc(hWnd_, uMsg_, wParam_, lParam_);
}