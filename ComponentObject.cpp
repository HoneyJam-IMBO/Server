#include "stdafx.h"
#include "ComponentObject.h"

BOOL CComponentObject::Begin(){
	XMStoreFloat4x4(&m_xmf4x4World, XMMatrixIdentity());

	//자신의 이름 virtual이 내가 생각하는게 맞다면 맨 밑에서 여기까지 올라와서 이거도 실행하니까 결국 id가 항상 END일꺼임
	//그래서 지움 나중에 필요하면 넣고
	//m_ID = OBJECTID_END;

	return TRUE;
}
BOOL CComponentObject::End(){

	ClearComponents();

	return TRUE;
}

void CComponentObject::Update(float fTimeelapsed){

	//모든 컴포넌트를 돌면서 Update실행
	for (auto i : m_mapComponents){
		i.second->Update(fTimeelapsed);
	}
}

//자신의 위치나 방향을 바꾸는 함수들
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
//자신의 위치나 방향을 바꾸는 함수들


//Component관련 함수
//Component Set
BOOL CComponentObject::SetComponent(CComponentBase* pComponenet){
	if (!pComponenet) return FALSE;

	//component id검사 이상한 id이면 패스
	//LATER 0414 family검사도 해줘야 함.
	for (int i = 0; i < COMPONENTID_END; ++i){
		if (i == pComponenet->GetID()){
			for (auto i : m_mapComponents){
				//family id가 같은것이 있다면 안넣어 줌
				if (i.second->GetFamilyID() == pComponenet->GetFamilyID())
					return FALSE;
			}

			//최종적으로 검사 다 끝나면 넣어줌
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

	//자신의 이름
	m_ID = OBJECTID_END;
}
CComponentObject::~CComponentObject(){

}
