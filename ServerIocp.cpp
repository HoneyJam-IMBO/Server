#include "stdafx.h"
#include "ServerIocp.h"


DWORD WINAPI TimerThreadCallback(LPVOID parameter)
{

	CServerIocp *Owner = (CServerIocp*)parameter;
	Owner->TimerThreadCallback();

	return 0;
}

DWORD WINAPI DataBaseThreadCallback(LPVOID parameter) {
	CServerIocp *Owner = (CServerIocp*)parameter;
	Owner->KeepThreadCallback();

	return 0;
}


VOID CServerIocp::TimerThreadCallback(){
	m_bIsRun = TRUE;
	//
	int currentTime = 0;
	//std::cout << "Timer Start" << std::endl;
	//���� ���϶� ����
	while (m_bIsRun){

		//std::cout << std::endl;
		Sleep(1000);//1�� �� �Ŀ�
		while (true){
			//���� �ð��� ����
			if (0 != m_lCommand.size()){
				//��ɾ �ִٸ�
				currentTime = GetTickCount();

				//��ɱ���ü�� ���+�����ؾ��� �ð� + ������ ��ü �����͸� ������ �ڴ�.
				//std::cout << "event ����" << std::endl << std::endl;
				stCOMMAND command = GetCommand();

				//std::cout << "event üũ" << std::endl << std::endl;
				if (command.active_time > currentTime){
					//std::cout << "event �ð��� �����ð����� ����" << std::endl << std::endl;
					break;
				}

				//�̰� �ش� ��ü�� �ٲ�� ��.


				//CDynamicObject* pObject = reinterpret_cast<CDynamicObject*>(command.pObject);
			//	pObject->Command(mIocpHandle, command.active_command, command.active_time);
				PopCommand();

				//std::cout << pObject->GetID() << std::endl;
				//std::cout << "event POST" << std::endl << std::endl;
				//PostQueuedCompletionStatus(mIocpHandle, 0, COMMAND_KEY, reinterpret_cast<OVERLAPPED*>(&overlapped_excommand));

			}

		}
	}
}


//servermain thread callback�Լ�
//DWORD WINAPI ServerMainThreadCallback(LPVOID parameter)
//{
//	std::cout << "ServerMainThreadCallback Start" << std::endl;
//	CServerIocp *Owner = (CServerIocp*)parameter;
//	Owner->ServerMainThreadCallback();
//
//	return 0;
//}


// KeepAlive Thread Callback �Լ�
DWORD WINAPI KeepThreadCallback(LPVOID pParameter)
{
	//std::cout << "KeppThreadcallback Start" << std::endl;
	CServerIocp *pOwner = (CServerIocp*) pParameter;
	
	pOwner->KeepThreadCallback();

	return 0;
}

CServerIocp::CServerIocp(VOID)
{
	//m_ServerMainStartupEventHandle = NULL;
	//m_ServerMainEndEventHandle = NULL;
}

CServerIocp::~CServerIocp(VOID)
{
}

VOID CServerIocp::KeepThreadCallback(VOID)
{
	// KeepAlive ��ȣ
	DWORD dwKeepAlive = 0xFFFF;

	while (TRUE)
	{
		// 30�ʵ��� ���� �̺�Ʈ�� �߻����� ������ �Ѿ�ϴ�.
		DWORD dwResult = WaitForSingleObject(m_hKeepThreadDestroyEvent, 30000);

		// ���� �̺�Ʈ�� �߻�������� Thread�� �����մϴ�.
		if (dwResult == WAIT_OBJECT_0) return;

		// ������ �ִ� ��� Session�� ��Ŷ�� �����մϴ�.
		m_oConnectedSessionManager.WriteAll(0x3000000, (BYTE*)&dwKeepAlive, sizeof(DWORD));
	}
}
BOOL CServerIocp::BeginServerMain(){

	//m_pServerMain = new ServerMain(this);
	//m_pServerMain->Begin();

	//m_pServerMain->GetSpaceController()->ShowSpaceInfo();

	//HANDLE Thread = CreateThread(NULL, 0, ::ServerMainThreadCallback, this, 0, NULL);
	////mWorkerThreadVector.push_back(WorkerThread);
	//if (Thread == NULL)
	//	return FALSE;
	//WaitForSingleObject(m_ServerMainStartupEventHandle, INFINITE);
	//Ÿ�̸� ������ 

	//m_pTimerThread = new std::thread(::TimerThreadCallback, this);

	return TRUE;


}


