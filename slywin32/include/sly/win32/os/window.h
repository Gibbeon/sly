#pragma once

#include "sly/win32.h"
#include "sly/win32/os/windowsystem.h"

namespace sly {
    namespace os {

        class Win32Window : public IWindow
        {
        public:
            Win32Window(Win32WindowSystem& parent);
            virtual ~Win32Window() {} 

            virtual retval<void> init(const WindowDesc& desc = WindowBuilder().build());
            virtual retval<void> release();
            
            virtual void setVisible(bool_t visible) { ShowWindow(_hWND, visible ? SW_SHOW : SW_HIDE); }

                   // Accessors.
            virtual uint_t getWidth() const         { return _width; }
            virtual uint_t getHeight() const        { return _height; }
            virtual gsl::czstring<> getTitle() const       { return _title; }

            virtual HWND getHwnd() const { return _hWND; }
            virtual void setHwnd(HWND hWND) { _hWND = hWND; }

            virtual bool_t processMessages();

        protected:
            static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

        private:
            Win32WindowSystem& _parent;
            gsl::czstring<> _title;
            uint_t _width;
            uint_t _height;
            HWND _hWND;
            bool_t _initialized;
        };
    }
}