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

	//�ʱ� �ܰ� �÷��̾� �Լ���, ���߿� ���� ����

	//CRoom* GetRoomInfo() { return m_pRoom; }
	CGameObject* GetPlayer() { return m_pPlayer; }
	void CreatePlayer();
	//�ʱ� �ܰ� �÷��̾� �Լ���, ���߿� ���� ����
private:
	//CRoom* m_pRoom;
	// ���ӵǾ����� �Ǻ��ϴ� ����
	BOOL m_bConnected;
	CGameObject* m_pPlayer;
};
