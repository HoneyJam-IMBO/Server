#pragma once

////인공지능 관련
//#define COMMAND_KEY 1
//
//enum COMMAND{
//	TEST,
//	COLLISION,
//	COMMAND_END
//};
//
//struct stCOMMAND{
//	VOID* pObject;
//	//수행 시간
//	int active_time;
//	//명령어
//	COMMAND active_command;
//	VOID* pTarget;
//};
//
//typedef struct _OVERLAPPED_EXCOMMAND
//{
//	OVERLAPPED	Overlapped;
//	COMMAND		command;
//	int active_time;
//
//	VOID		*Object;
//	VOID		*pTarget;
//} OVERLAPPED_EXCOMMAND;
//
////인공지능 관련


//공간 관련 정의
#define MAP_SIZE 100000
#define MAP_LEVEL 3
#define VISUAL_FIELD_LEVEL 1
#define DEFAULT_COMAT_NUM 10
#define DEFAULT_MIDDLECOMAT_NUM 2
#define STATIC_OBJECT_LIMIT 300

#define UNIT	1250

//공간 관련 정의

//한바으이 최대 플레이어 
#define MAX_NUM_REGION_PLAYER 8
#define MAX_NUM_REGION 10

//서버
//마우스 버튼 인풋
#define M_LBUTTON		0x01
#define M_RBUTTON		0x02

#define MAX_USER 100
#define DEFAULT_PORT 9595

#define MAX_OBJECT_NUM 1000
//서버


//규칙 정의
#define GAME_FRAME 30

#define PLAYER_SPEED 300

#define BULLET_SPEED 5000
#define DYNAMICOBJ_SPEED 20

#define BULLET_RADIUS 5
#define COMAT_RADIUS 50
#define MIDDLECOMAT_RADIUS 500

#define PLAYER_RADIUS 20
#define PLANET_RADIUS 10000

enum OBJECT_TAG {
	PLAYER,
	BULLET,
	ASTEROID,
	COMAT,
	MIDDLECOMAT,
	BIGCOMAT,
	PLANET,
	OBJECT_END
};


