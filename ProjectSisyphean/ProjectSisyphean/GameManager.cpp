/**
* @file GameManager.cpp
* @brief �Q�[���i�s���Ǘ�����N���X����
* @author EtuCho
* @date �쐬��2018_02_04
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
* @brief �Q�[���}�l�[�W�����Ǘ����Ă�����̂�������
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
* @brief �A�b�v�f�[�g
*/
void CGameManager::update(std::shared_ptr<CDirectInput>& Keyboard_,int frameCnt_)
{
	//�v���C���[��]
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
* @brief �z���������_�����O����
*/
void CGameManager::render(XMFLOAT4X4 matView_, XMFLOAT4X4 matProj_)
{
	m_pPlayer->render(matView_, matProj_);
}
