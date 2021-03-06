// 패킷 처리를 위해서 새로 작성한 ProcProtocol.cpp
#include "stdafx.h"
#include "ServerIocp.h"

#define READ_PACKET(PROTOCOL)\
	BYTE WriteBuffer[MAX_BUFFER_LENGTH] = {0, };\
	S_##PROTOCOL Data;\
	READ_##PROTOCOL(pPacket, Data);


//0606
//여기 전부 나중에
//0606

VOID CServerIocp::PROC_PT_TEMP(CConnectedSession *pConnectedSession, DWORD dwProtocol, BYTE *pPacket, DWORD dwPacketLength)
{
	
	//printf("temp\n");

}
VOID CServerIocp::PROC_PT_LOGIN_CS(CConnectedSession *pConnectedSession, DWORD dwProtocol, BYTE *pPacket, DWORD dwPacketLength)
{
	// 전처리 함수로 간략화
	READ_PACKET(PT_LOGIN_CS);

	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };

	pConnectedSession->SetID(Data.ID);
	pConnectedSession->SetPW(Data.PW);
	pConnectedSession->SetDBevent(LOADID);


	
	stDBQUEUE dbQueueData;
	dbQueueData.etype = LOADID;
	dbQueueData.pSession = pConnectedSession;
	wsprintf(dbQueueData.ExecCode, L"EXEC dbo.ID_Check_SP2 %s", Data.ID);

	m_DataBase.pushDBEvent(dbQueueData);

	// DataBase 유저데이터 불러오기
	//idpw = m_DataBase.LoadUserInfo(recv_id);



}

VOID CServerIocp::PROC_PT_SIGN_UP_CS(CConnectedSession *pConnectedSession, DWORD dwProtocol, BYTE *pPacket, DWORD dwPacketLength)
{
	// 전처리 함수로 간략화
	READ_PACKET(PT_SIGN_UP_CS);

	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };

	pConnectedSession->SetID(Data.ID);
	pConnectedSession->SetPW(Data.PW);
	pConnectedSession->SetDBevent(SIGNUP);

	S_IDPW idpw;
	wcscpy(idpw.ID, Data.ID);
	wcscpy(idpw.PW, Data.PW);

	stDBQUEUE dbQueueData;
	dbQueueData.etype = LOADID;
	dbQueueData.pSession = pConnectedSession;
	wsprintf(dbQueueData.ExecCode, L"EXEC dbo.ID_Check_SP2 %s", Data.ID);

	m_DataBase.pushDBEvent(dbQueueData);

	

}

