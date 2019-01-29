#pragma once

#include <string>
#include "sly/macOS.h"

namespace sly {
    namespace os {
        class MacOSWindow
        {
            public:
                MacOSWindow(uint_t width, uint_t height, std::string pszTitle);

                static void OnRender(const sly::os::MacOSWindow& window);

                virtual bool_t Show() { return true; }

                // Accessors.
                virtual uint_t GetWidth() const         { return m_width; }
                virtual uint_t GetHeight() const        { return m_height; }
                virtual std::string GetTitle() const       { return m_title; }

                //virtual HWND GetHwnd() const { return m_hWND; }
                //virtual void SetHwnd(HWND hWND) { m_hWND = hWND; }

                virtual bool_t ProcessMessages();

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