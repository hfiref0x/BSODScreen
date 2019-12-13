/*******************************************************************************
*
*  (C) COPYRIGHT AUTHORS, 2018 - 2019
*
*  TITLE:       MAIN.C
*
*  VERSION:     1.02
*
*  DATE:        01 Dec 2019
*
*  Screensaver entry point.
*
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
* ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
* TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
* PARTICULAR PURPOSE.
*
*******************************************************************************/

#pragma once

#define OEMRESOURCE

#include "global.h"

using namespace Gdiplus;

#define ROS_SCR_MAX_SCENE_TEXT      16

static const char   *SceneText[ROS_SCR_MAX_SCENE_TEXT] = {
    "MODERN",
    "DYNAMIC",
    "BEAUTIFUL",
    "MINIMALISTIC",
    "ENERGETIC",
    "SOPHISTICATED",
    "That's ReactOS",
    "Not just an Open but also",
    "INSPIRED BY:",
    "IDA Pro",
    "wnt4sp6a.zip (235 MB, 912 MB unpacked)",
    "w2ksp1.zip (203 MB, 627 MB unpacked)",
    "Creative Copy-Paste",
    "Crowdsourcing",
    "Sh*tpostings",
    "BSOD"
};

int         quit = 0;
ULONG       screen_width, screen_height, text_index = 0;
ULONG_PTR   gdiplusToken;
double      g_FOV = 60.0, screen_ar = 1.0;

BOOL        g_IsReactOS = FALSE;
BOOL        g_bCrash = FALSE;

typedef double(__cdecl *PSINCOSFN)(double x);

#define IDB_bragin_obshak_jpg           TEXT("BRAGIN_OBSHAK.JPG")
#define IDB_ReactOS_logo_png            TEXT("REACTOS_LOGO.PNG")
#define IDB_Impression_png              TEXT("IMPRESSION.PNG")
#define IDB_fundraising_png             TEXT("FUNDRAISING.PNG")
#define IDB_BSOD_PNG                    TEXT("BSOD.PNG")
#define IDB_ROS_Butthurt_png            TEXT("ROS_BUTTHURT.PNG")
#define IDB_pepe_frog_png               TEXT("PEPE-FROG.PNG")
#define IDB_bsod3_png                   TEXT("BSOD3.PNG")
#define IDB_font_png                    TEXT("FONT.PNG")

#define ROS_SCR_SIZEOF_VERTEX_ARRAY     24
#define ROS_SCR_MAX_TEXTURES            16
#define ROS_SCR_MAIN_TIMER              1001
#define ROS_SCR_TEXT_TIMER              1002

static GLint    texutre_ids[ROS_SCR_MAX_TEXTURES];

