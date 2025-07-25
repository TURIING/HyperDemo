/********************************************************************************
* @author: TURIING
* @email: turiing@163.com
* @date: 2024/10/27 14:04
* @version: 1.0
* @description: 
********************************************************************************/

#include "LogManager.h"

void LogManager::Init() {
     m_pLogger = spdlog::stdout_color_mt<spdlog::async_factory>("HyperDemoLogger");
     m_pLogger->set_level(spdlog::level::trace);
     m_pLogger->set_pattern("[%^%H:%M:%S:%e] [%P-%t] [%1!L] [%s:%#] - %v%$");
     LOG_INFO("Log initialization successful");
}
