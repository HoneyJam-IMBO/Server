#include "stdafx.h"
#include "RegionObject.h"


/////////////////////////region
/////////////////////////region

void CRegionObject::Begin() {

	CGameObject::Begin();
}
void CRegionObject::End() {
	m_pRegion = nullptr;
}

bool CRegionObject::Animate(float fTimeElapsed) {
	return true;
}

//Set Getter
CRegion* CRegionObject::GetRegion() {

	return m_pRegion;

}
void CRegionObject::SetRegion(CRegion * pRegion) {
	if (pRegion) {//pRegion가 있다면
		m_pRegion = pRegion;
	}

}
//Set Getter



//생성, 소멸자
CRegionObject::CRegionObject() : CGameObject() {
	m_pRegion = nullptr;
}
CRegionObject::~CRegionObject() {

}
