/**
* @file Camera.cpp
* @brief �J�����쐬
* @author EtuCho
* @date �쐬��2018_02_03
*/
#pragma once

#include "stdafx.h"
#include "CommonType.h"

class CCamera
{
private:
	XMFLOAT4X4	m_matView;		//! �r���[�s��
	XMFLOAT3	m_vEyePt;		//! �J�����i���_�j�ʒu
	XMFLOAT3	m_vLookatPt;	//! �����ʒu
	XMFLOAT3	m_vUpVec;		//! ����ʒu

	XMFLOAT4X4	m_matProj;		//! �v���W�F�N�V�����s��
	FLOAT		m_angle;		//! ����p
	FLOAT		m_aspect;		//! �A�X�y�N�g��
	FLOAT		m_near;			//! �O���N���b�v
	FLOAT		m_far;			//! ����N���b�v

public:
	CCamera ();
	~CCamera ();
	XMFLOAT4X4 getViewMatrix()			{ return m_matView; };		//! �r���[�s��
	XMFLOAT4X4 getProjectionMatrix()	{ return m_matProj; };		//! �v���W�F�N�V�����s��
	void init (
		XMFLOAT3 vEyePt_,		//! �J�����i���_�j�ʒu
		XMFLOAT3 vLookatPt_,	//! �����ʒu
		XMFLOAT3 vUpVec_,		//! ����ʒu
		FLOAT	angle_,			//! ����p
		FLOAT	aspect_,		//! �A�X�y�N�g��
		FLOAT	near_,			//! �O���N���b�v
		FLOAT	far_			//! ����N���b�v
		);
	void update();				//! �r���[�s��A�v���W�F�N�V�����s����X�V����@���J�������ړ�������������
};

