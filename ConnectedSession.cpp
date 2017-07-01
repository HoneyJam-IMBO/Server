#include "stdafx.h"
#include "ConnectedSession.h"

CConnectedSession::CConnectedSession(VOID)
{
	// 접속 되었는지 판별하는 변수
	m_bConnected = FALSE;

	//생성자에서 만들고 재활용
	m_pPlayer = new CGameObject(this);

}

void CConnectedSession::CreatePlayer() {
	m_pPlayer->Begin();

}
//CConnectedSession::CConnectedSession(int visual_field_size)
//{
//	// 접속 되었는지 판별하는 변수
//	m_bConnected = FALSE;
//
//
//	//위치 초기화 ? 0321 의문
//	m_pPlayer = new CPlayer(visual_field_size);
//	m_pPlayer->SetPosition(0.f, 0.f, 100.f);
//
//}

CConnectedSession::~CConnectedSession(VOID)
{
	if (m_pPlayer) delete m_pPlayer;
}

BOOL CConnectedSession::Restart(SOCKET hListenSocket)
{
	// 동기화 개체
	CThreadSync Sync;

	m_pPlayer->Restart();


	// 개체를 종료해 줍니다.
	End();

	// 개체를 다시 시작하고 Accept상태로 만들어 줍니다.
	// Accept를 하기위해서는 반드시 hListenSocket 값이 필요합니다.
	// 이 값은 CServerIocp의 멤버인 m_pListen의 GetSocket으로 받아올 수 있습니다.
	return Begin() && Accept(hListenSocket);
}
