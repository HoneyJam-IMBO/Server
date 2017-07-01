#include "stdafx.h"
#include "DynamicObject.h"

//////////////////////////////Dynamic
//////////////////////////////Dynamic

void CDynamicObject::Begin() {

}

void CDynamicObject::End() {

}


bool CDynamicObject::Animate(float fTimeElapsed) {

	//상태가 변화할 시에 TRUE;
	//안변했으면 FALS;
	//default는 FALSE임
	bool flag = false;

	//#ifdef _DEBUG
	//	std::cout << "SPACE 의 MOVINGOBJ ANIMATE" << std::endl;
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
	//std::cout << "id: " << GetID() << " 의 위치 ";
	//printf("pos: %f, %f, %f \n", xmfPos.x, xmfPos.y, xmfPos.z);
	if (xmfPos.x > MAP_SIZE || xmfPos.y > MAP_SIZE || xmfPos.z > MAP_SIZE || xmfPos.x < 0 || xmfPos.y < 0 || xmfPos.z < 0) {
		//std::cout << "id: " << GetID() << " 의 상태 변환! ";
		//std::cout << "id: " << GetID() << " 방향 전환 !!!!!!!!11111 의 위치 ";
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
	//회전 축

	XMStoreFloat3(&m_d3dxvRotationAxis, XMVector3Normalize(XMVectorSet(RANDOM_DIR, RANDOM_DIR, RANDOM_DIR, 0.0f)));
	//m_fRotationSpeed = rand() % 100;
	m_fRotationSpeed = 0;

	//이동 방향
	XMStoreFloat3(&m_d3dxvMovingDir, XMVector3Normalize(XMVectorSet(RANDOM_DIR, RANDOM_DIR, RANDOM_DIR, 0.0f)));

	m_fMovingSpeed = DYNAMICOBJ_SPEED;

}
CDynamicObject::~CDynamicObject() {

}
