#include "application.h"
#include <windowsx.h>
#include <vector>
#include <algorithm>

void Application::PaintEvent()
{
	m_graphics.BeginDraw();

	ShaderData shaderData;
	shaderData.eye = mth::float3x3::Rotation(m_cameraRotation.x, m_cameraRotation.y, 0.0f) * mth::float3(0.0f, 0.0f, -m_cameraDistance) + m_center;
	shaderData.worldMatrix = mth::float4x4::ScalingTranslation(mth::float3(m_modelScale), -m_modelOffset * m_modelScale);
	shaderData.cameraMatrix =
		mth::float4x4::PerspectiveFOV(mth::pi * 0.25f, static_cast<float>(m_resolution.x) * 0.5f / static_cast<float>(m_resolution.y), 0.1f, 1000.0f) *
		mth::float4x4::RotationCamera(shaderData.eye, mth::float3(m_cameraRotation.x, m_cameraRotation.y, 0.0f));
	shaderData.ambient = 0.5f;
	m_graphics.RenderModel(shaderData);

	if (m_plainShowing)
	{
		shaderData.worldMatrix = mth::float4x4(m_plainRotation);
		shaderData.worldMatrix(0, 3) = m_plainOffset.x;
		shaderData.worldMatrix(1, 3) = m_plainOffset.y;
		shaderData.worldMatrix(2, 3) = m_plainOffset.z;
		shaderData.ambient = 1.0f;
		m_graphics.RenderPlain(shaderData);

		for (std::size_t i = 1; i < m_slice.size(); i += 2)
		{
			const float scale = min(static_cast<float>(m_resolution.x) * 0.5f, static_cast<float>(m_resolution.y));
			const mth::float2 offset = mth::float2(static_cast<float>(m_resolution.x) * 0.75f, static_cast<float>(m_resolution.y) * 0.5f);
			const mth::float2 p1 = offset + m_slice[i - 1] * scale;
			const mth::float2 p2 = offset + m_slice[i - 0] * scale;
			m_graphics.Context2D()->DrawLine(D2D1::Point2F(p1.x, p1.y), D2D1::Point2F(p2.x, p2.y), m_brush.Get(), 2.0f);
		}
	}

	m_graphics.EndDraw();
	ValidateRect(m_mainWindow, nullptr);
}

void Application::Resize(int width, int height)
{
	m_resolution.x = width;
	m_resolution.y = height;
	m_graphics.Resize(width, height);
}

void Application::DropFileEvent(HDROP drop)
{
	WCHAR filename[MAX_PATH + 1]{};
	DragQueryFile(drop, 0, filename, MAX_PATH);
	try
	{
		if (m_model.Load(filename))
		{
			m_graphics.LoadModel(m_model.Vertices().data(), static_cast<unsigned>(m_model.Vertices().size()));
			SetViewForModel();
			InvalidateRect(m_mainWindow, nullptr, false);
		}
	}
	catch (const std::exception& ex)
	{
		OutputDebugStringA(ex.what());
		MessageBoxA(nullptr, ex.what(), "Error", MB_OK);
	}
	DragFinish(drop);
	SetForegroundWindow(m_mainWindow);
}

void Application::MouseLButtonDownEvent(int x, int y, WPARAM flags)
{
	SetCapture(m_mainWindow);
	m_prevCursor = { x, y };
}

void Application::MouseRButtonDownEvent(int x, int y, WPARAM flags)
{
	SetCapture(m_mainWindow);
	m_prevCursor = { x, y };
}

void Application::MouseLButtonUpEvent(int x, int y, WPARAM flags)
{
	if (0 == (flags & (MK_LBUTTON | MK_RBUTTON)))
		ReleaseCapture();
	m_prevCursor = { x, y };
}

void Application::MouseRButtonUpEvent(int x, int y, WPARAM flags)
{
	if (0 == (flags & (MK_LBUTTON | MK_RBUTTON)))
		ReleaseCapture();
	m_prevCursor = { x, y };
}

void Application::MouseMoveEvent(int x, int y, WPARAM flags)
{
	const float sensitivity = 0.008f;
	const mth::float2 delta(
		static_cast<float>(x - m_prevCursor.x),
		static_cast<float>(y - m_prevCursor.y));

	if ((flags & MK_CONTROL) && m_plainShowing)
	{
		mth::float3x3 camRot;
		if (flags & (MK_LBUTTON | MK_RBUTTON))
			camRot = mth::float3x3::Rotation(m_cameraRotation.x, m_cameraRotation.y, 0.0f);
		if (flags & MK_RBUTTON)
			m_plainOffset += camRot * (mth::float3(delta.x, -delta.y, 0.0f) * sensitivity * m_cameraDistance * 0.1f);
		if (flags & MK_LBUTTON)
			m_plainRotation = 
				mth::float3x3::RotationNormal(camRot * mth::float3(-1.0f, 0.0f, 0.0f), static_cast<float>(delta.y) * sensitivity) *
				mth::float3x3::RotationNormal(camRot * mth::float3(0.0f, -1.0f, 0.0f), static_cast<float>(delta.x) * sensitivity) *
				m_plainRotation;

		if (flags & (MK_LBUTTON | MK_RBUTTON))
			CalcSlice();
	}
	else
	{
		if (flags & MK_RBUTTON)
		{
			m_center -= mth::float3x3::Rotation(m_cameraRotation.x, m_cameraRotation.y, 0.0f) * (mth::float3(delta.x, -delta.y, 0.0f) * sensitivity * m_cameraDistance * 0.1f);
		}
		if (flags & MK_LBUTTON)
		{
			m_cameraRotation.x += static_cast<float>(delta.y) * sensitivity;
			m_cameraRotation.y += static_cast<float>(delta.x) * sensitivity;
		}
	}
	if (flags & (MK_LBUTTON | MK_RBUTTON))
		InvalidateRect(m_mainWindow, nullptr, false);

	m_prevCursor = { x, y };
}

