#include "util.h"

#include <iostream>


void print_surface_caps(VkSurfaceCapabilitiesKHR const& capabilities)
{
    std::cout << "=== Surface Capabilities ===\n"
              << "  minImageCount:           " << capabilities.minImageCount << "\n"
              << "  maxImageCount:           " << capabilities.maxImageCount << "\n"
              << "  currentExtent:           " << capabilities.currentExtent.width << " x " << capabilities.currentExtent.height << "\n"
              << "  minImageExtent:          " << capabilities.minImageExtent.width << " x " << capabilities.minImageExtent.height << "\n"
              << "  maxImageExtent:          " << capabilities.maxImageExtent.width << " x " << capabilities.maxImageExtent.height << "\n"
              << "  maxImageArrayLayers:     " << capabilities.maxImageArrayLayers << "\n"
              << "  supportedTransforms:     0x" << std::hex << capabilities.supportedTransforms << std::dec << "\n"
              << "  currentTransform:        0x" << std::hex << capabilities.currentTransform << std::dec << "\n"
              << "  supportedCompositeAlpha: 0x" << std::hex << capabilities.supportedCompositeAlpha << std::dec << "\n"
              << "  supportedUsageFlags:     0x" << std::hex << capabilities.supportedUsageFlags << std::dec << "\n"
              << "============================" << std::endl;
}
