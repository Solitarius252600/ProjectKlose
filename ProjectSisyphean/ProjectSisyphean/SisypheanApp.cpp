/**
* @file SisypheanApp��.cpp
* @brief �Q�[���A�v���N���X����
* @author EtuCho
* @date �쐬��2018_02_01
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
* @brief �J�����쐬�ɕK�v�ȏ����Q�b�g
*/
void CSisypheanApp::initCameraInfo()
{
	m_vEyePt	= XMFLOAT3{ 0.0f, 0.0f,  -800.0f };		//! �J�����i���_�j�ʒu
	m_vLookatPt = XMFLOAT3{ 0.0f, 0.0f,     0.0f };		//! �����ʒu
	m_vUpVec	= XMFLOAT3{ 0.0f, 1.0f,     0.0f };	//! ����ʒu
	m_angle		= (FLOAT)XM_PI / 4;					//! ����p
	m_aspect	= (FLOAT)WINDOW_WIDTH / (FLOAT)WINDOW_HEIGHT;		//! �A�X�y�N�g��
	m_near		= 0.1f;								//! �O���N���b�v
	m_far		= 1000.0f;							//! ����N���b�v
}


/**
* @fn bool createSprites()
* @brief �X�v���C�g�쐬
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
		//! �Q�[���}�l�[�W���ɂ���ăQ�[���I�u�W�F�N�g������
		m_pGameManager->init(m_pDevice, m_pDeviceContext, m_viewPort, HLSL_MyHLSL);

		return true;
	}
	catch (LPCWSTR str) {
		MessageBox(0, str, NULL, MB_OK);
		return false;
	}
}

//! �I�[�v�j���O
void CSisypheanApp::doOpenning()
{
	if (m_pKeyboard->isKeyPressed(DIK_SPACE)) {
		m_gameStatus = ePlaying;
	}
}


//! �v���[��
void CSisypheanApp::doPlaying()
{
	try
	{
		m_frameCounter++;
		m_frameCounter = m_frameCounter > 65536 ? 0 : m_frameCounter;

//******************************************************************************************************
//Debug�p
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
			//MessageBox(0, L"�Q�[���N���A�ł��B", NULL, MB_OK);
		}
		else if (status_ == eGameOver)
		{
			m_gameStatus = eGameOver;
			//MessageBox(0, L"�Q�[���I�[�o�[�ł��B", NULL, MB_OK);
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


//! �V�[������ʂɃ����_�����O
void CSisypheanApp::renderSprite(XMFLOAT4X4 matView_, XMFLOAT4X4 matProj_)
{
	switch (m_gameStatus)
	{
	case eOpenning:
		m_pOpening->render(matView_, matProj_);
		//MessageBox(0, L"�I�[�v�j���O�ł��B", NULL, MB_OK);
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