///////////////////////행서엉진입
VOID CServerIocp::PROC_PT_ENTER_EARTH_CS(CConnectedSession *pConnectedSession, DWORD dwProtocol, BYTE *pPacket, DWORD dwPacketLength) {
	// 전처리 함수로 간략화
	READ_PACKET(PT_ENTER_EARTH_CS);

	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };

	//이제 ID부여해야함 
	//특정 조건을 만족하면 진입 허가
	pConnectedSession->CreatePlayer();
	//지역 관리자에게 플레이어 AddPlayer해줘서 넣어줌 

	//CPlayer* pPlayer = pConnectedSession->GetPlayer();
	//if (m_pServerMain->GetObjectManager()->AddPlayer(pConnectedSession)) {
	//	//AddPlayer가 성공하면, 즉 게임에 들어갔다면 
	//	//성공 을 보내줌 지금은 그냥 성공임
	//
	//	XMFLOAT3 xmfPos;
	//	XMStoreFloat3(&xmfPos, pPlayer->GetPlayerPosition());
	//	//team, 내 위치 보내줌
	//	pConnectedSession->WritePacket(PT_ENTER_EARTH_SUC, Packet, WRITE_PT_ENTER_EARTH_SUC(Packet, 
	//		pPlayer->GetID(), pPlayer->GetTeam(), xmfPos.x, xmfPos.y, xmfPos.z));
	//
	//}
	//else {
	//	pConnectedSession->WritePacket(PT_ENTER_EARTH_FAIL, Packet, WRITE_PT_ENTER_EARTH_FAIL(Packet));
	//
	//}
}
// 사용자 등록 프로토콜 처리
VOID CServerIocp::PROC_PT_FREQUENCY_MOVE_CS(CConnectedSession *pConnectedSession, DWORD dwProtocol, BYTE *pPacket, DWORD dwPacketLength)
{

	// 전처리 함수로 간략화
	READ_PACKET(PT_FREQUENCY_MOVE_CS);
	// 실제 코드
	
	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };

	m_RoomManager.GetRoomInfoRoomID(pConnectedSession->GetPlayer()->GetROOM_ID())->WriteAllExceptMe(pConnectedSession->GetPlayer()->GetSLOT_ID(), PT_FREQUENCY_MOVE_SC, Packet, WRITE_PT_FREQUENCY_MOVE_SC(Packet,
		pConnectedSession->GetPlayer()->GetSLOT_ID(), Data.POSX, Data.POSY, Data.POSZ, Data.ANGLEY, Data.ANIMNUM));


}
VOID CServerIocp::PROC_PT_BOSS_FREQUENCY_MOVE_CS(CConnectedSession *pConnectedSession, DWORD dwProtocol, BYTE *pPacket, DWORD dwPacketLength)
{

	// 전처리 함수로 간략화
	READ_PACKET(PT_BOSS_FREQUENCY_MOVE_CS);
	// 실제 코드

	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };

	m_RoomManager.GetRoomInfoRoomID(pConnectedSession->GetPlayer()->GetROOM_ID())->WriteAllExceptMe(pConnectedSession->GetPlayer()->GetSLOT_ID(), PT_BOSS_FREQUENCY_MOVE_SC, Packet, WRITE_PT_BOSS_FREQUENCY_MOVE_SC(Packet, Data.POSX, Data.POSY, Data.POSZ, Data.ANGLEY, Data.ANIMNUM));

	//cout << "BOSS FREQ ANIM NUM : " << Data.ANIMNUM << endl;

}
VOID CServerIocp::PROC_PT_MOUSE_LEFT_ATTACK_CS(CConnectedSession *pConnectedSession, DWORD dwProtocol, BYTE *pPacket, DWORD dwPacketLength)
{
	//플레이어의 지역이 아직 설정 안되있으면 return;
	//if (nullptr == pConnectedSession->GetPlayer()->GetRegion()) return;


	// 전처리 함수로 간략화
	READ_PACKET(PT_MOUSE_LEFT_ATTACK_CS);
	// 실제 코드
	
	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };

	INT SLOT_ID = pConnectedSession->GetPlayer()->GetSLOT_ID();
	bool bAttack = Data.ATTACK;
	//std::cout << dwDirection << ' '<<"ANGLEY -" << fAngleY << std::endl;

	INT ROOM_ID = pConnectedSession->GetPlayer()->GetROOM_ID();

	//m_pRoom->WriteAll(PT_FREQUENCY_MOVE_SC, Packet, WRITE_PT_FREQUENCY_MOVE_SC(Packet,
	//	SLOT_ID, dwDirection, fAngleY));

	m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->WriteAllExceptMe(SLOT_ID, PT_MOUSE_LEFT_ATTACK_SC, Packet, WRITE_PT_MOUSE_LEFT_ATTACK_SC(Packet,
		SLOT_ID, bAttack));

	//std::cout << SLOT_ID << "Player Attack!" << std::endl;
	//위치 동기화
	//pPlayer->SetPlayerPosition(XMLoadFloat3(&xmfPos));

	////충돌체크

	////브로드 캐스트
	//pPlayer->GetRegion()->WriteAll(PT_FREQUENCY_MOVE_SC, Packet,
	//	WRITE_PT_FREQUENCY_MOVE_SC(Packet, PLAYER, 
	//		pPlayer->GetID(), xmfPos.x, xmfPos.y, xmfPos.z));

}


VOID CServerIocp::PROC_PT_KEY_INPUT_CS(CConnectedSession *pConnectedSession, DWORD dwProtocol, BYTE *pPacket, DWORD dwPacketLength)
{
//	//플레이어의 지역이 아직 설정 안되있으면 return;
//	if (nullptr == pConnectedSession->GetPlayer()->GetRegion()) return;
//
//	// 전처리 함수로 간략화
//	READ_PACKET(PT_KEY_INPUT_CS);
//
//	CPlayer* pPlayer = pConnectedSession->GetPlayer();
//	XMFLOAT3 xmfPos;
//	xmfPos.x = Data.X;
//	xmfPos.y = Data.Y;
//	xmfPos.z = Data.Z;
//	
//	pPlayer->SetPlayerPosition(XMLoadFloat3(&xmfPos));
//	
//	
//	XMStoreFloat3(&xmfPos, pConnectedSession->GetPlayer()->GetPlayerPosition());
//	
//	pPlayer->SetdwDirection(Data.DIRECTION);
//
//	//패킷을 처리한 후 
//	//플레이어가 있는 공간의 모든 플레이어에게
//
//	//브로드 캐스트
//	pPlayer->GetRegion()->WriteAll(PT_KEY_INPUT_ALL_SC, pPacket, WRITE_PT_KEY_INPUT_ALL_SC(pPacket,
//		pPlayer->GetID(), pPlayer->GetdwDirection(), Data.X, Data.Y, Data.Z));
//

}


