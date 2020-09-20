#pragma once

#include <spdlog/spdlog.h>

namespace Finally::Log
{

template <typename FormatString, typename... Args>
inline void Info(FormatString& Message, Args&&... Arguments)
{
    spdlog::info(Message, std::forward<Args>(Arguments)...);
}

template <typename FormatString, typename... Args>
inline void Warn(FormatString& Message, Args&&... Arguments)
{
    spdlog::warn(Message, std::forward<Args>(Arguments)...);
}

template <typename FormatString, typename... Args>
inline void Error(FormatString& Message, Args&&... Arguments)
{
    spdlog::error(Message, std::forward<Args>(Arguments)...);
}

template <typename FormatString, typename... Args>
inline void Critical(FormatString& Message, Args&&... Arguments)
{
    spdlog::critical(Message, std::forward<Args>(Arguments)...);
}

}  // namespace Finally::Core
