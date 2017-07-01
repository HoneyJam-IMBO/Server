#include "stdafx.h"
#include "Componenet.h"

BOOL CComponentBase::Begin() {
	
	return TRUE;
};

BOOL CComponentBase::End() {
	//������Ʈ id
	m_ID = COMPONENTID_END;

	//���� ������ ������Ʈ�� ��Ƴ��� �йи� id
	//ex) geometry ����� render�� �׳� render
	m_FamilyID = FAMILYID_END;

	//�ڽ��� ������
	m_pOwner = NULL;

	return TRUE;
};

void CComponentBase::SetOwner(CComponentObject* pObject){
	if (!pObject)return;

	//������ ������ ���������� �Ű澲�� �ʴ´�.
	m_pOwner = pObject;
}

CComponentBase::CComponentBase(){
	//������Ʈ id
	m_ID = COMPONENTID_END;

	//���� ������ ������Ʈ�� ��Ƴ��� �йи� id
	//ex) geometry ����� render�� �׳� render
	m_FamilyID = FAMILYID_END;

	//�ڽ��� ������
	m_pOwner = NULL;
}
CComponentBase::~CComponentBase(){

}