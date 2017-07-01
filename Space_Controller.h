#pragma once

#include <mutex>

#include "Space.h"
#include "default_space.h"
#include "planet_space.h"
#include "mine_space.h"


class Index{
public:
	int x;
	int y;
	int z;

	Index();
	Index(int x, int y, int z);
	~Index();
	void operator =(Index& tmp);
	Index& operator +(Index& tmp);
	Index& operator -(Index& tmp);
};


class space_controller {
private:
	//lock
	std::mutex m_Sync;
	//������ ũ��
	int size;
	//������ ���� 
	int level;
	//���� �ϳ��� ũ��
	int one_size;
	//�� ���̵忡 �ִ� ������ ����
	int one_side_space_count;
	//������ ����
	int space_num;


	//�Ѿ� �Ŵ���
	//BulletManager* m_pBulletManager;
	BulletManager* m_pBlockBulletManager;

	//�׸� �׷��� �ϴ� ������
	int* render_space_indexs;
	int space_counter;

	int visual_field_level;
	int visual_field_size;
	//�׸� �׷��� �ϴ� ������

	//���� �ִ� �������� ���� ��ü�� ��� ����Ʈ
	std::list<CSpaceObject*> m_lBlockObject;
	//���� �ִ� �������� ���� ��ü�� ��� ����Ʈ

	//������ ��ü���� �׸� ���̴� ����Ʈ
	//DLinkedList<CShader*> m_lShader;
	//CShader* m_pShader;
	//CShader* m_pMovingShader;

	//������
	space** m_ppSpace;


public:
	void lock(){ m_Sync.lock(); }
	void unlock(){ m_Sync.unlock(); }

	//�༺��
	std::vector<CDynamicObject*> m_vPlanetObject;

	//space active ����
	virtual void wakeUpSpace(CPlayer* pPlayer);
	//active ����


	//�þ�ó��
	std::list<CDynamicObject*> GetNearObjectList(CPlayer* pPlayer);
	std::list<CPlayer*> GetNearPlayerList(CDynamicObject* pObject);
	std::list<CPlayer*> GetNearPlayerList(CPlayer* pPlayer);

	virtual std::list<CPlayer*> GetNearPlayerList(XMFLOAT3 xmfPos);

	void ProcView_NearObjectList(CPlayer* pPlayer);

	void AddBlockObject(CSpaceObject* obj);
	//ť�� ���̴� ������ �迭
	//int								m_nCubeInstancingShaders;
	//CGSCubeInstancingShader*		m_pGSSpaceShader;

	virtual void AddPlayer(CConnectedSession* pConnectedSession);
	space_controller();
	~space_controller();


	virtual void BuildWorld(CServerIocp* pServerIocp, int objnum);

	//������ ���ֹ��� �ʴ� ��ü ����
	virtual void CreateStaticObject(CServerIocp* pServerIocp, int objnum);
	virtual void InitSpaces(CServerIocp* pServerIocp, int si, int le, int vfl);

	//���� ��ġ�� �����ϸ� �� �ֺ��� �ֵ鸸 �׸��� �ϸ� ���� �ʳ�.
	//�÷��̾��� ��ġ�� ���޹ް� ����.
	//�������� �������� ����
	//�÷��̾��� ��ġ => ���� ���� => �ֺ� ���� => �׸��� �׷��� �ϴ� ����

	//���� ��Ʈ��
	//���� ��ü�� render
	//void RenderSpaces(ID3D11DeviceContext *pd3dDeviceContext, CCamera *pCamera);
	//���� animate
	virtual void AnimateSpaces(float fTimeElapsed, XMVECTOR position);
	//���� ��Ʈ��


	//���� ��Ʈ��
	//���� render
	//���� ����
	//void SprayedPacketVer1();
	void WriteEnterSpacePacketVer1(CConnectedSession* pConnectedSession);
	//�ټ� ����
	void PrepareRenderVer2(XMVECTOR position);

	//void RenderWorld(ID3D11DeviceContext *pd3dDeviceContext, CCamera *pCamera, XMFLOAT3 position);
	//���� Animate
	virtual void AnimateWorld(float fTimeElapsed);
	//���� ��Ʈ��

	//void CreateWireFrameRasterizerState(ID3D11Device *pd3dDevice);

	//�ڽ��� �ִ� ������ ã�� �Լ� �ش� ������ ��ȣ�� �����Ѵ�.
	int SearchSpace(XMVECTOR position);
	Index SearchSpace_Index(XMVECTOR position);

	//�ش� ������ �ε��� xyz�� spacenum���� �ٲٴ� �Լ�
	int GetSpaceIndexNum(Index& index);

	//�ش� ������ �ε����� ��ȿ���� �˻��ϴ� �Լ�
	bool CheckSpaceNum(Index& index);

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
	bool SearchSpaces(CConnectedSession* pConnectedSession);

	void ShowSpaceInfo();


	//set get
	//�Ѿ�
	BulletManager* GetpBlockBulletManager(){ return m_pBlockBulletManager; }
	//	BulletManager* GetpBulletManager(){ return m_pBulletManager; }
	int GetSpaceNum(){ return space_num; }
	BOOL GetBlockObjectList(std::list<CSpaceObject*>& lBlockObject);
	space** GetSpaces(){ return m_ppSpace; }

	//������ ũ��
	int Getsize(){ return size; }
	//������ ���� 
	int Getlevel(){ return level; }
	//���� �ϳ��� ũ��
	int Getone_size(){ return one_size; }
	//�� ���̵忡 �ִ� ������ ����
	int Getone_side_space_count(){ return one_side_space_count; }
	//������ ����
	int Getspace_num(){ return space_num; }

	int Getvisual_field_level(){ return visual_field_level; }
	int Getvisual_field_size(){ return visual_field_size; }

};
