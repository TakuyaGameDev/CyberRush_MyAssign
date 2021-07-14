#pragma once
#include "AIBase.h"

class Enemy;

class SpacenautAI :
	public AIBase
{
public:
	SpacenautAI(Enemy& enemy);
	~SpacenautAI();

	void Update(std::list<std::shared_ptr<Enemy>>& enemies);

	bool Search(std::list<std::shared_ptr<Enemy>>& enemies);
	// �����s��
	bool Walk(std::list<std::shared_ptr<Enemy>>& enemies);
	// ��ڲ԰��Z���Ɏ�����Z�������킹��
	bool ArrangementZ(std::list<std::shared_ptr<Enemy>>& enemies);
	// Z������ڲ԰�Ƃ�������U��������(�e���o��)
	bool Attack(std::list<std::shared_ptr<Enemy>>& enemies);

	bool OnDamaged(std::list<std::shared_ptr<Enemy>>& enemies);
	bool Death(std::list<std::shared_ptr<Enemy>>& enemies);

private:

	void Initialize(void);
	bool(SpacenautAI::* updater_)(std::list<std::shared_ptr<Enemy>>&);

	int frame;
	int damage_anim_frame;
	int target_pos_z;
	Vector2I partnerPos_;

	bool moveRight_;
	bool moveLeft_;

	bool anim_flag;
};
