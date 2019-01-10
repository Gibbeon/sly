#include "sly/gl4/renderingdevice.h"
#include "sly/win32/os/window.h"

using namespace sly::gfx;

/* A simple function that will read a file into an allocated char pointer buffer */
char* filetobuf(char *file)
{
    FILE *fptr;
    long length;
    char *buf;

    fopen_s(&fptr, file, "rb"); /* Open file for reading */
    if (!fptr) /* Return NULL on failure */
        return NULL;
    fseek(fptr, 0, SEEK_END); /* Seek to the end of the file */
    length = ftell(fptr); /* Find out how many bytes into the file we are */
    buf = (char*)malloc(length+1); /* Allocate a buffer for the entire length of the file and a null terminator */
    fseek(fptr, 0, SEEK_SET); /* Go back to the beginning of the file */
    fread(buf, length, 1, fptr); /* Read the contents of the file in to the buffer */
    fclose(fptr); /* Close the file */
    buf[length] = 0; /* Null terminator */

    return buf; /* Return the buffer */
}


GL4Window::GL4Window()
{
	_window = new sly::os::Win32Window(1024,768,"GL HI!");
    InitializeExtensions();
    InitializeOpenGL(_window->GetHwnd(), _window->GetHeight(), _window->GetWidth(), 1.0, 0.0, true);
}

