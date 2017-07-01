#pragma once
#include <mutex>

class CObjectManager {
public:
	virtual void Begin() {};
	virtual void End() {};
	virtual void Animate(float fTimeElapced) {};

	virtual bool AddPlayer(CConnectedSession* pConnectedSession) { return true; };

	void lock() { m_Sync.lock(); }
	void unlock() { m_Sync.unlock(); }

private:
	std::mutex m_Sync;

public:
	CObjectManager() {};
	virtual ~CObjectManager() {};
};
