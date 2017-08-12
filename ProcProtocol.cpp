// ��Ŷ ó���� ���ؼ� ���� �ۼ��� ProcProtocol.cpp
#include "stdafx.h"
#include "ServerIocp.h"

#define READ_PACKET(PROTOCOL)\
	BYTE WriteBuffer[MAX_BUFFER_LENGTH] = {0, };\
	S_##PROTOCOL Data;\
	READ_##PROTOCOL(pPacket, Data);


//0606
//���� ���� ���߿�
//0606
VOID CServerIocp::PROC_PT_LOGIN_CS(CConnectedSession *pConnectedSession, DWORD dwProtocol, BYTE *pPacket, DWORD dwPacketLength)
{
	// ��ó�� �Լ��� ����ȭ
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

	// DataBase ���������� �ҷ�����
	//idpw = m_DataBase.LoadUserInfo(recv_id);



}

VOID CServerIocp::PROC_PT_SIGN_UP_CS(CConnectedSession *pConnectedSession, DWORD dwProtocol, BYTE *pPacket, DWORD dwPacketLength)
{
	// ��ó�� �Լ��� ����ȭ
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

///////////////////////�༭������
VOID CServerIocp::PROC_PT_ENTER_EARTH_CS(CConnectedSession *pConnectedSession, DWORD dwProtocol, BYTE *pPacket, DWORD dwPacketLength) {
	// ��ó�� �Լ��� ����ȭ
	READ_PACKET(PT_ENTER_EARTH_CS);

	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };

	//���� ID�ο��ؾ��� 
	//Ư�� ������ �����ϸ� ���� �㰡
	pConnectedSession->CreatePlayer();
	//���� �����ڿ��� �÷��̾� AddPlayer���༭ �־��� 

	//CPlayer* pPlayer = pConnectedSession->GetPlayer();
	//if (m_pServerMain->GetObjectManager()->AddPlayer(pConnectedSession)) {
	//	//AddPlayer�� �����ϸ�, �� ���ӿ� ���ٸ� 
	//	//���� �� ������ ������ �׳� ������
	//
	//	XMFLOAT3 xmfPos;
	//	XMStoreFloat3(&xmfPos, pPlayer->GetPlayerPosition());
	//	//team, �� ��ġ ������
	//	pConnectedSession->WritePacket(PT_ENTER_EARTH_SUC, Packet, WRITE_PT_ENTER_EARTH_SUC(Packet, 
	//		pPlayer->GetID(), pPlayer->GetTeam(), xmfPos.x, xmfPos.y, xmfPos.z));
	//
	//}
	//else {
	//	pConnectedSession->WritePacket(PT_ENTER_EARTH_FAIL, Packet, WRITE_PT_ENTER_EARTH_FAIL(Packet));
	//
	//}
}
// ����� ��� �������� ó��
VOID CServerIocp::PROC_PT_FREQUENCY_MOVE_CS(CConnectedSession *pConnectedSession, DWORD dwProtocol, BYTE *pPacket, DWORD dwPacketLength)
{
	//�÷��̾��� ������ ���� ���� �ȵ������� return;
	//if (nullptr == pConnectedSession->GetPlayer()->GetRegion()) return;


	// ��ó�� �Լ��� ����ȭ
	READ_PACKET(PT_FREQUENCY_MOVE_CS);
	// ���� �ڵ�
	
	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };
	
	INT SLOT_ID = pConnectedSession->GetPlayer()->GetSLOT_ID();
	INT ROOM_ID = pConnectedSession->GetPlayer()->GetROOM_ID();
	float fPosX = Data.POSX;
	float fPosY = Data.POSY;
	float fPosZ = Data.POSZ;
	float fAngleY = Data.ANGLEY;
	DWORD dwDirection = Data.DIRECTION;
	bool bJump = Data.JUMP;
	
	m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->WriteAllExceptMe(SLOT_ID, PT_FREQUENCY_MOVE_SC, Packet, WRITE_PT_FREQUENCY_MOVE_SC(Packet,
		SLOT_ID, fPosX, fPosY, fPosZ, fAngleY, dwDirection, bJump));
		
	//cout <<ROOM_ID << ", " << SLOT_ID << ", "<< fPosX << ", " << fPosY << ", " << fPosZ << endl;
	//std::cout << SLOT_ID << ", " << fPosX <<", " << fPosY << ", " << fPosZ << " Angle : "<< fAngleY << std::endl;
	//��ġ ����ȭ
	//pPlayer->SetPlayerPosition(XMLoadFloat3(&xmfPos));

	////�浹üũ
	
	////��ε� ĳ��Ʈ
	//pPlayer->GetRegion()->WriteAll(PT_FREQUENCY_MOVE_SC, Packet,
	//	WRITE_PT_FREQUENCY_MOVE_SC(Packet, PLAYER, 
	//		pPlayer->GetID(), xmfPos.x, xmfPos.y, xmfPos.z));

}