VOID CServerIocp::PROC_PT_MOUSE_INPUT_CS(CConnectedSession *pConnectedSession, DWORD dwProtocol, BYTE *pPacket, DWORD dwPacketLength)
{
	////플레이어의 지역이 아직 설정 안되있으면 return;
	//if (nullptr == pConnectedSession->GetPlayer()->GetRegion()) return;
	//
	//// 전처리 함수로 간략화
	//READ_PACKET(PT_MOUSE_INPUT_CS);
	//// 실제 코드
	//
	//CPlayer* pPlayer = pConnectedSession->GetPlayer();
	//
	////서버 test 하기 위한 마우스 인풋 통일 + 서버에서 승인받은 정보로 Rotate해줄 꺼다
	//if (M_RBUTTON == Data.MOUSEBUTTON)
	//	pPlayer->Rotate(Data.CYDELTA, 0.0f, -Data.CXDELTA);
	//else 
	//	pPlayer->Rotate(Data.CYDELTA, Data.CXDELTA, 0.0f);
	//
	////브로드 캐스트
	//pPlayer->GetRegion()->WriteAll(PT_MOUSE_INPUT_ALL_SC, pPacket, WRITE_PT_MOUSE_INPUT_ALL_SC(pPacket,
	//	pPlayer->GetID(), Data.CXDELTA, Data.CYDELTA, Data.MOUSEBUTTON));

}


VOID CServerIocp::PROC_PT_MOUSE_BUTTON_INPUT_CS(CConnectedSession *pConnectedSession, DWORD dwProtocol, BYTE *pPacket, DWORD dwPacketLength)
{
	////플레이어의 지역이 아직 설정 안되있으면 return;
	//if (nullptr == pConnectedSession->GetPlayer()->GetRegion()) return;
	//
	//// 전처리 함수로 간략화
	//READ_PACKET(PT_MOUSE_BUTTON_INPUT_CS);
	//// 실제 코드
	//
	//CPlayer* pPlayer = pConnectedSession->GetPlayer();
	//
	////해당 플레이어의 마우스 버튼값 설정 
	//pPlayer->SetdwMouseButton(Data.MOUSEBUTTON);
	//
	//
	////브로드 캐스트
	//pPlayer->GetRegion()->WriteAll(PT_MOUSE_BUTTON_INPUT_ALL_SC, pPacket, WRITE_PT_MOUSE_BUTTON_INPUT_ALL_SC(pPacket,
	//	pPlayer->GetID(), Data.MOUSEBUTTON));
	//
	////std::cout << "PT_MOUSE_BUTTON_INPUT_ALL_SC send suc" << std::endl;
	//

}



VOID CServerIocp::PROC_PT_ROOM_CREATE_CS(CConnectedSession *pConnectedSession, DWORD dwProtocol, BYTE *pPacket, DWORD dwPacketLength){
	m_RoomManager.Create(pConnectedSession);

	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };
	m_oConnectedSessionManager.WriteAll(PT_ROOM_LIST_COUNT_SC, Packet, WRITE_PT_ROOM_LIST_COUNT_SC(Packet, m_RoomManager.GetRoomCount()));

	for (int i = 0; i < m_RoomManager.GetRoomCount(); ++i) {
		ZeroMemory(Packet, MAX_BUFFER_LENGTH);
		m_oConnectedSessionManager.WriteAll(PT_ROOM_LIST_SC, Packet, WRITE_PT_ROOM_LIST_SC(Packet, m_RoomManager.GetRoomsList()[i]->GetRoomID(), m_RoomManager.GetRoomsList()[i]->GetPlayerNum()));
	}
}

