#pragma once
//#include "Object.h"
#include "DynamicObject.h"

#include "RegionObject.h"




#define DIR_FORWARD				0x01
#define DIR_BACKWARD			0x02
#define DIR_LEFT				0x04
#define DIR_RIGHT				0x08
#define DIR_UP					0x10
#define DIR_DOWN				0x20



//class CPlayer :public CRegionObject {
//public:
//	virtual void Begin();
//	virtual void End();
//	virtual bool Animate(float fTimeElapsed) { return true; };
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
//private:
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
//
//
//