void GL4Window::swapBuffers()
{
    BeginScene(.4f, .4f, 1.0f, 1.0f);
    EndScene();
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

void GL4Window::InitializeExtensions()
{
	WNDCLASSEX wc;

    //Step 1: Registering the Window Class
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = (HINSTANCE)GetModuleHandle(NULL);
    wc.hIcon         = nullptr;
    wc.hCursor       = nullptr;
    wc.hbrBackground = nullptr;
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = "Core";
    wc.hIconSm       = nullptr;

    if(!RegisterClassEx(&wc))
    {
        return;
    }

    HWND fakeWND = CreateWindow(
        wc.lpszClassName, "Fake Window",      // window class, title
        WS_CLIPSIBLINGS | WS_CLIPCHILDREN, // style
        0, 0,                       // position x, y
        1, 1,                       // width, height
        NULL, NULL,                 // parent window, menu
        wc.hInstance, NULL);           // instance, param
 
 	if( !fakeWND )
    {
        int_t error = GetLastError();
		return;
    }

	HDC deviceContext;
	PIXELFORMATDESCRIPTOR pixelFormat;
	int error;
	HGLRC renderContext;
	bool_t result;

	// Get the device context for this window.
	deviceContext = GetDC(fakeWND);
	if(!deviceContext)
	{
		return;
	}

	ZeroMemory(&pixelFormat, sizeof(pixelFormat));
	pixelFormat.nSize = sizeof(pixelFormat);
	pixelFormat.nVersion = 1;
	pixelFormat.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pixelFormat.iPixelType = PFD_TYPE_RGBA;
	pixelFormat.cColorBits = 32;
	pixelFormat.cAlphaBits = 8;
	pixelFormat.cDepthBits = 24;

	// Set a temporary default pixel format.
	error = SetPixelFormat(deviceContext, 1, &pixelFormat);
	if(error != 1)
	{
		return;
	}

	// Create a temporary rendering context.
	renderContext = wglCreateContext(deviceContext);
	if(!renderContext)
	{
		return;
	}

	// Set the temporary rendering context as the current rendering context for this window.
	error = wglMakeCurrent(deviceContext, renderContext);
	if(error != 1)
	{
		return;
	}

	// Initialize the OpenGL extensions needed for this application.  Note that a temporary rendering context was needed to do so.
	result = LoadExtensionList();
	if(!result)
	{
		return;
	}

	// Release the temporary rendering context now that the extensions have been loaded.
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(renderContext);
	renderContext = NULL;

	// Release the device context for this window.
	ReleaseDC(fakeWND, deviceContext);
    DestroyWindow(fakeWND);

	deviceContext = 0;
}

bool_t GL4Window::InitializeOpenGL(HWND hwnd, int screenWidth, int screenHeight, float screenDepth, float screenNear, bool_t vsync)
{
	int attributeListInt[19];
	int pixelFormat[1];
	unsigned int formatCount;
	int result;
	PIXELFORMATDESCRIPTOR pixelFormatDescriptor;
	int attributeList[5];
	float fieldOfView, screenAspect;
	char *vendorString, *rendererString;

	// Get the device context for this window.
	m_deviceContext = GetDC(hwnd);
	if(!m_deviceContext)
	{
		return false;
	}
	
	// Support for OpenGL rendering.
	attributeListInt[0] = WGL_SUPPORT_OPENGL_ARB;
	attributeListInt[1] = TRUE;

	// Support for rendering to a window.
	attributeListInt[2] = WGL_DRAW_TO_WINDOW_ARB;
	attributeListInt[3] = TRUE;

	// Support for hardware acceleration.
	attributeListInt[4] = WGL_ACCELERATION_ARB;
	attributeListInt[5] = WGL_FULL_ACCELERATION_ARB;

	// Support for 24bit color.
	attributeListInt[6] = WGL_COLOR_BITS_ARB;
	attributeListInt[7] = 24;

	// Support for 24 bit depth buffer.
	attributeListInt[8] = WGL_DEPTH_BITS_ARB;
	attributeListInt[9] = 24;

	// Support for double buffer.
	attributeListInt[10] = WGL_DOUBLE_BUFFER_ARB;
	attributeListInt[11] = TRUE;

	// Support for swapping front and back buffer.
	attributeListInt[12] = WGL_SWAP_METHOD_ARB;
	attributeListInt[13] = WGL_SWAP_EXCHANGE_ARB;

	// Support for the RGBA pixel type.
	attributeListInt[14] = WGL_PIXEL_TYPE_ARB;
	attributeListInt[15] = WGL_TYPE_RGBA_ARB;

	// Support for a 8 bit stencil buffer.
	attributeListInt[16] = WGL_STENCIL_BITS_ARB;
	attributeListInt[17] = 8;

	// Null terminate the attribute list.
	attributeListInt[18] = 0;

	// Query for a pixel format that fits the attributes we want.
	result = wglChoosePixelFormatARB(m_deviceContext, attributeListInt, NULL, 1, pixelFormat, &formatCount);
	if(result != 1)
	{
		return false;
	}

	// If the video card/display can handle our desired pixel format then we set it as the current one.
	result = SetPixelFormat(m_deviceContext, pixelFormat[0], &pixelFormatDescriptor);
	if(result != 1)
	{
        int_t output = GetLastError();
		return false;
	}

	// Set the 4.0 version of OpenGL in the attribute list.
	attributeList[0] = WGL_CONTEXT_MAJOR_VERSION_ARB;
	attributeList[1] = 4;
	attributeList[2] = WGL_CONTEXT_MINOR_VERSION_ARB;
	attributeList[3] = 0;

	// Null terminate the attribute list.
	attributeList[4] = 0;

	// Create a OpenGL 4.0 rendering context.
	m_renderingContext = wglCreateContextAttribsARB(m_deviceContext, 0, attributeList);
	if(m_renderingContext == NULL)
	{
		return false;
	}

	// Set the rendering context to active.
	result = wglMakeCurrent(m_deviceContext, m_renderingContext);
	if(result != 1)
	{
		return false;
	}
	
	// Set the depth buffer to be entirely cleared to 1.0 values.
	glClearDepth(1.0f);

	// Enable depth testing.
	glEnable(GL_DEPTH_TEST);
	
	// Set the polygon winding to front facing for the left handed system.
	glFrontFace(GL_CW);

	// Enable back face culling.
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// Initialize the world/model matrix to the identity matrix.
	BuildIdentityMatrix(m_worldMatrix);

	// Set the field of view and screen aspect ratio.
	fieldOfView = 3.14159265358979323846f / 4.0f;
	screenAspect = (float)screenWidth / (float)screenHeight;

	// Build the perspective projection matrix.
	BuildPerspectiveFovLHMatrix(m_projectionMatrix, fieldOfView, screenAspect, screenNear, screenDepth);

	// Get the name of the video card.
	vendorString = (char*)glGetString(GL_VENDOR);
	rendererString = (char*)glGetString(GL_RENDERER);

	// Store the video card name in a class member variable so it can be retrieved later.
	strcpy_s(m_videoCardDescription, vendorString);
	strcat_s(m_videoCardDescription, " - ");
	strcat_s(m_videoCardDescription, rendererString);

	// Turn on or off the vertical sync depending on the input bool_t value.
	if(vsync)
	{
		result = wglSwapIntervalEXT(1);
	}
	else
	{
		result = wglSwapIntervalEXT(0);
	}

	// Check if vsync was set correctly.
	if(result != 1)
	{
		return false;
	}

	
    /* We're going to create a simple diamond made from lines */
    const GLfloat diamond[4][2] = {
    {  0.0,  1.0  }, /* Top point */
    {  1.0,  0.0  }, /* Right point */
    {  0.0, -1.0  }, /* Bottom point */
    { -1.0,  0.0  } }; /* Left point */

    const GLfloat colors[4][3] = {
    {  1.0,  0.0,  0.0  }, /* Red */
    {  0.0,  1.0,  0.0  }, /* Green */
    {  0.0,  0.0,  1.0  }, /* Blue */
    {  1.0,  1.0,  1.0  } }; /* White */

    /* These pointers will receive the contents of our shader source code files */
    char *vertexsource, *fragmentsource;

    /* These are handles used to reference the shaders */
    GLuint vertexshader, fragmentshader;

    /* This is a handle to the shader program */
    GLuint shaderprogram;

    /* Allocate and assign a Vertex Array Object to our handle */
    glGenVertexArrays(1, &vao);

    /* Bind our Vertex Array Object as the current used object */
    glBindVertexArray(vao);

    /* Allocate and assign two Vertex Buffer Objects to our handle */
    glGenBuffers(2, vbo);

    /* Bind our first VBO as being the active buffer and storing vertex attributes (coordinates) */
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

    /* Copy the vertex data from diamond to our buffer */
    /* 8 * sizeof(GLfloat) is the size of the diamond array, since it contains 8 GLfloat values */
    glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(GLfloat), diamond, GL_STATIC_DRAW);

    /* Specify that our coordinate data is going into attribute index 0, and contains two floats per vertex */
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);

    /* Enable attribute index 0 as being used */
    glEnableVertexAttribArray(0);

    /* Bind our second VBO as being the active buffer and storing vertex attributes (colors) */
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);

    /* Copy the color data from colors to our buffer */
    /* 12 * sizeof(GLfloat) is the size of the colors array, since it contains 12 GLfloat values */
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), colors, GL_STATIC_DRAW);

    /* Specify that our color data is going into attribute index 1, and contains three floats per vertex */
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    /* Enable attribute index 1 as being used */
    glEnableVertexAttribArray(1);

    /* Read our shaders into the appropriate buffers */
    vertexsource = filetobuf("c:\\tutorial2.vert");
    fragmentsource = filetobuf("c:\\tutorial2.frag");

    /* Create an empty vertex shader handle */
    vertexshader = glCreateShader(GL_VERTEX_SHADER);

    /* Send the vertex shader source code to GL */
    /* Note that the source code is NULL character terminated. */
    /* GL will automatically detect that therefore the length info can be 0 in this case (the last parameter) */
    glShaderSource(vertexshader, 1, (const char**)&vertexsource, 0);

    /* Compile the vertex shader */
    glCompileShader(vertexshader);

    glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &IsCompiled_VS);
    if(IsCompiled_VS == FALSE)
    {
       glGetShaderiv(vertexshader, GL_INFO_LOG_LENGTH, &maxLength);

       /* The maxLength includes the NULL character */
       vertexInfoLog = (char *)malloc(maxLength);

       glGetShaderInfoLog(vertexshader, maxLength, &maxLength, vertexInfoLog);

       /* Handle the error in an appropriate way such as displaying a message or writing to a log file. */
       /* In this simple program, we'll just leave */
       free(vertexInfoLog);
       return false;
    }

    /* Create an empty fragment shader handle */
    fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);

    /* Send the fragment shader source code to GL */
    /* Note that the source code is NULL character terminated. */
    /* GL will automatically detect that therefore the length info can be 0 in this case (the last parameter) */
    glShaderSource(fragmentshader, 1, (const char**)&fragmentsource, 0);

    /* Compile the fragment shader */
    glCompileShader(fragmentshader);

    glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &IsCompiled_FS);
    if(IsCompiled_FS == FALSE)
    {
       glGetShaderiv(fragmentshader, GL_INFO_LOG_LENGTH, &maxLength);

       /* The maxLength includes the NULL character */
       fragmentInfoLog = (char *)malloc(maxLength);

       glGetShaderInfoLog(fragmentshader, maxLength, &maxLength, fragmentInfoLog);

       /* Handle the error in an appropriate way such as displaying a message or writing to a log file. */
       /* In this simple program, we'll just leave */
       free(fragmentInfoLog);
       return false;
    }

    /* If we reached this point it means the vertex and fragment shaders compiled and are syntax error free. */
    /* We must link them together to make a GL shader program */
    /* GL shader programs are monolithic. It is a single piece made of 1 vertex shader and 1 fragment shader. */
    /* Assign our program handle a "name" */
    shaderprogram = glCreateProgram();

    /* Attach our shaders to our program */
    glAttachShader(shaderprogram, vertexshader);
    glAttachShader(shaderprogram, fragmentshader);

    /* Bind attribute index 0 (coordinates) to in_Position and attribute index 1 (color) to in_Color */
    /* Attribute locations must be setup before calling glLinkProgram. */
    glBindAttribLocation(shaderprogram, 0, "in_Position");
    glBindAttribLocation(shaderprogram, 1, "in_Color");

    /* Link our program */
    /* At this stage, the vertex and fragment programs are inspected, optimized and a binary code is generated for the shader. */
    /* The binary code is uploaded to the GPU, if there is no error. */
    glLinkProgram(shaderprogram);

    /* Again, we must check and make sure that it linked. If it fails, it would mean either there is a mismatch between the vertex */
    /* and fragment shaders. It might be that you have surpassed your GPU's abilities. Perhaps too many ALU operations or */
    /* too many texel fetch instructions or too many interpolators or dynamic loops. */

    glGetProgramiv(shaderprogram, GL_LINK_STATUS, (int *)&IsLinked);
    if(IsLinked == FALSE)
    {
       /* Noticed that glGetProgramiv is used to get the length for a shader program, not glGetShaderiv. */
       glGetProgramiv(shaderprogram, GL_INFO_LOG_LENGTH, &maxLength);

       /* The maxLength includes the NULL character */
       shaderProgramInfoLog = (char *)malloc(maxLength);

       /* Notice that glGetProgramInfoLog, not glGetShaderInfoLog. */
       glGetProgramInfoLog(shaderprogram, maxLength, &maxLength, shaderProgramInfoLog);

       /* Handle the error in an appropriate way such as displaying a message or writing to a log file. */
       /* In this simple program, we'll just leave */
       free(shaderProgramInfoLog);
       return false;
    }

    /* Load the shader into the rendering pipeline */
    glUseProgram(shaderprogram);

	return true;
}