static const double qvertex[ROS_SCR_SIZEOF_VERTEX_ARRAY][8] = {
    {-0.5, -0.5, -0.5,1.0,  0.0, 0.0, 0.0, 0.0}, // vertex+texcoord
    {-0.5, 0.5, -0.5, 1.0,  1.0, 0.0, 0.0, 0.0},
    {0.5 , 0.5,-0.5,  1.0,  1.0, 1.0, 0.0, 0.0},
    {0.5, -0.5, -0.5, 1.0,  0.0, 1.0, 0.0, 0.0},

    {0.5, -0.5, 0.5, 1.0,  1.0, 0.0, 0.0, 0.0},
    {0.5, 0.5,  0.5, 1.0,  1.0, 1.0, 0.0, 0.0},
    {-0.5, 0.5,   0.5, 1.0,  0.0, 1.0, 0.0, 0.0},
    {-0.5, -0.5,  0.5, 1.0,  0.0, 0.0, 0.0, 0.0},

    {0.5, -0.5, -0.5, 1.0,  0.0, 0.0, 0.0, 0.0},
    {0.5, 0.5,  -0.5, 1.0,  1.0, 0.0, 0.0, 0.0},
    {0.5, 0.5,   0.5, 1.0,  1.0, 1.0, 0.0, 0.0},
    {0.5, -0.5, 0.5, 1.0,   0.0, 1.0, 0.0, 0.0},

    {-0.5, -0.5, -0.5, 1.0, 0.0, 0.0, 0.0, 0.0},
    {-0.5, 0.5, -0.5, 1.0,  1.0, 0.0, 0.0, 0.0},
    {-0.5, 0.5, 0.5, 1.0,   1.0, 1.0, 0.0, 0.0},
    {-0.5, -0.5, 0.5, 1.0,  0.0, 1.0, 0.0, 0.0},

    {-0.5, 0.5, -0.5, 1.0,  0.0, 1.0, 0.0, 0.0},
    {0.5, 0.5,  -0.5, 1.0,  1.0, 1.0, 0.0, 0.0},
    {0.5, 0.5,   0.5, 1.0,  1.0, 0.0, 0.0, 0.0},
    {-0.5, 0.5,  0.5, 1.0,  0.0, 0.0, 0.0, 0.0},

    {-0.5, -0.5, -0.5, 1.0, 0.0, 0.0, 0.0, 0.0},
    {0.5, -0.5,  -0.5, 1.0, 1.0, 0.0, 0.0, 0.0},
    {0.5, -0.5,   0.5, 1.0, 1.0, 1.0, 0.0, 0.0},
    {-0.5, -0.5,  0.5, 1.0, 0.0, 1.0, 0.0, 0.0}
};

/*

Initialize OpenGL context with x4 AA

*/
HDC InitWGL(HWND hwnd, HGLRC *glrc)
{
    PIXELFORMATDESCRIPTOR	pfd;
    int						index = 0;
    HDC						wdc;
    HGLRC					ctx = NULL;
    UINT					nfmt;
    HWND					ProbeWindow;

    PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = NULL;

    int	attribs[26] = {
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
        WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
        WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
        WGL_COLOR_BITS_ARB, 32,
        WGL_ALPHA_BITS_ARB, 8,
        WGL_DEPTH_BITS_ARB, 24,
        WGL_STENCIL_BITS_ARB, 0,
        WGL_SWAP_METHOD_ARB, WGL_SWAP_EXCHANGE_ARB,
        WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
        WGL_SAMPLE_BUFFERS_ARB, 1,
        WGL_SAMPLES_ARB, 4,
        0, 0 };

    RtlSecureZeroMemory(&pfd, sizeof(pfd));
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER |
        PFD_SUPPORT_OPENGL | PFD_GENERIC_ACCELERATED | PFD_SWAP_EXCHANGE;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 32;
    pfd.cAlphaBits = 8;
    pfd.cDepthBits = 24;
    pfd.iLayerType = PFD_MAIN_PLANE;

    ProbeWindow = CreateWindowEx(0, TEXT("STATIC"), NULL,
        WS_VISIBLE | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_CHILD | SS_BLACKRECT,
        0, 0, 128, 128, hwnd, NULL, NULL, NULL);
    if (!ProbeWindow)
        return NULL;

    wdc = GetDC(ProbeWindow);
    while (wdc) {
        index = ChoosePixelFormat(wdc, &pfd);
        if (index == 0)
            break;

        if (!SetPixelFormat(wdc, index, &pfd))
            break;

        ctx = wglCreateContext(wdc);
        if (!ctx)
            break;

        if (!wglMakeCurrent(wdc, ctx))
            break;

        wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
        if (!wglChoosePixelFormatARB)
            break;

        /* get an index of pixel format we need */

        wglChoosePixelFormatARB(wdc, (const int *)&attribs, NULL, 1, &index, &nfmt);
        break;
    }

    /* destroying all of the probe stuff */
    wglMakeCurrent(NULL, NULL);

    if (ctx)
        wglDeleteContext(ctx);

    if (wdc)
        ReleaseDC(ProbeWindow, wdc);

    DestroyWindow(ProbeWindow);
    ctx = NULL;

    /* create actual GL context with pixel format index we found before */
    wdc = GetDC(hwnd);
    while (wdc) {

        if (!SetPixelFormat(wdc, index, &pfd))
            break;

        ctx = wglCreateContext(wdc);
        if (!ctx)
            break;

        if (wglMakeCurrent(wdc, ctx)) {
            *glrc = ctx;
            return wdc; // Success
        }

        /* Error */
        break;
    }

    /* Cleanup on error */
    wglMakeCurrent(NULL, NULL);

    if (ctx)
        wglDeleteContext(ctx);

    if (wdc)
        ReleaseDC(hwnd, wdc);

    return NULL;
}

