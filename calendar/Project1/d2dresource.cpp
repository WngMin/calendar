#include "d2dresource.h"

HRESULT D2DResource::Initialize(HWND hwnd)
{
	HRESULT hr = S_OK;
	hr = CreateD2DResource(hwnd);
	return hr;
}

ID2D1HwndRenderTarget* D2DResource::getRenderTarget()
{
	return m_pRenderTarget;
}

IDWriteTextFormat* D2DResource::getTextFormat()
{
	return m_pWriterTextFormat;
}

IDWriteTextFormat* D2DResource::getTextFormat_1()
{
	return m_pWriterTextFormat_1;
}

IDWriteTextFormat* D2DResource::getTextFormat_2()
{
	return m_pWriterTextFormat_2;
}

ID2D1SolidColorBrush* D2DResource::getBlackBrush()
{
	return m_pSolidBlackBrush;
}

HRESULT D2DResource::CreateD2DResource(HWND hwnd)
{
	HRESULT hr = S_OK;

	// Factory
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);
	if (SUCCEEDED(hr)) // RenderTarget
	{
		RECT rect;
		GetClientRect(hwnd, &rect);
		D2D1_SIZE_U size = D2D1::SizeU(
			rect.right - rect.left,
			rect.bottom - rect.top
		);
		hr = m_pD2DFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(hwnd, size),
			&m_pRenderTarget
		);
	}
	if (SUCCEEDED(hr)) // 1
	{
		hr = m_pRenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Black),
			&m_pSolidBlackBrush
		);
	}
	if (SUCCEEDED(hr))
	{
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(m_pDwriterFactory),
			reinterpret_cast<IUnknown**>(&m_pDwriterFactory)
		);
	}
	if (SUCCEEDED(hr))
	{
		hr = m_pDwriterFactory->CreateTextFormat(
			L"Rockwell",
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			10,
			L"en-US", //locale
			&m_pWriterTextFormat
		);
	}
	if (SUCCEEDED(hr))
	{
		// Center the text horizontally and vertically.
		m_pWriterTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

		m_pWriterTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}
	if (SUCCEEDED(hr))
	{
		hr = m_pDwriterFactory->CreateTextFormat(
			L"Rockwell",
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			30,
			L"en-US", //locale
			&m_pWriterTextFormat_1
		);
	}
	if (SUCCEEDED(hr))
	{
		// Center the text horizontally and vertically.
		m_pWriterTextFormat_1->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

		m_pWriterTextFormat_1->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}
	if (SUCCEEDED(hr))
	{
		hr = m_pDwriterFactory->CreateTextFormat(
			L"PMingLiU",
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			20,
			L"en-US", //locale
			&m_pWriterTextFormat_2
		);
	}
	if (SUCCEEDED(hr))
	{
		// Center the text horizontally and vertically.
		m_pWriterTextFormat_2->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

		m_pWriterTextFormat_2->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
	}
	return hr;
}
