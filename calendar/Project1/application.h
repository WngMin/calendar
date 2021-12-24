#pragma once


#include "d2dresource.h"
#include <Windows.h>
#include "calendar.h"
#include "frameresource.h"
#include "Timer.h"

class Application
{
public:
	Application() : m_hInstance(nullptr), m_hwnd(nullptr), m_frame(), m_timer()
	{
		m_pD2DResource = new D2DResource();
	};
	~Application()
	{
		delete m_pD2DResource;
	}

	void Run();

	HRESULT Initialize(HINSTANCE hInstance);

	static LRESULT CALLBACK ApplicationMSGProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	HRESULT Render();
	unsigned int m_curYear = 2020;
	unsigned int m_month = 0;
	float m_lineWidth1 = 0.5;
	float m_lineWidth2 = 0.5;

	HINSTANCE m_hInstance;
	HWND m_hwnd;
	Calendar m_calendar;
	FrameResource m_frame;

	D2DResource* m_pD2DResource;
	Timer m_timer;
};

extern Application* application;