#pragma once

class Game
{
public:
	Game();
	~Game();

public:
	void Init(HWND hwnd);
	void Update();
	void Render();

private:
	void RenderBegin();
	void RenderEnd();

private:
	// 후면 버퍼 제작
	void CreateDeviceAndSwapChain();
	// 후면 버퍼에 요청
	void CreateRenderTargetView();
	void SetViewPort();

private:
	void CreateGeometry();
	void CreateInputLayout();

	void CreateVS();
	void CreatePS();

	void CreateSRV();


	void LoadShaderFromFile(const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob);

	
private:
	HWND _hwnd;
	uint32 _width = 0;
	uint32 _height = 0;

private:
	// Device & SwapChain
	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11DeviceContext> _deviceContext;
	ComPtr<IDXGISwapChain> _swapChain;

	// RTV (렌더타겟뷰)
	ComPtr<ID3D11RenderTargetView> _renderTargetView;

	// Misc
	D3D11_VIEWPORT _viewport = {0};
	float _clearColor[4] = { 0.f, 0.f, 0.f, 0.f };

private:
	// Geometry
	std::vector<Vertex> _vertexes;
	ComPtr<ID3D11Buffer> _vertexBuffer;
	vector<uint32> _indexes;
	ComPtr<ID3D11InputLayout> _inputLayerout;
	ComPtr<ID3D11Buffer> _indexBuffer;

	// VS
	ComPtr<ID3D11VertexShader> _vertexShader;
	ComPtr<ID3DBlob> _vsBlob;

	// PS
	ComPtr<ID3D11PixelShader> _pixelShader;
	ComPtr<ID3DBlob> _psBlob;

	// SRV
	ComPtr<ID3D11ShaderResourceView> _shaderResourceView;
	// [CPU <-> RAM] [GPU <-> VRAM]
};