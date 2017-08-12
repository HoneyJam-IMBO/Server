#pragma once

inline VOID READ_PT_LOGIN_SERVER_SUC(BYTE *buffer, S_PT_LOGIN_SERVER_SUC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}
inline VOID READ_PT_LOGIN_SERVER_ALREADY(BYTE *buffer, S_PT_LOGIN_SERVER_FAIL &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}

inline VOID READ_PT_LOGIN_SERVER_FAIL(BYTE *buffer, S_PT_LOGIN_SERVER_FAIL &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}
inline VOID READ_PT_SIGN_UP_SUC_SC(BYTE *buffer, S_PT_SIGN_UP_SUC_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}


inline VOID READ_PT_SIGN_UP_FAIL_SC(BYTE *buffer, S_PT_SIGN_UP_FAIL_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}
///////////////////////////////////////青己柳涝
inline VOID READ_PT_ENTER_EARTH_CS(BYTE *buffer, S_PT_ENTER_EARTH_CS &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}


inline VOID READ_PT_ENTER_EARTH_FAIL(BYTE *buffer, S_PT_ENTER_EARTH_FAIL &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}
inline VOID READ_PT_ENTER_EARTH_SUC(BYTE *buffer, S_PT_ENTER_EARTH_SUC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD_PTR(&parameter.MYID);
	Stream->ReadInt32(&parameter.TEAM);
	Stream->ReadFloat(&parameter.X);
	Stream->ReadFloat(&parameter.Y);
	Stream->ReadFloat(&parameter.Z);
}

///////////////////////////////////////青己柳涝

inline VOID READ_PT_ENTER_SERVER_FAIL(BYTE *buffer, S_PT_ENTER_SERVER_FAIL &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}

inline VOID READ_PT_LOGIN_CS(BYTE *buffer, S_PT_LOGIN_CS &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadWCHARs(parameter.ID, 10);
	Stream->ReadWCHARs(parameter.PW, 10);
	
}
inline VOID READ_PT_SIGN_UP_CS(BYTE *buffer, S_PT_SIGN_UP_CS &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadWCHARs(parameter.ID, 10);
	Stream->ReadWCHARs(parameter.PW, 10);

}


inline VOID READ_PT_ENTER_SERVER_ALL(BYTE *buffer, S_PT_ENTER_SERVER_ALL &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD_PTR(&parameter.ID);
	Stream->ReadFloat(&parameter.X);
	Stream->ReadFloat(&parameter.Y);
	Stream->ReadFloat(&parameter.Z);
}

inline VOID READ_PT_LEAVE_SERVER_ALL(BYTE *buffer, S_PT_LEAVE_SERVER_ALL &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD_PTR(&parameter.ID);
}

inline VOID READ_PT_ENTER_SERVER_S(BYTE *buffer, S_PT_ENTER_SERVER_S &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD_PTR(&parameter.MYID);
	Stream->ReadFloat(&parameter.X);
	Stream->ReadFloat(&parameter.Y);
	Stream->ReadFloat(&parameter.Z);
}

inline VOID READ_PT_KEY_INPUT_CS(BYTE *buffer, S_PT_KEY_INPUT_CS &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD(&parameter.DIRECTION);
	Stream->ReadFloat(&parameter.X);
	Stream->ReadFloat(&parameter.Y);
	Stream->ReadFloat(&parameter.Z);
}

inline VOID READ_PT_KEY_INPUT_ALL_SC(BYTE *buffer, S_PT_KEY_INPUT_ALL_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD_PTR(&parameter.ID);
	Stream->ReadDWORD(&parameter.DIRECTION);
	Stream->ReadFloat(&parameter.X);
	Stream->ReadFloat(&parameter.Y);
	Stream->ReadFloat(&parameter.Z);
}

inline VOID READ_PT_MOUSE_INPUT_CS(BYTE *buffer, S_PT_MOUSE_INPUT_CS &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadFloat(&parameter.CXDELTA);
	Stream->ReadFloat(&parameter.CYDELTA);
	Stream->ReadDWORD(&parameter.MOUSEBUTTON);
}

inline VOID READ_PT_MOUSE_INPUT_ALL_SC(BYTE *buffer, S_PT_MOUSE_INPUT_ALL_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD_PTR(&parameter.ID);
	Stream->ReadFloat(&parameter.CXDELTA);
	Stream->ReadFloat(&parameter.CYDELTA);
	Stream->ReadDWORD(&parameter.MOUSEBUTTON);
}