void GL4Window::Shutdown(HWND hwnd)
{
	// Release the rendering context.
	if(m_renderingContext)
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(m_renderingContext);
		m_renderingContext = 0;
	}

	// Release the device context.
	if(m_deviceContext)
	{
		ReleaseDC(hwnd, m_deviceContext);
		m_deviceContext = 0;
	}

	
	return;
}

void GL4Window::BeginScene(float red, float green, float blue, float alpha)
{
	// Set the color to clear the screen to.
	glClearColor(red, green, blue, alpha); 

	// Clear the screen and depth buffer.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Loop our display increasing the number of shown vertexes each time.
     * Start with 2 vertexes (a line) and increase to 3 (a triangle) and 4 (a diamond) */
    for (int i=2; i <= 3; i++)
    {
        /* Make our background black */
        //glClearColor(0.0, 0.0, 0.0, 1.0);
        //glClear(GL_COLOR_BUFFER_BIT);

        /* Invoke glDrawArrays telling that our data is a line loop and we want to draw 2-4 vertexes */
        glDrawArrays(GL_TRIANGLE_STRIP, 0, i);

        /* Swap our buffers to make our changes visible */
        //SDL_GL_SwapWindow(window);

        /* Sleep for 2 seconds */
        //SDL_Delay(2000);
    }

	
	return;
}

