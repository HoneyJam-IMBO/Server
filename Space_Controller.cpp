#include "stdafx.h"
#include "Space_Controller.h"



Index::Index(){
	x = 0;
	y = 0;
	z = 0;
}
Index::Index(int x, int y, int z){
	this->x = x;
	this->y = y;
	this->z = z;
}
Index::~Index(){ }
void Index::operator = (Index& tmp){
	x = tmp.x;
	y = tmp.y;
	z = tmp.z;
}
Index& Index::operator + (Index& tmp){
	x = x + tmp.x;
	y = y + tmp.y;
	z = z + tmp.z;
	return *this;
}
Index& Index::operator - (Index& tmp){
	x = x - tmp.x;
	y = y - tmp.y;
	z = z - tmp.z;
	return *this;
}


//space controller
//space controller
//space controller
space_controller::space_controller(){
	size = 0;

	//총알 매니져
	//m_pBulletManager = NULL;
	m_pBlockBulletManager = NULL;
	//m_plBlockObject = new DLinkedList<CGameObject>;
}
space_controller::~space_controller(){
	for (int i = 0; i < space_num; i++){
		delete m_ppSpace[i];
	}
	delete m_ppSpace;

	m_lBlockObject.clear();
	//m_plBlockObject->deleteAll();
	//delete m_plBlockObject;


	//총알
	//if (m_pBulletManager) m_pBulletManager->End();
	if (m_pBlockBulletManager) m_pBlockBulletManager->End();
}

void space_controller::AddBlockObject(CSpaceObject* obj){
	m_lBlockObject.push_back(obj);
}

void space_controller::wakeUpSpace(CPlayer* pPlayer){

	XMVECTOR position = pPlayer->GetPlayerPosition();

	XMFLOAT3 xmfPos;
	XMStoreFloat3(&xmfPos, position);
	int x = xmfPos.x;
	int y = xmfPos.y;
	int z = xmfPos.z;

	Index index = Index((int)x / one_size, (int)y / one_size, (int)z / one_size);

	//보이는 공간의 범위에서 가장 작은 공간의 인덱스
	x = index.x - visual_field_level;
	y = index.y - visual_field_level;
	z = index.z - visual_field_level;
	//보이는 공간의 범위에서 가장 작은 공간의 인덱스

	std::list<CPlayer*> lNearPlayer;

	for (int i = 0; i < visual_field_size; i++){
		for (int j = 0; j < visual_field_size; j++){
			for (int k = 0; k < visual_field_size; k++){
				Index currentindex = Index(x + i, y + j, z + k);
				if (CheckSpaceNum(currentindex)){//해당 공간이 유효 하다면
					//해당 공간안의 플레이어를 얻어온다.
					if (m_ppSpace[GetSpaceIndexNum(currentindex)]->getActive()) continue;
					//a만약 이미 active상태면 pass~

					//아니면
					//공간을 꺠움
					std::cout << "이 공간이 꺠어남 : " << GetSpaceIndexNum(currentindex) << std::endl;
					m_ppSpace[GetSpaceIndexNum(currentindex)]->wakeUpSpace();
				}
			}//x for end
		}//y for end
	}//z for end

	return;
}

