/**
* @file Player.h
* @brief �v���C���[�N���X��`
* @author EtuCho
* @date �쐬��2018_02_05
* @details �v���C���[�͋��𔭎˂��邾���A���s����̓S�[���N���X�ōs��
			�ΐ��\�肵�Ă��܂��̂Ńv���C���[�ԍ��őΐ�҂𕪂���
*/
#pragma once
#include "Sphere.h"
#include "MediaResource.h"

class CPlayer :
	public CSprite
{
	typedef CSprite super;

private:
	vector <std::shared_ptr<CSphere>> m_Ball;
	const int k_NumberOfBall = 5;
	XMFLOAT2 k_RoatLim = { 10.0f,-80.0f };

public:
	CPlayer();
	virtual ~CPlayer();

	void init(ID3D11Device*			pDevice_,
		ID3D11DeviceContext*	pDeviceContext_,
		D3D11_VIEWPORT          viewPort_[],
		LPCWSTR					hlslName_);

	void render(XMFLOAT4X4 matView_, XMFLOAT4X4 matProj_);
	void roll(XMFLOAT3 alp_);
	void shot();
	void update(int frameCnt_);
	void checkHitBall();
};

