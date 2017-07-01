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

	//노드 추가
	Node<T>* createNode(T* data)
	{
		Node<T>* newNode = new Node < T >;
		newNode->data = data;
		newNode->next = NULL;
		newNode->prev = NULL;
		return newNode;
	}
	//처음 노드
	Node<T>* begin(){ return head->next; }
	//끝 노드
	Node<T>* end(){ return tail; }

	//노드 찾기
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

	//삽입
	void insert(Node<T>* pNode, T* data)
	{
		Node<T>* newNode = createNode(data);
		newNode->next = pNode->next;
		newNode->prev = pNode;
		pNode->next->prev = newNode;
		pNode->next = newNode;
	}

	//앞에 삽입
	void push_front(T* data){ insert(head, data); }
	//뒤에 삽입
	void push_back(T* data){ insert(end()->prev, data); }

	//지우기
	void erase(Node<T>* delNode)
	{
		if (delNode == head || delNode == tail)
			return;

		delNode->prev->next = delNode->next;
		delNode->next->prev = delNode->prev;
		delete delNode;
		delNode = NULL;
	}
	//찾아 지우기
	void findErase(T* data){
		Node<T>* deleteNode = find(data);
		if (deleteNode != NULL){
			erase(deleteNode);
		}
	}

	//초기화//
	/*
	리스트는 노드를 따로 가진다. push_back 해주는 일을 새로운 노드를 생성하여 뒤에 넣는 작업이다.
	deleteAll 하고도 data에는 접근이 가능하다. data를 없애는건 이 리스트가 해주는 일이 아니다.
	clear라고 하면 그냥 모든 노드를 지우고 다시 처음 상태로 돌아가는 함수이다.
	*/
	void clear(){
		//다 지운 후
		deleteAll();

		//초기 상태로 돌아간다.
		head = new Node < T >;
		tail = new Node < T >;
		head->next = tail;
		tail->prev = head;
	}
};