void GL4Window::EndScene()
{
	// Present the back buffer to the screen since rendering is complete.
	::SwapBuffers(m_deviceContext);

	return;
}

bool_t GL4Window::LoadExtensionList()
{
	// Load the OpenGL extensions that this application will be using.
	wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
	if(!wglChoosePixelFormatARB)
	{
		return false;
	}

	wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
	if(!wglCreateContextAttribsARB)
	{
		return false;
	}

	wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)wglGetProcAddress("wglSwapIntervalEXT");
	if(!wglSwapIntervalEXT)
	{
		return false;
	}

	glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
	if(!glAttachShader)
	{
		return false;
	}

	glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
	if(!glBindBuffer)
	{
		return false;
	}

	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");
	if(!glBindVertexArray)
	{
		return false;
	}

	glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
	if(!glBufferData)
	{
		return false;
	}

	glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
	if(!glCompileShader)
	{
		return false;
	}

	glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
	if(!glCreateProgram)
	{
		return false;
	}

	glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
	if(!glCreateShader)
	{
		return false;
	}

	glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");
	if(!glDeleteBuffers)
	{
		return false;
	}

	glDeleteProgram = (PFNGLDELETEPROGRAMPROC)wglGetProcAddress("glDeleteProgram");
	if(!glDeleteProgram)
	{
		return false;
	}

	glDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
	if(!glDeleteShader)
	{
		return false;
	}

	glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)wglGetProcAddress("glDeleteVertexArrays");
	if(!glDeleteVertexArrays)
	{
		return false;
	}

	glDetachShader = (PFNGLDETACHSHADERPROC)wglGetProcAddress("glDetachShader");
	if(!glDetachShader)
	{
		return false;
	}

	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");
	if(!glEnableVertexAttribArray)
	{
		return false;
	}

	glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
	if(!glGenBuffers)
	{
		return false;
	}

	glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
	if(!glGenVertexArrays)
	{
		return false;
	}

	glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)wglGetProcAddress("glGetAttribLocation");
	if(!glGetAttribLocation)
	{
		return false;
	}

	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)wglGetProcAddress("glGetProgramInfoLog");
	if(!glGetProgramInfoLog)
	{
		return false;
	}

	glGetProgramiv = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv");
	if(!glGetProgramiv)
	{
		return false;
	}

	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
	if(!glGetShaderInfoLog)
	{
		return false;
	}

	glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
	if(!glGetShaderiv)
	{
		return false;
	}

	glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
	if(!glLinkProgram)
	{
		return false;
	}

	glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
	if(!glShaderSource)
	{
		return false;
	}

	glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
	if(!glUseProgram)
	{
		return false;
	}

	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
	if(!glVertexAttribPointer)
	{
		return false;
	}

	glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)wglGetProcAddress("glBindAttribLocation");
	if(!glBindAttribLocation)
	{
		return false;
	}

	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
	if(!glGetUniformLocation)
	{
		return false;
	}

	glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)wglGetProcAddress("glUniformMatrix4fv");
	if(!glUniformMatrix4fv)
	{
		return false;
	}

	glActiveTexture = (PFNGLACTIVETEXTUREPROC)wglGetProcAddress("glActiveTexture");
	if(!glActiveTexture)
	{
		return false;
	}

	glUniform1i = (PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i");
	if(!glUniform1i)
	{
		return false;
	}

	glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)wglGetProcAddress("glGenerateMipmap");
	if(!glGenerateMipmap)
	{
		return false;
	}

	glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glDisableVertexAttribArray");
	if(!glDisableVertexAttribArray)
	{
		return false;
	}

	glUniform3fv = (PFNGLUNIFORM3FVPROC)wglGetProcAddress("glUniform3fv");
	if(!glUniform3fv)
	{
		return false;
	}

	glUniform4fv = (PFNGLUNIFORM4FVPROC)wglGetProcAddress("glUniform4fv");
	if(!glUniform4fv)
	{
		return false;
	}


	return true;
}

