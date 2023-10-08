#include "graphics.h"
#include <d3dcompiler.h>
#include <vector>
#include <stdexcept>
#include <fstream>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d2d1.lib")
#pragma comment (lib, "dxgi.lib")
#pragma comment (lib, "d3dcompiler.lib")


void ThrowIfFailed(HRESULT result, const char* message)
{
	if (FAILED(result))
		throw std::runtime_error(message);
}

#if 1
#define SAMPLE_COUNT (4)
#define SAMPLE_QUALITY(format) (m_device3D->CheckMultisampleQualityLevels(format, SAMPLE_COUNT, &msaaQuality), msaaQuality - 1)
#else
#define SAMPLE_COUNT (1)
#define SAMPLE_QUALITY(format) (0)
#endif

void Graphics::CreatePlain()
{
	constexpr int lineCount = 11;
	Vertex vertices[lineCount * 4];
	for (int i = 0; i < lineCount; ++i)
	{
		const float p = (static_cast<float>(1 - lineCount) * 0.5f + static_cast<float>(i)) / static_cast<float>(lineCount - 1);
		vertices[4 * i + 0].position = mth::float3(p, 0.0f,  0.5f);
		vertices[4 * i + 1].position = mth::float3(p, 0.0f, -0.5f);
		vertices[4 * i + 2].position = mth::float3( 0.5f, 0.0f, p);
		vertices[4 * i + 3].position = mth::float3(-0.5f, 0.0f, p);
	}
	for (Vertex& v : vertices)
		v.normal = mth::float3(0.0f, 1.0f, 0.0f);

	D3D11_BUFFER_DESC bufferDesc{};
	D3D11_SUBRESOURCE_DATA bufferData{};

	bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	bufferDesc.ByteWidth = sizeof(vertices);
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferData.pSysMem = vertices;
	ThrowIfFailed(m_device3D->CreateBuffer(&bufferDesc, &bufferData, &m_plainVertexBuffer), "Failed to create vertex buffer");
	m_plainVertexCount = ARRAYSIZE(vertices);
}

void Graphics::RenderGeometry(const ShaderData& shaderData, ID3D11Buffer* vertexBuffer, unsigned vertexCount, D3D11_PRIMITIVE_TOPOLOGY topology) const
{
	D3D11_MAPPED_SUBRESOURCE resource;
	if (SUCCEEDED(m_context3D->Map(m_shaderConstBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &resource)))
	{
		std::memcpy(resource.pData, &shaderData, sizeof(ShaderData));
		m_context3D->Unmap(m_shaderConstBuffer.Get(), 0);
	}
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	m_context3D->IASetPrimitiveTopology(topology);
	m_context3D->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	m_context3D->VSSetConstantBuffers(0, 1, m_shaderConstBuffer.GetAddressOf());
	m_context3D->PSSetConstantBuffers(0, 1, m_shaderConstBuffer.GetAddressOf());
	m_context3D->Draw(vertexCount, 0);
}

Graphics::Graphics()
	: m_viewport{}
	, m_plainVertexCount{}
	, m_modelVertexCount{} {}

