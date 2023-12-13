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
	void CreateGeometry();
	void CreateInputLayout();
	void CreateVS();
	void CreatePS();

	void CreateRasterizerState();
	void CreateSamplerState();
	void CreateBlendState();
 	void CreateSRV();

	void CreateConstantBuffer();

	void LoadShaderFromFile(const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob);

private:
	HWND _hwnd;
	Graphics* _graphics;
	

private:
	// Geometry
	vector<Vertex> _vertexes;
	VertexBuffer* _vertexBuffer;

	vector<uint32> _indexes;
	IndexBuffer* _indexBuffer;
	InputLayout* _inputLayout;

	// VS
	ComPtr<ID3D11VertexShader> _vertexShader;
	ComPtr<ID3DBlob> _vsBlob;

	// RS
	ComPtr<ID3D11RasterizerState> _rasterizerState;

	// PS
	ComPtr<ID3D11PixelShader> _pixelShader;
	ComPtr<ID3DBlob> _psBlob;

	// SRV
	ComPtr<ID3D11ShaderResourceView> _shaderResourceView;
	// [CPU <-> RAM] [GPU <-> VRAM]
	ComPtr<ID3D11SamplerState> _samplerState;
	ComPtr<ID3D11BlendState> _blendState;

private:
	// SRT
	TransformData _transformData;
	ComPtr<ID3D11Buffer> _constantBuffer;

	Vector3 _localPosition = { 0.f, 0.f, 0.f };
	Vector3 _localRotation = { 0.f, 0.f, 0.f };
	Vector3 _localScale = { 1.f, 1.f, 1.f };
};