#include "GameManager.h" 

GameManager* GameManager::m_mySingleton = NULL;

GameManager::GameManager() {
}

GameManager* GameManager::sharedGameManager() {
	if (m_mySingleton == NULL) {
		m_mySingleton = new GameManager();
	}
	return m_mySingleton;
}