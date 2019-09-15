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

	//������Ʈ�� �ڽ��� ��������
	void Update(float elapsedTime);

	//�ڽ��� ��ġ�� ������ �ٲٴ� �Լ���
//	void SetPosition(const XMVECTOR& d3dxvPosition);
//	void SetPosition(float xPosition, float yPosition, float zPosition);
//	XMVECTOR GetPosition();

//	void Rotate(const XMVECTOR* pd3dxvAxis, float fAngle);
//	void Rotate(float fPitch, float fYaw, float fRoll);
//	//�ڽ��� ��ġ�� ������ �ٲٴ� �Լ���

	//�ڽ��� id��ȯ
	const object_id GetID() const { return m_ID; }
	
	//Component���� �Լ�
	//Component Set
	BOOL SetComponent(CComponentBase* pComponenet);
	
	//Get
	CComponentBase* GetComponenet(const component_id& componenetID);
	const CComponentBase* GetComponenet(const component_id& componenetID)const;

	//Clear
	void ClearComponents();
private:
//	XMFLOAT4X4 m_xmf4x4World;

	//�ڽ��� �̸�
	object_id m_ID;

	mapComponent	m_mapComponents;

public:
	CComponentObject();
	virtual ~CComponentObject();
};