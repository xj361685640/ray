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
#include "imagtga.h"
#include <ray/dccmn.h>

_NAME_BEGIN

using namespace image;

#define TGA_TYPE_PALETTE 1
#define TGA_TYPE_RGB 2
#define TGA_TYPE_GRAY 3
#define TGA_TYPE_PALETTE_RLE  9
#define TGA_TYPE_RGB_RLE 10
#define TGA_TYPE_GRAY_RLE 11

#define TGA_BPP_8 8
#define TGA_BPP_16 16
#define TGA_BPP_24 24
#define TGA_BPP_32 32

#define TGA_ATTRIB_ALPHA 8
#pragma pack(push)
#pragma pack(1)

struct TGAHeader
{
	std::uint8_t  id_length;
	std::uint8_t  colormap_type;
	std::uint8_t  image_type;
	std::uint16_t colormap_index;
	std::uint16_t colormap_length;
	std::uint8_t  colormap_size;
	std::uint16_t x_origin;
	std::uint16_t y_origin;
	std::uint16_t width;
	std::uint16_t height;
	std::uint8_t  pixel_size;
	std::uint8_t  attributes;
};

#pragma pack(pop)

TGAHandler::TGAHandler() noexcept
{
}

TGAHandler::~TGAHandler() noexcept
{
}

bool
TGAHandler::doCanRead(StreamReader& stream) const noexcept
{
	TGAHeader hdr;

	if (!stream.read((char*)&hdr, sizeof(hdr)))
		return false;

	if (hdr.image_type != 0 &&
		hdr.image_type != 2 &&
		hdr.image_type != 3 &&
		hdr.image_type != 10)
	{
		return false;
	}

	if (hdr.colormap_type != 0)
		return false;

	if (hdr.id_length != 0)
		return false;

	if (hdr.pixel_size != 32 &&
		hdr.pixel_size != 24 &&
		hdr.pixel_size != 16)
	{
		return false;
	}

	return true;
}

bool
TGAHandler::doCanRead(const char* type_name) const noexcept
{
	return std::strncmp(type_name, "tga", 3) == 0;
}

