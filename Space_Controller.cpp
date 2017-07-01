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

	//�Ѿ� �Ŵ���
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


	//�Ѿ�
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

	//���̴� ������ �������� ���� ���� ������ �ε���
	x = index.x - visual_field_level;
	y = index.y - visual_field_level;
	z = index.z - visual_field_level;
	//���̴� ������ �������� ���� ���� ������ �ε���

	std::list<CPlayer*> lNearPlayer;

	for (int i = 0; i < visual_field_size; i++){
		for (int j = 0; j < visual_field_size; j++){
			for (int k = 0; k < visual_field_size; k++){
				Index currentindex = Index(x + i, y + j, z + k);
				if (CheckSpaceNum(currentindex)){//�ش� ������ ��ȿ �ϴٸ�
					//�ش� �������� �÷��̾ ���´�.
					if (m_ppSpace[GetSpaceIndexNum(currentindex)]->getActive()) continue;
					//a���� �̹� active���¸� pass~

					//�ƴϸ�
					//������ �ƿ�
					std::cout << "�� ������ �ƾ : " << GetSpaceIndexNum(currentindex) << std::endl;
					m_ppSpace[GetSpaceIndexNum(currentindex)]->wakeUpSpace();
				}
			}//x for end
		}//y for end
	}//z for end

	return;
}

//�÷��̾� ó�� ����ÿ� ��� ������ ���� üũ�ϴ� �Լ�
//�÷��̾� ó�� ����ÿ� ��� ������ ���� üũ�ϴ� �Լ�
void space_controller::AddPlayer(CConnectedSession* pConnectedSession){

	lock();

	std::cout << "Space Controller AddPlayer" << std::endl;
	//connectedSession�� �÷��̾ �޾ƿ´�.
	CPlayer* pPlayer = pConnectedSession->GetPlayer();


	//�÷��̾��� ��ġ�� ��� ������ �ִ��� ��� �� 
	int space_index = SearchSpace(pPlayer->GetPosition());

	//�ش� ������ ���� �ִ´�. >?? �������� �÷��̾ ��� �������� ���� �� �𸣰��� 
	pPlayer->SetSpace(m_ppSpace[space_index]);
	//m_ppSpace[space_index]->AddMovingObject(pPlayer);


	//�������� ConnectedSesion�� �����ϴ� ���Ϳ� push_back���ش�.
	m_ppSpace[space_index]->AddPlayer(pConnectedSession);

	//�� �Ŀ� ���� �ֺ��� ��� ��ü�� �����ϴ� list�� �߰����ش�.


	//	����������;

	std::list<CDynamicObject*> lNearObject;
	lNearObject = GetNearObjectList(pPlayer);
	pPlayer->ProcView_OBJ(lNearObject);

	//ProcView_NearObjectList(pPlayer);

	std::list<CPlayer*> lNearPlayer;
	lNearPlayer = GetNearPlayerList(pPlayer);
	pPlayer->ProcView_PLAYER(lNearPlayer);

	//�ֺ��� ���� ����
	wakeUpSpace(pPlayer);

	unlock();
	//EnterSpace�������� ��� ����
	//m_ppSpace[space_index]->WriteEnterSpacePacketVer2(pConnectedSession);
}
//�÷��̾� ó�� ����ÿ� ��� ������ ���� üũ�ϴ� �Լ�
//�÷��̾� ó�� ����ÿ� ��� ������ ���� üũ�ϴ� �Լ�


