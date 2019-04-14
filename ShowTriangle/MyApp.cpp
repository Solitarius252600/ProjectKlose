/**
* @file MyApp.cpp
* @brief MyApp�N���X�̎���
* @author EtuCho
* @date 2019/04/14
*/
#include "MyApp.h"

//
// MyApp�N���X����
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

	// �I�u�W�F�N�g�쐬
	// �w�i�쐬
	// ��Q���쐬

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
	//! �Q�[���X�V
}