VOID CServerIocp::PROC_PT_ROOM_DATA_CHANGE_CS(CConnectedSession * pConnectedSession, DWORD dwProtocol, BYTE * pPacket, DWORD dwPacketLength){
	READ_PACKET(PT_ROOM_DATA_CHANGE_CS);
	INT ROOM_ID = Data.ROOM_ID;
	INT SLOT_ID = Data.SLOT_ID;
	m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayers()[SLOT_ID]->GetPlayer()->SetREADY(Data.READY);
	for (int i = 0; i < m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayerNum(); ++i) {//방안의 전부중
		if (i == SLOT_ID) continue;//나 뺴고
		if (m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayers()[i]->GetPlayer()->GetCHARACTER() == Data.CHARACTER)//내가 고른 캐릭터 있나 검사
			Data.CHARACTER = m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayers()[SLOT_ID]->GetPlayer()->GetCHARACTER();//있으면 고른 케릭터 변경하지 않음
	}
	m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayers()[SLOT_ID]->GetPlayer()->SetCHARACTER(Data.CHARACTER);//위의 로직 돌고 나온 Data.Chr입력

	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };
	//m_pRoom->WriteAllExceptMe(SLOT_ID, PT_ROOM_DATA_CHANGE_SC, Packet, WRITE_PT_ROOM_DATA_CHANGE_SC(Packet, SLOT_ID, Data.READY, Data.CHARACTER));
	m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->WriteAll(PT_ROOM_DATA_CHANGE_SC, Packet, WRITE_PT_ROOM_DATA_CHANGE_SC(Packet, SLOT_ID, Data.READY, Data.CHARACTER));
	
	//room안의 모든 player가 ready면 시작
	int nReadyPlayer{ 0 };
	for (int i = 0; i < m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayerNum(); ++i) {
		if (m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayers()[i]->GetPlayer()->GetREADY())
			nReadyPlayer++;
	}

	if (nReadyPlayer == m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayerNum()) {//방안의 모든 사람이 ready했으면 출발
		m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->WriteAll(PT_FTOWN_START_SC, Packet, WRITE_PT_FTOWN_START_SC(Packet));

		for (int i = 0; i < m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayerNum(); ++i)
			m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayers()[i]->GetPlayer()->SetREADY(0);

	}
	//room안의 모든 player가 ready면 시작
}

VOID CServerIocp::PROC_PT_ROOM_JOIN_CS(CConnectedSession * pConnectedSession, DWORD dwProtocol, BYTE * pPacket, DWORD dwPacketLength){
	READ_PACKET(PT_ROOM_JOIN_CS);
	m_RoomManager.Join(pConnectedSession, Data.ROOM_NUM);
}

VOID CServerIocp::PROC_PT_FTOWN_READY_CS(CConnectedSession * pConnectedSession, DWORD dwProtocol, BYTE * pPacket, DWORD dwPacketLength){
	READ_PACKET(PT_FTOWN_READY_CS);
	
	m_Sync.lock();

	int LoadingComplateNum = m_RoomManager.GetRoomInfoRoomID(Data.ROOM_ID)->GetLoadingComplateNum();
	LoadingComplateNum++;
	INT ROOM_ID = Data.ROOM_ID;

	if (LoadingComplateNum == m_RoomManager.GetRoomInfoRoomID(Data.ROOM_ID)->GetPlayerNum()) {
		std::cout << "FTOWN LOADING COMP!!!!" << std::endl;
		BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };
		m_RoomManager.GetRoomInfoRoomID(Data.ROOM_ID)->WriteAll(PT_FTOWN_READY_SC, Packet, WRITE_PT_FTOWN_READY_SC(Packet));
		m_RoomManager.GetRoomInfoRoomID(Data.ROOM_ID)->SetLoadingComplateNum(0);
		for (int i = 0; i < m_RoomManager.GetRoomInfoRoomID(Data.ROOM_ID)->GetPlayerNum(); ++i) {
			memset(Packet, 0, MAX_BUFFER_LENGTH);
			m_RoomManager.GetRoomInfoRoomID(Data.ROOM_ID)->SetPlayerHP(i, 1000);
			m_RoomManager.GetRoomInfoRoomID(Data.ROOM_ID)->WriteAll(PT_PLAYER_HP_SC, Packet, WRITE_PT_PLAYER_HP_SC(Packet, i, 1000));
		}
		//memset(Packet, 0, MAX_BUFFER_LENGTH);
		//m_RoomManager.GetRoomInfoRoomID(Data.ROOM_ID)->WriteAll(PT_BOSS_HP_SC, Packet, WRITE_PT_BOSS_HP_SC(Packet, 10000));

		m_Sync.unlock();
		return VOID();
	}
	m_RoomManager.GetRoomInfoRoomID(Data.ROOM_ID)->SetLoadingComplateNum(LoadingComplateNum);
	int temp = m_RoomManager.GetRoomInfoRoomID(Data.ROOM_ID)->GetLoadingComplateNum();
	m_Sync.unlock();
	return VOID();
}


