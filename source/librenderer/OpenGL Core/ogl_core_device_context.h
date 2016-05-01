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
#ifndef _H_OGL_CORE_DEVICE_CONTEXT_H_
#define _H_OGL_CORE_DEVICE_CONTEXT_H_

#include "ogl_types.h"

_NAME_BEGIN

class OGLCoreDeviceContext final : public GraphicsContext2
{
	__DeclareSubClass(OGLCoreDeviceContext, GraphicsContext2)
public:
	OGLCoreDeviceContext() noexcept;
	~OGLCoreDeviceContext() noexcept;

	bool setup(const GraphicsContextDesc& desc) noexcept;
	void close() noexcept;

	void renderBegin() noexcept;
	void renderEnd() noexcept;

	void setViewport(const Viewport& viewport) noexcept;
	const Viewport& getViewport() const noexcept;

	void setScissor(const Scissor& scissor) noexcept;
	const Scissor& getScissor() const noexcept;

	void setStencilCompare(GraphicsStencilFace face, GraphicsCompareFunc func) noexcept;
	GraphicsCompareFunc getStencilCompare(GraphicsStencilFace face) noexcept;

	void setStencilReference(GraphicsStencilFace face, std::uint32_t reference) noexcept;
	std::uint32_t getStencilReference(GraphicsStencilFace face) noexcept;

	void setStencilFrontWriteMask(GraphicsStencilFace face, std::uint32_t mask) noexcept;
	std::uint32_t getStencilFrontWriteMask(GraphicsStencilFace face) noexcept;

	void setRenderPipeline(GraphicsPipelinePtr pipeline) noexcept;
	GraphicsPipelinePtr getRenderPipeline() const noexcept;

	void setDescriptorSet(GraphicsDescriptorSetPtr descriptorSet) noexcept;
	GraphicsDescriptorSetPtr getDescriptorSet() const noexcept;

	void setVertexBufferData(GraphicsDataPtr data) noexcept;
	GraphicsDataPtr getVertexBufferData() const noexcept;

	void setIndexBufferData(GraphicsDataPtr data) noexcept;
	GraphicsDataPtr getIndexBufferData() const noexcept;

	void* mapTexture(GraphicsTexturePtr texture, std::uint32_t x, std::uint32_t y, std::uint32_t w, std::uint32_t h, GraphicsFormat format, GraphicsAccessFlags flags) noexcept;
	void unmapTexture(GraphicsTexturePtr texture) noexcept;

	void setFramebuffer(GraphicsFramebufferPtr target) noexcept;
	void setFramebuffer(GraphicsFramebufferPtr target, const float4& color, float depth, std::int32_t stencil) noexcept;
	void clearFramebuffer(GraphicsClearFlags flags, const float4& color, float depth, std::int32_t stencil) noexcept;
	void clearFramebufferIndexed(GraphicsClearFlags flags, const float4& color, float depth, std::int32_t stencil, std::uint32_t i) noexcept;
	void discardFramebuffer() noexcept;
	void blitFramebuffer(GraphicsFramebufferPtr src, const Viewport& v1, GraphicsFramebufferPtr dest, const Viewport& v2) noexcept;
	void readFramebuffer(GraphicsFramebufferPtr source, GraphicsFormat pfd, std::size_t w, std::size_t h, std::size_t bufsize, void* data) noexcept;
	GraphicsFramebufferPtr getFramebuffer() const noexcept;

	void drawRenderMesh(const GraphicsIndirect& renderable) noexcept;
	void drawRenderMesh(const GraphicsIndirect renderable[], std::size_t first, std::size_t count) noexcept;

	bool isTextureSupport(GraphicsFormat format) noexcept;
	bool isTextureDimSupport(GraphicsTextureDim dimension) noexcept;
	bool isVertexSupport(GraphicsFormat format) noexcept;
	bool isShaderSupport(GraphicsShaderStage stage) noexcept;

	void present() noexcept;

private:
	bool checkSupport() noexcept;

	bool initDebugControl(const GraphicsContextDesc& desc) noexcept;
	bool initTextureSupports() noexcept;
	bool initTextureDimSupports() noexcept;
	bool initVertexSupports() noexcept;
	bool initShaderSupports() noexcept;
	bool initStateSystem() noexcept;

	static void GLAPIENTRY debugCallBack(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const GLvoid* userParam) noexcept;

private:
	friend class OGLDevice;
	void setDevice(GraphicsDevicePtr device) noexcept;
	GraphicsDevicePtr getDevice() noexcept;

private:
	OGLCoreDeviceContext(const OGLCoreDeviceContext&) noexcept = delete;
	OGLCoreDeviceContext& operator=(const OGLCoreDeviceContext&) noexcept = delete;

private:
	OGLSwapchainPtr _glcontext;

	float4 _clearColor;
	GLfloat _clearDepth;
	GLint   _clearStencil;

	OGLCoreFramebufferPtr _renderTexture;

	OGLProgramPtr _shaderObject;

	OGLCorePipelinePtr _pipeline;
	OGLCoreDescriptorSetPtr _descriptorSet;

	OGLGraphicsStatePtr _state;
	OGLGraphicsStatePtr _stateDefault;
	GraphicsStateDesc _stateCaptured;

	GLuint _stateObjDraw;
	GLuint _stateObjDrawGeo;

	GLuint      _tokenBuffer;
	GLuint      _tokenCmdList;
	std::string _tokenData;

	bool _needUpdateLayout;
	bool _needUpdateState;

	OGLCoreGraphicsDataPtr _vbo;
	OGLCoreGraphicsDataPtr _ibo;

	Viewport _viewport;
	Scissor _scissor;

	std::vector<GraphicsFormat> _supportTextures;
	std::vector<GraphicsTextureDim> _supportTextureDims;
	std::vector<GraphicsFormat> _supportAttribute;
	std::vector<GraphicsShaderStage> _supportShaders;

	GraphicsDeviceWeakPtr _device;
};

_NAME_END

#endif