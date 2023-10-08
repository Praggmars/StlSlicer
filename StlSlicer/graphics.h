#pragma once

#include <d2d1_3.h>
#include <d3d11_4.h>
#include "math/position.hpp"
#include "model.h"

#include <wrl.h>
using Microsoft::WRL::ComPtr;

void ThrowIfFailed(HRESULT result, const char* message = "Unknown error");

struct ShaderData
{
	mth::float4x4 worldMatrix;
	mth::float4x4 cameraMatrix;
	mth::float3 eye;
	float ambient;
};

class Graphics
{
	ComPtr<ID3D11Device> m_device3D;
	ComPtr<ID3D11DeviceContext> m_context3D;
	ComPtr<IDXGISwapChain> m_swapChain;
	ComPtr<ID3D11RenderTargetView> m_renderTargetView;
	ComPtr<ID3D11DepthStencilView> m_depthStencilView;
	ComPtr<ID3D11DepthStencilState> m_depthStencilState;
	ComPtr<ID3D11RasterizerState> m_rasterizerState;
	D3D11_VIEWPORT m_viewport;
	ComPtr<ID3D11InputLayout> m_inputLayout;
	ComPtr<ID3D11VertexShader> m_vertexShader;
	ComPtr<ID3D11PixelShader> m_pixelShader;
	ComPtr<ID3D11Buffer> m_shaderConstBuffer;
	ComPtr<ID2D1Device> m_device2D;
	ComPtr<ID2D1DeviceContext> m_context2D;
	ComPtr<ID2D1Bitmap1> m_targetBitmap;

	ComPtr<ID3D11Buffer> m_plainVertexBuffer;
	UINT m_plainVertexCount;
	ComPtr<ID3D11Buffer> m_modelVertexBuffer;
	UINT m_modelVertexCount;

private:
	void CreatePlain();
	void RenderGeometry(const ShaderData& shaderData, ID3D11Buffer* vertexBuffer, unsigned vertexCount, D3D11_PRIMITIVE_TOPOLOGY topology) const;

public:
	Graphics();

	void Init(HWND target);
	void Resize(int width, int height);
	void BeginDraw() const;
	void EndDraw() const;

	void RenderPlain(const ShaderData& shaderData) const;

	void LoadModel(const Vertex* vertices, unsigned vertexCount);
	void RenderModel(const ShaderData& shaderData) const;

	ComPtr<ID2D1SolidColorBrush> CreateBrush(mth::float4 color) const;

	inline ID3D11Device* Device3D() const { return m_device3D.Get(); }
	inline ID3D11DeviceContext* Context3D() const { return m_context3D.Get(); }
	inline ID2D1Device* Device2D() const { return m_device2D.Get(); }
	inline ID2D1DeviceContext* Context2D() const { return m_context2D.Get(); }
};