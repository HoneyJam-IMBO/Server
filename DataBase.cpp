#include "stdafx.h"
#include "DataBase.h"

DWORD WINAPI DBThreadCallback(LPVOID parameter)
{
	CDataBase *Owner = (CDataBase*)parameter;
	Owner->DBThreadCallback();

	return 0;
}
//ㅇㅇ
VOID CDataBase::DBThreadCallback() {
	int times = 0;

	std::cout << "DB thread start" << std::endl;
	//게임 중일때 동안
	while (1) {

		//std::cout << std::endl;
		Sleep(10);//1/100초 쉰 후에
		while (true) {
			//현제 시간을 받음
			if (!m_DataBaseQueue.empty()) {
				
				stDBQUEUE DBevent = popDBEvent();

				switch (DBevent.etype) {
				case LOADID:
					LoadUserInfo(DBevent);
					
					break;

				case SIGNUP:
					InsertUserInfo(DBevent);
				
					break;
				}

			}
			//
		}
	}
}
stDBQUEUE CDataBase::popDBEvent() {
	CThreadSync Sync;
	stDBQUEUE retval = m_DataBaseQueue.front();
	m_DataBaseQueue.pop();


	return retval;
}
void CDataBase::pushDBEvent(stDBQUEUE DBevent)
{
	CThreadSync Sync;
	m_DataBaseQueue.push(DBevent);
}

CDataBase::CDataBase()
{
}


CDataBase::~CDataBase()
{
}

BOOL CDataBase::Begin(HANDLE hIOCP) {

	memset(&m_DBOverlapped_ex, 0, sizeof(m_DBOverlapped_ex));

	m_hIOCP = hIOCP;

	// Allocate environment handle
	retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);

	// Set the ODBC version environment attribute
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
		retcode = SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0);

	// Allocate connection handle
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
		retcode = SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);

	// Set login timeout to 5 seconds
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
		SQLSetConnectAttr(hDbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, 0);

	// Connect to data source
	retcode = SQLConnect(hDbc, (SQLWCHAR*)L"Imbo_Server", SQL_NTS, (SQLWCHAR*)L"sa", SQL_NTS, (SQLWCHAR*)L"9558a1e82", SQL_NTS);

	// Allocate statement handle
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
		retcode = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);

	// Process data
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
		cout << "DB Connection Success!" << endl;
		return true;
	}

	m_pDBThread = new std::thread(::DBThreadCallback, this);

}

VOID CDataBase::End() {
	SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

	SQLDisconnect(hDbc);

	SQLFreeHandle(SQL_HANDLE_DBC, hDbc);

	SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
}

void CDataBase::LoadUserInfo(stDBQUEUE DBevent)
{
	SQLLEN oID, oPW;

	S_IDPW idpw;

	//wsprintf(sql_buf, L"EXEC dbo.ID_Check_SP2 %s", ID);
	//MultiByteToWideChar(CP_UTF8, 0, sql_buf, strlen(sql_buf), sql_data, sizeof sql_data / sizeof *sql_data);
	//sql_data[strlen(sql_buf)] = '\0';
	SQLExecDirect(hStmt, DBevent.ExecCode, SQL_NTS);

	SQLBindCol(hStmt, 1, SQL_C_WCHAR, (SQLPOINTER)idpw.ID, sizeof(idpw.ID),
		&oID);
	SQLBindCol(hStmt, 2, SQL_C_WCHAR, (SQLPOINTER)idpw.PW, sizeof(idpw.PW),
		&oPW);


	while (SQLFetch(hStmt) != SQL_NO_DATA)
	{
		wcout << idpw.ID << " , " << idpw.PW << endl;
	}

	for (int i = 0; i < 10; i++) {
		if (idpw.PW[i] == ' ')
			idpw.PW[i] = '\0';
	}
	for (int i = 0; i < 10; i++) {
		if (idpw.ID[i] == ' ')
			idpw.ID[i] = '\0';
	}
	
	DB_ST *dbover = new DB_ST;
	dbover->etype = DBevent.etype;
	dbover->idpw = idpw;
	dbover->pSession = DBevent.pSession;

	m_DBOverlapped_ex.IoType = IO_DB;
	m_DBOverlapped_ex.Object = dbover;

	PostQueuedCompletionStatus(m_hIOCP, 1, NULL, reinterpret_cast<OVERLAPPED*>(&m_DBOverlapped_ex));

}

void CDataBase::InsertUserInfo(stDBQUEUE DBevent)
{


	//SQLLEN oID, oPW;
	//wchar_t sql_buf[100];
	//wchar_t sql_data[100];


	//wsprintf(sql_buf, L"EXEC dbo.Sign_Up_SP2 %s, %s", id, pw);
	//MultiByteToWideChar(CP_UTF8, 0, sql_buf, strlen(sql_buf), sql_data, sizeof sql_data / sizeof *sql_data);
	//sql_data[strlen(sql_buf)] = '\0';
	SQLExecDirect(hStmt, DBevent.ExecCode, SQL_NTS);


	
}
