#pragma once

//#include "ServerMain.h"
#include <thread>
#include <mutex>
#include "Room.h"
#include "RoomManager.h"

// CIocp�� ��� �޽��ϴ�.
class CServerIocp : public CIocp
{
public:
	CServerIocp(VOID);
	virtual ~CServerIocp(VOID);


	//���� ���� ���� ����
	BOOL BeginServerMain();

	// ��ü�� �ʱ�ȭ �ϰ� �����ϱ� ���� �Լ�
	BOOL Begin(VOID);
	
	// ��ü�� �����ϱ� ���� �Լ�
	VOID End(VOID);

	// KeepAlive Thread Callback �Լ�
	VOID KeepThreadCallback(VOID);


	//servermain thread callback �Լ�
	//VOID ServerMainThreadCallback(VOID);

	//manager geter
	CConnectedSessionManager* GetManager() { return &m_oConnectedSessionManager; }

	//ai ���� �Լ�
	//Ÿ�̸� �ݺ� �Լ�
	VOID TimerThreadCallback();

	bool GetIsRun(){ return m_bIsRun; }


	//Ŀ��� ����Ʈ �Լ�
	void AddCommand(stCOMMAND stCmd);
	stCOMMAND CServerIocp::GetCommand();
	void PopCommand();
	//Ŀ��� ����Ʈ �Լ�

	//lock
	void lock(){ m_Sync.lock(); }
	void unlock(){ m_Sync.unlock(); }
	//ai ���� �Լ�
protected:
	// CIocp ��� �����Լ����� �缱�� �մϴ�.
	VOID OnIoRead(VOID *pObject, DWORD dwDataLength);
	VOID OnIoWrote(VOID *pObject, DWORD dwDataLength);
	VOID OnIoConnected(VOID *pObject);
	VOID OnIoDisconnected(VOID *pObject);

	//aió�� �ݹ� �Լ�
	VOID OnIoProcAI(VOID* pObject);
	//aió�� �ݹ� �Լ�
private:
	//CRoom* m_pRoom{ nullptr };
	//aió�� ����
	//Ÿ�̸� ������
	std::thread* m_pTimerThread;

	//��ɾ� ť
	std::list<stCOMMAND> m_lCommand;

	//lock
	std::mutex m_Sync;
	//aió�� ����

	//servermain�� ����� ���´�.
	//ServerMain* m_pServerMain;
	//HANDLE m_ServerMainStartupEventHandle;
	//HANDLE m_ServerMainEndEventHandle;
	bool m_bIsRun;
	// ������ Listen�� ����� ��ü
	CNetworkSession *m_pListen;
	CConnectedSessionManager m_oConnectedSessionManager;
	CRoomManager m_RoomManager;
	// KeepAlive Thread�� �����ϴ� �ڵ鰪
	HANDLE m_hKeepThread;
	// KeepAlive Thread�� �����Ҷ� ����ϴ� �̺�Ʈ
	HANDLE m_hKeepThreadDestroyEvent;

private:
	// ��Ŷ ó���� �� �Լ���
	VOID PROC_PT_LOGIN_CS(CConnectedSession *pConnectedSession, DWORD dwProtocol, BYTE *pPacket, DWORD dwPacketLength);//�α��� ��û ó��

	//�༺ ���� 
	VOID PROC_PT_ENTER_EARTH_CS(CConnectedSession *pConnectedSession, DWORD dwProtocol, BYTE *pPacket, DWORD dwPacketLength);//�α��� ��û ó��


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
