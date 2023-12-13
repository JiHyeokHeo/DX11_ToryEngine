#include "pch.h"
#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;
	
	//_graphics = make_shared<Graphics>(hwnd);
	_graphics = new Graphics(hwnd);
	_vertexBuffer = new VertexBuffer(_graphics->GetDevice()); 
	_indexBuffer = new IndexBuffer(_graphics->GetDevice());
	_inputLayout = new InputLayout(_graphics->GetDevice());

	CreateGeometry();
	CreateVS();
	CreateInputLayout();
	CreatePS();

	CreateRasterizerState();
	CreateSamplerState();
	CreateBlendState();

	CreateSRV();
	CreateConstantBuffer();
}

void Game::Update()
{
	Matrix matScale = Matrix::CreateScale(_localScale);
	Matrix matRotation = Matrix::CreateRotationX(_localRotation.x);
	matRotation *= Matrix::CreateRotationY(_localRotation.y);
	matRotation *= Matrix::CreateRotationZ(_localRotation.z);
	Matrix matTranslation = Matrix::CreateTranslation(_localPosition);

	Matrix matWorld = matScale * matRotation * matTranslation; // SRT
	_transformData.matWorld = matWorld;

	D3D11_MAPPED_SUBRESOURCE subResource;
	ZeroMemory(&subResource, sizeof(subResource));

	_graphics->GetDeviceContext()->Map(_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
	::memcpy(subResource.pData, &_transformData, sizeof(_transformData));  //CPU에서 GPU로 데이터 복사
	_graphics->GetDeviceContext()->Unmap(_constantBuffer.Get(), 0);
}

void Game::Render()
{
	_graphics->RenderBegin();
	{
		uint32 stride = sizeof(Vertex);
		uint32 offset = 0;
		auto _deviceContext = _graphics->GetDeviceContext();
		// IA
		_deviceContext->IASetVertexBuffers(0, 1, _vertexBuffer->GetComPtr().GetAddressOf(), &stride, &offset);
		_deviceContext->IASetIndexBuffer(_indexBuffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);
		_deviceContext->IASetInputLayout(_inputLayout->GetComPtr().Get());
		_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		
		// VS
		_deviceContext->VSSetShader(_vertexShader.Get(), nullptr, 0);
		_deviceContext->VSSetConstantBuffers(0, 1, _constantBuffer.GetAddressOf());
		
		// RS
		_deviceContext->RSSetState(_rasterizerState.Get());


		// PS
		_deviceContext->PSSetShader(_pixelShader.Get(), nullptr, 0);
		_deviceContext->PSSetShaderResources(0, 1, _shaderResourceView.GetAddressOf());
		_deviceContext->PSSetSamplers(0, 1, _samplerState.GetAddressOf());

		// OM
		_deviceContext->OMSetBlendState(_blendState.Get(), nullptr, 0xFFFFFFFF);
		//_deviceContext->Draw(_vertexes.size(), 0);
		_deviceContext->DrawIndexed(_indexes.size(), 0, 0);
	}

	_graphics->RenderEnd();
}

void Game::CreateGeometry()
{
	// VertexData
	{
		_vertexes.resize(4);
		
		// 1 3
		// 0 2
		_vertexes[0].position = Vector3(-0.5f, -0.5f, 0.f);
		_vertexes[0].uv = Vector2(0.f, 1.f);
		//_vertexes[0].color = Color(1.f, 0.f, 0.f, 1.f);
		
		_vertexes[1].position = Vector3(-0.5f, 0.5f, 0.f);
		_vertexes[1].uv = Vector2(0.f, 0.f);
		//_vertexes[1].color = Color(1.f, 0.f, 0.f, 1.f);

		_vertexes[2].position = Vector3(0.5f, -0.5f, 0.f);
		_vertexes[2].uv = Vector2(1.f, 1.f);
		//_vertexes[2].color = Color(1.f, 0.f, 0.f, 1.f);

		_vertexes[3].position = Vector3(0.5f, 0.5f, 0.f);
		_vertexes[3].uv = Vector2(1.f, 0.f);
		//_vertexes[3].color = Color(1.f, 0.f, 0.f, 1.f);
	}

	// VertexBuffer
	{
		_vertexBuffer->Create(_vertexes);
	}

	// Index
		// 1 3
		// 0 2
	{
		_indexes.resize(6);
		_indexes.push_back(0);
		_indexes.push_back(1);
		_indexes.push_back(2);

		_indexes.push_back(2);
		_indexes.push_back(1);
		_indexes.push_back(3);
	}

	// IndexBuffer
	{
		_indexBuffer->Create(_indexes);
	}
}

void Game::CreateInputLayout()
{
	vector<D3D11_INPUT_ELEMENT_DESC> layout =
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT, 0,0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT, 0,12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};

	_inputLayout->Create(layout, _vsBlob);
}

