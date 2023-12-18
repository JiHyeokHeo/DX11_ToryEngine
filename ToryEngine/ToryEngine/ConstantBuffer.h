#pragma once

template<typename T>
class ConstantBuffer
{
public:
	ConstantBuffer(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> deviceContext)
		: _device(device), _deviceContext(deviceContext)
	{

	}

	~ConstantBuffer() {};

	ComPtr<ID3D11Buffer> GetComPtr() { return _transformBuffer; }

	void Create()
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Usage = D3D11_USAGE_DYNAMIC; // CPU_ WRITE + GPU_ READ
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		desc.ByteWidth = sizeof(T);
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; // CPU 접근 가능

		HRESULT hr = _device->CreateBuffer(&desc, nullptr, _transformBuffer.GetAddressOf());
		assert(SUCCEEDED(hr));
	}

	void CopyData(const T& data)
	{
		D3D11_MAPPED_SUBRESOURCE subResource;
		ZeroMemory(&subResource, sizeof(subResource));

		_deviceContext->Map(_transformBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
		::memcpy(subResource.pData, &data, sizeof(data));  //CPU에서 GPU로 데이터 복사
		_deviceContext->Unmap(_transformBuffer.Get(), 0);
	}

private:
	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11DeviceContext> _deviceContext;
	ComPtr<ID3D11Buffer> _transformBuffer;
};

