#include "stdafx.h"
#include "Player.h"


/////////////////////////player
/////////////////////////player

void CPlayer::Begin() {

	m_eObjTag = PLAYER;

	//마우스 처리를 하기위해 추가된 코드
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
	//지역에서 빼줌
	if (m_pRegion) m_pRegion->DeletePlayer(m_pConnectedSession);

	//나의 뷰리스트 후처리 cl
	ClearViewList_OBJ();
	ClearViewList_PLAYER();

	//ID재설정
	SetID();

	//마우스 처리를 하기위해 추가된 코드
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
	//0412 마우스 버튼입력처리를 위한 변수
	m_dwMousebutton = 0;
}
//CPlayer 생성, 소멸자
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
	//서버 >>?
	float fPlayerSpeed = PLAYER_SPEED;
	//서버
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

	//LATER 0404 여기에 Move를 추가 한다. dwDirection을 이용한 Move를.
	//받은 Direction을 가지고 플레이어를 렌더한다. 
	//서버
	if ((m_dwDirection != 0))
	{
		Move(m_dwDirection, fPlayerSpeed*fTimeElapsed, false);
		//std::cout <<"Player Update Func : POS - "<< m_d3dxvPosition.x << ", " << m_d3dxvPosition.y << ", " << m_d3dxvPosition.z << std::endl;
	}
	//서버
	//서버

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

	//처음 정보 줄 때 필요한 애들 다 여기서 준다. 
	//방향 속도 위치 회전정도 회전속도 회전축 타입 etc.
	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };

	//CLog::WriteLog(_T("PutObj"));
	//std::cout << pObj->GetID() << "가 " << GetID() << "에게" << std::endl;

	XMFLOAT3 xmfPos;
	XMStoreFloat3(&xmfPos, pObj->GetPosition());

	XMFLOAT3 xmfDir;
	XMStoreFloat3(&xmfDir, pObj->GetMovingDir());


	return WritePacket(PT_PUT_OBJ_SC, Packet, WRITE_PT_PUT_OBJ_SC(Packet, pObj->GetID(), pObj->GetTag(), xmfPos.x, xmfPos.y, xmfPos.z
		, xmfDir.x, xmfDir.y, xmfDir.z,
		pObj->GetSpeed(), pObj->GetAccSpeed()));

}


BOOL CPlayer::PutObjects(std::list<CDynamicObject*>& lPutObjects) {

	//처음 정보 줄 때 필요한 애들 다 여기서 준다. 
	//방향 속도 위치 회전정도 회전속도 회전축 타입 etc.
	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };

	//CLog::WriteLog(_T("PutObj"));
	//std::cout << pObj->GetID() << "가 " << GetID() << "에게" << std::endl;
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

	//정보 수집
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
			//카운트가 50개를 넘어가면 
			WritePacket(PT_PUT_OBJS_SC, Packet, WRITE_PT_PUT_OBJS_SC(Packet, count, ID, TAG, POSX, POSY, POSZ
				, DIRX, DIRY, DIRZ,
				SPD, ACCSPD));
			//일단 보낸 후 
			std::cout << count << std::endl;
			count = 0;
			//카운트 초기화
		}
	}
	if (0 != count) {
		//마지막으로 남은 것 보내기
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
	//std::cout << pObj->GetID() << "가 " << GetID() << "에게" << std::endl;
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
	//std::cout << pObj->GetID() << "가 " << GetID() << "에게" << std::endl;

	return WritePacket(PT_REMOVE_OBJ_SC, Packet, WRITE_PT_REMOVE_OBJ_SC(Packet, pObj->GetID(), pObj->GetTag()));

}
BOOL CPlayer::ChangeStateObject(CDynamicObject* pObj) {

	//나중에 state추가하고 여기 추가.
	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };

	XMFLOAT3 xmfPos;
	XMStoreFloat3(&xmfPos, pObj->GetPosition());


	XMFLOAT3 xmfDir;
	XMStoreFloat3(&xmfDir, pObj->GetMovingDir());


	//CLog::WriteLog(_T("MoveObj"));
	//std::cout << pObj->GetID() << "가 " << GetID() << "에게" << std::endl;
	return WritePacket(PT_CHANGE_STATE_OBJ_SC, Packet, WRITE_PT_CHANGE_STATE_OBJ_SC(Packet, pObj->GetID(), pObj->GetTag(),
		00/*pObj->GetState()*/, xmfPos.x, xmfPos.y, xmfPos.z,
		xmfDir.x, xmfDir.y, xmfDir.z,
		pObj->GetSpeed(), pObj->GetAccSpeed()));

}

