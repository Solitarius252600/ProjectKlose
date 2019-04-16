/**
* @file Sprite.h
* @brief テクスチャ付きのポリゴン・クラス実装
* @author EtuCho
* @date 作成日2018_02_04
*/
#pragma once

#include "stdafx.h"
#include "CommonType.h"

/** 
* @class CSprite
* @brief  ポリゴン・クラス
*/
class CSprite
{
protected:
	ID3D11DeviceContext*	m_pDeviceContext = NULL;	//! デバイス・コンテキスト
	D3D11_VIEWPORT          m_viewPort[1];				//! ビューポート

	ID3D11InputLayout*	m_pInputLayout		= NULL;	//! 入力レイアウト
	std::vector<ID3D11Buffer*> m_pVBArray;
	XMFLOAT2			m_VBLeftTop			= { 0.0f, 0.0f };	//! 頂点バッファ　矩形　左上
	XMFLOAT2			m_VBRightBottom		= { 0.0f, 0.0f };	//! 頂点バッファ　矩形　右下
	XMFLOAT2			m_VBSize			= { 0.0f, 0.0f };	//! 頂点バッファ　サイズ
	XMFLOAT2			m_baseSize			= { 0.0f, 0.0f };	//! 元のサイズ

	ID3D11VertexShader*	m_pVertexShader		= NULL;	//! effectではなく、個別にバーテックスシェーダー
	ID3D11PixelShader*	m_pPixelShader		= NULL;	//! effectではなく、個別にピクセルシェーダー
	ID3D11Buffer*		m_pConstantBuffer	= NULL;	//! アプリ←→シェーダー架け橋 ディフューズを渡すためのコンスタントバッファー

	ID3D11SamplerState*			m_pSampleLinear	= NULL;	//! テクスチャーのサンプラー
	ID3D11ShaderResourceView*	m_pTexture		= NULL;	//! テクスチャー

	Position<XMFLOAT4>	m_position;		//! 姿勢<位置 向き スケール 
	XMFLOAT4X4		m_mFinalWorld;		//! 最終的なワールド行列（この姿勢でレンダリングする）
	XMFLOAT4X4		m_matTran;			//! 平行移動行列
	XMFLOAT4X4		m_matPitch;			//! 回転行列　ピッチ
	XMFLOAT4X4		m_matYaw;			//! 回転行列　ヨー
	XMFLOAT4X4		m_matRoll;			//! 回転行列　ロール
	XMFLOAT4X4		m_matScale;			//! スケール行列
	size_t			m_animIndex	= 0;	//! アニメーションのUV配列
	BOOL			m_active	= TRUE;	//! 活動中
	FLOAT			m_moveQuantity;		//! 移動量
public:
	CSprite();
	~CSprite();
	virtual void init(
		ID3D11Device*			pDevice_,
		ID3D11DeviceContext*	pDeviceContext_,
		D3D11_VIEWPORT          viewPort_[],
		LPCWSTR					hlslName_,
		LPCWSTR					textureName_,
		XMFLOAT4				position_,
		XMFLOAT2				size_,
		std::vector<UVCoord>	uvArray_);
	void reset(XMFLOAT4 pos_) {
		setActive(TRUE);
		setPos(pos_);
	}
	void computePosition (void);
	virtual void render(XMFLOAT4X4 matView_, XMFLOAT4X4 matProj_, size_t uvIndex_ = 0, XMFLOAT4 diffuse_ = {0, 0, 0, 0});
	void release(void);
	BOOL getActive(void)				{ return m_active; }
	void setActive(BOOL cond_)			{ m_active = cond_; };
	void setScale(FLOAT scale_) {
		m_position.scale = scale_;
		m_VBSize.x = m_baseSize.x * scale_;
		m_VBSize.y = m_baseSize.y * scale_;
	};
	XMFLOAT4 getPos()				{ return m_position.pos;	};
	void setPos(XMFLOAT4 pos_)		{ m_position.pos    = pos_;	};
	void offsetPos(XMFLOAT4 pos_)	{ m_position.offset(pos_);	};
	void offsetPosInNormalRange(XMFLOAT4 pos_) {
		offsetPos(pos_);
		if (outOfWindow()) {
			offsetPos({ -pos_.x, -pos_.y, -pos_.z, pos_.w });
		}
	};
	BOOL isInvalid()
	{
		if (outOfWindow() || !m_active)
		{
			return TRUE;
		}
		return FALSE;
	}
	BOOL outOfWindow(void) {
		FLOAT left		= m_position.pos.x - m_VBSize.x / 2;
		FLOAT right		= m_position.pos.x + m_VBSize.x / 2;
		FLOAT top		= m_position.pos.y + m_VBSize.y / 2;
		FLOAT bottom	= m_position.pos.y - m_VBSize.y / 2;
		if ((left < WINDOW_LEFT) || (right > WINDOW_RIGHT) || (top > WINDOW_TOP) || (bottom < WINDOW_BOTTOM))
		{
			return TRUE;
		}
		return FALSE;
	}
	XMFLOAT2 getSize()				{ return m_VBSize; };

	//! 【向き】
	void setAngle(XMFLOAT3 degrees_)	{ m_position.setAngle(degrees_);	}
	FLOAT getAngleZ()					{ return m_position.roll;			};
	void setAngleZ(FLOAT degree_)		{ m_position.roll = degree_;		};
	void addAngle(XMFLOAT3 alpha_) {
		m_position.setAngle({
			m_position.pitch	+= alpha_.x,
			m_position.yaw		+= alpha_.y,
			m_position.roll		+= alpha_.z
		});
	}
	size_t getNumOfVBs() { return m_pVBArray.size(); };
	virtual BOOL collision(XMFLOAT4 pos_, FLOAT range_);
	virtual BOOL collision(XMFLOAT4 pos1_, XMFLOAT4 pos2_, FLOAT range_);
};