VOID CServerIocp::PROC_PT_FTOWN_NPC_READY_CS(CConnectedSession * pConnectedSession, DWORD dwProtocol, BYTE * pPacket, DWORD dwPacketLength) {
	READ_PACKET(PT_FTOWN_NPC_READY_CS);
	INT ROOM_ID = Data.ROOM_ID;
	INT SLOT_ID = Data.SLOT_ID;
	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };

	// 자신 레디 상태로 바꾸고
	m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayers()[SLOT_ID]->GetPlayer()->SetREADY(true);

	int nReadyPlayer{ 0 };
	for (int i = 0; i < m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayerNum(); ++i) {
		if (m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayers()[i]->GetPlayer()->GetREADY())
			nReadyPlayer++;
	}
	if (nReadyPlayer == m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayerNum()) {//방안의 모든 사람이 ready했으면 출발
		m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->WriteAll(PT_FTOWN_NPC_READY_COMP_SC, Packet, WRITE_PT_FTOWN_NPC_READY_COMP_SC(Packet));
		for (int i = 0; i < m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayerNum(); ++i)
			m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayers()[i]->GetPlayer()->SetREADY(0);
		memset(Packet, 0, MAX_BUFFER_LENGTH);
		m_RoomManager.GetRoomInfoRoomID(Data.ROOM_ID)->WriteAll(PT_BOSS_HP_SC, Packet, WRITE_PT_BOSS_HP_SC(Packet, 2000));
		return;
	}

	m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->WriteAllExceptMe(SLOT_ID, PT_FTOWN_NPC_READY_SC, Packet, WRITE_PT_FTOWN_NPC_READY_SC(Packet,
		SLOT_ID, true));

	return VOID();
}
VOID CServerIocp::PROC_PT_FTOWN_BOSS_ACTION_CAMERA_READY_CS(CConnectedSession * pConnectedSession, DWORD dwProtocol, BYTE * pPacket, DWORD dwPacketLength) {
	READ_PACKET(PT_FTOWN_BOSS_ACTION_CAMERA_READY_CS);
	INT ROOM_ID = Data.ROOM_ID;
	INT SLOT_ID = Data.SLOT_ID;
	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };

	// 자신 레디 상태로 바꾸고
	m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayers()[SLOT_ID]->GetPlayer()->SetREADY(true);

	int nReadyPlayer{ 0 };
	for (int i = 0; i < m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayerNum(); ++i) {
		if (m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayers()[i]->GetPlayer()->GetREADY())
			nReadyPlayer++;
	}
	if (nReadyPlayer == m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayerNum()) {//방안의 모든 사람이 ready했으면 출발
		m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->WriteAll(PT_FTOWN_BOSS_ACTION_CAMERA_READY_COMP_SC, Packet, WRITE_PT_FTOWN_BOSS_ACTION_CAMERA_READY_COMP_SC(Packet));
		for (int i = 0; i < m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayerNum(); ++i)
			m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayers()[i]->GetPlayer()->SetREADY(0);
		

		return;
	}

	m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->WriteAllExceptMe(SLOT_ID, PT_FTOWN_BOSS_ACTION_CAMERA_READY_SC, Packet, WRITE_PT_FTOWN_BOSS_ACTION_CAMERA_READY_SC(Packet,
		SLOT_ID, true));

	return VOID();
}
VOID CServerIocp::PROC_PT_FTOWN_NPC2_READY_CS(CConnectedSession * pConnectedSession, DWORD dwProtocol, BYTE * pPacket, DWORD dwPacketLength) {
	READ_PACKET(PT_FTOWN_NPC2_READY_CS);
	INT ROOM_ID = Data.ROOM_ID;
	INT SLOT_ID = Data.SLOT_ID;
	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };

	// 자신 레디 상태로 바꾸고
	m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayers()[SLOT_ID]->GetPlayer()->SetREADY(true);

	int nReadyPlayer{ 0 };
	for (int i = 0; i < m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayerNum(); ++i) {
		if (m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayers()[i]->GetPlayer()->GetREADY())
			nReadyPlayer++;
	}
	if (nReadyPlayer == m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayerNum()) {//방안의 모든 사람이 ready했으면 출발
		m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->WriteAll(PT_FTOWN_NPC2_READY_COMP_SC, Packet, WRITE_PT_FTOWN_NPC_READY_COMP_SC(Packet));
		for (int i = 0; i < m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayerNum(); ++i)
			m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayers()[i]->GetPlayer()->SetREADY(0);
		return;
	}

	m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->WriteAllExceptMe(SLOT_ID, PT_FTOWN_NPC2_READY_SC, Packet, WRITE_PT_FTOWN_NPC_READY_SC(Packet,
		SLOT_ID, true));

	return VOID();
}


