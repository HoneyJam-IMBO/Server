#pragma once
#include "ConnectedSession.h"

class CRoomManager : public CMultiThreadSync<CRoomManager>
{
public:
	CRoomManager();
	~CRoomManager();

	BOOL Begin();
	VOID End();

	void SetRoomCount(int RoomCount) {m_iRoomCount = RoomCount;}
	int GetRoomCount() { return m_iRoomCount; }
	std::vector<CRoom*>& GetRoomsList() { return m_vRoomsList; }
	CRoom* GetRoomInfoRoomID(int Room_ID) { 
		for (auto p : m_vRoomsList)
	{ 
		if (p->GetRoomID() == Room_ID)
			return p;
	}
	return nullptr; }
	bool Create(CConnectedSession* pReader);
	bool Join(CConnectedSession* pSession, int Room_ID);
	bool Leave(int Room_ID, int Slot_ID);
private:
	std::vector<CRoom*> m_vRoomsList;
	int					m_iRoomNum		{ 0 };
	int					m_iRoomCount	{ 0 };
};

