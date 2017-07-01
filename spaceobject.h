#pragma once
//#include "Object.h"
#include "Space.h"

//
////이제 공간이 아니라 지역이다.
///*
//주요 기능은 객체에 id를 부여하는 것이다.
//지역에서 활동하는 객체는 이 클래스를 상속받아야 한다.
//*/
//class CSpaceObject :public CGameObject {
//public:
//	virtual void Begin();
//	virtual void End();
//	virtual bool Animate(float fTimeElapsed);
//
//	// 고유함수
//	CSpace* GetSpace();
//	void SetSpace(CSpace* pSpace);
//
//	//고유함수
//
//protected:
//	CSpace* m_pSpace;
//
//private:
//
//public:
//	CSpaceObject();
//	virtual ~CSpaceObject();
//};
//
//