VOID CServerIocp::PROC_PT_ALDENARD_READY_CS(CConnectedSession * pConnectedSession, DWORD dwProtocol, BYTE * pPacket, DWORD dwPacketLength) {
	READ_PACKET(PT_ALDENARD_READY_CS);

	int LoadingComplateNum = m_RoomManager.GetRoomInfoRoomID(Data.ROOM_ID)->GetLoadingComplateNum();
	LoadingComplateNum++;
	if (LoadingComplateNum == m_RoomManager.GetRoomInfoRoomID(Data.ROOM_ID)->GetPlayerNum()) {
		BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };
		m_RoomManager.GetRoomInfoRoomID(Data.ROOM_ID)->WriteAll(PT_ALDENARD_READY_SC, Packet, WRITE_PT_ALDENARD_READY_SC(Packet));
		m_RoomManager.GetRoomInfoRoomID(Data.ROOM_ID)->SetLoadingComplateNum(0);
		return VOID();
	}
	m_RoomManager.GetRoomInfoRoomID(Data.ROOM_ID)->SetLoadingComplateNum(LoadingComplateNum);
	return VOID();
}

VOID CServerIocp::PROC_PT_SARASEN_START_CS(CConnectedSession * pConnectedSession, DWORD dwProtocol, BYTE * pPacket, DWORD dwPacketLength) {
	READ_PACKET(PT_SARASEN_START_CS);
	INT ROOM_ID = Data.ROOM_ID;
	INT SLOT_ID = Data.SLOT_ID;
	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };
	// 자신 레디 상태로 바꾸고
	m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayers()[SLOT_ID]->GetPlayer()->SetREADY(true);

	int nReadyPlayer{ 0 };
	for (int i = 0; i < m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayerNum(); ++i) {
		if (m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayers()[i]->GetPlayer()->GetREADY())
			nReadyPlayer++;
	}
	if (nReadyPlayer == m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayerNum()) {//방안의 모든 사람이 ready했으면 출발
		m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->WriteAll(PT_SARASEN_START_COMP_SC, Packet, WRITE_PT_SARASEN_START_COMP_SC(Packet));
		for (int i = 0; i < m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayerNum(); ++i)
			m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayers()[i]->GetPlayer()->SetREADY(0);
		return;
	}

	m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->WriteAllExceptMe(SLOT_ID, PT_SARASEN_START_SC, Packet, WRITE_PT_SARASEN_START_SC(Packet,
		SLOT_ID, true));

	return VOID();
}
VOID CServerIocp::PROC_PT_SARASEN_READY_CS(CConnectedSession * pConnectedSession, DWORD dwProtocol, BYTE * pPacket, DWORD dwPacketLength) {
	READ_PACKET(PT_SARASEN_READY_CS);

	cout << "SARASEN LOADING READY!" << endl;
	int LoadingComplateNum = m_RoomManager.GetRoomInfoRoomID(Data.ROOM_ID)->GetLoadingComplateNum();
	LoadingComplateNum++;
	if (LoadingComplateNum == m_RoomManager.GetRoomInfoRoomID(Data.ROOM_ID)->GetPlayerNum()) {
		BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };
		m_RoomManager.GetRoomInfoRoomID(Data.ROOM_ID)->WriteAll(PT_SARASEN_READY_SC, Packet, WRITE_PT_SARASEN_READY_SC(Packet));
		m_RoomManager.GetRoomInfoRoomID(Data.ROOM_ID)->SetLoadingComplateNum(0);
		cout << "SARASEN LOADING START!" << endl;
		return VOID();
	}
	m_RoomManager.GetRoomInfoRoomID(Data.ROOM_ID)->SetLoadingComplateNum(LoadingComplateNum);
	return VOID();
}