void AppLoadTextureFromResource(LPCTSTR ResourceName, GLint texture_id)
{
    HBITMAP		newBitmap;
    BITMAP      obj_bmp;
    Bitmap		*gdipImage;
    Color		bgcolor(255, 255, 255, 255);
    UINT        tex_width, tex_height;
    HRSRC       hRsrc;
    HGLOBAL     res_data;
    LPSTREAM    res_stream;
    ULONG       tex_size;

    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);

    // too laggy with software rendering
    if (g_IsReactOS == FALSE) {
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 8.0);
    }

    hRsrc = FindResource(GetModuleHandle(NULL), ResourceName, RT_RCDATA);
    if (!hRsrc)
        return;

    res_data = LoadResource(GetModuleHandle(NULL), hRsrc);
    if (!res_data)
        return;

    tex_size = SizeofResource(GetModuleHandle(NULL), hRsrc);

    if (S_OK != CreateStreamOnHGlobal(NULL, TRUE, &res_stream))
        return;

    res_stream->Write(res_data, tex_size, NULL);

    gdipImage = Bitmap::FromStream(res_stream);
    if (gdipImage == NULL)
    {
        res_stream->Release();
        return;
    }

    newBitmap = NULL;
    gdipImage->GetHBITMAP(bgcolor, &newBitmap);

    if (newBitmap != NULL)
    {
        tex_width = gdipImage->GetWidth();
        tex_height = gdipImage->GetHeight();

        memset(&obj_bmp, 0, sizeof(obj_bmp));
        GetObject(newBitmap, sizeof(obj_bmp), (LPVOID)&obj_bmp);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex_width, tex_height, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, obj_bmp.bmBits);
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, tex_width, tex_height, GL_BGRA_EXT, GL_UNSIGNED_BYTE, obj_bmp.bmBits);

        DeleteObject(newBitmap);
    }

    delete gdipImage;
    res_stream->Release();
}

void AppInitialize()
{
    GdiplusStartupInput gdiplusStartupInput;

    // Initialize GDI+.
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);
}

void AppCleanup()
{
    GdiplusShutdown(gdiplusToken);
}

void DrawChar(double x, double y, double char_size, char c)
{
    const double    char_tex_size = 1.0 / 16.0;
    const double    char_size_x = char_size, char_size_y = char_size_x * screen_ar;
    double          tx0, ty0, tx1, ty1;
    int             cy = 15 - c / 16, cx = c % 16;

    tx0 = cx * char_tex_size;
    tx1 = tx0 + char_tex_size;

    ty0 = cy * char_tex_size + (1.0 / 2048.0);
    ty1 = ty0 + char_tex_size - (1.0 / 4096.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_2D, texutre_ids[8]);

    glBegin(GL_QUADS);

    glTexCoord2d(tx0, ty0);
    glVertex3d(x, y, 0);

    glTexCoord2d(tx1, ty0);
    glVertex3d(x + char_size_x, y, 0);

    glTexCoord2d(tx1, ty1);
    glVertex3d(x + char_size_x, y + char_size_y, 0);

    glTexCoord2d(tx0, ty1);
    glVertex3d(x, y + char_size_y, 0);

    glEnd();
}

