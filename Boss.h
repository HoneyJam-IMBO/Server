#pragma once
class CBoss : public CMultiThreadSync<CBoss>
{
public:
	CBoss();
	~CBoss();
	void begin(int InitHP) { m_HP = InitHP; }
	void end() {}
	void SetHP(int hp) { m_HP = hp; }
	int DamageToHP(int damage) { CThreadSync Sync; m_HP -= damage; return m_HP; }
	int GetHP() { CThreadSync Sync; return m_HP; };
private:
	int m_HP;

};

