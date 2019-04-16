/**
* @file DebugUtil.cpp
* @brief デバッグメッセージ出力用
* @author EtuCho
* @date 作成日2018_02_03
*/
#include "stdafx.h"
#include "DebugUtil.h"

/**
* @fn HRESULT PutMessage(LPCTSTR lpString_)
* @brief エラーメッセージをユーザーに表示する
*/
HRESULT PutMessage(LPCTSTR lpString_)
{
	std::cout << lpString_ << std::endl;
	MessageBox(0, lpString_, NULL, MB_OK);
	return GetLastError();
}