VOID CServerIocp::PROC_PT_MOUSE_LEFT_ATTACK_CS(CConnectedSession *pConnectedSession, DWORD dwProtocol, BYTE *pPacket, DWORD dwPacketLength)
{
	//�÷��̾��� ������ ���� ���� �ȵ������� return;
	//if (nullptr == pConnectedSession->GetPlayer()->GetRegion()) return;


	// ��ó�� �Լ��� ����ȭ
	READ_PACKET(PT_MOUSE_LEFT_ATTACK_CS);
	// ���� �ڵ�
	
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
	//��ġ ����ȭ
	//pPlayer->SetPlayerPosition(XMLoadFloat3(&xmfPos));

	////�浹üũ

	////��ε� ĳ��Ʈ
	//pPlayer->GetRegion()->WriteAll(PT_FREQUENCY_MOVE_SC, Packet,
	//	WRITE_PT_FREQUENCY_MOVE_SC(Packet, PLAYER, 
	//		pPlayer->GetID(), xmfPos.x, xmfPos.y, xmfPos.z));

}


VOID CServerIocp::PROC_PT_KEY_INPUT_CS(CConnectedSession *pConnectedSession, DWORD dwProtocol, BYTE *pPacket, DWORD dwPacketLength)
{
//	//�÷��̾��� ������ ���� ���� �ȵ������� return;
//	if (nullptr == pConnectedSession->GetPlayer()->GetRegion()) return;
//
//	// ��ó�� �Լ��� ����ȭ
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
//	//��Ŷ�� ó���� �� 
//	//�÷��̾ �ִ� ������ ��� �÷��̾��
//
//	//��ε� ĳ��Ʈ
//	pPlayer->GetRegion()->WriteAll(PT_KEY_INPUT_ALL_SC, pPacket, WRITE_PT_KEY_INPUT_ALL_SC(pPacket,
//		pPlayer->GetID(), pPlayer->GetdwDirection(), Data.X, Data.Y, Data.Z));
//

}


VOID CServerIocp::PROC_PT_MOUSE_INPUT_CS(CConnectedSession *pConnectedSession, DWORD dwProtocol, BYTE *pPacket, DWORD dwPacketLength)
{
	////�÷��̾��� ������ ���� ���� �ȵ������� return;
	//if (nullptr == pConnectedSession->GetPlayer()->GetRegion()) return;
	//
	//// ��ó�� �Լ��� ����ȭ
	//READ_PACKET(PT_MOUSE_INPUT_CS);
	//// ���� �ڵ�
	//
	//CPlayer* pPlayer = pConnectedSession->GetPlayer();
	//
	////���� test �ϱ� ���� ���콺 ��ǲ ���� + �������� ���ι��� ������ Rotate���� ����
	//if (M_RBUTTON == Data.MOUSEBUTTON)
	//	pPlayer->Rotate(Data.CYDELTA, 0.0f, -Data.CXDELTA);
	//else 
	//	pPlayer->Rotate(Data.CYDELTA, Data.CXDELTA, 0.0f);
	//
	////��ε� ĳ��Ʈ
	//pPlayer->GetRegion()->WriteAll(PT_MOUSE_INPUT_ALL_SC, pPacket, WRITE_PT_MOUSE_INPUT_ALL_SC(pPacket,
	//	pPlayer->GetID(), Data.CXDELTA, Data.CYDELTA, Data.MOUSEBUTTON));

}