VOID CServerIocp::PROC_PT_SARASEN_BOSS_START_CS(CConnectedSession * pConnectedSession, DWORD dwProtocol, BYTE * pPacket, DWORD dwPacketLength) {
	READ_PACKET(PT_SARASEN_BOSS_START_CS);
	INT ROOM_ID = Data.ROOM_ID;
	INT SLOT_ID = Data.SLOT_ID;
	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };
	// 자신 레디 상태로 바꾸고
	m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayers()[SLOT_ID]->GetPlayer()->SetREADY(true);

	int nReadyPlayer{ 0 };
	for (int i = 0; i < m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayerNum(); ++i) {
		if (m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayers()[i]->GetPlayer()->GetREADY())
			nReadyPlayer++;
	}
	if (nReadyPlayer == m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayerNum()) {//방안의 모든 사람이 ready했으면 출발
		m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->WriteAll(PT_SARASEN_BOSS_START_COMP_SC, Packet, WRITE_PT_SARASEN_BOSS_START_COMP_SC(Packet));
		m_RoomManager.GetRoomInfoRoomID(Data.ROOM_ID)->GetpBoss()->SetHP(2000);
		memset(Packet, 0, MAX_BUFFER_LENGTH);
		m_RoomManager.GetRoomInfoRoomID(Data.ROOM_ID)->WriteAll(PT_BOSS_HP_SC, Packet, WRITE_PT_BOSS_HP_SC(Packet, 2000));
		for (int i = 0; i < m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayerNum(); ++i)
			m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayers()[i]->GetPlayer()->SetREADY(0);
		return;
	}

	m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->WriteAllExceptMe(SLOT_ID, PT_SARASEN_BOSS_START_SC, Packet, WRITE_PT_SARASEN_BOSS_START_SC(Packet,
		SLOT_ID, true));

	return VOID();
}

VOID CServerIocp::PROC_PT_SARASEN_BOSS_ACTION_CAMERA_READY_CS(CConnectedSession * pConnectedSession, DWORD dwProtocol, BYTE * pPacket, DWORD dwPacketLength) {
	READ_PACKET(PT_SARASEN_BOSS_ACTION_CAMERA_READY_CS);
	INT ROOM_ID = Data.ROOM_ID;
	INT SLOT_ID = Data.SLOT_ID;
	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };
	// 자신 레디 상태로 바꾸고
	m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayers()[SLOT_ID]->GetPlayer()->SetREADY(true);

	int nReadyPlayer{ 0 };
	for (int i = 0; i < m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayerNum(); ++i) {
		if (m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayers()[i]->GetPlayer()->GetREADY())
			nReadyPlayer++;
	}
	if (nReadyPlayer == m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayerNum()) {//방안의 모든 사람이 ready했으면 출발
		m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->WriteAll(PT_SARASEN_BOSS_ACTION_CAMERA_READY_COMP_SC, Packet, WRITE_PT_SARASEN_BOSS_ACTION_CAMERA_READY_COMP_SC(Packet));
		for (int i = 0; i < m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayerNum(); ++i)
			m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayers()[i]->GetPlayer()->SetREADY(0);
		return;
	}

	m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->WriteAllExceptMe(SLOT_ID, PT_SARASEN_BOSS_ACTION_CAMERA_READY_SC, Packet, WRITE_PT_SARASEN_BOSS_ACTION_CAMERA_READY_SC(Packet,
		SLOT_ID, true));

	return VOID();
}

