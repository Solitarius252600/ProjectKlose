/**
* @file D3D11App.h
* @brief D3D�A�v���P�[�V�����w�b�_�[�t�@�C��
* @author EtuCho
* @date 2019/04/14
* @details D3D�g�p���{�̋@�\��`
*/
#pragma once
#include "Common.h"
#include "D3D11Timer.h"



#ifndef INCLUDE_D3D11APP
#define INCLUDE_D3D11APP


/**
* @brief Direct3D11�A�v���P�[�V������{�@�\���`����N���X
* @details �E�C���h�E�v���V�[�W���Ƃ��f�o�C�X�̒�`�Ɛ����A���b�Z�[�W�����ȂǊ�ՂɂȂ鏈��
*/
class D3D11App
{
public:
	/**
	* @brief �R���X�g���N�^
	*/
	D3D11App();

	/**
	* @brief �f�X�g���N�^
	*/
	virtual ~D3D11App();

	/**
	* @fn HRESULT Initialize(HINSTANCE hInstance, int nCmdShow)
	* @brief ������
	* @details �E�C���h�E�N���X��o�^�A�e�p�����[�^���`����
	*		   �Œ���K�v�Ȃ��̂�����`�A�g������Ȃ�p����ŃI�[�o�[���C�h
	*/
	virtual HRESULT Initialize(HINSTANCE hInstance, int nCmdShow);

	/**
	* @fn void Update(float dt)
	* @brief �A�v���P�[�V�����X�V
	* @param[float] dt �f�B���C�^�C��
	* @details �����͌p����̔h���N���X��
	*/
	virtual void Update(float dt) = 0;

	/**
	* @fn void Render()
	* @brief �V�[���̕`��
	* @details ���z���\�b�h�A�p����Ŏ���
	*/
	virtual void Render() = 0;

	/**
	* @fn void RunMessageLoop()
	* @brief �V�X�e�����烁�b�Z�[�W�̃`�F�b�N�ƃA�v���P�[�V��������
	*/
	void RunMessageLoop();

	/**
	* @fn LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	* @brief ���b�Z�[�W����̃C�x���g�`�F�b�N
	*/
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

protected:
	/**
	* @fn HRESULT CreateDevice()
	* @brief �֘A�f�o�C�X�̍쐬
	*/
	HRESULT CreateDevice();

	/**
	* @fn HRESULT CompileShaderFromFile()
	* @brief �V�F�[�_�[�R���p�C��
	*/
	HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

	/**
	* @fn void DiscardDeviceResources()
	* @brief �f�o�C�X�p��
	*/
	void DiscardDeviceResources();

	/**
	* @fn virtual void OnResize(UINT width, UINT height)
	* @brief ���s�I��
	*/
	virtual void OnDestroy();

	/**
	* @fn void CalculateFrameStats()
	* @brief FPS�v�Z�ƕ\��
	*/
	void CalculateFrameStats();


protected:
	//! �E�C���h�E
	HWND								m_hWnd = nullptr;
	//! �E�C���h�E���O
	string								m_wndCaption = "D3D11App";
	//! ���s�����ǂ���
	BOOL								m_fRunning = TRUE;
	//! FPS�v�Z�Ǝ��s���Ԃ��L�^����
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
