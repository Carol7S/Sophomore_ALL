// Think.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "Think.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
HBITMAP hBm1, hBm2, hBm3, hBm4, hBm5, hBm6, hBm7, hBm8, hBm9;
BITMAP bm, bm2;
HDC hdc, hdcmem, hdcmem2;
// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_THINK, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_THINK));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_THINK));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_THINK);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }
   hBm1 = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP1));
  
   
   hBm2 = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP2));
   
   hBm3 = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP3));

   hBm4 = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP4));

   hBm5 = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP5));

   hBm6 = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP6));

   hBm7 = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP7));

   hBm8 = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP8));

   hBm9 = LoadBitmap(hInstance, MAKEINTRESOURCE(IDB_BITMAP9));
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    RECT rect;
    GetClientRect(hWnd, &rect);
    static int flag=0, flag_Dire=0;//flag_Dire初始为0， 北为1，东为2， 南为3， 西为4 
    static double x1, y1;
    switch (message)
    {
    case WM_CREATE:
        hdc = GetDC(hWnd);
        hdcmem = CreateCompatibleDC(hdc);
        hdcmem2 = CreateCompatibleDC(hdc);
        ReleaseDC(hWnd, hdc);
        x1 = (rect.left + rect.right) / 2.4;
        y1 = (rect.top + rect.bottom) / 3;
        break;
    case WM_KEYUP:
        InvalidateRect(hWnd, NULL, 1);	//刷新用户区。
        break;
    case WM_CHAR:
        if (wParam == 'w') {
            flag = 1;
        }
        else if (wParam == 's') {
            flag = 2;
        }
        else if (wParam == 'a') {
            flag = 3;
        }
        else if (wParam == 'd') {
            flag = 4;
        }
        break;

    case WM_KEYDOWN:
        if (wParam == VK_UP) {
            flag = 1;
        }
        else if (wParam == VK_DOWN) {
            flag = 2;
        }
        else if (wParam == VK_LEFT) {
            flag = 3;
        }
        else if (wParam == VK_RIGHT) {
            flag = 4;
        }
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        hdc = BeginPaint(hWnd, &ps);
        SelectObject(hdcmem2, hBm9);
        GetObject(hBm9, sizeof(BITMAP), &bm2);
        BitBlt(hdc, 0, 0, rect.right, rect.bottom, hdcmem2, 0, 0, SRCCOPY);
        // TODO: 在此处添加使用 hdc 的任何绘图代码...
        if (flag == 1)//向上
        {
            y1 -= 20;

            if (rect.top >= y1) {
                y1 += 50;

            }
            SelectObject(hdcmem, hBm3);
            GetObject(hBm3, sizeof(BITMAP), &bm);
            BitBlt(hdc, x1, y1, bm.bmWidth, bm.bmHeight, hdcmem, 0, 0, SRCCOPY);

            flag = 0;
            flag_Dire = 1;
            Sleep(500);
            InvalidateRect(hWnd, NULL, 1);	//刷新用户区。
        }
        else if (flag == 2)//向下
        {
            y1 += 20;

            if (rect.bottom <= y1 + bm.bmHeight) {
                y1 -= 50;

            }
            SelectObject(hdcmem, hBm2);
            GetObject(hBm2, sizeof(BITMAP), &bm);
            BitBlt(hdc, x1, y1, bm.bmWidth, bm.bmHeight, hdcmem, 0, 0, SRCCOPY);

            flag = 0;
            flag_Dire = 3;
            Sleep(500);
            InvalidateRect(hWnd, NULL, 1);	//刷新用户区。
        }
        else if (flag == 3)//向左
        {
            x1 -= 20;

            if (rect.left >= x1) {
                x1 += 50;

            }
            SelectObject(hdcmem, hBm5);
            GetObject(hBm5, sizeof(BITMAP), &bm);
            BitBlt(hdc, x1, y1, bm.bmWidth, bm.bmHeight, hdcmem, 0, 0, SRCCOPY);

            flag = 0;
            flag_Dire = 4;
            Sleep(500);
            InvalidateRect(hWnd, NULL, 1);	//刷新用户区。
        }
        else if (flag == 4)//向右
        {
            x1 += 20;

            if (rect.right <= x1 + bm.bmWidth) {
                x1 -= 50;

            }
            SelectObject(hdcmem, hBm7);
            GetObject(hBm7, sizeof(BITMAP), &bm);
            BitBlt(hdc, x1, y1, bm.bmWidth, bm.bmHeight, hdcmem, 0, 0, SRCCOPY);

            flag = 0;
            flag_Dire = 2;
            Sleep(500);
            InvalidateRect(hWnd, NULL, 1);	//刷新用户区。
        }
        else if (flag == 0 && (flag_Dire == 0||flag_Dire == 3)) {
            SelectObject(hdcmem, hBm1);
            GetObject(hBm1, sizeof(BITMAP), &bm);
            BitBlt(hdc, x1, y1, bm.bmWidth, bm.bmHeight, hdcmem, 0, 0, SRCCOPY);
        }
        else if (flag == 0 && flag_Dire == 1) {
            SelectObject(hdcmem, hBm4);
            GetObject(hBm4, sizeof(BITMAP), &bm);
            BitBlt(hdc, x1, y1, bm.bmWidth, bm.bmHeight, hdcmem, 0, 0, SRCCOPY);
        }
        else if (flag == 0 && flag_Dire == 4) {
            SelectObject(hdcmem, hBm6);
            GetObject(hBm6, sizeof(BITMAP), &bm);
            BitBlt(hdc, x1, y1, bm.bmWidth, bm.bmHeight, hdcmem, 0, 0, SRCCOPY);
        }
        else if (flag == 0 && flag_Dire == 2) {
            SelectObject(hdcmem, hBm8);
            GetObject(hBm8, sizeof(BITMAP), &bm);
            BitBlt(hdc, x1, y1, bm.bmWidth, bm.bmHeight, hdcmem, 0, 0, SRCCOPY);
        }
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        DeleteObject(hBm1);
        DeleteObject(hBm2);
        DeleteObject(hBm3);
        DeleteObject(hBm4);
        DeleteObject(hBm5);
        DeleteObject(hBm6);
        DeleteObject(hBm7);
        DeleteObject(hBm8);
        DeleteObject(hBm9);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
