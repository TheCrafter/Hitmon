//==================================================
//= Public functions
//==================================================

template<typename WindowData>
Window<WindowData>::Window(WindowData data)
    : mData(data)
{
}

template<typename WindowData>
bool Window<WindowData>::Init(HINSTANCE instance)
{
    if(!RegisterWindowClass(instance))
        return false;

    // Create window
    mWindow = CreateWindowEx(
        0,                              // Extended window style of the window created
        mData.GetClassName(),           // Class name from previous call to RegisterClass[Ex]
        "Hitmon",                       // Window Name
        0,                              // Window style
        64,                             // Initial x position for window
        64,                             // Initial y position for window
        640,                            // Window width
        480,                            // Window height
        0,                              // Handle to parent window
        0,                              // Handle to menu
        instance,                       // A handle to the instance of the module to be associated with the window.
        (LPVOID)this);	                // Pointer to params for the window

    return mWindow != 0;
}

template<typename WindowData>
HWND Window<WindowData>::GetWindow() const
{
    return mWindow;
}

//==================================================
//== Private functions
//==================================================

template<typename WindowData>
bool Window<WindowData>::RegisterWindowClass(HINSTANCE instance)
{
        WNDCLASSEX windowClass;
        windowClass.cbSize = sizeof(WNDCLASSEX);
        windowClass.style = CS_HREDRAW | CS_VREDRAW;
        windowClass.lpfnWndProc = WindowProc;
        windowClass.cbClsExtra = 0;
        windowClass.cbWndExtra = 0;
        windowClass.hInstance = instance;
        windowClass.hIcon = LoadIcon(0, IDI_SHIELD);
        windowClass.hCursor = LoadCursor(0, IDC_CROSS);
        windowClass.hbrBackground = 0;
        windowClass.lpszMenuName = 0;
        windowClass.lpszClassName = mData.GetClassName();
        windowClass.hIconSm = 0;

        return RegisterClassEx(&windowClass) != 0;
}

template<typename WindowData>
LRESULT CALLBACK Window<WindowData>::WindowProc(
        HWND   window,
        UINT   msg,
        WPARAM wParam,
        LPARAM lParam)
{
    // WM_GETMINMAXINFO is the first message sent to window proc
    // so just pass it to the default window procedure
    if(msg == WM_GETMINMAXINFO)
        return DefWindowProc(window, msg, wParam, lParam);

    if(msg == WM_NCCREATE)
    {
        // Retrieve create parameters
        LPCREATESTRUCT createStruct = (LPCREATESTRUCT)lParam;

        // Extract window data
        Window<WindowData>* thisPtr = (Window<WindowData>*)createStruct->lpCreateParams;

        // Set window user data
        SetWindowLongPtr(window, GWLP_USERDATA, (LONG_PTR)thisPtr);

        // Return callback function
        return thisPtr->mData.wndProcCallback(window, msg, wParam, lParam);
    }

    // Retrieve user data
    Window<WindowData>* thisPtr = (Window<WindowData>*)GetWindowLongPtr(window, GWLP_USERDATA);

    // Return callback function
    return thisPtr->mData.wndProcCallback(window, msg, wParam, lParam);
}