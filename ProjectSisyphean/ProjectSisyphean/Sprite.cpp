/**
* @file Sprite.cpp
* @brief テクスチャ付きのポリゴン・クラス実装
* @author EtuCho
* @date 作成日2018_02_04
*/

#include "stdafx.h"
#include "Sprite.h"

CSprite::CSprite()
{
}

CSprite::~CSprite()
{
}


/**
* @fn void init()
* @brief 初期化
*/
void CSprite::init(
	ID3D11Device*			pDevice_,
	ID3D11DeviceContext*	pDeviceContext_,
	D3D11_VIEWPORT			viewPort_[],
	LPCWSTR					hlslName_,
	LPCWSTR					textureName_,
	XMFLOAT4				position_,
	XMFLOAT2				size_,
	std::vector<UVCoord>	uvArray_)
{
	HRESULT hr;
	m_pDeviceContext	= pDeviceContext_;	//! レンダリングに必要　＜実行中に変化しない＞
	m_viewPort[0]		= viewPort_[0];		//! レンダリングに必要　＜実行中に変化しない＞
	m_baseSize			= size_;
	m_VBSize			= size_;
	m_active			= TRUE;
	m_position.setup({ position_.x, position_.y, position_.z, 0.0f }, 0.0f, 0.0f, 0.0f, 1.0f);	//位置

	//hlslファイル読み込み ブロブ作成　ブロブとはシェーダーの塊みたいなもの。XXシェーダーとして特徴を持たない。後で各種シェーダーに成り得る。
	ID3DBlob *pBlobVS = NULL;
	ID3DBlob *pErrors = NULL;

	//! ブロブからバーテックスシェーダー作成
	hr = D3DX11CompileFromFile(
		hlslName_,		 //! ファイル名
		NULL,			 //! マクロ定義(なし)
		NULL,			 //! インクルード・ファイル定義(なし)
		"VS",			 //! 「VS関数」がシェーダから実行される
		"vs_5_0",		 //! 頂点シェーダ
		0,				 //! コンパイル・オプション
		0,				 //! エフェクトのコンパイル・オプション(なし)
		NULL,			 //! 直ぐにコンパイルしてから関数を抜ける。
		&pBlobVS,		 //! コンパイルされたバイト・コード
		&pErrors,		 //! エラーメッセージ
		NULL);			 //! 戻り値
	if (FAILED(hr))
	{
		throw L"CSprite::init HLSL (VS)読み込み失敗";
	}
	SAFE_RELEASE(pErrors);
	hr = pDevice_->CreateVertexShader(
		pBlobVS->GetBufferPointer(),	//! バイト・コードへのポインタ
		pBlobVS->GetBufferSize(),		//! バイト・コードの長さ
		NULL,
		&m_pVertexShader);				//! 頂点シェーダを受け取る変数
	if (FAILED(hr))
	{
		SAFE_RELEASE(pBlobVS);			//! バイト・コードを解放
		throw L"CSprite::init バーテックスシェーダー作成失敗";
	}

	//! 頂点インプットレイアウトを定義	
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{
			"POSITION",						//! シグネチャ
			0,								//! 成分のセマンティック・インデックス番号
			DXGI_FORMAT_R32G32B32_FLOAT,	//! エレメントのフォーマット
			0,								//! 入力スロット番号
			0,								//! 先頭までのオフセット値（バイト数）
			D3D11_INPUT_PER_VERTEX_DATA,	//! 入力データは各頂点のデータ
			0								//! インスタンス毎の繰り返し回数
		},
		{
			"TEXCOORD",						//! シグネチャ
			0,								//! 成分のセマンティック・インデックス番号
			DXGI_FORMAT_R32G32_FLOAT,		//! エレメントのフォーマット
			0,								//! 入力スロット番号
			sizeof(XMFLOAT3),				//! 先頭までのオフセット値（バイト数）
			D3D11_INPUT_PER_VERTEX_DATA,	//! 入力データは各頂点のデータ
			0								//! インスタンス毎の繰り返し回数
		}
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);
	hr = pDevice_->CreateInputLayout(
		layout,
		numElements,
		pBlobVS->GetBufferPointer(),
		pBlobVS->GetBufferSize(),
		&m_pInputLayout);
	//! 頂点インプットレイアウトを作成
	if (FAILED(hr))
		throw L"CSprite::init 頂点インプットレイアウト作成失敗";

	//! ブロブからピクセルシェーダー作成
	hr = D3DX11CompileFromFile(
		hlslName_,	 //! ファイル名
		NULL,		 //! マクロ定義(なし)
		NULL,		 //! インクルード・ファイル定義(なし)
		"PS",		 //! 「PS関数」がシェーダから実行される
		"ps_5_0",	 //! ピクセル・シェーダ
		0,			 //! コンパイル・オプション
		0,			 //! エフェクトのコンパイル・オプション(なし)
		NULL,		 //! 直ぐにコンパイルしてから関数を抜ける。
		&pBlobVS,	 //! コンパイルされたバイト・コード
		&pErrors,	 //! エラーメッセージは不要
		NULL);
	SAFE_RELEASE(pErrors);
	if (FAILED(hr)) //! 戻り値
		throw L"CSprite HLSL (PS)読み込み失敗";

	//! ピクセル・シェーダの作成
	hr = pDevice_->CreatePixelShader(
		pBlobVS->GetBufferPointer(),	//! バイト・コードへのポインタ
		pBlobVS->GetBufferSize(),		//! バイト・コードの長さ
		NULL,
		&m_pPixelShader);				//! ピクセル・シェーダを受け取る変数
	SAFE_RELEASE(pBlobVS);				//! バイト・コードを解放
	if (FAILED(hr))
		throw L"CSprite::init ピクセルシェーダー作成失敗";

	//! バーテックスバッファー作成
	m_VBLeftTop		= { 0.0f - (size_.x / 2.0f), 0.0f - (size_.y / 2.0f) };
	m_VBRightBottom = { 0.0f + (size_.x / 2.0f), 0.0f + (size_.y / 2.0f) };
	for (size_t i = 0; i < uvArray_.size(); i++)
	{
		VertexWithTex<XMFLOAT3> vertices[] =
		{
			{ XMFLOAT3(m_VBLeftTop.x,		m_VBLeftTop.y,		0),uvArray_[i].v1 },	//! 頂点1
			{ XMFLOAT3(m_VBLeftTop.x,		m_VBRightBottom.y,	0),uvArray_[i].v2 },	//! 頂点2
			{ XMFLOAT3(m_VBRightBottom.x,	m_VBLeftTop.y,		0),uvArray_[i].v3 },	//! 頂点3
			{ XMFLOAT3(m_VBRightBottom.x,	m_VBRightBottom.y,	0),uvArray_[i].v4 }		//! 頂点4	
		};

		D3D11_BUFFER_DESC bd;
		bd.Usage = D3D11_USAGE_DYNAMIC; //! D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(VertexWithTex<XMFLOAT3>) * 4;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; //! 0
		bd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA initData;
		ID3D11Buffer*		pVB;
		initData.pSysMem = vertices;
		if (FAILED(pDevice_->CreateBuffer(&bd, &initData, &pVB)))
		{
			throw L"CSprite::init 頂点バッファ作成失敗";
		}
		m_pVBArray.push_back(pVB);
	}

	//! テクスチャー用サンプラー作成
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(D3D11_SAMPLER_DESC));

	samplerDesc.Filter		= D3D11_FILTER_ANISOTROPIC; //! D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.AddressU	= D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV	= D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW	= D3D11_TEXTURE_ADDRESS_WRAP;

	samplerDesc.MipLODBias		= 0.0f;
	samplerDesc.MaxAnisotropy	= 2;
	samplerDesc.ComparisonFunc	= D3D11_COMPARISON_NEVER;
	samplerDesc.BorderColor[0]	= 0.0f;
	samplerDesc.BorderColor[1]	= 0.0f;
	samplerDesc.BorderColor[2]	= 0.0f;
	samplerDesc.BorderColor[3]	= 0.0f;
	samplerDesc.MinLOD			= -FLT_MAX;
	samplerDesc.MaxLOD			=  FLT_MAX;

	pDevice_->CreateSamplerState(&samplerDesc, &m_pSampleLinear);

	//! テクスチャー作成
	hr = D3DX11CreateShaderResourceViewFromFile(pDevice_, textureName_, NULL, NULL, &m_pTexture, NULL);
	if (FAILED(hr))
		throw L"CSprite::init テクスチャー作成失敗";

	//! コンスタントバッファー作成　ここでは変換行列渡し用
	D3D11_BUFFER_DESC cb;
	cb.Usage			= D3D11_USAGE_DYNAMIC;			 //! 動的(ダイナミック)使用法
	cb.BindFlags		= D3D11_BIND_CONSTANT_BUFFER;	 //! 定数バッファ
	cb.CPUAccessFlags	= D3D11_CPU_ACCESS_WRITE;		 //! CPUから書き込む
	cb.MiscFlags		= 0;
	cb.StructureByteStride = 0;

	//! 定数バッファの作成
	cb.ByteWidth		= sizeof(ShaderGlobal_0);		 //! バッファ・サイズ
	hr = pDevice_->CreateBuffer(&cb, NULL, &m_pConstantBuffer);
	if (FAILED(hr))
		throw L"CSprite::init 定数バッファ作成失敗";
}

