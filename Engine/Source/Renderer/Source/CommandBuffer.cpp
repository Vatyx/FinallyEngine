#include "Renderer/CommandBuffer.h"

#include <utility>

namespace Finally::Renderer
{

CommandBuffer::CommandBuffer(VulkanCommandBuffer&& resource)
{
    mVulkanCommandBuffer = std::move(resource);
}

}
