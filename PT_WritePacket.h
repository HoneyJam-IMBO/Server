#pragma once

inline DWORD WRITE_PT_ENTER_SERVER_ALL(BYTE *buffer, S_PT_ENTER_SERVER_ALL &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD_PTR(parameter.ID);
	Stream->WriteFloat(parameter.X);
	Stream->WriteFloat(parameter.Y);
	Stream->WriteFloat(parameter.Z);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_LEAVE_SERVER_ALL(BYTE *buffer, S_PT_LEAVE_SERVER_ALL &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD_PTR(parameter.ID);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ENTER_SERVER_S(BYTE *buffer, S_PT_ENTER_SERVER_S &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD_PTR(parameter.MYID);
	Stream->WriteFloat(parameter.X);
	Stream->WriteFloat(parameter.Y);
	Stream->WriteFloat(parameter.Z);

	return Stream->GetLength();
}


inline DWORD WRITE_PT_KEY_INPUT_CS(BYTE *buffer, S_PT_KEY_INPUT_CS &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(parameter.DIRECTION);
	Stream->WriteFloat(parameter.X);
	Stream->WriteFloat(parameter.Y);
	Stream->WriteFloat(parameter.Z);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_KEY_INPUT_ALL_SC(BYTE *buffer, S_PT_KEY_INPUT_ALL_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD_PTR(parameter.ID);
	Stream->WriteDWORD(parameter.DIRECTION);
	Stream->WriteFloat(parameter.X);
	Stream->WriteFloat(parameter.Y);
	Stream->WriteFloat(parameter.Z);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_MOUSE_INPUT_CS(BYTE *buffer, S_PT_MOUSE_INPUT_CS &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteFloat(parameter.CXDELTA);
	Stream->WriteFloat(parameter.CYDELTA);
	Stream->WriteDWORD(parameter.MOUSEBUTTON);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_MOUSE_INPUT_ALL_SC(BYTE *buffer, S_PT_MOUSE_INPUT_ALL_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD_PTR(parameter.ID);
	Stream->WriteFloat(parameter.CXDELTA);
	Stream->WriteFloat(parameter.CYDELTA);
	Stream->WriteDWORD(parameter.MOUSEBUTTON);


	return Stream->GetLength();
}

inline DWORD WRITE_MOUSE_BUTTON_INPUT_CS(BYTE *buffer, S_PT_MOUSE_BUTTON_INPUT_CS &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(parameter.MOUSEBUTTON);

	return Stream->GetLength();
}

inline DWORD WRITE_MOUSE_BUTTON_INPUT_ALL_SC(BYTE *buffer, S_PT_MOUSE_BUTTON_INPUT_ALL_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD_PTR(parameter.ID);
	Stream->WriteDWORD(parameter.MOUSEBUTTON);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_FIRE_BULLET_ALL_SC(BYTE *buffer, S_PT_FIRE_BULLET_ALL_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD_PTR(parameter.ID);
	Stream->WriteDWORD_PTR(parameter.BULLETID);

	return Stream->GetLength();
}


inline DWORD WRITE_PT_PUT_OBJ_SC(BYTE *buffer, S_PT_PUT_OBJ_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD_PTR(parameter.ID);
	Stream->WriteInt32(parameter.TAG);
	Stream->WriteFloat(parameter.Y);
	Stream->WriteFloat(parameter.X);
	Stream->WriteFloat(parameter.Z);

	Stream->WriteFloat(parameter.MOVINGDIR_Y);
	Stream->WriteFloat(parameter.MOVINGDIR_X);
	Stream->WriteFloat(parameter.MOVINGDIR_Z);

	Stream->WriteFloat(parameter.SPD);
	Stream->WriteFloat(parameter.ACCSPD);

	return Stream->GetLength();

}

inline DWORD WRITE_PT_REMOVE_OBJ_SC(BYTE *buffer, S_PT_REMOVE_OBJ_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD_PTR(parameter.ID);
	Stream->WriteInt32(parameter.TAG);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_CHANGE_STATE_OBJ_SC(BYTE *buffer, S_PT_CHANGE_STATE_OBJ_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD_PTR(parameter.ID);
	Stream->WriteInt32(parameter.TAG);
	Stream->WriteDWORD(parameter.DIRECTION);

	Stream->WriteFloat(parameter.Y);
	Stream->WriteFloat(parameter.X);
	Stream->WriteFloat(parameter.Z);

	Stream->WriteFloat(parameter.MOVINGDIR_Y);
	Stream->WriteFloat(parameter.MOVINGDIR_X);
	Stream->WriteFloat(parameter.MOVINGDIR_Z);

	Stream->WriteFloat(parameter.SPD);
	Stream->WriteFloat(parameter.ACCSPD);

	return Stream->GetLength();
}


inline DWORD WRITE_PT_PUT_OBJS_SC(BYTE *buffer, S_PT_PUT_OBJS_SC &parameter){
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteInt32(parameter.COUNT);
	for (int i = 0; i < parameter.COUNT; ++i) {

		Stream->WriteDWORD_PTR(parameter.ID[i]);
		Stream->WriteInt32(parameter.TAG[i]);
		Stream->WriteFloat(parameter.X[i]);
		Stream->WriteFloat(parameter.Y[i]);
		Stream->WriteFloat(parameter.Z[i]);

		Stream->WriteFloat(parameter.MOVINGDIR_X[i]);
		Stream->WriteFloat(parameter.MOVINGDIR_Y[i]);
		Stream->WriteFloat(parameter.MOVINGDIR_Z[i]);

		Stream->WriteFloat(parameter.SPD[i]);
		Stream->WriteFloat(parameter.ACCSPD[i]);
	}

	return Stream->GetLength();
}


inline DWORD WRITE_PT_REMOVE_OBJS_SC(BYTE *buffer, S_PT_REMOVE_OBJS_SC &parameter) {
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteInt32(parameter.COUNT);
	for (int i = 0; i < parameter.COUNT; ++i) {

		Stream->WriteDWORD_PTR(parameter.ID[i]);
		Stream->WriteInt32(parameter.TAG[i]);
		
	}

	return Stream->GetLength();
}

inline DWORD WRITE_PT_PUT_PLAYER_SC(BYTE *buffer, S_PT_PUT_PLAYER_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD_PTR(parameter.ID);
	Stream->WriteDWORD(parameter.DIRECTION);
	Stream->WriteFloat(parameter.RIGHTX);
	Stream->WriteFloat(parameter.RIGHTY);
	Stream->WriteFloat(parameter.RIGHTZ);
	Stream->WriteFloat(parameter.UPX);
	Stream->WriteFloat(parameter.UPY);
	Stream->WriteFloat(parameter.UPZ);
	Stream->WriteFloat(parameter.LOOKX);
	Stream->WriteFloat(parameter.LOOKY);
	Stream->WriteFloat(parameter.LOOKZ);
	Stream->WriteFloat(parameter.POSX);
	Stream->WriteFloat(parameter.POSY);
	Stream->WriteFloat(parameter.POSZ);
	
	return Stream->GetLength();
}

inline DWORD WRITE_PT_REMOVE_PLAYER_SC(BYTE *buffer, S_PT_REMOVE_PLAYER_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD_PTR(parameter.ID);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_CHANGE_STATE_PLAYER_SC(BYTE *buffer, S_PT_CHANGE_STATE_PLAYER_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD_PTR(parameter.ID);
	Stream->WriteDWORD(parameter.DIRECTION);

	Stream->WriteFloat(parameter.Y);
	Stream->WriteFloat(parameter.X);
	Stream->WriteFloat(parameter.Z);

	return Stream->GetLength();
}

///////////////////////////////////////////////////
///////////////////////////////////////////////////
///////////////////////////////////////////////////


inline DWORD WRITE_PT_LOGIN_SERVER_SUC(BYTE *buffer)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	return Stream->GetLength();
}
inline DWORD WRITE_PT_LOGIN_SERVER_ALREADY(BYTE *buffer)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	return Stream->GetLength();
}
inline DWORD WRITE_PT_LOGIN_SERVER_FAIL(BYTE *buffer)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_SIGN_UP_SUC_SC(BYTE *buffer)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_SIGN_UP_FAIL_SC(BYTE *buffer)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	return Stream->GetLength();
}
/////////////////////////////////青己柳涝
inline DWORD WRITE_PT_ENTER_EARTH_CS(BYTE *buffer)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ENTER_EARTH_FAIL(BYTE *buffer)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ENTER_EARTH_SUC(BYTE *buffer, DWORD_PTR MYID, INT TEAM, FLOAT X, FLOAT Y, FLOAT Z)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD_PTR(MYID);
	Stream->WriteInt32(TEAM);
	Stream->WriteFloat(X);
	Stream->WriteFloat(Y);
	Stream->WriteFloat(Z);

	return Stream->GetLength();
}
/////////////////////////////////////////青己柳涝

inline DWORD WRITE_PT_LOGIN_CS(BYTE *buffer, WCHAR* ID, WCHAR* PW)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteWCHARs(ID, 10);
	Stream->WriteWCHARs(PW, 10);


	return Stream->GetLength();
}
inline DWORD WRITE_PT_SIGN_UP_CS(BYTE *buffer, WCHAR* ID, WCHAR* PW)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteWCHARs(ID, 10);
	Stream->WriteWCHARs(PW, 10);


	return Stream->GetLength();
}

inline DWORD WRITE_PT_ENTER_SERVER_FAIL(BYTE *buffer)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_FREQUENCY_MOVE_CS(BYTE *buffer,INT TYPE, DWORD_PTR ID, FLOAT x, FLOAT y, FLOAT z)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteInt32(TYPE);
	Stream->WriteDWORD_PTR(ID);
	Stream->WriteFloat(x);
	Stream->WriteFloat(y);
	Stream->WriteFloat(z);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_FREQUENCY_MOVE_SC(BYTE *buffer, INT TYPE, DWORD_PTR ID, FLOAT x, FLOAT y, FLOAT z)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteInt32(TYPE);
	Stream->WriteDWORD_PTR(ID);
	Stream->WriteFloat(x);
	Stream->WriteFloat(y);
	Stream->WriteFloat(z);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ENTER_SERVER_ALL(BYTE *buffer, DWORD_PTR id, FLOAT X, FLOAT Y, FLOAT Z)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD_PTR(id);
	Stream->WriteFloat(X);
	Stream->WriteFloat(Y);
	Stream->WriteFloat(Z);
	return Stream->GetLength();
}

inline DWORD WRITE_PT_LEAVE_SERVER_ALL(BYTE *buffer, DWORD_PTR id)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD_PTR(id);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ENTER_SERVER_S(BYTE *buffer, DWORD_PTR myid, FLOAT X, FLOAT Y, FLOAT Z)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD_PTR(myid);
	Stream->WriteDWORD_PTR(X);
	Stream->WriteDWORD_PTR(Y);
	Stream->WriteDWORD_PTR(Z);

	return Stream->GetLength();

	
}

