/**
* @file MyVector.h
* @brief ベクトル演算をするクラス
* @author EtuCho
* @date 作成日2018_02_07
*/
#pragma once
#include "stdafx.h"

/**
* @fn XMFLOAT4 ComputeUnitVector(XMFLOAT4 v_)
* @brief ベクトルを正規化するメソッド
* @details 戻り値：正規化した後の単位ベクトル
*/
XMFLOAT4 ComputeUnitVector(XMFLOAT4 v_)
{
	//ベクトルの長さ
	float length = powf((v_.x * v_.x) + (v_.y * v_.y) + (v_.z * v_.z), 0.5);

	//XYZ各成分を長さで割る,wはそのまま
	XMFLOAT4 unit;
	unit.x = v_.x / length;
	unit.y = v_.y / length;
	unit.z = v_.z / length;
	unit.w = v_.w;

	return unit;
}

/**
* @fn FLOAT ComputeVec3Dot(XMFLOAT4 *pV1, XMFLOAT4 *pV2)
* @brief ベクトル同士の内積を求める
* @details 戻り値：内積（スカラー値）
*/
FLOAT ComputeVec3Dot(XMFLOAT4 pV1_, XMFLOAT4 pV2_)
{
	return ((pV1_.x) * (pV2_.x) + (pV1_.y) * (pV2_.y) + (pV1_.z) * (pV2_.z));
}

/**
* @fn FLOAT ComputeVec3ScalarMultiplication(XMFLOAT4 *pV_, FLOAT *pS_)
* @brief ベクトルとスカラーの乗算
* @details 戻り値：ベクトル
*/
XMFLOAT4 ComputeVec3ScalarMultiplication(XMFLOAT4 pV_, FLOAT pS_)
{
	return { pV_.x * pS_,pV_.y * pS_, pV_.z * pS_, pV_.w, };
}

/**
* @fn FLOAT ComputeVec3PlusVec3(XMFLOAT4 pV1_, XMFLOAT4 pV2_)
* @brief ベクトルとベクトルの足し算
* @details 戻り値：ベクトル
*/
XMFLOAT4 ComputeVec3PlusVec3(XMFLOAT4 pV1_, XMFLOAT4 pV2_)
{
	return{ (pV1_.x) + (pV2_.x), (pV1_.y) + (pV2_.y), (pV1_.z) + (pV2_.z), 1.0f };
}