//VOID CServerIocp::ServerMainThreadCallback(VOID)
//{
//
//	SetEvent(m_ServerMainStartupEventHandle);
//	
//	while (m_bIsRun){
//		//������ �� ������ ����
//
//		//���� �߰��� �ڵ�
//		Sleep(1000/GAME_FRAME); //30fps
//		
//		m_pServerMain->AnimateObjects();
//		
//
//	}
//		
//	SetEvent(m_ServerMainEndEventHandle);
//}

// CIocp�� �����Լ���
VOID CServerIocp::OnIoConnected(VOID *pObject)
{

	std::cout << "OnIoConnected" << std::endl;
	// ���� �����Լ����� �Ѿ�� pObject�� ������ ����� ��ü�� �Ѿ���� �˴ϴ�.
	// �̰��� ���⼭ Ŭ���̾�Ʈ�� ������ CConnectedSession���� ����ȯ�� �� �־� �ް� �˴ϴ�.
	// ����ȯ�� reinterpret_cast�� ����մϴ�.
	CConnectedSession *pConnectedSession = reinterpret_cast<CConnectedSession*>(pObject);
	//1. �� ��ü�� ������ �� player�� ����µ� player�� space��ü�� �����ڿ��� ID�� �ڽ��� �����ͷ� set���ش�.

	if (!pConnectedSession){
		return;
	}

	// ������ ��ü�� IO�� IOCP�� ���ؼ� �ޱ����ؼ� IOCP�� ����ϴ� ������ ��ġ�� �˴ϴ�.
	// ���⼭ GetSocket�� �̿��ؼ� ������ ����ϰ� �ش� Ű�� ��ü�� �����͸� �̿��ϰ� �˴ϴ�.
	if (!CIocp::RegisterSocketToIocp(pConnectedSession->GetSocket(), reinterpret_cast<ULONG_PTR>(pConnectedSession))) 
		return;

	// IOCP �ʱ� �ޱ⸦ ������ �ݴϴ�.
	if (!pConnectedSession->InitializeReadForIocp())
	{ 
		// ���� �������� ��� ��ü�� ������� �ݴϴ�.
		pConnectedSession->Restart(m_pListen->GetSocket()); 
		return; 
	}

	pConnectedSession->SetConnected(TRUE);



	//�÷��̾��� ��ġ�� �ʱ�ȭ �Ǿ������ϱ� ������ ������ �ش�.
	//���⼭ �� ���ְŵ��!!

	//���߿� �߰� 
	//0606
	//m_pServerMain->GetSpaceController()->AddPlayer(pConnectedSession);
	//0606

	//�÷��̾ ������ ������ �Ϸ��ߴٴ� ��Ŷ ����

	//������ ��� ������ ������ ���� 
	//���߿��� �ش� ������ ������ ��� ������ �ٲ���.
	//���� ����,

	//�̰͵� �� �ʿ䰡 ����ȿ !
	//�̰� �� ID�� �����ָ� �Ǵ°ž�
	//pConnectedSession->GetPlayer()->GetSpace()->WriteEnterServer_S(pConnectedSession);

	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };

	INT id = pConnectedSession->GetPlayer()->GetNETWORK_ID();
	//���� ������ �˸�
	pConnectedSession->WritePacket(PT_ENTER_SERVER_SUC, Packet, WRITE_PT_ENTER_SERVER_SUC(Packet, id));

	// �α� �����ϸ� �� ��� ������ ������
	ZeroMemory(Packet, MAX_BUFFER_LENGTH);
	pConnectedSession->WritePacket(PT_ROOM_LIST_COUNT_SC, Packet, WRITE_PT_ROOM_LIST_COUNT_SC(Packet, m_RoomManager.GetRoomCount()));

	for (int i = 0; i < m_RoomManager.GetRoomCount(); ++i) {
		ZeroMemory(Packet, MAX_BUFFER_LENGTH);
		pConnectedSession->WritePacket(PT_ROOM_LIST_SC, Packet, WRITE_PT_ROOM_LIST_SC(Packet, m_RoomManager.GetRoomsList()[i]->GetRoomID(), m_RoomManager.GetRoomsList()[i]->GetPlayerNum()));
		////
	}
	//CPlayer* pPlayer = pConnectedSession->GetPlayer();
	//
	//XMFLOAT3 xmfPos;
	//XMStoreFloat3(&xmfPos, pPlayer->GetPlayerPosition());
	//
	//pConnectedSession->WritePacket(PT_ENTER_SERVER_S, Packet, WRITE_PT_ENTER_SERVER_S(Packet,
	//	pPlayer->GetID(), xmfPos.x, xmfPos.y, xmfPos.z));
	//
	//std::cout << "PT_ENTER_SERVER_S send suc" << std::endl;


	//������ �ڽ��� ������ ��� ����ڿ��� ���� �� ���� �� �ʿ䰡 �����
	//BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };
	//XMFLOAT3 xmfPos;
	//XMStoreFloat3(&xmfPos, pConnectedSession->GetPlayer()->GetPlayerPosition());
	//pConnectedSession->GetPlayer()->GetSpace()->WriteAll(PT_ENTER_SERVER_ALL, Packet, WRITE_PT_ENTER_SERVER_ALL(
	//	Packet, pConnectedSession->GetPlayer()->GetID(), xmfPos.x, xmfPos.y, xmfPos.z));


	
	//XMStoreFloat3(&xmfPos, pConnectedSession->GetPlayer()->GetPlayerPosition());
	//std::cout << "OnIoConnected : ID - " << pConnectedSession->GetPlayer()->GetID() << std::endl << " Pos - " << xmfPos.x << ", " << xmfPos.y << ", " << xmfPos.z << std::endl;

	//CLog::WriteLog(_T("player connected, id : "));
	//std::cout << pConnectedSession->GetPlayer()->GetID() << std::endl;
}