void GL4Window::GetWorldMatrix(float* matrix)
{
	matrix[0]  = m_worldMatrix[0];
	matrix[1]  = m_worldMatrix[1];
	matrix[2]  = m_worldMatrix[2];
	matrix[3]  = m_worldMatrix[3];

	matrix[4]  = m_worldMatrix[4];
	matrix[5]  = m_worldMatrix[5];
	matrix[6]  = m_worldMatrix[6];
	matrix[7]  = m_worldMatrix[7];

	matrix[8]  = m_worldMatrix[8];
	matrix[9]  = m_worldMatrix[9];
	matrix[10] = m_worldMatrix[10];
	matrix[11] = m_worldMatrix[11];

	matrix[12] = m_worldMatrix[12];
	matrix[13] = m_worldMatrix[13];
	matrix[14] = m_worldMatrix[14];
	matrix[15] = m_worldMatrix[15];

	return;
}

void GL4Window::GetProjectionMatrix(float* matrix)
{
	matrix[0]  = m_projectionMatrix[0];
	matrix[1]  = m_projectionMatrix[1];
	matrix[2]  = m_projectionMatrix[2];
	matrix[3]  = m_projectionMatrix[3];

	matrix[4]  = m_projectionMatrix[4];
	matrix[5]  = m_projectionMatrix[5];
	matrix[6]  = m_projectionMatrix[6];
	matrix[7]  = m_projectionMatrix[7];

	matrix[8]  = m_projectionMatrix[8];
	matrix[9]  = m_projectionMatrix[9];
	matrix[10] = m_projectionMatrix[10];
	matrix[11] = m_projectionMatrix[11];

	matrix[12] = m_projectionMatrix[12];
	matrix[13] = m_projectionMatrix[13];
	matrix[14] = m_projectionMatrix[14];
	matrix[15] = m_projectionMatrix[15];

	return;
}