//플레이어 처음 입장시에 어느 공간에 들어갈지 체크하는 함수
//플레이어 처음 입장시에 어느 공간에 들어갈지 체크하는 함수
void space_controller::AddPlayer(CConnectedSession* pConnectedSession){

	lock();

	std::cout << "Space Controller AddPlayer" << std::endl;
	//connectedSession의 플레이어를 받아온다.
	CPlayer* pPlayer = pConnectedSession->GetPlayer();


	//플레이어의 위치로 어느 공간에 있는지 계산 후 
	int space_index = SearchSpace(pPlayer->GetPosition());

	//해당 공간에 집어 넣는다. >?? 공간에서 플레이어를 어떻게 관리할지 아직 잘 모르겠음 
	pPlayer->SetSpace(m_ppSpace[space_index]);
	//m_ppSpace[space_index]->AddMovingObject(pPlayer);


	//공간에서 ConnectedSesion을 관리하는 벡터에 push_back해준다.
	m_ppSpace[space_index]->AddPlayer(pConnectedSession);

	//그 후에 공간 주변의 모든 객체를 관리하는 list에 추가해준다.


	//	ㅁㄴㅇㅁㅇ;

	std::list<CDynamicObject*> lNearObject;
	lNearObject = GetNearObjectList(pPlayer);
	pPlayer->ProcView_OBJ(lNearObject);

	//ProcView_NearObjectList(pPlayer);

	std::list<CPlayer*> lNearPlayer;
	lNearPlayer = GetNearPlayerList(pPlayer);
	pPlayer->ProcView_PLAYER(lNearPlayer);

	//주변의 공간 깨움
	wakeUpSpace(pPlayer);

	unlock();
	//EnterSpace프로토콜 잠시 보류
	//m_ppSpace[space_index]->WriteEnterSpacePacketVer2(pConnectedSession);
}
//플레이어 처음 입장시에 어느 공간에 들어갈지 체크하는 함수
//플레이어 처음 입장시에 어느 공간에 들어갈지 체크하는 함수


void space_controller::BuildWorld(CServerIocp* pServerIocp, int objnum){
	//m_pBulletManager = new BulletManager();
	//m_pBulletManager->Begin();

	m_pBlockBulletManager = new BulletManager();
	m_pBlockBulletManager->Begin();

	//공간 초기화
	m_ppSpace = new space*[space_num];
	for (auto i = 0; i < space_num; ++i){
		m_ppSpace[i] = nullptr;
	}

	//광산

	m_ppSpace[0] = new mine_space(this);


	//전역 운석들
	int nStaticObject = 2;
	CreateStaticObject(pServerIocp, nStaticObject);

	//지구
	m_ppSpace[GetSpaceIndexNum(Index(1, 1, 1))] = new planet_space(this, m_vPlanetObject[0]);
	m_ppSpace[GetSpaceIndexNum(Index(1, 2, 1))] = new planet_space(this, m_vPlanetObject[0]);
	m_ppSpace[GetSpaceIndexNum(Index(2, 1, 1))] = new planet_space(this, m_vPlanetObject[0]);
	m_ppSpace[GetSpaceIndexNum(Index(2, 2, 1))] = new planet_space(this, m_vPlanetObject[0]);

	m_ppSpace[GetSpaceIndexNum(Index(1, 1, 2))] = new planet_space(this, m_vPlanetObject[0]);
	m_ppSpace[GetSpaceIndexNum(Index(1, 2, 2))] = new planet_space(this, m_vPlanetObject[0]);
	m_ppSpace[GetSpaceIndexNum(Index(2, 1, 2))] = new planet_space(this, m_vPlanetObject[0]);
	m_ppSpace[GetSpaceIndexNum(Index(1, 1, 2))] = new planet_space(this, m_vPlanetObject[0]);
	//지구 공간

	//태양 공간
	m_ppSpace[GetSpaceIndexNum(Index(3, 3, 3))] = new planet_space(this, m_vPlanetObject[1]);
	m_ppSpace[GetSpaceIndexNum(Index(3, 4, 3))] = new planet_space(this, m_vPlanetObject[1]);
	m_ppSpace[GetSpaceIndexNum(Index(4, 3, 3))] = new planet_space(this, m_vPlanetObject[1]);
	m_ppSpace[GetSpaceIndexNum(Index(4, 4, 3))] = new planet_space(this, m_vPlanetObject[1]);

	m_ppSpace[GetSpaceIndexNum(Index(3, 3, 4))] = new planet_space(this, m_vPlanetObject[1]);
	m_ppSpace[GetSpaceIndexNum(Index(3, 4, 4))] = new planet_space(this, m_vPlanetObject[1]);
	m_ppSpace[GetSpaceIndexNum(Index(4, 3, 4))] = new planet_space(this, m_vPlanetObject[1]);
	m_ppSpace[GetSpaceIndexNum(Index(4, 4, 4))] = new planet_space(this, m_vPlanetObject[1]);
	//태양 공간
	//공간 


	//default space, 공간 build
	for (int i = 0; i < space_num; i++){

		if (m_ppSpace[i]){
			//이미 정의된 공간이면 공간 build만 한다.
			m_ppSpace[i]->SetSpaceNum(i, one_size, one_side_space_count);
			m_ppSpace[i]->BuildWorld(pServerIocp);
			continue;
		}

		m_ppSpace[i] = new default_space(this);
		m_ppSpace[i]->SetSpaceNum(i, one_size, one_side_space_count);
		m_ppSpace[i]->BuildWorld(pServerIocp);
	}


}

