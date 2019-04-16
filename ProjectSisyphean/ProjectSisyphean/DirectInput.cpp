/**
* @file DirectInput.cpp
* @brief ダイレクトインプット実装ファイル
* @author EtuCho
* @date 作成日2018_02_04
* @details シングルトンパターンで実装,入力デバイスマウス追加必要
*/

#include "stdafx.h"
#include "DirectInput.h"

//! クラス変数
std::shared_ptr<CDirectInput> CDirectInput::m_instance = NULL;

/****************************************************************
//! Private  Methods
*****************************************************************/
CDirectInput::CDirectInput()
{
}

CDirectInput::~CDirectInput()
{
}

/**
* @fn HRESULT init(HWND inHWnd)
* @brief 初期化
*/
HRESULT CDirectInput::init(HWND inHWnd)
{
	m_pDinput = NULL;		 //! DirectInput オブジェクト
	m_pKeyDevice = NULL;		 //! キーボード
	m_pMouseDevice = NULL;		 //! マウス

	ZeroMemory(&m_keyboardInput, sizeof(BYTE) * BUFFER_SIZE);		 //! キーボードの入力情報
	ZeroMemory(&m_keyboardInputPrev, sizeof(BYTE) * BUFFER_SIZE);	 //! 前回のキーボードの入力情報

	ZeroMemory(&m_pressed, sizeof(BYTE) * BUFFER_SIZE);		 //! 押された
	ZeroMemory(&m_pressedOnce, sizeof(BYTE) * BUFFER_SIZE);	 //! 一回押された

	ZeroMemory(&m_mouseInput, sizeof(DIMOUSESTATE2));		 //! マウスの入力情報
	ZeroMemory(&m_mouseInputPrev, sizeof(DIMOUSESTATE2));	 //! 前回のマウスの入力情報

	//! DirectInputオブジェクトの生成
	if (FAILED(DirectInput8Create(GetModuleHandle(NULL),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(VOID**)&m_pDinput,
		NULL))) {
		return E_FAIL;
	}

	//! キーボードの初期化
	//! DirectInputデバイスオブジェクトの生成
	if (FAILED(m_pDinput->CreateDevice(GUID_SysKeyboard,
		&m_pKeyDevice,
		NULL))) {
		return E_FAIL;
	}


	//! デバイスをキーボードに設定
	if (FAILED(m_pKeyDevice->SetDataFormat(&c_dfDIKeyboard))) {
		return E_FAIL;
	}


	//! 協調レベルの設定
	if (FAILED(m_pKeyDevice->SetCooperativeLevel(inHWnd,
		DISCL_NONEXCLUSIVE | DISCL_BACKGROUND))) {
		return E_FAIL;
	}


	//! デバイスを取得する
	m_pKeyDevice->Acquire();
	return S_OK;
}

/**
* @fn VOID free()
* @brief 解放
*/
VOID CDirectInput::free()
{
	if (m_pMouseDevice)
		m_pMouseDevice->Unacquire();
	SAFE_RELEASE(m_pMouseDevice);	 //! マウス

	if (m_pKeyDevice)
		m_pKeyDevice->Unacquire();
	SAFE_RELEASE(m_pKeyDevice);		//! キーボード

	SAFE_RELEASE(m_pDinput);		//! DirectInput オブジェクト
}

/****************************************************************
//! Public Methods
*****************************************************************/
/**
* @fn shared_ptr<CDirectInput> getInstance(HWND inHWnd)
* @brief インスタンスを取得 【クラスメソッド】<Singleton-pattern>
*/
std::shared_ptr<CDirectInput> CDirectInput::getInstance(HWND inHWnd)
{
	if (m_instance == NULL) {
		m_instance = shared_ptr<CDirectInput>(new CDirectInput());
		m_instance->init(inHWnd);
	}
	return m_instance;
}

/**
* @fn VOID releaseInstance()
* @brief インスタンスを解放 【クラスメソッド】<Singleton-pattern>
*/
VOID CDirectInput::releaseInstance()
{
	m_instance->free();
}

/**
* @fn HRESULT getState()
* @brief デバイス更新
*/
HRESULT CDirectInput::getState()
{
	//! キーボードの更新
	HRESULT hr = m_pKeyDevice->Acquire();

	if ((hr == DI_OK) || (hr == S_FALSE)) {
		memcpy(m_keyboardInputPrev, m_keyboardInput, sizeof(BYTE) * BUFFER_SIZE);	 //! 前回の状態を退避

		m_pKeyDevice->GetDeviceState(sizeof(m_keyboardInput), &m_keyboardInput);	 //! キーボードの状態を取得
		for (int i = 0; i < BUFFER_SIZE; i++) {
			if (IS_KEY_PRESSED(m_keyboardInput[i])) {
				if ((!m_pressedOnce[i]) && (!m_pressed[i])) {
					m_pressedOnce[i] = TRUE;		 //! 初めて押された
					m_pressed[i] = TRUE;
				}
				else {
					m_pressedOnce[i] = FALSE;
				}
			}
			else {
				m_pressedOnce[i] = FALSE;
				m_pressed[i] = FALSE;
			}
		}
	}
	return S_OK;
}

/**
* @fn BOOL isKeyPressed(BYTE aKey)
* @brief キーが押されているかどうか
*/
BOOL CDirectInput::isKeyPressed(BYTE aKey)
{
	// 現在押している
	if (IS_KEY_PRESSED(m_keyboardInput[aKey]))
	{
		return TRUE;
	}
	return FALSE;
}

/**
* @fn BOOL isPressedOnce(BYTE aKey)
* @brief キーが一回押されているかどうか
*/
BOOL CDirectInput::isPressedOnce(BYTE aKey)
{
	return m_pressedOnce[aKey];
}

/**
* @fn BOOL isKeyTrigger(BYTE aKey)
* @brief キーが押され続いてるかどうか
*/
BOOL CDirectInput::isKeyTrigger(BYTE aKey)
{
	//! 前回押していて現在押している
	if ((IS_KEY_PRESSED(m_keyboardInputPrev[aKey])) && (IS_KEY_PRESSED(m_keyboardInput[aKey])))
	{
		return TRUE;
	}
	return FALSE;
}

/**
* @fn BOOL isKeyReleased(BYTE aKey)
* @brief キーが離された
*/
BOOL CDirectInput::isKeyReleased(BYTE aKey)
{
	//! 前回押していて現在離している
	if ((IS_KEY_PRESSED(m_keyboardInputPrev[aKey])) && !(IS_KEY_PRESSED(m_keyboardInput[aKey])))
	{
		return TRUE;
	}
	return FALSE;
}