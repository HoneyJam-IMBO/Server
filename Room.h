#pragma once
#include "ConnectedSession.h"
#include "Boss.h"

class CRoom {
public:
	//플레이어 접속
	void AddPlayer(CConnectedSession* pSession);
	int RemovePlayer(INT SLOT_ID);
	bool CreateRoom(CConnectedSession* pReader);

	bool WriteAll(DWORD protocol, BYTE* packet, DWORD packetLength);
	bool WriteAllExceptMe(INT SLOT_ID, DWORD protocol, BYTE* packet, DWORD packetLength);
	
	
	int GetPlayerNum() { return m_CurPlayerNum; }
	void SetRoomID(int RoomNum) { m_RoomNum = RoomNum; }
	int GetRoomID() { return m_RoomNum; }
	CConnectedSession** GetPlayers() { return m_ppConnectedSession; }

	int GetLoadingComplateNum() { return m_LoadingComplateNum; }
	void SetLoadingComplateNum(int n) { m_LoadingComplateNum = n; }

	CBoss* GetpBoss() { return m_pBoss; }

private:
	CConnectedSession** m_ppConnectedSession{ nullptr };
	int m_RoomNum{ 0 };
	int m_CurPlayerNum{ 0 };
	int m_LoadingComplateNum{ 0 };
	CBoss* m_pBoss;
public:
	CRoom(int nRoomNum);
	~CRoom();
};