VOID CServerIocp::PROC_PT_RANGE_SKILL_INFO_CS(CConnectedSession *pConnectedSession, DWORD dwProtocol, BYTE *pPacket, DWORD dwPacketLength) {
	READ_PACKET(PT_RANGE_SKILL_INFO_CS);
	//Data.SLOT_ID
	//Data.X Y Z
	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };
	m_RoomManager.GetRoomInfoRoomID(pConnectedSession->GetPlayer()->GetROOM_ID())->WriteAllExceptMe(Data.SLOT_ID, PT_RANGE_SKILL_INFO_SC, Packet, WRITE_PT_RANGE_SKILL_INFO_SC(Packet, Data.SLOT_ID, Data.X, Data.Y, Data.Z));
}
VOID CServerIocp::PROC_PT_SKILL_COLLISION_TO_TARGET_CS(CConnectedSession * pConnectedSession, DWORD dwProtocol, BYTE * pPacket, DWORD dwPacketLength) {
	READ_PACKET(PT_SKILL_COLLISION_TO_TARGET_CS);

	//Data.ROOM_ID;
	//Data.MY_SLOT_ID;
	//Data.TARGET_SLOT_ID;
	//Data.CHARACTER;
	//Data.SKILL_NUM;
	m_Sync.lock();

	if(Data.MY_SLOT_ID == 5)
		Data.CHARACTER = 6;
	//cout << "MY : " << Data.MY_SLOT_ID << " / TARGET : " << Data.TARGET_SLOT_ID << " / CHARACTER : " << Data.CHARACTER << " / SKILLNUM : " << Data.SKILL_NUM << endl;
	if (Data.TARGET_SLOT_ID == 5) // 5는 보스
	{
		int retval = m_RoomManager.GetRoomInfoRoomID(Data.ROOM_ID)->GetpBoss()->DamageToHP(DamageFromCharacterSkill(Data.CHARACTER, Data.SKILL_NUM));
		
		BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };
		if (retval > 0) {
			m_RoomManager.GetRoomInfoRoomID(Data.ROOM_ID)->WriteAll(PT_BOSS_HP_SC, Packet, WRITE_PT_BOSS_HP_SC(Packet, retval));
			
			}
		else {
			m_RoomManager.GetRoomInfoRoomID(Data.ROOM_ID)->WriteAll(PT_BOSS_CLEAR_SC, Packet, WRITE_PT_BOSS_CLEAR_SC(Packet));
			for (int i = 0; i < m_RoomManager.GetRoomInfoRoomID(Data.ROOM_ID)->GetPlayerNum(); ++i) {
				memset(Packet, 0, MAX_BUFFER_LENGTH);
				m_RoomManager.GetRoomInfoRoomID(Data.ROOM_ID)->SetPlayerHP(i, 1000);
				m_RoomManager.GetRoomInfoRoomID(Data.ROOM_ID)->WriteAll(PT_PLAYER_HP_SC, Packet, WRITE_PT_PLAYER_HP_SC(Packet, i, 1000));
			}
		}
		//cout << "BOSS HP : " << retval << endl;
	}
	else{
		int retval = DamageFromCharacterSkill(Data.CHARACTER, Data.SKILL_NUM);
		// 양수면 데미지 / 음수면 힐

		retval = m_RoomManager.GetRoomInfoRoomID(Data.ROOM_ID)->DamagerToPlayerHP(Data.TARGET_SLOT_ID, retval);

		BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };
		m_RoomManager.GetRoomInfoRoomID(Data.ROOM_ID)->WriteAll(PT_PLAYER_HP_SC, Packet, WRITE_PT_PLAYER_HP_SC(Packet, Data.TARGET_SLOT_ID, retval));

		//cout << Data.TARGET_SLOT_ID<< " PLAYER HP : " << retval << endl;
	}
	m_Sync.unlock();
	return VOID();
}

int CServerIocp::DamageFromCharacterSkill(INT Character, INT SkillNum) {
	int retval = 0;

	if (SkillNum == 99)
		return 9999999;
	if (SkillNum == 9)
		return 300;
	switch (Character) {
	case 0: // 레인저
		if (SkillNum == 1) return -100;
		else if (SkillNum == 2) return 800;
		else if (SkillNum == 3) return 1000;
		else if (SkillNum == 4) return 1000;
		if (SkillNum == 9)
			return 300;
		break;
	case 1: // 기사
	
		if (SkillNum == 1) return 1000;
		else if (SkillNum == 2) return 1000;
		else if (SkillNum == 3) return 1000;

		break;
	case 2: // 공간
		if (SkillNum == 1) return 100;
		if (SkillNum == 2) return 1000;
		else if (SkillNum == 3) return 1500;
		else if (SkillNum == 4) return 100;
		if (SkillNum == 9)
			return 300;
		break;
	case 3: // 수녀
		if (SkillNum == 0) return 100;
		if (SkillNum == 1) return -300;
		else if (SkillNum == 2) return 200;
		else if (SkillNum == 3) return -500;
		else if (SkillNum == 4) return 300;
		if (SkillNum == 9)
			return 300;
		break;
	case 4: // 법사
		if (SkillNum == 1) return 500;
		else if (SkillNum == 2) return 1000;
		else if (SkillNum == 3) return -500;
		else if (SkillNum == 4) return 1200;
		if (SkillNum == 9)
			return 300;
		break;
	case 5: // 바드
		if (SkillNum == 1) return 300;
		else if (SkillNum == 2) return 200;
		else if (SkillNum == 3) return 500; 
		else if (SkillNum == 4) return -300;
		if (SkillNum == 9)
			return 300;
		break;
	case 6: // 보스
		if (SkillNum == 1) return 300;
		else if (SkillNum == 2) return 300;
		else if (SkillNum == 3) return 300;
		else if (SkillNum == 4) return 300;
		if (SkillNum == 9)
			return 200;
		break;
	}

	return retval;
}