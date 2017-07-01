#include "stdafx.h"
#include "SpaceObject.h"



/////////////space
/////////////space

void CSpaceObject::Begin() {

	CGameObject::Begin();
}
void CSpaceObject::End() {
	m_pSpace = nullptr;
}

//space Set Getter
CSpace* CSpaceObject::GetSpace() {

	return m_pSpace;

}
void CSpaceObject::SetSpace(CSpace* pSpace) {
	if (pSpace) {//pSpace가 있다면
		m_pSpace = pSpace;
	}

}
//space Set Getter
bool CSpaceObject::Animate(float fTimeElapsed) {
	return true;
}

//CSpaceObject 생성, 소멸자
CSpaceObject::CSpaceObject() : CGameObject() {
	m_pSpace = nullptr;
}
CSpaceObject::~CSpaceObject() {
	//굳이 m_pSpace를 delete하지 않느다. space_controller에서 delete해줄 것임
}
//CSpaceObject 생성, 소멸자

