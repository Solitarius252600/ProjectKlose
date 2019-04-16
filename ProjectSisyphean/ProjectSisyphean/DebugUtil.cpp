/**
* @file DebugUtil.cpp
* @brief �f�o�b�O���b�Z�[�W�o�͗p
* @author EtuCho
* @date �쐬��2018_02_03
*/
#include "stdafx.h"
#include "DebugUtil.h"

/**
* @fn HRESULT PutMessage(LPCTSTR lpString_)
* @brief �G���[���b�Z�[�W�����[�U�[�ɕ\������
*/
HRESULT PutMessage(LPCTSTR lpString_)
{
	std::cout << lpString_ << std::endl;
	MessageBox(0, lpString_, NULL, MB_OK);
	return GetLastError();
}