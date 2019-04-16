/**
* @file Camera.cpp
* @brief カメラ作成
* @author EtuCho
* @date 作成日2018_02_03
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
	m_vEyePt	= vEyePt_;		//! カメラ（視点）位置
	m_vLookatPt	= vLookatPt_;	//! 注視位置
	m_vUpVec	= vUpVec_;		//! 上方位置
	m_angle		= angle_;		//! 視野角
	m_aspect	= aspect_;		//! アスペクト比
	m_near		= near_;		//! 前方クリップ
	m_far		= far_;			//! 後方クリップ
	XMStoreFloat4x4(&m_matView, XMMatrixIdentity());
	XMStoreFloat4x4(&m_matProj, XMMatrixIdentity());
	update();
}

void CCamera::update()
{
	//! ビュートランスフォーム（視点座標変換）
	XMStoreFloat4x4(&m_matView, XMMatrixLookAtLH(
		XMLoadFloat3(&m_vEyePt),
		XMLoadFloat3(&m_vLookatPt),
		XMLoadFloat3(&m_vUpVec)));

	//! プロジェクショントランスフォーム（射影変換）
	XMStoreFloat4x4(&m_matProj, XMMatrixPerspectiveFovLH(
		m_angle,	//! 視野角
		m_aspect,	//! アスペクト比
		m_near,		//! 前方クリップ
		m_far));	//! 後方クリップ
}
