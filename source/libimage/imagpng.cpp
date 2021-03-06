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
#include "imagpng.h"

#include <png.h>

_NAME_BEGIN

namespace image
{

struct PNGInfoStruct
{
	jmp_buf jmpbuf;
	bool verbose;

	union
	{
		StreamReader* in;
	} stream;
};

void PNGAPI png_err(png_structp png_ptr, png_const_charp message)
{
	PNGInfoStruct* info = (PNGInfoStruct*)png_get_io_ptr(png_ptr);
	longjmp(info->jmpbuf, 1);
}

void PNGAPI png_warn(png_structp png_ptr, png_const_charp message)
{
	PNGInfoStruct* info = (PNGInfoStruct*)png_get_io_ptr(png_ptr);
	longjmp(info->jmpbuf, 1);
}

void PNGAPI PNG_stream_reader(png_structp png_ptr, png_bytep data, png_size_t length)
{
	PNGInfoStruct* info = (PNGInfoStruct*)png_get_io_ptr(png_ptr);
	info->stream.in->read((char*)data, (std::streamsize)length);
}

PNGHandler::PNGHandler() noexcept
{
}

PNGHandler::~PNGHandler() noexcept
{
}

bool
PNGHandler::doCanRead(StreamReader& stream) const noexcept
{
	static constexpr std::uint8_t magic[] = { 0x89, 'P', 'N', 'G' };

	std::uint8_t hdr[sizeof(magic)];

	if (stream.read((char*)hdr, sizeof(hdr)))
		return std::memcmp(hdr, magic, sizeof(magic)) == 0;

	return false;
}

bool
PNGHandler::doCanRead(const char* type_name) const noexcept
{
	return std::strncmp(type_name, "png", 3) == 0;
}

bool
PNGHandler::doLoad(StreamReader& stream, Image& image) noexcept
{
	PNGInfoStruct info;
	info.stream.in = &stream;

	if (::setjmp(info.jmpbuf))
		return false;

	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, &png_err, &png_warn);
	if (!png_ptr)
		return false;

	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr)
	{
		::png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
		return false;
	}

	::png_set_strip_16(png_ptr);
	::png_set_packing(png_ptr);
	::png_set_read_fn(png_ptr, &info, &PNG_stream_reader);
	::png_set_filler(png_ptr, 0xff, PNG_FILLER_AFTER);
	::png_set_benign_errors(png_ptr, 1);
	::png_read_info(png_ptr, info_ptr);

	png_uint_32 width, height;
	int bit_depth, color_type, interlace_type;

	if (!::png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_type, 0, 0))
	{
		::png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
		return false;
	}

	if (color_type == PNG_COLOR_TYPE_PALETTE)
		::png_set_expand(png_ptr);

	if (bit_depth < 8)
		::png_set_expand(png_ptr);

	if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
		::png_set_expand(png_ptr);

	int intent;
	if (png_get_sRGB(png_ptr, info_ptr, &intent))
		png_set_sRGB(png_ptr, info_ptr, intent);

	if (color_type & PNG_COLOR_TYPE_RGBA ||
		color_type & PNG_COLOR_TYPE_RGB)
	{
		png_uint_32 pixelSize;
		image::format_t format;
		if (color_type & PNG_COLOR_TYPE_RGBA)
		{
			format = image::format_t::R8G8B8A8SRGB;
			pixelSize = 4;
		}
		else if (color_type & PNG_COLOR_TYPE_RGB)
		{
			format = image::format_t::R8G8B8SRGB;
			pixelSize = 3;
		}

		if (!image.create(width, height, format))
			return false;

		std::size_t columnLength = width * pixelSize;
		std::uint8_t* pixel = (std::uint8_t*)image.data();

		std::vector<png_bytep> pointers(height, 0);
		for (std::size_t i = 0; i < height; i++)
			pointers[i] = pixel + i * columnLength;

		::png_start_read_image(png_ptr);
		::png_read_image(png_ptr, pointers.data());
		::png_read_end(png_ptr, info_ptr);
	}

	::png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
	return true;
}

bool
PNGHandler::doSave(StreamWrite&, const Image&) noexcept
{
	return false;
}

}

_NAME_END