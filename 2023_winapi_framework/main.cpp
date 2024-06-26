﻿#include<iostream>
#include "pch.h"
#include "BaseWindow.h"
using namespace std;
#ifdef _DEBUG
#ifdef UNICODE
    #pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
    #pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
#endif 

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(325);
    BaseWindow game({ WINDOW_WIDTH, WINDOW_HEIGHT });
    game.Run(hInstance, lpCmdLine, nCmdShow);
}