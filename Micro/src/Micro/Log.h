#pragma once

#include "Core.h"
#include "spdlog\spdlog.h"
#include "spdlog\fmt\ostr.h"

namespace Micro
{
	class MICRO_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};

}

//CORE Log Macros
#define MC_CORE_TRACE(...)   ::Micro::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define MC_CORE_INFO(...)    ::Micro::Log::GetCoreLogger()->info(__VA_ARGS__)
#define MC_CORE_WARN(...)    ::Micro::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define MC_CORE_ERROR(...)   ::Micro::Log::GetCoreLogger()->error(__VA_ARGS__)
#define MC_CORE_FATAL(...)   ::Micro::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client Log Macros
#define MC_TRACE(...)        ::Micro::Log::GetClientLogger()->trace(__VA_ARGS__)
#define MC_INFO(...)         ::Micro::Log::GetClientLogger()->info(__VA_ARGS__)
#define MC_WARN(...)         ::Micro::Log::GetClientLogger()->warn(__VA_ARGS__)
#define MC_ERROR(...)        ::Micro::Log::GetClientLogger()->error(__VA_ARGS__)
#define MC_FATAL(...)        ::Micro::Log::GetClientLogger()->fatal(__VA_ARGS__)