/**
* @file Sprite.cpp
* @brief �e�N�X�`���t���̃|���S���E�N���X����
* @author EtuCho
* @date �쐬��2018_02_04
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
* @brief ������
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
	m_pDeviceContext	= pDeviceContext_;	//! �����_�����O�ɕK�v�@�����s���ɕω����Ȃ���
	m_viewPort[0]		= viewPort_[0];		//! �����_�����O�ɕK�v�@�����s���ɕω����Ȃ���
	m_baseSize			= size_;
	m_VBSize			= size_;
	m_active			= TRUE;
	m_position.setup({ position_.x, position_.y, position_.z, 0.0f }, 0.0f, 0.0f, 0.0f, 1.0f);	//�ʒu

	//hlsl�t�@�C���ǂݍ��� �u���u�쐬�@�u���u�Ƃ̓V�F�[�_�[�̉�݂����Ȃ��́BXX�V�F�[�_�[�Ƃ��ē����������Ȃ��B��Ŋe��V�F�[�_�[�ɐ��蓾��B
	ID3DBlob *pBlobVS = NULL;
	ID3DBlob *pErrors = NULL;

	//! �u���u����o�[�e�b�N�X�V�F�[�_�[�쐬
	hr = D3DX11CompileFromFile(
		hlslName_,		 //! �t�@�C����
		NULL,			 //! �}�N����`(�Ȃ�)
		NULL,			 //! �C���N���[�h�E�t�@�C����`(�Ȃ�)
		"VS",			 //! �uVS�֐��v���V�F�[�_������s�����
		"vs_5_0",		 //! ���_�V�F�[�_
		0,				 //! �R���p�C���E�I�v�V����
		0,				 //! �G�t�F�N�g�̃R���p�C���E�I�v�V����(�Ȃ�)
		NULL,			 //! �����ɃR���p�C�����Ă���֐��𔲂���B
		&pBlobVS,		 //! �R���p�C�����ꂽ�o�C�g�E�R�[�h
		&pErrors,		 //! �G���[���b�Z�[�W
		NULL);			 //! �߂�l
	if (FAILED(hr))
	{
		throw L"CSprite::init HLSL (VS)�ǂݍ��ݎ��s";
	}
	SAFE_RELEASE(pErrors);
	hr = pDevice_->CreateVertexShader(
		pBlobVS->GetBufferPointer(),	//! �o�C�g�E�R�[�h�ւ̃|�C���^
		pBlobVS->GetBufferSize(),		//! �o�C�g�E�R�[�h�̒���
		NULL,
		&m_pVertexShader);				//! ���_�V�F�[�_���󂯎��ϐ�
	if (FAILED(hr))
	{
		SAFE_RELEASE(pBlobVS);			//! �o�C�g�E�R�[�h�����
		throw L"CSprite::init �o�[�e�b�N�X�V�F�[�_�[�쐬���s";
	}

	//! ���_�C���v�b�g���C�A�E�g���`	
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{
			"POSITION",						//! �V�O�l�`��
			0,								//! �����̃Z�}���e�B�b�N�E�C���f�b�N�X�ԍ�
			DXGI_FORMAT_R32G32B32_FLOAT,	//! �G�������g�̃t�H�[�}�b�g
			0,								//! ���̓X���b�g�ԍ�
			0,								//! �擪�܂ł̃I�t�Z�b�g�l�i�o�C�g���j
			D3D11_INPUT_PER_VERTEX_DATA,	//! ���̓f�[�^�͊e���_�̃f�[�^
			0								//! �C���X�^���X���̌J��Ԃ���
		},
		{
			"TEXCOORD",						//! �V�O�l�`��
			0,								//! �����̃Z�}���e�B�b�N�E�C���f�b�N�X�ԍ�
			DXGI_FORMAT_R32G32_FLOAT,		//! �G�������g�̃t�H�[�}�b�g
			0,								//! ���̓X���b�g�ԍ�
			sizeof(XMFLOAT3),				//! �擪�܂ł̃I�t�Z�b�g�l�i�o�C�g���j
			D3D11_INPUT_PER_VERTEX_DATA,	//! ���̓f�[�^�͊e���_�̃f�[�^
			0								//! �C���X�^���X���̌J��Ԃ���
		}
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);
	hr = pDevice_->CreateInputLayout(
		layout,
		numElements,
		pBlobVS->GetBufferPointer(),
		pBlobVS->GetBufferSize(),
		&m_pInputLayout);
	//! ���_�C���v�b�g���C�A�E�g���쐬
	if (FAILED(hr))
		throw L"CSprite::init ���_�C���v�b�g���C�A�E�g�쐬���s";

	//! �u���u����s�N�Z���V�F�[�_�[�쐬
	hr = D3DX11CompileFromFile(
		hlslName_,	 //! �t�@�C����
		NULL,		 //! �}�N����`(�Ȃ�)
		NULL,		 //! �C���N���[�h�E�t�@�C����`(�Ȃ�)
		"PS",		 //! �uPS�֐��v���V�F�[�_������s�����
		"ps_5_0",	 //! �s�N�Z���E�V�F�[�_
		0,			 //! �R���p�C���E�I�v�V����
		0,			 //! �G�t�F�N�g�̃R���p�C���E�I�v�V����(�Ȃ�)
		NULL,		 //! �����ɃR���p�C�����Ă���֐��𔲂���B
		&pBlobVS,	 //! �R���p�C�����ꂽ�o�C�g�E�R�[�h
		&pErrors,	 //! �G���[���b�Z�[�W�͕s�v
		NULL);
	SAFE_RELEASE(pErrors);
	if (FAILED(hr)) //! �߂�l
		throw L"CSprite HLSL (PS)�ǂݍ��ݎ��s";

	//! �s�N�Z���E�V�F�[�_�̍쐬
	hr = pDevice_->CreatePixelShader(
		pBlobVS->GetBufferPointer(),	//! �o�C�g�E�R�[�h�ւ̃|�C���^
		pBlobVS->GetBufferSize(),		//! �o�C�g�E�R�[�h�̒���
		NULL,
		&m_pPixelShader);				//! �s�N�Z���E�V�F�[�_���󂯎��ϐ�
	SAFE_RELEASE(pBlobVS);				//! �o�C�g�E�R�[�h�����
	if (FAILED(hr))
		throw L"CSprite::init �s�N�Z���V�F�[�_�[�쐬���s";

	//! �o�[�e�b�N�X�o�b�t�@�[�쐬
	m_VBLeftTop		= { 0.0f - (size_.x / 2.0f), 0.0f - (size_.y / 2.0f) };
	m_VBRightBottom = { 0.0f + (size_.x / 2.0f), 0.0f + (size_.y / 2.0f) };
	for (size_t i = 0; i < uvArray_.size(); i++)
	{
		VertexWithTex<XMFLOAT3> vertices[] =
		{
			{ XMFLOAT3(m_VBLeftTop.x,		m_VBLeftTop.y,		0),uvArray_[i].v1 },	//! ���_1
			{ XMFLOAT3(m_VBLeftTop.x,		m_VBRightBottom.y,	0),uvArray_[i].v2 },	//! ���_2
			{ XMFLOAT3(m_VBRightBottom.x,	m_VBLeftTop.y,		0),uvArray_[i].v3 },	//! ���_3
			{ XMFLOAT3(m_VBRightBottom.x,	m_VBRightBottom.y,	0),uvArray_[i].v4 }		//! ���_4	
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
			throw L"CSprite::init ���_�o�b�t�@�쐬���s";
		}
		m_pVBArray.push_back(pVB);
	}

	//! �e�N�X�`���[�p�T���v���[�쐬
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

	//! �e�N�X�`���[�쐬
	hr = D3DX11CreateShaderResourceViewFromFile(pDevice_, textureName_, NULL, NULL, &m_pTexture, NULL);
	if (FAILED(hr))
		throw L"CSprite::init �e�N�X�`���[�쐬���s";

	//! �R���X�^���g�o�b�t�@�[�쐬�@�����ł͕ϊ��s��n���p
	D3D11_BUFFER_DESC cb;
	cb.Usage			= D3D11_USAGE_DYNAMIC;			 //! ���I(�_�C�i�~�b�N)�g�p�@
	cb.BindFlags		= D3D11_BIND_CONSTANT_BUFFER;	 //! �萔�o�b�t�@
	cb.CPUAccessFlags	= D3D11_CPU_ACCESS_WRITE;		 //! CPU���珑������
	cb.MiscFlags		= 0;
	cb.StructureByteStride = 0;

	//! �萔�o�b�t�@�̍쐬
	cb.ByteWidth		= sizeof(ShaderGlobal_0);		 //! �o�b�t�@�E�T�C�Y
	hr = pDevice_->CreateBuffer(&cb, NULL, &m_pConstantBuffer);
	if (FAILED(hr))
		throw L"CSprite::init �萔�o�b�t�@�쐬���s";
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

	//! �V�F�[�_�[�@�萔�o�b�t�@
	D3D11_MAPPED_SUBRESOURCE pData;
	if (SUCCEEDED (m_pDeviceContext->Map (
		m_pConstantBuffer,		 //! �}�b�v���郊�\�[�X
		0,						 //! �T�u���\�[�X�̃C���f�b�N�X�ԍ�
		D3D11_MAP_WRITE_DISCARD, //! �������݃A�N�Z�X
		0,
		&pData)))				 //! �f�[�^�̏������ݐ�|�C���^
	{
		ShaderGlobal_0 sg;
		XMStoreFloat4x4 (&sg.matWVP, XMLoadFloat4x4(&m_mFinalWorld) * XMLoadFloat4x4 (&matView_) * XMLoadFloat4x4 (&matProj_));
		XMStoreFloat4x4 (&sg.matWVP, XMMatrixTranspose (XMLoadFloat4x4(&sg.matWVP)));
		sg.diffuse = diffuse_;
		memcpy_s (pData.pData, pData.RowPitch, (void*)&sg, sizeof (ShaderGlobal_0));

		m_pDeviceContext->Unmap (m_pConstantBuffer, 0);
	}

	//! ���_�C���v�b�g���C�A�E�g���Z�b�g
	m_pDeviceContext->IASetInputLayout (m_pInputLayout);
	//! �v���~�e�B�u�E�g�|���W�[���Z�b�g
	m_pDeviceContext->IASetPrimitiveTopology (D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	//! �o�[�e�b�N�X�o�b�t�@�[���Z�b�g
	UINT stride = sizeof (VertexWithTex<XMFLOAT3>);
	UINT offset = 0;
	m_pDeviceContext->IASetVertexBuffers (0, 1, &m_pVBArray[uvIndex_], &stride, &offset);

	//! �g�p����V�F�[�_�[�̓o�^�@�ieffect�́h�e�N�j�b�N�h�ɑ����j
	m_pDeviceContext->VSSetShader(m_pVertexShader, NULL, 0);
	//! VS�ɒ萔�o�b�t�@��ݒ�
	m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	//! RS�Ƀr���[�|�[�g��ݒ�
	m_pDeviceContext->RSSetViewports(1, m_viewPort);

	//! PS�Ƀs�N�Z���E�V�F�[�_��ݒ�
	m_pDeviceContext->PSSetShader(m_pPixelShader, NULL, 0);
	m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer); //! PS�ɒ萔�o�b�t�@��ݒ�

	//! �e�N�X�`���[���V�F�[�_�[�ɓn��
	m_pDeviceContext->PSSetSamplers(0, 1, &m_pSampleLinear); //! PS�ɃT���v���[��ݒ�
	m_pDeviceContext->PSSetShaderResources(
		0,				//! �ݒ肷��ŏ��̃X���b�g�ԍ�
		1,				//! �ݒ肷��V�F�[�_�E���\�[�X�E�r���[�̐�
		&m_pTexture);	//! �ݒ肷��V�F�[�_�E���\�[�X�E�r���[�̔z��

	//! �v���~�e�B�u�������_�����O
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
	//! �K�����������̂Ƌt�̏��ԂŃ����[�X
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