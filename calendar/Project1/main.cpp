#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

#include <Windows.h>
#include "application.h"


Application* application;

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow
)
{
    application = new Application();

    HRESULT hr = application->Initialize(hInstance);
    if (FAILED(hr)) { return -1; }

    application->Run();
    return 0;
}