#include "WinDef.h"
#include "Window/Window.h"
#include <string>

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


        Window wnd(800, 300, "Graphics Engine");
        
        MSG msg;
        BOOL gResult;
        // Infinite loop to keep the window running
        while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
        {
            TranslateMessage(&msg); // Translates virtual-key messages into character messages
            DispatchMessage(&msg); // Dispatches a message to a window procedure
        }

        // Check the result of GetMessage
        if (gResult == -1)
        {
            return -1; // If there was an error, return -1
        }
        else
        {
            return msg.wParam; // Otherwise, return the exit code
        }
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
