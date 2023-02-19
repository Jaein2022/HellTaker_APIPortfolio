#include "J_Window.h"
#include "J_ImageManager.h"
#include "J_Input.h"
#include <J_GameEngineTime.h>
#include <J_SoundManager.h>

J_Window* J_Window::instance_ = new J_Window();
bool isWindowOn = true;
LRESULT CALLBACK WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);

J_Window::J_Window()
    : hInstance_(NULL),
    hWnd_(NULL),
    windowClassName_(""), 
    windowTitle_(""), 
    windowSize_(float4::ZERO), 
    windowPos_(float4::ZERO)
{
}

J_Window::~J_Window()
{
    if (nullptr != hWnd_)
    {
        DestroyWindow(hWnd_);
        hWnd_ = nullptr;
    }
}

void J_Window::CreateMainWindowClass(HINSTANCE _hInstance, const std::string& _windowClassName)
{
    if (NULL == _hInstance)
    {
        J_GameEngineDebug::AssertFalse();
        return;
    }

    if (true == _windowClassName.empty())
    {
        J_GameEngineDebug::AssertFalse();
        return;
    }

    hInstance_ = _hInstance;
    windowClassName_ = _windowClassName;

    //WNDCLASSEXW: 아래의 구조체타입 변수 선언용 typedef.
    //typedef struct tagWNDCLASSEXW {
    //    UINT        cbSize;
    //    /* Win 3.x */
    //    UINT        style;            윈도우의 형태.
    //    WNDPROC     lpfnWndProc;      윈도우 관련 메시지를 처리할 함수 이름.    
    //    int         cbClsExtra;       여유 공간. 거의 쓰지 않음.
    //    int         cbWndExtra;       여유 공간. 거의 쓰지 않음.
    //    HINSTANCE   hInstance;        윈도우 클래스를 사용하는 프로그램(인스턴스)의 핸들.  
    //    HICON       hIcon;            윈도우 아이콘
    //    HCURSOR     hCursor;          윈도우에서 쓸 커서 형태.
    //    HBRUSH      hbrBackground;    윈도우 배경을 칠할 특정 색의 브러시 오브젝트 지정. +1: 백색, +2:회색
    //    LPCWSTR     lpszMenuName;     프로그램이 쓸 메뉴 지정. 사용하지 않을거라면 NULL
    //    LPCWSTR     lpszClassName;    윈도우 클래스의 이름. MyRegisterClass()를 통해 OS에 등록된 클래스이름과 다르면 실행되지 않는다.
    //    /* Win 4.0 */
    //    HICON       hIconSm;          윈도우가 최소화되면 사용할 아이콘.
    //} WNDCLASSEXW, * PWNDCLASSEXW, NEAR* NPWNDCLASSEXW, FAR* LPWNDCLASSEXW;

    WNDCLASSEXA wcex{};
    wcex.cbSize = sizeof(WNDCLASSEXA);
    wcex.style = CS_HREDRAW | CS_VREDRAW;   //가로 | 세로 화면크기 갱신 옵션
    wcex.lpfnWndProc = WndProc;             //DispatchMessage()가 받은 MSG변수를 보낼 목적지가 되는 함수. 
    wcex.cbClsExtra = 0;                    //??
    wcex.cbWndExtra = 0;                    //??
    wcex.hInstance = hInstance_;            //윈도우 인스턴스의 핸들.

    wcex.hIcon = nullptr;                   //이 윈도우가 사용할 기본 아이콘 핸들.
    wcex.hCursor = nullptr;                 //이 윈도우가 사용할 커서 핸들.
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);    //윈도우 기본 배경 색.

    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = windowClassName_.c_str();  //윈도우 클래스 이름.
    wcex.hIconSm = nullptr;                 //이 윈도우가 최소화되었을 때 사용할 아이콘 핸들.

    RegisterClassExA(&wcex);    //위에서 설정한 옵션의 윈도우를 그리겠다고 OS에게 등록하는 함수. 실패하면 0을 반환.
}

void J_Window::CreateMainWindow(const std::string& _windowTitle, const float4& _windowPos, const float4& _windowSize)
{
    if (NULL == hInstance_)
    {
        J_GameEngineDebug::AssertFalse();
        return;
    }

    if (true == _windowTitle.empty())
    {
        J_GameEngineDebug::AssertFalse();
        return;
    }

    windowTitle_ = _windowTitle;

    hWnd_ = CreateWindowA(
        windowClassName_.c_str(),       //윈도우 클래스 이름.
        windowTitle_.c_str(),           //윈도우 제목.
        WS_OVERLAPPEDWINDOW,            //윈도우 형태: 기본 윈도우.
        _windowPos.IntX(),              //윈도우 위치의 x좌표. CW_USEDEFAULT: 적당히.
        _windowPos.IntY(),              //윈도우 위치의 y좌표.
        _windowSize.IntX(),             //윈도우 가로길이:
        _windowSize.IntY(),             //윈도우 세로길이.
        nullptr,                        //부모 윈도우가 있다면 여기 넣는다.
        nullptr,                        //메뉴 핸들이 따로 있다면 여기 넣는다.
        hInstance_,                     //윈도우를 만든 주체인 인스턴스의 핸들을 넣는다.
        nullptr                         //???
    );


    if (NULL == hWnd_)
    {
        J_GameEngineDebug::AssertFalse();
        return;
    }

    ShowWindow(hWnd_, SW_SHOW);
    UpdateWindow(hWnd_);
    SetWindowPosAndSize(_windowPos, _windowSize);

    HDC windowHDC = ::GetDC(hWnd_);
    if (nullptr == windowHDC)
    {
        J_GameEngineDebug::AssertFalse();
        return;
    }

    J_ImageManager::GetInstance().InitializeWindow(windowHDC);
    //프로그램이 종료되면 자동으로 윈도우즈가 모든 핸들들을 해제하므로 ReleaseDC()걱정은 하지 않아도 된다.
}

