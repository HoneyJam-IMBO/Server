#include "stdafx.h"
#include "Player.h"


/////////////////////////player
/////////////////////////player

void CPlayer::Begin() {

	m_eObjTag = PLAYER;

	//���콺 ó���� �ϱ����� �߰��� �ڵ�
	m_d3dxvPosition = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_d3dxvRight = XMFLOAT3(1.0f, 0.0f, 0.0f);
	m_d3dxvUp = XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_d3dxvLook = XMFLOAT3(0.0f, 0.0f, 1.0f);

	m_d3dxvVelocity = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_d3dxvGravity = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_fMaxVelocityXZ = 0.0f;
	m_fMaxVelocityY = 0.0f;
	m_fFriction = 0.0f;


	m_fPitch = 0.0f;
	m_fRoll = 0.0f;
	m_fYaw = 0.0f;

	m_dwMousebutton = 0;
	m_dwDirection = 0;
	SetPosition(XMLoadFloat3(&m_d3dxvPosition));

	m_BoundingSphere.Radius = PLAYER_RADIUS;
}

void CPlayer::End() {

}

void CPlayer::Restart() {

	Begin();
	//�������� ����
	if (m_pRegion) m_pRegion->DeletePlayer(m_pConnectedSession);

	//���� �丮��Ʈ ��ó�� cl
	ClearViewList_OBJ();
	ClearViewList_PLAYER();

	//ID�缳��
	SetID();

	//���콺 ó���� �ϱ����� �߰��� �ڵ�
	m_d3dxvPosition = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_d3dxvRight = XMFLOAT3(1.0f, 0.0f, 0.0f);
	m_d3dxvUp = XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_d3dxvLook = XMFLOAT3(0.0f, 0.0f, 1.0f);

	m_d3dxvVelocity = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_d3dxvGravity = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_fMaxVelocityXZ = 0.0f;
	m_fMaxVelocityY = 0.0f;
	m_fFriction = 0.0f;


	m_fPitch = 0.0f;
	m_fRoll = 0.0f;
	m_fYaw = 0.0f;

	m_dwDirection = 0;
	//0412 ���콺 ��ư�Է�ó���� ���� ����
	m_dwMousebutton = 0;
}
//CPlayer ����, �Ҹ���
void CPlayer::Move(DWORD dwDirection, float fDistance, bool bUpdateVelocity)
{
	if (dwDirection)
	{
		XMVECTOR d3dxvShift = XMVectorZero();
		if (dwDirection & DIR_FORWARD) d3dxvShift += XMLoadFloat3(&m_d3dxvLook) * fDistance;
		if (dwDirection & DIR_BACKWARD) d3dxvShift -= XMLoadFloat3(&m_d3dxvLook) * fDistance;
		if (dwDirection & DIR_RIGHT) d3dxvShift += XMLoadFloat3(&m_d3dxvRight) * fDistance;
		if (dwDirection & DIR_LEFT) d3dxvShift -= XMLoadFloat3(&m_d3dxvRight) * fDistance;
		if (dwDirection & DIR_UP) d3dxvShift += XMLoadFloat3(&m_d3dxvUp) * fDistance;
		if (dwDirection & DIR_DOWN) d3dxvShift -= XMLoadFloat3(&m_d3dxvUp) * fDistance;

		Move(d3dxvShift, bUpdateVelocity);
	}
}