void GL4Window::GetVideoCardInfo(char* cardName)
{
	strcpy_s(cardName, 128, m_videoCardDescription);
	return;
}

void GL4Window::BuildIdentityMatrix(float* matrix)
{
	matrix[0]  = 1.0f;
	matrix[1]  = 0.0f;
	matrix[2]  = 0.0f;
	matrix[3]  = 0.0f;

	matrix[4]  = 0.0f;
	matrix[5]  = 1.0f;
	matrix[6]  = 0.0f;
	matrix[7]  = 0.0f;

	matrix[8]  = 0.0f;
	matrix[9]  = 0.0f;
	matrix[10] = 1.0f;
	matrix[11] = 0.0f;

	matrix[12] = 0.0f;
	matrix[13] = 0.0f;
	matrix[14] = 0.0f;
	matrix[15] = 1.0f;

	return;
}

void GL4Window::BuildPerspectiveFovLHMatrix(float* matrix, float fieldOfView, float screenAspect, float screenNear, float screenDepth)
{
	matrix[0]  = 1.0f / (screenAspect * tan(fieldOfView * 0.5f));
	matrix[1]  = 0.0f;
	matrix[2]  = 0.0f;
	matrix[3]  = 0.0f;

	matrix[4]  = 0.0f;
	matrix[5]  = 1.0f / tan(fieldOfView * 0.5f);
	matrix[6]  = 0.0f;
	matrix[7]  = 0.0f;

	matrix[8]  = 0.0f;
	matrix[9]  = 0.0f;
	matrix[10] = screenDepth / (screenDepth - screenNear);
	matrix[11] = 1.0f;

	matrix[12] = 0.0f;
	matrix[13] = 0.0f;
	matrix[14] = (-screenNear * screenDepth) / (screenDepth - screenNear);
	matrix[15] = 0.0f;

	return;
}

void GL4Window::MatrixRotationY(float* matrix, float angle)
{
	matrix[0]  = cosf(angle);
	matrix[1]  = 0.0f;
	matrix[2]  = -sinf(angle);
	matrix[3]  = 0.0f;

	matrix[4]  = 0.0f;
	matrix[5]  = 1.0f;
	matrix[6]  = 0.0f;
	matrix[7]  = 0.0f;

	matrix[8]  = sinf(angle);
	matrix[9]  = 0.0f;
	matrix[10] = cosf(angle);
	matrix[11] = 0.0f;

	matrix[12] = 0.0f;
	matrix[13] = 0.0f;
	matrix[14] = 0.0f;
	matrix[15] = 1.0f;

	return;
}

