#pragma once

////�ΰ����� ����
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
//	//���� �ð�
//	int active_time;
//	//��ɾ�
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
////�ΰ����� ����


//���� ���� ����
#define MAP_SIZE 100000
#define MAP_LEVEL 3
#define VISUAL_FIELD_LEVEL 1
#define DEFAULT_COMAT_NUM 10
#define DEFAULT_MIDDLECOMAT_NUM 2
#define STATIC_OBJECT_LIMIT 300

#define UNIT	1250

//���� ���� ����

//�ѹ����� �ִ� �÷��̾� 
#define MAX_NUM_REGION_PLAYER 8
#define MAX_NUM_REGION 10

//����
//���콺 ��ư ��ǲ
#define M_LBUTTON		0x01
#define M_RBUTTON		0x02

#define MAX_USER 100
#define DEFAULT_PORT 9595

#define MAX_OBJECT_NUM 1000
//����


//��Ģ ����
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
	// ���������� ������ �˸��ϴ�.
	PT_VERSION	= 0x1000001,

	//Ŭ���̾�Ʈ���� �� �����Ӹ��� ������ �ڽ��� ��ġ�� �����ϴ� �⺻ ��������
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

	//���� �˸�
	PT_ENTER_SERVER_ALL,
	/*
	DWORD_PTR	: ID
	FLOAT		: X
	FLOAT		: Y
	FLOAT		: Z
	*/

	//���� �˸�
	PT_LEAVE_SERVER_ALL,
	/*
	DWORD_PTR : ID
	*/

	////////////////////////////���� ����
	//ó�� ���� ���� id, pw�� �־�� ��
	PT_ENTER_SERVER_SUC,
	
	//���� �Ұ�
	PT_ENTER_SERVER_FAIL,
	////////////////////////////���� ����

	///////////////////////////////////�α���
	//�α��� ��û
	PT_LOGIN_CS,
	/*
	WCHAR : ID[10]
	WCHAR : PW[10]
	*/

	//�α��� ����
	PT_LOGIN_SERVER_SUC,

	//�̹� �α��� ����
	PT_LOGIN_SERVER_ALREADY,

	//�α��� ����
	PT_LOGIN_SERVER_FAIL,

	PT_SIGN_UP_CS,
	/*
	WCHAR : ID[10]
	WCHAR : PW[10]
	*/
	//ȸ������ ����
	PT_SIGN_UP_SUC_SC,
	//���̵� �ߺ�
	PT_SIGN_UP_FAIL_SC,

	///////////////////////////////////�α���

	////////////////////////////////�༺����
	//�༺���� ��û
	PT_ENTER_EARTH_CS,
	
	//�༺���� ����
	PT_ENTER_EARTH_SUC,
	/*
	INT : TEAM
	DWORD_PTR	: MYID
	FLOAT		: X
	FLOAT		: Y
	FLOAT		: Z
	*/

	//�༺���� ����
	PT_ENTER_EARTH_FAIL,
	////////////////////////////////�༺����

	//���� ����
	PT_ENTER_SERVER_S,
	/*
	DWORD_PTR	:	MYID
	FLOAT	:	X
	FLOAT	:	Y
	FLOAT	:	Z
	*/
	
	

	//Ű ��ǲ
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
	//Ű ��ǲ

	//���콺 ��ǲ
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

	//���콺 ��ư�Է� 
	PT_MOUSE_BUTTON_INPUT_CS,
	/*
	DWORD	: MOUSEBUTTON
	*/

	PT_MOUSE_BUTTON_INPUT_ALL_SC,
	/*
	DWORD_PTR	: ID
	DWORD	: MOUSEBUTTON
	*/
	//���콺 ��ǲ

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
	
		PT_ALDENARD_START_CS, // ��ŸƮ�� �ε� ���۾˸�
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
	// �������� ��
	PT_END
};