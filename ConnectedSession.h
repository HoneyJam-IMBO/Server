#pragma once
//#include "Player.h"

class CGameObject;
class CRoom;
// CPacketSession�� ��ӹ��� CConnectedSession
class CConnectedSession : public CPacketSession
{
public:
	CConnectedSession(VOID);
	virtual ~CConnectedSession(VOID);

	// ��ü�� �����ϰ� �ٽ� Accept���·� ������ִ� �Լ�
	// CServerIocp���� OnIoDisconnected�� �Ǿ����� ��ü�� �����ϰ� �ٽ� �ʱ�ȭ �Ҷ� ����ϰ� �˴ϴ�.
	BOOL Restart(SOCKET hListenSocket);

	// m_bConnected�� ���� �����ϰ� �������� �Լ�
	VOID SetConnected(BOOL bConnected) { CThreadSync Sync; m_bConnected = bConnected; }
	BOOL GetConnected(VOID) { CThreadSync Sync; return m_bConnected; }
	VOID SetID(wchar_t * ID) { wcscpy(myID, ID); }
	wchar_t* GetID() { return myID; }
	VOID SetPW(wchar_t * PW) { wcscpy(myPW, PW); }
	wchar_t* GetPW() { return myPW; }
	VOID SetDBevent(DBEVENT etype) { m_DBetype = etype; }
	DBEVENT GetDBevent() { return m_DBetype; }
	//�ʱ� �ܰ� �÷��̾� �Լ���, ���߿� ���� ����

	//CRoom* GetRoomInfo() { return m_pRoom; }
	CGameObject* GetPlayer() { return m_pPlayer; }
	void CreatePlayer();
	//�ʱ� �ܰ� �÷��̾� �Լ���, ���߿� ���� ����
private:
	//CRoom* m_pRoom;
	wchar_t myID[10];
	wchar_t myPW[10];
	DBEVENT m_DBetype;
	// ���ӵǾ����� �Ǻ��ϴ� ����
	BOOL m_bConnected;
	CGameObject* m_pPlayer;
};
