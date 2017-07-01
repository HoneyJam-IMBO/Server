#pragma once


class CComponentObject;

enum component_id{
	COMPONENTID_END
};

enum family_id{
	FAMILYID_END
};


class CComponentBase{
public:
	virtual BOOL Begin();
	virtual BOOL End();

	//해당 컴포넌트 Update
	virtual void Update(float fTimeElapsed){};

	//familyid, 내 id get
	const family_id const GetFamilyID(){ return m_FamilyID; };
	const component_id const GetID(){ return m_ID; };

	//owner set, get
	void SetOwner(CComponentObject* pObject);
	CComponentObject* GetOwner(){ return m_pOwner; }

private:
	//컴포넌트 id
	component_id m_ID;

	//같은 종류의 컴포넌트를 모아놓은 패밀리 id
	//ex) geometry 사용한 render와 그냥 render
	family_id m_FamilyID;

	CComponentObject* m_pOwner;

public:
	
	CComponentBase();
	virtual ~CComponentBase();
};

