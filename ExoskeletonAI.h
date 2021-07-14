#pragma once
#include "AIBase.h"
class ExoskeletonAI :
    public AIBase
{
public:
	ExoskeletonAI(Enemy& enemy);
	~ExoskeletonAI();
	// �X�V�֐�
	void Update(std::list<std::shared_ptr<Enemy>>& enemies);

	// ��ڲ԰�̔w��ɉ�荞��
	bool Run(std::list<std::shared_ptr<Enemy>>& enemies);
	// ����
	bool Death(std::list<std::shared_ptr<Enemy>>& enemies);
private:
	// ������
	void Initialize(void);
	// ��ԑJ�ڊ֐��߲��
	bool(ExoskeletonAI::* updater_)(std::list<std::shared_ptr<Enemy>>&);
	// �ڒn������A��ڲ԰�̈ʒu��������ڰѶ���
	int searchFrame;
	// ׼ޱ݊p�x
	float rad;
	// ��ڲ԰���߼޼��
	Vector2I player_pos;
};

