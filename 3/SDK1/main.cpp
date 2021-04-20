/*------------------------------------------------------------
   HELLOWIN.C -- Displays "Hello, Windows 98!" in client area
                 (c) Charles Petzold, 1998
  ------------------------------------------------------------*/

#include <windows.h>


LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM) ;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdLine, int iCmdShow)
{
    static TCHAR szAppName[] = TEXT ("HelloWin") ;
    HWND         hwnd ;
    MSG          msg ;
    WNDCLASS     wndclass ;

    wndclass.style         = CS_HREDRAW | CS_VREDRAW ;
    wndclass.lpfnWndProc   = WndProc ;
    wndclass.cbClsExtra    = 0 ;
    wndclass.cbWndExtra    = 0 ;
    wndclass.hInstance     = hInstance ;
    wndclass.hIcon         = LoadIcon (NULL, IDI_APPLICATION) ;
    wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW) ;
    wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH) ;
    wndclass.lpszMenuName  = NULL ;
    wndclass.lpszClassName = szAppName ;

    if (!RegisterClass (&wndclass))
    {
        MessageBox (NULL, TEXT ("This program requires Windows NT!"),
                    szAppName, MB_ICONERROR) ;
        return 0 ;
    }
    hwnd = CreateWindow (szAppName,                  // window class name
                         TEXT ("The Windows Program"), // window caption
                         WS_OVERLAPPEDWINDOW,        // window style
                         CW_USEDEFAULT,              // initial x position
                         CW_USEDEFAULT,              // initial y position
                         800,              // initial x size
                         600,              // initial y size
                         NULL,                       // parent window handle
                         NULL,                       // window menu handle
                         hInstance,                  // program instance handle
                         NULL) ;                     // creation parameters

    ShowWindow (hwnd, iCmdShow) ;
    UpdateWindow (hwnd) ;

    while (GetMessage (&msg, NULL, 0, 0))//GetMessage�����ö����е���һ����Ϣ����msg�ṹ���ֶ�
    {
        TranslateMessage (&msg) ;//��������Ϣת��Ϊ�ַ���Ϣ
        DispatchMessage (&msg) ;//DispatchMessage�Դ���ϢΪ���������ʵ��Ĵ�����Ϣ�������
    }
    return msg.wParam ;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    RECT rect;
    HDC hdc;
    HFONT hF_black,hF_big;	//��������������
    PAINTSTRUCT ps;
    TEXTMETRIC tm;	//����һ��TEXTMETRIC�ṹ�����Լ�¼������Ϣ
    char lpsz_1[]="����һ�к�ɫ�ġ�����ΪSYSTEM_FONT�����֣���ɫ����δ����";
    char lpsz_2[]="������ʾ�����Զ������壬��ɫΪ��ɫ����ɫ��������������";
    char lpsz_3[]="����չ��������ǰ������ɫ�Ĵ����֣���ɫ��������ĺ������ա�";
    char lpsz_4[]="��ǰ����Ϊ��š�б�岢�����»��ߵ����֡�";
    char lpsz_5[]="����������������Ĳ�������?";
    char lpsz_6[]="ף���ɹ�!";
    GetClientRect(hwnd, &rect);
    int X=0,Y=0;
    SIZE size;		//����һ��SIZE���͵Ľṹ

    char a[255];

    switch (message)
    {
        case WM_PAINT:
            hdc=BeginPaint(hwnd,&ps);
            SetTextColor(hdc,RGB(255,0,0));	//�����ı���ɫΪ��ɫ
            GetTextMetrics(hdc,&tm);  //��ȡȱʡ���壬д��tm�ṹ��

            //sprintf(a,"%d",tm.tmExternalLeading);
            //MessageBox(hwnd, a, "111", strlen(a));
            GetTextExtentPoint32(hdc, lpsz_1, strlen(lpsz_1), &size);
            X = rect.right - size.cx;
//            X = rect.right;
            //��ȱʡ���������һ���ı�
            TextOut(hdc,X,Y,lpsz_1,strlen(lpsz_1));
            //���м�������ı����������е���ʼY����λ��
            Y=Y+tm.tmHeight+100*tm.tmExternalLeading;

            ///////////////////////////////////////////////////////////////////////////////

            hF_black=CreateFont(		 	//�����Զ�������
                    20,			//����ĸ߶�
                    0,		//��ϵͳ���ݸ߿��ѡȡ������ѿ��ֵ
                    0,			//�ı�����б��Ϊ0����ʾˮƽ
                    0,			//�������б��Ϊ0
                    FW_HEAVY,		//����Ĵֶȣ�FW_HEAVYΪ���
                    0,			//��б����
                    0,			//���»���
                    0,			//��ɾ����
                    ANSI_CHARSET,	//��ʾ���õ��ַ���ΪANSI_CHARSET
                    OUT_DEFAULT_PRECIS,		//�������Ϊȱʡ����
                    CLIP_DEFAULT_PRECIS,		//���þ���Ϊȱʡ����
                    DEFAULT_QUALITY,		//�������Ϊȱʡֵ
                    DEFAULT_PITCH|FF_DONTCARE,//�ּ�������ϵ��ʹ��ȱʡֵ
                    "������" ); 		//��������
            SetTextColor(hdc,RGB(0,255,0));	//�����ı���ɫΪ��ɫ
            SelectObject(hdc,hF_black);	//���Զ�������ѡ���豸����
            GetTextMetrics(hdc,&tm); //��ȡ�������Ϣ��д��tm�ṹ��
            GetTextExtentPoint32(hdc, lpsz_2, strlen(lpsz_2), &size);
            X = rect.right - size.cx;
            //sprintf(a,"%d",tm.tmExternalLeading);
            //MessageBox(hwnd, a, "111", strlen(a));

            //��hF_black��������ڶ����ı�
            TextOut(hdc,X,Y,lpsz_2,strlen(lpsz_2));
            Y=Y+tm.tmHeight+10*tm.tmExternalLeading;

            ///////////////////////////////////////////////////////////////////////////////

            SetTextColor(hdc,RGB(0,0,255));	//�����ı���ɫΪ��ɫ
            //��ǰ��������������ı�
            GetTextExtentPoint32(hdc, lpsz_3, strlen(lpsz_3), &size);
            X = rect.right - size.cx;
            TextOut(hdc,X,Y,lpsz_3,strlen(lpsz_3));
            Y=Y+tm.tmHeight+100*tm.tmExternalLeading;

            ///////////////////////////////////////////////////////////////////////////////

            hF_big=CreateFont		//����������
                    (
                            30,			//����߶�              �����ۺϣ�����tmExternalLeadingΪ1
                            0,
                            0,
                            0,
                            FW_NORMAL,     //�ֶ�
                            1,			    //����б��
                            1,		     	//�������ʱ���»���
                            0,
                            ANSI_CHARSET,
                            OUT_DEFAULT_PRECIS,
                            CLIP_DEFAULT_PRECIS,
                            DEFAULT_QUALITY,
                            DEFAULT_PITCH|FF_DONTCARE,
                            "�����"
                    );

            SelectObject(hdc,hF_big);//���Զ�������ѡ���豸����
            SetTextColor(hdc,RGB(155,155,155));	//�����ı���ɫ
            //tm�����ϵ�
            GetTextExtentPoint32(hdc, lpsz_4, strlen(lpsz_4), &size);
            X = rect.right - size.cx;
            Y=Y+tm.tmHeight+200*tm.tmExternalLeading;
            //����������ı�
            TextOut(hdc,X,Y,lpsz_4,strlen(lpsz_4));

            ///////////////////////////////////////////////////////////////////////////////

            GetTextMetrics(hdc,&tm);
            //sprintf(a,"%d",tm.tmExternalLeading);
            //MessageBox(hwnd, a, "111", strlen(a));

            SetTextColor(hdc,RGB(255,0,0));//�����ı���ɫΪ��ɫ
            GetTextExtentPoint32(hdc, lpsz_5, strlen(lpsz_5), &size);
            X = rect.right - size.cx;
//            X=0;				//�趨����ı���X����λ��
            Y=Y+tm.tmHeight+30*tm.tmExternalLeading;
            //����������ı�
            TextOut(hdc,X,Y,lpsz_5,strlen(lpsz_5));

            ///////////////////////////////////////////////////////////////////////////////

            GetTextExtentPoint32(hdc,lpsz_5,strlen(lpsz_5),&size);//����lpsz_5���
            //��ȡ�ַ����Ŀ��
            X=X+size.cx;			//��ȡ��ʼ����
            //����������ı�
            TextOut(hdc,X,Y,lpsz_6,strlen(lpsz_6));

            DeleteObject(hF_black);
            DeleteObject(hF_big);
            EndPaint(hwnd,&ps);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }

    return DefWindowProc (hwnd, message, wParam, lParam) ;
}

