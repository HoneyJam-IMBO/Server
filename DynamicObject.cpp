#include "stdafx.h"
#include "DynamicObject.h"

//////////////////////////////Dynamic
//////////////////////////////Dynamic

void CDynamicObject::Begin() {

}

void CDynamicObject::End() {

}


bool CDynamicObject::Animate(float fTimeElapsed) {

	//���°� ��ȭ�� �ÿ� TRUE;
	//�Ⱥ������� FALS;
	//default�� FALSE��
	bool flag = false;

	//#ifdef _DEBUG
	//	std::cout << "SPACE �� MOVINGOBJ ANIMATE" << std::endl;
	//#endif

	XMVECTOR pos = GetPosition();
	XMVECTOR vVel = XMLoadFloat3(&XMFLOAT3(m_d3dxvMovingDir.x*m_fMovingSpeed*fTimeElapsed, m_d3dxvMovingDir.y*m_fMovingSpeed*fTimeElapsed, m_d3dxvMovingDir.z*m_fMovingSpeed*fTimeElapsed));
	pos = pos + vVel;
	XMFLOAT3 xmfPos;
	XMStoreFloat3(&xmfPos, pos);


	//if (m_ID == 191){
	//	int i = GetSpace()->GetSpaceNum();
	//	int a = 0;
	//	//////////////////////////////CHECK
	//}
	//std::cout << "id: " << GetID() << " �� ��ġ ";
	//printf("pos: %f, %f, %f \n", xmfPos.x, xmfPos.y, xmfPos.z);
	if (xmfPos.x > MAP_SIZE || xmfPos.y > MAP_SIZE || xmfPos.z > MAP_SIZE || xmfPos.x < 0 || xmfPos.y < 0 || xmfPos.z < 0) {
		//std::cout << "id: " << GetID() << " �� ���� ��ȯ! ";
		//std::cout << "id: " << GetID() << " ���� ��ȯ !!!!!!!!11111 �� ��ġ ";
		//printf("pos: %f, %f, %f \n", xmfPos.x, xmfPos.y, xmfPos.z);
		//printf("pos: %f, %f, %f \n", xmfPos.x, xmfPos.y, xmfPos.z);

		m_d3dxvMovingDir.x = -m_d3dxvMovingDir.x;
		m_d3dxvMovingDir.y = -m_d3dxvMovingDir.y;
		m_d3dxvMovingDir.z = -m_d3dxvMovingDir.z;

		XMVECTOR vVel = XMLoadFloat3(&XMFLOAT3(m_d3dxvMovingDir.x*m_fMovingSpeed*fTimeElapsed, m_d3dxvMovingDir.y*m_fMovingSpeed*fTimeElapsed, m_d3dxvMovingDir.z*m_fMovingSpeed*fTimeElapsed));

		pos = pos + vVel;

		flag = true;
	}

	SetPosition(pos);

	//Rotate(&XMLoadFloat3(&m_d3dxvRotationAxis), m_fRotationSpeed * fTimeElapsed);

	return flag;
}



CDynamicObject::CDynamicObject() : CSpaceObject() {
	//ȸ�� ��

	XMStoreFloat3(&m_d3dxvRotationAxis, XMVector3Normalize(XMVectorSet(RANDOM_DIR, RANDOM_DIR, RANDOM_DIR, 0.0f)));
	//m_fRotationSpeed = rand() % 100;
	m_fRotationSpeed = 0;

	//�̵� ����
	XMStoreFloat3(&m_d3dxvMovingDir, XMVector3Normalize(XMVectorSet(RANDOM_DIR, RANDOM_DIR, RANDOM_DIR, 0.0f)));

	m_fMovingSpeed = DYNAMICOBJ_SPEED;

}
CDynamicObject::~CDynamicObject() {

}
