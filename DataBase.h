#pragma once


class CDataBase : public CMultiThreadSync<CDataBase>
{

private:
	SQLHENV hEnv;
	SQLHDBC hDbc;
	SQLHSTMT hStmt;
	SQLRETURN retcode;
	HANDLE m_hIOCP;
	OVERLAPPED_EX m_DBOverlapped_ex;

	//queue<stDBQUEUE> m_DataBaseQueue;
	std::queue<stDBQUEUE> m_DataBaseQueue;
	
	std::thread* m_pDBThread;

public:
	VOID DBThreadCallback();

	stDBQUEUE popDBEvent();

	void pushDBEvent(stDBQUEUE DBevent);

	CDataBase();
	~CDataBase();

	BOOL Begin(HANDLE hIOCP);

	VOID End();

	// ID, PW 불러오기
	void LoadUserInfo(stDBQUEUE DBevent);
	// ID, PW 등록
	void InsertUserInfo(stDBQUEUE DBevent);
	
	



};