void CPlayer::Update(float fTimeElapsed)
{
	//���� >>?
	float fPlayerSpeed = PLAYER_SPEED;
	//����
	XMStoreFloat3(&m_d3dxvVelocity, XMLoadFloat3(&m_d3dxvVelocity) + XMLoadFloat3(&m_d3dxvGravity) * fTimeElapsed);
	float fLength = sqrtf(m_d3dxvVelocity.x * m_d3dxvVelocity.x + m_d3dxvVelocity.z * m_d3dxvVelocity.z);


	float fMaxVelocityXZ = m_fMaxVelocityXZ * fTimeElapsed;
	if (fLength > fMaxVelocityXZ)
	{
		m_d3dxvVelocity.x *= (fMaxVelocityXZ / fLength);
		m_d3dxvVelocity.z *= (fMaxVelocityXZ / fLength);
	}
	float fMaxVelocityY = m_fMaxVelocityY * fTimeElapsed;
	fLength = sqrtf(m_d3dxvVelocity.y * m_d3dxvVelocity.y);
	if (fLength > fMaxVelocityY) m_d3dxvVelocity.y *= (fMaxVelocityY / fLength);

	//LATER 0404 ���⿡ Move�� �߰� �Ѵ�. dwDirection�� �̿��� Move��.
	//���� Direction�� ������ �÷��̾ �����Ѵ�. 
	//����
	if ((m_dwDirection != 0))
	{
		Move(m_dwDirection, fPlayerSpeed*fTimeElapsed, false);
		//std::cout <<"Player Update Func : POS - "<< m_d3dxvPosition.x << ", " << m_d3dxvPosition.y << ", " << m_d3dxvPosition.z << std::endl;
	}
	//����
	//����

	Move(XMLoadFloat3(&m_d3dxvVelocity), false);


	XMVECTOR d3dxvDeceleration = -XMLoadFloat3(&m_d3dxvVelocity);
	d3dxvDeceleration = XMVector3Normalize(d3dxvDeceleration);
	fLength = XMVectorGetX(XMVector3Length(XMLoadFloat3(&m_d3dxvVelocity)));
	float fDeceleration = (m_fFriction * fTimeElapsed);
	if (fDeceleration > fLength) fDeceleration = fLength;
	XMStoreFloat3(&m_d3dxvVelocity, XMLoadFloat3(&m_d3dxvVelocity) + d3dxvDeceleration * fDeceleration);

	//XMFLOAT3 xmfPos;
	//XMStoreFloat3(&xmfPos, GetPlayerPosition());
	//std::cout << "Player Update Func : ID - " << GetID() << std::endl << " Pos - " << xmfPos.x << ", " << xmfPos.y << ", " << xmfPos.z << std::endl;

}
void CPlayer::Move(const XMVECTOR& d3dxvShift, bool bUpdateVelocity)
{
	if (bUpdateVelocity)
	{
		XMStoreFloat3(&m_d3dxvVelocity, XMLoadFloat3(&m_d3dxvVelocity) + d3dxvShift);
	}
	else
	{
		XMVECTOR d3dxvPosition = XMLoadFloat3(&m_d3dxvPosition) + d3dxvShift;
		XMStoreFloat3(&m_d3dxvPosition, d3dxvPosition);
		CGameObject::SetPosition(m_d3dxvPosition.x, m_d3dxvPosition.y, m_d3dxvPosition.z);


		//m_BoundingSphere.Center = m_d3dxvPosition;
		//m_pCamera->Move(d3dxvShift);
	}
}

