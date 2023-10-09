#pragma once

#include "graphics.h"
#include "model.h"

class Application
{
	HWND m_mainWindow;
	POINT m_prevCursor;
	mth::vec2<int> m_resolution;
	Graphics m_graphics;
	Model m_model;
	mth::float3 m_center;
	mth::float2 m_cameraRotation;
	float m_cameraDistance;
	mth::float4x4 m_modelTransform;
	mth::float4x4 m_plainTransform;
	bool m_plainShowing;
	std::vector<mth::float2> m_slice;
	float m_sliceScale;
	ComPtr<ID2D1SolidColorBrush> m_brush;
	int m_processorCount;

private:
	void PaintEvent();
	void Resize(int width, int height);
	void DropFileEvent(HDROP drop);
	void MouseLButtonDownEvent(int x, int y, WPARAM flags);
	void MouseRButtonDownEvent(int x, int y, WPARAM flags);
	void MouseLButtonUpEvent(int x, int y, WPARAM flags);
	void MouseRButtonUpEvent(int x, int y, WPARAM flags);
	void MouseMoveEvent(int x, int y, WPARAM flags);
	void MouseWheelEvent(int x, int y, WPARAM flags);
	void KeyDownEvent(WPARAM key);
	void KeyUpEvent(WPARAM key);

	void SetViewForModel();
	void CalcSlice();

public:
	Application();
	~Application();
	void Init(const wchar_t* title, int width, int height);
	void Run();
	LRESULT MessageHandler(UINT msg, WPARAM wparam, LPARAM lparam);
};