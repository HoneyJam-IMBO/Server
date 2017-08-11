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
	//게임 중일때 동안
	while (m_bIsRun){

		//std::cout << std::endl;
		Sleep(1000);//1초 쉰 후에
		while (true){
			//현제 시간을 받음
			if (0 != m_lCommand.size()){
				//명령어가 있다면
				currentTime = GetTickCount();

				//명령구조체에 명령+수행해야할 시간 + 수행할 객체 포인터를 가져야 겠다.
				//std::cout << "event 복사" << std::endl << std::endl;
				stCOMMAND command = GetCommand();

				//std::cout << "event 체크" << std::endl << std::endl;
				if (command.active_time > currentTime){
					//std::cout << "event 시간이 현제시간보다 많음" << std::endl << std::endl;
					break;
				}

				//이거 해당 객체로 바꿔야 함.


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


//servermain thread callback함수
//DWORD WINAPI ServerMainThreadCallback(LPVOID parameter)
//{
//	std::cout << "ServerMainThreadCallback Start" << std::endl;
//	CServerIocp *Owner = (CServerIocp*)parameter;
//	Owner->ServerMainThreadCallback();
//
//	return 0;
//}


// KeepAlive Thread Callback 함수
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
	// KeepAlive 신호
	DWORD dwKeepAlive = 0xFFFF;

	while (TRUE)
	{
		// 30초동안 종료 이벤트가 발생하지 않으면 넘어갑니다.
		DWORD dwResult = WaitForSingleObject(m_hKeepThreadDestroyEvent, 30000);

		// 종료 이벤트가 발생했을경우 Thread를 종료합니다.
		if (dwResult == WAIT_OBJECT_0) return;

		// 접속해 있는 모든 Session에 패킷을 전송합니다.
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
	//타이머 쓰레드 

	//m_pTimerThread = new std::thread(::TimerThreadCallback, this);

	return TRUE;


}


//VOID CServerIocp::ServerMainThreadCallback(VOID)
//{
//
//	SetEvent(m_ServerMainStartupEventHandle);
//	
//	while (m_bIsRun){
//		//게임이 끝 났으면 종료
//
//		//지금 추가한 코드
//		Sleep(1000/GAME_FRAME); //30fps
//		
//		m_pServerMain->AnimateObjects();
//		
//
//	}
//		
//	SetEvent(m_ServerMainEndEventHandle);
//}

// CIocp의 가상함수들
VOID CServerIocp::OnIoConnected(VOID *pObject)
{

	std::cout << "OnIoConnected" << std::endl;
	// 여기 가상함수에서 넘어온 pObject는 접속을 담당한 개체가 넘어오게 됩니다.
	// 이것을 여기서 클라이언트를 관리할 CConnectedSession으로 형변환을 해 주어 받게 됩니다.
	// 형변환은 reinterpret_cast를 사용합니다.
	CConnectedSession *pConnectedSession = reinterpret_cast<CConnectedSession*>(pObject);
	//1. 이 객체가 생성될 대 player를 만드는데 player는 space객체라서 생성자에서 ID를 자신의 포인터로 set해준다.

	if (!pConnectedSession){
		return;
	}

	// 접속한 개체의 IO를 IOCP를 통해서 받기위해서 IOCP에 등록하는 과정을 거치게 됩니다.
	// 여기서 GetSocket을 이용해서 소켓을 등록하고 해당 키는 개체의 포인터를 이용하게 됩니다.
	if (!CIocp::RegisterSocketToIocp(pConnectedSession->GetSocket(), reinterpret_cast<ULONG_PTR>(pConnectedSession))) 
		return;

	// IOCP 초기 받기를 실행해 줍니다.
	if (!pConnectedSession->InitializeReadForIocp())
	{ 
		// 만일 실패했을 경우 개체를 재시작해 줍니다.
		pConnectedSession->Restart(m_pListen->GetSocket()); 
		return; 
	}

	pConnectedSession->SetConnected(TRUE);



	//플레이어의 위치가 초기화 되어있으니까 공간을 설정해 준다.
	//여기서 다 해주거든요!!

	//나중에 추가 
	//0606
	//m_pServerMain->GetSpaceController()->AddPlayer(pConnectedSession);
	//0606

	//플레이어가 서버에 접속을 완료했다는 패킷 전송

	//접속한 모든 유저의 정보를 주자 
	//나중에는 해당 공간에 접속한 모든 유저로 바꾸자.
	//접속 성공,

	//이것도 할 필요가 없어효 !
	//이건 내 ID만 정해주면 되는거야
	//pConnectedSession->GetPlayer()->GetSpace()->WriteEnterServer_S(pConnectedSession);

	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };

	INT id = pConnectedSession->GetPlayer()->GetNETWORK_ID();
	//접속 성공을 알림
	pConnectedSession->WritePacket(PT_ENTER_SERVER_SUC, Packet, WRITE_PT_ENTER_SERVER_SUC(Packet, id));

	// 로긴 성공하면 방 목록 정보를 보낸다
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


	//접속한 자신의 정보를 모든 사용자에게 전송 은 이제 할 필요가 없어요
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

	// 여기 가상함수에서 넘어온 pObject는 OnIoConnected와 마찬가지로 접속을 담당한 개체가 넘어오게 됩니다.
	// 이것을 여기서 클라이언트를 관리할 CConnectedSession으로 형변환을 해 주어 받게 됩니다.
	// 형변환은 reinterpret_cast를 사용합니다.
	CConnectedSession *pConnectedSession = reinterpret_cast<CConnectedSession*>(pObject);
	
	if (!pConnectedSession) {
		return;
	}

	

	//공간에 있는 플레이어 삭제
	//이 함수에서 이 플레이어가 나갔음을 알림 
	//space* pSpace = pConnectedSession->GetPlayer()->GetSpace();
	
	//CRoom* pRoom = pConnectedSession->GetRoom();
	INT SLOT_ID = pConnectedSession->GetPlayer()->GetSLOT_ID();
	INT ROOM_ID = pConnectedSession->GetPlayer()->GetROOM_ID();
	if(ROOM_ID != -1)
		m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->RemovePlayer(SLOT_ID);
	//pRoom->RemovePlayer(SLOT_ID);
	// 접속을 종료하였기 때문에 개체를 재시작해 줍니다.
	pConnectedSession->Restart(m_pListen->GetSocket());

	pConnectedSession->SetConnected(FALSE);
}

VOID CServerIocp::OnIoRead(VOID *pObject, DWORD dwDataLength)
{
	// 여기 가상함수에서 넘어온 pObject는 OnIoConnected와 마찬가지로 접속을 담당한 개체가 넘어오게 됩니다.
	// 이것을 여기서 클라이언트를 관리할 CConnectedSession으로 형변환을 해 주어 받게 됩니다.
	// 형변환은 reinterpret_cast를 사용합니다.
	CConnectedSession *pConnectedSession = reinterpret_cast<CConnectedSession*>(pObject);

	if (!pConnectedSession) {
		return;
	}
	// 받은 프로토콜과 패킷 길이를 저장하는 변수
	DWORD dwProtocol = 0, dwPacketLength = 0;
	// 패킷을 저장하는 변수
	BYTE Packet[MAX_BUFFER_LENGTH] = {0,};

	// CNetworkSession에서 CPacketSession으로 데이터를 가져옵니다.
	if (pConnectedSession->ReadPacketForIocp(dwDataLength))
	{
		// CPacketSession에서 패킷을 뽑아 냅니다.
		while (pConnectedSession->GetPacket(dwProtocol, Packet, dwPacketLength))
		{
			// 프로토콜에 따른 switch 문
			switch (dwProtocol)
			{
			//클라이언트가 매 프레임마다 자신의 위치를 전송해 주는 원시적인 프로토콜
			case PT_LOGIN_CS:
				PROC_PT_LOGIN_CS(pConnectedSession, dwProtocol, Packet, dwPacketLength);
				break;
			case PT_SIGN_UP_CS:
				PROC_PT_SIGN_UP_CS(pConnectedSession, dwProtocol, Packet, dwPacketLength);
				break;
			//행성진입
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

	
	//나 중 에 해 야 할 곳 
	//나 중 에 해 야 할 곳 
	//나 중 에 해 야 할 곳 
	//나 중 에 해 야 할 곳 
	//나 중 에 해 야 할 곳 
	//나 중 에 해 야 할 곳 
	//나 중 에 해 야 할 곳 

	//나 중 에 해 야 할 곳 
}

VOID CServerIocp::OnIoProcDB(VOID* pObject) {
	int ret = 0 ;
	DB_ST* pDBST = reinterpret_cast<DB_ST*>(pObject);
	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };
	CConnectedSession* pSession = reinterpret_cast<CConnectedSession*>(pDBST->pSession);
	//해서 얻어온 플레이어 객체에게 결과를 통보

	switch (pDBST->etype) {
	case LOADID:
		if (pSession->GetDBevent() == LOADID) // 만약 로그인 요청이였다면
		{
			if (wcscmp(pDBST->idpw.ID, pSession->GetID()) != 0)
				ret++;
			if (wcscmp(pDBST->idpw.PW, pSession->GetPW()) != 0)
				ret++;
			if (true == m_oConnectedSessionManager.IsThisIDLogin(pDBST->idpw.PW))
				ret = -1;

			if (ret == 0) { // 로그인 성공
				pSession->WritePacket(PT_LOGIN_SERVER_SUC, Packet, WRITE_PT_LOGIN_SERVER_SUC(Packet));

				// 로긴 성공하면 방 목록 정보를 보낸다
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
		else if (pSession->GetDBevent() == SIGNUP) // 원래 회원가입 요청이였다면
		{
			if (wcscmp(pDBST->idpw.ID, pSession->GetID()) == 0)
				ret++;

			if (ret == 0) {
				// DB 회원가입 요청
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
		//타입을 알았으니 해당 타입으로 형변환
		//CConnectedSession* pSession = reinterpret_cast<CConnectedSession*>(pObject);
		//해서 얻어온 플레이어 객체에게 결과를 통보
		//std::cout << pCmp->x << ", " << pCmp->y << std::endl;;

}
BOOL CServerIocp::Begin(VOID)
{
	// 상속 받은 IOCP 개체를 시작합니다.
	if (!CIocp::Begin()) return FALSE;

	// Listen에 사용할 개체를 생성합니다.
	m_pListen = new CNetworkSession();

	// 개체를 시작합니다.
	if (!m_pListen->Begin())
	{
		// 실패했을 경우 End함수를 호출하고 종료합니다.
		CServerIocp::End();

		return FALSE;
	}

	// TCP로 사용할 것을 선언합니다.
	if (!m_pListen->TcpBind())
	{
		// 실패했을 경우 End함수를 호출하고 종료합니다.
		CServerIocp::End();

		return FALSE;
	}

	// 포트 9595으로 Listen을 하고 최대 100명으로 설정합니다.
	
	if (!m_pListen->Listen(DEFAULT_PORT, MAX_USER))
	{
		// 실패했을 경우 End함수를 호출하고 종료합니다.
		CServerIocp::End();

		return FALSE;
	}

	// IOCP에 Listen 소켓을 등록시켜 줍니다. 그리고 키로는 해당 개체의 포인터를 설정합니다.
	if (!CIocp::RegisterSocketToIocp(m_pListen->GetSocket(), reinterpret_cast<ULONG_PTR>(m_pListen)))
	{
		// 실패했을 경우 End함수를 호출하고 종료합니다.
		CServerIocp::End();

		return FALSE;
	}

	// CConnectedSessionManager를 시작합니다.
	// 시작 함수내에는 CConnectedSession을 생성하고 Accept상태로 만드는 코드가 추가되어 있습니다.
	if (!m_oConnectedSessionManager.Begin(m_pListen->GetSocket()))
	{
		CServerIocp::End();

		return FALSE;
	}

	// KeepAlive 종료 이벤트를 생성합니다.
	m_hKeepThreadDestroyEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (!m_hKeepThreadDestroyEvent)
	{ 
		// 실패했을경우 종료합니다.
		CServerIocp::End(); 
		return FALSE; 
	}

	// KeepAlive Thread를 생성합니다.
	m_hKeepThread = CreateThread(NULL, 0, ::KeepThreadCallback, this, 0, NULL);
	if (!m_hKeepThread) 
	{ 
		// 생성 실패했을 경우 종료합니다.
		CServerIocp::End(); 
		return FALSE; 
	}
	
	////메인 루프 스레드 헨들 생성
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
	// CServerIocp를 종료할때

	//ServerMain종료
	m_bIsRun = FALSE;

	// m_mUser 삭제

	// m_hKeepThread가 NULL이 아니면 KeepAlive Thread를 종료해 줍니다.
	if (m_hKeepThread)
	{
		// 종료 이벤트를 발생시킵니다.
		SetEvent(m_hKeepThreadDestroyEvent);

		// Thread가 종료될 때까지 대기합니다.
		WaitForSingleObject(m_hKeepThread, INFINITE);

		// 핸들값을 닫아줍니다.
		CloseHandle(m_hKeepThread);
		m_hKeepThread = NULL;
	}

	// KeepAlive 종료 이벤트가 NULL이 아니면
	if (m_hKeepThreadDestroyEvent)
	{
		// 이벤트를 닫아줍니다.
		CloseHandle(m_hKeepThreadDestroyEvent);
		m_hKeepThreadDestroyEvent = NULL;
	}
	
	//
//	if (m_ServerMainStartupEventHandle)
//		CloseHandle(m_ServerMainStartupEventHandle);


	//타이머 쓰레드 종료 검사
	//m_pTimerThread->join();

	// IOCP를 종료합니다.
	CIocp::End();
	m_DataBase.End();
	m_RoomManager.End();
	// CConnectedSessionManager를 종료합니다.
	m_oConnectedSessionManager.End();

	// 생성했던 Listen용 개체를 종료하고 삭제해 줍니다.
	if (m_pListen)
	{
		m_pListen->End();

		delete m_pListen;
	}

	//ServerMain이 종료하기를 기다림
	//WaitForSingleObject(m_ServerMainEndEventHandle, INFINITE);
	//if (m_ServerMainEndEventHandle)
	//	CloseHandle(m_ServerMainEndEventHandle);
}



//커멘트 리스트 함수
void CServerIocp::AddCommand(stCOMMAND stCmd){
	//커멘드를 시간순으로 작은애가 앞에 오도록 정렬해서 넣는다.
	//int i = 0;
	lock();
	//m_lCommand.push_back(stCmd);
	//unlock();
	//
	//return;
	if (0 == m_lCommand.size()){
		//명령이 없으면 그냥 집어넣음
		m_lCommand.push_back(stCmd);
		unlock();
		return;
	}

	auto i = m_lCommand.begin();
	if (i->active_time > stCmd.active_time){
		//제일 처음보다 작으면 맨앞에 넣음
		m_lCommand.push_front(stCmd);
		unlock();
		return;
	}
	for (i; i != m_lCommand.end(); ++i) {


		if (i->active_time <= stCmd.active_time) {
			//커지는 그 순간 삽입
			// a가 b보다 클때 삽입
			m_lCommand.insert(i, stCmd);
			break;
		}

	}

	unlock();

}
stCOMMAND CServerIocp::GetCommand(){
	//처음 값을 복사해서 
	lock();
	stCOMMAND return_value = *m_lCommand.begin();
	unlock();

	return return_value;
}
void CServerIocp::PopCommand(){
	lock();
	//처음 명령을 삭제
	m_lCommand.erase(m_lCommand.begin());
	unlock();
}
//커멘트 리스트 함수