BOOL CPlayer::PutPlayer(CPlayer* pPlayer) {

	//처음 정보 줄 때 필요한 애들 다 여기서 준다. 
	//방향 속도 위치 회전정도 회전속도 회전축 타입 etc.
	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };

	CLog::WriteLog(_T("PutPlayer"));
	std::cout << pPlayer->GetID() << "가 " << GetID() << "에게" << std::endl;

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
	std::cout << pPlayer->GetID() << "가 " << GetID() << "에게" << std::endl;


	return WritePacket(PT_REMOVE_PLAYER_SC, Packet, WRITE_PT_REMOVE_PLAYER_SC(Packet, pPlayer->GetID()));


}
BOOL CPlayer::ChangeStatePlayer(CPlayer* pPlayer) {

	//나중에 state추가하고 여기 추가.
	BYTE Packet[MAX_BUFFER_LENGTH] = { 0, };

	XMFLOAT3 xmfPos;
	XMStoreFloat3(&xmfPos, pPlayer->GetPosition());

	CLog::WriteLog(_T("ChangeStatePlayer"));
	std::cout << pPlayer->GetID() << "가 " << GetID() << "에게" << std::endl;

	return WritePacket(PT_CHANGE_STATE_PLAYER_SC, Packet, WRITE_PT_CHANGE_STATE_PLAYER_SC(Packet, pPlayer->GetID()
		, 00/*pObj->GetState()*/, xmfPos.x, xmfPos.y, xmfPos.z));

}

//시야처리
//lock처리
//lock처리
//lock처리
//lock처리
void CPlayer::ProcView_OBJ(std::list<CDynamicObject*>& lNear) {

	//viewlist <id정보로 이루어진 list> 검색

	std::list<CDynamicObject*> lPutObjects;

	//near의 모든 객체에 대해서
	for (auto pObject : lNear) {

		//내꺼 lock
		lock();

		//viewlist에 없으면 
		if (false == FindViewList_OBJ(pObject)) {
			//viewlist에 추가
			PutViewList_OBJ(pObject);

			//내꺼 unlock
			unlock();

			//putObj -> 새로운 객체가 들어왔다는 PT 생성
			lPutObjects.push_back(pObject);
			//PutObject(pObject);
		}
		else {//viewlist에 있으면
			unlock();
		}
	}

	PutObjects(lPutObjects);


	std::list<CDynamicObject*> lRemovedObject;
	//viewlist에 있는 모든 객체에 대해

	for (CDynamicObject* pObject : m_lView_OBJ) {


		pObject->lock();
		auto i = find_if(lNear.begin(), lNear.end(), [pObject](CDynamicObject* pnear) {
			return (pObject->GetID() == pnear->GetID());
		});

		pObject->unlock();

		//near에 없으면 
		if (i == lNear.end()) {
			//removedIDlist에 추가
			lRemovedObject.push_back(pObject);
			//PutRemovedIDList(pPlayer);
		}

	}

	//RemovedIDlist의 모든 객체에 대해
	for (auto i : lRemovedObject) {
		//viewlist에서 제거
		lock();
		RemoveViewList_OBJ(i);

		unlock();

	}

	if (0 != lRemovedObject.size()) {
		lock();
		//나 removeObj(상대)
		this->RemoveObjects(lRemovedObject);
		unlock();
	}

}



