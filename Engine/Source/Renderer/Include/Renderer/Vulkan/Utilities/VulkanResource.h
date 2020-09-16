#pragma once

namespace Finally::Renderer
{

template <typename T>
class VulkanResource
{
public:
    [[nodiscard]] T GetHandle() const { return Handle; }
    operator T() const { return Handle; }

protected:
    T Handle{};
};

}  // namespace Finally::Renderer
