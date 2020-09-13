#pragma once

#include <type_traits>
#include <xutility>

namespace Finally
{

template <typename T, typename Cleanup>
class DelayedResourceCleanup
{
public:
    virtual ~DelayedResourceCleanup() { Cleanup()(Resource); }

protected:
    T Resource;
};

template <typename T, typename Deleter>
struct UniqueResource {
    constexpr UniqueResource() = default;
    constexpr explicit UniqueResource(T InResource) : Resource(std::move(InResource)) {}

    template <typename... Args>
    constexpr explicit UniqueResource(Args&&... args) : Resource(std::forward<Args>(args)...)
    {}

    constexpr UniqueResource(UniqueResource& other) = delete;
    constexpr UniqueResource& operator=(UniqueResource& rhs) = delete;

    constexpr UniqueResource(UniqueResource&& Other) noexcept : Resource(std::exchange(Other.Resource, T{})) {}
    constexpr UniqueResource& operator=(UniqueResource&& Other) noexcept
    {
        if (Resource) { Deleter{}(Resource); }

        Resource = std::exchange(Other.Resource, T{});

        return *this;
    }

    ~UniqueResource()
    {
        if (Resource) { Deleter{}(Resource); }
    }

    T Get() const { return Resource; }

private:
    T Resource{};
};

// struct VkDeviceWrapper
//{
//	VkDeviceWrapper() = default;
//	VkDeviceWrapper(VkDevice InDevice) : Device(InDevice) {}
//
//	~VkDeviceWrapper() { if (Device != VK_NULL_HANDLE) { vkDestroyDevice(Device, nullptr); } }
//
//	VkDeviceWrapper(const VkDeviceWrapper&) = delete;
//	VkDeviceWrapper(const VkDeviceWrapper&) = delete;
//	VkDeviceWrapper(VkDeviceWrapper&& Source)
//	{
//		Device = Source.Device;
//		Source.Device = VK_NULL_HANDLE;
//	}
//
//	VkDevice Device = VK_NULL_HANDLE;
//};

}  // namespace Finally
