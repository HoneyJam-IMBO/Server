#pragma once
/*
begin, end로직의 시작이며
Animate를 가짐 게임에 있어서 기본적인 움직임을 담당함
Tag와 충동체크, ID부여 까지도 맡음
*/
#include <mutex>

//#include "Region.h"
//#include "Space.h"

class CGameObject {
public:
	virtual void Begin();
	virtual void End();
	void Restart();
	virtual bool Animate(float fTimeElapsed) { return true; };


	void SetPosition(const XMVECTOR& d3dxvPosition);
	void SetPosition(float xPosition, float yPosition, float zPosition);

	XMVECTOR GetLook();
	XMVECTOR GetUp();
	XMVECTOR GetRight();

	void Move(XMVECTOR direction, float distance);

	XMVECTOR GetPosition();

	void Rotate(const XMVECTOR* pd3dxvAxis, float fAngle);
	void Rotate(float fPitch, float fYaw, float fRoll);

	OBJECT_TAG GetTag() { return m_eObjTag; }
	void SetBoundingSphereRadius(float r) { m_BoundingSphere.Radius = r; }
	BoundingSphere GetBoundingSphere() { return m_BoundingSphere; }

	//id
	INT GetNETWORK_ID() { return NETWORK_ID; }
	void SetNETWORK_ID() { NETWORK_ID = StaticIDCounter++; }
	INT GetROOM_ID() { return ROOM_ID; }
	void SetROOM_ID(INT id) { ROOM_ID = id; }
	INT GetSLOT_ID() { return SLOT_ID; }
	void SetSLOT_ID(INT id) { SLOT_ID = id; }
	INT GetCHARACTER() { return CHARACTER; }
	void SetCHARACTER(INT id) { CHARACTER = id; }
	BOOL GetREADY() { return READY; }
	void SetREADY(BOOL b) { READY = b; }

	//lock mutex 함수 
	void lock() { m_Sync.lock(); }
	void unlock() { m_Sync.unlock(); }

	//network
	void SetConnectedSession(CConnectedSession* pConnectedSession) { m_pConnectedSession = pConnectedSession; }
	CConnectedSession* GetConnectedSession() { return m_pConnectedSession; }
private:
	//객체의 고유 id
	INT NETWORK_ID{ -1 };
	INT ROOM_ID{ -1 };
	INT SLOT_ID{ -1 };
	BOOL READY{ false };
	INT CHARACTER{ -1 };
	//DWORD_PTR 은 64비트 unsigned int다.

	static INT StaticIDCounter;
	//mutext 변수 
	std::mutex m_Sync;


protected:
	//정보 송수신을 위한 변수
	CConnectedSession* m_pConnectedSession;

	//충돌 체크
	BoundingSphere m_BoundingSphere;

	//테그
	OBJECT_TAG m_eObjTag;

	XMFLOAT4X4 m_d3dxmtxWorld;
public:
	CGameObject(CConnectedSession* pConnectedSession);
	virtual ~CGameObject();
};

