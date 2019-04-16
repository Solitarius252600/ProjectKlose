/**
* @file Player.cpp
* @brief �v���C���[�N���X����
* @author EtuCho
* @date �쐬��2018_02_05
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
* @brief Z������]������̍��W���v�Z����
* @details  ���x���x�N�g���̂܂܂Ōv�Z����A���̊֐��̓{�[���̑��x���v���C���[�̌����ɍ��킹�Čv�Z���đ������
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
* @brief �v���C���[�ƃv���C���[�������̏�����
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
* @brief ���t���[���X�V����
* @details ��{�̓v���C���[���Ǘ����鋅�̃X�e�[�^�X�X�V
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
* @brief �����Ɣz���̃A�N�e�B�u���̃����_�����O
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
* @brief ���~�b�g�͈͓��ŉ�]����
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
* @brief ���𔭎�
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
* @brief �����m�̓����蔻��
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