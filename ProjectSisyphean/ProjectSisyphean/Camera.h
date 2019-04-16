/**
* @file Camera.cpp
* @brief カメラ作成
* @author EtuCho
* @date 作成日2018_02_03
*/
#pragma once

#include "stdafx.h"
#include "CommonType.h"

class CCamera
{
private:
	XMFLOAT4X4	m_matView;		//! ビュー行列
	XMFLOAT3	m_vEyePt;		//! カメラ（視点）位置
	XMFLOAT3	m_vLookatPt;	//! 注視位置
	XMFLOAT3	m_vUpVec;		//! 上方位置

	XMFLOAT4X4	m_matProj;		//! プロジェクション行列
	FLOAT		m_angle;		//! 視野角
	FLOAT		m_aspect;		//! アスペクト比
	FLOAT		m_near;			//! 前方クリップ
	FLOAT		m_far;			//! 後方クリップ

public:
	CCamera ();
	~CCamera ();
	XMFLOAT4X4 getViewMatrix()			{ return m_matView; };		//! ビュー行列
	XMFLOAT4X4 getProjectionMatrix()	{ return m_matProj; };		//! プロジェクション行列
	void init (
		XMFLOAT3 vEyePt_,		//! カメラ（視点）位置
		XMFLOAT3 vLookatPt_,	//! 注視位置
		XMFLOAT3 vUpVec_,		//! 上方位置
		FLOAT	angle_,			//! 視野角
		FLOAT	aspect_,		//! アスペクト比
		FLOAT	near_,			//! 前方クリップ
		FLOAT	far_			//! 後方クリップ
		);
	void update();				//! ビュー行列、プロジェクション行列を更新する　＜カメラを移動させたい時＞
};

