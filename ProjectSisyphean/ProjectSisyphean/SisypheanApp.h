/**
* @file SisypheanApp名.cpp
* @brief ゲームアプリクラスヘッダー
* @author EtuCho
* @date 作成日2018_02_01
*/

#pragma once
#include "Application.h"
#include "Sprite.h"
#include "GameManager.h"

class CSisypheanApp :
	public CApplication
{
	typedef CApplication super;
private:
	std::unique_ptr<CSprite>		m_pOpening		= NULL;
	std::unique_ptr<CSprite>		m_pClear		= NULL;
	std::unique_ptr<CSprite>		m_pOver			= NULL;
	std::unique_ptr<CGameManager>	m_pGameManager	= NULL;

	//!【Method】 <Private>
	bool createSprites(void);
	void initCameraInfo();
	void doOpenning();
	void doPlaying();
	void doGameClear();
	void doGameOver();
	void doEnding();
public:
	CSisypheanApp();
	~CSisypheanApp();
	void renderSprite(XMFLOAT4X4 matView, XMFLOAT4X4 matProj);
};