void J_Window::SetWindowPosAndSize(const float4& _windowPos, const float4& _windowSize)
{
    windowPos_ = _windowPos;
    windowSize_ = _windowSize;
    RECT windowRect = { 0, 0, windowSize_.IntX(), windowSize_.IntY() };
    AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, false);
    SetWindowPos(
        hWnd_,
        HWND_TOP,
        windowPos_.IntX(),
        windowPos_.IntY(),
        windowRect.right - windowRect.left, //windowSize_.IntX(), 
        windowRect.bottom - windowRect.top, //windowSize_.IntY(),
        0
    );
}

void J_Window::Update(void(*UpdateFunctions)())
{
    //MSG: 아래 tagMSG 구조체타입 변수 생성용 typedef. 사용자가 입력한 정보를 저장한다.
    //    typedef struct tagMSG {
    //        HWND        hwnd;         //윈도우를 그릴 때 필요한 정보를 가지고 있는 핸들.
    //        UINT        message;      //사용자가 입력한 내용.
    //        WPARAM      wParam;       //세부적인 입력 내용.
    //        LPARAM      lParam;       //세부적인 입력 내용. WPARAM과 무슨 차이인지는 모르겠다.
    //        DWORD       time;         //입력 시간.
    //        POINT       pt;           //입력이 들어왔을때 마우스 포인터가 있던 위치.
    //#ifdef _MAC
    //        DWORD       lPrivate;     
    //#endif
    //    } MSG, * PMSG, NEAR* NPMSG, FAR* LPMSG;

    //GetMessageW(): 입력이 들어왔을때 다른 입력내용들은 첫번째 매개변수인 msg를 통해서 전달하고,
    //종료 명령일때만 false를 반환해서 루프를 끝내고 윈도우를 닫는다.
    //입력이 들어오든 들어오지 않든 게임은 계속 실행되어야 하므로 여기서는 사용하지 않는다. 

    MSG msg;

    while (isWindowOn)
    {
        if (nullptr == UpdateFunctions) //업데이트 함수포인터가 연결이 안되어있다면 폭파.
        {
            assert(false && "nullptr == UpdateFunctions");
            return;
        }
        else
        {
            UpdateFunctions();
            //함수포인터도 변수처럼 쓰는 '함수'이므로 반드시 ()로 끝내줘야 한다.
            //J_GameEngineTime::GetInstance().UpdateDeltaTime();
            //J_Input::GetInstance().Update();
            //J_SoundManager::GetInstance().UpdateSound();
        }

        if (0 != PeekMessage(   //PeekMessage(): 상시 입력체크를 하다가 입력이 들어오면 0이 아닌 다른 값을 반환하고 msg에 입력의 자세한 내용을 저장한다.
            &msg,               //들어온 입력의 구체적인 내용 전달.
            //nullptr,            //윈도우 핸들. nullptr을 넣어주면 모든 윈도우의 메세지를 다 처리한다.
            this->hWnd_,
            0,                  //필터 최소??
            0,                  //필터 최대??
            PM_REMOVE           //지연되는 메시지 처리 방식 결정.
            //PM_REMOVE: 지연되는 메시지 지움. PM_NOREMOVE: 지연되는 메시지도 남김없이 처리함. 
            //PM_NOYIELD: ??
        ))       
        {
            if (!TranslateAccelerator(msg.hwnd, nullptr, &msg))
            {
                TranslateMessage(&msg); //사용자의 입력 내용을 정리, 변환해서 OS가 이해할 수 있는 형태로 만든다.
                DispatchMessage(&msg);  //WndProc()로 메시지를 보낸다.
            }
        }
    }
}

void J_Window::TurnOff()
{
    isWindowOn = false;
}

LRESULT CALLBACK WndProc(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
    switch (_message)
    {
    case WM_PAINT:
    {
        //WM_PAINT 메시지가 들어왔을때 BeginPaint()함수가 없으면 다른 윈도우에 가려진 무효영역을 그리기 위해
        //루프 함수에 WM_PAINT 메시지가 무한정 들어와서 절대로 PeekMessage()함수가 0을 반환하지 않는다.
        //그래서 WM_PAINT메시지를 처리할 거라면 반드시 BeginPaint()함수를 사용해야 한다. 
        //아니면 아예 WM_PAINT 메시지 자체를 직접 받지 말고 DefWindowProc() 함수로 넘겨야 한다.
        //GetDC()함수는 WM_PAINT 메시지를 처리해주지 못하므로 의미 없다. 반드시 BeginPaint()여야 한다.

        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(_hWnd, &ps);
        EndPaint(_hWnd, &ps);
        break;
    }
    case WM_DESTROY:
    {
        isWindowOn = false;
        break;
    }
    default:
        return DefWindowProc(_hWnd, _message, _wParam, _lParam);
    }
    return 0;
}