void Application::MouseWheelEvent(int x, int y, WPARAM flags)
{
	m_cameraDistance *= GET_WHEEL_DELTA_WPARAM(flags) < 0 ? 1.1f : 1.0f / 1.1f;
	InvalidateRect(m_mainWindow, nullptr, false);
}

void Application::KeyDownEvent(WPARAM key)
{
	if (VK_SPACE == key)
	{
		m_plainShowing = !m_plainShowing;
		InvalidateRect(m_mainWindow, nullptr, false);
	}
}

void Application::KeyUpEvent(WPARAM key)
{
}

void Application::SetViewForModel()
{
	m_model.OptimalPositioning(m_modelOffset, m_modelScale);
	m_center = 0.0f;
	m_cameraDistance = 2.0f;
	m_plainRotation = mth::float3x3::Identity();
	m_plainOffset = 0.0f;
	CalcSlice();
}

void Application::CalcSlice()
{
	const mth::float3 normal = m_plainRotation * mth::float3(0.0f, 1.0f, 0.0f);
	const float distance = normal.Dot(m_plainOffset / m_modelScale + m_modelOffset);
	m_slice = m_model.CalcSlice(normal, distance, m_processorCount);

	for (mth::float2& p : m_slice)
	{
		const mth::float3 offset = mth::float3x3::RotateUnitVector(normal, mth::float3(0.0f, 1.0f, 0.0f)) * m_modelOffset;
		p.x -= offset.x;
		p.y -= offset.z;
		p *= m_modelScale;
	}
}

Application::Application()
	: m_mainWindow{}
	, m_prevCursor{}
	, m_cameraDistance{}
	, m_modelScale{}
	, m_plainShowing{ true }
	, m_processorCount{} {}

Application::~Application()
{
}

void Application::Init(const wchar_t* title, int width, int height)
{
	WNDCLASSEXW wc{};
	wc.cbSize = sizeof(wc);
	wc.hInstance = GetModuleHandleW(nullptr);
	wc.lpszClassName = title;
	wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = DefWindowProcW;
	RegisterClassExW(&wc);
	RECT rect{ 0, 0, width, height };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, 0);
	m_resolution.x = rect.right - rect.left;
	m_resolution.y = rect.bottom - rect.top;
	m_mainWindow = CreateWindowExW(WS_EX_ACCEPTFILES, title, title, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, m_resolution.x, m_resolution.y, nullptr, nullptr, nullptr, nullptr);
	SetWindowLongPtrW(m_mainWindow, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
	SetWindowLongPtrW(m_mainWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(static_cast<LRESULT(*)(HWND, UINT, WPARAM, LPARAM)>(
		[](HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)->LRESULT {
			return reinterpret_cast<Application*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA))->MessageHandler(msg, wparam, lparam);
		})));

	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	m_processorCount = sysinfo.dwNumberOfProcessors;

	m_graphics.Init(m_mainWindow);
	m_model.Cube();
	SetViewForModel();
	m_graphics.LoadModel(m_model.Vertices().data(), static_cast<unsigned>(m_model.Vertices().size()));
	m_brush = m_graphics.CreateBrush(mth::float4(1.0f, 1.0f, 1.0f, 1.0f));

	ShowWindow(m_mainWindow, SW_SHOWDEFAULT);
	UpdateWindow(m_mainWindow);
}

void Application::Run()
{
	MSG message{};
	while (GetMessageW(&message, nullptr, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessageW(&message);
	}
}

LRESULT Application::MessageHandler(UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_MOUSEMOVE:
		MouseMoveEvent(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam), wparam);
		return 0;
	case WM_MOUSEWHEEL:
		MouseWheelEvent(m_prevCursor.x, m_prevCursor.y, wparam);
		return 0;
	case WM_LBUTTONDOWN:
		MouseLButtonDownEvent(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam), wparam);
		return 0;
	case WM_RBUTTONDOWN:
		MouseRButtonDownEvent(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam), wparam);
		return 0;
	case WM_LBUTTONUP:
		MouseLButtonUpEvent(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam), wparam);
		return 0;
	case WM_RBUTTONUP:
		MouseRButtonUpEvent(GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam), wparam);
		return 0;
	case WM_KEYDOWN:
		KeyDownEvent(wparam);
		return 0;
	case WM_KEYUP:
		KeyUpEvent(wparam);
		return 0;
	case WM_PAINT:
		PaintEvent();
		return 0;
	case WM_SIZE:
		Resize(LOWORD(lparam), HIWORD(lparam));
		return 0;
	case WM_DROPFILES:
		DropFileEvent(reinterpret_cast<HDROP>(wparam));
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProcW(m_mainWindow, msg, wparam, lparam);
}