VOID CServerIocp::OnIoDisconnected(VOID *pObject)
{
	std::cout << "OnDisConnected" << std::endl;

	// ���� �����Լ����� �Ѿ�� pObject�� OnIoConnected�� ���������� ������ ����� ��ü�� �Ѿ���� �˴ϴ�.
	// �̰��� ���⼭ Ŭ���̾�Ʈ�� ������ CConnectedSession���� ����ȯ�� �� �־� �ް� �˴ϴ�.
	// ����ȯ�� reinterpret_cast�� ����մϴ�.
	CConnectedSession *pConnectedSession = reinterpret_cast<CConnectedSession*>(pObject);
	
	if (!pConnectedSession) {
		return;
	}

	

	//������ �ִ� �÷��̾� ����
	//�� �Լ����� �� �÷��̾ �������� �˸� 
	//space* pSpace = pConnectedSession->GetPlayer()->GetSpace();
	
	//CRoom* pRoom = pConnectedSession->GetRoom();
	INT SLOT_ID = pConnectedSession->GetPlayer()->GetSLOT_ID();
	INT ROOM_ID = pConnectedSession->GetPlayer()->GetROOM_ID();
	if(ROOM_ID != -1)
		m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->RemovePlayer(SLOT_ID);
	//pRoom->RemovePlayer(SLOT_ID);
	// ������ �����Ͽ��� ������ ��ü�� ������� �ݴϴ�.
	pConnectedSession->Restart(m_pListen->GetSocket());

	pConnectedSession->SetConnected(FALSE);
}

