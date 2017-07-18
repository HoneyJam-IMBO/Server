#pragma once

//#include "ServerMain.h"
#include <thread>
#include <mutex>
#include "Room.h"
#include "RoomManager.h"

// CIocp를 상속 받습니다.
class CServerIocp : public CIocp
{
public:
	CServerIocp(VOID);
	virtual ~CServerIocp(VOID);


	//서버 메인 루프 시작
	BOOL BeginServerMain();

	// 개체를 초기화 하고 시작하기 위한 함수
	BOOL Begin(VOID);
	
	// 개체를 종료하기 위한 함수
	VOID End(VOID);

	// KeepAlive Thread Callback 함수
	VOID KeepThreadCallback(VOID);


	//servermain thread callback 함수
	//VOID ServerMainThreadCallback(VOID);

	//manager geter
	CConnectedSessionManager* GetManager() { return &m_oConnectedSessionManager; }

	//ai 관련 함수
	//타이머 콜벡 함수
	VOID TimerThreadCallback();

	bool GetIsRun(){ return m_bIsRun; }


	//커멘드 리스트 함수
	void AddCommand(stCOMMAND stCmd);
	stCOMMAND CServerIocp::GetCommand();
	void PopCommand();
	//커멘드 리스트 함수

	//lock
	void lock(){ m_Sync.lock(); }
	void unlock(){ m_Sync.unlock(); }
	//ai 관련 함수
protected:
	// CIocp 상속 가상함수들을 재선언 합니다.
	VOID OnIoRead(VOID *pObject, DWORD dwDataLength);
	VOID OnIoWrote(VOID *pObject, DWORD dwDataLength);
	VOID OnIoConnected(VOID *pObject);
	VOID OnIoDisconnected(VOID *pObject);

	//ai처리 콜백 함수
	VOID OnIoProcAI(VOID* pObject);
	//ai처리 콜백 함수
private:
	//CRoom* m_pRoom{ nullptr };
	//ai처리 변수
	//타이머 스레드
	std::thread* m_pTimerThread;

	//명령어 큐
	std::list<stCOMMAND> m_lCommand;

	//lock
	std::mutex m_Sync;
	//ai처리 변수

	//servermain을 멤버로 갖는다.
	//ServerMain* m_pServerMain;
	//HANDLE m_ServerMainStartupEventHandle;
	//HANDLE m_ServerMainEndEventHandle;
	bool m_bIsRun;
	// 서버의 Listen을 담당할 개체
	CNetworkSession *m_pListen;
	CConnectedSessionManager m_oConnectedSessionManager;
	CRoomManager m_RoomManager;
	// KeepAlive Thread를 관리하는 핸들값
	HANDLE m_hKeepThread;
	// KeepAlive Thread를 종료할때 사용하는 이벤트
	HANDLE m_hKeepThreadDestroyEvent;

private:
	// 패킷 처리를 할 함수들
	VOID PROC_PT_LOGIN_CS(CConnectedSession *pConnectedSession, DWORD dwProtocol, BYTE *pPacket, DWORD dwPacketLength);//로그인 요청 처리

	//행성 진입 
	VOID PROC_PT_ENTER_EARTH_CS(CConnectedSession *pConnectedSession, DWORD dwProtocol, BYTE *pPacket, DWORD dwPacketLength);//로그인 요청 처리


	VOID PROC_PT_FREQUENCY_MOVE_CS(CConnectedSession *pConnectedSession, DWORD dwProtocol, BYTE *pPacket, DWORD dwPacketLength);
	VOID PROC_PT_MOUSE_LEFT_ATTACK_CS(CConnectedSession * pConnectedSession, DWORD dwProtocol, BYTE * pPacket, DWORD dwPacketLength);
	VOID PROC_PT_KEY_INPUT_CS(CConnectedSession *pConnectedSession, DWORD dwProtocol, BYTE *pPacket, DWORD dwPacketLength);
	VOID PROC_PT_MOUSE_INPUT_CS(CConnectedSession *pConnectedSession, DWORD dwProtocol, BYTE *pPacket, DWORD dwPacketLength);
	VOID PROC_PT_MOUSE_BUTTON_INPUT_CS(CConnectedSession *pConnectedSession, DWORD dwProtocol, BYTE *pPacket, DWORD dwPacketLength);
	VOID PROC_PT_ROOM_CREATE_CS(CConnectedSession *pConnectedSession, DWORD dwProtocol, BYTE *pPacket, DWORD dwPacketLength);
	VOID PROC_PT_ROOM_DATA_CHANGE_CS(CConnectedSession *pConnectedSession, DWORD dwProtocol, BYTE *pPacket, DWORD dwPacketLength);
	VOID PROC_PT_ROOM_JOIN_CS(CConnectedSession *pConnectedSession, DWORD dwProtocol, BYTE *pPacket, DWORD dwPacketLength);
	VOID PROC_PT_FTOWN_READY_CS(CConnectedSession *pConnectedSession, DWORD dwProtocol, BYTE *pPacket, DWORD dwPacketLength);
};
