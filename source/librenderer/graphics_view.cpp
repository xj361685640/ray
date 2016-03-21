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
#include <ray/graphics_view.h>

_NAME_BEGIN

__ImplementSubInterface(GraphicsRenderTexture, GraphicsChild, "GraphicsRenderTexture")

GraphicsRenderTextureDesc::GraphicsRenderTextureDesc() noexcept
	: _width(0)
	, _height(0)
{
}

GraphicsRenderTextureDesc::~GraphicsRenderTextureDesc() noexcept
{
}

void 
GraphicsRenderTextureDesc::setWidth(std::uint32_t w) noexcept
{
	_width = w;
}

void 
GraphicsRenderTextureDesc::setHeight(std::uint32_t h) noexcept
{
	_height = h;
}

std::uint32_t 
GraphicsRenderTextureDesc::getWidth() const noexcept
{
	return _width;
}

std::uint32_t 
GraphicsRenderTextureDesc::getHeight() const noexcept
{
	return _height;
}

void
GraphicsRenderTextureDesc::attach(GraphicsTexturePtr texture) noexcept
{
	assert(texture);
	assert(std::find(_textures.begin(), _textures.end(), texture) == _textures.end());

	_textures.push_back(texture);
}

void
GraphicsRenderTextureDesc::detach(GraphicsTexturePtr texture) noexcept
{
	auto it = std::find(_textures.begin(), _textures.end(), texture);
	if (it != _textures.end())
		_textures.erase(it);
}

GraphicsTextures&
GraphicsRenderTextureDesc::getTextures() noexcept
{
	return _textures;
}

const GraphicsTextures&
GraphicsRenderTextureDesc::getTextures() const noexcept
{
	return _textures;
}

void
GraphicsRenderTextureDesc::setSharedDepthTexture(GraphicsTexturePtr target) noexcept
{
	_sharedDepthTexture = target;
}

void
GraphicsRenderTextureDesc::setSharedStencilTexture(GraphicsTexturePtr target) noexcept
{
	_sharedStencilTexture = target;
}

GraphicsTexturePtr
GraphicsRenderTextureDesc::getSharedDepthTexture() const noexcept
{
	return _sharedDepthTexture;
}

GraphicsTexturePtr
GraphicsRenderTextureDesc::getSharedStencilTexture() const noexcept
{
	return _sharedStencilTexture;
}

GraphicsRenderTexture::GraphicsRenderTexture() noexcept
{
}

GraphicsRenderTexture::~GraphicsRenderTexture() noexcept
{
}

_NAME_END