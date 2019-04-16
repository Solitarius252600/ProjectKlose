/**
* @file Sphere.cpp
* @brief プレイヤーが発射する球のクラス定義
* @author EtuCho
* @date 作成日2018_02_04
*/
#pragma once
#include "stdafx.h"
#include "Sprite.h"

class CSphere :
	public CSprite
{
	typedef CSprite super;
private:
	XMFLOAT4 m_Speed = { 0.0f,0.0f,0.0f,0.0f};
	const float k_gravity = -0.3f;
	const int k_activeLimitTime = 300;
	int m_activeTime = 0;
public:
	const XMFLOAT4 k_Speed = { 0.0f,25.0f,0.0f,0.0f };

	CSphere();
	virtual ~CSphere();

	FLOAT getGra() { return k_gravity; }
	void setSpeed(XMFLOAT4 sp_);
	void addSpeed(XMFLOAT4 sp_);
	XMFLOAT4 getSpeed();
	void reflection();
	BOOL checkHitWindow(XMFLOAT4 pos_);
	void move();
	void activeLimit();
	void resetActiveTime() { m_activeTime = k_activeLimitTime; }
	BOOL checkHitBall(shared_ptr<CSphere>& targetBall_);
	void hitBall(shared_ptr<CSphere> targetBall_);


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
};

