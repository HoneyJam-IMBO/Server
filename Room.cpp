#include "stdafx.h"
#include "Room.h"

void CRoom::AddPlayer(CConnectedSession * pSession){
	if (m_CurPlayerNum >= 4) return;
	// 풀방시 입장 실패 전송해야댐

	m_ppConnectedSession[m_CurPlayerNum] = pSession;
	pSession->GetPlayer()->SetSLOT_ID(m_CurPlayerNum);
	pSession->GetPlayer()->SetROOM_ID(m_RoomNum);
	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };

	std::cout << "ROOM JIN SCC : " << pSession->GetPlayer()->GetSLOT_ID() << " SLOT_COUNT : " << m_CurPlayerNum + 1 << std::endl;
	pSession->WritePacket(PT_ROOM_JOIN_SCC_SC, Packet, WRITE_PT_ROOM_JOIN_SCC_SC(Packet,
		pSession->GetPlayer()->GetSLOT_ID(), (m_CurPlayerNum+1)));

	std::cout << "AddPlayer : " << m_RoomNum << " " << m_CurPlayerNum << std::endl;

	int slot_id = pSession->GetPlayer()->GetSLOT_ID();
	int characterIndex = pSession->GetPlayer()->GetCHARACTER();
	bool bReady = pSession->GetPlayer()->GetREADY();

	for (int i = 0; i < m_CurPlayerNum; ++i) {
		
		int other_slot_id = m_ppConnectedSession[i]->GetPlayer()->GetSLOT_ID();
		int other_characterIndex = m_ppConnectedSession[i]->GetPlayer()->GetCHARACTER();
		bool other_bReady = m_ppConnectedSession[i]->GetPlayer()->GetREADY();

		std::cout << "Room Join SC : " << bReady << " " << slot_id << " " << characterIndex << std::endl;
		pSession->WritePacket(PT_ROOM_JOIN_SC, Packet, WRITE_PT_ROOM_JOIN_SC(Packet,
			other_slot_id/*slot id*/, other_bReady, other_characterIndex/*kind of char*/));

		
		m_ppConnectedSession[i]->WritePacket(PT_ROOM_JOIN_SC, Packet, WRITE_PT_ROOM_JOIN_SC(Packet,
			slot_id/*slot id*/, bReady, characterIndex/*kind of char*/));

	}


	m_CurPlayerNum++;
}

int CRoom::RemovePlayer(INT SLOT_ID){
	for (int i = 0; i < m_CurPlayerNum; ++i) {
		if (SLOT_ID == i) {
			//exchange
			m_CurPlayerNum--;
			
			BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };

			m_ppConnectedSession[i] = m_ppConnectedSession[m_CurPlayerNum];//마지막꺼 해당 슬롯에 넣어줌
			m_ppConnectedSession[i]->GetPlayer()->SetSLOT_ID(i);
			m_ppConnectedSession[i]->WritePacket(PT_CHANGE_SLOTID_SC, Packet, WRITE_PT_CHANGE_SLOTID_SC(Packet, i));
			//exchange

			//예외처리
			for (int i = 0; i < m_CurPlayerNum; ++i) {
				m_ppConnectedSession[i]->WritePacket(PT_ROOM_OUT_SC, Packet, WRITE_PT_ROOM_OUT_SC(Packet,
					m_CurPlayerNum));
			}


			if (m_CurPlayerNum == 1) {
				int slot_id = m_ppConnectedSession[0]->GetPlayer()->GetSLOT_ID();
				int characterIndex = m_ppConnectedSession[0]->GetPlayer()->GetCHARACTER();
				bool bReady = m_ppConnectedSession[0]->GetPlayer()->GetREADY();

				BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };
				m_ppConnectedSession[0]->WritePacket(PT_ROOM_JOIN_SC, Packet, WRITE_PT_ROOM_JOIN_SC(Packet,
					0/*slot id*/, bReady, characterIndex/*kind of char*/));

			}
			if (m_CurPlayerNum < 1) {//player 아무도 없으면 방 지움
				m_CurPlayerNum = 0;
				m_LoadingComplateNum = 0;
				//delete this;
				return 0;
			}
			

			for (int j = 0; j < m_CurPlayerNum; ++j) {//바뀐 정보 모든 애들에게 뿌려줌
				for (int k = 0; k < m_CurPlayerNum; ++k) {

					int slot_id = m_ppConnectedSession[k]->GetPlayer()->GetSLOT_ID();
					int characterIndex = m_ppConnectedSession[k]->GetPlayer()->GetCHARACTER();
					bool bReady = m_ppConnectedSession[k]->GetPlayer()->GetREADY();
					std::cout << "Room Join SC : " << bReady << " " << slot_id << " " << characterIndex << std::endl;
					m_ppConnectedSession[j]->WritePacket(PT_ROOM_JOIN_SC, Packet, WRITE_PT_ROOM_JOIN_SC(Packet,
						slot_id/*slot id*/, bReady, characterIndex/*kind of char*/));
				}
			}
			return 1;
		}
	}

}

bool CRoom::WriteAll(DWORD protocol, BYTE * packet, DWORD packetLength){
	//std::cout << "WriteAll : "<< std::endl;

	for (int i = 0; i < m_CurPlayerNum; ++i) {
		m_ppConnectedSession[i]->WritePacket(protocol, packet, packetLength);
	}
	return true;
}

bool CRoom::WriteAllExceptMe(INT SLOT_ID, DWORD protocol, BYTE * packet, DWORD packetLength){
	//std::cout << "WriteAllExceptMe : "<< std::endl;

	for (int i = 0; i < m_CurPlayerNum; ++i) {
		if (i == SLOT_ID) continue;
		m_ppConnectedSession[i]->WritePacket(protocol, packet, packetLength);
	}
	return true;
}

bool CRoom::CreateRoom(CConnectedSession * pReader){
	//BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };//나중에 room manager 만들어야함
	//INT ROOM_ID = 0;

	//std::cout << "Create Room :" << ROOM_ID << std::endl;

	//pReader->WritePacket(PT_ROOM_CREATE_SC, Packet, WRITE_PT_ROOM_CREATE_SC(Packet, ROOM_ID));
	//AddPlayer(pReader);
	return true;
}

CRoom::CRoom(int nRoomNum){
	m_RoomNum = nRoomNum;

	m_CurPlayerNum = 0;
	m_LoadingComplateNum = 0;

	m_ppConnectedSession = new CConnectedSession*[4];

	m_pBoss->begin(10000);
}

CRoom::~CRoom(){
	delete[] m_ppConnectedSession;
}
