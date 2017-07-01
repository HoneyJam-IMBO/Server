#pragma once
#include "SpaceObject.h"



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