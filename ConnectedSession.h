#pragma once
//#include "Player.h"

class CGameObject;
class CRoom;
// CPacketSession을 상속받은 CConnectedSession
class CConnectedSession : public CPacketSession
{
public:
	CConnectedSession(VOID);
	virtual ~CConnectedSession(VOID);

	// 개체를 종료하고 다시 Accept상태로 만들어주는 함수
	// CServerIocp에서 OnIoDisconnected가 되었을때 개체를 종료하고 다시 초기화 할때 사용하게 됩니다.
	BOOL Restart(SOCKET hListenSocket);

	// m_bConnected의 값을 설정하고 가져오는 함수
	VOID SetConnected(BOOL bConnected) { CThreadSync Sync; m_bConnected = bConnected; }
	BOOL GetConnected(VOID) { CThreadSync Sync; return m_bConnected; }

	//초기 단계 플레이어 함수들, 나중에 수정 요함

	//CRoom* GetRoomInfo() { return m_pRoom; }
	CGameObject* GetPlayer() { return m_pPlayer; }
	void CreatePlayer();
	//초기 단계 플레이어 함수들, 나중에 수정 요함
private:
	//CRoom* m_pRoom;
	// 접속되었는지 판별하는 변수
	BOOL m_bConnected;
	CGameObject* m_pPlayer;
};
