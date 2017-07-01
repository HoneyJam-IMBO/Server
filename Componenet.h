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

	//�ش� ������Ʈ Update
	virtual void Update(float fTimeElapsed){};

	//familyid, �� id get
	const family_id const GetFamilyID(){ return m_FamilyID; };
	const component_id const GetID(){ return m_ID; };

	//owner set, get
	void SetOwner(CComponentObject* pObject);
	CComponentObject* GetOwner(){ return m_pOwner; }

private:
	//������Ʈ id
	component_id m_ID;

	//���� ������ ������Ʈ�� ��Ƴ��� �йи� id
	//ex) geometry ����� render�� �׳� render
	family_id m_FamilyID;

	CComponentObject* m_pOwner;

public:
	
	CComponentBase();
	virtual ~CComponentBase();
};

