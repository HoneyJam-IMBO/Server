#pragma once 
#include "stdafx.h"

//�Ӱ迵���� ������� ���� ��ȯ ť
template <class T>
class MTCCircularQueue : public CMultiThreadSync<MTCCircularQueue<T>>{
public:
	MTCCircularQueue(){
		ZeroMemory(m_Queue, sizeof(m_Queue));
		m_QueueHead = m_QueueTail = 0;
	}
	~MTCCircularQueue(){}

private:
	T m_Queue[MAX_QUEUE_LENGTH];//���� ť�� ���� �����Ͱ� ����Ǵ� �޸� ����
	DWORD m_QueuHead;//head ������ �ϴ� ����
	DWORD m_QueueTail;//tail ������ �ϴ� ����

public:
	BOOL Begin(){
		ZeroMemory(m_Queue, sizeof(m_Queue));
		m_QueueHead = m_QueueTail = 0;

		return TRUE;
	}

	BOOL End() { return TRUE; }

	BOOL Push(T data){
		DWORD TempTail = (m_QueueTail + 1) % MAX_QUEUE_LENGTH;
		// ���� ���ο� �����͸� �Է��� ��ġ�� temptail�� ����
		if (TempTail == m_QueueHead)//Ȥ�� ������ head�� temptail�� ���� ��� ť�� ���� �� �����̹Ƿ� ���� ����
			return FALSE;

		CopyMemory(&m_Queue[TempTail], &data, sizeof(T));

		m_QueueTail = TempTail;
		//����� temptail�� ����  ���� tail ���� ����ִ� m_queuetail�� �Է�

		return TRUE;
	}

	BOOL Pop(T& data){//����Ÿ�� ����Ҷ� ����ϴ� �Լ�
		if (m_QueueHead == m_QueueTail)//head�� tail�� ������ Ȯ���Ͽ� ť�� ����ִ��� Ȯ��
			return FALSE;

		DWORD TempHead = (m_QueueHead + 1) % MAX_QUEUE_LENGTH;
		//���� �������� ���� head�� ���� �̿��ؼ� temphead�� ����

		CopyMemory(&data, &m_Queue[TempHead], sizeof(T));//���� ���´�.

		m_QueueHead = TempHead;
		//����� temphead�� ���� ���� head ���� ����ִ� m_queuehead�� �Է��Ѵ�.

		return TRUE;
	}

	BOOL IsEmpty(){
		if (m_QueueHead == m_QueieTail) return TRUE;
		return FALSE;
	}
};