inline VOID READ_PT_MOUSE_BUTTON_INPUT_CS(BYTE *buffer, S_PT_MOUSE_BUTTON_INPUT_CS &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD(&parameter.MOUSEBUTTON);
}

inline VOID READ_PT_MOUSE_BUTTON_INPUT_ALL_SC(BYTE *buffer, S_PT_MOUSE_BUTTON_INPUT_ALL_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD_PTR(&parameter.ID);
	Stream->ReadDWORD(&parameter.MOUSEBUTTON);
}

inline VOID READ_PT_FIRE_BULLET_ALL_SC(BYTE *buffer, S_PT_FIRE_BULLET_ALL_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


	Stream->ReadDWORD_PTR(&parameter.ID);
	Stream->ReadDWORD_PTR(&parameter.BULLETID);
}


inline VOID READ_PT_PUT_OBJ_SC(BYTE *buffer, S_PT_PUT_OBJ_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD_PTR(&parameter.ID);

	Stream->ReadInt32(&parameter.TAG);
	Stream->ReadFloat(&parameter.X);
	Stream->ReadFloat(&parameter.Y);
	Stream->ReadFloat(&parameter.Z);


	Stream->ReadFloat(&parameter.MOVINGDIR_X);
	Stream->ReadFloat(&parameter.MOVINGDIR_Y);
	Stream->ReadFloat(&parameter.MOVINGDIR_Z);

	Stream->ReadFloat(&parameter.SPD);
	Stream->ReadFloat(&parameter.ACCSPD);
}

inline VOID READ_PT_REMOVE_OBJ_SC(BYTE *buffer, S_PT_REMOVE_OBJ_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD_PTR(&parameter.ID);
	Stream->ReadInt32(&parameter.TAG);
}

inline VOID READ_PT_CHANGE_STATE_OBJ_SC(BYTE *buffer, S_PT_CHANGE_STATE_OBJ_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD_PTR(&parameter.ID);
	Stream->ReadInt32(&parameter.TAG);
	Stream->ReadDWORD(&parameter.DIRECTION);

	Stream->ReadFloat(&parameter.X);
	Stream->ReadFloat(&parameter.Y);
	Stream->ReadFloat(&parameter.Z);

	Stream->ReadFloat(&parameter.MOVINGDIR_X);
	Stream->ReadFloat(&parameter.MOVINGDIR_Y);
	Stream->ReadFloat(&parameter.MOVINGDIR_Z);

	Stream->ReadFloat(&parameter.SPD);
	Stream->ReadFloat(&parameter.ACCSPD);
}


inline VOID READ_PT_PUT_OBJS_SC(BYTE *buffer, S_PT_PUT_OBJS_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadInt32(&parameter.COUNT);
	
	for (int i = 0; i < parameter.COUNT; ++i) {
		Stream->ReadDWORD_PTR(&parameter.ID[i]);
		Stream->ReadInt32(&parameter.TAG[i]);
		//Stream->ReadDWORD(&parameter.DIRECTION[i]);

		Stream->ReadFloat(&parameter.X[i]);
		Stream->ReadFloat(&parameter.Y[i]);
		Stream->ReadFloat(&parameter.Z[i]);

		Stream->ReadFloat(&parameter.MOVINGDIR_X[i]);
		Stream->ReadFloat(&parameter.MOVINGDIR_Y[i]);
		Stream->ReadFloat(&parameter.MOVINGDIR_Z[i]);

		Stream->ReadFloat(&parameter.SPD[i]);
		Stream->ReadFloat(&parameter.ACCSPD[i]);
	}
}


inline VOID READ_PT_REMOVE_OBJS_SC(BYTE *buffer, S_PT_REMOVE_OBJS_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadInt32(&parameter.COUNT);

	for (int i = 0; i < parameter.COUNT; ++i) {
		Stream->ReadDWORD_PTR(&parameter.ID[i]);
		Stream->ReadInt32(&parameter.TAG[i]);
	}
}




