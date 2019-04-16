/**
* @file MyVector.h
* @brief �x�N�g�����Z������N���X
* @author EtuCho
* @date �쐬��2018_02_07
*/
#pragma once
#include "stdafx.h"

/**
* @fn XMFLOAT4 ComputeUnitVector(XMFLOAT4 v_)
* @brief �x�N�g���𐳋K�����郁�\�b�h
* @details �߂�l�F���K��������̒P�ʃx�N�g��
*/
XMFLOAT4 ComputeUnitVector(XMFLOAT4 v_)
{
	//�x�N�g���̒���
	float length = powf((v_.x * v_.x) + (v_.y * v_.y) + (v_.z * v_.z), 0.5);

	//XYZ�e�����𒷂��Ŋ���,w�͂��̂܂�
	XMFLOAT4 unit;
	unit.x = v_.x / length;
	unit.y = v_.y / length;
	unit.z = v_.z / length;
	unit.w = v_.w;

	return unit;
}

/**
* @fn FLOAT ComputeVec3Dot(XMFLOAT4 *pV1, XMFLOAT4 *pV2)
* @brief �x�N�g�����m�̓��ς����߂�
* @details �߂�l�F���ρi�X�J���[�l�j
*/
FLOAT ComputeVec3Dot(XMFLOAT4 pV1_, XMFLOAT4 pV2_)
{
	return ((pV1_.x) * (pV2_.x) + (pV1_.y) * (pV2_.y) + (pV1_.z) * (pV2_.z));
}

/**
* @fn FLOAT ComputeVec3ScalarMultiplication(XMFLOAT4 *pV_, FLOAT *pS_)
* @brief �x�N�g���ƃX�J���[�̏�Z
* @details �߂�l�F�x�N�g��
*/
XMFLOAT4 ComputeVec3ScalarMultiplication(XMFLOAT4 pV_, FLOAT pS_)
{
	return { pV_.x * pS_,pV_.y * pS_, pV_.z * pS_, pV_.w, };
}

/**
* @fn FLOAT ComputeVec3PlusVec3(XMFLOAT4 pV1_, XMFLOAT4 pV2_)
* @brief �x�N�g���ƃx�N�g���̑����Z
* @details �߂�l�F�x�N�g��
*/
XMFLOAT4 ComputeVec3PlusVec3(XMFLOAT4 pV1_, XMFLOAT4 pV2_)
{
	return{ (pV1_.x) + (pV2_.x), (pV1_.y) + (pV2_.y), (pV1_.z) + (pV2_.z), 1.0f };
}