VOID CServerIocp::OnIoRead(VOID *pObject, DWORD dwDataLength)
{
	// ���� �����Լ����� �Ѿ�� pObject�� OnIoConnected�� ���������� ������ ����� ��ü�� �Ѿ���� �˴ϴ�.
	// �̰��� ���⼭ Ŭ���̾�Ʈ�� ������ CConnectedSession���� ����ȯ�� �� �־� �ް� �˴ϴ�.
	// ����ȯ�� reinterpret_cast�� ����մϴ�.
	CConnectedSession *pConnectedSession = reinterpret_cast<CConnectedSession*>(pObject);

	if (!pConnectedSession) {
		return;
	}
	// ���� �������ݰ� ��Ŷ ���̸� �����ϴ� ����
	DWORD dwProtocol = 0, dwPacketLength = 0;
	// ��Ŷ�� �����ϴ� ����
	BYTE Packet[MAX_BUFFER_LENGTH] = {0,};

	// CNetworkSession���� CPacketSession���� �����͸� �����ɴϴ�.
	if (pConnectedSession->ReadPacketForIocp(dwDataLength))
	{
		// CPacketSession���� ��Ŷ�� �̾� ���ϴ�.
		while (pConnectedSession->GetPacket(dwProtocol, Packet, dwPacketLength))
		{
			// �������ݿ� ���� switch ��
			switch (dwProtocol)
			{
			//Ŭ���̾�Ʈ�� �� �����Ӹ��� �ڽ��� ��ġ�� ������ �ִ� �������� ��������
			case PT_LOGIN_CS:
				PROC_PT_LOGIN_CS(pConnectedSession, dwProtocol, Packet, dwPacketLength);
				break;
			case PT_SIGN_UP_CS:
				PROC_PT_SIGN_UP_CS(pConnectedSession, dwProtocol, Packet, dwPacketLength);
				break;
			//�༺����
			case PT_ENTER_EARTH_CS:
				PROC_PT_ENTER_EARTH_CS(pConnectedSession, dwProtocol, Packet, dwPacketLength);
				break;
			case PT_KEY_INPUT_CS:
				PROC_PT_KEY_INPUT_CS(pConnectedSession, dwProtocol, Packet, dwPacketLength);
				break;
			case PT_MOUSE_INPUT_CS:
				PROC_PT_MOUSE_INPUT_CS(pConnectedSession, dwProtocol, Packet, dwPacketLength);
				break;
			case PT_MOUSE_BUTTON_INPUT_CS:
				PROC_PT_MOUSE_BUTTON_INPUT_CS(pConnectedSession, dwProtocol, Packet, dwPacketLength);
				break;
			case PT_ROOM_CREATE_CS:
				PROC_PT_ROOM_CREATE_CS(pConnectedSession, dwProtocol, Packet, dwPacketLength);
				break;
			case PT_ROOM_DATA_CHANGE_CS:
				PROC_PT_ROOM_DATA_CHANGE_CS(pConnectedSession, dwProtocol, Packet, dwPacketLength);
				break;
			case PT_ROOM_JOIN_CS:
				PROC_PT_ROOM_JOIN_CS(pConnectedSession, dwProtocol, Packet, dwPacketLength);
				break;
			case PT_FTOWN_READY_CS:
				PROC_PT_FTOWN_READY_CS(pConnectedSession, dwProtocol, Packet, dwPacketLength);
			case PT_ALDENARD_READY_CS:
				PROC_PT_FTOWN_READY_CS(pConnectedSession, dwProtocol, Packet, dwPacketLength);
			case PT_SARASEN_READY_CS:
				PROC_PT_FTOWN_READY_CS(pConnectedSession, dwProtocol, Packet, dwPacketLength);
			case PT_FREQUENCY_MOVE_CS:
				PROC_PT_FREQUENCY_MOVE_CS(pConnectedSession, dwProtocol, Packet, dwPacketLength);
				break;
			case PT_MOUSE_LEFT_ATTACK_CS:
				PROC_PT_MOUSE_LEFT_ATTACK_CS(pConnectedSession, dwProtocol, Packet, dwPacketLength);
				break;
			}
		}
	}

	if (!pConnectedSession->InitializeReadForIocp())
		pConnectedSession->Restart(m_pListen->GetSocket());
}