void space_controller::BuildWorld(CServerIocp* pServerIocp, int objnum){
	//m_pBulletManager = new BulletManager();
	//m_pBulletManager->Begin();

	m_pBlockBulletManager = new BulletManager();
	m_pBlockBulletManager->Begin();

	//���� �ʱ�ȭ
	m_ppSpace = new space*[space_num];
	for (auto i = 0; i < space_num; ++i){
		m_ppSpace[i] = nullptr;
	}

	//����

	m_ppSpace[0] = new mine_space(this);


	//���� ���
	int nStaticObject = 2;
	CreateStaticObject(pServerIocp, nStaticObject);

	//����
	m_ppSpace[GetSpaceIndexNum(Index(1, 1, 1))] = new planet_space(this, m_vPlanetObject[0]);
	m_ppSpace[GetSpaceIndexNum(Index(1, 2, 1))] = new planet_space(this, m_vPlanetObject[0]);
	m_ppSpace[GetSpaceIndexNum(Index(2, 1, 1))] = new planet_space(this, m_vPlanetObject[0]);
	m_ppSpace[GetSpaceIndexNum(Index(2, 2, 1))] = new planet_space(this, m_vPlanetObject[0]);

	m_ppSpace[GetSpaceIndexNum(Index(1, 1, 2))] = new planet_space(this, m_vPlanetObject[0]);
	m_ppSpace[GetSpaceIndexNum(Index(1, 2, 2))] = new planet_space(this, m_vPlanetObject[0]);
	m_ppSpace[GetSpaceIndexNum(Index(2, 1, 2))] = new planet_space(this, m_vPlanetObject[0]);
	m_ppSpace[GetSpaceIndexNum(Index(1, 1, 2))] = new planet_space(this, m_vPlanetObject[0]);
	//���� ����

	//�¾� ����
	m_ppSpace[GetSpaceIndexNum(Index(3, 3, 3))] = new planet_space(this, m_vPlanetObject[1]);
	m_ppSpace[GetSpaceIndexNum(Index(3, 4, 3))] = new planet_space(this, m_vPlanetObject[1]);
	m_ppSpace[GetSpaceIndexNum(Index(4, 3, 3))] = new planet_space(this, m_vPlanetObject[1]);
	m_ppSpace[GetSpaceIndexNum(Index(4, 4, 3))] = new planet_space(this, m_vPlanetObject[1]);

	m_ppSpace[GetSpaceIndexNum(Index(3, 3, 4))] = new planet_space(this, m_vPlanetObject[1]);
	m_ppSpace[GetSpaceIndexNum(Index(3, 4, 4))] = new planet_space(this, m_vPlanetObject[1]);
	m_ppSpace[GetSpaceIndexNum(Index(4, 3, 4))] = new planet_space(this, m_vPlanetObject[1]);
	m_ppSpace[GetSpaceIndexNum(Index(4, 4, 4))] = new planet_space(this, m_vPlanetObject[1]);
	//�¾� ����
	//���� 


	//default space, ���� build
	for (int i = 0; i < space_num; i++){

		if (m_ppSpace[i]){
			//�̹� ���ǵ� �����̸� ���� build�� �Ѵ�.
			m_ppSpace[i]->SetSpaceNum(i, one_size, one_side_space_count);
			m_ppSpace[i]->BuildWorld(pServerIocp);
			continue;
		}

		m_ppSpace[i] = new default_space(this);
		m_ppSpace[i]->SetSpaceNum(i, one_size, one_side_space_count);
		m_ppSpace[i]->BuildWorld(pServerIocp);
	}


}

//������ ���ֹ��� �ʴ� ��ü ����
void space_controller::CreateStaticObject(CServerIocp* pServerIocp, int objnum){

	//���� �༺ �ʱ�ȭ
	CDynamicObject* ppObj = new CPlanet(pServerIocp);

	int xPosition = 20 * UNIT;
	int yPosition = 20 * UNIT;
	int zPosition = 20 * UNIT;

	ppObj->SetPosition(xPosition, yPosition, zPosition);

	ppObj->SetBoundingSphereRadius(PLANET_RADIUS);
	//������ �������� ����
	ppObj->SetMovingSpeed(0);
	//������ ������ �Ծ���� ����
	m_vPlanetObject.push_back(ppObj);
	//���� �༺ �ʱ�ȭ



	//�¾� �༺ �ʱ�ȭ
	ppObj = new CPlanet(pServerIocp);

	xPosition = 40 * UNIT;
	yPosition = 40 * UNIT;
	zPosition = 40 * UNIT;

	ppObj->SetPosition(xPosition, yPosition, zPosition);

	ppObj->SetBoundingSphereRadius(PLANET_RADIUS);
	//�¾�� �������� ����
	ppObj->SetMovingSpeed(0);
	//�¾�� ������ �Ծ���� ����
	m_vPlanetObject.push_back(ppObj);
	//�¾� �༺ �ʱ�ȭ


}
void space_controller::InitSpaces(CServerIocp* pServerIocp, int si, int le, int vfl){
	//ũ�� ���� 
	size = si;
	//���� ����
	level = le;

	//�� ���̵忡 �ִ� ������ ����
	one_side_space_count = pow(2, level);
	//���� �ϳ��� ũ��
	one_size = size / one_side_space_count;
	//������ ����
	space_num = pow(one_side_space_count, 3);

	//���̴� ������ ����, �� ���� �˻縦 �ؾ��ϴ� ������ �� ���� ũ��
	visual_field_level = vfl;
	visual_field_size = 1 + visual_field_level * 2;
	//���̴� ������ ����, �� ���� �˻縦 �ؾ��ϴ� ������ �� ���� ũ��

	//���̴� ������ �迭
	render_space_indexs = new int[visual_field_size * visual_field_size * visual_field_size];
	//���̴� ������ �迭

	BuildWorld(pServerIocp, DEFAULT_COMAT_NUM);
	//BuildWorld(0);

}