inline DWORD WRITE_PT_KEY_INPUT_CS(BYTE *buffer, DWORD direction, FLOAT x, FLOAT y, FLOAT z)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(direction);
	Stream->WriteFloat(x);
	Stream->WriteFloat(y);
	Stream->WriteFloat(z);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_KEY_INPUT_ALL_SC(BYTE *buffer, DWORD_PTR id, DWORD direction, FLOAT x, FLOAT y, FLOAT z)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD_PTR(id);
	Stream->WriteDWORD(direction);
	Stream->WriteFloat(x);
	Stream->WriteFloat(y);
	Stream->WriteFloat(z);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_MOUSE_INPUT_CS(BYTE *buffer, FLOAT cxdelta, FLOAT cydelta, DWORD mouseButton)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteFloat(cxdelta);
	Stream->WriteFloat(cydelta);
	Stream->WriteDWORD(mouseButton);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_MOUSE_INPUT_ALL_SC(BYTE *buffer, DWORD_PTR id, FLOAT cxdelta, FLOAT cydelta, DWORD mouseButton)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD_PTR(id);
	Stream->WriteFloat(cxdelta);
	Stream->WriteFloat(cydelta);
	Stream->WriteDWORD(mouseButton);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_MOUSE_BUTTON_INPUT_CS(BYTE *buffer, DWORD mouseButton)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD(mouseButton);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_MOUSE_BUTTON_INPUT_ALL_SC(BYTE *buffer, DWORD_PTR id, DWORD mouseButton)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD_PTR(id);
	Stream->WriteDWORD(mouseButton);

	return Stream->GetLength();
}