void GL4Window::MatrixTranslation(float* matrix, float x, float y, float z)
{
	matrix[0]  = 1.0f;
	matrix[1]  = 0.0f;
	matrix[2]  = 0.0f;
	matrix[3]  = 0.0f;

	matrix[4]  = 0.0f;
	matrix[5]  = 1.0f;
	matrix[6]  = 0.0f;
	matrix[7]  = 0.0f;

	matrix[8]  = 0.0f;
	matrix[9]  = 0.0f;
	matrix[10] = 1.0f;
	matrix[11] = 0.0f;

	matrix[12] = x;
	matrix[13] = y;
	matrix[14] = z;
	matrix[15] = 1.0f;

	return;
}

void GL4Window::MatrixMultiply(float* result, float* matrix1, float* matrix2)
{
	result[0]  = (matrix1[0] * matrix2[0]) + (matrix1[1] * matrix2[4]) + (matrix1[2] * matrix2[8]) + (matrix1[3] * matrix2[12]);
	result[1]  = (matrix1[0] * matrix2[1]) + (matrix1[1] * matrix2[5]) + (matrix1[2] * matrix2[9]) + (matrix1[3] * matrix2[13]);
	result[2]  = (matrix1[0] * matrix2[2]) + (matrix1[1] * matrix2[6]) + (matrix1[2] * matrix2[10]) + (matrix1[3] * matrix2[14]);
	result[3]  = (matrix1[0] * matrix2[3]) + (matrix1[1] * matrix2[7]) + (matrix1[2] * matrix2[11]) + (matrix1[3] * matrix2[15]);

	result[4]  = (matrix1[4] * matrix2[0]) + (matrix1[5] * matrix2[4]) + (matrix1[6] * matrix2[8]) + (matrix1[7] * matrix2[12]);
	result[5]  = (matrix1[4] * matrix2[1]) + (matrix1[5] * matrix2[5]) + (matrix1[6] * matrix2[9]) + (matrix1[7] * matrix2[13]);
	result[6]  = (matrix1[4] * matrix2[2]) + (matrix1[5] * matrix2[6]) + (matrix1[6] * matrix2[10]) + (matrix1[7] * matrix2[14]);
	result[7]  = (matrix1[4] * matrix2[3]) + (matrix1[5] * matrix2[7]) + (matrix1[6] * matrix2[11]) + (matrix1[7] * matrix2[15]);

	result[8]  = (matrix1[8] * matrix2[0]) + (matrix1[9] * matrix2[4]) + (matrix1[10] * matrix2[8]) + (matrix1[11] * matrix2[12]);
	result[9]  = (matrix1[8] * matrix2[1]) + (matrix1[9] * matrix2[5]) + (matrix1[10] * matrix2[9]) + (matrix1[11] * matrix2[13]);
	result[10] = (matrix1[8] * matrix2[2]) + (matrix1[9] * matrix2[6]) + (matrix1[10] * matrix2[10]) + (matrix1[11] * matrix2[14]);
	result[11] = (matrix1[8] * matrix2[3]) + (matrix1[9] * matrix2[7]) + (matrix1[10] * matrix2[11]) + (matrix1[11] * matrix2[15]);

	result[12] = (matrix1[12] * matrix2[0]) + (matrix1[13] * matrix2[4]) + (matrix1[14] * matrix2[8]) + (matrix1[15] * matrix2[12]);
	result[13] = (matrix1[12] * matrix2[1]) + (matrix1[13] * matrix2[5]) + (matrix1[14] * matrix2[9]) + (matrix1[15] * matrix2[13]);
	result[14] = (matrix1[12] * matrix2[2]) + (matrix1[13] * matrix2[6]) + (matrix1[14] * matrix2[10]) + (matrix1[15] * matrix2[14]);
	result[15] = (matrix1[12] * matrix2[3]) + (matrix1[13] * matrix2[7]) + (matrix1[14] * matrix2[11]) + (matrix1[15] * matrix2[15]);

	return;
}