//���� ��ġ�� �����ϸ� �� �ֺ��� �ֵ鸸 �׸��� �ϸ� ���� �ʳ�.
//�÷��̾��� ��ġ�� ���޹ް� ����.
//�������� �������� ����
//�÷��̾��� ��ġ => ���� ���� => �ֺ� ���� => �׸��� �׷��� �ϴ� ����

//���� ��Ʈ��
//���� animate
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
//���� ��Ʈ��

//���� ��Ʈ��
//�÷��̾ ó�� �������� ��� �θ��� �Լ�
void space_controller::WriteEnterSpacePacketVer1(CConnectedSession* pConnectedSession){//���� ����

	//���ڷ� ���� �ش� ��ü�� EnterSpace ��Ŷ ����
	pConnectedSession->GetPlayer()->GetSpace()->WriteEnterSpacePacketVer1(pConnectedSession);


}
//�÷��̾ ó�� �������� ��� �θ��� �Լ�


void space_controller::PrepareRenderVer2(XMVECTOR position){//���� ����
	//�÷��̾� ��ġ�� �������� ��ü ����Ʈ�� �޾ƿ´�.
	//DLinkedList<CGameObject>* tmplist;
	//
	///* 
	//�ؾ� �Ǵ� �ž�����������!!!!!!!!!!!!!!!
	//���⼭ �׸��� �׷��� �� ������ �迭�� ��ȯ �ް�
	//���� ������ ����, ���и� �޴´�. <�׸� ������ ������ ����>
	//�����ϸ� ��� ������ ���Ͽ� �Ʒ��� ������ �ݺ� �Ѵ�. <�������� ��ü�� ���̴� ����Ʈ�� �ִ� ����>
	//*/
	//if (SearchSpaces(position)){//������ ã�µ� ���� �Ѵٸ�
	//	//Space_CGSCubeInstancingShader* tmp = (Space_CGSCubeInstancingShader*)m_pShader;
	//	//space_controller�� <space_counter, render_space_indexs>�� ���ŵ�.
	//
	//	for (int i = 0; i < space_counter; i++){//���ŵ� spaces �迭�� �� ��ŭ ���� 
	//		//�ش� ������ ��� ��ü�� ���� �˻� ����Ʈ�� �߰�
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
	//	//�����̴� ��ü
	//	//tmp = (Space_CGSCubeInstancingShader*)m_pMovingShader;
	//	//space_controller�� <space_counter, render_space_indexs>�� ���ŵ�.
	//
	//	for (int i = 0; i < space_counter; i++){//���ŵ� spaces �迭�� �� ��ŭ ���� 
	//		//�ش� ������ ��� ��ü�� ���� �˻� ����Ʈ�� �߰�
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

//���� Animate
void space_controller::AnimateWorld(float fTimeElapsed)
{

	//�Ѿ�
	//m_pBulletManager->Update(fTimeElapsed, m_pBlockBulletManager);

	for (int i = 0; i < space_num; i++){


		m_ppSpace[i]->AnimateObject(fTimeElapsed);
	}
	//5. ��� ��ü Animate �Ŀ�

	//#ifdef _DEBUG
	//	std::cout << "SPACE CONTROLLER�� ANIMATEWORLD" << std::endl;
	//#endif
	//6. �� ��ü ����Ʈ���� ��� ��ü�� �ش� ������ push_back

	for (auto i : m_lBlockObject){



		//int nFiringBullet = m_pBlockBulletManager->GetnBullet();
		CDynamicObject *tmp = (CDynamicObject *)i;
		//���� ���ŵ� �����ȿ� push_back
		int spaceindex = tmp->GetSpace()->GetSpaceNum();
		//#ifdef _DEBUG
		//		std::cout << "SPACE CONTROLLER�� BLOCK_LIST UPDATE" << std::endl;
		//#endif


		///0520 ����
		//std::list<CPlayer*> lNearPlayer;
		//
		//lNearPlayer = GetNearPlayerList(tmp);
		//
		//tmp->ProcView(lNearPlayer);

		//if (lNearPlayer.size() != 0){
		//	//���� �÷��̾ �ִٸ� 
		//	//�ش��ϴ� �÷��̾�� �þ� ó�������� ��ģ��. 
		//
		//}



		m_ppSpace[spaceindex]->AddMovingObject(tmp);

	}
	m_lBlockObject.clear();

	//���� ��Ʈ������ �Ѿ��� �ִٸ�
	////�Ѿ� block manager���� ��� �Ѿ��� ��й� ���ش�.
	//if (nFiringBullet != 0){
	//	std::vector<BulletObject*> BulletCont = m_pBlockBulletManager->GetBulletContainer();
	//	std::vector<BulletObject*>::iterator Iter = BulletCont.begin();
	//	//std::cout << std::endl << std::endl;
	//	//std::cout << "BLOCKBULLET PROC" << std::endl << std::endl;
	//	//�߻����� �Ѿ� ��ŭ��
	//w	for (int i = 0; i < nFiringBullet; ++i){
	//		int current_space_index = SearchSpace((*Iter)->GetPosition());
	//
	//		//blockManager���� �����ְ�
	//		//std::cout << "BlockBulletManager" << std::endl;
	//		m_pBlockBulletManager->DeleteBullet((*Iter)->GetID());
	//
	//		//���� �̻��� index��� �����Ѿ� ����
	//		if (-1 == current_space_index) continue;
	//		//��й�
	//		//std::cout << "BulletManager " << current_space_index << std::endl;
	//		m_ppSpace[current_space_index]->GetpBulletManager()->AddBullet((*Iter));
	//		Iter++;
	//	}
	//}
}
//���� ��Ʈ��


//�ڽ��� �ִ� ������ ã�� �Լ� �ش� ������ ��ȣ�� �����Ѵ�.
int space_controller::SearchSpace(XMVECTOR position){

	XMFLOAT3 xmfPos;
	XMStoreFloat3(&xmfPos, position);
	int x = xmfPos.x;
	int y = xmfPos.y;
	int z = xmfPos.z;


	//�ڽ��� ��ġ�� �̿��� �ε����� ����
	int indexX = (int)x / one_size;
	int indexY = (int)y / one_size;
	int indexZ = (int)z / one_size;



	int index = indexX + (indexY * one_side_space_count) + (indexZ * one_side_space_count * one_side_space_count);

	//���� ó�� ���� ��
	if (index < 0 || index >= space_num){
		return -1;
	}
	if (x < 0 || y < 0 || z < 0 ||
		x > size || y > size || z > size){
		return -1;
	}
	//���� ó�� ���� ��


	return index;
}
Index space_controller::SearchSpace_Index(XMVECTOR position){

	XMFLOAT3 xmfPos;
	XMStoreFloat3(&xmfPos, position);
	int x = xmfPos.x;
	int y = xmfPos.y;
	int z = xmfPos.z;


	//�ڽ��� ��ġ�� �̿��� �ε����� ����
	int indexX = (int)x / one_size;
	int indexY = (int)y / one_size;
	int indexZ = (int)z / one_size;



	int index = indexX + (indexY * one_side_space_count) + (indexZ * one_side_space_count * one_side_space_count);

	//���� ó�� ���� ��
	if (index < 0 || index >= space_num){
		return Index(-1, -1, -1);
	}
	if (x < 0 || y < 0 || z < 0 ||
		x > size || y > size || z > size){
		return Index(-1, -1, -1);
	}
	//���� ó�� ���� ��


	return Index(indexX, indexY, indexZ);
}


//�ش� ������ �ε��� xyz�� spacenum���� �ٲٴ� �Լ�
int space_controller::GetSpaceIndexNum(Index& index){
	return index.x + (index.y * one_side_space_count) + (index.z * one_side_space_count * one_side_space_count);
}

//�ش� ������ �ε����� ��ȿ���� �˻��ϴ� �Լ�
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
�ڽ��� �׷��� �ϴ� �������� ��ȣ�迭�� ��ȯ�ϴ� �Լ�
<in>
�ڽ��� index X Y Z -> ������ �޾ƿ´�. �� ó���� ���⼭ �Ѵ�.

<out>
space_controller�� <space_counter, render_space_indexs>�� ���ŵ�.
render_space_indexs = �׸��� �׷��� �� �ε����� �迭 �� ó�� ������
<space_conrtoller> �� ������ �ִ� �迭�̴�. ���̴� ������ �̿��� �ִ� � �������� �� �� �ִ�.
space_counter = �׸��� �׷��� �ϴ� ������ ���� �̴�. ��� ���������� �� �� �� �ֱ⿡ ����ؼ� �־��ش�.

<return>
bool ����, ���� ��ȯ�Ǵ� ������ ���� ��� false�� ���� �Ѵ�.
*/
//
bool space_controller::SearchSpaces(CConnectedSession* pConnectedSession){

	XMVECTOR position = pConnectedSession->GetPlayer()->GetPlayerPosition();

	XMFLOAT3 xmfPos;
	XMStoreFloat3(&xmfPos, position);
	int x = xmfPos.x;
	int y = xmfPos.y;
	int z = xmfPos.z;


	//�ڽ��� ��ġ�� �̿��� �ε����� ����
	//���⼭ ������ �߻� -0.4 / one_size = 0��.. 
	Index index = Index((int)x / one_size, (int)y / one_size, (int)z / one_size);

	//���̴� ������ �������� ���� ���� ������ �ε���
	x = index.x - visual_field_level;
	y = index.y - visual_field_level;
	z = index.z - visual_field_level;
	//���̴� ������ �������� ���� ���� ������ �ε���

	int space_counter = 0;//��� ������ �ִ��� ī��Ʈ �� ī����
	//���� �ؾ��� ���� �ε��� �迭 �����͸� �Ѱ� �޴´�
	int* render_space_indexs = pConnectedSession->GetPlayer()->Getrender_space_indexs();

	//x y z�� ���Ͽ� 
	for (int i = 0; i < visual_field_size; i++){
		for (int j = 0; j < visual_field_size; j++){
			for (int k = 0; k < visual_field_size; k++){
				Index currentindex = Index(x + i, y + j, z + k);
				if (CheckSpaceNum(currentindex)){//�ش� ������ ��ȿ �ϴٸ�
					//�ش� ������ space_controller�� �׸��׸� ���� �迭�� ���� �ִ´�.
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
	printf("������ ũ�� : %d \n������ ���� : %d \n���� �ϳ��� ũ�� : %d\n�� ���̵忡 �ִ� ������ ���� : %d\n������ ���� : %d \n",
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

	//���̴� ������ �������� ���� ���� ������ �ε���
	x = index.x - visual_field_level;
	y = index.y - visual_field_level;
	z = index.z - visual_field_level;
	//���̴� ������ �������� ���� ���� ������ �ε���


	//x y z�� ���Ͽ� 

	std::list<CPlayer*> lNearPlayer;

	for (int i = 0; i < visual_field_size; i++){
		for (int j = 0; j < visual_field_size; j++){
			for (int k = 0; k < visual_field_size; k++){
				Index currentindex = Index(x + i, y + j, z + k);
				if (CheckSpaceNum(currentindex)){//�ش� ������ ��ȿ �ϴٸ�
					//�ش� �������� �÷��̾ ���´�.
					std::list<CConnectedSession*> lConnectedSession;
					if (m_ppSpace[GetSpaceIndexNum(currentindex)]->GetConnectedSessionList(lConnectedSession)){
						//�ִٸ�
						//��� player push_back
						for (auto i : lConnectedSession){
							//�� �ڽ��� ����
							if (i->GetPlayer()->GetID() == pPlayer->GetID()) continue;
							lNearPlayer.push_back(i->GetPlayer());
#ifdef _DEBUG
							//std::cout << "player " << i->GetPlayer()->GetID() << "�� ��ó�� �ִ�." << std::endl;
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

	//���̴� ������ �������� ���� ���� ������ �ε���
	x = index.x - visual_field_level;
	y = index.y - visual_field_level;
	z = index.z - visual_field_level;
	//���̴� ������ �������� ���� ���� ������ �ε���


	//x y z�� ���Ͽ� 

	std::list<CPlayer*> lNearPlayer;

	for (int i = 0; i < visual_field_size; i++){
		for (int j = 0; j < visual_field_size; j++){
			for (int k = 0; k < visual_field_size; k++){
				Index currentindex = Index(x + i, y + j, z + k);
				if (CheckSpaceNum(currentindex)){//�ش� ������ ��ȿ �ϴٸ�
					//�ش� �������� �÷��̾ ���´�.
					std::list<CConnectedSession*> lConnectedSession;
					if (m_ppSpace[GetSpaceIndexNum(currentindex)]->GetConnectedSessionList(lConnectedSession)){
						//�ִٸ�
						//��� player push_back
						for (auto i : lConnectedSession){

							lNearPlayer.push_back(i->GetPlayer());
#ifdef _DEBUG
							//std::cout << "player " << i->GetPlayer()->GetID() << "�� ��ó�� �ִ�." << std::endl;
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

	//���̴� ������ �������� ���� ���� ������ �ε���
	x = index.x - visual_field_level;
	y = index.y - visual_field_level;
	z = index.z - visual_field_level;
	//���̴� ������ �������� ���� ���� ������ �ε���


	//x y z�� ���Ͽ� 

	std::list<CPlayer*> lNearPlayer;

	for (int i = 0; i < visual_field_size; i++){
		for (int j = 0; j < visual_field_size; j++){
			for (int k = 0; k < visual_field_size; k++){
				Index currentindex = Index(x + i, y + j, z + k);
				if (CheckSpaceNum(currentindex)){//�ش� ������ ��ȿ �ϴٸ�
					//�ش� �������� �÷��̾ ���´�.
					std::list<CConnectedSession*> lConnectedSession;
					if (m_ppSpace[GetSpaceIndexNum(currentindex)]->GetConnectedSessionList(lConnectedSession)){
						//�ִٸ�
						//��� player push_back
						for (auto i : lConnectedSession){
							lNearPlayer.push_back(i->GetPlayer());
#ifdef _DEBUG
							//std::cout << "player " << i->GetPlayer()->GetID() << "�� ��ó�� �ִ�." << std::endl;
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

	//���̴� ������ �������� ���� ���� ������ �ε���
	x = index.x - visual_field_level;
	y = index.y - visual_field_level;
	z = index.z - visual_field_level;
	//���̴� ������ �������� ���� ���� ������ �ε���


	//x y z�� ���Ͽ� 
	std::list<CDynamicObject*> lNearObject;
	for (int i = 0; i < visual_field_size; i++){
		for (int j = 0; j < visual_field_size; j++){
			for (int k = 0; k < visual_field_size; k++){
				Index currentindex = Index(x + i, y + j, z + k);
				if (CheckSpaceNum(currentindex)){//�ش� ������ ��ȿ �ϴٸ�wwwwwww
					//�ش� �������� �÷��̾ ���´�.
					std::list<CDynamicObject*> lObject;
					if (m_ppSpace[GetSpaceIndexNum(currentindex)]->GetMovingObjectList(lObject)){
						//�ִٸ�
						//��� player push_back
						for (auto i : lObject){
							lNearObject.push_back(i);
							//pConnectedSession->GetPlayer()->PutViewList_OBJ(i);
							//pConnectedSession->GetPlayer()->PutObject(i);
							//#ifdef _DEBUG
							//							std::cout << "player " << i->GetPlayer()->GetID() << "�� ��ó�� �ִ�." << std::endl;
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

	//���̴� ������ �������� ���� ���� ������ �ε���
	x = index.x - visual_field_level;
	y = index.y - visual_field_level;
	z = index.z - visual_field_level;
	//���̴� ������ �������� ���� ���� ������ �ε���


	//x y z�� ���Ͽ� 

	for (int i = 0; i < visual_field_size; i++) {
		for (int j = 0; j < visual_field_size; j++) {
			for (int k = 0; k < visual_field_size; k++) {
				Index currentindex = Index(x + i, y + j, z + k);
				if (CheckSpaceNum(currentindex)) {//�ش� ������ ��ȿ �ϴٸ�wwwwwww
					//�ش� �������� �÷��̾ ���´�.
					std::list<CDynamicObject*> lObject;
					if (m_ppSpace[GetSpaceIndexNum(currentindex)]->GetMovingObjectList(lObject)) {
						//�ִٸ�
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





