/**
* @file MyApp.cpp
* @brief MyAppクラスの実装
* @author EtuCho
* @date 2019/04/14
*/
#include "MyApp.h"

//
// MyAppクラス実装
//

MyApp::MyApp()
{
	m_wndCaption = "ShowTriangle";
}

MyApp::~MyApp()
{

}

HRESULT MyApp::Initialize(HINSTANCE hInstance, int nCmdShow)
{
	if (!SUCCEEDED(D3D11App::Initialize(hInstance, nCmdShow)))
	{
		return S_FALSE;
	}

	HRESULT hr = S_OK;

	// オブジェクト作成
	// 背景作成
	// 障害物作成

	return hr;
}

void MyApp::Render()
{
	// Clear the back buffer 
	m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, Colors::MidnightBlue);

	// Render a triangle
	m_pImmediateContext->VSSetShader(m_pVertexShader, nullptr, 0);
	m_pImmediateContext->PSSetShader(m_pPixelShader, nullptr, 0);
	m_pImmediateContext->Draw(3, 0);

	// Present the information rendered to the back buffer to the front buffer (the screen)
	m_pSwapChain->Present(0, 0);
}

void MyApp::Update(float dt)
{
	//! ゲーム更新
}