void SceneDrawText(const char *text)
{
    const double char_size = 32.0 / screen_width;
    double  x = -0.9, y = -0.7;
    int     pos_x = 0, pos_y = 0;

    while (*text != '\0')
    {
        if (*text == '\n')
        {
            pos_x = 0;
            ++pos_y;
        }
        else
        {
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glColor4d(0, 0, 0, 1.0);
            DrawChar(x + pos_x * char_size, y - pos_y * char_size * screen_ar, char_size, *text);
            glColor4d(0.25, 1, 0.25, 1.0);
            DrawChar(-0.002 + x + pos_x * char_size, 0.003 + y - pos_y * char_size * screen_ar, char_size, *text);
            ++pos_x;
        }

        ++text;
    }
}

DWORD WINAPI DrawingThread(LPVOID lpThreadParameter)
{
    HWND	MainWindow = (HWND)lpThreadParameter;
    HDC     MainWindowDC;
    HGLRC	ctx;
    double	angle, sw = screen_width, sh = screen_height;
    int     iv;
    ULONG   index;

    PSINCOSFN	ntsin, ntcos;
    HMODULE		ntdll = GetModuleHandle(TEXT("ntdll.dll"));

    if (!ntdll)
        return 0;

    ntsin = (PSINCOSFN)GetProcAddress(ntdll, "sin");
    ntcos = (PSINCOSFN)GetProcAddress(ntdll, "cos");

    if ((ntsin == NULL) || (ntcos == NULL))
        return 0;

    ctx = NULL;
    MainWindowDC = InitWGL(MainWindow, &ctx);
    if (!MainWindowDC)
        return 0;

    screen_ar = sw / sh;

    glGenTextures(ROS_SCR_MAX_TEXTURES, (GLuint *)&texutre_ids);

    AppLoadTextureFromResource(IDB_bragin_obshak_jpg, texutre_ids[0]);
    AppLoadTextureFromResource(IDB_ReactOS_logo_png, texutre_ids[1]);
    AppLoadTextureFromResource(IDB_Impression_png, texutre_ids[2]);
    AppLoadTextureFromResource(IDB_fundraising_png, texutre_ids[3]);
    AppLoadTextureFromResource(IDB_BSOD_PNG, texutre_ids[4]);
    AppLoadTextureFromResource(IDB_ROS_Butthurt_png, texutre_ids[5]);
    AppLoadTextureFromResource(IDB_pepe_frog_png, texutre_ids[6]);
    AppLoadTextureFromResource(IDB_bsod3_png, texutre_ids[7]);
    AppLoadTextureFromResource(IDB_font_png, texutre_ids[8]);

    glEnable(GL_MULTISAMPLE_ARB);
    glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);

    glDrawBuffer(GL_BACK);
    angle = 0;

    while (!quit) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);
        glBlendFunc(GL_ONE, GL_ZERO);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(g_FOV, screen_ar, 0.1, 1000);
        glTranslated(-1.0, 0, -3.0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotated(angle, ntsin(angle / 20), ntcos(angle / 30), 0);

        /* The CUBE */

        glColor4d(1, 1, 1, 0);
        glEnable(GL_TEXTURE_2D);
        for (index = 0; index < ROS_SCR_SIZEOF_VERTEX_ARRAY / 4; ++index)
        {
            glBindTexture(GL_TEXTURE_2D, texutre_ids[index % 6]);
            glBegin(GL_QUADS);
            for (iv = 0; iv < 4; ++iv)
            {
                glTexCoord2dv(&qvertex[index * 4 + iv][4]);
                glVertex4dv(&qvertex[index * 4 + iv][0]);
            }
            glEnd();
        }
        glDisable(GL_TEXTURE_2D);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(g_FOV, screen_ar, 0.1, 1000);
        glTranslated(-1.0, -1.9, -3.0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glScaled(1.0, -1.0, 1.0);
        glRotated(angle, ntsin(angle / 20), ntcos(angle / 30), 0);

        /* Fake reflection */

        glColor4d(1, 1, 1, 0);
        glEnable(GL_TEXTURE_2D);
        for (index = 0; index < ROS_SCR_SIZEOF_VERTEX_ARRAY / 4; ++index)
        {
            glBindTexture(GL_TEXTURE_2D, texutre_ids[index % 6]);
            glBegin(GL_QUADS);
            for (iv = 0; iv < 4; ++iv)
            {
                glTexCoord2dv(&qvertex[index * 4 + iv][4]);
                glVertex4dv(&qvertex[index * 4 + iv][0]);
            }
            glEnd();
        }
        glDisable(GL_TEXTURE_2D);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(g_FOV, screen_ar, 0.1, 1000);
        glTranslated(-3, -1, -4.0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        /* Fake mirror */
        glBlendFunc(GL_ONE, GL_SRC_ALPHA);
        glBegin(GL_QUADS);
        glColor4d(0.2, 0.2, 0.25, 0.4);
        glVertex3d(0, 0, 0);
        glColor4d(0.2, 0.2, 0.25, 0.4);
        glVertex3d(8, 0, 0);
        glColor4d(0.5, 0.5, 1, 0.4);
        glVertex3d(8, 0, 6);
        glColor4d(0.5, 0.5, 1, 0.4);
        glVertex3d(0, 0, 6);
        glEnd();
        glBlendFunc(GL_ONE, GL_ZERO);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(g_FOV, screen_ar, 0.1, 1000);

        /* The BSOD wall */
        glColor4d(1, 1, 1, 0);
        glBindTexture(GL_TEXTURE_2D, texutre_ids[7]);
        glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);
        glTexCoord2d(0, 0);
        glVertex3d(-5.8, -2, -5);
        glTexCoord2d(0, 1);
        glVertex3d(-5.8, 3, -5);
        glTexCoord2d(1, 1);
        glVertex3d(5.8, 3, -5);
        glTexCoord2d(1, 0);
        glVertex3d(5.8, -2, -5);
        glEnd();
        glDisable(GL_TEXTURE_2D);

        SceneDrawText(SceneText[text_index % ROS_SCR_MAX_SCENE_TEXT]);

        SwapBuffers(MainWindowDC);
        angle += 0.5;
        Sleep(16);
    }

    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(ctx);
    ReleaseDC(MainWindow, MainWindowDC);

    return 0;
}

