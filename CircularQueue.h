#pragma once 
#include "stdafx.h"

//임계영역을 고려하지 않은 순환 큐
template <class T>
class MTCCircularQueue : public CMultiThreadSync<MTCCircularQueue<T>>{
public:
	MTCCircularQueue(){
		ZeroMemory(m_Queue, sizeof(m_Queue));
		m_QueueHead = m_QueueTail = 0;
	}
	~MTCCircularQueue(){}

private:
	T m_Queue[MAX_QUEUE_LENGTH];//실제 큐에 들어가는 데이터가 저장되는 메모리 영역
	DWORD m_QueuHead;//head 역할을 하는 변수
	DWORD m_QueueTail;//tail 역할을 하는 변수

public:
	BOOL Begin(){
		ZeroMemory(m_Queue, sizeof(m_Queue));
		m_QueueHead = m_QueueTail = 0;

		return TRUE;
	}

	BOOL End() { return TRUE; }

	BOOL Push(T data){
		DWORD TempTail = (m_QueueTail + 1) % MAX_QUEUE_LENGTH;
		// 먼저 새로운 데이터를 입력할 위치를 temptail에 저장
		if (TempTail == m_QueueHead)//혹시 현재의 head와 temptail가 같은 경우 큐가 가득 찬 상태이므로 넣지 못함
			return FALSE;

		CopyMemory(&m_Queue[TempTail], &data, sizeof(T));

		m_QueueTail = TempTail;
		//사용한 temptail의 값을  실제 tail 값이 들어있는 m_queuetail에 입력

		return TRUE;
	}

	BOOL Pop(T& data){//데이타를 출력할때 사용하는 함수
		if (m_QueueHead == m_QueueTail)//head와 tail이 같은지 확인하여 큐가 비어있는지 확인
			return FALSE;

		DWORD TempHead = (m_QueueHead + 1) % MAX_QUEUE_LENGTH;
		//값을 가져오기 위해 head의 값을 이용해서 temphead를 얻어낸다

		CopyMemory(&data, &m_Queue[TempHead], sizeof(T));//값을 얻어온다.

		m_QueueHead = TempHead;
		//사용한 temphead의 값을 실제 head 값이 들어있는 m_queuehead에 입력한다.

		return TRUE;
	}

	BOOL IsEmpty(){
		if (m_QueueHead == m_QueieTail) return TRUE;
		return FALSE;
	}
};
