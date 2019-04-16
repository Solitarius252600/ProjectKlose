/**
* @file Camera.cpp
* @brief �J�����쐬
* @author EtuCho
* @date �쐬��2018_02_03
*/

#include "stdafx.h"
#include "Camera.h"


CCamera::CCamera ()
{
}


CCamera::~CCamera ()
{
}

void CCamera::init(
	XMFLOAT3 vEyePt_, XMFLOAT3 vLookatPt_, XMFLOAT3 vUpVec_,
	FLOAT	angle_, FLOAT	aspect_, FLOAT	near_, FLOAT	far_)
{
	m_vEyePt	= vEyePt_;		//! �J�����i���_�j�ʒu
	m_vLookatPt	= vLookatPt_;	//! �����ʒu
	m_vUpVec	= vUpVec_;		//! ����ʒu
	m_angle		= angle_;		//! ����p
	m_aspect	= aspect_;		//! �A�X�y�N�g��
	m_near		= near_;		//! �O���N���b�v
	m_far		= far_;			//! ����N���b�v
	XMStoreFloat4x4(&m_matView, XMMatrixIdentity());
	XMStoreFloat4x4(&m_matProj, XMMatrixIdentity());
	update();
}

void CCamera::update()
{
	//! �r���[�g�����X�t�H�[���i���_���W�ϊ��j
	XMStoreFloat4x4(&m_matView, XMMatrixLookAtLH(
		XMLoadFloat3(&m_vEyePt),
		XMLoadFloat3(&m_vLookatPt),
		XMLoadFloat3(&m_vUpVec)));

	//! �v���W�F�N�V�����g�����X�t�H�[���i�ˉe�ϊ��j
	XMStoreFloat4x4(&m_matProj, XMMatrixPerspectiveFovLH(
		m_angle,	//! ����p
		m_aspect,	//! �A�X�y�N�g��
		m_near,		//! �O���N���b�v
		m_far));	//! ����N���b�v
}