void Graphics::Init(HWND target)
{
	// 3D device
	D3D_FEATURE_LEVEL featureLevels[] = {
		D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0
	};
	ThrowIfFailed(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_BGRA_SUPPORT, featureLevels, ARRAYSIZE(featureLevels), D3D11_SDK_VERSION, &m_device3D, nullptr, &m_context3D), "Failed to create D3D device");

	// Swapchain
	RECT rect;
	GetClientRect(target, &rect);

	ComPtr<IDXGIFactory> factory;
	ThrowIfFailed(CreateDXGIFactory(IID_PPV_ARGS(&factory)), "Failed to greate DXGI factory");

	UINT msaaQuality = 0;
	DXGI_SWAP_CHAIN_DESC swapChainDesc{};
	swapChainDesc.BufferCount = 2;
	swapChainDesc.BufferDesc.Width = max(1, rect.right);
	swapChainDesc.BufferDesc.Height = max(1, rect.bottom);
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = target;
	swapChainDesc.SampleDesc.Count = SAMPLE_COUNT;
	swapChainDesc.SampleDesc.Quality = SAMPLE_QUALITY(DXGI_FORMAT_B8G8R8A8_UNORM);
	swapChainDesc.Windowed = true;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;
	ThrowIfFailed(factory->CreateSwapChain(m_device3D.Get(), &swapChainDesc, &m_swapChain), "Failed to create swap chain");

	// 3D render target and depth buffer
	ComPtr<ID3D11Texture2D> backBufferTexture;
	ThrowIfFailed(m_swapChain->GetBuffer(0, IID_PPV_ARGS(&backBufferTexture)), "Failed to get back buffer texture");
	ThrowIfFailed(m_device3D->CreateRenderTargetView(backBufferTexture.Get(), nullptr, &m_renderTargetView), "Failed to create render target view");

	ComPtr<ID3D11Texture2D> depthBuffer;
	D3D11_TEXTURE2D_DESC depthBufferDesc{};
	depthBufferDesc.Width = swapChainDesc.BufferDesc.Width;
	depthBufferDesc.Height = swapChainDesc.BufferDesc.Height;
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc = swapChainDesc.SampleDesc;
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;
	ThrowIfFailed(m_device3D->CreateTexture2D(&depthBufferDesc, nullptr, &depthBuffer), "Failed to create depth buffer");
	ThrowIfFailed(m_device3D->CreateDepthStencilView(depthBuffer.Get(), nullptr, &m_depthStencilView));

	// Depth stencil state
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc{};
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	depthStencilDesc.StencilEnable = true;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	ThrowIfFailed(m_device3D->CreateDepthStencilState(&depthStencilDesc, &m_depthStencilState), "Failed to creaste depth stencil state");

	// Viewport
	m_viewport.TopLeftX = 0.0f;
	m_viewport.TopLeftY = 0.0f;
	m_viewport.Width = static_cast<float>(swapChainDesc.BufferDesc.Width) * 0.5f;
	m_viewport.Height = static_cast<float>(swapChainDesc.BufferDesc.Height);
	m_viewport.MinDepth = 0.0f;
	m_viewport.MaxDepth = 1.0f;

	// Rasterizer state
	D3D11_RASTERIZER_DESC rastDesc{};
	rastDesc.AntialiasedLineEnable = true;
	rastDesc.CullMode = D3D11_CULL_NONE;
	rastDesc.DepthBias = 0;
	rastDesc.DepthBiasClamp = 0.0f;
	rastDesc.DepthClipEnable = true;
	rastDesc.FrontCounterClockwise = false;
	rastDesc.MultisampleEnable = true;
	rastDesc.ScissorEnable = false;
	rastDesc.SlopeScaledDepthBias = 0.0f;
	rastDesc.FillMode = D3D11_FILL_SOLID;
	ThrowIfFailed(m_device3D->CreateRasterizerState(&rastDesc, &m_rasterizerState), "Failed to create rasterizer state");

	// Vertex shader
	static const char s_VsCode[] = R"(
cbuffer ShaderData
{
	matrix worldMatrix;
	matrix cameraMatrix;
	float3 eye;
	float ambient;
};
struct VertexShaderInput
{
	float4 position : POSITION;
	float3 normal : NORMAL;
};
struct PixelShaderInput
{
	float4 screenPosition : SV_POSITION;
	float3 position : POSITION;
	float3 normal : NORMAL;
};
PixelShaderInput main(VertexShaderInput input)
{
	PixelShaderInput output;
	output.screenPosition = mul(input.position, worldMatrix);
	output.position = output.screenPosition.xyz;
	output.screenPosition = mul(output.screenPosition, cameraMatrix);
	output.normal = mul(input.normal, (float3x3)worldMatrix);
	return output;
}
)";
	ComPtr<ID3DBlob> shaderCode;
	ComPtr<ID3DBlob> compileError;
	HRESULT hr = D3DCompile(s_VsCode, sizeof(s_VsCode) - 1, nullptr, nullptr, nullptr, "main", "vs_5_0", D3DCOMPILE_OPTIMIZATION_LEVEL2, 0, &shaderCode, &compileError);
	if (FAILED(hr))
	{
		if (compileError)
			OutputDebugStringA(reinterpret_cast<const char*>(compileError->GetBufferPointer()));
		ThrowIfFailed(hr, "Failed to compile vertex shader");
	}
	D3D11_INPUT_ELEMENT_DESC inputLayout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	ThrowIfFailed(m_device3D->CreateInputLayout(inputLayout, ARRAYSIZE(inputLayout), shaderCode->GetBufferPointer(), shaderCode->GetBufferSize(), &m_inputLayout), "Failed to create input layout");
	ThrowIfFailed(m_device3D->CreateVertexShader(shaderCode->GetBufferPointer(), shaderCode->GetBufferSize(), nullptr, &m_vertexShader), "Failed to create vertex shader");

	// Pixel shader
	static const char s_PsCode[] = R"(