inline DWORD WRITE_PT_FIRE_BULLET_ALL_SC(BYTE *buffer, DWORD_PTR id, DWORD_PTR BULLET_ID)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD_PTR(id);
	Stream->WriteDWORD_PTR(BULLET_ID);

	return Stream->GetLength();
}




inline DWORD WRITE_PT_PUT_OBJ_SC(BYTE *buffer, DWORD_PTR ID, INT TAG, FLOAT X, FLOAT Y, FLOAT Z
	, FLOAT MOVINGDIR_X, FLOAT MOVINGDIR_Y, FLOAT MOVINGDIR_Z,
	FLOAT SPD, FLOAT ACCSPD)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD_PTR(ID);
	Stream->WriteInt32(TAG);
	Stream->WriteFloat(X);
	Stream->WriteFloat(Y);
	Stream->WriteFloat(Z);

	Stream->WriteFloat(MOVINGDIR_X);
	Stream->WriteFloat(MOVINGDIR_Y);
	Stream->WriteFloat(MOVINGDIR_Z);

	Stream->WriteFloat(SPD);
	Stream->WriteFloat(ACCSPD);
	return Stream->GetLength();
}

inline DWORD WRITE_PT_REMOVE_OBJ_SC(BYTE *buffer, DWORD_PTR ID, INT TAG)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD_PTR(ID);
	Stream->WriteInt32(TAG);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_CHANGE_STATE_OBJ_SC(BYTE *buffer, DWORD_PTR ID, INT TAG, DWORD DIRECTION, FLOAT X, FLOAT Y, FLOAT Z
	, FLOAT MOVINGDIR_X, FLOAT MOVINGDIR_Y, FLOAT MOVINGDIR_Z,
	FLOAT SPD, FLOAT ACCSPD)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD_PTR(ID);
	Stream->WriteDWORD_PTR(TAG);
	Stream->WriteDWORD(DIRECTION);


	Stream->WriteFloat(X);
	Stream->WriteFloat(Y);
	Stream->WriteFloat(Z);

	Stream->WriteFloat(MOVINGDIR_X);
	Stream->WriteFloat(MOVINGDIR_Y);
	Stream->WriteFloat(MOVINGDIR_Z);

	Stream->WriteFloat(SPD);
	Stream->WriteFloat(ACCSPD);

	return Stream->GetLength();
}


