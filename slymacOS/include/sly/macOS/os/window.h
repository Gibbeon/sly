#pragma once

#include <string>
#include "sly/os/window.h"
#include "sly/os/operatingsystem.h"
#include "sly/macOS.h"

namespace sly {
    namespace os {

        class MacOSWindow : public IWindow
        {
        public:
                    MacOSWindow() : IWindow() {}
            virtual ~MacOSWindow() {} 

            virtual retval<void> init(WindowDesc& desc);
            static void onRender(const sly::os::MacOSWindow& window);
            virtual bool_t show() { return true; }

            // Accessors.
            virtual uint_t getWidth() const         { return m_width; }
            virtual uint_t getHeight() const        { return m_height; }
            virtual std::string getTitle() const       { return m_title; }

            //virtual HWND GetHwnd() const { return m_hWND; }
            //virtual void SetHwnd(HWND hWND) { m_hWND = hWND; }

            virtual void onRender() const;

            virtual bool_t processMessages();

        protected:
            //static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

        private:
            std::string m_title;
            uint_t m_width;
            uint_t m_height;
            //HWND m_hWND;
        };
    }
}