//공간에 구애받지 않는 객체 생성
void space_controller::CreateStaticObject(CServerIocp* pServerIocp, int objnum){

	//지구 행성 초기화
	CDynamicObject* ppObj = new CPlanet(pServerIocp);

	int xPosition = 20 * UNIT;
	int yPosition = 20 * UNIT;
	int zPosition = 20 * UNIT;

	ppObj->SetPosition(xPosition, yPosition, zPosition);

	ppObj->SetBoundingSphereRadius(PLANET_RADIUS);
	//지구는 움직이지 않음
	ppObj->SetMovingSpeed(0);
	//지구는 공간에 규약받지 않음
	m_vPlanetObject.push_back(ppObj);
	//지구 행성 초기화



	//태양 행성 초기화
	ppObj = new CPlanet(pServerIocp);

	xPosition = 40 * UNIT;
	yPosition = 40 * UNIT;
	zPosition = 40 * UNIT;

	ppObj->SetPosition(xPosition, yPosition, zPosition);

	ppObj->SetBoundingSphereRadius(PLANET_RADIUS);
	//태양는 움직이지 않음
	ppObj->SetMovingSpeed(0);
	//태양는 공간에 규약받지 않음
	m_vPlanetObject.push_back(ppObj);
	//태양 행성 초기화


}
void space_controller::InitSpaces(CServerIocp* pServerIocp, int si, int le, int vfl){
	//크기 설정 
	size = si;
	//레벨 설정
	level = le;

	//한 사이드에 있는 공간의 개수
	one_side_space_count = pow(2, level);
	//공간 하나의 크기
	one_size = size / one_side_space_count;
	//공간의 개수
	space_num = pow(one_side_space_count, 3);

	//보이는 공간의 범위, 총 렌더 검사를 해야하는 공간의 한 면의 크기
	visual_field_level = vfl;
	visual_field_size = 1 + visual_field_level * 2;
	//보이는 공간의 범위, 총 렌더 검사를 해야하는 공간의 한 면의 크기

	//보이는 공간의 배열
	render_space_indexs = new int[visual_field_size * visual_field_size * visual_field_size];
	//보이는 공간의 배열

	BuildWorld(pServerIocp, DEFAULT_COMAT_NUM);
	//BuildWorld(0);

}

//뭔가 위치를 전달하면 그 주변에 애들만 그리게 하면 되지 않나.
//플레이어의 위치를 전달받게 하자.
//공간분할 렌더링의 로직
//플레이어의 위치 => 현제 공간 => 주변 공간 => 그림을 그려야 하는 공간

//공간 컨트롤
//공간 animate
void space_controller::AnimateSpaces(float fTimeElapsed, XMVECTOR position)
{


	//m_pGSSpaceShader->AnimateObjects(fTimeElapsed);
	XMFLOAT3 xmfPos;
	XMStoreFloat3(&xmfPos, position);
	printf("num : %d, xyz : (%d, %d, %d)", SearchSpace(position), (int)xmfPos.x / one_size, (int)xmfPos.y / one_size, (int)xmfPos.z / one_size);
	printf(" render space num : %d", space_counter);
	printf(" one size : %d", one_size);
	//for (int i = 0; i < space_counter; i++){
	//	printf("%d ", render_space_indexs[i]);
	//}
	printf("\n");
}
//공간 컨트롤

