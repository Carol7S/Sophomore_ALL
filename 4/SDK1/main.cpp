#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include <time.h>
#define Pi 3.1415926


LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

HFONT CreateFont(HDC hdc,int nCharHeight,BOOL bItalic)
{
    HFONT hFont;
    hFont=CreateFont(				//����������.
            nCharHeight,				//����߶�.
            0,							//��ϵͳ���ݸ߿��ѡȡ������ѿ��ֵ.
            0,							//�ı���б��Ϊ0,��ʾˮƽ.
            0,							//������б��Ϊ0.
            400,						//����ֶ�.400Ϊ����.
            bItalic,					//��б����?,
            0,							//���»���.
            0,							//��ɾ����.
            ANSI_CHARSET,				//��ʾ���õ��ַ���ΪANSI_CHARSET.
            OUT_DEFAULT_PRECIS,			//ɾ������Ϊȱʡֵ.
            CLIP_DEFAULT_PRECIS,		//�ü�����Ϊȱʡֵ.
            DEFAULT_QUALITY,			//�������Ϊȱʡֵ.
            DEFAULT_PITCH|FF_DONTCARE,	//�ּ�������ϵ��ʹ��ȱʡֵ.
            "Arial");					//��������.
    if(hFont == NULL) return NULL;
    else return hFont;
}

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInst,LPSTR lpszCmdLine,int nCmdShow)
{
    HWND hwnd;
    MSG Msg;
    WNDCLASS wndclass ;
    char lpszClassName[] = "����";
    char lpszTitle[]= "My_Windows";

    wndclass.style = 0;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
    wndclass.hbrBackground =(HBRUSH) GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = lpszClassName;

    if(!RegisterClass(&wndclass))
    {
        MessageBeep(0) ;
        return FALSE ;
    }
    hwnd=CreateWindow(
            lpszClassName,
            lpszTitle,
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            NULL,
            NULL,
            hInstance,
            NULL);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while(GetMessage(&Msg,NULL,0,0))
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT message,WPARAM  wParam,LPARAM lParam)
{
    HDC hDC;				//�����豸�������.
    HBRUSH hBr;
    HPEN hPen;
    PAINTSTRUCT ps;			//���������ͼ��Ϣ�Ľṹ�����
    char cUP[]="��������UP��";
    char cCTRL[]="��������CTRL��";
    static int i=0;
    static int flag=0;
    static bool nCtrlRKeyDown = FALSE;
    static bool nCtrlKeyDown = FALSE;
    static bool nShiftBKeyDown = FALSE;
    static bool nShiftKeyDown = FALSE;
    RECT rect;
    GetClientRect(hWnd , &rect) ;

    switch(message)
    {
        case WM_KEYUP:
            InvalidateRect(hWnd,NULL,1);	//ˢ���û�����
            break;

        case WM_CHAR:
            if(wParam=='r')
            {
                flag = 1;
            }
            else if(wParam=='g')	//������b��ʱ
            {
                flag = 2;
            }
            else if(wParam=='b')	//������c��ʱ
            {
                flag = 3;
            }
            else if((GetAsyncKeyState(VK_CONTROL&0x8000)) && (GetAsyncKeyState('R'))){
                if(nCtrlKeyDown == TRUE){
                    nCtrlRKeyDown = TRUE;
                    nCtrlKeyDown = FALSE;
                }
            }
            else if((GetAsyncKeyState(VK_SHIFT&0x8000)) && (GetAsyncKeyState('B'))){
                if(nShiftKeyDown == TRUE){
                    nShiftBKeyDown = TRUE;
                    nShiftKeyDown = FALSE;
                }
            }
            break;

        case WM_KEYDOWN:
            if(wParam == VK_UP){
                flag = 4;
            }else if(wParam == VK_CONTROL){
                nCtrlKeyDown = TRUE;
                flag = 5;
            }else if(wParam == VK_SHIFT){
                nShiftKeyDown = TRUE;
                flag = 6;
            }
            break;

        case WM_PAINT:							//�����ͼ��Ϣ.
            hDC=BeginPaint(hWnd,&ps);
            SetTextColor(hDC,RGB(255,0,0));		//����������ɫΪ��ɫ��

            //�����Ϣ��
            if(flag == 1)
            {
                hPen = CreatePen(PS_SOLID, 1, RGB(0,0,0));
                SelectObject(hDC, hPen);
                hBr = CreateSolidBrush(RGB(255,0,0));
                SelectObject(hDC, hBr);
                Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);
                DeleteObject(hPen);
                DeleteObject(hBr);
            }
            else if(flag == 2)
            {
                hPen = CreatePen(PS_SOLID, 1, RGB(0,0,0));
                SelectObject(hDC, hPen);
                hBr = CreateSolidBrush(RGB(0,255,0));
                SelectObject(hDC, hBr);
                Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);
                DeleteObject(hPen);
                DeleteObject(hBr);
            }
            else if(flag == 3)
            {
                hPen = CreatePen(PS_SOLID, 1, RGB(0,0,0));
                SelectObject(hDC, hPen);
                hBr = CreateSolidBrush(RGB(0,0,255));
                SelectObject(hDC, hBr);
                Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);
                DeleteObject(hPen);
                DeleteObject(hBr);
            }
            else if(flag == 4){
                TextOut(hDC, (rect.left+rect.right)/2, (rect.top+rect.bottom)/2, cUP, strlen(cUP));
            }
            else if(flag == 5){
                if(!nCtrlRKeyDown)
                    TextOut(hDC, (rect.left+rect.right)/2, (rect.top+rect.bottom)/2, cCTRL, strlen(cCTRL));
                else{
                    hPen = CreatePen(PS_SOLID, 1, RGB(0,0,0));
                    SelectObject(hDC, hPen);
                    hBr = CreateSolidBrush(RGB(255,104,24));
                    SelectObject(hDC, hBr);
                    Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);
                    DeleteObject(hPen);
                    DeleteObject(hBr);
                }
            }
            else if(flag == 6){
                if(nShiftBKeyDown)
                    hPen = CreatePen(PS_SOLID, 1, RGB(0,0,0));
                    SelectObject(hDC, hPen);
                    hBr = CreateSolidBrush(RGB(236,24,255));
                    SelectObject(hDC, hBr);
                    Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);
                    DeleteObject(hPen);
                    DeleteObject(hBr);
            }
            EndPaint(hWnd,&ps);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProc(hWnd,message,wParam,lParam);
    }
    return 0;
}