void CPlayer::ProcView_PLAYER(std::list<CPlayer*>& lNear) {

	//viewlist <id정보로 이루어진 list> 검색

	//std::list<CPlayer*> lPutPlayers;

	//near의 모든 객체에 대해서
	for (auto pPlayer : lNear) {

		//내꺼 lock
		lock();

		//viewlist에 없으면 
		if (false == FindViewList_PLAYER(pPlayer)) {
			//viewlist에 추가
			PutViewList_PLAYER(pPlayer);

			//내꺼 unlock
			unlock();

			//putObj -> 새로운 객체가 들어왔다는 PT 생성
			//lPutPlayers.push_back(pPlayer);
			PutPlayer(pPlayer);


			//상대 viewlist에 있다면
			pPlayer->lock();
			if (pPlayer->FindViewList_PLAYER(this)) {
				pPlayer->unlock();
				//상대의 MoveObj(나) 실행
				pPlayer->ChangeStatePlayer(this);
			}
			else {//상대 viewlist에 없으면

				  //상대 viewlist에 추가
				pPlayer->PutViewList_PLAYER(this);
				//상대 putObj(나)
				pPlayer->PutPlayer(this);
				pPlayer->unlock();
			}
		}
		else {//viewlist에 있으면
			unlock();


			pPlayer->lock();
			if (pPlayer->FindViewList_PLAYER(this)) {//상대 viewlist에 있으면
				pPlayer->unlock();
				pPlayer->ChangeStatePlayer(this);
			}
			else {//없으면
				  //상대 viewlist에 추가
				pPlayer->PutViewList_PLAYER(this);
				//상대 PutObj(나)
				pPlayer->PutPlayer(this);
				pPlayer->unlock();
			}
		}
	}

	//PutObjects(lPutPlayers);

	std::list<CPlayer*> lRemovedPlayer;
	//viewlist에 있는 모든 객체에 대해
	for (CPlayer* pPlayer : m_lView_PLAYER) {


		pPlayer->lock();
		auto i = find_if(lNear.begin(), lNear.end(), [pPlayer](CPlayer* pnear) {
			return (pPlayer->GetID() == pnear->GetID());
		});

		pPlayer->unlock();

		//near에 없으면 
		if (i == lNear.end()) {
			//removedIDlist에 추가
			lRemovedPlayer.push_back(pPlayer);
			//PutRemovedIDList(pPlayer);
		}

	}

	//RemovedIDlist의 모든 객체에 대해
	for (auto i : lRemovedPlayer) {
		//viewlist에서 제거
		lock();
		RemoveViewList_PLAYER(i);
		//나 removeObj(상대)
		this->RemovePlayer(i);
		unlock();

		//상대 viewlist에 있으면
		i->lock();
		if (i->FindViewList_PLAYER(this)) {
			//상대 viewlist에서 제거
			i->RemoveViewList_PLAYER(this);

			//상대 RemoveObj 나
			i->RemovePlayer(this);

			i->unlock();
		}
		else {
			i->unlock();
		}

	}
}
//view list
//pObject 찾기
BOOL CPlayer::FindViewList_OBJ(CDynamicObject* pObject) {

	//viewlist <pObject정보로 이루어진 list> 검색
	std::list<CDynamicObject*>::iterator i = std::find_if(m_lView_OBJ.begin(), m_lView_OBJ.end(), [pObject](CDynamicObject* pview) {
		return pObject->GetID() == pview->GetID();
	});
	//찾았으면 true


	if (i != m_lView_OBJ.end()) return TRUE;

	//아니면 false
	return FALSE;
}
//넣기
BOOL CPlayer::PutViewList_OBJ(CDynamicObject* pObject) {

	m_lView_OBJ.push_back(pObject);

	return TRUE;
}
//지우기
BOOL CPlayer::RemoveViewList_OBJ(CDynamicObject* pObject) {

	//같은 값이 있다면 지움
	m_lView_OBJ.remove_if([pObject](CDynamicObject* pview) {
		return pObject->GetID() == pview->GetID();
	});

	return TRUE;
}
BOOL CPlayer::ClearViewList_OBJ() {
	//for (auto i : m_lView_OBJ) {
	//	//모든 객체들에게 나를 지운다.
	//	i->RemoveViewList(this);
	//}

	//그후 나의 뷰리스트 _oBJ를 지운다.
	m_lView_OBJ.clear();

	return TRUE;
}
//view list


//player view list
//pObject 찾기
BOOL CPlayer::FindViewList_PLAYER(CPlayer* pPlayer) {

	//viewlist <pObject정보로 이루어진 list> 검색
	std::list<CPlayer*>::iterator i = std::find_if(m_lView_PLAYER.begin(), m_lView_PLAYER.end(), [pPlayer](CPlayer* pview) {
		return pPlayer->GetID() == pview->GetID();
	});
	//찾았으면 true


	if (i != m_lView_PLAYER.end()) return TRUE;

	//아니면 false
	return FALSE;
}
//넣기
BOOL CPlayer::PutViewList_PLAYER(CPlayer* pPlayer) {

	m_lView_PLAYER.push_back(pPlayer);

	return TRUE;
}
//지우기
BOOL CPlayer::RemoveViewList_PLAYER(CPlayer* pPlayer) {

	//같은 값이 있다면 지움
	m_lView_PLAYER.remove_if([pPlayer](CPlayer* pview) {
		return pPlayer->GetID() == pview->GetID();
	});

	return TRUE;
}
BOOL CPlayer::ClearViewList_PLAYER() {
	for (auto i : m_lView_PLAYER) {
		i->lock();
		//모든 객체들에게 나를 지운다.
		i->RemoveViewList_PLAYER(this);
		i->RemovePlayer(this);

		i->unlock();
	}

	//그후 나의 뷰리스트 _oBJ를 지운다.
	m_lView_PLAYER.clear();

	return TRUE;
}
//player view list



//CPlayer 생성, 소멸자

CPlayer::CPlayer(CConnectedSession* pConnectedSession) : CRegionObject() {

	m_eObjTag = PLAYER;

	m_pConnectedSession = pConnectedSession;


	//마우스 처리를 하기위해 추가된 코드
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