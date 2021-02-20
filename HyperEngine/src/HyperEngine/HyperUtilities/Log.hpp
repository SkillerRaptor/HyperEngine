#pragma once

#include "HyperCore/Core.hpp"
#include "HyperUtilities/Logger.hpp"

namespace HyperUtilities
{
	class Log
	{
	private:
		static HyperCore::Ref<Logger> m_CoreLogger;
		static HyperCore::Ref<Logger> m_ClientLogger;

	public:
		static void Init();
		static void Shutdown();

		static void WaitForMessage(size_t messageId);

		static const HyperCore::Ref<Logger> GetCoreLogger() { return m_CoreLogger; }
		static const HyperCore::Ref<Logger> GetClientLogger() { return m_ClientLogger; }
	};
}

#define HP_CORE_INFO(...)    ::HyperUtilities::Log::GetCoreLogger()->Print(HyperUtilities::Logger::Level::HP_LEVEL_INFO, __VA_ARGS__)
#define HP_CORE_WARN(...)    ::HyperUtilities::Log::GetCoreLogger()->Print(HyperUtilities::Logger::Level::HP_LEVEL_WARN, __VA_ARGS__)
#define HP_CORE_ERROR(...)   ::HyperUtilities::Log::GetCoreLogger()->Print(HyperUtilities::Logger::Level::HP_LEVEL_ERROR, __VA_ARGS__)
#define HP_CORE_FATAL(...)   ::HyperUtilities::Log::GetCoreLogger()->Print(HyperUtilities::Logger::Level::HP_LEVEL_FATAL, __VA_ARGS__)
#define HP_CORE_DEBUG(...)   ::HyperUtilities::Log::GetCoreLogger()->Print(HyperUtilities::Logger::Level::HP_LEVEL_DEBUG, __VA_ARGS__)

#define HP_CLIENT_INFO(...)  ::HyperUtilities::Log::GetClientLogger()->Print(HyperUtilities::Logger::Level::HP_LEVEL_INFO, __VA_ARGS__)
#define HP_CLIENT_WARN(...)  ::HyperUtilities::Log::GetClientLogger()->Print(HyperUtilities::Logger::Level::HP_LEVEL_WARN, __VA_ARGS__)
#define HP_CLIENT_ERROR(...) ::HyperUtilities::Log::GetClientLogger()->Print(HyperUtilities::Logger::Level::HP_LEVEL_ERROR, __VA_ARGS__)
#define HP_CLIENT_FATAL(...) ::HyperUtilities::Log::GetClientLogger()->Print(HyperUtilities::Logger::Level::HP_LEVEL_FATAL, __VA_ARGS__)
#define HP_CLIENT_DEBUG(...) ::HyperUtilities::Log::GetClientLogger()->Print(HyperUtilities::Logger::Level::HP_LEVEL_DEBUG, __VA_ARGS__)