﻿/**
* @file Application.h
* @brief DirectX11をベースにしたアプリケーションクラスヘッダーファイル
* @author EtuCho
* @date 作成日2018_02_02
*/
#pragma once

#include "DebugUtil.h"
#include "Camera.h"
#include "DirectInput.h"
#include "MediaResource.h"

/**
* @brief アプリケーションクラス
* @details アプリケーションクラス
*/
class CApplication
{
private:

	ID3D11Texture2D*		m_pDepthStencil			= NULL;	//! 深度/ステンシル
	ID3D11DepthStencilView*	m_pDepthStencilView		= NULL;	//! 深度/ステンシル・ビュー 
	ID3D11DepthStencilState*m_pDepthStencilState	= NULL;	//! 深度/ステンシル・ステート・オブジェクト

	bool					m_isValidDepthMode		= true;	//! 深度バッファのモード
	ID3D11BlendState*		m_pBlendState			= NULL;	//! ブレンド・ステート
	ID3D11RasterizerState*	m_pRasterizerState		= NULL;	//! ラスタライザ・ステート・オブジェクト
	
	std::unique_ptr<CCamera>		m_pCamera	= NULL;	//! カメラ

	//ダイレクトX用メソッド
	HRESULT createBlendState();
	virtual void initCameraInfo() = 0;
	void app ();
	D3D11_BLEND_DESC getDefaultBlendDesc ();	//! ブレンドステート 無効
	D3D11_BLEND_DESC getAlignmenttBlendDesc ();	//! ブレンドステート 線形合成
	D3D11_BLEND_DESC getAddBlendDesc ();		//! ブレンドステート 加算合成
	D3D11_BLEND_DESC getSubtractBlendDesc ();	//! ブレンドステート 減算合成
	D3D11_BLEND_DESC getMultipleBlendDesc ();	//! ブレンドステート 乗算合成

	//メソッド
	void setClientSize(HWND hWnd_, LONG sx_, LONG sy_);
	void render ();
	virtual void renderSprite(XMFLOAT4X4	matView_, XMFLOAT4X4 matProj_) = 0;
	virtual void doOpenning () = 0;
	virtual void doPlaying () = 0;
	virtual void doGameClear() = 0;
	virtual void doGameOver() = 0;
	virtual void doEnding() = 0;

protected:
	HWND					m_hWnd;
	ID3D11Device*			m_pDevice			= NULL;	//! デバイス
	ID3D11DeviceContext*	m_pDeviceContext	= NULL;	//! デバイス・コンテキスト
	IDXGISwapChain*			m_pSwapChain		= NULL; //! スワップ・チェイン
	ID3D11RenderTargetView*	m_pRenderTargetView	= NULL;	//! 描画ターゲット・ビュー */
	D3D11_VIEWPORT          m_viewPort[1];				//! ビューポート
	std::shared_ptr<CDirectInput>	m_pKeyboard	= NULL;	//! キーボード　デバイス

	// ここからオリジナルのクラスを使用
	XMFLOAT3	m_vEyePt;		//! カメラ（視点）位置
	XMFLOAT3	m_vLookatPt;	//! 注視位置
	XMFLOAT3	m_vUpVec;		//! 上方位置
	FLOAT		m_angle;		//! 視野角
	FLOAT		m_aspect;		//! アスペクト比
	FLOAT		m_near;			//! 前方クリップ
	FLOAT		m_far;			//! 後方クリップ

	eGameStatus	m_gameStatus = eOpenning;
	int			m_frameCounter = 0;	//! フレーム数

	/**
	* @fn virtual bool createSprites(void)
	* @brief スプライト作成
	* @details 失敗の場合はfalseを返す
	*/
	virtual bool createSprites();
public:
	CApplication ();
	~CApplication ();

	HRESULT initWindow (HINSTANCE, WNDPROC, INT, INT, INT, INT, LPCWSTR);
	HRESULT initD3D ();
	HRESULT InitBackBuffer(void);
	LRESULT msgProc (HWND, UINT, WPARAM, LPARAM);
	void loop ();
	void release ();
};

