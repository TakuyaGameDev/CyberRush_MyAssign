#include "EnemyAIManager.h"
#include "Enemy.h"
#include "PodAI.h"

EnemyAIManager::EnemyAIManager(std::list<std::shared_ptr<Enemy>>& friends):
friendList_(friends)
{

}

EnemyAIManager::~EnemyAIManager()
{

}

void EnemyAIManager::UpDate(const std::shared_ptr<Enemy> enemy)
{
	// AIBase��e�Ƃ��Ă���PodAI���̊e�G��ׂɉ�����AI�̋N��
	// ���̐�ł͊֐��߲�����񂵂Ă���̂ŁA�����ɍ��v�����s�������s
	// friendList_ : �����̓G
	enemy->GetAISystem()->AIAction(friendList_);
}