//
//
//
//////////////////////////////region
//////////////////////////////region
//
//class CRegionObject :public CGameObject {
//public:
//	virtual void Begin();
//	virtual void End();
//	virtual bool Animate(float fTimeElapsed);
//
//	//지역객체 고유함수
//	CRegion* GetRegion();
//	void SetRegion(CRegion* pRegion);
//
//	//지역객체 고유함수
//
//protected:
//	CRegion* m_pRegion;
//
//private:
//
//public:
//	CRegionObject();
//	virtual ~CRegionObject();
//};
//
//
//
///////////////////////////////////////////////space
///////////////////////////////////////////////space
//
////이제 공간이 아니라 지역이다.
///*
//주요 기능은 객체에 id를 부여하는 것이다.
//지역에서 활동하는 객체는 이 클래스를 상속받아야 한다.
//*/
//class CSpaceObject :public CGameObject {
//public:
//	virtual void Begin();
//	virtual void End();
//	virtual bool Animate(float fTimeElapsed);
//
//	// 고유함수
//	CSpace* GetSpace();
//	void SetSpace(CSpace* pSpace);
//
//	//고유함수
//
//protected:
//	CSpace* m_pSpace;
//
//private:
//
//public:
//	CSpaceObject();
//	virtual ~CSpaceObject();
//};
//
//
//
//
//////////////////////////////////////////////////dynamic
//////////////////////////////////////////////////dynamic
//
//class CDynamicObject :public CSpaceObject {
//public:
//
//	virtual void Begin();
//	virtual void End();
//	//virtual BOOL WriteEvent();
//	virtual bool Animate(float fTimeElapsed);
//
//
//	//set get
//	void SetRotationAxis(const XMVECTOR& axis) {
//		XMFLOAT4 xmvRotationaxis;
//		XMStoreFloat4(&xmvRotationaxis, axis);
//		m_d3dxvMovingDir.x = xmvRotationaxis.x, m_d3dxvMovingDir.y = xmvRotationaxis.y, m_d3dxvMovingDir.z = xmvRotationaxis.z;
//	}
//	void GetRotationAxis(XMFLOAT3& out) { out = m_d3dxvRotationAxis; }
//
//	void SetRotationSpeed(float rspd) { m_fRotationSpeed = rspd; }
//	float GetRotationSpeed() { return m_fRotationSpeed; }
//
//	void SetMovingDir(const XMVECTOR& mdir) {
//		XMFLOAT4 xmvMovingdir;
//		XMStoreFloat4(&xmvMovingdir, mdir);
//		m_d3dxvMovingDir.x = xmvMovingdir.x, m_d3dxvMovingDir.y = xmvMovingdir.y, m_d3dxvMovingDir.z = xmvMovingdir.z;
//	}
//	XMVECTOR GetMovingDir() { return XMLoadFloat3(&m_d3dxvMovingDir); }
//
//	void SetMovingSpeed(float mspd) { m_fMovingSpeed = mspd; }
//	float GetMovingSpeed() { return m_fMovingSpeed; }
//
//	void SetAccSpeed(float aspd) { m_fAccSpeed = aspd; }
//	float GetAccSpeed() { return m_fAccSpeed; }
//
//	void SetSpeed(float spd) { m_fMovingSpeed = spd; }
//	float GetSpeed() { return m_fMovingSpeed; }
//	//set get
//
//
//private:
//
//	XMFLOAT3 m_d3dxvRotationAxis;;
//	float m_fRotationSpeed;
//
//	XMFLOAT3 m_d3dxvMovingDir;
//	float m_fMovingSpeed;
//	float m_fAccSpeed;
//
//public:
//	CDynamicObject();
//	//CDynamicObject(CServerIocp* pServerIocp);
//	virtual ~CDynamicObject();
//};
//
//
//
///////////////////////////////////////////////////player
///////////////////////////////////////////////////player
//
//
//
//
//#define DIR_FORWARD				0x01
//#define DIR_BACKWARD			0x02
//#define DIR_LEFT				0x04
//#define DIR_RIGHT				0x08
//#define DIR_UP					0x10
//#define DIR_DOWN				0x20
//
//
//
//class CPlayer :public CRegionObject {
//public:
//	virtual void Begin();
//	virtual void End();
//
//	void Restart();
//
//	void SetdwDirection(DWORD dwDirection) { m_dwDirection = dwDirection; }
//	DWORD GetdwDirection() { return m_dwDirection; }
//
//	//0412 플레이어의 마우스 버튼입력 처리를 위한 함수
//	void SetdwMouseButton(DWORD dwMousebutton) { m_dwMousebutton = dwMousebutton; }
//	DWORD GetdwMouseButton() { return m_dwMousebutton; }
//	//0412 플레이어의 마우스 버튼입력 처리를 위한 함수
//
//	XMVECTOR GetPlayerPosition() { return XMLoadFloat3(&m_d3dxvPosition); }
//	XMVECTOR GetPlayerRight() { return XMLoadFloat3(&m_d3dxvRight); }
//	XMVECTOR GetPlayerUp() { return XMLoadFloat3(&m_d3dxvUp); }
//	XMVECTOR GetPlayerLook() { return XMLoadFloat3(&m_d3dxvLook); }
//	//정보 송수신 get set
//	void SetConnectedSession(CConnectedSession* pConnectedSession) { m_pConnectedSession = pConnectedSession; }
//	CConnectedSession* GetConnectedSession() { return m_pConnectedSession; }
//
//	void SetPlayerPosition(XMVECTOR xmPosition) { XMStoreFloat3(&m_d3dxvPosition, xmPosition); }
//
//	//클라에서 보낸 마우스 움직임을 가지고 
//	//플레이어의 움직임을 처리하기 위한 함수 
//	void Rotate(float x, float y, float z);
//
//	void Move(DWORD nDirection, float fDistance, bool bVelocity = false);
//	void Move(const XMVECTOR& d3dxvShift, bool bVelocity = false);
//
//	void Update(float fTimeElapsed);
//	//void Move(float fxOffset = 0.0f, float fyOffset = 0.0f, float fzOffset = 0.0f);
//
//	//보이는 객체 관리 함수
//	BOOL WritePacket(DWORD dwProtocol, BYTE* Packet, DWORD dwPacketLength);
//
//	BOOL PutObject(CDynamicObject* pObj);
//	//몰아서 한번에 보내는 함수
//	BOOL PutObjects(std::list<CDynamicObject*>& lPutObjects);
//
//	BOOL RemoveObject(CDynamicObject* pObj);
//	//몰아서 한번에 보내는 함수
//	BOOL RemoveObjects(std::list<CDynamicObject*> lRemoveObject);
//
//	BOOL ChangeStateObject(CDynamicObject* pObj);
//
//	//보이는 플레이어 관리 함수
//	BOOL PutPlayer(CPlayer* pPlayer);
//	BOOL RemovePlayer(CPlayer* pPlayer);
//	BOOL ChangeStatePlayer(CPlayer* pPlayer);
//
//
//	//시야처리 
//	void ProcView_OBJ(std::list<CDynamicObject*>& lNear);
//	void ProcView_PLAYER(std::list<CPlayer*>& lNear);
//
//	//view list
//	//id 찾기
//	BOOL FindViewList_OBJ(CDynamicObject* pObject);
//	//넣기
//	BOOL PutViewList_OBJ(CDynamicObject* pObject);
//	//지우기
//	BOOL RemoveViewList_OBJ(CDynamicObject* pObject);
//
//	//클리어
//	BOOL ClearViewList_OBJ();
//	//view list
//
//
//	//player view list
//	//id 찾기
//	BOOL FindViewList_PLAYER(CPlayer* pPlayer);
//	//넣기
//	BOOL PutViewList_PLAYER(CPlayer* pPlayer);
//	//지우기
//	BOOL RemoveViewList_PLAYER(CPlayer* pPlayer);
//
//	//클리어
//	BOOL ClearViewList_PLAYER();
//	//player view list
//
//	void SetTeam(int i){ m_Team = i; }
//	int GetTeam() { return m_Team; }
//private:
//	int m_Team;
//
//	XMFLOAT3 m_d3dxvVelocity;
//	XMFLOAT3 m_d3dxvGravity;
//	float m_fMaxVelocityXZ;
//	float m_fMaxVelocityY;
//	float m_fFriction;
//
//	//플레이어의 키 입력 처리를 위한 변수
//	DWORD m_dwDirection;
//
//	//0412 플레이어의 마우스 버튼처리를 위한 변수
//	DWORD m_dwMousebutton;
//
//
//	float           			m_fPitch;
//	float           			m_fYaw;
//	float           			m_fRoll;
//
//	//플레이어 움직임
//	XMFLOAT3					m_d3dxvPosition;
//	XMFLOAT3					m_d3dxvRight;
//	XMFLOAT3					m_d3dxvUp;
//	XMFLOAT3					m_d3dxvLook;
//
//	//정보 송수신을 위한 변수
//	CConnectedSession* m_pConnectedSession;
//
//	//시야 처리를 위한 리스트
//	std::list<CDynamicObject*> m_lView_OBJ;
//
//	std::list<CPlayer*> m_lView_PLAYER;
//public:
//	CPlayer(CConnectedSession* pConnectedSession);
//	virtual ~CPlayer();
//
//};


