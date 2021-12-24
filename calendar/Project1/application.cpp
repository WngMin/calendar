#include "application.h"

void Application::Run()
{
    MSG msg = { 0 };
    m_timer.Reset();
    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            /*m_timer.Tick();*/
            HRESULT hr = Render();
            if (FAILED(hr)) { return; }
            /*double remainTime = 0.0167 - m_timer.GetDeltaTime();
            Sleep(remainTime);*/
        }
    }
}

HRESULT Application::Initialize(HINSTANCE hInstance)
{
    HRESULT hr = S_OK;
    m_hInstance = hInstance;

    WNDCLASSEX wcex = { sizeof(WNDCLASSEX) };
    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = Application::ApplicationMSGProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = sizeof(LONG_PTR);
    wcex.hInstance = hInstance;
    wcex.hbrBackground = NULL;
    wcex.lpszMenuName = NULL;
    wcex.hCursor = LoadCursor(NULL, IDI_APPLICATION);
    wcex.lpszClassName = L"D2DDemoApp";

    RegisterClassEx(&wcex);

    RECT rc;
    rc.top = 0;
    rc.left = 0;
    rc.bottom = 640;
    rc.right = 620;
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME, FALSE);
    m_hwnd = CreateWindow(
        L"D2DDemoApp",
        L"Calendar",
        WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        rc.right - rc.left,
        rc.bottom - rc.top,
        NULL,
        NULL,
        hInstance,
        nullptr
    );
    hr = m_hwnd ? S_OK : E_FAIL;
    if (SUCCEEDED(hr))
    {
        ShowWindow(m_hwnd, SW_SHOWNORMAL);
        UpdateWindow(m_hwnd);
    }
    if (SUCCEEDED(hr))
    {
        hr = m_pD2DResource->Initialize(m_hwnd);
    }
    return hr;
}

LRESULT Application::ApplicationMSGProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_MOUSEMOVE:
    {

        int x = LOWORD(lParam);
        int y = HIWORD(lParam);
        if (x < 600 && x > 520 && y < 230 && y > 200)
        {
            application->m_lineWidth1 = 1.5;
        }
        else
        {
            application->m_lineWidth1 = 0.5;
        }
        if (x < 600 && x > 520 && y < 330 && y > 300)
        {
            application->m_lineWidth2 = 1.5;
        }
        else
            application->m_lineWidth2 = 0.5;
        break;
    }
    case WM_LBUTTONDOWN:
    {

        int x = LOWORD(lParam);
        int y = HIWORD(lParam);
        if (x < 600 && x > 520 && y < 230 && y > 200)
        {
            if (x < 600 && x > 560)
                if (application->m_curYear > 3000)
                    ;
                else
                    application->m_curYear++;
            else
                if (application->m_curYear < 1000)
                    ;
                else
                    application->m_curYear--;

        }
        if (x < 600 && x > 520 && y < 330 && y > 300)
        {
            if (x < 600 && x > 560)
                if (application->m_month > 11)
                {
                    application-> m_curYear++;
                    application->m_month = 0;
                }
                else
                    application->m_month++;
            else
                if (application->m_month < 1)
                {
                    application->m_curYear--;
                    application->m_month = 12;
                }
                else
                    application->m_month--;
        }
        break;
    }
    case WM_MOUSEWHEEL:
    {
        if ((short)HIWORD(wParam) > 0)
        {
            SendMessage(hwnd, WM_KEYDOWN, VK_RIGHT, NULL);
        }
        else
        {
            SendMessage(hwnd, WM_KEYDOWN, VK_LEFT, NULL);
        }
        break;
    }
    case WM_KEYDOWN:
    {
        if (wParam == VK_RIGHT)
        {
            if (application->m_month > 11)
            {
                application->m_curYear++;
                application->m_month = 0;
            }
            else
                application->m_month++;
        }
        else if (wParam == VK_LEFT)
        {
            if (application->m_month < 1)
            {
                application->m_curYear--;
                application->m_month = 12;
            }
            else
                application->m_month--;
        }
        else if (wParam == VK_UP)
        {
            if (application->m_curYear > 3000)
                ;
            else
                application->m_curYear++;
        }
        else if (wParam == VK_DOWN)
        {
            if (application->m_curYear < 1000)
                ;
            else
                application->m_curYear--;
        }
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}