VOID CServerIocp::OnIoWrote(VOID *pObject, DWORD dwDataLength)
{
	CConnectedSession *pConnectedSession = reinterpret_cast<CConnectedSession*>(pObject);

	if (!pConnectedSession) return;

	pConnectedSession->WriteComplete();
}
VOID CServerIocp::OnIoProcAI(VOID *pObject)
{
	//CDynamicObject *pDynamicObject = reinterpret_cast<CDynamicObject*>(pObject);

	//pDynamicObject->CheckCollition(m_pServerMain->GetSpaceController());
	//pDynamicObject->CommandCollisionComplate();

	
	//�� �� �� �� �� �� �� 
	//�� �� �� �� �� �� �� 
	//�� �� �� �� �� �� �� 
	//�� �� �� �� �� �� �� 
	//�� �� �� �� �� �� �� 
	//�� �� �� �� �� �� �� 
	//�� �� �� �� �� �� �� 

	//�� �� �� �� �� �� �� 
}

VOID CServerIocp::OnIoProcDB(VOID* pObject) {
	int ret = 0 ;
	DB_ST* pDBST = reinterpret_cast<DB_ST*>(pObject);
	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };
	CConnectedSession* pSession = reinterpret_cast<CConnectedSession*>(pDBST->pSession);
	//�ؼ� ���� �÷��̾� ��ü���� ����� �뺸

	switch (pDBST->etype) {
	case LOADID:
		if (pSession->GetDBevent() == LOADID) // ���� �α��� ��û�̿��ٸ�
		{
			if (wcscmp(pDBST->idpw.ID, pSession->GetID()) != 0)
				ret++;
			if (wcscmp(pDBST->idpw.PW, pSession->GetPW()) != 0)
				ret++;
			if (true == m_oConnectedSessionManager.IsThisIDLogin(pDBST->idpw.PW))
				ret = -1;

			if (ret == 0) { // �α��� ����
				pSession->WritePacket(PT_LOGIN_SERVER_SUC, Packet, WRITE_PT_LOGIN_SERVER_SUC(Packet));

				// �α� �����ϸ� �� ��� ������ ������
				ZeroMemory(Packet, MAX_BUFFER_LENGTH);
				pSession->WritePacket(PT_ROOM_LIST_COUNT_SC, Packet, WRITE_PT_ROOM_LIST_COUNT_SC(Packet, m_RoomManager.GetRoomCount()));

				for (int i = 0; i < m_RoomManager.GetRoomCount(); ++i) {
					ZeroMemory(Packet, MAX_BUFFER_LENGTH);
					pSession->WritePacket(PT_ROOM_LIST_SC, Packet, WRITE_PT_ROOM_LIST_SC(Packet, m_RoomManager.GetRoomsList()[i]->GetRoomID(), m_RoomManager.GetRoomsList()[i]->GetPlayerNum()));
				////

				}
			}
			else if(ret == -1)
				pSession->WritePacket(PT_LOGIN_SERVER_ALREADY, Packet, WRITE_PT_LOGIN_SERVER_FAIL(Packet));
			else
				pSession->WritePacket(PT_LOGIN_SERVER_FAIL, Packet, WRITE_PT_LOGIN_SERVER_FAIL(Packet));

			
		}
		else if (pSession->GetDBevent() == SIGNUP) // ���� ȸ������ ��û�̿��ٸ�
		{
			if (wcscmp(pDBST->idpw.ID, pSession->GetID()) == 0)
				ret++;

			if (ret == 0) {
				// DB ȸ������ ��û
				stDBQUEUE dbQueueData;
				dbQueueData.etype = SIGNUP;
				dbQueueData.pSession = pDBST->pSession;
				wsprintf(dbQueueData.ExecCode, L"EXEC dbo.Sign_Up_SP2 %s, %s", pDBST->idpw.ID, pDBST->idpw.PW);

				m_DataBase.pushDBEvent(dbQueueData);

				pSession->WritePacket(PT_SIGN_UP_SUC_SC, Packet, WRITE_PT_SIGN_UP_SUC_SC(Packet));
			}
			else
				pSession->WritePacket(PT_SIGN_UP_FAIL_SC, Packet, WRITE_PT_SIGN_UP_FAIL_SC(Packet));
		}

		break;
	//case SIGNUP:
	//	break;
	}
	
	//else if (eUPDATE_PLAYER_XY == (*pType)) {
		//Ÿ���� �˾����� �ش� Ÿ������ ����ȯ
		//CConnectedSession* pSession = reinterpret_cast<CConnectedSession*>(pObject);
		//�ؼ� ���� �÷��̾� ��ü���� ����� �뺸
		//std::cout << pCmp->x << ", " << pCmp->y << std::endl;;

}
BOOL CServerIocp::Begin(VOID)
{
	// ��� ���� IOCP ��ü�� �����մϴ�.
	if (!CIocp::Begin()) return FALSE;

	// Listen�� ����� ��ü�� �����մϴ�.
	m_pListen = new CNetworkSession();

	// ��ü�� �����մϴ�.
	if (!m_pListen->Begin())
	{
		// �������� ��� End�Լ��� ȣ���ϰ� �����մϴ�.
		CServerIocp::End();

		return FALSE;
	}

	// TCP�� ����� ���� �����մϴ�.
	if (!m_pListen->TcpBind())
	{
		// �������� ��� End�Լ��� ȣ���ϰ� �����մϴ�.
		CServerIocp::End();

		return FALSE;
	}

	// ��Ʈ 9595���� Listen�� �ϰ� �ִ� 100������ �����մϴ�.
	
	if (!m_pListen->Listen(DEFAULT_PORT, MAX_USER))
	{
		// �������� ��� End�Լ��� ȣ���ϰ� �����մϴ�.
		CServerIocp::End();

		return FALSE;
	}

	// IOCP�� Listen ������ ��Ͻ��� �ݴϴ�. �׸��� Ű�δ� �ش� ��ü�� �����͸� �����մϴ�.
	if (!CIocp::RegisterSocketToIocp(m_pListen->GetSocket(), reinterpret_cast<ULONG_PTR>(m_pListen)))
	{
		// �������� ��� End�Լ��� ȣ���ϰ� �����մϴ�.
		CServerIocp::End();

		return FALSE;
	}

	// CConnectedSessionManager�� �����մϴ�.
	// ���� �Լ������� CConnectedSession�� �����ϰ� Accept���·� ����� �ڵ尡 �߰��Ǿ� �ֽ��ϴ�.
	if (!m_oConnectedSessionManager.Begin(m_pListen->GetSocket()))
	{
		CServerIocp::End();

		return FALSE;
	}

	// KeepAlive ���� �̺�Ʈ�� �����մϴ�.
	m_hKeepThreadDestroyEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (!m_hKeepThreadDestroyEvent)
	{ 
		// ����������� �����մϴ�.
		CServerIocp::End(); 
		return FALSE; 
	}

	// KeepAlive Thread�� �����մϴ�.
	m_hKeepThread = CreateThread(NULL, 0, ::KeepThreadCallback, this, 0, NULL);
	if (!m_hKeepThread) 
	{ 
		// ���� �������� ��� �����մϴ�.
		CServerIocp::End(); 
		return FALSE; 
	}
	
	////���� ���� ������ ��� ����
	//m_ServerMainStartupEventHandle = CreateEvent(0, FALSE, FALSE, 0);
	//if (m_ServerMainStartupEventHandle == NULL)
	//{
	//	End();
	//
	//	return FALSE;
	//}
	//m_ServerMainEndEventHandle = CreateEvent(0, FALSE, FALSE, 0);
	//if (m_ServerMainEndEventHandle == NULL)
	//{
	//	End();
	//	return FALSE;
	//}
	m_bIsRun = FALSE;
	m_DataBase.Begin(mIocpHandle);
	m_RoomManager.Begin();
	std::cout << "Server Start : port - %d, max user - %d" << DEFAULT_PORT << MAX_USER <<std::endl;

	return TRUE;
}

