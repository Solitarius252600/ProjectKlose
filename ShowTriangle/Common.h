/**
* @file Common.h
* @brief �W���̃V�X�e�� �C���N���[�h �t�@�C���̃C���N���[�h �t�@�C���A�܂��͎Q�Ɖ񐔂������A
*		 �����܂�ύX����Ȃ��A�v���W�F�N�g���ʂŎg���C���N���[�h �t�@�C�����L�q���܂��B
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

//! �萔
// 16:9	1080 �~ 640(HD)(�E�B���h���[�h)
#define WINDOW_WIDTH					1080//! �E�B���h�E��
#define WINDOW_HEIGHT					640//! �E�B���h�E����


/**
* @fn void SafeRelease(Interface **ppInterfaceToRelease)
* @brief �Z�[�t�����[�X
* @param[tmp] *&pInterfaceToRelease �������e���v���[�g�N���X�i�|�C���^�j
* @details ���S�ɉ������e���v���[�g�֐�
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
