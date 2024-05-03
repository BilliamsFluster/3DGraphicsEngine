#include "WinDef.h"
#include "Window/Window.h"
#include "Application.h"
#include <string>
#include <sstream>

// Window procedure function to handle messages sent to the window
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CLOSE: // When the window receives a close message
        PostQuitMessage(69); // Send a quit message with exit code 69
        break;

    case WM_KEYDOWN:
        if (wParam == 'F')
        {
            SetWindowTextA(hWnd, "KeyPRessed");
            break;
        }
    }
    return DefWindowProc(hWnd, msg, wParam, lParam); // Default window procedure for unhandled messages
}

// Entry point for a Windows application
int CALLBACK WinMain(
    HINSTANCE	hInstance,       // Handle to the current instance of the application
    HINSTANCE	hPrevInstance,   // Handle to the previous instance (always NULL for Win32 programs)
    LPSTR		lpCmdLine,       // Command line arguments as a single string
    int			nCmdShow)        // Specifies how the window is to be shown
{
    try
    {
        return Application{}.Go();
    }
    catch (const Exception& e)
    {
        MessageBoxA(nullptr,e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
        
    }
    catch (const std::exception& e)
    {
        MessageBoxA(nullptr, e.what(), "Standard Exception ", MB_OK | MB_ICONEXCLAMATION);
    }
    catch (...)
    {
        MessageBoxA(nullptr,"No Details Available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
    }
    return -1;
}