inline DWORD WRITE_PT_PUT_OBJS_SC(BYTE *buffer, INT COUNT, DWORD_PTR* ID, INT* TAG, FLOAT* X, FLOAT* Y, FLOAT* Z
	, FLOAT* MOVINGDIR_X, FLOAT* MOVINGDIR_Y, FLOAT* MOVINGDIR_Z,
	FLOAT* SPD, FLOAT* ACCSPD){
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteInt32(COUNT);
	for (int i = 0; i < COUNT; ++i) {

		Stream->WriteInt32(ID[i]);
		Stream->WriteInt32(TAG[i]);
		Stream->WriteFloat(X[i]);
		Stream->WriteFloat(Y[i]);
		Stream->WriteFloat(Z[i]);

		Stream->WriteFloat(MOVINGDIR_X[i]);
		Stream->WriteFloat(MOVINGDIR_Y[i]);
		Stream->WriteFloat(MOVINGDIR_Z[i]);

		Stream->WriteFloat(SPD[i]);
		Stream->WriteFloat(ACCSPD[i]);
	}

	return Stream->GetLength();
}

inline DWORD WRITE_PT_REMOVE_OBJS_SC(BYTE *buffer, INT COUNT, DWORD_PTR* ID, INT* TAG) {
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteInt32(COUNT);
	for (int i = 0; i < COUNT; ++i) {

		Stream->WriteInt32(ID[i]);
		Stream->WriteInt32(TAG[i]);
		
	}

	return Stream->GetLength();
}