//월드 컨트롤
//플레이어가 처음 접속했을 경우 부르는 함수
void space_controller::WriteEnterSpacePacketVer1(CConnectedSession* pConnectedSession){//단일 공간

	//인자로 들어온 해당 객체만 EnterSpace 패킷 전송
	pConnectedSession->GetPlayer()->GetSpace()->WriteEnterSpacePacketVer1(pConnectedSession);


}
//플레이어가 처음 접속했을 경우 부르는 함수


void space_controller::PrepareRenderVer2(XMVECTOR position){//단일 공간
	//플레이어 위치의 공간안의 객체 리스트를 받아온다.
	//DLinkedList<CGameObject>* tmplist;
	//
	///* 
	//해야 되는 거어어어어어어어어어어어!!!!!!!!!!!!!!!
	//여기서 그림을 그려야 할 공간의 배열을 반환 받고
	//리턴 값으로 성공, 실패를 받는다. <그릴 공간이 없으면 실패>
	//성공하면 모든 공간에 대하여 아래의 과정을 반복 한다. <공간안의 객체를 쉐이더 리스트에 넣는 과정>
	//*/
	//if (SearchSpaces(position)){//공간을 찾는데 성공 한다면
	//	//Space_CGSCubeInstancingShader* tmp = (Space_CGSCubeInstancingShader*)m_pShader;
	//	//space_controller의 <space_counter, render_space_indexs>가 갱신됨.
	//
	//	for (int i = 0; i < space_counter; i++){//갱신된 spaces 배열들 수 만큼 루프 
	//		//해당 공간의 모든 객체를 렌더 검사 리스트에 추가
	//		tmplist = m_ppSpace[render_space_indexs[i]]->GetObjectList();
	//		Node<CGameObject>* obj = tmplist->begin();
	//		while (obj != tmplist->end()){
	//
	//			//tmp->Push_Back(obj->data);
	//
	//			obj = obj->next;
	//		}//while end
	//	}
	//
	//	//움직이는 객체
	//	//tmp = (Space_CGSCubeInstancingShader*)m_pMovingShader;
	//	//space_controller의 <space_counter, render_space_indexs>가 갱신됨.
	//
	//	for (int i = 0; i < space_counter; i++){//갱신된 spaces 배열들 수 만큼 루프 
	//		//해당 공간의 모든 객체를 렌더 검사 리스트에 추가
	//		tmplist = m_ppSpace[render_space_indexs[i]]->GetMovingObjectList();
	//		Node<CGameObject>* obj = tmplist->begin();
	//		while (obj != tmplist->end()){
	//
	//			//tmp->Push_Back(obj->data);
	//
	//			obj = obj->next;
	//		}//while end
	//	}
	//
	//}
}

