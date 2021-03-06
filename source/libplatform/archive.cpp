// +----------------------------------------------------------------------
// | Project : ray.
// | All rights reserved.
// +----------------------------------------------------------------------
// | Copyright (c) 2013-2017.
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
#include <ray/archive.h>

_NAME_BEGIN

archive::archive() noexcept
{
}

archive::~archive() noexcept
{
}

archivebuf*
archive::rdbuf() const noexcept
{
	return _strbuf;
}

void
archive::set_rdbuf(archivebuf* buf) noexcept
{
	_strbuf = buf;
}

void
archive::_init(archivebuf* _buf, ios_base::openmode mode) noexcept
{
	this->set_rdbuf(_buf);
	_mode = mode;
	ios_base::_init();
}

void
archive::setOpenMode(ios_base::openmode mode) noexcept
{
	_mode = mode;
}

ios_base::openmode
archive::getOpenMode() const noexcept
{
	return _mode;
}

std::size_t
archive::size() const noexcept
{
	return this->rdbuf()->size();
}

const char*
archive::type_name() const noexcept
{
	return this->rdbuf()->type_name();
}

const char*
archive::type_name(type_t type) const noexcept
{
	return this->rdbuf()->type_name(type);
}

const archive::type_t
archive::type() const noexcept
{
	return this->rdbuf()->type();
}

bool
archive::is_null() const noexcept
{
	return this->rdbuf()->is_null();
}

bool
archive::is_boolean() const noexcept
{
	return this->rdbuf()->is_boolean();
}

bool
archive::is_integral() const noexcept
{
	return this->rdbuf()->is_integral();
}

bool
archive::is_float() const noexcept
{
	return this->rdbuf()->is_float();
}

bool
archive::is_string() const noexcept
{
	return this->rdbuf()->is_string();
}

bool
archive::is_numeric() const noexcept
{
	return this->rdbuf()->is_numeric();
}

bool
archive::is_array() const noexcept
{
	return this->rdbuf()->is_array();
}

bool
archive::is_object() const noexcept
{
	return this->rdbuf()->is_object();
}

_NAME_END