void Game::CreateVS()
{
	LoadShaderFromFile(L"Default.hlsl", "VS", "vs_5_0", _vsBlob);
	HRESULT hr = _graphics->GetDevice()->CreateVertexShader(_vsBlob->GetBufferPointer(), _vsBlob->GetBufferSize(), nullptr, _vertexShader.GetAddressOf());
	assert(SUCCEEDED(hr));
}

void Game::CreatePS()
{
	LoadShaderFromFile(L"Default.hlsl", "PS", "ps_5_0", _psBlob);
	HRESULT hr = _graphics->GetDevice()->CreatePixelShader(_psBlob->GetBufferPointer(), _psBlob->GetBufferSize(), nullptr, _pixelShader.GetAddressOf());
	assert(SUCCEEDED(hr));
}

void Game::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.FillMode = D3D11_FILL_SOLID;
	desc.CullMode = D3D11_CULL_BACK;
	desc.FrontCounterClockwise = false;

	HRESULT hr = _graphics->GetDevice()->CreateRasterizerState(&desc, _rasterizerState.GetAddressOf());
	assert(SUCCEEDED(hr));
}

void Game::CreateSamplerState()
{
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.BorderColor[0] = 1;
	desc.BorderColor[1] = 0;
	desc.BorderColor[2] = 0;
	desc.BorderColor[3] = 1;
	desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;

	_graphics->GetDevice()->CreateSamplerState(&desc, _samplerState.GetAddressOf());
}

void Game::CreateBlendState()
{
	D3D11_BLEND_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AlphaToCoverageEnable = false;
	desc.IndependentBlendEnable = false;
	desc.RenderTarget[0].BlendEnable = true;
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	_graphics->GetDevice()->CreateBlendState(&desc, _blendState.GetAddressOf());
}

void Game::CreateSRV()
{
	DirectX::TexMetadata md;
	DirectX::ScratchImage img;
	HRESULT hr = ::LoadFromWICFile(L"Skeleton.png", WIC_FLAGS_NONE, &md, img);
	assert(SUCCEEDED(hr));

	hr = ::CreateShaderResourceView(_graphics->GetDevice().Get(), img.GetImages(), img.GetImageCount(), md, _shaderResourceView.GetAddressOf());
	assert(SUCCEEDED(hr));
}

void Game::CreateConstantBuffer()
{
	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Usage = D3D11_USAGE_DYNAMIC; // CPU_ WRITE + GPU_ READ
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	desc.ByteWidth = sizeof(TransformData);
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; // CPU 접근 가능

	HRESULT hr = _graphics->GetDevice()->CreateBuffer(&desc, nullptr, _constantBuffer.GetAddressOf());
	assert(SUCCEEDED(hr));
}

void Game::LoadShaderFromFile(const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob)
{
	const uint32 compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;

	HRESULT hr = ::D3DCompileFromFile(
		path.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		name.c_str(),
		version.c_str(),
		compileFlag,
		0,
		blob.GetAddressOf(),
		nullptr
	);
	assert(SUCCEEDED(hr));
}
