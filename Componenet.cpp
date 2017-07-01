#include "stdafx.h"
#include "Componenet.h"

BOOL CComponentBase::Begin() {
	
	return TRUE;
};

BOOL CComponentBase::End() {
	//컴포넌트 id
	m_ID = COMPONENTID_END;

	//같은 종류의 컴포넌트를 모아놓은 패밀리 id
	//ex) geometry 사용한 render와 그냥 render
	m_FamilyID = FAMILYID_END;

	//자신의 소유자
	m_pOwner = NULL;

	return TRUE;
};

void CComponentBase::SetOwner(CComponentObject* pObject){
	if (!pObject)return;

	//이전에 주인이 누구였는지 신경쓰지 않는다.
	m_pOwner = pObject;
}

CComponentBase::CComponentBase(){
	//컴포넌트 id
	m_ID = COMPONENTID_END;

	//같은 종류의 컴포넌트를 모아놓은 패밀리 id
	//ex) geometry 사용한 render와 그냥 render
	m_FamilyID = FAMILYID_END;

	//자신의 소유자
	m_pOwner = NULL;
}
CComponentBase::~CComponentBase(){

}