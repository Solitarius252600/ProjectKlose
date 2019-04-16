/**
* @file DirectInput.h
* @brief ダイレクトインプットのクラスヘッダー
* @author EtuCho
* @date 作成日2018_02_04
* @details シングルトンパターンで実装,入力デバイスマウス追加必要
*/
#pragma once
#include "stdafx.h"
#include "CommonType.h"


//! 定数
#define KEY_PRESSED			0x80
#define IS_KEY_PRESSED(x)	(x & KEY_PRESSED)
#define BUFFER_SIZE			256

class CDirectInput
{
	// Properties
	static std::shared_ptr<CDirectInput>	m_instance;
	LPDIRECTINPUT8			m_pDinput;		//! DirectInput オブジェクト
	LPDIRECTINPUTDEVICE8	m_pKeyDevice;	//! キーボード				
	LPDIRECTINPUTDEVICE8	m_pMouseDevice;	//! マウス					

	BYTE m_keyboardInput[BUFFER_SIZE];		//! キーボードの入力情報	
	BYTE m_keyboardInputPrev[BUFFER_SIZE];	//! 前回のキーボードの入力情報

	BOOL m_pressed[BUFFER_SIZE];
	BOOL m_pressedOnce[BUFFER_SIZE];
	DIMOUSESTATE2	m_mouseInput;			//! マウスの入力情報	
	DIMOUSESTATE2	m_mouseInputPrev;		//! 前回のマウスの入力情報

	// Methids
	CDirectInput();							//! 【シングルトン・パターン】
	HRESULT init(HWND inHWnd);
	VOID free();
public:
	~CDirectInput();
	// Methids
	static std::shared_ptr<CDirectInput> getInstance(HWND inHWnd);	//! インスタンスを取得
	static VOID releaseInstance();					//! インスタンスを解放

	HRESULT getState();

	BOOL isKeyPressed(BYTE aKey);
	BOOL isPressedOnce(BYTE aKey);
	BOOL isKeyTrigger(BYTE aKey);
	BOOL isKeyReleased(BYTE aKey);
};

