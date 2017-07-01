// Server.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
//#include "ServerMain.h"
#include "Timer.h"

int _tmain(int argc, _TCHAR* argv[])
{
	CoInitialize(NULL);

	// Winsock�� ����ϱ� ���� DLL �ε�
	WSADATA WsaData;
	WSAStartup(MAKEWORD(2, 2), &WsaData);	// 2.2 ������ �ε��մϴ�.
  
	// ������ ũ���� �Ǿ����� ó���� �� �ְ� �ϴ� MiniDump
	if (!CMiniDump::Begin())
		return 0;

	// ������ �����ϴ°�
	//���� ���� ����, ���� ������ ���� Ŭ����
	//ServerMain* sm = nullptr;
	CGameTimer m_GameTimer;
	float fTimeElapsed;
	//���� IOCP ����� ����ϴ� Ŭ����
	CServerIocp ServerIocp;
	if (ServerIocp.Begin())
	{
		//ServerBegin
		ServerIocp.BeginServerMain();
		//ServerBegin
		char a;
		std::cin >> a;

		//while (true){
		//	m_GameTimer.Tick();
		//	fTimeElapsed = m_GameTimer.GetTimeElapsed();
		//	sm->AnimateObjects(fTimeElapsed);
		//}

		ServerIocp.End();
	}

	// ����� DLL�� ��ε� ��ŵ�ϴ�.
	WSACleanup();
	CMiniDump::End();	// MiniDump�� �����ϴ�.
	CoUninitialize();

	return 0;
}

