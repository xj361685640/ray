// +----------------------------------------------------------------------
// | Project : ray.
// | All rights reserved.
// +----------------------------------------------------------------------
// | Copyright (c) 2013-2015.
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
#ifndef _H_MSTREAM_H_
#define _H_MSTREAM_H_

#include <ray/iostream.h>
#include <vector>

_NAME_BEGIN

class EXPORT MemoryBuf : public streambuf
{
public:
    MemoryBuf() noexcept;
    ~MemoryBuf() noexcept;

    bool open(const char* filename, const ios_base::openmode mode) noexcept;
    bool open(const wchar_t* filename, const ios_base::openmode mode) noexcept;

    void close() noexcept;

    streamsize read(char_type* str, std::streamsize cnt) noexcept;
    streamsize write(const char_type* str, std::streamsize cnt) noexcept;

    streamoff seekg(ios_base::off_type pos, ios_base::seekdir dir) noexcept;
    streamoff tellg() noexcept;

    streamsize size() noexcept;
    void resize(streamsize size) noexcept;

    char_type* map() noexcept;
    void unmap() noexcept;
    bool isMapping() const noexcept;

    bool is_open() const noexcept;

    int flush() noexcept;

    void copy(streambuf& other) noexcept;

private:

    bool _isMappinged;

    std::size_t _next;

    std::vector<char_type> _data;
};

class EXPORT MemoryStream : public iostream
{
public:
    MemoryStream() noexcept;
    ~MemoryStream() noexcept;

    void resize(streamsize size) noexcept;

    char_type* map() noexcept;
    void unmap() noexcept;
    bool isMapping() const noexcept;

protected:

    MemoryBuf _buf;
};

_NAME_END

#endif