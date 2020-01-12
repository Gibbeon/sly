#include "sly/win32/os/window.h"

using namespace sly::os;

Win32Window::Win32Window(Win32WindowSystem& parent) : 
    _parent(parent),
    _initialized(false) {

}

sly::retval<void> Win32Window::release() {
    if(_initialized) {
        setVisible(false);
        DestroyWindow(_hWND);
        _hWND = nullptr;
        _parent.release(*this);
        _initialized = false;
    }
    
    return success();
}

sly::retval<void> Win32Window::init(const WindowDesc& desc)
{
    _width = desc.width;
    _height = desc.height;
    _title = desc.title;

    HINSTANCE hInstance= GetModuleHandle(NULL);
    // Initialize the window class.
    WNDCLASSEX windowClass = { 0 }; 
    windowClass.cbSize = sizeof(WNDCLASSEX);
    windowClass.style = CS_HREDRAW | CS_VREDRAW;
    windowClass.lpfnWndProc = WindowProc;
    windowClass.hInstance = hInstance;
    windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    windowClass.lpszClassName =  "Win32Window";
    RegisterClassEx(&windowClass);

    ::RECT windowRect = { 0, 0, static_cast<LONG>(_width), static_cast<LONG>(_height) };
    AdjustWindowRect(&windowRect, WS_OVERLAPPED, FALSE);
    
    /*
    _In_ DWORD dwExStyle,
    _In_opt_ LPCWSTR lpClassName,
    _In_opt_ LPCWSTR lpWindowName,
    _In_ DWORD dwStyle,
    _In_ int X,
    _In_ int Y,
    _In_ int nWidth,
    _In_ int nHeight,
    _In_opt_ HWND hWndParent,
    _In_opt_ HMENU hMenu,
    _In_opt_ HINSTANCE hInstance,
    _In_opt_ LPVOID lpParam);
    */

    // Create the window and store a handle to it.
    this->setHwnd(CreateWindowEx(
        WS_EX_TRANSPARENT,
        windowClass.lpszClassName,
        getTitle().c_str(),
        WS_OVERLAPPED,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        windowRect.right - windowRect.left,
        windowRect.bottom - windowRect.top,
        nullptr,        // We have no parent window.
        nullptr,        // We aren't using menus.
        hInstance,
        this));

    //ShowWindow(_hWND, SW_SHOWDEFAULT);

    _initialized = true;

    return success();
}

bool_t Win32Window::processMessages()
{
    MSG msg = {};
    bool_t process = true;
    while (process)
    {
        process = false;
        // Process any messages in the queue.
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            process = true; 
        }
    }

    // Return this part of the WM_QUIT message to Windows.
    return static_cast<char>(msg.wParam);
}

// Main message handler for the sample.
LRESULT CALLBACK Win32Window::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    Win32Window* pSample = reinterpret_cast<Win32Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

    switch (message)
    {
    case WM_CREATE:
        {
            // Save the DXSample* passed in to CreateWindow.
            LPCREATESTRUCT pCreateStruct = reinterpret_cast<LPCREATESTRUCT>(lParam);
            SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pCreateStruct->lpCreateParams));
        }
        return 0;

case WM_PAINT: {
	ValidateRect(hWnd, NULL);
} return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    // Handle any messages the switch statement didn't.
    return DefWindowProc(hWnd, message, wParam, lParam);
}