//월드 Animate
void space_controller::AnimateWorld(float fTimeElapsed)
{

	//총알
	//m_pBulletManager->Update(fTimeElapsed, m_pBlockBulletManager);

	for (int i = 0; i < space_num; i++){


		m_ppSpace[i]->AnimateObject(fTimeElapsed);
	}
	//5. 모든 객체 Animate 후에

	//#ifdef _DEBUG
	//	std::cout << "SPACE CONTROLLER의 ANIMATEWORLD" << std::endl;
	//#endif
	//6. 블럭 객체 리스트안의 모든 객체를 해당 공간에 push_back

	for (auto i : m_lBlockObject){



		//int nFiringBullet = m_pBlockBulletManager->GetnBullet();
		CDynamicObject *tmp = (CDynamicObject *)i;
		//현재 갱신된 공간안에 push_back
		int spaceindex = tmp->GetSpace()->GetSpaceNum();
		//#ifdef _DEBUG
		//		std::cout << "SPACE CONTROLLER의 BLOCK_LIST UPDATE" << std::endl;
		//#endif


		///0520 수정
		//std::list<CPlayer*> lNearPlayer;
		//
		//lNearPlayer = GetNearPlayerList(tmp);
		//
		//tmp->ProcView(lNearPlayer);

		//if (lNearPlayer.size() != 0){
		//	//만약 플레이어가 있다면 
		//	//해당하는 플레이어는 시야 처리과정을 거친다. 
		//
		//}



		m_ppSpace[spaceindex]->AddMovingObject(tmp);

	}
	m_lBlockObject.clear();

	//현재 컨트롤중인 총알이 있다면
	////총알 block manager안의 모든 총알을 재분배 해준다.
	//if (nFiringBullet != 0){
	//	std::vector<BulletObject*> BulletCont = m_pBlockBulletManager->GetBulletContainer();
	//	std::vector<BulletObject*>::iterator Iter = BulletCont.begin();
	//	//std::cout << std::endl << std::endl;
	//	//std::cout << "BLOCKBULLET PROC" << std::endl << std::endl;
	//	//발사중인 총알 만큼만
	//w	for (int i = 0; i < nFiringBullet; ++i){
	//		int current_space_index = SearchSpace((*Iter)->GetPosition());
	//
	//		//blockManager에서 지워주고
	//		//std::cout << "BlockBulletManager" << std::endl;
	//		m_pBlockBulletManager->DeleteBullet((*Iter)->GetID());
	//
	//		//만약 이상한 index라면 다음총알 진행
	//		if (-1 == current_space_index) continue;
	//		//재분배
	//		//std::cout << "BulletManager " << current_space_index << std::endl;
	//		m_ppSpace[current_space_index]->GetpBulletManager()->AddBullet((*Iter));
	//		Iter++;
	//	}
	//}
}
//월드 컨트롤


//자신이 있는 공간을 찾는 함수 해당 공간의 번호를 리턴한다.
int space_controller::SearchSpace(XMVECTOR position){

	XMFLOAT3 xmfPos;
	XMStoreFloat3(&xmfPos, position);
	int x = xmfPos.x;
	int y = xmfPos.y;
	int z = xmfPos.z;


	//자신의 위치를 이용해 인덱스를 얻어옴
	int indexX = (int)x / one_size;
	int indexY = (int)y / one_size;
	int indexZ = (int)z / one_size;



	int index = indexX + (indexY * one_side_space_count) + (indexZ * one_side_space_count * one_side_space_count);

	//예외 처리 범위 밖
	if (index < 0 || index >= space_num){
		return -1;
	}
	if (x < 0 || y < 0 || z < 0 ||
		x > size || y > size || z > size){
		return -1;
	}
	//예외 처리 범위 밖


	return index;
}
Index space_controller::SearchSpace_Index(XMVECTOR position){

	XMFLOAT3 xmfPos;
	XMStoreFloat3(&xmfPos, position);
	int x = xmfPos.x;
	int y = xmfPos.y;
	int z = xmfPos.z;


	//자신의 위치를 이용해 인덱스를 얻어옴
	int indexX = (int)x / one_size;
	int indexY = (int)y / one_size;
	int indexZ = (int)z / one_size;



	int index = indexX + (indexY * one_side_space_count) + (indexZ * one_side_space_count * one_side_space_count);

	//예외 처리 범위 밖
	if (index < 0 || index >= space_num){
		return Index(-1, -1, -1);
	}
	if (x < 0 || y < 0 || z < 0 ||
		x > size || y > size || z > size){
		return Index(-1, -1, -1);
	}
	//예외 처리 범위 밖


	return Index(indexX, indexY, indexZ);
}


//해당 공간의 인덱스 xyz를 spacenum으로 바꾸는 함수
int space_controller::GetSpaceIndexNum(Index& index){
	return index.x + (index.y * one_side_space_count) + (index.z * one_side_space_count * one_side_space_count);
}

//해당 공간의 인덱스가 유효한지 검사하는 함수
bool space_controller::CheckSpaceNum(Index& index){
	if (index.x < 0 || index.y < 0 || index.z < 0 ||
		index.x > one_side_space_count - 1 || index.y > one_side_space_count - 1 || index.z > one_side_space_count - 1){
		return false;
	}
	int num = GetSpaceIndexNum(index);
	if (0 > num || num >= space_num){
		return false;
	}

	return true;
}

