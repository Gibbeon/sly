#pragma once

#include <string>
#include "sly/os/window.h"
#include "sly/win32.h"

namespace sly {
    namespace os {

        class Win32Window : public IWindow
        {
        public:
        
            virtual ~Win32Window() {} 

            virtual retval<void> init(WindowDesc& desc);
            virtual void onRender();
            virtual bool_t show() { return ShowWindow(m_hWND, SW_SHOWDEFAULT); }

            // Accessors.
            virtual uint_t getWidth() const         { return m_width; }
            virtual uint_t getHeight() const        { return m_height; }
            virtual std::string getTitle() const       { return m_title; }

            virtual HWND getHwnd() const { return m_hWND; }
            virtual void setHwnd(HWND hWND) { m_hWND = hWND; }

            virtual bool_t processMessages();

        protected:
            static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

        private:
            std::string m_title;
            uint_t m_width;
            uint_t m_height;
            HWND m_hWND;
        };
    }
}