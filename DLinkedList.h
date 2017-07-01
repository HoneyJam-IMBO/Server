#pragma once
#include "stdafx.h"
#include <iostream>

template <typename T>
class Node{
private:
public:
	T* data;
	Node* next;
	Node* prev;
	Node(){ data = NULL; next = NULL; prev = NULL; }
};

template <typename T>
class DLinkedList{
private:
	Node<T>* head;
	Node<T>* tail;
public:
	DLinkedList(){
		head = new Node < T >;
		tail = new Node < T >;
		head->next = tail;
		tail->prev = head;
	}
	void deleteAll(){
		while (head)
		{
			Node<T>* temp = head;
			head = head->next;
			if (temp) {
				delete temp;
				temp = NULL;
			}
		}
	}

	//��� �߰�
	Node<T>* createNode(T* data)
	{
		Node<T>* newNode = new Node < T >;
		newNode->data = data;
		newNode->next = NULL;
		newNode->prev = NULL;
		return newNode;
	}
	//ó�� ���
	Node<T>* begin(){ return head->next; }
	//�� ���
	Node<T>* end(){ return tail; }

	//��� ã��
	Node<T>* find(T* data)
	{
		for (Node<T>* pNode = begin();
			pNode != end();
			pNode = pNode->next)
		{
			if (pNode->data == data)
				return pNode;
		}
		return NULL;
	}

	//����
	void insert(Node<T>* pNode, T* data)
	{
		Node<T>* newNode = createNode(data);
		newNode->next = pNode->next;
		newNode->prev = pNode;
		pNode->next->prev = newNode;
		pNode->next = newNode;
	}

	//�տ� ����
	void push_front(T* data){ insert(head, data); }
	//�ڿ� ����
	void push_back(T* data){ insert(end()->prev, data); }

	//�����
	void erase(Node<T>* delNode)
	{
		if (delNode == head || delNode == tail)
			return;

		delNode->prev->next = delNode->next;
		delNode->next->prev = delNode->prev;
		delete delNode;
		delNode = NULL;
	}
	//ã�� �����
	void findErase(T* data){
		Node<T>* deleteNode = find(data);
		if (deleteNode != NULL){
			erase(deleteNode);
		}
	}

	//�ʱ�ȭ//
	/*
	����Ʈ�� ��带 ���� ������. push_back ���ִ� ���� ���ο� ��带 �����Ͽ� �ڿ� �ִ� �۾��̴�.
	deleteAll �ϰ� data���� ������ �����ϴ�. data�� ���ִ°� �� ����Ʈ�� ���ִ� ���� �ƴϴ�.
	clear��� �ϸ� �׳� ��� ��带 ����� �ٽ� ó�� ���·� ���ư��� �Լ��̴�.
	*/
	void clear(){
		//�� ���� ��
		deleteAll();

		//�ʱ� ���·� ���ư���.
		head = new Node < T >;
		tail = new Node < T >;
		head->next = tail;
		tail->prev = head;
	}
};

