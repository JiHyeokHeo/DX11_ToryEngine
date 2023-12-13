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


	void CreateRasterizerState();
	void CreateSamplerState();
	void CreateBlendState();


private:
	HWND _hwnd;

	shared_ptr<Graphics> _graphics;

private:
	shared_ptr<Geometry<VertexTextureData>> _geometry;
	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;
	shared_ptr<InputLayout> _inputLayout;

	// VS
	shared_ptr<VertexShader> _vertexShader; 

	// RS
	ComPtr<ID3D11RasterizerState> _rasterizerState;

	// PS
	shared_ptr<PixelShader> _pixelShader;

	shared_ptr<Texture> _texture1;

	// [CPU <-> RAM] [GPU <-> VRAM]
	ComPtr<ID3D11SamplerState> _samplerState;
	ComPtr<ID3D11BlendState> _blendState;

private:
	// SRT
	TransformData _transformData;
	shared_ptr<ConstantBuffer<TransformData>> _constantBuffer;

	Vector3 _localPosition = { 0.f, 0.f, 0.f };
	Vector3 _localRotation = { 0.f, 0.f, 0.f };
	Vector3 _localScale = { 1.f, 1.f, 1.f };
};