VOID CServerIocp::End(VOID)
{
	// CServerIocp�� �����Ҷ�

	//ServerMain����
	m_bIsRun = FALSE;

	// m_mUser ����

	// m_hKeepThread�� NULL�� �ƴϸ� KeepAlive Thread�� ������ �ݴϴ�.
	if (m_hKeepThread)
	{
		// ���� �̺�Ʈ�� �߻���ŵ�ϴ�.
		SetEvent(m_hKeepThreadDestroyEvent);

		// Thread�� ����� ������ ����մϴ�.
		WaitForSingleObject(m_hKeepThread, INFINITE);

		// �ڵ鰪�� �ݾ��ݴϴ�.
		CloseHandle(m_hKeepThread);
		m_hKeepThread = NULL;
	}

	// KeepAlive ���� �̺�Ʈ�� NULL�� �ƴϸ�
	if (m_hKeepThreadDestroyEvent)
	{
		// �̺�Ʈ�� �ݾ��ݴϴ�.
		CloseHandle(m_hKeepThreadDestroyEvent);
		m_hKeepThreadDestroyEvent = NULL;
	}
	
	//
//	if (m_ServerMainStartupEventHandle)
//		CloseHandle(m_ServerMainStartupEventHandle);


	//Ÿ�̸� ������ ���� �˻�
	//m_pTimerThread->join();

	// IOCP�� �����մϴ�.
	CIocp::End();
	m_DataBase.End();
	m_RoomManager.End();
	// CConnectedSessionManager�� �����մϴ�.
	m_oConnectedSessionManager.End();

	// �����ߴ� Listen�� ��ü�� �����ϰ� ������ �ݴϴ�.
	if (m_pListen)
	{
		m_pListen->End();

		delete m_pListen;
	}

	//ServerMain�� �����ϱ⸦ ��ٸ�
	//WaitForSingleObject(m_ServerMainEndEventHandle, INFINITE);
	//if (m_ServerMainEndEventHandle)
	//	CloseHandle(m_ServerMainEndEventHandle);
}