inline DWORD WRITE_PT_PUT_PLAYER_SC(BYTE *buffer, DWORD_PTR ID, DWORD DIRECTION, FLOAT RIGHTX, FLOAT RIGHTY, FLOAT RIGHTZ
	, FLOAT UPX, FLOAT UPY, FLOAT UPZ
	, FLOAT LOOKX, FLOAT LOOKY, FLOAT LOOKZ
	, FLOAT POSX, FLOAT POSY, FLOAT POSZ)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteDWORD_PTR(ID);
	Stream->WriteDWORD(DIRECTION);
	Stream->WriteFloat(RIGHTX);
	Stream->WriteFloat(RIGHTY);
	Stream->WriteFloat(RIGHTZ);
	Stream->WriteFloat(UPX);
	Stream->WriteFloat(UPY);
	Stream->WriteFloat(UPZ);
	Stream->WriteFloat(LOOKX);
	Stream->WriteFloat(LOOKY);
	Stream->WriteFloat(LOOKZ);
	Stream->WriteFloat(POSX);
	Stream->WriteFloat(POSY);
	Stream->WriteFloat(POSZ);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_REMOVE_PLAYER_SC(BYTE *buffer, INT ID)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteInt32(ID);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_CHANGE_STATE_PLAYER_SC(BYTE *buffer, INT ID, DWORD DIRECTION, FLOAT X, FLOAT Y, FLOAT Z)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteInt32(ID);
	Stream->WriteDWORD(DIRECTION);


	Stream->WriteFloat(X);
	Stream->WriteFloat(Y);
	Stream->WriteFloat(Z);

	return Stream->GetLength();
}
inline DWORD WRITE_PT_ENTER_SERVER_SUC(BYTE *buffer, INT ID)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteInt32(ID);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_JOIN_CS(BYTE *buffer, INT ID, INT ROOM)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	std::cout << "ROOM_JOIN_CS - ID : " << ID<< "/ ROOM : " << ROOM << std::endl;
	Stream->WriteInt32(ID);
	Stream->WriteInt32(ROOM);
	
	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_JOIN_SCC_SC(BYTE *buffer, INT SLOT_ID, INT SLOT_COUNT)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	std::cout << "ROOM_JOIN_SCC_SC - SLOT_ID : " << SLOT_ID << "/ SLOT_COUNT : " << SLOT_COUNT << std::endl;
	Stream->WriteInt32(SLOT_ID);
	Stream->WriteInt32(SLOT_COUNT);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_JOIN_SC(BYTE *buffer, INT SLOT_ID,BOOL READY, INT CHARACTER)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	std::cout << "ROOM_JOIN_SC - SLOT_ID : " << SLOT_ID << "/ READY : " << READY << "/ CHARACTER : " << CHARACTER << std::endl;

	Stream->WriteInt32(SLOT_ID);
	Stream->WriteBOOL(READY);
	Stream->WriteInt32(CHARACTER);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_CREATE_SCC_SC(BYTE *buffer, INT ROOM_ID)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	std::cout << "ROOM_CREATE_SCC_SC - ROOM_ID : " << ROOM_ID << std::endl;

	Stream->WriteInt32(ROOM_ID);

	return Stream->GetLength();
}
inline DWORD WRITE_PT_ROOM_CREATE_CS(BYTE *buffer, INT ID)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	std::cout << "ROOM_CREATE_CS - ID : " << ID << std::endl;

	Stream->WriteInt32(ID);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_CREATE_SC(BYTE *buffer, INT ROOM_ID)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	std::cout << "ROOM_CREATE_SC - ROOM_ID : " << ROOM_ID << std::endl;

	Stream->WriteInt32(ROOM_ID);

	return Stream->GetLength();
}


inline DWORD WRITE_PT_ROOM_DATA_CHANGE_CS(BYTE *buffer,INT ROOM_ID, INT SLOT_ID, BOOL READY, INT CHARACTER)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	std::cout << "ROOM_DATA_CHANGE_CS - ROOM_ID : " << ROOM_ID << "/ SLOT_ID : " << SLOT_ID << "/ READY : " << READY << "/ CHARACTER : " << CHARACTER << std::endl;

	Stream->WriteInt32(ROOM_ID);
	Stream->WriteInt32(SLOT_ID);
	Stream->WriteBOOL(READY);
	Stream->WriteInt32(CHARACTER);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_DATA_CHANGE_SC(BYTE *buffer, INT SLOT_ID, BOOL READY, INT CHARACTER)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	std::cout << "ROOM_DATA_CHANGE_SC - SLOT_ID : " << SLOT_ID << "/ READY : " << READY << "/ CHARACTER : " << CHARACTER << std::endl;

	Stream->WriteInt32(SLOT_ID);
	Stream->WriteBOOL(READY);
	Stream->WriteInt32(CHARACTER);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_ADDPLAYER_SC(BYTE *buffer, INT SLOT_COUNT)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	std::cout << "ROOM_ADDPLAYER_SC - SLOT_COUNT : " << SLOT_COUNT << std::endl;

	Stream->WriteInt32(SLOT_COUNT);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_ROOM_OUT_SC(BYTE *buffer, INT SLOT_COUNT)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	std::cout << "ROOM_OUT_SC - SLOT_COUNT : " << SLOT_COUNT << std::endl;

	Stream->WriteInt32(SLOT_COUNT);

	return Stream->GetLength();
}