inline VOID READ_PT_PUT_PLAYER_SC(BYTE *buffer, S_PT_PUT_PLAYER_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD_PTR(&parameter.ID);
	Stream->ReadDWORD(&parameter.DIRECTION);
	Stream->ReadFloat(&parameter.RIGHTX);
	Stream->ReadFloat(&parameter.RIGHTY);
	Stream->ReadFloat(&parameter.RIGHTZ);
	Stream->ReadFloat(&parameter.UPX);
	Stream->ReadFloat(&parameter.UPY);
	Stream->ReadFloat(&parameter.UPZ);
	Stream->ReadFloat(&parameter.LOOKX);
	Stream->ReadFloat(&parameter.LOOKY);
	Stream->ReadFloat(&parameter.LOOKZ);
	Stream->ReadFloat(&parameter.POSX);
	Stream->ReadFloat(&parameter.POSY);
	Stream->ReadFloat(&parameter.POSZ);
	
}

inline VOID READ_PT_REMOVE_PLAYER_SC(BYTE *buffer, S_PT_REMOVE_PLAYER_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD_PTR(&parameter.ID);
}

inline VOID READ_PT_CHANGE_STATE_PLAYER_SC(BYTE *buffer, S_PT_CHANGE_STATE_PLAYER_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadDWORD_PTR(&parameter.ID);
	Stream->ReadDWORD(&parameter.DIRECTION);

	Stream->ReadFloat(&parameter.X);
	Stream->ReadFloat(&parameter.Y);
	Stream->ReadFloat(&parameter.Z);
}

inline VOID READ_PT_ENTER_SERVER_SUC(BYTE *buffer, S_PT_ENTER_SERVER_SUC& parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadInt32(&parameter.ID);
}

inline VOID READ_PT_ROOM_JOIN_CS(BYTE *buffer, S_PT_ROOM_JOIN_CS &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadInt32(&parameter.ID);
	Stream->ReadInt32(&parameter.ROOM_NUM);
}

inline VOID READ_PT_ROOM_JOIN_SCC_SC(BYTE *buffer, S_PT_ROOM_JOIN_SCC_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadInt32(&parameter.SLOT_ID);
	Stream->ReadInt32(&parameter.SLOT_COUNT);
}


inline VOID READ_PT_ROOM_JOIN_SC(BYTE *buffer, S_PT_ROOM_JOIN_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadInt32(&parameter.SLOT_ID);
	Stream->ReadBOOL(&parameter.READY);
	Stream->ReadInt32(&parameter.CHARACTER);
}

inline VOID READ_PT_ROOM_CREATE_SCC_SC(BYTE *buffer, S_PT_ROOM_CREATE_SCC_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadInt32(&parameter.ROOM_ID);
}
inline VOID READ_PT_ROOM_CREATE_CS(BYTE *buffer, S_PT_ROOM_CREATE_CS &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadInt32(&parameter.ID);
}
inline VOID READ_PT_ROOM_CREATE_SC(BYTE *buffer, S_PT_ROOM_CREATE_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadInt32(&parameter.ROOM_ID);
}

inline VOID READ_PT_ROOM_DATA_CHANGE_CS(BYTE *buffer, S_PT_ROOM_DATA_CHANGE_CS &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadInt32(&parameter.ROOM_ID);
	Stream->ReadInt32(&parameter.SLOT_ID);
	Stream->ReadBOOL(&parameter.READY);
	Stream->ReadInt32(&parameter.CHARACTER);
}
inline VOID READ_PT_ROOM_DATA_CHANGE_SC(BYTE *buffer, S_PT_ROOM_DATA_CHANGE_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadInt32(&parameter.SLOT_ID);
	Stream->ReadBOOL(&parameter.READY);
	Stream->ReadInt32(&parameter.CHARACTER);
}

inline VOID READ_PT_ROOM_ADDPLAYER_SC(BYTE *buffer, S_PT_ROOM_ADDPLAYER_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadInt32(&parameter.SLOT_COUNT);
}

inline VOID READ_PT_ROOM_OUT_SC(BYTE *buffer, S_PT_ROOM_OUT_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadInt32(&parameter.SLOT_COUNT);
}

inline VOID READ_PT_CHANGE_SLOTID_SC(BYTE *buffer, S_PT_CHANGE_SLOTID_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadInt32(&parameter.SLOT_ID);
}

