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

    while (GetMessage (&msg, NULL, 0, 0))//GetMessage函数用队列中的下一个消息填入msg结构的字段
    {
        TranslateMessage (&msg) ;//将按键消息转换为字符消息
        DispatchMessage (&msg) ;//DispatchMessage以此消息为参数呼叫适当的窗口消息处理程序
    }
    return msg.wParam ;
}

LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    RECT rect;
    HDC hdc;
    HFONT hF_black,hF_big;	//定义两种字体句柄
    PAINTSTRUCT ps;
    TEXTMETRIC tm;	//定义一个TEXTMETRIC结构，用以记录字体信息
    char lpsz_1[]="这是一行红色的、字体为SYSTEM_FONT的文字，红色代表未来。";
    char lpsz_2[]="现在显示的是自定义字体，颜色为绿色，绿色代表生机勃勃。";
    char lpsz_3[]="现在展现在您面前的是蓝色的粗体字，蓝色代表广阔的海洋和天空。";
    char lpsz_4[]="当前字体为大号、斜体并带有下划线的文字。";
    char lpsz_5[]="现在您掌握了字体的操作了吗?";
    char lpsz_6[]="祝您成功!";
    GetClientRect(hwnd, &rect);
    int X=0,Y=0;
    SIZE size;		//定义一个SIZE类型的结构

    char a[255];

    switch (message)
    {
        case WM_PAINT:
            hdc=BeginPaint(hwnd,&ps);
            SetTextColor(hdc,RGB(255,0,0));	//设置文本颜色为红色
            GetTextMetrics(hdc,&tm);  //获取缺省字体，写入tm结构中

            //sprintf(a,"%d",tm.tmExternalLeading);
            //MessageBox(hwnd, a, "111", strlen(a));
            GetTextExtentPoint32(hdc, lpsz_1, strlen(lpsz_1), &size);
            X = rect.right - size.cx;
//            X = rect.right;
            //用缺省字体输出第一行文本
            TextOut(hdc,X,Y,lpsz_1,strlen(lpsz_1));
            //换行继续输出文本，计算新行的起始Y坐标位置
            Y=Y+tm.tmHeight+100*tm.tmExternalLeading;

            ///////////////////////////////////////////////////////////////////////////////

            hF_black=CreateFont(		 	//创建自定义字体
                    20,			//字体的高度
                    0,		//由系统根据高宽比选取字体最佳宽度值
                    0,			//文本的倾斜度为0，表示水平
                    0,			//字体的倾斜度为0
                    FW_HEAVY,		//字体的粗度，FW_HEAVY为最粗
                    0,			//非斜体字
                    0,			//无下划线
                    0,			//无删除线
                    ANSI_CHARSET,	//表示所用的字符集为ANSI_CHARSET
                    OUT_DEFAULT_PRECIS,		//输出精度为缺省精度
                    CLIP_DEFAULT_PRECIS,		//剪裁精度为缺省精度
                    DEFAULT_QUALITY,		//输出质量为缺省值
                    DEFAULT_PITCH|FF_DONTCARE,//字间距和字体系列使用缺省值
                    "粗体字" ); 		//字体名称
            SetTextColor(hdc,RGB(0,255,0));	//设置文本颜色为绿色
            SelectObject(hdc,hF_black);	//将自定义字体选入设备环境
            GetTextMetrics(hdc,&tm); //获取字体的信息，写入tm结构中
            GetTextExtentPoint32(hdc, lpsz_2, strlen(lpsz_2), &size);
            X = rect.right - size.cx;
            //sprintf(a,"%d",tm.tmExternalLeading);
            //MessageBox(hwnd, a, "111", strlen(a));

            //用hF_black字体输出第二行文本
            TextOut(hdc,X,Y,lpsz_2,strlen(lpsz_2));
            Y=Y+tm.tmHeight+10*tm.tmExternalLeading;

            ///////////////////////////////////////////////////////////////////////////////

            SetTextColor(hdc,RGB(0,0,255));	//设置文本颜色为蓝色
            //当前字体输出第三行文本
            GetTextExtentPoint32(hdc, lpsz_3, strlen(lpsz_3), &size);
            X = rect.right - size.cx;
            TextOut(hdc,X,Y,lpsz_3,strlen(lpsz_3));
            Y=Y+tm.tmHeight+100*tm.tmExternalLeading;

            ///////////////////////////////////////////////////////////////////////////////

            hF_big=CreateFont		//引入新字体
                    (
                            30,			//字体高度              参数综合，导致tmExternalLeading为1
                            0,
                            0,
                            0,
                            FW_NORMAL,     //粗度
                            1,			    //定义斜体
                            1,		     	//定义输出时带下划线
                            0,
                            ANSI_CHARSET,
                            OUT_DEFAULT_PRECIS,
                            CLIP_DEFAULT_PRECIS,
                            DEFAULT_QUALITY,
                            DEFAULT_PITCH|FF_DONTCARE,
                            "大号字"
                    );

            SelectObject(hdc,hF_big);//将自定义字体选入设备环境
            SetTextColor(hdc,RGB(155,155,155));	//设置文本颜色
            //tm还是老的
            GetTextExtentPoint32(hdc, lpsz_4, strlen(lpsz_4), &size);
            X = rect.right - size.cx;
            Y=Y+tm.tmHeight+200*tm.tmExternalLeading;
            //输出第四行文本
            TextOut(hdc,X,Y,lpsz_4,strlen(lpsz_4));

            ///////////////////////////////////////////////////////////////////////////////

            GetTextMetrics(hdc,&tm);
            //sprintf(a,"%d",tm.tmExternalLeading);
            //MessageBox(hwnd, a, "111", strlen(a));

            SetTextColor(hdc,RGB(255,0,0));//设置文本颜色为红色
            GetTextExtentPoint32(hdc, lpsz_5, strlen(lpsz_5), &size);
            X = rect.right - size.cx;
//            X=0;				//设定输出文本的X坐标位置
            Y=Y+tm.tmHeight+30*tm.tmExternalLeading;
            //输出第五行文本
            TextOut(hdc,X,Y,lpsz_5,strlen(lpsz_5));

            ///////////////////////////////////////////////////////////////////////////////

            GetTextExtentPoint32(hdc,lpsz_5,strlen(lpsz_5),&size);//计算lpsz_5宽度
            //获取字符串的宽度
            X=X+size.cx;			//获取起始坐标
            //输出第六行文本
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

