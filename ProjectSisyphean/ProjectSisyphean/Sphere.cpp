/**
* @file Sphere.cpp
* @brief �v���C���[�����˂��鋅�̃N���X����
* @author EtuCho
* @date �쐬��2018_02_04
*/
#include "Sphere.h"

CSphere::CSphere()
{
}


CSphere::~CSphere()
{
}


void CSphere::setSpeed(XMFLOAT4 sp_)
{
	m_Speed = sp_;
}

void CSphere::addSpeed(XMFLOAT4 sp_)
{
	XMFLOAT4 newSpeed = { m_Speed.x + sp_.x, m_Speed.y + sp_.y, m_Speed.z + sp_.z, m_Speed.w };

	m_Speed = newSpeed;
}

XMFLOAT4 CSphere::getSpeed()
{
	return m_Speed;
}

/**
* @fn void reflection()
* @brief �t�B�[���h�ǂƓ���������̌����V�~�����[�V����
*/
void CSphere::reflection()
{
	XMFLOAT4 newSpeed = { m_Speed.x * 0.8f, m_Speed.y * 0.8f, m_Speed.z * 0.8f, m_Speed.w * 0.8f};

	m_Speed = newSpeed;
}

/**
* @fn void checkHitWindow(XMFLOAT4 pos_)
* @brief �t�B�[���h�ǂƂ̓����蔻��
*/
BOOL CSphere::checkHitWindow(XMFLOAT4 pos_)
{
	BOOL IsHit = false;
	FLOAT left = pos_.x - m_VBSize.x / 2;
	FLOAT right = pos_.x + m_VBSize.x / 2;
	FLOAT top = pos_.y + m_VBSize.y / 2;
	FLOAT bottom = pos_.y - m_VBSize.y / 2;

	if (left < WINDOW_LEFT + 32.0f || right > WINDOW_RIGHT - 32.0f)
	{
		m_Speed.x = -m_Speed.x;
		IsHit = true;
	}
	if (top > WINDOW_TOP - 32.0f || bottom < WINDOW_BOTTOM + 32.0f)
	{
		m_Speed.y = -m_Speed.y;
		IsHit = true;
	}

	return IsHit;
}

/**
* @fn void move()
* @brief �ړ�����
*/
void CSphere::move()
{
	//! ���V���W
	XMFLOAT4 newPos = { 0.0f,0.0f,0.0f,0.0f };

	newPos = { super::getPos().x + getSpeed().x,super::getPos().y + getSpeed().y,super::getPos().z + getSpeed().z,super::getPos().w + getSpeed().w, };

	//! �t�B�[���h�Ǔ����蔻��
	if (checkHitWindow(newPos))
	{
		//! ���˂���x���x������
		reflection();
	}
	else
	{
		//! ������Ȃ��Ȃ���W�X�V
		super::offsetPos(getSpeed());
	}
	
	
	//! �d�͉e�����󂯂�
	addSpeed({ 0.0f,getGra(),0.0f,0.0f });

}

/**
* @fn void activeLimit()
* @brief �������Ԑ���
*/
void CSphere::activeLimit()
{
	if (m_activeTime > 0)
	{
		m_activeTime--;
	}
	else
	{
		super::setActive(false);
	}
}

/**
* @fn BOOL checkHitBall()
* @brief �ق��̃{�[���Ƃ̓����蔻��(�~���m�̓����蔻��)
*/
BOOL CSphere::checkHitBall(shared_ptr<CSphere>& targetBall_)
{
	FLOAT dis = 0.0f;
	FLOAT var = 0.0f;

	dis = (sqrtf(powf((super::getPos().x - targetBall_->getPos().x), 2.0) + powf((super::getPos().y - targetBall_->getPos().y), 2.0)));
	var = dis - (super::getSize().x + targetBall_->getSize().x);
	if (var < 0)
	{
		return TRUE;
	}
	return FALSE;
}


/**
* @fn void hitBall(shared_ptr<CSphere> targetBall_)
* @brief �^�[�Q�b�g�{�[���Ɠ��������甽�˂���
*/
void CSphere::hitBall(shared_ptr<CSphere> targetBall_)
{
	XMFLOAT4 normal = ComputeUnitVector({ targetBall_->getPos().x - super::getPos().x, targetBall_->getPos().y - super::getPos().y, targetBall_->getPos().z - super::getPos().z, 1.0f });
	
	setSpeed(ComputeVec3PlusVec3(getSpeed(), ComputeVec3ScalarMultiplication(normal, 2.0f * ComputeVec3Dot(ComputeVec3ScalarMultiplication(getSpeed(), -1.0f), normal))));
}