HRESULT Application::Render()
{
    const wchar_t* fes[13][32];
    for (int i = 0; i < 13; i++)
        for (int j = 0; j < 32; j++)
            fes[i][j] = L"\0";
    fes[1][1] = L"元旦";
    fes[3][12] = L"植树节";
    fes[5][1] = L"劳动节";
    fes[6][1] = L"儿童节";
    fes[9][10] = L"教师节";
    fes[10][1] = L"国庆节";
    fes[11][10] = L"万圣节";
    fes[12][24] = L"平安夜";
    fes[12][25] = L"圣诞节";

    if (m_month != 0)
    {
        HRESULT hr = S_OK;
        m_pD2DResource->getRenderTarget()->BeginDraw();
        m_pD2DResource->getRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
        m_pD2DResource->getRenderTarget()->Clear(D2D1::ColorF(D2D1::ColorF::Gray));
        // Year Controller
        m_pD2DResource->getRenderTarget()->DrawRectangle(
            m_frame.rectForYear,
            m_pD2DResource->getBlackBrush(),
            m_lineWidth1
        );
        // Month Controller
        m_pD2DResource->getRenderTarget()->DrawRectangle(
            m_frame.rectForMonth,
            m_pD2DResource->getBlackBrush(),
            m_lineWidth2
        );
        wchar_t buffer[1000];
        wsprintf(buffer, L"%d", m_curYear);
        m_pD2DResource->getRenderTarget()->DrawText(
            buffer,
            wcslen(buffer),
            m_pD2DResource->getTextFormat(),
            m_frame.rectForYear,
            m_pD2DResource->getBlackBrush()
        );
        // Month Controller
        wsprintf(buffer, L"%d", m_month);
        m_pD2DResource->getRenderTarget()->DrawText(
            buffer,
            wcslen(buffer),
            m_pD2DResource->getTextFormat(),
            m_frame.rectForMonth,
            m_pD2DResource->getBlackBrush()
        );
        const wchar_t* weeks[7] = { L"Sun", L"Mon", L"Tue", L"Wed", L"Thu", L"Fir", L"Sat" };
        for (int x = 0; x < 7; x++)
        {
            m_pD2DResource->getRenderTarget()->DrawText(
                weeks[x],
                wcslen(weeks[x]),
                m_pD2DResource->getTextFormat_1(),
                m_frame.rectForCalSingleMonth[x],
                m_pD2DResource->getBlackBrush()
            );
        }
        std::vector<MonthAndWeek> v = m_calendar.GetMonthOfYear(m_curYear);
        unsigned int t = 1;
        for (int x = 1; x < 7; x++)
        {
            int y;
            if (x == 1)
                y = v[m_month - 1].m_week;
            else
                y = 0;
            for (; y < 7; y++)
            {
                if (t > v[m_month - 1].m_month)
                    break;
                m_pD2DResource->getRenderTarget()->DrawRectangle(
                    m_frame.rectForCalSingleMonth[x * 7 + y],
                    m_pD2DResource->getBlackBrush(),
                    1.f
                );
                if (wcslen(fes[m_month][t]) != 0)
                {
                    m_pD2DResource->getRenderTarget()->DrawText(
                        fes[m_month][t],
                        wcslen(fes[m_month][t]),
                        m_pD2DResource->getTextFormat_2(),
                        m_frame.rectForCalSingleMonth[x * 7 + y],
                        m_pD2DResource->getBlackBrush()
                    );
                }
                wsprintf(buffer, L"%d", t++);
                m_pD2DResource->getRenderTarget()->DrawText(
                    buffer,
                    wcslen(buffer),
                    m_pD2DResource->getTextFormat_1(),
                    m_frame.rectForCalSingleMonth[x * 7 + y],
                    m_pD2DResource->getBlackBrush()
                );
            }
        }
        hr = m_pD2DResource->getRenderTarget()->EndDraw();
        return hr;
    }

    // Whole Year
    else
    {
        HRESULT hr = S_OK;
        m_pD2DResource->getRenderTarget()->BeginDraw();
        m_pD2DResource->getRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
        m_pD2DResource->getRenderTarget()->Clear(D2D1::ColorF(D2D1::ColorF::Gray));
        // Year Controller
        m_pD2DResource->getRenderTarget()->DrawRectangle(
            m_frame.rectForYear,
            m_pD2DResource->getBlackBrush(),
            m_lineWidth1
        );
        // Month Controller
        m_pD2DResource->getRenderTarget()->DrawRectangle(
            m_frame.rectForMonth,
            m_pD2DResource->getBlackBrush(),
            m_lineWidth2
        );
        wchar_t buffer[1000];
        wsprintf(buffer, L"%d", m_curYear);
        m_pD2DResource->getRenderTarget()->DrawText(
            buffer,
            wcslen(buffer),
            m_pD2DResource->getTextFormat(),
            m_frame.rectForYear,
            m_pD2DResource->getBlackBrush()
        );
        // Month Controller
        wsprintf(buffer, L"%d", m_month);
        m_pD2DResource->getRenderTarget()->DrawText(
            buffer,
            wcslen(buffer),
            m_pD2DResource->getTextFormat(),
            m_frame.rectForMonth,
            m_pD2DResource->getBlackBrush()
        );
        std::vector<MonthAndWeek> v = m_calendar.GetMonthOfYear(m_curYear);

        for (int k = 0; k < 12; k++)
        {

            if (k < 6)
            {
                D2D1::Matrix3x2F trans = D2D1::Matrix3x2F::Translation(0, 106.6 * k);
                m_pD2DResource->getRenderTarget()->SetTransform(trans);
            }
            else
            {
                D2D1::Matrix3x2F trans = D2D1::Matrix3x2F::Translation(250, 106.6 * (k - 6));
                m_pD2DResource->getRenderTarget()->SetTransform(trans);
            }
            unsigned int t = 1;
            const wchar_t* weeks[7] = { L"Sun", L"Mon", L"Tue", L"Wed", L"Thu", L"Fir", L"Sat" };
            for (int x = 0; x < 7; x++)
            {
                m_pD2DResource->getRenderTarget()->DrawText(
                    weeks[x],
                    wcslen(weeks[x]),
                    m_pD2DResource->getTextFormat(),
                    m_frame.rectForCal[x],
                    m_pD2DResource->getBlackBrush()
                );
            }
            for (int x = 1; x < 7; x++)
            {
                int y;
                if (x == 1)
                    y = v[k].m_week;
                else
                    y = 0;
                for (; y < 7; y++)
                {
                    if (t > v[k].m_month)
                        break;
                    m_pD2DResource->getRenderTarget()->DrawRectangle(
                        m_frame.rectForCal[x * 7 + y],
                        m_pD2DResource->getBlackBrush(),
                        .5f
                    );
                    wsprintf(buffer, L"%d", t++);
                    m_pD2DResource->getRenderTarget()->DrawText(
                        buffer,
                        wcslen(buffer),
                        m_pD2DResource->getTextFormat(),
                        m_frame.rectForCal[x * 7 + y],
                        m_pD2DResource->getBlackBrush()
                    );
                }
            }
        }
        hr = m_pD2DResource->getRenderTarget()->EndDraw();
        return hr;
    }
}