void CPlayer::Rotate(float x, float y, float z)
{
	XMMATRIX mtxRotate;

	if (x != 0.0f)
	{
		mtxRotate = XMMatrixRotationAxis(XMLoadFloat3(&m_d3dxvRight), XMConvertToRadians(x));
		XMStoreFloat3(&m_d3dxvLook, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvLook), mtxRotate));
		XMStoreFloat3(&m_d3dxvUp, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvUp), mtxRotate));
	}
	if (y != 0.0f)
	{
		mtxRotate = XMMatrixRotationAxis(XMLoadFloat3(&m_d3dxvUp), XMConvertToRadians(y));
		XMStoreFloat3(&m_d3dxvLook, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvLook), mtxRotate));
		XMStoreFloat3(&m_d3dxvRight, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvRight), mtxRotate));
	}
	if (z != 0.0f)
	{
		mtxRotate = XMMatrixRotationAxis(XMLoadFloat3(&m_d3dxvLook), XMConvertToRadians(z));
		XMStoreFloat3(&m_d3dxvUp, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvUp), mtxRotate));
		XMStoreFloat3(&m_d3dxvRight, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvRight), mtxRotate));
	}
	//	m_pCamera->Rotate(x, y, z);

	//if (y != 0.0f)
	//{
	//	mtxRotate = XMMatrixRotationAxis(XMLoadFloat3(&m_d3dxvUp), XMConvertToRadians(y));
	//	XMStoreFloat3(&m_d3dxvLook, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvLook), mtxRotate));
	//	XMStoreFloat3(&m_d3dxvRight, XMVector3TransformNormal(XMLoadFloat3(&m_d3dxvRight), mtxRotate));
	//}

	XMStoreFloat3(&m_d3dxvLook, XMVector3Normalize(XMLoadFloat3(&m_d3dxvLook)));
	XMStoreFloat3(&m_d3dxvRight, XMVector3Cross(XMLoadFloat3(&m_d3dxvUp), XMLoadFloat3(&m_d3dxvLook)));
	XMStoreFloat3(&m_d3dxvRight, XMVector3Normalize(XMLoadFloat3(&m_d3dxvRight)));
	XMStoreFloat3(&m_d3dxvUp, XMVector3Cross(XMLoadFloat3(&m_d3dxvLook), XMLoadFloat3(&m_d3dxvRight)));
	XMStoreFloat3(&m_d3dxvUp, XMVector3Normalize(XMLoadFloat3(&m_d3dxvUp)));

	m_d3dxmtxWorld._11 = m_d3dxvRight.x;
	m_d3dxmtxWorld._12 = m_d3dxvRight.y;
	m_d3dxmtxWorld._13 = m_d3dxvRight.z;

	m_d3dxmtxWorld._21 = m_d3dxvUp.x;
	m_d3dxmtxWorld._22 = m_d3dxvUp.y;
	m_d3dxmtxWorld._23 = m_d3dxvUp.z;

	m_d3dxmtxWorld._31 = m_d3dxvLook.x;
	m_d3dxmtxWorld._32 = m_d3dxvLook.y;
	m_d3dxmtxWorld._33 = m_d3dxvLook.z;
}

BOOL CPlayer::WritePacket(DWORD dwProtocol, BYTE* Packet, DWORD dwPacketLength) {

	return m_pConnectedSession->WritePacket(dwProtocol, Packet, dwPacketLength);

}

BOOL CPlayer::PutObject(CDynamicObject* pObj) {

	//ó�� ���� �� �� �ʿ��� �ֵ� �� ���⼭ �ش�. 
	//���� �ӵ� ��ġ ȸ������ ȸ���ӵ� ȸ���� Ÿ�� etc.
	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };

	//CLog::WriteLog(_T("PutObj"));
	//std::cout << pObj->GetID() << "�� " << GetID() << "����" << std::endl;

	XMFLOAT3 xmfPos;
	XMStoreFloat3(&xmfPos, pObj->GetPosition());

	XMFLOAT3 xmfDir;
	XMStoreFloat3(&xmfDir, pObj->GetMovingDir());


	return WritePacket(PT_PUT_OBJ_SC, Packet, WRITE_PT_PUT_OBJ_SC(Packet, pObj->GetID(), pObj->GetTag(), xmfPos.x, xmfPos.y, xmfPos.z
		, xmfDir.x, xmfDir.y, xmfDir.z,
		pObj->GetSpeed(), pObj->GetAccSpeed()));

}


