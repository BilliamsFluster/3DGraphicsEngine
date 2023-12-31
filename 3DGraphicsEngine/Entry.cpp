#include <Windows.h>

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
    // Define a unique class name for the window
    const wchar_t* pClassName = L"hw";

    // Initialize a WNDCLASSEX structure to describe the window class
    WNDCLASSEX wc = { 0 };
    wc.cbSize = sizeof(wc); // Size of the structure
    wc.style = CS_OWNDC; // Class style (own device context)
    wc.lpfnWndProc = WndProc; // Pointer to the window procedure
    wc.cbClsExtra = 0; // Extra bytes to allocate following the window-class structure
    wc.cbWndExtra = 0; // Extra bytes to allocate following the window instance
    wc.hInstance = hInstance; // Handle to the instance that contains the window procedure
    wc.hIcon = nullptr; // Handle to the class icon (not set)
    wc.hCursor = nullptr; // Handle to the class cursor (not set)
    wc.hbrBackground = nullptr; // Handle to the class background brush (not set)
    wc.lpszMenuName = nullptr; // Pointer to the resource name of the class menu (not set)
    wc.lpszClassName = pClassName; // Pointer to the class name
    wc.hIcon = nullptr; // Handle to the small icon associated with the window class (not set)

    // Register the window class with the operating system
    RegisterClassEx(&wc);

    // Create an instance of the window
    HWND hWnd = CreateWindowEx(
        0, pClassName, // Extended window style and class name
        L"Graphics Window", // Window title
        WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, // Window style (caption, minimize box, system menu)
        200, 200, // Window position (x, y)
        640, 480, // Window size (width, height)
        nullptr, // Parent window handle (no parent)
        nullptr, // Menu handle (no menu)
        hInstance, // Handle to the instance of the module to be associated with the window
        nullptr // Pointer to a value to be passed to the window (not used)
    );

    // Display the window
    ShowWindow(hWnd, SW_SHOW);

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