VOID CServerIocp::PROC_PT_MOUSE_BUTTON_INPUT_CS(CConnectedSession *pConnectedSession, DWORD dwProtocol, BYTE *pPacket, DWORD dwPacketLength)
{
	////�÷��̾��� ������ ���� ���� �ȵ������� return;
	//if (nullptr == pConnectedSession->GetPlayer()->GetRegion()) return;
	//
	//// ��ó�� �Լ��� ����ȭ
	//READ_PACKET(PT_MOUSE_BUTTON_INPUT_CS);
	//// ���� �ڵ�
	//
	//CPlayer* pPlayer = pConnectedSession->GetPlayer();
	//
	////�ش� �÷��̾��� ���콺 ��ư�� ���� 
	//pPlayer->SetdwMouseButton(Data.MOUSEBUTTON);
	//
	//
	////��ε� ĳ��Ʈ
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
	for (int i = 0; i < m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayerNum(); ++i) {//����� ������
		if (i == SLOT_ID) continue;//�� ����
		if (m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayers()[i]->GetPlayer()->GetCHARACTER() == Data.CHARACTER)//���� �� ĳ���� �ֳ� �˻�
			Data.CHARACTER = m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayers()[SLOT_ID]->GetPlayer()->GetCHARACTER();//������ �� �ɸ��� �������� ����
	}
	m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayers()[SLOT_ID]->GetPlayer()->SetCHARACTER(Data.CHARACTER);//���� ���� ���� ���� Data.Chr�Է�

	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };
	//m_pRoom->WriteAllExceptMe(SLOT_ID, PT_ROOM_DATA_CHANGE_SC, Packet, WRITE_PT_ROOM_DATA_CHANGE_SC(Packet, SLOT_ID, Data.READY, Data.CHARACTER));
	m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->WriteAll(PT_ROOM_DATA_CHANGE_SC, Packet, WRITE_PT_ROOM_DATA_CHANGE_SC(Packet, SLOT_ID, Data.READY, Data.CHARACTER));
	
	//room���� ��� player�� ready�� ����
	int nReadyPlayer{ 0 };
	for (int i = 0; i < m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayerNum(); ++i) {
		if (m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayers()[i]->GetPlayer()->GetREADY())
			nReadyPlayer++;
	}

	if (nReadyPlayer == m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayerNum()) {//����� ��� ����� ready������ ���
		m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->WriteAll(PT_FTOWN_START_SC, Packet, WRITE_PT_FTOWN_START_SC(Packet));

		for (int i = 0; i < m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayerNum(); ++i)
			m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayers()[i]->GetPlayer()->SetREADY(0);

	}
	//room���� ��� player�� ready�� ����
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

	// �ڽ� ���� ���·� �ٲٰ�
	m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayers()[SLOT_ID]->GetPlayer()->SetREADY(true);

	int nReadyPlayer{ 0 };
	for (int i = 0; i < m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayerNum(); ++i) {
		if (m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayers()[i]->GetPlayer()->GetREADY())
			nReadyPlayer++;
	}
	if (nReadyPlayer == m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayerNum()) {//����� ��� ����� ready������ ���
		m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->WriteAll(PT_FTOWN_NPC_READY_COMP_SC, Packet, WRITE_PT_FTOWN_NPC_READY_COMP_SC(Packet));
		for (int i = 0; i < m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayerNum(); ++i)
			m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayers()[i]->GetPlayer()->SetREADY(0);
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

	// �ڽ� ���� ���·� �ٲٰ�
	m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayers()[SLOT_ID]->GetPlayer()->SetREADY(true);

	int nReadyPlayer{ 0 };
	for (int i = 0; i < m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayerNum(); ++i) {
		if (m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayers()[i]->GetPlayer()->GetREADY())
			nReadyPlayer++;
	}
	if (nReadyPlayer == m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayerNum()) {//����� ��� ����� ready������ ���
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

	// �ڽ� ���� ���·� �ٲٰ�
	m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayers()[SLOT_ID]->GetPlayer()->SetREADY(true);

	int nReadyPlayer{ 0 };
	for (int i = 0; i < m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayerNum(); ++i) {
		if (m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayers()[i]->GetPlayer()->GetREADY())
			nReadyPlayer++;
	}
	if (nReadyPlayer == m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayerNum()) {//����� ��� ����� ready������ ���
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
	}
	m_RoomManager.GetRoomInfoRoomID(Data.ROOM_ID)->SetLoadingComplateNum(LoadingComplateNum);
	return VOID();
}

VOID CServerIocp::PROC_PT_SARASEN_START_CS(CConnectedSession * pConnectedSession, DWORD dwProtocol, BYTE * pPacket, DWORD dwPacketLength) {
	READ_PACKET(PT_SARASEN_START_CS);
	INT ROOM_ID = Data.ROOM_ID;
	INT SLOT_ID = Data.SLOT_ID;
	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };
	// �ڽ� ���� ���·� �ٲٰ�
	m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayers()[SLOT_ID]->GetPlayer()->SetREADY(true);

	int nReadyPlayer{ 0 };
	for (int i = 0; i < m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayerNum(); ++i) {
		if (m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayers()[i]->GetPlayer()->GetREADY())
			nReadyPlayer++;
	}
	if (nReadyPlayer == m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayerNum()) {//����� ��� ����� ready������ ���
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

	int LoadingComplateNum = m_RoomManager.GetRoomInfoRoomID(Data.ROOM_ID)->GetLoadingComplateNum();
	LoadingComplateNum++;
	if (LoadingComplateNum == m_RoomManager.GetRoomInfoRoomID(Data.ROOM_ID)->GetPlayerNum()) {
		BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };
		m_RoomManager.GetRoomInfoRoomID(Data.ROOM_ID)->WriteAll(PT_SARASEN_READY_SC, Packet, WRITE_PT_SARASEN_READY_SC(Packet));
		m_RoomManager.GetRoomInfoRoomID(Data.ROOM_ID)->SetLoadingComplateNum(0);
	}
	m_RoomManager.GetRoomInfoRoomID(Data.ROOM_ID)->SetLoadingComplateNum(LoadingComplateNum);
	return VOID();
}