BOOL CPlayer::PutObjects(std::list<CDynamicObject*>& lPutObjects) {

	//ó�� ���� �� �� �ʿ��� �ֵ� �� ���⼭ �ش�. 
	//���� �ӵ� ��ġ ȸ������ ȸ���ӵ� ȸ���� Ÿ�� etc.
	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };

	//CLog::WriteLog(_T("PutObj"));
	//std::cout << pObj->GetID() << "�� " << GetID() << "����" << std::endl;
	DWORD_PTR ID[STATIC_OBJECT_LIMIT] = { 0, };
	INT TAG[STATIC_OBJECT_LIMIT] = { 0, };
	FLOAT POSX[STATIC_OBJECT_LIMIT] = { 0, };
	FLOAT POSY[STATIC_OBJECT_LIMIT] = { 0, };
	FLOAT POSZ[STATIC_OBJECT_LIMIT] = { 0, };
	FLOAT DIRX[STATIC_OBJECT_LIMIT] = { 0, };
	FLOAT DIRY[STATIC_OBJECT_LIMIT] = { 0, };
	FLOAT DIRZ[STATIC_OBJECT_LIMIT] = { 0, };

	FLOAT SPD[STATIC_OBJECT_LIMIT] = { 0, };
	FLOAT ACCSPD[STATIC_OBJECT_LIMIT] = { 0, };

	//���� ����
	int count = 0;
	for (auto pObject : lPutObjects) {
		XMFLOAT3 xmfPos;
		XMStoreFloat3(&xmfPos, pObject->GetPosition());
		POSX[count] = xmfPos.x;
		POSY[count] = xmfPos.y;
		POSZ[count] = xmfPos.z;

		XMFLOAT3 xmfDir;
		XMStoreFloat3(&xmfDir, pObject->GetMovingDir());
		DIRX[count] = xmfDir.x;
		DIRY[count] = xmfDir.y;
		DIRZ[count] = xmfDir.z;

		ACCSPD[count] = pObject->GetAccSpeed();
		SPD[count] = pObject->GetSpeed();


		TAG[count] = pObject->GetTag();
		//std::cout << TAG[count] << " ";

		ID[count++] = pObject->GetID();

		if (count > 50) {
			//ī��Ʈ�� 50���� �Ѿ�� 
			WritePacket(PT_PUT_OBJS_SC, Packet, WRITE_PT_PUT_OBJS_SC(Packet, count, ID, TAG, POSX, POSY, POSZ
				, DIRX, DIRY, DIRZ,
				SPD, ACCSPD));
			//�ϴ� ���� �� 
			std::cout << count << std::endl;
			count = 0;
			//ī��Ʈ �ʱ�ȭ
		}
	}
	if (0 != count) {
		//���������� ���� �� ������
		WritePacket(PT_PUT_OBJS_SC, Packet, WRITE_PT_PUT_OBJS_SC(Packet, count, ID, TAG, POSX, POSY, POSZ
			, DIRX, DIRY, DIRZ,
			SPD, ACCSPD));

		std::cout << count << std::endl;
	}


	return TRUE;
}

BOOL CPlayer::RemoveObjects(std::list<CDynamicObject*> lRemoveObject) {

	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };

	//CLog::WriteLog(_T("RemoveObj"));
	//std::cout << pObj->GetID() << "�� " << GetID() << "����" << std::endl;
	DWORD_PTR ID[STATIC_OBJECT_LIMIT];
	INT TAG[STATIC_OBJECT_LIMIT];

	int count = 0;
	for (auto pObject : lRemoveObject) {

		ID[count] = pObject->GetID();
		TAG[count++] = pObject->GetTag();
	}
	//return WritePacket(PT_REMOVE_OBJ_SC, Packet, WRITE_PT_REMOVE_OBJ_SC(Packet, pObj->GetID()));

	return WritePacket(PT_REMOVE_OBJS_SC, Packet, WRITE_PT_REMOVE_OBJS_SC(Packet, count, ID, TAG));

}

BOOL CPlayer::RemoveObject(CDynamicObject* pObj) {

	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };

	//CLog::WriteLog(_T("RemoveObj"));
	//std::cout << pObj->GetID() << "�� " << GetID() << "����" << std::endl;

	return WritePacket(PT_REMOVE_OBJ_SC, Packet, WRITE_PT_REMOVE_OBJ_SC(Packet, pObj->GetID(), pObj->GetTag()));

}
BOOL CPlayer::ChangeStateObject(CDynamicObject* pObj) {

	//���߿� state�߰��ϰ� ���� �߰�.
	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };

	XMFLOAT3 xmfPos;
	XMStoreFloat3(&xmfPos, pObj->GetPosition());


	XMFLOAT3 xmfDir;
	XMStoreFloat3(&xmfDir, pObj->GetMovingDir());


	//CLog::WriteLog(_T("MoveObj"));
	//std::cout << pObj->GetID() << "�� " << GetID() << "����" << std::endl;
	return WritePacket(PT_CHANGE_STATE_OBJ_SC, Packet, WRITE_PT_CHANGE_STATE_OBJ_SC(Packet, pObj->GetID(), pObj->GetTag(),
		00/*pObj->GetState()*/, xmfPos.x, xmfPos.y, xmfPos.z,
		xmfDir.x, xmfDir.y, xmfDir.z,
		pObj->GetSpeed(), pObj->GetAccSpeed()));

}

