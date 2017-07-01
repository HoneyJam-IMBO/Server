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
	//공간의 크기
	int size;
	//공간의 레벨 
	int level;
	//공간 하나의 크기
	int one_size;
	//한 사이드에 있는 공간의 개수
	int one_side_space_count;
	//공간의 개수
	int space_num;


	//총알 매니져
	//BulletManager* m_pBulletManager;
	BulletManager* m_pBlockBulletManager;

	//그림 그려야 하는 공간들
	int* render_space_indexs;
	int space_counter;

	int visual_field_level;
	int visual_field_size;
	//그림 그려야 하는 공간들

	//원래 있던 공간에서 나간 객체를 담는 리스트
	std::list<CSpaceObject*> m_lBlockObject;
	//원래 있던 공간에서 나간 객체를 담는 리스트

	//공간의 객체들을 그릴 쉐이더 리스트
	//DLinkedList<CShader*> m_lShader;
	//CShader* m_pShader;
	//CShader* m_pMovingShader;

	//공간들
	space** m_ppSpace;


public:
	void lock(){ m_Sync.lock(); }
	void unlock(){ m_Sync.unlock(); }

	//행성들
	std::vector<CDynamicObject*> m_vPlanetObject;

	//space active 관리
	virtual void wakeUpSpace(CPlayer* pPlayer);
	//active 관리


	//시야처리
	std::list<CDynamicObject*> GetNearObjectList(CPlayer* pPlayer);
	std::list<CPlayer*> GetNearPlayerList(CDynamicObject* pObject);
	std::list<CPlayer*> GetNearPlayerList(CPlayer* pPlayer);

	virtual std::list<CPlayer*> GetNearPlayerList(XMFLOAT3 xmfPos);

	void ProcView_NearObjectList(CPlayer* pPlayer);

	void AddBlockObject(CSpaceObject* obj);
	//큐브 쉐이더 포인터 배열
	//int								m_nCubeInstancingShaders;
	//CGSCubeInstancingShader*		m_pGSSpaceShader;

	virtual void AddPlayer(CConnectedSession* pConnectedSession);
	space_controller();
	~space_controller();


	virtual void BuildWorld(CServerIocp* pServerIocp, int objnum);

	//공간에 구애받지 않는 객체 생성
	virtual void CreateStaticObject(CServerIocp* pServerIocp, int objnum);
	virtual void InitSpaces(CServerIocp* pServerIocp, int si, int le, int vfl);

	//뭔가 위치를 전달하면 그 주변에 애들만 그리게 하면 되지 않나.
	//플레이어의 위치를 전달받게 하자.
	//공간분할 렌더링의 로직
	//플레이어의 위치 => 현제 공간 => 주변 공간 => 그림을 그려야 하는 공간

	//공간 컨트롤
	//공간 자체를 render
	//void RenderSpaces(ID3D11DeviceContext *pd3dDeviceContext, CCamera *pCamera);
	//공간 animate
	virtual void AnimateSpaces(float fTimeElapsed, XMVECTOR position);
	//공간 컨트롤


	//월드 컨트롤
	//월드 render
	//단일 공간
	//void SprayedPacketVer1();
	void WriteEnterSpacePacketVer1(CConnectedSession* pConnectedSession);
	//다수 공간
	void PrepareRenderVer2(XMVECTOR position);

	//void RenderWorld(ID3D11DeviceContext *pd3dDeviceContext, CCamera *pCamera, XMFLOAT3 position);
	//월드 Animate
	virtual void AnimateWorld(float fTimeElapsed);
	//월드 컨트롤

	//void CreateWireFrameRasterizerState(ID3D11Device *pd3dDevice);

	//자신이 있는 공간을 찾는 함수 해당 공간의 번호를 리턴한다.
	int SearchSpace(XMVECTOR position);
	Index SearchSpace_Index(XMVECTOR position);

	//해당 공간의 인덱스 xyz를 spacenum으로 바꾸는 함수
	int GetSpaceIndexNum(Index& index);

	//해당 공간의 인덱스가 유효한지 검사하는 함수
	bool CheckSpaceNum(Index& index);

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
	bool SearchSpaces(CConnectedSession* pConnectedSession);

	void ShowSpaceInfo();


	//set get
	//총알
	BulletManager* GetpBlockBulletManager(){ return m_pBlockBulletManager; }
	//	BulletManager* GetpBulletManager(){ return m_pBulletManager; }
	int GetSpaceNum(){ return space_num; }
	BOOL GetBlockObjectList(std::list<CSpaceObject*>& lBlockObject);
	space** GetSpaces(){ return m_ppSpace; }

	//공간의 크기
	int Getsize(){ return size; }
	//공간의 레벨 
	int Getlevel(){ return level; }
	//공간 하나의 크기
	int Getone_size(){ return one_size; }
	//한 사이드에 있는 공간의 개수
	int Getone_side_space_count(){ return one_side_space_count; }
	//공간의 개수
	int Getspace_num(){ return space_num; }

	int Getvisual_field_level(){ return visual_field_level; }
	int Getvisual_field_size(){ return visual_field_size; }

};