cbuffer ShaderData
{
	matrix worldMatrix;
	matrix cameraMatrix;
	float3 eye;
	float ambient;
};
struct PixelShaderInput
{
	float4 screenPosition : SV_POSITION;
	float3 position : POSITION;
	float3 normal : NORMAL;
};
float4 main(PixelShaderInput input) : SV_TARGET
{
	float3 lightDirection = normalize(eye - input.position);
	float intensity = saturate(dot(normalize(input.normal), lightDirection));
	intensity = ambient + (1.0f - ambient) * intensity;
	return float4(intensity, intensity, intensity, 1.0f);
}
)";
	hr = D3DCompile(s_PsCode, sizeof(s_PsCode) - 1, nullptr, nullptr, nullptr, "main", "ps_5_0", D3DCOMPILE_OPTIMIZATION_LEVEL2, 0, &shaderCode, &compileError);
	if (FAILED(hr))
	{
		if (compileError)
			OutputDebugStringA(reinterpret_cast<const char*>(compileError->GetBufferPointer()));
		ThrowIfFailed(hr, "Failed to compile pixel shader");
	}
	ThrowIfFailed(m_device3D->CreatePixelShader(shaderCode->GetBufferPointer(), shaderCode->GetBufferSize(), nullptr, &m_pixelShader), "Failed to create pixel shader");

	// Shader buffer
	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.ByteWidth = sizeof(ShaderData);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	ThrowIfFailed(m_device3D->CreateBuffer(&bufferDesc, nullptr, &m_shaderConstBuffer), "Failed to create constant buffer");

	// 2D device
	ComPtr<IDXGIDevice> dxgiDevice;
	ThrowIfFailed(m_device3D.As(&dxgiDevice), "Failed to query DXGI device");
	ComPtr<ID2D1Factory1> d2dFactory;
	ThrowIfFailed(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, IID_PPV_ARGS(&d2dFactory)), "Failed to create D2D factory");
	ThrowIfFailed(d2dFactory->CreateDevice(dxgiDevice.Get(), &m_device2D), "Failed to create D2D device");
	ThrowIfFailed(m_device2D->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &m_context2D), "Failed to create D2D device context");

	// 2D target
	ComPtr<IDXGISurface> backBufferSurface;
	ThrowIfFailed(m_swapChain->GetBuffer(0, IID_PPV_ARGS(&backBufferSurface)), "Failed to get back buffer surface");
	ThrowIfFailed(m_context2D->CreateBitmapFromDxgiSurface(backBufferSurface.Get(), D2D1::BitmapProperties1(D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW, D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED)), &m_targetBitmap), "Failed to create render tarteg bitmap");
	m_context2D->SetTarget(m_targetBitmap.Get());

	CreatePlain();
}

