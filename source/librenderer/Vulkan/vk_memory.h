// +----------------------------------------------------------------------
// | Project : ray.
// | All rights reserved.
// +----------------------------------------------------------------------
// | Copyright (c) 2013-2016.
// +----------------------------------------------------------------------
// | * Redistribution and use of this software in source and binary forms,
// |   with or without modification, are permitted provided that the following
// |   conditions are met:
// |
// | * Redistributions of source code must retain the above
// |   copyright notice, this list of conditions and the
// |   following disclaimer.
// |
// | * Redistributions in binary form must reproduce the above
// |   copyright notice, this list of conditions and the
// |   following disclaimer in the documentation and/or other
// |   materials provided with the distribution.
// |
// | * Neither the name of the ray team, nor the names of its
// |   contributors may be used to endorse or promote products
// |   derived from this software without specific prior
// |   written permission of the ray team.
// |
// | THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// | "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// | LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// | A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// | OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// | SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// | LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// | DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// | THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// | (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// | OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// +----------------------------------------------------------------------
#ifndef _H_VK_MEMORY_H_
#define _H_VK_MEMORY_H_

#include "vk_types.h"

_NAME_BEGIN

class VulkanMemory final
{
public:
	VulkanMemory() noexcept;
	virtual ~VulkanMemory() noexcept;

	bool setup(const char* data, std::uint32_t datasize, std::uint32_t typeBits, std::uint32_t mask) noexcept;
	void close() noexcept;

	std::uint32_t size() const noexcept;

	void* map(std::uint32_t access) noexcept;
	void* map(std::uint32_t offset, std::uint32_t cnt, std::uint32_t access) noexcept;

	void unmap() noexcept;

	VkDeviceMemory getDeviceMemory() const noexcept;

	void setDevice(GraphicsDevicePtr device) noexcept;
	GraphicsDevicePtr getDevice() noexcept;

	bool memory_type_from_properties(VkMemoryType memoryTypes[], uint32_t typeBits, VkFlags requirements_mask, uint32_t *typeIndex);

private:
	VulkanMemory(const VulkanMemory&) noexcept = delete;
	VulkanMemory& operator=(const VulkanMemory&) noexcept = delete;

private:
	bool _isMapping;
	std::uint32_t _size;

	VkDeviceMemory _vkMemory;

	GraphicsDeviceWeakPtr _device;
};

_NAME_END

#endif