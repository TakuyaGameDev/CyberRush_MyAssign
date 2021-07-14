#pragma once
#include <vector>
#include "AIBase.h"

#include "Geometory.h"

constexpr int LaserSizeX = 0;
constexpr int LaserSizeY = 50;

class BigboyAI :
	public AIBase
{
public:
	BigboyAI(Enemy& enemy);
	~BigboyAI();

	void Update(std::list<std::shared_ptr<Enemy>>& enemies);
private:
	void Initialize(void);
	// �֐��߲��
	bool(BigboyAI::* updater_)(std::list<std::shared_ptr<Enemy>>& enemies);

	// ��莞�Ԏ~�܂�����ڲ԰�̍s�����ώ@����B
	// ������Bigboy�̍s�������肷��B
	bool Observe(std::list<std::shared_ptr<Enemy>>& enemies);
	// ��ڲ԰�Ɍ������ĕ���
	bool Walk(std::list<std::shared_ptr<Enemy>>& enemies);
	// ��ڲ԰�Ƃ�Z�������킹��
	bool ZArrange(std::list<std::shared_ptr<Enemy>>& enemies);
	// �ڰђP�ʂōU������
	bool Attack(std::list<std::shared_ptr<Enemy>>& enemies);
	// ��莞�Ԍo�����獂���ެ��߂���
	bool Jump(std::list<std::shared_ptr<Enemy>>& enemies);
	// ��Ұ��
	bool OnDamaged(std::list<std::shared_ptr<Enemy>>& enemies);
	// ����
	bool Death(std::list<std::shared_ptr<Enemy>>& enemies);
	// �^�b�N��
	bool LaserAttack(std::list<std::shared_ptr<Enemy>>& enemies);

	float jumpSp_;
	float jumpForce_;
	float jumpFirstSp_;

	float tackleAccelSp_;
	float tackleSp_;
	float tackleFirstSp_;

	bool isShotLaser_[2];

	int walkFrame_;
	bool isJumpAction_;
	int jumpInterval_;

	Vector2I laserRect_;
};

