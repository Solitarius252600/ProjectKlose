/**
* @file SisypheanApp名.cpp
* @brief ゲームアプリクラス実装
* @author EtuCho
* @date 作成日2018_02_01
*/
#include "stdafx.h"
#include "SisypheanApp.h"


CSisypheanApp::CSisypheanApp()
{
}


CSisypheanApp::~CSisypheanApp()
{
}

/**
* @fn void initCameraInfo()
* @brief カメラ作成に必要な情報をゲット
*/
void CSisypheanApp::initCameraInfo()
{
	m_vEyePt	= XMFLOAT3{ 0.0f, 0.0f,  -800.0f };		//! カメラ（視点）位置
	m_vLookatPt = XMFLOAT3{ 0.0f, 0.0f,     0.0f };		//! 注視位置
	m_vUpVec	= XMFLOAT3{ 0.0f, 1.0f,     0.0f };	//! 上方位置
	m_angle		= (FLOAT)XM_PI / 4;					//! 視野角
	m_aspect	= (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT;		//! アスペクト比
	m_near		= 0.1f;								//! 前方クリップ
	m_far		= 1000.0f;							//! 後方クリップ
}


/**
* @fn bool createSprites()
* @brief スプライト作成
*/
bool CSisypheanApp::createSprites()
{
	super::createSprites();
	try {
		//! 1/1
		vector <UVCoord>  iUV1_1 = {
			UVCoord{ { 0, 1.0f },{ 0, 0.0f },{ 1, 1.0f },{ 1, 0.0f } }
		};
		m_pOpening = unique_ptr<CSprite>(new CSprite());
		m_pOpening->init(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_MyHLSL, Tex_Title, { 0.0f, 0.0f, 0.0f, 0.0f }, { WINDOW_WIDTH , WINDOW_HEIGHT }, iUV1_1);
		
		m_pClear = unique_ptr<CSprite>(new CSprite());
		m_pClear->init(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_MyHLSL, Tex_GameClear, { 0.0f, 0.0f, 0.0f, 0.0f }, { WINDOW_WIDTH , WINDOW_HEIGHT }, iUV1_1);
		
		m_pOver = unique_ptr<CSprite>(new CSprite());
		m_pOver->init(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_MyHLSL, Tex_GameOver, { 0.0f, 0.0f, 0.0f, 0.0f }, { WINDOW_WIDTH , WINDOW_HEIGHT }, iUV1_1);
	
		m_pGameManager = unique_ptr<CGameManager>(new CGameManager());
		//! ゲームマネージャによってゲームオブジェクト初期化
		m_pGameManager->init(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_MyHLSL);

		return true;
	}
	catch (LPCWSTR str) {
		MessageBox(0, str, NULL, MB_OK);
		return false;
	}
}

//! オープニング
void CSisypheanApp::doOpenning()
{
	if (m_pKeyboard->isKeyPressed(DIK_SPACE)) {
		m_gameStatus = ePlaying;
	}
}


//! プレー中
void CSisypheanApp::doPlaying()
{
	try
	{
		m_frameCounter++;
		m_frameCounter = m_frameCounter > 65536 ? 0 : m_frameCounter;

//******************************************************************************************************
//Debug用
		if (m_pKeyboard->isPressedOnce(DIK_C)) {
			throw eGameClear;
		}
		if (m_pKeyboard->isPressedOnce(DIK_O)) {
			throw eGameOver;
		}
//******************************************************************************************************
		m_pGameManager->update(m_pKeyboard,m_frameCounter);



	}//! end of try
	catch (eGameStatus status_)
	{
		if (status_ == eGameClear)
		{
			m_gameStatus = eGameClear;
			//MessageBox(0, L"ゲームクリアです。", NULL, MB_OK);
		}
		else if (status_ == eGameOver)
		{
			m_gameStatus = eGameOver;
			//MessageBox(0, L"ゲームオーバーです。", NULL, MB_OK);
		}
	}//! end of catch
}
void CSisypheanApp::doGameClear()
{
	if (m_pKeyboard->isPressedOnce(DIK_R)) {
		m_gameStatus = eOpenning;
	}
}

void CSisypheanApp::doGameOver()
{
	if (m_pKeyboard->isPressedOnce(DIK_R)) {
		m_gameStatus = eOpenning;
	}
}

void CSisypheanApp::doEnding()
{
}


//! シーンを画面にレンダリング
void CSisypheanApp::renderSprite(XMFLOAT4X4 matView_, XMFLOAT4X4 matProj_)
{
	switch (m_gameStatus)
	{
	case eOpenning:
		m_pOpening->render(matView_, matProj_);
		//MessageBox(0, L"オープニングです。", NULL, MB_OK);
		break;
	case ePlaying:
		m_pGameManager->render(matView_, matProj_);
		break;
	case eGameClear:
		m_pClear->render(matView_, matProj_);
		break;
	case eGameOver:
		m_pOver->render(matView_, matProj_);
		break;
	case eEnding:
		break;
	default:
		break;
	}

}