void CSprite::computePosition (void)
{
	XMMATRIX scale	= XMMatrixScaling(m_position.scale, m_position.scale, m_position.scale);
	XMMATRIX pitch	= XMMatrixRotationX(XMConvertToRadians(m_position.pitch));
	XMMATRIX yaw	= XMMatrixRotationY(XMConvertToRadians(m_position.yaw));
	XMMATRIX roll	= XMMatrixRotationZ(XMConvertToRadians(m_position.roll));
	XMMATRIX trans	= XMMatrixTranslation(getPos().x, getPos().y, getPos().z);
	XMMATRIX finalWorld = scale * pitch * yaw * roll * trans;

	XMStoreFloat4x4(&m_matScale,	scale);
	XMStoreFloat4x4(&m_matPitch,	pitch);
	XMStoreFloat4x4(&m_matYaw,		yaw);
	XMStoreFloat4x4(&m_matRoll,		roll);
	XMStoreFloat4x4(&m_matTran,		trans);
	XMStoreFloat4x4(&m_mFinalWorld,	finalWorld);
}

void CSprite::render(
	XMFLOAT4X4	matView_,
	XMFLOAT4X4	matProj_,
	size_t		uvIndex_,
	XMFLOAT4	diffuse_)
{
	if (!m_active)
	{
		return;
	}
	computePosition ();

	//! シェーダー　定数バッファ
	D3D11_MAPPED_SUBRESOURCE pData;
	if (SUCCEEDED (m_pDeviceContext->Map (
		m_pConstantBuffer,		 //! マップするリソース
		0,						 //! サブリソースのインデックス番号
		D3D11_MAP_WRITE_DISCARD, //! 書き込みアクセス
		0,
		&pData)))				 //! データの書き込み先ポインタ
	{
		ShaderGlobal_0 sg;
		XMStoreFloat4x4 (&sg.matWVP, XMLoadFloat4x4(&m_mFinalWorld) * XMLoadFloat4x4 (&matView_) * XMLoadFloat4x4 (&matProj_));
		XMStoreFloat4x4 (&sg.matWVP, XMMatrixTranspose (XMLoadFloat4x4(&sg.matWVP)));
		sg.diffuse = diffuse_;
		memcpy_s (pData.pData, pData.RowPitch, (void*)&sg, sizeof (ShaderGlobal_0));

		m_pDeviceContext->Unmap (m_pConstantBuffer, 0);
	}

	//! 頂点インプットレイアウトをセット
	m_pDeviceContext->IASetInputLayout (m_pInputLayout);
	//! プリミティブ・トポロジーをセット
	m_pDeviceContext->IASetPrimitiveTopology (D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//! バーテックスバッファーをセット
	UINT stride = sizeof (VertexWithTex<XMFLOAT3>);
	UINT offset = 0;
	m_pDeviceContext->IASetVertexBuffers (0, 1, &m_pVBArray[uvIndex_], &stride, &offset);

	//! 使用するシェーダーの登録　（effectの”テクニック”に相当）
	m_pDeviceContext->VSSetShader(m_pVertexShader, NULL, 0);
	//! VSに定数バッファを設定
	m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	//! RSにビューポートを設定
	m_pDeviceContext->RSSetViewports(1, m_viewPort);

	//! PSにピクセル・シェーダを設定
	m_pDeviceContext->PSSetShader(m_pPixelShader, NULL, 0);
	m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer); //! PSに定数バッファを設定

	//! テクスチャーをシェーダーに渡す
	m_pDeviceContext->PSSetSamplers(0, 1, &m_pSampleLinear); //! PSにサンプラーを設定
	m_pDeviceContext->PSSetShaderResources(
		0,				//! 設定する最初のスロット番号
		1,				//! 設定するシェーダ・リソース・ビューの数
		&m_pTexture);	//! 設定するシェーダ・リソース・ビューの配列

	//! プリミティブをレンダリング
	m_pDeviceContext->Draw(4, 0);
}

BOOL CSprite::collision(XMFLOAT4 pos_, FLOAT range_)
{
	if (isInvalid())
	{
		return FALSE;
	}
	return collision(pos_, getPos(), range_);
}

BOOL CSprite::collision(XMFLOAT4 pos1_, XMFLOAT4 pos2_, FLOAT range_)
{
	if (isInvalid())
	{
		return FALSE;
	}
	FLOAT dist2 =
		(pos1_.x - pos2_.x) * (pos1_.x - pos2_.x) +
		(pos1_.y - pos2_.y) * (pos1_.y - pos2_.y) +
		(pos1_.z - pos2_.z) * (pos1_.z - pos2_.z);

	return dist2 <= (range_ * range_);
}

void CSprite::release(void)
{
	//! 必ず生成したのと逆の順番でリリース
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pSampleLinear);
	SAFE_RELEASE(m_pConstantBuffer);
	SAFE_RELEASE(m_pVertexShader);
	SAFE_RELEASE(m_pPixelShader);
	for (size_t i = 0; i < m_pVBArray.size(); i++)
	{
		SAFE_RELEASE(m_pVBArray[i]);
	}
	SAFE_RELEASE(m_pInputLayout);
}