VOID CServerIocp::PROC_PT_SARASEN_BOSS_START_CS(CConnectedSession * pConnectedSession, DWORD dwProtocol, BYTE * pPacket, DWORD dwPacketLength) {
	READ_PACKET(PT_SARASEN_BOSS_START_CS);
	INT ROOM_ID = Data.ROOM_ID;
	INT SLOT_ID = Data.SLOT_ID;
	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };
	// �ڽ� ���� ���·� �ٲٰ�
	m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayers()[SLOT_ID]->GetPlayer()->SetREADY(true);

	int nReadyPlayer{ 0 };
	for (int i = 0; i < m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayerNum(); ++i) {
		if (m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayers()[i]->GetPlayer()->GetREADY())
			nReadyPlayer++;
	}
	if (nReadyPlayer == m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayerNum()) {//����� ��� ����� ready������ ���
		m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->WriteAll(PT_SARASEN_BOSS_START_COMP_SC, Packet, WRITE_PT_SARASEN_BOSS_START_COMP_SC(Packet));
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
	// �ڽ� ���� ���·� �ٲٰ�
	m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayers()[SLOT_ID]->GetPlayer()->SetREADY(true);

	int nReadyPlayer{ 0 };
	for (int i = 0; i < m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayerNum(); ++i) {
		if (m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayers()[i]->GetPlayer()->GetREADY())
			nReadyPlayer++;
	}
	if (nReadyPlayer == m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayerNum()) {//����� ��� ����� ready������ ���
		m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->WriteAll(PT_SARASEN_BOSS_ACTION_CAMERA_READY_COMP_SC, Packet, WRITE_PT_SARASEN_BOSS_ACTION_CAMERA_READY_COMP_SC(Packet));
		for (int i = 0; i < m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayerNum(); ++i)
			m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->GetPlayers()[i]->GetPlayer()->SetREADY(0);
		return;
	}

	m_RoomManager.GetRoomInfoRoomID(ROOM_ID)->WriteAllExceptMe(SLOT_ID, PT_SARASEN_BOSS_ACTION_CAMERA_READY_SC, Packet, WRITE_PT_SARASEN_BOSS_ACTION_CAMERA_READY_SC(Packet,
		SLOT_ID, true));

	return VOID();
}