typedef enum _PROTOCOL
{
	// 프로토콜의 시작을 알립니다.
	PT_VERSION	= 0x1000001,

	//클라이언트에서 매 프레임마다 서버로 자신의 위치를 전송하는 기본 프로토콜
	PT_FREQUENCY_MOVE_CS,
	/*
	INT		:	TYPE
	DWORD_PTR	: ID
	FLOAT	:	X
	FLOAT	:	Y
	FLOAT	:	Z
	*/

	PT_FREQUENCY_MOVE_SC,
	/*
	INT		:	TYPE
	DWORD_PTR	: ID
	FLOAT	:	X
	FLOAT	:	Y
	FLOAT	:	Z
	*/

	//입장 알림
	PT_ENTER_SERVER_ALL,
	/*
	DWORD_PTR	: ID
	FLOAT		: X
	FLOAT		: Y
	FLOAT		: Z
	*/

	//퇴장 알림
	PT_LEAVE_SERVER_ALL,
	/*
	DWORD_PTR : ID
	*/

	////////////////////////////서버 진입
	//처음 입장 승인 id, pw가 있어야 함
	PT_ENTER_SERVER_SUC,
	
	//입장 불가
	PT_ENTER_SERVER_FAIL,
	////////////////////////////서버 진입

	///////////////////////////////////로그인
	//로그인 요청
	PT_LOGIN_CS,
	/*
	WCHAR : ID[10]
	WCHAR : PW[10]
	*/

	//로그인 성공
	PT_LOGIN_SERVER_SUC,

	//이미 로그인 접속
	PT_LOGIN_SERVER_ALREADY,

	//로그인 실패
	PT_LOGIN_SERVER_FAIL,

	PT_SIGN_UP_CS,
	/*
	WCHAR : ID[10]
	WCHAR : PW[10]
	*/
	//회원가입 성공
	PT_SIGN_UP_SUC_SC,
	//아이디 중복
	PT_SIGN_UP_FAIL_SC,

	///////////////////////////////////로그인

	////////////////////////////////행성진입
	//행성진입 요청
	PT_ENTER_EARTH_CS,
	
	//행성진입 성공
	PT_ENTER_EARTH_SUC,
	/*
	INT : TEAM
	DWORD_PTR	: MYID
	FLOAT		: X
	FLOAT		: Y
	FLOAT		: Z
	*/

	//행성진입 실패
	PT_ENTER_EARTH_FAIL,
	////////////////////////////////행성진입

	//입장 성공
	PT_ENTER_SERVER_S,
	/*
	DWORD_PTR	:	MYID
	FLOAT	:	X
	FLOAT	:	Y
	FLOAT	:	Z
	*/
	
	

	//키 인풋
	PT_KEY_INPUT_CS,
	/*
	DWORD	:	DIRECTION
	FLOAT	:	X
	FLOAT	:	Y
	FLOAT	:	Z
	*/

	PT_KEY_INPUT_ALL_SC,
	/*
	DWORD_PTR	:	ID
	DWORD	:	DIRECTION
	FLOAT	:	X
	FLOAT	:	Y
	FLOAT	:	Z
	*/
	//키 인풋

	//마우스 인풋
	PT_MOUSE_INPUT_CS,
	/*
	FLOAT	: CXDELTA
	FLOAT	: CYDELTA
	DWORD	: MOUSEBUTTON
	*/

	PT_MOUSE_INPUT_ALL_SC,
	/*
	DWORD_PTR	:	ID
	FLOAT	: CXDELTA
	FLOAT	: CYDELTA
	DWORD	: MOUSEBUTTON
	*/

	//마우스 버튼입력 
	PT_MOUSE_BUTTON_INPUT_CS,
	/*
	DWORD	: MOUSEBUTTON
	*/

	PT_MOUSE_BUTTON_INPUT_ALL_SC,
	/*
	DWORD_PTR	: ID
	DWORD	: MOUSEBUTTON
	*/
	//마우스 인풋

	PT_FIRE_BULLET_ALL_SC,
	/*
	DWORD_PTR	:	ID
	DWORD_PTR	:	BULLET_ID
	*/
		

	PT_PUT_OBJ_SC,
	/*
	DWORD_PTR	:	ID
	INT		:	TAG
	FLOAT	:	X
	FLOAT	:	Y
	FLOAT	:	Z
	FLOAT	: MOVINGDIR_X
	FLOAT	: MOVINGDIR_Y
	FLOAT	: MOVINGDIR_Z

	FLOAT	: SPD
	FLOAT	: ACCSPD
	*/

	PT_REMOVE_OBJ_SC,
	/*
	DWORD_PTR	:	ID
	*/

	PT_CHANGE_STATE_OBJ_SC,
	/*
	DWORD_PTR	:	ID
	DWORD	:	DIRECTION
	FLOAT	:	X
	FLOAT	:	Y
	FLOAT	:	Z
	FLOAT	: MOVINGDIR_X
	FLOAT	: MOVINGDIR_Y
	FLOAT	: MOVINGDIR_Z

	FLOAT	: SPD
	FLOAT	: ACCSPD
	*/

	PT_PUT_OBJS_SC,
	/*
	INT		:	COUNT
	DWORD_PTR*	:	ID
	INT*	:	TAG
	FLOAT*	:	X
	FLOAT*	:	Y
	FLOAT*	:	Z
	FLOAT*	: MOVINGDIR_X
	FLOAT*	: MOVINGDIR_Y
	FLOAT*	: MOVINGDIR_Z

	FLOAT*	: SPD
	FLOAT*	: ACCSPD
	*/

	PT_REMOVE_OBJS_SC,
	/*
	INT			:	COUNT
	INT*		:	TAG
	DWORD_PTR*	:	ID
	*/

	PT_PUT_PLAYER_SC,
	/*
	DWORD_PTR	:	ID
	FLOAT	:	RIGHTX
	FLOAT	:	RIGHTY
	FLOAT	:	RIGHTZ
	FLOAT	:	UPX
	FLOAT	:	UPY
	FLOAT	:	UPZ
	FLOAT	:	LOOKX
	FLOAT	:	LOOKY
	FLOAT	:	LOOKZ
	FLOAT	:	POSX
	FLOAT	:	POSY
	FLOAT	:	POSZ
	*/

	PT_REMOVE_PLAYER_SC,
	/*
	DWORD_PTR	:	ID
	INT		:	TAG
	*/

	PT_CHANGE_STATE_PLAYER_SC,
	/*
	DWORD_PTR	:	ID
	INT		:	TAG
	DWORD	:	DIRECTION
	FLOAT	:	X
	FLOAT	:	Y
	FLOAT	:	Z
	*/
		PT_ROOM_JOIN_CS,
		/*
		INT : ID
		INT : ROOM_NUM
		*/
		PT_ROOM_JOIN_SCC_SC,
		/*
		INT : SLOT_ID
		INT : SLOT_COUNT
		*/
		PT_ROOM_JOIN_SC,
		/*
		INT : SLOT_ID
		BOOL : READY
		INT : CHARACTER
		*/
		PT_ROOM_CREATE_CS,
		/*
		INT : ID
		*/
		PT_ROOM_CREATE_SC,
		/*
		INT : ROOM_ID
		*/
		PT_ROOM_CREATE_SCC_SC,
		/*
		INT : ROOM_ID
		*/
		PT_ROOM_DATA_CHANGE_CS,
		/*
		INT : ROOM_ID
		INT : SLOT_ID
		BOOL : READY
		INT : CHARACTER
		*/
		PT_ROOM_DATA_CHANGE_SC,
		/*
		INT : SLOT_ID
		BOOL : READY
		INT : CHARACTER
		*/
		PT_ROOM_OUT_SC,
		/*
		INT : SLOT_COUNT
		*/
		PT_CHANGE_SLOTID_SC,
		/*
		INT : SLOT_ID
		*/
		PT_FTOWN_START_SC,
		/*
		*/
	
		PT_ALDENARD_START_CS, // 스타트가 로딩 시작알림
		/*
		*/
		PT_ALDENARD_START_SC,
		/*
		*/
		PT_SARASEN_START_CS,
		/*
		*/
		PT_SARASEN_START_SC,
		/*
		*/
		PT_FTOWN_READY_CS,
		/*
		*/
		
		PT_FTOWN_READY_SC,
		/*
		*/

		PT_FTOWN_NPC_READY_CS, 
		/*
		*/
		PT_FTOWN_NPC_READY_SC,
		/*
		*/

		PT_FTOWN_NPC2_READY_CS,
		/*
		*/
		PT_FTOWN_NPC2_READY_SC,
		/*
		*/




		PT_ALDENARD_READY_CS,
		/*
		*/
		PT_ALDENARD_READY_SC,
		/*
		*/
		PT_SARASEN_READY_CS,
		/*
		*/
		PT_SARASEN_READY_SC,
		/*
		*/
		PT_MOUSE_LEFT_ATTACK_SC,
		/*
		*/
		PT_MOUSE_LEFT_ATTACK_CS,
		/*
		*/
		PT_ROOM_LIST_SC,
		/*
		*/
		PT_ROOM_LIST_COUNT_SC,
		/*
		*/
	// 프로토콜 끝
	PT_END
};