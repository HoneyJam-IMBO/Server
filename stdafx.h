// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������ 
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#define DEBUG

#include "../Assets/import/LowLib/Global.h"

//direct ���
#include <Mmsystem.h>
#include <math.h>

//#include <d3d11.h>
//#include <d3dx11.h>
//#include <D3DX10Math.h>
//#include <d3dcompiler.h>
//

//#include <DirectXMath.h>
//#include <DirectXColors.h>
//#include <DirectXPackedVector.h>
//#include <DirectXCollision.h>

#include "../Assets/import/LowLib/CriticalSection.h"
#include "../Assets/import/LowLib/MultiThreadSync.h"
#include "../Assets/import/LowLib/MemoryPool.h"
#include "../Assets/import/LowLib/CircularQueue.h"
#include "../Assets/import/LowLib/NetworkSession.h"
#include "../Assets/import/LowLib/PacketSession.h"
#include "../Assets/import/LowLib/Iocp.h"
#include "../Assets/import/LowLib/Stream.h"
#include "../Assets/import/LowLib/MiniDump.h"
#include "../Assets/import/LowLib/IniFile.h"

#include "CircularQueue.h"

#include "Protocol.h"
#include "PT_Structure.h"
#include "PT_ReadPacket.h"
#include "PT_WritePacket.h"



#include "ConnectedSession.h"
#include "ConnectedSessionManager.h"

#include "Timer.h"
#include "Object.h"
//#include "Space.h"
//#include "ServerMain.h"
#include "ServerIocp.h"
//#include "Space.h"


//����
//#include "Space.h"
#define RANDOM_DIR ((rand() * 0xFFFFFF) / RAND_MAX )-1

//
////�������� ���� ����
//#define STATIC_OBJECT_LIMIT	200
////�������� ���� ���� protocol struct ����� ���ǵǾ� ���� 
//
#include "DLinkedList.h"
//����
#include <map>
#include <set>
#include <algorithm>
#include <list>
#include <vector>
#include <queue>
//#include <sqlext.h>

using namespace std;

static void gotoxy(int x, int y, const char *msg, ...){
#ifdef _DEBUG
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	va_list arg;

	va_start(arg, msg);
	vprintf(msg, arg);
	va_end(arg);

	printf("\n");

#endif
}