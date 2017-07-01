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
//	//0412 �÷��̾��� ���콺 ��ư�Է� ó���� ���� �Լ�
//	void SetdwMouseButton(DWORD dwMousebutton) { m_dwMousebutton = dwMousebutton; }
//	DWORD GetdwMouseButton() { return m_dwMousebutton; }
//	//0412 �÷��̾��� ���콺 ��ư�Է� ó���� ���� �Լ�
//
//	XMVECTOR GetPlayerPosition() { return XMLoadFloat3(&m_d3dxvPosition); }
//	XMVECTOR GetPlayerRight() { return XMLoadFloat3(&m_d3dxvRight); }
//	XMVECTOR GetPlayerUp() { return XMLoadFloat3(&m_d3dxvUp); }
//	XMVECTOR GetPlayerLook() { return XMLoadFloat3(&m_d3dxvLook); }
//	//���� �ۼ��� get set
//	void SetConnectedSession(CConnectedSession* pConnectedSession) { m_pConnectedSession = pConnectedSession; }
//	CConnectedSession* GetConnectedSession() { return m_pConnectedSession; }
//
//	void SetPlayerPosition(XMVECTOR xmPosition) { XMStoreFloat3(&m_d3dxvPosition, xmPosition); }
//
//	//Ŭ�󿡼� ���� ���콺 �������� ������ 
//	//�÷��̾��� �������� ó���ϱ� ���� �Լ� 
//	void Rotate(float x, float y, float z);
//
//	void Move(DWORD nDirection, float fDistance, bool bVelocity = false);
//	void Move(const XMVECTOR& d3dxvShift, bool bVelocity = false);
//
//	void Update(float fTimeElapsed);
//	//void Move(float fxOffset = 0.0f, float fyOffset = 0.0f, float fzOffset = 0.0f);
//
//	//���̴� ��ü ���� �Լ�
//	BOOL WritePacket(DWORD dwProtocol, BYTE* Packet, DWORD dwPacketLength);
//
//	BOOL PutObject(CDynamicObject* pObj);
//	//���Ƽ� �ѹ��� ������ �Լ�
//	BOOL PutObjects(std::list<CDynamicObject*>& lPutObjects);
//
//	BOOL RemoveObject(CDynamicObject* pObj);
//	//���Ƽ� �ѹ��� ������ �Լ�
//	BOOL RemoveObjects(std::list<CDynamicObject*> lRemoveObject);
//
//	BOOL ChangeStateObject(CDynamicObject* pObj);
//
//	//���̴� �÷��̾� ���� �Լ�
//	BOOL PutPlayer(CPlayer* pPlayer);
//	BOOL RemovePlayer(CPlayer* pPlayer);
//	BOOL ChangeStatePlayer(CPlayer* pPlayer);
//
//
//	//�þ�ó�� 
//	void ProcView_OBJ(std::list<CDynamicObject*>& lNear);
//	void ProcView_PLAYER(std::list<CPlayer*>& lNear);
//
//	//view list
//	//id ã��
//	BOOL FindViewList_OBJ(CDynamicObject* pObject);
//	//�ֱ�
//	BOOL PutViewList_OBJ(CDynamicObject* pObject);
//	//�����
//	BOOL RemoveViewList_OBJ(CDynamicObject* pObject);
//
//	//Ŭ����
//	BOOL ClearViewList_OBJ();
//	//view list
//
//
//	//player view list
//	//id ã��
//	BOOL FindViewList_PLAYER(CPlayer* pPlayer);
//	//�ֱ�
//	BOOL PutViewList_PLAYER(CPlayer* pPlayer);
//	//�����
//	BOOL RemoveViewList_PLAYER(CPlayer* pPlayer);
//
//	//Ŭ����
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
//	//�÷��̾��� Ű �Է� ó���� ���� ����
//	DWORD m_dwDirection;
//
//	//0412 �÷��̾��� ���콺 ��ưó���� ���� ����
//	DWORD m_dwMousebutton;
//
//
//	float           			m_fPitch;
//	float           			m_fYaw;
//	float           			m_fRoll;
//
//	//�÷��̾� ������
//	XMFLOAT3					m_d3dxvPosition;
//	XMFLOAT3					m_d3dxvRight;
//	XMFLOAT3					m_d3dxvUp;
//	XMFLOAT3					m_d3dxvLook;
//
//	//���� �ۼ����� ���� ����
//	CConnectedSession* m_pConnectedSession;
//
//	//�þ� ó���� ���� ����Ʈ
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