/*
자신이 그려야 하는 공간들의 번호배열을 반환하는 함수
<in>
자신의 index X Y Z -> 음수라도 받아온다. 후 처리는 여기서 한다.

<out>
space_controller의 <space_counter, render_space_indexs>가 갱신됨.
render_space_indexs = 그림을 그려야 할 인덱스의 배열 맨 처음 포인터
<space_conrtoller> 가 가지고 있는 배열이다. 보이는 범위를 이용해 최대 몇개 까지인지 알 수 있다.
space_counter = 그림을 그려야 하는 공간의 개수 이다. 계속 유동적으로 변 할 수 있기에 계산해서 넣어준다.

<return>
bool 성공, 실패 반환되는 공간이 없을 경우 false를 리턴 한다.
*/
//
bool space_controller::SearchSpaces(CConnectedSession* pConnectedSession){

	XMVECTOR position = pConnectedSession->GetPlayer()->GetPlayerPosition();

	XMFLOAT3 xmfPos;
	XMStoreFloat3(&xmfPos, position);
	int x = xmfPos.x;
	int y = xmfPos.y;
	int z = xmfPos.z;


	//자신의 위치를 이용해 인덱스를 얻어옴
	//여기서 오류가 발생 -0.4 / one_size = 0임.. 
	Index index = Index((int)x / one_size, (int)y / one_size, (int)z / one_size);

	//보이는 공간의 범위에서 가장 작은 공간의 인덱스
	x = index.x - visual_field_level;
	y = index.y - visual_field_level;
	z = index.z - visual_field_level;
	//보이는 공간의 범위에서 가장 작은 공간의 인덱스

	int space_counter = 0;//몇개의 공간이 있는지 카운트 할 카운터
	//렌더 해야할 공간 인덱스 배열 포인터를 넘겨 받는다
	int* render_space_indexs = pConnectedSession->GetPlayer()->Getrender_space_indexs();

	//x y z에 대하여 
	for (int i = 0; i < visual_field_size; i++){
		for (int j = 0; j < visual_field_size; j++){
			for (int k = 0; k < visual_field_size; k++){
				Index currentindex = Index(x + i, y + j, z + k);
				if (CheckSpaceNum(currentindex)){//해당 공간이 유효 하다면
					//해당 공간을 space_controller의 그림그릴 공간 배열에 집어 넣는다.
					render_space_indexs[space_counter++] = GetSpaceIndexNum(currentindex);
				}
			}//x for end
		}//y for end
	}//z for end

	if (space_counter == 0) return false;
	if (space_counter > space_num){
		return false;
	}

	pConnectedSession->GetPlayer()->Setspace_counter(space_counter);
	return true;
}


void space_controller::ShowSpaceInfo(){
	printf("공간의 크기 : %d \n공간의 레벨 : %d \n공간 하나의 크기 : %d\n한 사이드에 있는 공간의 개수 : %d\n공간의 개수 : %d \n",
		size, level, one_size, one_side_space_count, space_num);
}

