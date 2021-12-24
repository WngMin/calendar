#pragma once
#pragma once

#include <d2d1.h>
#include <dwrite.h>

template <class Interface>
inline void SafeRelease(Interface** ppInterfaceToRelease)
{
	if (*ppInterfaceToRelease)
	{
		(*ppInterfaceToRelease)->Release();
		(*ppInterfaceToRelease) = NULL;
	}
}

class D2DResource
{
public:
	D2DResource() :
		m_pD2DFactory(nullptr),
		m_pRenderTarget(nullptr),

		m_pSolidBlackBrush(nullptr),
		m_pDwriterFactory(nullptr),
		m_pWriterTextFormat(nullptr)
	{}
	~D2DResource()
	{
		SafeRelease(&m_pD2DFactory);
		SafeRelease(&m_pRenderTarget);

		SafeRelease(&m_pSolidBlackBrush);

		SafeRelease(&m_pDwriterFactory);
		SafeRelease(&m_pWriterTextFormat);
	}

	HRESULT Initialize(HWND hwnd);
	ID2D1HwndRenderTarget* getRenderTarget();

	IDWriteTextFormat* getTextFormat();
	IDWriteTextFormat* getTextFormat_1();
	IDWriteTextFormat* getTextFormat_2();
	ID2D1SolidColorBrush* getBlackBrush();

private:
	HRESULT CreateD2DResource(HWND hwnd);
private:
	ID2D1Factory* m_pD2DFactory;
	ID2D1HwndRenderTarget* m_pRenderTarget;

	ID2D1SolidColorBrush* m_pSolidBlackBrush;

	IDWriteFactory* m_pDwriterFactory;
	IDWriteTextFormat* m_pWriterTextFormat;
	IDWriteTextFormat* m_pWriterTextFormat_1;
	IDWriteTextFormat* m_pWriterTextFormat_2;
};
