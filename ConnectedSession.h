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
	VOID SetID(wchar_t * ID) { wcscpy(myID, ID); }
	wchar_t* GetID() { return myID; }
	VOID SetPW(wchar_t * PW) { wcscpy(myPW, PW); }
	wchar_t* GetPW() { return myPW; }
	VOID SetDBevent(DBEVENT etype) { m_DBetype = etype; }
	DBEVENT GetDBevent() { return m_DBetype; }
	//초기 단계 플레이어 함수들, 나중에 수정 요함

	//CRoom* GetRoomInfo() { return m_pRoom; }
	CGameObject* GetPlayer() { return m_pPlayer; }
	void CreatePlayer();
	//초기 단계 플레이어 함수들, 나중에 수정 요함
private:
	//CRoom* m_pRoom;
	wchar_t myID[10];
	wchar_t myPW[10];
	DBEVENT m_DBetype;
	// 접속되었는지 판별하는 변수
	BOOL m_bConnected;
	CGameObject* m_pPlayer;
};
