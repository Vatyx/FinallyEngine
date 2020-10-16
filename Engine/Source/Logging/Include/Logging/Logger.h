#pragma once

#include <memory>

#include <spdlog/common.h>
#include <spdlog/sinks/wincolor_sink.h>
#include <spdlog/spdlog.h>

#define DeclareLogCategory(category, catDisplayName)                                                                                                 \
    const char category ## CatStr[] = "#catDisplayName";                                                                                \
    const auto category = Finally::Logger::LogCategory<category##CatStr>{};

namespace Finally::Logger
{

template <const char* Name>
struct LogCategory
{
    static constexpr const char* categoryName = Name;
};

using namespace spdlog;

using Logger = std::shared_ptr<logger>;

template <typename FormatString, typename... Args>
using LoggingFunction = void (spdlog::logger::*)(const FormatString&, const Args&...);

template <const char* Name, typename FormatString, typename... Args>
inline void Info(LogCategory<Name> Category, FormatString&& Message, Args&&... Arguments)
{
    constexpr LoggingFunction<FormatString, Args...> loggingFunction = &spdlog::logger::info;
    Details::InternalLog<loggingFunction>(Category, Message, std::forward<Args>(Arguments)...);
}

template <const char* Name, typename FormatString, typename... Args>
inline void Warn(LogCategory<Name> Category, FormatString&& Message, Args&&... Arguments)
{
    constexpr LoggingFunction<FormatString, Args...> loggingFunction = &spdlog::logger::warn;
    Details::InternalLog<loggingFunction>(Category, Message, std::forward<Args>(Arguments)...);
}

template <const char* Name, typename FormatString, typename... Args>
inline void Error(LogCategory<Name> Category, FormatString&& Message, Args&&... Arguments)
{
    constexpr LoggingFunction<FormatString, Args...> loggingFunction = &spdlog::logger::error;
    Details::InternalLog<loggingFunction>(Category, Message, std::forward<Args>(Arguments)...);
}

template <const char* Name, typename FormatString, typename... Args>
inline void Critical(LogCategory<Name> Category, FormatString&& Message, Args&&... Arguments)
{
    constexpr LoggingFunction<FormatString, Args...> loggingFunction = &spdlog::logger::critical;
    Details::InternalLog<loggingFunction>(Category, Message, std::forward<Args>(Arguments)...);
}

namespace Details
{
    template <auto LoggingFunction, const char* Name, typename FormatString, typename... Args>
    inline void InternalLog(LogCategory<Name> category, FormatString&& message, Args&&... args)
    {
        std::shared_ptr<spdlog::logger> loggerRef = spdlog::get(category.categoryName);
        if (loggerRef == nullptr)
        {
            auto sink = std::make_shared<sinks::wincolor_stdout_sink_mt>();
            loggerRef = std::make_shared<spdlog::logger>(category.categoryName, sink);

            spdlog::register_logger(loggerRef);
        }

        (loggerRef.get()->*LoggingFunction)(std::forward<FormatString>(message), std::forward<Args>(args)...);
    }
}  // namespace Details

}  // namespace Finally::Logger

DeclareLogCategory(LogDefault, "Default");