BOOL CPlayer::PutPlayer(CPlayer* pPlayer) {

	//ó�� ���� �� �� �ʿ��� �ֵ� �� ���⼭ �ش�. 
	//���� �ӵ� ��ġ ȸ������ ȸ���ӵ� ȸ���� Ÿ�� etc.
	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };

	CLog::WriteLog(_T("PutPlayer"));
	std::cout << pPlayer->GetID() << "�� " << GetID() << "����" << std::endl;

	XMFLOAT3 xmfPos;
	XMStoreFloat3(&xmfPos, pPlayer->GetPlayerPosition());

	XMFLOAT3 xmfRight;
	XMStoreFloat3(&xmfRight, pPlayer->GetPlayerRight());

	XMFLOAT3 xmfUp;
	XMStoreFloat3(&xmfUp, pPlayer->GetPlayerUp());

	XMFLOAT3 xmfLook;
	XMStoreFloat3(&xmfLook, pPlayer->GetPlayerLook());




	return WritePacket(PT_PUT_PLAYER_SC, Packet, WRITE_PT_PUT_PLAYER_SC(Packet, pPlayer->GetID(),
		pPlayer->GetdwDirection(),
		xmfRight.x, xmfRight.y, xmfRight.z,
		xmfUp.x, xmfUp.y, xmfUp.z,
		xmfLook.x, xmfLook.y, xmfLook.z,
		xmfPos.x, xmfPos.y, xmfPos.z));

}



BOOL CPlayer::RemovePlayer(CPlayer* pPlayer) {

	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };

	CLog::WriteLog(_T("RemovePlayer"));
	std::cout << pPlayer->GetID() << "�� " << GetID() << "����" << std::endl;


	return WritePacket(PT_REMOVE_PLAYER_SC, Packet, WRITE_PT_REMOVE_PLAYER_SC(Packet, pPlayer->GetID()));


}
BOOL CPlayer::ChangeStatePlayer(CPlayer* pPlayer) {

	//���߿� state�߰��ϰ� ���� �߰�.
	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };

	XMFLOAT3 xmfPos;
	XMStoreFloat3(&xmfPos, pPlayer->GetPosition());

	CLog::WriteLog(_T("ChangeStatePlayer"));
	std::cout << pPlayer->GetID() << "�� " << GetID() << "����" << std::endl;

	return WritePacket(PT_CHANGE_STATE_PLAYER_SC, Packet, WRITE_PT_CHANGE_STATE_PLAYER_SC(Packet, pPlayer->GetID()
		, 00/*pObj->GetState()*/, xmfPos.x, xmfPos.y, xmfPos.z));

}

