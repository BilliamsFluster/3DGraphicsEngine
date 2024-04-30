#include "Window.h"


Window::WindowClass Window::WindowClass::wndClass;

const wchar_t* Window::WindowClass::GetName() noexcept
{
     return wndClassName;
}

HINSTANCE Window::WindowClass::GetInstance() noexcept
{
    return wndClass.hInst;
}

Window::WindowClass::WindowClass() noexcept
	: hInst(GetModuleHandle(nullptr))
{
    WNDCLASSEX wc = { 0 };
    wc.cbSize = sizeof(wc); // Size of the structure
    wc.style = CS_OWNDC; // Class style (own device context)
    wc.lpfnWndProc = HandleMsgSetup; // Pointer to the window procedure
    wc.cbClsExtra = 0; // Extra bytes to allocate following the window-class structure
    wc.cbWndExtra = 0; // Extra bytes to allocate following the window instance
    wc.hInstance = GetInstance(); // Handle to the instance that contains the window procedure
    wc.hIcon = nullptr; // Handle to the class icon (not set)
    wc.hCursor = nullptr; // Handle to the class cursor (not set)
    wc.hbrBackground = nullptr; // Handle to the class background brush (not set)
    wc.lpszMenuName = nullptr; // Pointer to the resource name of the class menu (not set)
    wc.lpszClassName = (LPCWSTR)GetName(); // Pointer to the class name
    wc.hIcon = nullptr; // Handle to the small icon associated with the window class (not set)

    // Register the window class with the operating system
    RegisterClassEx(&wc);
}

Window::WindowClass::~WindowClass()
{
    UnregisterClass((LPCWSTR)wndClassName, GetInstance());
}

Window::Window(int width, int height, const wchar_t* name) noexcept
{
    //client region size 
    RECT wr;
    wr.left = 100;
    wr.right = width + wr.left;
    wr.top = 100;
    wr.bottom = height + wr.top;
    AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);

    hWnd = CreateWindow(
        WindowClass::GetName(), name,
        WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top, nullptr, nullptr, WindowClass::GetInstance(), this
    );
    ShowWindow(hWnd, SW_SHOWDEFAULT);
}

Window::~Window()
{
    DestroyWindow(hWnd);
}

LRESULT WINAPI Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (msg == WM_NCCREATE)
    {
        const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
        Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
        SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));
        return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT WINAPI Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT  Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
    switch (msg)
    {
    case WM_CLOSE:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}
