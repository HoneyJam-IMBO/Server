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
	if (pSpace) {//pSpace�� �ִٸ�
		m_pSpace = pSpace;
	}

}
//space Set Getter
bool CSpaceObject::Animate(float fTimeElapsed) {
	return true;
}

//CSpaceObject ����, �Ҹ���
CSpaceObject::CSpaceObject() : CGameObject() {
	m_pSpace = nullptr;
}
CSpaceObject::~CSpaceObject() {
	//���� m_pSpace�� delete���� �ʴ���. space_controller���� delete���� ����
}
//CSpaceObject ����, �Ҹ���

