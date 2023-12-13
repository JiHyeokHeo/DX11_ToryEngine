#include "pch.h"
#include "Graphics.h"

Graphics::Graphics(HWND hwnd)
{
	_hwnd = hwnd;

	CreateDeviceAndSwapChain();
	CreateRenderTargetView();
	SetViewPort();
}

Graphics::~Graphics()
{
}

void Graphics::RenderBegin()
{	
	// OutputMerger
	_deviceContext->OMSetRenderTargets(1, _renderTargetView.GetAddressOf(), nullptr);
	_deviceContext->ClearRenderTargetView(_renderTargetView.Get(), _clearColor);
	_deviceContext->RSSetViewports(1, &_viewport);
}

void Graphics::RenderEnd()
{
	HRESULT hr = _swapChain->Present(1, 0);
	assert(SUCCEEDED(hr));
}

void Graphics::CreateDeviceAndSwapChain()
{
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	{
		desc.BufferDesc.Width = GloWinSizeX;
		desc.BufferDesc.Height = GloWinSizeY;
		desc.BufferDesc.RefreshRate.Numerator = 60;
		desc.BufferDesc.RefreshRate.Denominator = 1;
		desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.BufferCount = 1;
		desc.OutputWindow = _hwnd;
		desc.Windowed = true;
		desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	}

	HRESULT hr = ::D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&desc,
		_swapChain.GetAddressOf(),
		_device.GetAddressOf(),
		nullptr,
		_deviceContext.GetAddressOf()
	);

	assert(SUCCEEDED(hr));
}

void Graphics::CreateRenderTargetView()
{
	HRESULT hr;

	ComPtr<ID3D11Texture2D> backBuffer = nullptr;
	hr = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)backBuffer.GetAddressOf());
	assert(SUCCEEDED(hr));

	hr = _device->CreateRenderTargetView(backBuffer.Get(), nullptr, _renderTargetView.GetAddressOf());
	assert(SUCCEEDED(hr));
}

void Graphics::SetViewPort()
{
	_viewport.TopLeftX = 0.f;
	_viewport.TopLeftY = 0.f;
	_viewport.Width = static_cast<float>(GloWinSizeX);
	_viewport.Height = static_cast<float>(GloWinSizeY);
	_viewport.MinDepth = 0.f;
	_viewport.MaxDepth = 1.f;
}
