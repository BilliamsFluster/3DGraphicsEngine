#include "Window.h"
#include <sstream>
#include <string>
#include "resource.h"




Window::WindowClass Window::WindowClass::wndClass;

const char* Window::WindowClass::GetName() noexcept
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
    WNDCLASSEXA wc = { 0 };
    wc.cbSize = sizeof(wc); // Size of the structure
    wc.style = CS_OWNDC; // Class style (own device context)
    wc.lpfnWndProc = HandleMsgSetup; // Pointer to the window procedure
    wc.cbClsExtra = 0; // Extra bytes to allocate following the window-class structure
    wc.cbWndExtra = 0; // Extra bytes to allocate following the window instance
    wc.hInstance = GetInstance(); // Handle to the instance that contains the window procedure
    wc.hIcon = static_cast<HICON>(LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 32,32,0)); // Handle to the class icon (not set)
    wc.hCursor = nullptr; // Handle to the class cursor (not set)
    wc.hbrBackground = nullptr; // Handle to the class background brush (not set)
    wc.lpszMenuName = nullptr; // Pointer to the resource name of the class menu (not set)
    wc.lpszClassName = GetName(); // Pointer to the class name
    wc.hIconSm = static_cast<HICON>(LoadImage(hInst, MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0));; // Handle to the small icon associated with the window class (not set)

    // Register the window class with the operating system
    RegisterClassExA(&wc);
}

Window::WindowClass::~WindowClass()
{
    UnregisterClassA(wndClassName, GetInstance());
}

Window::Window(int width, int height, const char* name)
{
    //client region size 
    RECT wr;
    wr.left = 100;
    wr.right = width + wr.left;
    wr.top = 100;
    wr.bottom = height + wr.top;
    AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);
    if (FAILED(AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE)))
    {
        throw WND_LAST_EXCEPT();
    }
    
    
    hWnd = CreateWindowA(
        WindowClass::GetName(), name,
        WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top, nullptr, nullptr, WindowClass::GetInstance(), this
    );
    if (hWnd == nullptr)
    {
        throw WND_LAST_EXCEPT();
    }
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

Window::WinException::WinException(int line, const char* file, HRESULT hr) noexcept
    :Exception(line, file), hr(hr)
{

}

const char* Window::WinException::what() const noexcept
{
    std::ostringstream oss;
    oss << GetType() << std::endl
        << "[Error Code] " << GetErrorCode() << std::endl
        << "[Description] " << GetErrorString() << std::endl << GetOriginString();
    whatBuffer = oss.str();
    return whatBuffer.c_str();
}

const char* Window::WinException::GetType() const noexcept
{
    return "Window Exception";
}

std::string Window::WinException::TranslateErrorCode(HRESULT hr) noexcept
{
    char* pMsgBuf = nullptr;
    DWORD nMsgLen = FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER |
        FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr, hr, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US), reinterpret_cast<LPSTR>(&pMsgBuf), 0, nullptr);
    if (nMsgLen == 0)
    {
        return "Unidentified error code";
    }
    
    std::string errorString = pMsgBuf;
    
    LocalFree(pMsgBuf);
    
    return errorString;
}

HRESULT Window::WinException::GetErrorCode() const noexcept
{
    return hr;
}

std::string Window::WinException::GetErrorString() const noexcept
{
    return TranslateErrorCode(hr);
}
