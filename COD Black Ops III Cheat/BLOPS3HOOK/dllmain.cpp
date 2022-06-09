#define _cRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include "MinHook.h"
#include <stdio.h>
#include <math.h>
#include "globalvars.h"
#include "rendering.h"
#include "esp.h"
#include "aimbot.h"
#include "radar.h"
#include "healthbar.h"

#if defined _M_X64
#pragma comment(lib, "libMinHook-x64-v120-mdd.lib")
#endif

Rendering rendering;
Esp esp;
Radar radar;
HealthBar healthBar;
bool firstRun = true;

void InitVars()
{
	rendering.Init();

}

__int64 hRegisterShader(char* shadername, int num, unsigned int num2, unsigned int num3)
{
	puts(shadername);
	return pRegisterShader(shadername, num, num2, num3);
}

int __fastcall hCG_Draw2D(int localClientNum)
{
	int val = pCG_Draw2D(localClientNum);
	if (firstRun)
	{
		InitVars();
		firstRun = false;
	}

	float color[4] = { 1.f, 0.64f, 0.f, 1.f };
	float color2[4] = { 0.f, 0.f, 1.f, 1.f };
	float color3[4] = { 1.f, 0.f, 0.f, 1.f };
	float color4[4] = { 0.f, 1.f, 0.f, 1.f };
	rendering.DrawBox(10, 10, 100, 100, color);

	return val;
}

void __fastcall hCL_WritePacket(int localClientNum)
{
	int num = pCL_GetCurrentCmdNumber(localClientNum);
	return pCL_WritePacket(localClientNum);
}

__int64 hBG_WeaponFireRecoil(double val, void* ps, float* recoilSpeed, float* kickaVel)
{
	return 0;
}

void startConsole()
{
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	freopen("CONIN$", "r", stdin);
}

BOOL Init()
{
	startConsole();


	if (MH_Initialize() != MH_OK) {
		printf("Init failed!\n");
		return 1;
	}

	//CG_Draw2D
	if (MH_CreateHook((LPVOID)(OFFCG_Draw2D), &hCG_Draw2D, reinterpret_cast<LPVOID*>(&pCG_Draw2D)) != MH_OK) {
		printf("Hook creation failed! %d\n", MH_CreateHook((LPVOID)(OFFCG_Draw2D), &hCG_Draw2D, reinterpret_cast<LPVOID*>(&pCG_Draw2D)));
		return 1;
	}

	if (MH_EnableHook((LPVOID)(OFFCG_Draw2D)) != MH_OK) {
		printf("Hook enable failed %d!\n", MH_EnableHook((LPVOID)(OFFCG_Draw2D)));
		return 1;
	}

	return TRUE;
}

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD reason, LPVOID lpReserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)&Init, NULL, NULL, NULL);
		break;
	default:
		break;
	}

	return TRUE;
}