#include <windows.h>
#include <cmath>
#define Pi 3.1415926

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);   //窗口函数
//--------------------------以下是入口代码-------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
    WNDCLASSEX wcex;
    HWND hWnd;
    MSG msg;
    char szWindowClass[] = "窗口实例";   //窗口类名
    char szTitle[] = "My Windows";   //窗口标题名

//------------------------以下初始化窗口类---------------------------------
    wcex.cbSize = sizeof(WNDCLASSEX); //窗口类的大小
    wcex.style = CS_HREDRAW | CS_VREDRAW;   //窗口类型
    wcex.lpfnWndProc = WndProc;     //窗口处理函数
    wcex.cbClsExtra = 0;            //窗口类无扩展
    wcex.cbWndExtra = 0;            //窗口实例无扩展
    wcex.hInstance = hInstance;     //当前实例句柄
    wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION); //窗口的图标为默认图标
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);                //窗口采用箭头光标
    wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //窗口背景为白色
    wcex.lpszMenuName = NULL;   //窗口中无菜单
    wcex.lpszClassName = szWindowClass; //窗口的类名为"窗口实例"
    wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION); //窗口的小图标为默认图标

//---------------------以下进行窗口类的注册-------------------------------------
    if(!RegisterClassEx(&wcex)){    //注册失败则发出警告
        MessageBox(NULL, "窗口类注册失败!", "窗口注册", NULL);
        return 1;
    }
//---------------------以下创建窗口--------------------------------------------
    hWnd = CreateWindow(
            szWindowClass,      //窗口类名
            szTitle,            //窗口实例的标题名
            WS_OVERLAPPEDWINDOW,    //窗口的风格
            CW_USEDEFAULT,CW_USEDEFAULT,      //窗口左上角坐标为默认值
            CW_USEDEFAULT, CW_USEDEFAULT,   //窗口的高和宽为默认值
            NULL,                    //此窗口无父窗口
            NULL,                   //此窗口无主菜单
            hInstance,          //创建此窗口应用程序的当前句柄
            NULL                        //不使用该值
    );

    if(!hWnd){      //如果创建窗口失败则发出警告
        MessageBox(NULL, "创建窗口失败!", "创建窗口", NULL);
        return 1;
    }
    ShowWindow(hWnd, nCmdShow);     //显示窗口
    UpdateWindow(hWnd);             //绘制用户区
    while(GetMessage(&msg, NULL, 0, 0)){ //消息循环
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return(int) msg.wParam;     //程序终止时将信息返回系统
}
//-------------------以下是窗口函数的代码--------------------------------------
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam){
    PAINTSTRUCT ps;
    HDC hDC;				//定义设备环境句柄.
    HBRUSH hBrush;			//定义画刷句柄
    HPEN hP;				//定义画笔句柄
    PAINTSTRUCT PtStr;		//定义包含绘图信息的结构体变量
    static double dfRange=100.0;
    static long i=0, j=0;
    static long lCentreX=0,lCentreY=0,lRadious=(long)(0.2*dfRange);//定义圆心坐标和圆坐标.
    static POINT lpSin[100];	//定义正弦曲线的点坐标.
    static bool flag=1;

    for(int j=0;j<100;j++)		//生成正弦曲线的点坐标.
    {
        lpSin[j].x=(long)(j*2*Pi/100*60);
        lpSin[j].y=(long)(dfRange*sin(j*2*Pi/100));
    }

    switch(message)
    {
        case WM_PAINT:							//处理绘图消息.
            hDC=BeginPaint(hWnd,&PtStr);		//获得设备环境指针.
            SetWindowOrgEx(hDC,-200,-200,NULL);	//设置原点坐标为(-200,-200).

            hP=CreatePen(PS_SOLID,1,RGB(255,0,0));	//创新画笔.
            SelectObject(hDC,hP);					//选入画笔.
            Polyline(hDC,lpSin,100);				//绘制正弦曲线.
            DeleteObject(hP);		//删除画笔.

            if(i<=25) //第一个1/4周期.
            {
                hP=CreatePen(PS_DASH,1,RGB(255,0,0));//创新红笔.
                hBrush=CreateHatchBrush(HS_BDIAGONAL,RGB(255,0,0));//创新红画刷.
                lRadious=(long)(dfRange*0.2+i%25*dfRange*0.4/25);//计算半径.
            }
            else if(i<=50)//第二个1/4周期.
            {
                hP=CreatePen(PS_DASH,1,RGB(0,255,0));//创新绿笔.
                hBrush=CreateHatchBrush(HS_DIAGCROSS,RGB(0,255,0));//创新绿刷.
                lRadious=(long)(dfRange*0.2+i%25*dfRange*0.4/25);//计算半径.
            }
            else if(i<=75)//第三个周期.
            {
                hP=CreatePen(PS_DASH,1,RGB(0,0,255));//创新蓝笔
                hBrush=CreateHatchBrush(HS_CROSS,RGB(0,0,255));//创新蓝刷.
                lRadious=(long)(dfRange*0.2+i%25*dfRange*0.4/25);//计算半径.
            }
            else//第四个周期.
            {
                hP=CreatePen(PS_DASH,1,RGB(255,255,0));//创新黄笔
                hBrush=CreateHatchBrush(HS_VERTICAL,RGB(255,255,0));//创新黄刷.
                lRadious=(long)(dfRange*0.2+i%25*dfRange*0.4/25);//计算半径.
            }
            SelectObject(hDC,hBrush);	//选入画刷.
            SelectObject(hDC,hP);		//选入画笔.
            lCentreX=lpSin[i].x;		//圆心x坐标.
            lCentreY=lpSin[i].y;		//圆心y坐标.
            Ellipse(hDC,lCentreX-lRadious,lCentreY-lRadious,
                    lCentreX+lRadious,lCentreY+lRadious);	//画圆.
            if(i<99){
                if(flag==1)
                    i++;
                else
                    i--;
            }
            else if(i==99){
                flag=0;
                i--;
            }
            DeleteObject(hP);
            EndPaint(hWnd, &ps);
            Sleep(100);
            if (0<i && i<100)
                InvalidateRect(hWnd, NULL, 1);

            return 0;
        default:                    //默认时采用系统消息默认处理函数
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
}