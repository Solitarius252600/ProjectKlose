/**
* @file DirectInput.cpp
* @brief �_�C���N�g�C���v�b�g�����t�@�C��
* @author EtuCho
* @date �쐬��2018_02_04
* @details �V���O���g���p�^�[���Ŏ���,���̓f�o�C�X�}�E�X�ǉ��K�v
*/

#include "stdafx.h"
#include "DirectInput.h"

//! �N���X�ϐ�
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
* @brief ������
*/
HRESULT CDirectInput::init(HWND inHWnd)
{
	m_pDinput = NULL;		 //! DirectInput �I�u�W�F�N�g
	m_pKeyDevice = NULL;		 //! �L�[�{�[�h
	m_pMouseDevice = NULL;		 //! �}�E�X

	ZeroMemory(&m_keyboardInput, sizeof(BYTE) * BUFFER_SIZE);		 //! �L�[�{�[�h�̓��͏��
	ZeroMemory(&m_keyboardInputPrev, sizeof(BYTE) * BUFFER_SIZE);	 //! �O��̃L�[�{�[�h�̓��͏��

	ZeroMemory(&m_pressed, sizeof(BYTE) * BUFFER_SIZE);		 //! �����ꂽ
	ZeroMemory(&m_pressedOnce, sizeof(BYTE) * BUFFER_SIZE);	 //! ��񉟂��ꂽ

	ZeroMemory(&m_mouseInput, sizeof(DIMOUSESTATE2));		 //! �}�E�X�̓��͏��
	ZeroMemory(&m_mouseInputPrev, sizeof(DIMOUSESTATE2));	 //! �O��̃}�E�X�̓��͏��

	//! DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(GetModuleHandle(NULL),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(VOID**)&m_pDinput,
		NULL))) {
		return E_FAIL;
	}

	//! �L�[�{�[�h�̏�����
	//! DirectInput�f�o�C�X�I�u�W�F�N�g�̐���
	if (FAILED(m_pDinput->CreateDevice(GUID_SysKeyboard,
		&m_pKeyDevice,
		NULL))) {
		return E_FAIL;
	}


	//! �f�o�C�X���L�[�{�[�h�ɐݒ�
	if (FAILED(m_pKeyDevice->SetDataFormat(&c_dfDIKeyboard))) {
		return E_FAIL;
	}


	//! �������x���̐ݒ�
	if (FAILED(m_pKeyDevice->SetCooperativeLevel(inHWnd,
		DISCL_NONEXCLUSIVE | DISCL_BACKGROUND))) {
		return E_FAIL;
	}


	//! �f�o�C�X���擾����
	m_pKeyDevice->Acquire();
	return S_OK;
}

/**
* @fn VOID free()
* @brief ���
*/
VOID CDirectInput::free()
{
	if (m_pMouseDevice)
		m_pMouseDevice->Unacquire();
	SAFE_RELEASE(m_pMouseDevice);	 //! �}�E�X

	if (m_pKeyDevice)
		m_pKeyDevice->Unacquire();
	SAFE_RELEASE(m_pKeyDevice);		//! �L�[�{�[�h

	SAFE_RELEASE(m_pDinput);		//! DirectInput �I�u�W�F�N�g
}

/****************************************************************
//! Public Methods
*****************************************************************/
/**
* @fn shared_ptr<CDirectInput> getInstance(HWND inHWnd)
* @brief �C���X�^���X���擾 �y�N���X���\�b�h�z<Singleton-pattern>
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
* @brief �C���X�^���X����� �y�N���X���\�b�h�z<Singleton-pattern>
*/
VOID CDirectInput::releaseInstance()
{
	m_instance->free();
}

/**
* @fn HRESULT getState()
* @brief �f�o�C�X�X�V
*/
HRESULT CDirectInput::getState()
{
	//! �L�[�{�[�h�̍X�V
	HRESULT hr = m_pKeyDevice->Acquire();

	if ((hr == DI_OK) || (hr == S_FALSE)) {
		memcpy(m_keyboardInputPrev, m_keyboardInput, sizeof(BYTE) * BUFFER_SIZE);	 //! �O��̏�Ԃ�ޔ�

		m_pKeyDevice->GetDeviceState(sizeof(m_keyboardInput), &m_keyboardInput);	 //! �L�[�{�[�h�̏�Ԃ��擾
		for (int i = 0; i < BUFFER_SIZE; i++) {
			if (IS_KEY_PRESSED(m_keyboardInput[i])) {
				if ((!m_pressedOnce[i]) && (!m_pressed[i])) {
					m_pressedOnce[i] = TRUE;		 //! ���߂ĉ����ꂽ
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
* @brief �L�[��������Ă��邩�ǂ���
*/
BOOL CDirectInput::isKeyPressed(BYTE aKey)
{
	// ���݉����Ă���
	if (IS_KEY_PRESSED(m_keyboardInput[aKey]))
	{
		return TRUE;
	}
	return FALSE;
}

/**
* @fn BOOL isPressedOnce(BYTE aKey)
* @brief �L�[����񉟂���Ă��邩�ǂ���
*/
BOOL CDirectInput::isPressedOnce(BYTE aKey)
{
	return m_pressedOnce[aKey];
}

/**
* @fn BOOL isKeyTrigger(BYTE aKey)
* @brief �L�[�������ꑱ���Ă邩�ǂ���
*/
BOOL CDirectInput::isKeyTrigger(BYTE aKey)
{
	//! �O�񉟂��Ă��Č��݉����Ă���
	if ((IS_KEY_PRESSED(m_keyboardInputPrev[aKey])) && (IS_KEY_PRESSED(m_keyboardInput[aKey])))
	{
		return TRUE;
	}
	return FALSE;
}

/**
* @fn BOOL isKeyReleased(BYTE aKey)
* @brief �L�[�������ꂽ
*/
BOOL CDirectInput::isKeyReleased(BYTE aKey)
{
	//! �O�񉟂��Ă��Č��ݗ����Ă���
	if ((IS_KEY_PRESSED(m_keyboardInputPrev[aKey])) && !(IS_KEY_PRESSED(m_keyboardInput[aKey])))
	{
		return TRUE;
	}
	return FALSE;
}