#include "System.h"

// µ¥Àý
apanoo::System* apanoo::System::m_Instance = NULL;
apanoo::System * apanoo::System::GetInstance()
{
	if (NULL == m_Instance)
	{
		m_Instance = new System;
	}
	return m_Instance;
}

apanoo::Time* apanoo::System::SystemTime()
{

}

