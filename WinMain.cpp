#pragma once
#include "Game.h"
#include "windows.h"

#define IDI_MYICON 201

using namespace Polycode;

#if defined(_DEBUG)
Game * pGame;
#else
std::unique_ptr<main> pMain;
#endif

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	PolycodeView *view = new PolycodeView(hInstance, nCmdShow, L"Voxel Alpha 1.0");

#if defined(_DEBUG)
	pGame = new Game(view);
#else
	pAsteroids = std::unique_ptr<Asteroids>( new Asteroids(view) );
#endif
	
	HICON hMyIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYICON));
	SendMessage(view->hwnd, WM_SETICON, (WPARAM)ICON_SMALL, (LPARAM)hMyIcon);

	MSG Msg;

	do
	{
		while (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
	} 
	while (pGame->Update());

	return Msg.wParam;
}