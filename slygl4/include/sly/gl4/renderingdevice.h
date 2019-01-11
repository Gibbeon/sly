#pragma once

#include "sly/gl4.h"
#include "sly/gfx.h"
#include "sly/win32/os/window.h"

namespace sly {
	namespace gfx {
		class GL4Window : public IWindow {
		public:
			GL4Window();

			virtual void init(Window& desc) {}

            virtual void processMessages() { _window->ProcessMessages(); }
            virtual void swapBuffers();

            virtual void setVisible(bool_t show) { _window->Show(); }

            //virtual IRenderTarget&  getBackBuffer() { return; }
            //virtual ICommandQueue& getDirectCommandQueue() { return; }

			//virtual bool_t Attach(IDrawWindow* pWindow);
			//virtual bool_t SwapBuffers();

			void InitializeExtensions();
		private:

			bool_t InitializeOpenGL(HWND, int, int, float, float, bool_t);
			void Shutdown(HWND);

			void BeginScene(float, float, float, float);
			void EndScene();

			void GetWorldMatrix(float*);
			void GetProjectionMatrix(float*);
			void GetVideoCardInfo(char*);

			void BuildIdentityMatrix(float*);
			void BuildPerspectiveFovLHMatrix(float*, float, float, float, float);
			void MatrixRotationY(float*, float);
			void MatrixTranslation(float*, float, float, float);
			void MatrixMultiply(float*, float*, float*);

		private:
			bool_t LoadExtensionList();

		private:
			HDC m_deviceContext;
			HGLRC m_renderingContext;

			PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
			PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
			PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT;

			float m_worldMatrix[16];
			float m_projectionMatrix[16];
			char m_videoCardription[128];

			GLuint vao, vbo[2]; /* Create handles for our Vertex Array Object and two Vertex Buffer Objects */
			int IsCompiled_VS, IsCompiled_FS;
			int IsLinked;
			int maxLength;
			char *vertexInfoLog;
			char *fragmentInfoLog;
			char *shaderProgramInfoLog;

			sly::os::Win32Window* _window;

		public:
			PFNGLATTACHSHADERPROC glAttachShader;
			PFNGLBINDBUFFERPROC glBindBuffer;
			PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
			PFNGLBUFFERDATAPROC glBufferData;
			PFNGLCOMPILESHADERPROC glCompileShader;
			PFNGLCREATEPROGRAMPROC glCreateProgram;
			PFNGLCREATESHADERPROC glCreateShader;
			PFNGLDELETEBUFFERSPROC glDeleteBuffers;
			PFNGLDELETEPROGRAMPROC glDeleteProgram;
			PFNGLDELETESHADERPROC glDeleteShader;
			PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
			PFNGLDETACHSHADERPROC glDetachShader;
			PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
			PFNGLGENBUFFERSPROC glGenBuffers;
			PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
			PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
			PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
			PFNGLGETPROGRAMIVPROC glGetProgramiv;
			PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
			PFNGLGETSHADERIVPROC glGetShaderiv;
			PFNGLLINKPROGRAMPROC glLinkProgram;
			PFNGLSHADERSOURCEPROC glShaderSource;
			PFNGLUSEPROGRAMPROC glUseProgram;
			PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
			PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
			PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
			PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
			PFNGLACTIVETEXTUREPROC glActiveTexture;
			PFNGLUNIFORM1IPROC glUniform1i;
			PFNGLGENERATEMIPMAPPROC glGenerateMipmap;
			PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
			PFNGLUNIFORM3FVPROC glUniform3fv;
			PFNGLUNIFORM4FVPROC glUniform4fv;
		};
	}

} 