BOOL space_controller::GetBlockObjectList(std::list<CSpaceObject*>& lBlockObject){
	if (0 == m_lBlockObject.size()){
		return FALSE;

	}
	lBlockObject = m_lBlockObject;
	return TRUE;
}
std::list<CPlayer*> space_controller::GetNearPlayerList(CPlayer* pPlayer){


	XMVECTOR position = pPlayer->GetPlayerPosition();

	XMFLOAT3 xmfPos;
	XMStoreFloat3(&xmfPos, position);
	int x = xmfPos.x;
	int y = xmfPos.y;
	int z = xmfPos.z;

	Index index = Index((int)x / one_size, (int)y / one_size, (int)z / one_size);

	//보이는 공간의 범위에서 가장 작은 공간의 인덱스
	x = index.x - visual_field_level;
	y = index.y - visual_field_level;
	z = index.z - visual_field_level;
	//보이는 공간의 범위에서 가장 작은 공간의 인덱스


	//x y z에 대하여 

	std::list<CPlayer*> lNearPlayer;

	for (int i = 0; i < visual_field_size; i++){
		for (int j = 0; j < visual_field_size; j++){
			for (int k = 0; k < visual_field_size; k++){
				Index currentindex = Index(x + i, y + j, z + k);
				if (CheckSpaceNum(currentindex)){//해당 공간이 유효 하다면
					//해당 공간안의 플레이어를 얻어온다.
					std::list<CConnectedSession*> lConnectedSession;
					if (m_ppSpace[GetSpaceIndexNum(currentindex)]->GetConnectedSessionList(lConnectedSession)){
						//있다면
						//모든 player push_back
						for (auto i : lConnectedSession){
							//나 자신은 빼고
							if (i->GetPlayer()->GetID() == pPlayer->GetID()) continue;
							lNearPlayer.push_back(i->GetPlayer());
#ifdef _DEBUG
							//std::cout << "player " << i->GetPlayer()->GetID() << "가 근처에 있다." << std::endl;
#endif
						}

					}
				}
			}//x for end
		}//y for end
	}//z for end

	return lNearPlayer;
}


std::list<CPlayer*> space_controller::GetNearPlayerList(XMFLOAT3 xmfPos){



	int x = xmfPos.x;
	int y = xmfPos.y;
	int z = xmfPos.z;

	Index index = Index((int)x / one_size, (int)y / one_size, (int)z / one_size);

	//보이는 공간의 범위에서 가장 작은 공간의 인덱스
	x = index.x - visual_field_level;
	y = index.y - visual_field_level;
	z = index.z - visual_field_level;
	//보이는 공간의 범위에서 가장 작은 공간의 인덱스


	//x y z에 대하여 

	std::list<CPlayer*> lNearPlayer;

	for (int i = 0; i < visual_field_size; i++){
		for (int j = 0; j < visual_field_size; j++){
			for (int k = 0; k < visual_field_size; k++){
				Index currentindex = Index(x + i, y + j, z + k);
				if (CheckSpaceNum(currentindex)){//해당 공간이 유효 하다면
					//해당 공간안의 플레이어를 얻어온다.
					std::list<CConnectedSession*> lConnectedSession;
					if (m_ppSpace[GetSpaceIndexNum(currentindex)]->GetConnectedSessionList(lConnectedSession)){
						//있다면
						//모든 player push_back
						for (auto i : lConnectedSession){

							lNearPlayer.push_back(i->GetPlayer());
#ifdef _DEBUG
							//std::cout << "player " << i->GetPlayer()->GetID() << "가 근처에 있다." << std::endl;
#endif
						}

					}
				}
			}//x for end
		}//y for end
	}//z for end

	return lNearPlayer;
}