inline DWORD WRITE_PT_CHANGE_SLOTID_SC(BYTE *buffer, INT SLOT_ID)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	std::cout << "ROOM_CHANGE_SLOTID_SC - SLOT_ID : " << SLOT_ID << std::endl;

	Stream->WriteInt32(SLOT_ID);

	return Stream->GetLength();
}


inline DWORD WRITE_PT_FTOWN_START_SC(BYTE *buffer)
{
	CStreamSP Stream;

	std::cout << "FTOWN_START_SC -  : " << std::endl;

	Stream->SetBuffer(buffer);

	return Stream->GetLength();
}


inline DWORD WRITE_PT_FTOWN_READY_CS(BYTE *buffer)
{
	CStreamSP Stream;
	std::cout << "FTOWN_READY_CS -  : " << std::endl;


	Stream->SetBuffer(buffer);

	return Stream->GetLength();
}


inline DWORD WRITE_PT_FTOWN_READY_SC(BYTE *buffer)
{
	CStreamSP Stream;
	std::cout << "_FTOWN_READY_SC -  : " << std::endl;

	Stream->SetBuffer(buffer);

	return Stream->GetLength();
}


inline DWORD WRITE_PT_FREQUENCY_MOVE_CS(BYTE *buffer, float POSX, float POSY, float POSZ, float ANGLEY, DWORD DIRECTION, bool JUMP)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteFloat(POSX);
	Stream->WriteFloat(POSY);
	Stream->WriteFloat(POSZ);
	Stream->WriteFloat(ANGLEY);
	Stream->WriteDWORD(DIRECTION);
	Stream->WriteBOOL(JUMP);
	
	return Stream->GetLength();
}
inline DWORD WRITE_PT_FREQUENCY_MOVE_SC(BYTE *buffer,INT SLOT_ID, float POSX, float POSY, float POSZ, float ANGLEY, DWORD DIRECTION, bool JUMP)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteInt32(SLOT_ID);
	Stream->WriteFloat(POSX);
	Stream->WriteFloat(POSY);
	Stream->WriteFloat(POSZ);
	Stream->WriteFloat(ANGLEY);
	Stream->WriteDWORD(DIRECTION);
	Stream->WriteBOOL(JUMP);
	return Stream->GetLength();
}
inline DWORD WRITE_PT_MOUSE_LEFT_ATTACK_CS(BYTE *buffer, bool ATTACK)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteBOOL(ATTACK);

	return Stream->GetLength();
}
inline DWORD WRITE_PT_MOUSE_LEFT_ATTACK_SC(BYTE *buffer, INT SLOT_ID, bool ATTACK)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteInt32(SLOT_ID);
	Stream->WriteBOOL(ATTACK);
	return Stream->GetLength();
}
inline DWORD WRITE_PT_ROOM_LIST_COUNT_SC(BYTE *buffer, INT ROOM_COUNT)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteInt32(ROOM_COUNT);
	return Stream->GetLength();
}
inline DWORD WRITE_PT_ROOM_LIST_SC(BYTE *buffer, INT ROOM_ID, INT PLAYER_NUM)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteInt32(ROOM_ID);
	Stream->WriteInt32(PLAYER_NUM);
	return Stream->GetLength();
}
inline DWORD WRITE_PT_FTOWN_READY_CS(BYTE *buffer, INT ROOM_ID)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteInt32(ROOM_ID);
	return Stream->GetLength();
}
inline DWORD WRITE_PT_ALDENARD_READY_CS(BYTE *buffer, INT ROOM_ID)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteInt32(ROOM_ID);
	return Stream->GetLength();
}
inline DWORD WRITE_PT_SARASEN_READY_CS(BYTE *buffer, INT ROOM_ID)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->WriteInt32(ROOM_ID);
	return Stream->GetLength();
}