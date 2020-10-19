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

    VulkanResource(VulkanResource&& Resource) noexcept { *this = std::move(Resource); }

    VulkanResource& operator=(VulkanResource&& Resource) noexcept
    {
        Handle = Resource.Handle;
        mDevice = Resource.mDevice;
        Resource.Handle = {};
        Resource.mDevice = {};
        return *this;
    }

    [[nodiscard]] T GetHandle() const { return Handle; }
    operator T() const { return Handle; }

    [[nodiscard]] T Release()
    {
        T temp = Handle;
        Handle = VK_NULL_HANDLE;
        mDevice = nullptr;
        return temp;
    }

protected:
    T Handle{};
    const class VulkanDevice* mDevice = nullptr;
};

}  // namespace Finally::Renderer