inline VOID READ_PT_FREQUENCY_MOVE_CS(BYTE *buffer, S_PT_FREQUENCY_MOVE_CS &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadFloat(&parameter.POSX);
	Stream->ReadFloat(&parameter.POSY);
	Stream->ReadFloat(&parameter.POSZ);
	Stream->ReadFloat(&parameter.ANGLEY);
	Stream->ReadDWORD(&parameter.DIRECTION);
	Stream->ReadBOOL(&parameter.JUMP);

}
inline VOID READ_PT_FREQUENCY_MOVE_SC(BYTE *buffer, S_PT_FREQUENCY_MOVE_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadInt32(&parameter.SLOT_ID);
	Stream->ReadFloat(&parameter.POSX);
	Stream->ReadFloat(&parameter.POSY);
	Stream->ReadFloat(&parameter.POSZ);
	Stream->ReadFloat(&parameter.ANGLEY);
	Stream->ReadDWORD(&parameter.DIRECTION);
	Stream->ReadBOOL(&parameter.JUMP);

}
inline VOID READ_PT_MOUSE_LEFT_ATTACK_CS(BYTE *buffer, _S_PT_MOUSE_LEFT_ATTACK_CS &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadBOOL(&parameter.ATTACK);
}
inline VOID READ_PT_MOUSE_LEFT_ATTACK_SC(BYTE *buffer, _S_PT_MOUSE_LEFT_ATTACK_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadInt32(&parameter.SLOT_ID);
	Stream->ReadBOOL(&parameter.ATTACK);

}
inline VOID READ_PT_ROOM_LIST_COUNT_SC(BYTE *buffer, _S_PT_ROOM_LIST_COUNT_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadInt32(&parameter.ROOM_COUNT);

}
inline VOID READ_PT_ROOM_LIST_SC(BYTE *buffer, _S_PT_ROOM_LIST_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadInt32(&parameter.ROOM_ID);
	Stream->ReadBOOL(&parameter.PLAYER_NUM);

}
inline VOID READ_PT_FTOWN_READY_CS(BYTE *buffer, S_PT_FTOWN_READY_CS &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);
	std::cout << "FTOWN_READY" << std::endl;
	Stream->ReadInt32(&parameter.ROOM_ID);

	std::cout << "FTOWN_ READY!" << std::endl;
	//Stream->ReadBOOL(&parameter.PLAYER_NUM);
}

inline VOID READ_PT_FTOWN_NPC_READY_CS(BYTE *buffer, S_PT_FTOWN_NPC_READY_CS &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadInt32(&parameter.ROOM_ID);
	Stream->ReadInt32(&parameter.SLOT_ID);

}

inline VOID READ_PT_FTOWN_NPC_READY_SC(BYTE *buffer, S_PT_FTOWN_NPC_READY_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);
	Stream->ReadInt32(&parameter.SLOT_ID);
	Stream->ReadBOOL(&parameter.READY);
}


inline VOID READ_PT_FTOWN_NPC_READY_COMP_SC(BYTE *buffer, S_PT_FTOWN_NPC_READY_COMP_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}


inline VOID READ_PT_FTOWN_BOSS_ACTION_CAMERA_READY_SC(BYTE *buffer, S_PT_FTOWN_BOSS_ACTION_CAMERA_READY_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);
	Stream->ReadInt32(&parameter.SLOT_ID);
	Stream->ReadBOOL(&parameter.READY);
}

inline VOID READ_PT_FTOWN_BOSS_ACTION_CAMERA_READY_CS(BYTE *buffer, S_PT_FTOWN_BOSS_ACTION_CAMERA_READY_CS &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);
	Stream->ReadInt32(&parameter.ROOM_ID);
	Stream->ReadInt32(&parameter.SLOT_ID);
}

inline VOID READ_PT_FTOWN_BOSS_ACTION_CAMERA_READY_COMP_SC(BYTE *buffer, S_PT_FTOWN_BOSS_ACTION_CAMERA_READY_COMP_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);
}


inline VOID READ_PT_FTOWN_NPC2_READY_CS(BYTE *buffer, S_PT_FTOWN_NPC2_READY_CS &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadInt32(&parameter.ROOM_ID);
	Stream->ReadInt32(&parameter.SLOT_ID);

}

