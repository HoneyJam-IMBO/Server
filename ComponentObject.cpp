#include "stdafx.h"
#include "ComponentObject.h"

BOOL CComponentObject::Begin(){
	XMStoreFloat4x4(&m_xmf4x4World, XMMatrixIdentity());

	//�ڽ��� �̸� virtual�� ���� �����ϴ°� �´ٸ� �� �ؿ��� ������� �ö�ͼ� �̰ŵ� �����ϴϱ� �ᱹ id�� �׻� END�ϲ���
	//�׷��� ���� ���߿� �ʿ��ϸ� �ְ�
	//m_ID = OBJECTID_END;

	return TRUE;
}
BOOL CComponentObject::End(){

	ClearComponents();

	return TRUE;
}

void CComponentObject::Update(float fTimeelapsed){

	//��� ������Ʈ�� ���鼭 Update����
	for (auto i : m_mapComponents){
		i.second->Update(fTimeelapsed);
	}
}

//�ڽ��� ��ġ�� ������ �ٲٴ� �Լ���
void CComponentObject::SetPosition(const XMVECTOR& d3dxvPosition){
	XMFLOAT3 xmfPosition;
	XMStoreFloat3(&xmfPosition, d3dxvPosition);
	SetPosition(xmfPosition.x, xmfPosition.y, xmfPosition.z);
}
void CComponentObject::SetPosition(float xPosition, float yPosition, float zPosition){
	m_xmf4x4World._41 = xPosition;
	m_xmf4x4World._42 = yPosition;
	m_xmf4x4World._43 = zPosition;
}
XMVECTOR CComponentObject::GetPosition(){
	return XMVectorSet(m_xmf4x4World._41, m_xmf4x4World._42, m_xmf4x4World._43, 0.0f);
}

void CComponentObject::Rotate(const XMVECTOR* pd3dxvAxis, float fAngle){
	XMMATRIX mtxRotate;
	mtxRotate = XMMatrixRotationAxis(*pd3dxvAxis, XMConvertToRadians(fAngle));
	XMStoreFloat4x4(&m_xmf4x4World, mtxRotate * XMLoadFloat4x4(&m_xmf4x4World));
}
void CComponentObject::Rotate(float fPitch, float fYaw, float fRoll){
	XMMATRIX mtxRotate;
	mtxRotate = XMMatrixRotationRollPitchYaw(XMConvertToRadians(fPitch),
		XMConvertToRadians(fYaw), XMConvertToRadians(fRoll));
	XMStoreFloat4x4(&m_xmf4x4World, mtxRotate * XMLoadFloat4x4(&m_xmf4x4World));

}
//�ڽ��� ��ġ�� ������ �ٲٴ� �Լ���


//Component���� �Լ�
//Component Set
BOOL CComponentObject::SetComponent(CComponentBase* pComponenet){
	if (!pComponenet) return FALSE;

	//component id�˻� �̻��� id�̸� �н�
	//LATER 0414 family�˻絵 ����� ��.
	for (int i = 0; i < COMPONENTID_END; ++i){
		if (i == pComponenet->GetID()){
			for (auto i : m_mapComponents){
				//family id�� �������� �ִٸ� �ȳ־� ��
				if (i.second->GetFamilyID() == pComponenet->GetFamilyID())
					return FALSE;
			}

			//���������� �˻� �� ������ �־���
			m_mapComponents.insert(pairComponent(pComponenet->GetID(), pComponenet));
			return TRUE;
		}
	}

	return FALSE;
}

//Get
CComponentBase* CComponentObject::GetComponenet(const component_id& componenetID){
	mapComponent::const_iterator  find_iterator = m_mapComponents.find(componenetID);
	return find_iterator->second;
}
const CComponentBase* CComponentObject::GetComponenet(const component_id& componenetID)const{
	mapComponent::const_iterator  find_iterator =  m_mapComponents.find(componenetID);
	return find_iterator->second;
}

//Clear
void CComponentObject::ClearComponents(){
	m_mapComponents.clear();
}

	
CComponentObject::CComponentObject(){
	XMStoreFloat4x4(&m_xmf4x4World, XMMatrixIdentity());

	//�ڽ��� �̸�
	m_ID = OBJECTID_END;
}
CComponentObject::~CComponentObject(){

}
