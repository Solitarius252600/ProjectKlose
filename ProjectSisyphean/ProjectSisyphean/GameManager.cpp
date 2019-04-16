/**
* @file GameManager.cpp
* @brief ゲーム進行を管理するクラス実装
* @author EtuCho
* @date 作成日2018_02_04
*/
#include "stdafx.h"
#include "GameManager.h"



CGameManager::CGameManager()
{
}


CGameManager::~CGameManager()
{
}


/**
* @fn void init()
* @brief ゲームマネージャが管理しているものを初期化
*/
void CGameManager::init(
	ID3D11Device*			pDevice_,
	ID3D11DeviceContext*	pDeviceContext_,
	D3D11_VIEWPORT          viewPort_[],
	LPCWSTR					hlslName_)
{
	m_pPlayer = unique_ptr<CPlayer>(new CPlayer());
	m_pPlayer->init(pDevice_,pDeviceContext_,viewPort_,hlslName_);
}

/**
* @fn void update()
* @brief アップデート
*/
void CGameManager::update(std::shared_ptr<CDirectInput>& Keyboard_,int frameCnt_)
{
	//プレイヤー回転
	if (Keyboard_->isKeyTrigger(DIK_UPARROW))
	{
		m_pPlayer->roll({ 0.0f,0.0f,3.0f });
	}
	if (Keyboard_->isKeyTrigger(DIK_DOWNARROW))
	{
		m_pPlayer->roll({ 0.0f,0.0f,-3.0f });
	}
	if (Keyboard_->isPressedOnce(DIK_SPACE))
	{
		m_pPlayer->shot();
	}

	m_pPlayer->update(frameCnt_);
}

/**
* @fn void render()
* @brief 配下をレンダリングする
*/
void CGameManager::render(XMFLOAT4X4 matView_, XMFLOAT4X4 matProj_)
{
	m_pPlayer->render(matView_, matProj_);
}
