/**
* @file D3D11App.h
* @brief D3Dアプリケーションヘッダーファイル
* @author EtuCho
* @date 2019/04/14
* @details D3D使用上基本の機能定義
*/
#pragma once
#include "Common.h"
#include "D3D11Timer.h"



#ifndef INCLUDE_D3D11APP
#define INCLUDE_D3D11APP


/**
* @brief Direct3D11アプリケーション基本機能を定義するクラス
* @details ウインドウプロシージャとかデバイスの定義と生成、メッセージ処理など基盤になる処理
*/
class D3D11App
{
public:
	/**
	* @brief コンストラクタ
	*/
	D3D11App();

	/**
	* @brief デストラクタ
	*/
	virtual ~D3D11App();

	/**
	* @fn HRESULT Initialize(HINSTANCE hInstance, int nCmdShow)
	* @brief 初期化
	* @details ウインドウクラスを登録、各パラメータを定義する
	*		   最低限必要なものだけ定義、拡張するなら継承先でオーバーライド
	*/
	virtual HRESULT Initialize(HINSTANCE hInstance, int nCmdShow);

	/**
	* @fn void Update(float dt)
	* @brief アプリケーション更新
	* @param[float] dt ディレイタイム
	* @details 実装は継承先の派生クラスで
	*/
	virtual void Update(float dt) = 0;

	/**
	* @fn void Render()
	* @brief シーンの描画
	* @details 仮想メソッド、継承先で実装
	*/
	virtual void Render() = 0;

	/**
	* @fn void RunMessageLoop()
	* @brief システムからメッセージのチェックとアプリケーション処理
	*/
	void RunMessageLoop();

	/**
	* @fn LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	* @brief メッセージからのイベントチェック
	*/
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

protected:
	/**
	* @fn HRESULT CreateDevice()
	* @brief 関連デバイスの作成
	*/
	HRESULT CreateDevice();

	/**
	* @fn HRESULT CompileShaderFromFile()
	* @brief シェーダーコンパイル
	*/
	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

	/**
	* @fn void DiscardDeviceResources()
	* @brief デバイス廃棄
	*/
	void DiscardDeviceResources();

	/**
	* @fn virtual void OnResize(UINT width, UINT height)
	* @brief 実行終了
	*/
	virtual void OnDestroy();

	/**
	* @fn void CalculateFrameStats()
	* @brief FPS計算と表示
	*/
	void CalculateFrameStats();


protected:
	//! ウインドウ
	HWND								m_hWnd = nullptr;
	//! ウインドウ名前
	string								m_wndCaption = "D3D11App";
	//! 実行中かどうか
	BOOL								m_fRunning = TRUE;
	//! FPS計算と実行時間を記録する
	shared_ptr<D3D11Timer>				m_pTimer;

	D3D_DRIVER_TYPE         m_driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL       m_featureLevel = D3D_FEATURE_LEVEL_11_0;
	ID3D11Device*           m_pd3dDevice = nullptr;
	ID3D11Device1*          m_pd3dDevice1 = nullptr;
	ID3D11DeviceContext*    m_pImmediateContext = nullptr;
	ID3D11DeviceContext1*   m_pImmediateContext1 = nullptr;
	IDXGISwapChain*         m_pSwapChain = nullptr;
	IDXGISwapChain1*        m_pSwapChain1 = nullptr;
	ID3D11RenderTargetView* m_pRenderTargetView = nullptr;

	ID3D11VertexShader* m_pVertexShader = nullptr;
	ID3D11PixelShader* m_pPixelShader = nullptr;
	ID3D11InputLayout* m_pVertexLayout = nullptr;
	ID3D11Buffer* m_pVertexBuffer = nullptr;

	struct SimpleVertex
	{
		XMFLOAT3 Pos;
	};

};

#endif