bool
TGAHandler::doLoad(StreamReader& stream, Image& image) noexcept
{
	TGAHeader hdr;
	if (!stream.read((char*)&hdr, sizeof(hdr))) return false;

	std::uint32_t columns = hdr.width;
	std::uint32_t rows = hdr.height;
	std::uint32_t nums = columns * rows;
	std::uint32_t length = nums * hdr.pixel_size / 8;

	if (hdr.id_length != 0)
		stream.seekg(hdr.id_length, ios_base::cur);

	switch (hdr.image_type)
	{
	case TGA_TYPE_PALETTE:
		return false;
	case TGA_TYPE_RGB:
	{
		image::format_t format = image::format_t::Undefined;
		if (hdr.pixel_size == TGA_BPP_8)
			format = image::format_t::R8SRGB;
		else if (hdr.pixel_size == TGA_BPP_16)
			format = image::format_t::R8G8SRGB;
		else if (hdr.pixel_size == TGA_BPP_24)
			format = image::format_t::B8G8R8SRGB;
		else if (hdr.pixel_size == TGA_BPP_32)
			format = image::format_t::B8G8R8A8SRGB;
		else
			return false;

		if (!image.create(columns, rows, format))
			return false;

		if (!stream.read((char*)image.data(), length))
			return false;
	}
	break;
	case TGA_TYPE_GRAY:
	{
		if (!image.create(columns, rows, image::format_t::R8SRGB))
			return false;

		if (!stream.read((char*)image.data(), length))
			return false;
	}
	break;
	case TGA_TYPE_RGB_RLE:
	{
		std::vector<std::uint8_t> buffers(stream.size() - sizeof(TGAHeader));
		std::uint8_t* buf = (std::uint8_t*)buffers.data();

		if (!stream.read((char*)buf, buffers.size()))
			return false;

		switch (hdr.pixel_size)
		{
		case TGA_BPP_16:
		{
			if (!image.create(columns, rows, image::format_t::R8G8SRGB))
				return false;

			std::uint8_t* data = (std::uint8_t*)image.data();
			std::uint8_t* end = (std::uint8_t*)(image.data() + image.size());

			while (data < end)
			{
				std::uint8_t packe = *buf++;
				if (packe & 0x80)
				{
					std::uint8_t length = (std::uint8_t)(1 + (packe & 0x7f));

					for (std::uint8_t i = 0; i < length; i++, data += 2)
					{
						data[0] = buf[0];
						data[1] = buf[1];
					}

					buf += 2;
				}
				else
				{
					std::uint8_t length = ++packe;

					for (std::uint8_t i = 0; i < length; i++, data += 2, buf += 2)
					{
						data[0] = buf[0];
						data[1] = buf[1];
						data[2] = buf[2];
					}
				}
			}
		}
		break;
		case TGA_BPP_24:
		{
			if (!image.create(columns, rows, image::format_t::B8G8R8SRGB))
				return false;

			std::uint8_t* data = (std::uint8_t*)image.data();
			std::uint8_t* end = (std::uint8_t*)(image.data() + image.size());

			while (data < end)
			{
				std::uint8_t packe = *buf++;
				if (packe & 0x80)
				{
					std::uint8_t length = (std::uint8_t)(1 + (packe & 0x7f));

					for (std::uint8_t i = 0; i < length; i++, data += 3)
					{
						data[0] = buf[0];
						data[1] = buf[1];
						data[2] = buf[2];
					}

					buf += 3;
				}
				else
				{
					std::uint8_t length = ++packe;

					for (std::uint8_t i = 0; i < length; i++, data += 3, buf += 3)
					{
						data[0] = buf[0];
						data[1] = buf[1];
						data[2] = buf[2];
					}
				}
			}
		}
		break;
		case TGA_BPP_32:
		{
			if (!image.create(columns, rows, image::format_t::B8G8R8A8SRGB))
				return false;

			std::uint32_t* data = (std::uint32_t*)image.data();
			std::uint32_t* end = (std::uint32_t*)(image.data() + image.size());

			while (data < end)
			{
				std::uint8_t packe = *buf++;
				if (packe & 0x80)
				{
					std::uint8_t length = (std::uint8_t)(1 + (packe & 0x7f));

					for (std::uint8_t i = 0; i < length; i++)
						*data++ = *(std::uint32_t*)buf;

					buf += 4;
				}
				else
				{
					std::uint8_t length = ++packe;
					for (std::uint8_t i = 0; i < length; i++)
						*data++ = *((std::uint32_t*&)buf)++;
				}
			}
		}
		break;
		default:
			return false;
		}
	}
	break;
	case TGA_TYPE_GRAY_RLE:
	{
		std::vector<std::uint8_t> buffers(stream.size() - sizeof(TGAHeader));
		std::uint8_t* buf = (std::uint8_t*)buffers.data();

		if (!stream.read((char*)buf, buffers.size()))
			return false;

		if (!image.create(columns, rows, image::format_t::R8SRGB))
			return false;

		std::uint8_t* data = (std::uint8_t*)image.data();
		std::uint8_t* end = (std::uint8_t*)(image.data() + image.size());

		while (data < end)
		{
			std::uint8_t packe = *buf++;
			if (packe & 0x80)
			{
				std::uint8_t length = (std::uint8_t)(1 + (packe & 0x7f));

				for (std::uint8_t i = 0; i < length; i++)
					*data++ = *(std::uint32_t*)buf;

				buf++;
			}
			else
			{
				std::uint8_t length = ++packe;
				for (std::uint8_t i = 0; i < length; i++)
					*data++ = *buf++;
			}
		}
	}
	break;
	default:
		return false;
	}

	if (hdr.y_origin == 0)
	{
		if (hdr.pixel_size == 24)
		{
			std::size_t half = image.height() >> 1;
			for (std::size_t i = 0; i < half; i++)
			{
				RGB* dest = (RGB*)image.data() + image.width() * (image.height() - i - 1);
				RGB* src = (RGB*)image.data() + image.width() * i;
				for (std::uint32_t j = 0; j < image.width(); j++)
				{
					std::swap(*dest, *src);
					dest++;
					src++;
				}
			}
		}
		else if (hdr.pixel_size == 32)
		{
			std::size_t half = image.height() >> 1;
			for (std::size_t i = 0; i < half; i++)
			{
				RGBA* dest = (RGBA*)image.data() + image.width() * (image.height() - i - 1);
				RGBA* src = (RGBA*)image.data() + image.width() * i;
				for (std::uint32_t j = 0; j < image.width(); j++)
				{
					std::swap(*dest, *src);
					dest++;
					src++;
				}
			}
		}
	}

	return true;
}

bool
TGAHandler::doSave(StreamWrite& stream, const Image& image) noexcept
{
	auto channel = image.channel();
	auto type_size = image.type_size();

	std::size_t destLength = 0;
	std::uint8_t pixelSize = type_size * channel * 8;

	if (pixelSize != TGA_BPP_8 && pixelSize != TGA_BPP_16 && pixelSize != TGA_BPP_24 && pixelSize != TGA_BPP_32)
		return false;

	bool isGreyscale = pixelSize == TGA_BPP_8;
	bool hasAlpha = pixelSize == TGA_BPP_32 ? true : false;

	TGAHeader header;
	header.id_length = 0;
	header.colormap_type = 0;
	header.image_type = isGreyscale ? TGA_TYPE_GRAY : TGA_TYPE_RGB;
	header.colormap_index = 0;
	header.colormap_length = 0;
	header.colormap_size = 0;
	header.x_origin = 0;
	header.y_origin = 0;
	header.width = image.width();
	header.height = image.height();
	header.pixel_size = pixelSize;
	header.attributes = hasAlpha ? TGA_ATTRIB_ALPHA : 0;

	stream.write((char*)&header, sizeof(header));
	stream.write((char*)image.data(), image.size());

	return true;
}

_NAME_END