std::list<CPlayer*> space_controller::GetNearPlayerList(CDynamicObject* pObject){


	XMVECTOR position = pObject->GetPosition();

	XMFLOAT3 xmfPos;
	XMStoreFloat3(&xmfPos, position);
	int x = xmfPos.x;
	int y = xmfPos.y;
	int z = xmfPos.z;

	Index index = Index((int)x / one_size, (int)y / one_size, (int)z / one_size);

	//보이는 공간의 범위에서 가장 작은 공간의 인덱스
	x = index.x - visual_field_level;
	y = index.y - visual_field_level;
	z = index.z - visual_field_level;
	//보이는 공간의 범위에서 가장 작은 공간의 인덱스


	//x y z에 대하여 

	std::list<CPlayer*> lNearPlayer;

	for (int i = 0; i < visual_field_size; i++){
		for (int j = 0; j < visual_field_size; j++){
			for (int k = 0; k < visual_field_size; k++){
				Index currentindex = Index(x + i, y + j, z + k);
				if (CheckSpaceNum(currentindex)){//해당 공간이 유효 하다면
					//해당 공간안의 플레이어를 얻어온다.
					std::list<CConnectedSession*> lConnectedSession;
					if (m_ppSpace[GetSpaceIndexNum(currentindex)]->GetConnectedSessionList(lConnectedSession)){
						//있다면
						//모든 player push_back
						for (auto i : lConnectedSession){
							lNearPlayer.push_back(i->GetPlayer());
#ifdef _DEBUG
							//std::cout << "player " << i->GetPlayer()->GetID() << "가 근처에 있다." << std::endl;
#endif
						}

					}
				}
			}//x for end
		}//y for end
	}//z for end

	return lNearPlayer;
}
std::list<CDynamicObject*> space_controller::GetNearObjectList(CPlayer* pPlayer){
	//	lock();

	XMVECTOR position = pPlayer->GetPlayerPosition();

	XMFLOAT3 xmfPos;
	XMStoreFloat3(&xmfPos, position);
	int x = xmfPos.x;
	int y = xmfPos.y;
	int z = xmfPos.z;

	Index index = Index((int)xmfPos.x / one_size, (int)xmfPos.y / one_size, (int)xmfPos.z / one_size);

	//보이는 공간의 범위에서 가장 작은 공간의 인덱스
	x = index.x - visual_field_level;
	y = index.y - visual_field_level;
	z = index.z - visual_field_level;
	//보이는 공간의 범위에서 가장 작은 공간의 인덱스


	//x y z에 대하여 
	std::list<CDynamicObject*> lNearObject;
	for (int i = 0; i < visual_field_size; i++){
		for (int j = 0; j < visual_field_size; j++){
			for (int k = 0; k < visual_field_size; k++){
				Index currentindex = Index(x + i, y + j, z + k);
				if (CheckSpaceNum(currentindex)){//해당 공간이 유효 하다면wwwwwww
					//해당 공간안의 플레이어를 얻어온다.
					std::list<CDynamicObject*> lObject;
					if (m_ppSpace[GetSpaceIndexNum(currentindex)]->GetMovingObjectList(lObject)){
						//있다면
						//모든 player push_back
						for (auto i : lObject){
							lNearObject.push_back(i);
							//pConnectedSession->GetPlayer()->PutViewList_OBJ(i);
							//pConnectedSession->GetPlayer()->PutObject(i);
							//#ifdef _DEBUG
							//							std::cout << "player " << i->GetPlayer()->GetID() << "가 근처에 있다." << std::endl;
							//#endif
						}

					}
				}
			}//x for end
		}//y for end
	}//z for end

	//unlock();

	return lNearObject;
}

void space_controller::ProcView_NearObjectList(CPlayer* pPlayer) {



	XMVECTOR position = pPlayer->GetPlayerPosition();

	XMFLOAT3 xmfPos;
	XMStoreFloat3(&xmfPos, position);
	int x = xmfPos.x;
	int y = xmfPos.y;
	int z = xmfPos.z;

	Index index = Index((int)xmfPos.x / one_size, (int)xmfPos.y / one_size, (int)xmfPos.z / one_size);

	//보이는 공간의 범위에서 가장 작은 공간의 인덱스
	x = index.x - visual_field_level;
	y = index.y - visual_field_level;
	z = index.z - visual_field_level;
	//보이는 공간의 범위에서 가장 작은 공간의 인덱스


	//x y z에 대하여 

	for (int i = 0; i < visual_field_size; i++) {
		for (int j = 0; j < visual_field_size; j++) {
			for (int k = 0; k < visual_field_size; k++) {
				Index currentindex = Index(x + i, y + j, z + k);
				if (CheckSpaceNum(currentindex)) {//해당 공간이 유효 하다면wwwwwww
					//해당 공간안의 플레이어를 얻어온다.
					std::list<CDynamicObject*> lObject;
					if (m_ppSpace[GetSpaceIndexNum(currentindex)]->GetMovingObjectList(lObject)) {
						//있다면
						pPlayer->ProcView_OBJ(lObject);

					}
				}
			}//x for end
		}//y for end
	}//z for end


	std::list<CPlayer*> lNearPlayer;
	lNearPlayer = GetNearPlayerList(pPlayer);
	pPlayer->ProcView_PLAYER(lNearPlayer);
}





