/**
* @file DirectInput.h
* @brief �_�C���N�g�C���v�b�g�̃N���X�w�b�_�[
* @author EtuCho
* @date �쐬��2018_02_04
* @details �V���O���g���p�^�[���Ŏ���,���̓f�o�C�X�}�E�X�ǉ��K�v
*/
#pragma once
#include "stdafx.h"
#include "CommonType.h"


//! �萔
#define KEY_PRESSED			0x80
#define IS_KEY_PRESSED(x)	(x & KEY_PRESSED)
#define BUFFER_SIZE			256

class CDirectInput
{
	// Properties
	static std::shared_ptr<CDirectInput>	m_instance;
	LPDIRECTINPUT8			m_pDinput;		//! DirectInput �I�u�W�F�N�g
	LPDIRECTINPUTDEVICE8	m_pKeyDevice;	//! �L�[�{�[�h				
	LPDIRECTINPUTDEVICE8	m_pMouseDevice;	//! �}�E�X					

	BYTE m_keyboardInput[BUFFER_SIZE];		//! �L�[�{�[�h�̓��͏��	
	BYTE m_keyboardInputPrev[BUFFER_SIZE];	//! �O��̃L�[�{�[�h�̓��͏��

	BOOL m_pressed[BUFFER_SIZE];
	BOOL m_pressedOnce[BUFFER_SIZE];
	DIMOUSESTATE2	m_mouseInput;			//! �}�E�X�̓��͏��	
	DIMOUSESTATE2	m_mouseInputPrev;		//! �O��̃}�E�X�̓��͏��

	// Methids
	CDirectInput();							//! �y�V���O���g���E�p�^�[���z
	HRESULT init(HWND inHWnd);
	VOID free();
public:
	~CDirectInput();
	// Methids
	static std::shared_ptr<CDirectInput> getInstance(HWND inHWnd);	//! �C���X�^���X���擾
	static VOID releaseInstance();					//! �C���X�^���X�����

	HRESULT getState();

	BOOL isKeyPressed(BYTE aKey);
	BOOL isPressedOnce(BYTE aKey);
	BOOL isKeyTrigger(BYTE aKey);
	BOOL isKeyReleased(BYTE aKey);
};