//�þ�ó��
//lockó��
//lockó��
//lockó��
//lockó��
void CPlayer::ProcView_OBJ(std::list<CDynamicObject*>& lNear) {

	//viewlist <id������ �̷���� list> �˻�

	std::list<CDynamicObject*> lPutObjects;

	//near�� ��� ��ü�� ���ؼ�
	for (auto pObject : lNear) {

		//���� lock
		lock();

		//viewlist�� ������ 
		if (false == FindViewList_OBJ(pObject)) {
			//viewlist�� �߰�
			PutViewList_OBJ(pObject);

			//���� unlock
			unlock();

			//putObj -> ���ο� ��ü�� ���Դٴ� PT ����
			lPutObjects.push_back(pObject);
			//PutObject(pObject);
		}
		else {//viewlist�� ������
			unlock();
		}
	}

	PutObjects(lPutObjects);


	std::list<CDynamicObject*> lRemovedObject;
	//viewlist�� �ִ� ��� ��ü�� ����

	for (CDynamicObject* pObject : m_lView_OBJ) {


		pObject->lock();
		auto i = find_if(lNear.begin(), lNear.end(), [pObject](CDynamicObject* pnear) {
			return (pObject->GetID() == pnear->GetID());
		});

		pObject->unlock();

		//near�� ������ 
		if (i == lNear.end()) {
			//removedIDlist�� �߰�
			lRemovedObject.push_back(pObject);
			//PutRemovedIDList(pPlayer);
		}

	}

	//RemovedIDlist�� ��� ��ü�� ����
	for (auto i : lRemovedObject) {
		//viewlist���� ����
		lock();
		RemoveViewList_OBJ(i);

		unlock();

	}

	if (0 != lRemovedObject.size()) {
		lock();
		//�� removeObj(���)
		this->RemoveObjects(lRemovedObject);
		unlock();
	}

}



void CPlayer::ProcView_PLAYER(std::list<CPlayer*>& lNear) {

	//viewlist <id������ �̷���� list> �˻�

	//std::list<CPlayer*> lPutPlayers;

	//near�� ��� ��ü�� ���ؼ�
	for (auto pPlayer : lNear) {

		//���� lock
		lock();

		//viewlist�� ������ 
		if (false == FindViewList_PLAYER(pPlayer)) {
			//viewlist�� �߰�
			PutViewList_PLAYER(pPlayer);

			//���� unlock
			unlock();

			//putObj -> ���ο� ��ü�� ���Դٴ� PT ����
			//lPutPlayers.push_back(pPlayer);
			PutPlayer(pPlayer);


			//��� viewlist�� �ִٸ�
			pPlayer->lock();
			if (pPlayer->FindViewList_PLAYER(this)) {
				pPlayer->unlock();
				//����� MoveObj(��) ����
				pPlayer->ChangeStatePlayer(this);
			}
			else {//��� viewlist�� ������

				  //��� viewlist�� �߰�
				pPlayer->PutViewList_PLAYER(this);
				//��� putObj(��)
				pPlayer->PutPlayer(this);
				pPlayer->unlock();
			}
		}
		else {//viewlist�� ������
			unlock();


			pPlayer->lock();
			if (pPlayer->FindViewList_PLAYER(this)) {//��� viewlist�� ������
				pPlayer->unlock();
				pPlayer->ChangeStatePlayer(this);
			}
			else {//������
				  //��� viewlist�� �߰�
				pPlayer->PutViewList_PLAYER(this);
				//��� PutObj(��)
				pPlayer->PutPlayer(this);
				pPlayer->unlock();
			}
		}
	}

	//PutObjects(lPutPlayers);

	std::list<CPlayer*> lRemovedPlayer;
	//viewlist�� �ִ� ��� ��ü�� ����
	for (CPlayer* pPlayer : m_lView_PLAYER) {


		pPlayer->lock();
		auto i = find_if(lNear.begin(), lNear.end(), [pPlayer](CPlayer* pnear) {
			return (pPlayer->GetID() == pnear->GetID());
		});

		pPlayer->unlock();

		//near�� ������ 
		if (i == lNear.end()) {
			//removedIDlist�� �߰�
			lRemovedPlayer.push_back(pPlayer);
			//PutRemovedIDList(pPlayer);
		}

	}

	//RemovedIDlist�� ��� ��ü�� ����
	for (auto i : lRemovedPlayer) {
		//viewlist���� ����
		lock();
		RemoveViewList_PLAYER(i);
		//�� removeObj(���)
		this->RemovePlayer(i);
		unlock();

		//��� viewlist�� ������
		i->lock();
		if (i->FindViewList_PLAYER(this)) {
			//��� viewlist���� ����
			i->RemoveViewList_PLAYER(this);

			//��� RemoveObj ��
			i->RemovePlayer(this);

			i->unlock();
		}
		else {
			i->unlock();
		}

	}
}
//view list
//pObject ã��
BOOL CPlayer::FindViewList_OBJ(CDynamicObject* pObject) {

	//viewlist <pObject������ �̷���� list> �˻�
	std::list<CDynamicObject*>::iterator i = std::find_if(m_lView_OBJ.begin(), m_lView_OBJ.end(), [pObject](CDynamicObject* pview) {
		return pObject->GetID() == pview->GetID();
	});
	//ã������ true


	if (i != m_lView_OBJ.end()) return TRUE;

	//�ƴϸ� false
	return FALSE;
}
//�ֱ�
BOOL CPlayer::PutViewList_OBJ(CDynamicObject* pObject) {

	m_lView_OBJ.push_back(pObject);

	return TRUE;
}
//�����
BOOL CPlayer::RemoveViewList_OBJ(CDynamicObject* pObject) {

	//���� ���� �ִٸ� ����
	m_lView_OBJ.remove_if([pObject](CDynamicObject* pview) {
		return pObject->GetID() == pview->GetID();
	});

	return TRUE;
}
BOOL CPlayer::ClearViewList_OBJ() {
	//for (auto i : m_lView_OBJ) {
	//	//��� ��ü�鿡�� ���� �����.
	//	i->RemoveViewList(this);
	//}

	//���� ���� �丮��Ʈ _oBJ�� �����.
	m_lView_OBJ.clear();

	return TRUE;
}
//view list