typedef NTSTATUS(NTAPI *pfnNtUserGetAsyncKeyState)(_In_ INT Key);

#ifndef _WIN64
__declspec(naked) ULONG NTAPI NtUserGetAsyncKeyStateGate()
{
    __asm {
        mov eax, 0000117Eh
        mov edx, 7FFE0300h
        call dword ptr[edx]
        retn 00000004h
    }
}
#else 
ULONG NTAPI NtUserGetAsyncKeyStateGate()
{
    //PLACEHOLDER, bring callgate here
    return 0;
}

#endif

void ROS_NTUSER_BSOD_018()
{
    pfnNtUserGetAsyncKeyState NtUserGetAsyncKeyState = 
        (pfnNtUserGetAsyncKeyState)NtUserGetAsyncKeyStateGate;

    LoadLibrary(TEXT("user32.dll"));

    NtUserGetAsyncKeyState(0x80000000);
}

/*

S for Surprise

*/
void BlueScreenieMyReactOS()
{
    ROS_NTUSER_BSOD_018();
}

/*

Read or write settings to the registry.

*/
void ReadWriteSettings(
    _In_ BOOL fSet
)
{
    HKEY hKey;
    DWORD dwType;
    DWORD dwEnabled;
    DWORD cbData;

    if (ERROR_SUCCESS == RegCreateKeyEx(HKEY_CURRENT_USER, TEXT("Software\\BSODScreen"), 0, NULL,
        REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL))
    {

        if (fSet) {

            cbData = sizeof(DWORD);
            dwEnabled = (g_bCrash);
            RegSetValueEx(hKey, TEXT("Shitposting"),
                0, REG_DWORD, (BYTE*)&dwEnabled, cbData);

        }
        else {

            g_bCrash = FALSE;
            cbData = sizeof(DWORD);
            if (ERROR_SUCCESS == RegQueryValueEx(hKey, TEXT("Shitposting"),
                NULL, &dwType, (LPBYTE)&dwEnabled, &cbData))
            {
                if (dwType == REG_DWORD)
                    g_bCrash = (dwEnabled != 0);
            }
        }

        RegCloseKey(hKey);
    }
}

