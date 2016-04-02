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
#ifndef _H_OGL_TYPES_H_
#define _H_OGL_TYPES_H_

#include <ray/graphics_device.h>
#include <ray/graphics_swapchain.h>
#include <ray/graphics_context.h>
#include <ray/graphics_data.h>
#include <ray/graphics_state.h>
#include <ray/graphics_sampler.h>
#include <ray/graphics_texture.h>
#include <ray/graphics_framebuffer.h>
#include <ray/graphics_shader.h>
#include <ray/graphics_pipeline.h>
#include <ray/graphics_descriptor.h>
#include <ray/graphics_input_layout.h>

#include "ogl_basic.h"

_NAME_BEGIN

#if _BUILD_OPENGL
#	ifdef GLEW_MX
	extern GLEWContext _glewctx;
#	define glewGetContext() (&_glewctx)
#	endif

#  if defined(__MINGW32__) || defined(__CYGWIN__)
#    define GLEXT_APIENTRY __stdcall
#  elif (_MSC_VER >= 800) || defined(_STDCALL_SUPPORTED) || defined(__BORLANDC__)
#    define GLEXT_APIENTRY __stdcall
#  else
#    define GLEXT_APIENTRY
#  endif
#endif

#if GL_DEBUG
#	if defined(_VISUAL_STUDIO_)
#		pragma warning(disable : 4127)
#	endif
#	define GL_CHECK(x) do { x; OGLCheck::checkError(); } while (false)
#else
#	define GL_CHECK(x) x
#endif

#if _DEBUG
#	if defined(_VISUAL_STUDIO_)
#		pragma warning(disable : 4127)
#	endif
#	define GL_PLATFORM_LOG(format, ...) OGLCheck::debugOutput(format, __VA_ARGS__)
#else
#	define GL_PLATFORM_LOG(format, ...)
#endif

#if _DEBUG
#	if defined(_VISUAL_STUDIO_)
#		pragma warning(disable : 4127)
#	endif
#	define GL_PLATFORM_ASSERT(expr, format) if (!(expr)) { OGLCheck::debugOutput(format); assert(expr); }
#else
#	define GL_PLATFORM_ASSERT(expr, format)
#endif

typedef std::shared_ptr<class OGLSwapchain> OGLSwapchainPtr;
typedef std::shared_ptr<class OGLDevice> OGLDevicePtr;
typedef std::shared_ptr<class OGLDeviceContext> OGLDeviceContextPtr;
typedef std::shared_ptr<class OGLFramebuffer> OGLFramebufferPtr;
typedef std::shared_ptr<class OGLShader> OGLShaderPtr;
typedef std::shared_ptr<class OGLShaderObject> OGLShaderObjectPtr;
typedef std::shared_ptr<class OGLGraphicsData> OGLGraphicsDataPtr;
typedef std::shared_ptr<class OGLInputLayout> OGLInputLayoutPtr;
typedef std::shared_ptr<class OGLDrawIndirectBuffer> OGLDrawIndirectBufferPtr;
typedef std::shared_ptr<class OGLGraphicsState> OGLGraphicsStatePtr;
typedef std::shared_ptr<class OGLTexture> OGLTexturePtr;
typedef std::shared_ptr<class OGLSampler> OGLSamplerPtr;
typedef std::shared_ptr<class OGLRenderPipeline> OGLRenderPipelinePtr;
typedef std::shared_ptr<class OGLDescriptorSet> OGLDescriptorSetPtr;

typedef std::vector<OGLShaderPtr> OGLShaders;

struct GPUfbconfig
{
	int redSize;
	int greenSize;
	int blueSize;
	int alphaSize;

	int bufferSize;
	int depthSize;
	int stencilSize;

	int accumSize;
	int accumRedSize;
	int accumGreenSize;
	int accumBlueSize;
	int accumAlphaSize;

	int samples;
};

struct GPUctxconfig
{
	int api;
	int major;
	int minor;
	int forward;
	int profile;
	int robustness;
	int release;
	int multithread;

#if _BUILD_PLATFORM_WINDOWS
	HGLRC share;
#endif
};

class OGLTypes
{
public:
	static GLenum asVertexType(GraphicsVertexType type) noexcept;
	static GLenum asVertexFormat(GraphicsFormat format) noexcept;
	static GLenum asIndexType(GraphicsIndexType type) noexcept;
	static GLenum asShaderType(GraphicsShaderStage type) noexcept;
	static GLenum asTextureTarget(GraphicsTextureDim mapping, bool multisampler) noexcept;
	static GLenum asTextureFormat(GraphicsFormat format) noexcept;
	static GLenum asTextureType(GraphicsFormat format) noexcept;
	static GLenum asTextureInternalFormat(GraphicsFormat format) noexcept;
	static GLenum asCompareFunction(GraphicsCompareFunc func) noexcept;
	static GLenum asBlendFactor(GraphicsBlendFactor func) noexcept;
	static GLenum asBlendOperation(GraphicsBlendOp op) noexcept;
	static GLenum asCullMode(GraphicsCullMode mode) noexcept;
	static GLenum asFillMode(GraphicsPolygonMode mode) noexcept;
	static GLenum asStencilOperation(GraphicsStencilOp stencilop) noexcept;
	static GLenum asSamplerWrap(GraphicsSamplerWrap wrap) noexcept;
	static GLenum asSamplerFilter(GraphicsSamplerFilter filter) noexcept;

	static GLboolean isCompressedTexture(GraphicsFormat format) noexcept;
};

class OGLCheck
{
public:
	static bool checkError() noexcept;

	static void debugOutput(const std::string& message, ...) noexcept;
};

_NAME_END

#endif