//Ŀ��Ʈ ����Ʈ �Լ�
void CServerIocp::AddCommand(stCOMMAND stCmd){
	//Ŀ��带 �ð������� �����ְ� �տ� ������ �����ؼ� �ִ´�.
	//int i = 0;
	lock();
	//m_lCommand.push_back(stCmd);
	//unlock();
	//
	//return;
	if (0 == m_lCommand.size()){
		//����� ������ �׳� �������
		m_lCommand.push_back(stCmd);
		unlock();
		return;
	}

	auto i = m_lCommand.begin();
	if (i->active_time > stCmd.active_time){
		//���� ó������ ������ �Ǿտ� ����
		m_lCommand.push_front(stCmd);
		unlock();
		return;
	}
	for (i; i != m_lCommand.end(); ++i) {


		if (i->active_time <= stCmd.active_time) {
			//Ŀ���� �� ���� ����
			// a�� b���� Ŭ�� ����
			m_lCommand.insert(i, stCmd);
			break;
		}

	}

	unlock();

}
stCOMMAND CServerIocp::GetCommand(){
	//ó�� ���� �����ؼ� 
	lock();
	stCOMMAND return_value = *m_lCommand.begin();
	unlock();

	return return_value;
}
void CServerIocp::PopCommand(){
	lock();
	//ó�� ����� ����
	m_lCommand.erase(m_lCommand.begin());
	unlock();
}
//Ŀ��Ʈ ����Ʈ �Լ