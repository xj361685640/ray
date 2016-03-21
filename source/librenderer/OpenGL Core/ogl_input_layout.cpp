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
#include "ogl_input_layout.h"
#include "ogl_shader.h"
#include "ogl_vbo.h"
#include "ogl_ibo.h"

_NAME_BEGIN

__ImplementSubClass(OGLInputLayout, GraphicsInputLayout, "OGLInputLayout")

OGLInputLayout::OGLInputLayout() noexcept
	: _vao(GL_NONE)
	, _ibo(GL_NONE)
{
}

OGLInputLayout::~OGLInputLayout() noexcept
{
}

bool
OGLInputLayout::setup(const GraphicsInputLayoutDesc& inputLayout) noexcept
{
	assert(!_vao);

	if (OGLTypes::asIndexType(inputLayout.getIndexType()) == GL_INVALID_ENUM)
		return false;

	auto& component = inputLayout.getVertexComponents();
	for (auto& it : component)
	{
		auto& semantic = it.getSemantic();
		if (semantic.empty())
		{
			GL_PLATFORM_LOG("Empty semantic");
			return false;
		}

		for (auto& ch : semantic)
		{
			if (ch < 'a' && ch > 'z')
			{
				GL_PLATFORM_LOG("Error semantic describe : %s", semantic);
				return false;
			}
		}
	}

	glCreateVertexArrays(1, &_vao);
	if (_vao == GL_NONE)
	{
		GL_PLATFORM_LOG("glCreateVertexArrays() fail");
		return false;
	}

	_inputLayoutDesc = inputLayout;
	return true;
}

void
OGLInputLayout::close() noexcept
{
	if (_vao)
	{
		glDeleteVertexArrays(1, &_vao);
		_vao = GL_NONE;
	}
}

GLuint 
OGLInputLayout::getInstanceID() const noexcept
{
	return _vao;
}

const GraphicsInputLayoutDesc&
OGLInputLayout::getGraphicsInputLayoutDesc() const noexcept
{
	return _inputLayoutDesc;
}

void
OGLInputLayout::bindLayout(OGLShaderObjectPtr program) noexcept
{
	glBindVertexArray(_vao);

	if (_program != program)
	{
		GLuint offset = 0;

		auto& components = _inputLayoutDesc.getVertexComponents();
		for (auto& it : components)
		{
			GLuint attribIndex = GL_INVALID_INDEX;
			GLuint bindingIndex = it.getVertexSlot();
			GLenum type = OGLTypes::asVertexFormat(it.getVertexFormat());

			auto& attributes = program->getActiveAttributes();
			for (auto& attrib : attributes)
			{
				if (attrib->getSemanticIndex() == it.getSemanticIndex() && attrib->getSemantic() == it.getSemantic())
				{
					attribIndex = attrib->downcast<OGLShaderAttribute>()->getLocation();
					break;
				}
			}

			if (attribIndex != GL_INVALID_INDEX)
			{
				glEnableVertexArrayAttrib(_vao, attribIndex);
				glVertexArrayAttribBinding(_vao, attribIndex, bindingIndex);
				glVertexArrayAttribFormat(_vao, attribIndex, it.getVertexCount(), type, GL_FALSE, offset);

				if (it.getVertexDivisor() > 0)
					glVertexArrayBindingDivisor(_vao, bindingIndex, it.getVertexDivisor());
			}

			offset += it.getVertexSize();
		}

		_program = program;
	}
}

void
OGLInputLayout::bindVbo(OGLVertexBufferPtr vbo, std::uint8_t slot) noexcept
{
	assert(vbo);

	if (slot > MAX_VERTEX_UNIT)
		return;

	if (_vbo[slot] != vbo)
	{
		GLuint stride = vbo->getGraphicsDataDesc().getStride();
		glVertexArrayVertexBuffer(_vao, slot, vbo->getInstanceID(), 0, stride);
		_vbo[slot] = vbo;
	}
}

void
OGLInputLayout::bindIbo(OGLIndexBufferPtr ibo) noexcept
{
	assert(ibo);
	assert(_inputLayoutDesc.getIndexType() != GraphicsIndexType::GraphicsIndexTypeNone);

	if (_ibo != ibo)
	{
		glVertexArrayElementBuffer(_vao, ibo->getInstanceID());
		_ibo = ibo;
	}	
}

void
OGLInputLayout::setDevice(GraphicsDevicePtr device) noexcept
{
	_device = device;
}

GraphicsDevicePtr
OGLInputLayout::getDevice() noexcept
{
	return _device.lock();
}

_NAME_END