//player view list
//pObject ã��
BOOL CPlayer::FindViewList_PLAYER(CPlayer* pPlayer) {

	//viewlist <pObject������ �̷���� list> �˻�
	std::list<CPlayer*>::iterator i = std::find_if(m_lView_PLAYER.begin(), m_lView_PLAYER.end(), [pPlayer](CPlayer* pview) {
		return pPlayer->GetID() == pview->GetID();
	});
	//ã������ true


	if (i != m_lView_PLAYER.end()) return TRUE;

	//�ƴϸ� false
	return FALSE;
}
//�ֱ�
BOOL CPlayer::PutViewList_PLAYER(CPlayer* pPlayer) {

	m_lView_PLAYER.push_back(pPlayer);

	return TRUE;
}
//�����
BOOL CPlayer::RemoveViewList_PLAYER(CPlayer* pPlayer) {

	//���� ���� �ִٸ� ����
	m_lView_PLAYER.remove_if([pPlayer](CPlayer* pview) {
		return pPlayer->GetID() == pview->GetID();
	});

	return TRUE;
}
BOOL CPlayer::ClearViewList_PLAYER() {
	for (auto i : m_lView_PLAYER) {
		i->lock();
		//��� ��ü�鿡�� ���� �����.
		i->RemoveViewList_PLAYER(this);
		i->RemovePlayer(this);

		i->unlock();
	}

	//���� ���� �丮��Ʈ _oBJ�� �����.
	m_lView_PLAYER.clear();

	return TRUE;
}
//player view list



//CPlayer ����, �Ҹ���

CPlayer::CPlayer(CConnectedSession* pConnectedSession) : CRegionObject() {

	m_eObjTag = PLAYER;

	m_pConnectedSession = pConnectedSession;


	//���콺 ó���� �ϱ����� �߰��� �ڵ�
	m_d3dxvPosition = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_d3dxvRight = XMFLOAT3(1.0f, 0.0f, 0.0f);
	m_d3dxvUp = XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_d3dxvLook = XMFLOAT3(0.0f, 0.0f, 1.0f);

	m_d3dxvVelocity = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_d3dxvGravity = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_fMaxVelocityXZ = 0.0f;
	m_fMaxVelocityY = 0.0f;
	m_fFriction = 0.0f;


	m_fPitch = 0.0f;
	m_fRoll = 0.0f;
	m_fYaw = 0.0f;

	m_dwMousebutton = 0;
	m_dwDirection = 0;

	m_BoundingSphere.Radius = PLAYER_RADIUS;
}

CPlayer::~CPlayer() {

}