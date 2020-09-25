#pragma once

namespace Finally::Renderer
{

class VulkanDevice;

template <typename T>
class VulkanResource
{
public:
    VulkanResource() noexcept = default;

    VulkanResource(VulkanResource&) = delete;
    VulkanResource& operator=(VulkanResource&) = delete;

    VulkanResource(VulkanResource&& Resource) noexcept
    {
        Handle = Resource.Handle;
        Resource.Handle = {};
    }

    VulkanResource& operator=(VulkanResource&& Resource) noexcept
    {
        Handle = Resource.Handle;
        Resource.Handle = {};
        return *this;
    }

    [[nodiscard]] T GetHandle() const { return Handle; }
    operator T() const { return Handle; }

protected:
    T Handle{};
};

}  // namespace Finally::Renderer
