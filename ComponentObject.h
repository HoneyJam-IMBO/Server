#pragma once
#include "Componenet.h"

enum object_id {
	
	OBJECTID_END
};
typedef std::pair<component_id, CComponentBase*> pairComponent;
typedef std::map<component_id, CComponentBase*> mapComponent;


class CComponentObject{
	virtual BOOL Begin();
	virtual BOOL End();

	//컴포넌트와 자신의 로직실행
	void Update(float elapsedTime);

	//자신의 위치나 방향을 바꾸는 함수들
//	void SetPosition(const XMVECTOR& d3dxvPosition);
//	void SetPosition(float xPosition, float yPosition, float zPosition);
//	XMVECTOR GetPosition();

//	void Rotate(const XMVECTOR* pd3dxvAxis, float fAngle);
//	void Rotate(float fPitch, float fYaw, float fRoll);
//	//자신의 위치나 방향을 바꾸는 함수들

	//자신의 id반환
	const object_id GetID() const { return m_ID; }
	
	//Component관련 함수
	//Component Set
	BOOL SetComponent(CComponentBase* pComponenet);
	
	//Get
	CComponentBase* GetComponenet(const component_id& componenetID);
	const CComponentBase* GetComponenet(const component_id& componenetID)const;

	//Clear
	void ClearComponents();
private:
//	XMFLOAT4X4 m_xmf4x4World;

	//자신의 이름
	object_id m_ID;

	mapComponent	m_mapComponents;

public:
	CComponentObject();
	virtual ~CComponentObject();
};