void Graphics::Resize(int width, int height)
{
	m_context3D->OMSetRenderTargets(0, nullptr, nullptr);
	m_renderTargetView.Reset();
	m_depthStencilView.Reset();
	m_context2D->SetTarget(nullptr);
	m_targetBitmap.Reset();

	m_viewport.Width = static_cast<float>(width) * 0.5f;
	m_viewport.Height = static_cast<float>(height);
	ThrowIfFailed(m_swapChain->ResizeBuffers(2, max(1, width), max(1, height), DXGI_FORMAT_UNKNOWN, 0), "Failed to resize swapchain buffer");

	// 3D render target and depth buffer
	ComPtr<ID3D11Texture2D> backBufferTexture;
	ThrowIfFailed(m_swapChain->GetBuffer(0, IID_PPV_ARGS(&backBufferTexture)), "Failed to get back buffer texture");
	ThrowIfFailed(m_device3D->CreateRenderTargetView(backBufferTexture.Get(), nullptr, &m_renderTargetView), "Failed to create render target view");
	
	ComPtr<ID3D11Texture2D> depthBuffer;
	UINT msaaQuality = 0;
	D3D11_TEXTURE2D_DESC depthBufferDesc{};
	depthBufferDesc.Width = max(1, width);
	depthBufferDesc.Height = max(1, height);
	depthBufferDesc.MipLevels = 1;
	depthBufferDesc.ArraySize = 1;
	depthBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthBufferDesc.SampleDesc.Count = SAMPLE_COUNT;
	depthBufferDesc.SampleDesc.Quality = SAMPLE_QUALITY(DXGI_FORMAT_B8G8R8A8_UNORM);
	depthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthBufferDesc.CPUAccessFlags = 0;
	depthBufferDesc.MiscFlags = 0;
	ThrowIfFailed(m_device3D->CreateTexture2D(&depthBufferDesc, nullptr, &depthBuffer), "Failed to create depth buffer");
	ThrowIfFailed(m_device3D->CreateDepthStencilView(depthBuffer.Get(), nullptr, &m_depthStencilView));

	// 2D target
	ComPtr<IDXGISurface> backBufferSurface;
	ThrowIfFailed(m_swapChain->GetBuffer(0, IID_PPV_ARGS(&backBufferSurface)), "Failed to get back buffer surface");
	ThrowIfFailed(m_context2D->CreateBitmapFromDxgiSurface(backBufferSurface.Get(), D2D1::BitmapProperties1(D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW, D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED)), &m_targetBitmap), "Failed to create render tarteg bitmap");
	m_context2D->SetTarget(m_targetBitmap.Get());
}

void Graphics::BeginDraw() const
{
	const float clearColor[]{ 0.1f, 0.15f, 0.2f, 1.0f };
	m_context3D->OMSetRenderTargets(1, m_renderTargetView.GetAddressOf(), m_depthStencilView.Get());
	m_context3D->ClearRenderTargetView(m_renderTargetView.Get(), clearColor);
	m_context3D->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	m_context3D->OMSetDepthStencilState(m_depthStencilState.Get(), 0);
	m_context3D->RSSetState(m_rasterizerState.Get());
	m_context3D->RSSetViewports(1, &m_viewport);
	m_context3D->IASetInputLayout(m_inputLayout.Get());
	m_context3D->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	m_context3D->PSSetShader(m_pixelShader.Get(), nullptr, 0);

	m_context2D->BeginDraw();
}

void Graphics::EndDraw() const
{
	m_context2D->EndDraw();
	m_swapChain->Present(1, 0);
}

void Graphics::RenderPlain(const ShaderData& shaderData) const
{
	RenderGeometry(shaderData, m_plainVertexBuffer.Get(), m_plainVertexCount, D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
}

void Graphics::LoadModel(const Vertex* vertices, unsigned vertexCount)
{
	D3D11_BUFFER_DESC bufferDesc{};
	D3D11_SUBRESOURCE_DATA bufferData{};
	ComPtr<ID3D11Buffer> vertexBuffer;

	bufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
	bufferDesc.ByteWidth = sizeof(*vertices) * vertexCount;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferData.pSysMem = vertices;
	ThrowIfFailed(m_device3D->CreateBuffer(&bufferDesc, &bufferData, &vertexBuffer), "Failed to create vertex buffer");

	m_modelVertexBuffer = std::move(vertexBuffer);
	m_modelVertexCount = vertexCount;
}

void Graphics::RenderModel(const ShaderData& shaderData) const
{
	RenderGeometry(shaderData, m_modelVertexBuffer.Get(), m_modelVertexCount, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

ComPtr<ID2D1SolidColorBrush> Graphics::CreateBrush(mth::float4 color) const
{
	ComPtr<ID2D1SolidColorBrush> brush;
	ThrowIfFailed(m_context2D->CreateSolidColorBrush(D2D1::ColorF(color.x, color.y, color.z, color.w), &brush));
	return brush;
}