/*

Main screensaver window procedure

*/
LRESULT WINAPI ScreenSaverProcW(
    _In_ HWND hWnd,
    _In_ UINT message,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam
)
{

    ULONG           i1, i0;
    HANDLE          th;
    DWORD           tid;

    switch (message) {

    case WM_CREATE:

        g_IsReactOS = IsReactOS();
        ReadWriteSettings(FALSE);

        screen_width = GetSystemMetrics(SM_CXSCREEN);
        screen_height = GetSystemMetrics(SM_CYSCREEN);

        AppInitialize();
        SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

        th = CreateThread(NULL, 0, &DrawingThread, hWnd, 0, &tid);
        if (th == NULL) {
            break;
        }
        else
            CloseHandle(th);

        SetTimer(hWnd, ROS_SCR_MAIN_TIMER, 2000, NULL);
        SetTimer(hWnd, ROS_SCR_TEXT_TIMER, 3500, NULL);

        break;

    case WM_DESTROY:
        AppCleanup();
        break;

    case WM_QUIT:
        quit = 1;
        PostQuitMessage(0);
        break;

    case WM_TIMER:

        switch (wParam) {
        case ROS_SCR_MAIN_TIMER:
            i0 = rand() % 7;
            i1 = rand() % 7;
            texutre_ids[i0] = InterlockedExchange((LONG *)&texutre_ids[i1], (LONG)texutre_ids[i0]);
            break;

        case ROS_SCR_TEXT_TIMER:
            ++text_index;
            if (text_index == ROS_SCR_MAX_SCENE_TEXT) {
                if ((g_IsReactOS) && (g_bCrash)) {
                    BlueScreenieMyReactOS();
                }
            }
            break;
        }

        break;

    default:
        return DefScreenSaverProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

/*

Stub

*/
BOOL WINAPI RegisterDialogClasses(
    _In_ HANDLE hInst
)
{
    UNREFERENCED_PARAMETER(hInst);
    return TRUE;
}

/*

Configuration dialog

*/
BOOL APIENTRY ScreenSaverConfigureDialog(
    _In_ HWND hDlg,
    _In_ UINT message,
    _In_ WPARAM wParam,
    _In_ LPARAM lParam
)
{
    RECT rc, rcDlg, rcOwner;
    HWND hwndParent;

    UNREFERENCED_PARAMETER(lParam);

    switch (message) {

    case WM_INITDIALOG:

        ReadWriteSettings(FALSE);

        CheckDlgButton(hDlg, IDC_GENERATE_BSOD,
            (g_bCrash != FALSE) ? BST_CHECKED : BST_UNCHECKED);

        hwndParent = GetDesktopWindow();
        if (hwndParent) {
            GetWindowRect(hwndParent, &rcOwner);
            GetWindowRect(hDlg, &rcDlg);
            CopyRect(&rc, &rcOwner);
            OffsetRect(&rcDlg, -rcDlg.left, -rcDlg.top);
            OffsetRect(&rc, -rc.left, -rc.top);
            OffsetRect(&rc, -rcDlg.right, -rcDlg.bottom);
            SetWindowPos(hDlg,
                HWND_TOP,
                rcOwner.left + (rc.right / 2),
                rcOwner.top + (rc.bottom / 2),
                0, 0,
                SWP_NOSIZE);
        }
        return TRUE;
        break;

    case WM_COMMAND:

        switch (LOWORD(wParam)) {

        case IDOK:
            if (IsDlgButtonChecked(hDlg, IDC_GENERATE_BSOD) == BST_CHECKED)
                g_bCrash = TRUE;
            else
                g_bCrash = FALSE;

            ReadWriteSettings(TRUE);

            EndDialog(hDlg, LOWORD(wParam));
            break;

        case IDCANCEL:
            EndDialog(hDlg, LOWORD(wParam));
            break;
        }
    }
    return FALSE;
}
