#include "stdafx.h"
#include "ConnectedSession.h"

CConnectedSession::CConnectedSession(VOID)
{
	// ���� �Ǿ����� �Ǻ��ϴ� ����
	m_bConnected = FALSE;

	//�����ڿ��� ����� ��Ȱ��
	m_pPlayer = new CGameObject(this);

}

void CConnectedSession::CreatePlayer() {
	m_pPlayer->Begin();

}
//CConnectedSession::CConnectedSession(int visual_field_size)
//{
//	// ���� �Ǿ����� �Ǻ��ϴ� ����
//	m_bConnected = FALSE;
//
//
//	//��ġ �ʱ�ȭ ? 0321 �ǹ�
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
	// ����ȭ ��ü
	CThreadSync Sync;

	m_pPlayer->Restart();


	// ��ü�� ������ �ݴϴ�.
	End();

	// ��ü�� �ٽ� �����ϰ� Accept���·� ����� �ݴϴ�.
	// Accept�� �ϱ����ؼ��� �ݵ�� hListenSocket ���� �ʿ��մϴ�.
	// �� ���� CServerIocp�� ����� m_pListen�� GetSocket���� �޾ƿ� �� �ֽ��ϴ�.
	return Begin() && Accept(hListenSocket);
}