inline VOID READ_PT_FTOWN_NPC2_READY_SC(BYTE *buffer, S_PT_FTOWN_NPC2_READY_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);
	Stream->ReadInt32(&parameter.SLOT_ID);
	Stream->ReadBOOL(&parameter.READY);

}
inline VOID READ_PT_FTOWN_NPC2_READY_COMP_SC(BYTE *buffer, S_PT_FTOWN_NPC2_READY_COMP_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}

inline VOID READ_PT_ALDENARD_READY_CS(BYTE *buffer, S_PT_ALDENARD_READY_CS &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadInt32(&parameter.ROOM_ID);
	//Stream->ReadBOOL(&parameter.PLAYER_NUM);

}
inline VOID READ_PT_ALDENARD_READY_SC(BYTE *buffer, S_PT_ALDENARD_READY_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}


inline VOID READ_PT_SARASEN_START_CS(BYTE *buffer, S_PT_SARASEN_START_CS &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadInt32(&parameter.ROOM_ID);
	Stream->ReadInt32(&parameter.SLOT_ID);

} 
inline VOID READ_PT_SARASEN_START_SC(BYTE *buffer, S_PT_SARASEN_START_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);
	
	Stream->ReadInt32(&parameter.SLOT_ID);
	Stream->ReadBOOL(&parameter.READY);

}
inline VOID READ_PT_SARASEN_START_COMP_SC(BYTE *buffer, S_PT_SARASEN_START_COMP_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}
inline VOID READ_PT_SARASEN_READY_CS(BYTE *buffer, S_PT_SARASEN_READY_CS &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadInt32(&parameter.ROOM_ID);
	//Stream->ReadBOOL(&parameter.PLAYER_NUM);

}
inline VOID READ_PT_SARASEN_READY_SC(BYTE *buffer, S_PT_SARASEN_READY_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);


}

inline VOID READ_PT_SARASEN_BOSS_START_CS(BYTE *buffer, S_PT_SARASEN_BOSS_START_CS &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadInt32(&parameter.ROOM_ID);
	Stream->ReadInt32(&parameter.SLOT_ID);

}
inline VOID READ_PT_SARASEN_BOSS_START_SC(BYTE *buffer, S_PT_SARASEN_BOSS_START_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

	Stream->ReadInt32(&parameter.SLOT_ID);
	Stream->ReadBOOL(&parameter.READY);

}
inline VOID READ_PT_SARASEN_BOSS_START_COMP_SC(BYTE *buffer, S_PT_SARASEN_BOSS_START_COMP_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);

}

inline VOID READ_PT_SARASEN_BOSS_ACTION_CAMERA_READY_SC(BYTE *buffer, S_PT_SARASEN_BOSS_ACTION_CAMERA_READY_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);
	Stream->ReadInt32(&parameter.SLOT_ID);
	Stream->ReadBOOL(&parameter.READY);
}

inline VOID READ_PT_SARASEN_BOSS_ACTION_CAMERA_READY_CS(BYTE *buffer, S_PT_SARASEN_BOSS_ACTION_CAMERA_READY_CS &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);
	Stream->ReadInt32(&parameter.ROOM_ID);
	Stream->ReadInt32(&parameter.SLOT_ID);
}

inline VOID READ_PT_SARASEN_BOSS_ACTION_CAMERA_READY_COMP_SC(BYTE *buffer, S_PT_SARASEN_BOSS_ACTION_CAMERA_READY_COMP_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);
}


inline VOID READ_PT_SKILL_COLLISION_TO_TARGET_CS(BYTE *buffer, S_PT_SKILL_COLLISION_TO_TARGET_CS &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);
	Stream->ReadInt32(&parameter.ROOM_ID);
	Stream->ReadInt32(&parameter.MY_SLOT_ID);
	Stream->ReadInt32(&parameter.TARGET_SLOT_ID);
	Stream->ReadInt32(&parameter.CHARACTER);
	Stream->ReadInt32(&parameter.SKILL_NUM);

}


inline VOID READ_PT_BOSS_HP_SC(BYTE *buffer, S_PT_BOSS_HP_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);
	Stream->ReadInt32(&parameter.BOSS_HP);
}



inline VOID READ_PT_BOSS_CLEAR_SC(BYTE *buffer, S_PT_BOSS_CLEAR_SC &parameter)
{
	CStreamSP Stream;
	Stream->SetBuffer(buffer);
}
