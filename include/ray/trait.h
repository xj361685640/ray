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
#ifndef _H_TRAIT_H_
#define _H_TRAIT_H_

#include <ray/platform.h>

#include <string>

_NAME_BEGIN

namespace trait
{
    template<typename T>
    struct functor {};

    template<typename Result, typename Class>
    struct functor<Result(Class::*)(void)>
    {
        typedef Result result_type;
        typedef Class class_type;
        typedef void arg_type;
    };

    template<typename Result, typename Class, class Args>
    struct functor<Result(Class::*)(Args)>
    {
        typedef Result result_type;
        typedef Class class_type;
        typedef Args arg_type;
    };

    template<typename T>
    struct _typeaddition
    {
        typedef T                value_type;
        typedef T*               pointer;
        typedef T&               reference;
        typedef const T          const_type;
        typedef const T*         const_pointer;
        typedef const T&         const_reference;
    };

    template<>
    struct _typeaddition<void>
    {
        typedef void             value_type;
        typedef void*            pointer;
        typedef const void*      const_pointer;
    };

    template<typename T>
    struct _typeaddition<T*>
    {
        typedef T                value_type;
        typedef T*               pointer;
        typedef T&               reference;
        typedef const T*         const_type;
        typedef const T*         const_pointer;
        typedef const T&         const_reference;
    };

    template<typename T>
    struct _typeaddition<T&>
    {
        typedef T                value_type;
        typedef T*               pointer;
        typedef T&               reference;
        typedef const T&         const_type;
        typedef const T*         const_pointer;
        typedef const T&         const_reference;
    };

    template<typename T>
    struct _typeaddition<const T*>
    {
        typedef T                value_type;
        typedef T*               pointer;
        typedef T&               reference;
        typedef const T*         const_type;
        typedef const T*         const_pointer;
        typedef const T&         const_reference;
    };

    template<typename _Elem, typename _Int_type>
    struct _Char_traits
    {
        typedef _Elem            char_type;
        typedef _Elem*           pointer;
        typedef _Elem&           reference;
        typedef const _Elem      const_type;
        typedef const _Elem*     const_pointer;
        typedef const _Elem&     const_reference;
        typedef _Int_type        int_type;

        static int compare(const char_type* str1, const char_type* str2, std::size_t cnt) noexcept
        {
            for (; 0 < cnt; --cnt, ++str1, ++str2)
            {
                if (!eq(*str1, *str2))
                    return (lt(*str1, *str2) ? -1 : 1);
            }

            return (0);
        }

        static bool eq(const char_type& lhs, const char_type& rhs) noexcept
        {
            return (lhs == rhs);
        }

        static bool lt(const char_type& lhs, const char_type& rhs) noexcept
        {
            return (lhs < rhs);
        }
    };

    template<typename T>
    struct erase_const
    {
        typedef T value_type;
    };

    template<typename T>
    struct erase_const<const T>
    {
        typedef T value_type;
    };

    template<typename T>
    struct erase_const<const T*>
    {
        typedef T* value_type;
    };

    template<typename T>
    struct erase_const<const T&>
    {
        typedef T& value_type;
    };

    template<typename _Ty>
    struct char_traits;

    template<>
    struct char_traits<char> : public _Char_traits<char, long>
    {
    public:
        static const std::string towcs(const wchar_t* str) noexcept
        {
            std::string _format;
            _format.resize(wcslen(str));
            wcstombs((char*)_format.c_str(), str, _format.size());
            return _format;
        }

        static const_pointer towcs(const char* str) noexcept
            {
 return (str);
}

static pointer get_pointer(pointer name) noexcept
    {
return name;
}

static const_pointer get_pointer(const_pointer name) noexcept
    {
return name;
}

static void set_pointer(const_pointer*& str, const_pointer* value) noexcept
    {
str = value;
}

static bool empty(const_pointer* str)
    {
return nullptr == str;
}
    };

    template<>
    class char_traits<wchar_t> : public _Char_traits<wchar_t, long>
    {
    public:
        static const std::wstring towcs(const char* str) noexcept
        {
            std::wstring _format;
            _format.resize(strlen(str));
            mbstowcs((wchar_t*)_format.c_str(), str, _format.size());
            return _format;
        }

        static const_pointer towcs(const wchar_t* str) noexcept
            {
 return str;
}

static pointer get_pointer(pointer str) noexcept
    {
return str;
}

static const_pointer get_pointer(const_pointer str) noexcept
    {
return str;
}

static void set_pointer(const_pointer*& str, const_pointer* value) noexcept
    {
str = value;
}

static bool empty(const_pointer* str)
    {
return nullptr == str;
}
    };

    template<>
    class char_traits<std::string> : public _Char_traits<char, long>
    {
    public:
        static const_pointer get_pointer(const std::string& name) noexcept
            {
 return name.c_str();
}

static void set_pointer(std::string& str, const_pointer value) noexcept
{
    if (nullptr == value)
        str.clear();
    else
        str = value;
}

static void set_poineter(std::string& s1, const std::string& s2) noexcept
    {
s1 = s2;
}

static bool empty(const std::string& str)
    {
return str.empty();
}
    };

    template<>
    class char_traits<std::wstring> : public _Char_traits<wchar_t, long>
    {
    public:
        static const_pointer get_pointer(const std::wstring& str) noexcept
            {
 return str.c_str();
}

static void set_pointer(std::wstring& str, const_pointer value) noexcept
{
    if (nullptr == value)
        str.clear();
    else
        str = value;
}

static void set_poineter(std::wstring& s1, const std::wstring& s2) noexcept
    {
s1 = s2;
}

static bool empty(const std::wstring& str)
    {
return str.empty();
}
    };
}

_NAME_END

#endif //_H_TRAIT_H_