#pragma once

#pragma once

#include <Windows.h>
#include "vec2.h"
#include "vec3.h"

class cg_t;
class cgs_t;
class entity_t;
class clientinfo_t;
class input_t;
class usercmd_t;
class refdef_t;

class cg_t
{
public:
	__int64 iClientNum;
	char _0x0008[24];
	__int32 iFrameTime;
	char _0x0024[92];
	vec3_t vecOrigin;
	char _0x008C[808];
	__int32 Health;
	char _0x03B8[4];
	__int32 MaxHealth;
	char _0x03C0[804];
	__int32 iPrimaryAmmo;
	__int32 iSecondaryAmmo;
	__int32 iGrenadeAmmo;
	__int32 iFlashAmmo;
	char _0x06F4[332];
};

class cgs_t
{
public:
	char _0x0000[8];
	__int32 iWidth;
	__int32 iHeight;
	char _0x0010[320];
	__int32 iMaxPlayer;
	char _0x0154[13164];
};

class entity_t
{
public:
	char _0x0000[64];
	vec3_t vecOrigin;
	char _0x004C[4];
	float fYaw;
	char _0x0054[1340];
	__int32 ET_TYPE;
	char _0x0594[824];
	BYTE bAllive;
	char _0x08CD[11];

	bool isAlive()
	{
		return this->bAllive == 2;
	}
};

class clientinfo_t
{
public:
	__int32 iClientNumber;
	char _0x0004[4];
	__int32 iTeam;
	char _0x000C[32];
	char cName[32];
	char _0x004C[308];
};

class input_t
{
public:
	usercmd_t* GetCmd(int localClientNum, int num)
	{
		DWORD64 input = localClientNum * 0x1981a0 + *(DWORD64*)(0x1434400e8);
		return (usercmd_t*)(input + 80 * (num & 0x7F) + 0x10c068);
	}

};

class usercmd_t
{
public:
	__int32 iServerTime; 
	__int32 iButtons; 
	char _0x0008[8];
	__int32 iViewAngleX; 
	__int32 iViewAngleY; 
	__int32 iViewAngleZ;  
	__int32 iWeaponIndex; 

};

class refdef_t
{
public:
	char _0x0000[8];
	__int32 iWidth; 
	__int32 iHeight; 
	char _0x0010[96];
	float fFovX; 
	float fFovY; 
	float N1B5B9CB5; 
	char _0x007C[4];
	vec3_t vecOrigin; 
	char _0x008C[16];
	vec3_t vecAxisX; 
	vec3_t vecAxisY; 
	vec3_t vecAxisZ; 

};