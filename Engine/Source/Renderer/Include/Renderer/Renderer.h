#pragma once

#include <memory>

namespace Finally::Renderer
{

class VulkanInstance;

class Renderer
{
public:
    Renderer();
    ~Renderer();

    [[nodiscard]] const VulkanInstance& GetVulkanInstance() const { return *Instance; }

private:
    std::unique_ptr<VulkanInstance> Instance;
};

}  // namespace Finally::Renderer
