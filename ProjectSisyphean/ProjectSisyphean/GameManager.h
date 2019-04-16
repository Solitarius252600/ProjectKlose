/**
* @file GameManager.h
* @brief ゲーム進行を管理するクラス
* @author EtuCho
* @date 作成日2018_02_04
*/
#pragma once
#include "MediaResource.h"
#include "Player.h"
#include "DirectInput.h"

class CGameManager
{
private:
	std::shared_ptr<CPlayer> m_pPlayer;

public:
	CGameManager();
	virtual ~CGameManager();

	void init(
		ID3D11Device*			pDevice_,
		ID3D11DeviceContext*	pDeviceContext_,
		D3D11_VIEWPORT          viewPort_[],
		LPCWSTR					hlslName_);
	void render(XMFLOAT4X4 matView_, XMFLOAT4X4 matProj_);
	void update(std::shared_ptr<CDirectInput>& Keyboard_,int frameCnt_);
};

