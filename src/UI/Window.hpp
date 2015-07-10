#ifndef HITMON_WINDOW
#define HITMON_WINDOW

namespace UI
{

#include <Windows.h>

//==================================================
/// \brief Wrapper class for creating windows using the WINAPI.
///
/// This class serves as a wrapper to simplify the window creation
/// process. All you have to do is to pass it a template parameter
/// with the struct/class of your choice. Your class can contain
/// whatever data you want to use in your window proc but you NEED
/// to have 3 public members:
/// -# LPCTSTR wndClassName
/// -# Window<{your struct name}>* thisWindow
/// -# WNDPROC wndProcCallback
/// Here is an example of a window data class
/// \code
/// class MyWindowData
/// {
/// public:
///     //------------------------
///     // Members you NEED to have
///     Window<MyWindowData>* thisWindow;
///
///     // Instead of this you can just create your own window
///     // proc as member function
///     WNDPROC wndProcCallback;
///     //------------------------
///
///     LPCTSTR GetClassName()
///     {
///         return "MyWindowName";
///     }
///
///     //------------------------
///     // Your members
///     //------------------------
///     int randomIntData;
///     char* uselessCharPtr;
///     Whatever* whateverYouWant;
///
///     // CAREFUL: The wndClassName member MUST HAVE A VALUE
///     // BEFORE you call Window<WindowData>::Init() function.
///
///     MyWindowData(LPCTSTR className)
///         : wndClassName(className),
///         wndProcCallback(DefWindowProc)
///     {
///     }
/// };
/// \endcode
///
/// \tparam WindowData This template parameter should be a struct or a
///         class with at least 3 public members (LPCTSTR, 
///         Window<WindowData>*, WNDPROC).
//==================================================
template<typename WindowData>
class Window
{
public:
    //==================================================
    /// Constructor
    ///
    /// \param data The struct or class that represents the
    ///        window data.
    //==================================================
    Window(WindowData data);

    //==================================================
    /// \brief Function to actually create the window.
    ///
    /// First, registers the window and then creates it.
    /// TODO: Add a way to control the window creation.
    ///
    /// \return True if everything are good, False otherwise.
    ///         In case of False, you can use WINAPI's GetLastError()
    ///         function to inspect the error code and find out what
    ///         went wrong.
    //==================================================
    bool Init(HINSTANCE instance);

    //==================================================
    /// \brief Getter for class member window.
    ///
    /// \return A handle to the window.
    //==================================================
    HWND GetWindow() const;

    //==================================================
    /// \brief Returns a pointer to this window's data.
    ///
    /// \return Pointer to class member window data.
    //==================================================
    WindowData* GetDataPtr();

private:
    /// Window's data.
    WindowData mData;

    /// Handle to the window.
    HWND mWindow;

    //==================================================
    /// Registers the window class
    //==================================================
    bool RegisterWindowClass(HINSTANCE instance);

    //==================================================
    /// \brief The default window proc of the window.
    ///
    /// When WM_NCCREATE message is sent, retrieves the window's
    /// data from message's lparam and then uses
    /// SetWindowLongPtr to set it's pointer to the GWLP_USERDATA
    /// space of the window.
    /// This is a hackish solution so we can use the window proc from
    /// inside a class.
    ///
    /// \param window Handle to the window.
    /// \param msg The message passed in proc.
    /// \param wParam wParam of the message.
    /// \param lParam lParam of the message.
    ///
    //==================================================
    static LRESULT CALLBACK WindowProc(
        HWND   window,
        UINT   msg,
        WPARAM wParam,
        LPARAM lParam);
};

// Include the ipp file that contains the implementations of the above functions.
// That's because I wanted to avoid having all of the in the header file.
#include "Window.ipp"

} // namespace UI

#endif