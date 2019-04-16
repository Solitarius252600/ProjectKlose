/**
* @file Player.cpp
* @brief プレイヤークラス実装
* @author EtuCho
* @date 作成日2018_02_05
*/
#include "stdafx.h"
#include "Player.h"



CPlayer::CPlayer()
{
	for (int i = 0; i < k_NumberOfBall; i++)
	{
		m_Ball.push_back(shared_ptr<CSphere>(new CSphere()));
	}
}


CPlayer::~CPlayer()
{
}

/**
* @fn XMFLOAT4 ComputePosByDirectionZ(XMFLOAT4 old_, FLOAT directionArray_)
* @brief Z軸を回転した後の座標を計算する
* @details  速度をベクトルのままで計算する、この関数はボールの速度をプレイヤーの向きに合わせて計算して代入する
*/
XMFLOAT4 ComputePosByDirectionZ(XMFLOAT4 old_, FLOAT directionArray_)
{
	XMFLOAT4 result;
	XMStoreFloat4(
		&result,
		XMVector3TransformCoord(
			XMLoadFloat4(&old_),
			XMMatrixRotationZ(XMConvertToRadians(directionArray_))));
	return result;
}

/**
* @fn void init ComputePosByDirectionZ(
	ID3D11Device*			pDevice_,
	ID3D11DeviceContext*	pDeviceContext_,
	D3D11_VIEWPORT          viewPort_[],
	LPCWSTR					hlslName_)
* @brief プレイヤーとプレイヤーが持つ球の初期化
*/
void CPlayer::init(
	ID3D11Device*			pDevice_,
	ID3D11DeviceContext*	pDeviceContext_,
	D3D11_VIEWPORT          viewPort_[],
	LPCWSTR					hlslName_)
{
	vector <UVCoord>  iUV1_1 = {
		UVCoord{ { 0, 1.0f },{ 0, 0.0f },{ 1, 1.0f },{ 1, 0.0f } }
	};

	super::init(pDevice_, pDeviceContext_, viewPort_, hlslName_, Tex_Player, { WINDOW_LEFT + 128.0f,WINDOW_BOTTOM + 64.0f ,0.0f,0.0f }, { 64.0f,256.0f }, iUV1_1);

	for (size_t i = 0; i < m_Ball.size(); i++)
	{
		m_Ball[i]->init(pDevice_, pDeviceContext_, viewPort_, hlslName_, Tex_Ball, { 0.0f,0.0f,0.0f,0.0f }, {32.0f,32.0f},iUV1_1);
		m_Ball[i]->setActive(false);
	}
}

/**
* @fn void update(int frameCnt_)
* @brief 毎フレーム更新する
* @details 基本はプレイヤーが管理する球のステータス更新
*/
void CPlayer::update(int frameCnt_)
{
	for (size_t i = 0; i < m_Ball.size(); i++)
	{
		if (m_Ball[i]->getActive())
		{
			m_Ball[i]->move();
			m_Ball[i]->activeLimit();
		}
	}
	checkHitBall();
}

/**
* @fn void render(XMFLOAT4X4 matView_, XMFLOAT4X4 matProj_)
* @brief 自分と配下のアクティブ球のレンダリング
*/
void CPlayer::render(XMFLOAT4X4 matView_, XMFLOAT4X4 matProj_)
{

	super::render(matView_, matProj_);

	for (size_t i = 0; i < m_Ball.size(); i++)
	{
		if (m_Ball[i]->getActive())
		{
			m_Ball[i]->render(matView_, matProj_);
		}
	}
}

/**
* @fn void roll(XMFLOAT3 alp_)
* @brief リミット範囲内で回転する
*/
void CPlayer::roll(XMFLOAT3 alp_)
{
	if (alp_.z > 0.0f)
	{
		if (super::getAngleZ() < k_RoatLim.x)
		{
			super::addAngle(alp_);
		}
	}
	else
	{
		if (super::getAngleZ() > k_RoatLim.y)
		{
			super::addAngle(alp_);
		}
	}
} 

/**
* @fn void shot()
* @brief 球を発射
*/
void CPlayer::shot()
{
	for (size_t i = 0; i < m_Ball.size(); i++)
	{
		if (!m_Ball[i]->getActive())
		{
			m_Ball[i]->setPos(super::getPos());
			m_Ball[i]->setActive(true);
			m_Ball[i]->setSpeed(ComputePosByDirectionZ(m_Ball[i]->k_Speed, super::getAngleZ()));
			m_Ball[i]->resetActiveTime();
			break;
		}
	}
}

/**
* @fn void checkHitBall()
* @brief 球同士の当たり判定
*/
void CPlayer::checkHitBall()
{
	for (size_t i = 0; i < m_Ball.size(); i++)
	{
		if (m_Ball[i]->getActive())
		{
			for (size_t j = i + 1; j < m_Ball.size() - i; j++)
			{
				if (m_Ball[j]->getActive())
				{
					if (m_Ball[i]->checkHitBall(m_Ball[j]))
					{
						m_Ball[i]->hitBall(m_Ball[j]);
						m_Ball[j]->hitBall(m_Ball[i]);
						break;
					}
				}
			}
		}
	}
}