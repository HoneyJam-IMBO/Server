#include "stdafx.h"
#include "RoomManager.h"
#include "Room.h"

CRoomManager::CRoomManager()
{
}

CRoomManager::~CRoomManager()
{
}

BOOL CRoomManager::Begin() {
	
	return true;
}

VOID CRoomManager::End() {

	for (auto v : m_vRoomsList) 
		delete v;
	
	m_vRoomsList.clear();

}

bool CRoomManager::Create(CConnectedSession * pReader)
{
	CThreadSync Sync;

	std::cout << "Create Room :" << m_iRoomNum << std::endl;

	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };
	pReader->WritePacket(PT_ROOM_CREATE_SC, Packet, WRITE_PT_ROOM_CREATE_SC(Packet, m_iRoomNum));

	CRoom* NewRoom = new CRoom(m_iRoomNum++);
	m_vRoomsList.push_back(NewRoom);
	m_iRoomCount++;
	NewRoom->AddPlayer(pReader);

	return true;
}

bool CRoomManager::Join(CConnectedSession * pSession, int Room_ID)
{
	CThreadSync Sync;
	if (nullptr == GetRoomInfoRoomID(Room_ID))
		return false;
	GetRoomInfoRoomID(Room_ID)->AddPlayer(pSession);
	return true;
}

bool CRoomManager::Leave(int Room_ID, int Slot_ID)
{
	CThreadSync Sync;
	for (auto iter = m_vRoomsList.begin(); iter != m_vRoomsList.end(); ++iter) {
		if ((*iter)->GetRoomID() == Room_ID) {
			if ((*iter)->RemovePlayer(Slot_ID) == 0) {
				delete *iter;
				m_vRoomsList.erase(iter);
				m_iRoomCount--;
			}
		}
	}
	return true;
}


