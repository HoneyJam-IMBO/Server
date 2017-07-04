#pragma once

// ConnectedSession�� �����ϴ� Ŭ����
// ���� ������ ȯ�濡�� �����ϰ� ����ϱ� ���ؼ� CMultiThreadSync�� ��ӹ޽��ϴ�.
class CConnectedSessionManager : public CMultiThreadSync<CConnectedSessionManager>
{
public:
	CConnectedSessionManager(VOID);
	virtual ~CConnectedSessionManager(VOID);

	// �����ϴ� �Լ�
	BOOL Begin(SOCKET hListenSocket);
	// �����ϴ� �Լ�
	VOID End(VOID);

	// ���ӵ� ��� ConnectedSession�� ��Ŷ�� �����ϴ� �Լ�
	VOID WriteAll(DWORD dwProtocol, BYTE *pData, DWORD dwLength);

	//vecter getter
	std::vector<CConnectedSession*> GetvConnectedSessions() { return m_vConnectedSessions; }
private:
	// ������ ConnectedSession��ü�� �����͸� �����ϴ� Vector
	std::vector<CConnectedSession*> m_vConnectedSessions;
};