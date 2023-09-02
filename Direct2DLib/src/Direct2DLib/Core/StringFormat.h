#pragma once

#include "Base.h"

// Disabling the reserevd suffix warning
#pragma warning(disable: 4455)

namespace D2DLib
{

	class D2DLIB_API StringFormat
	{
	public:
		StringFormat()
			: m_View(L"")
		{
		}

		StringFormat(const String& view)
			: m_View(view)
		{
		}

		void SetView(const String& view)
		{
			m_View = view;
		}

		const String& GetView() const { return m_View; }

		template<typename ...Args>
		StringFormat& Join(Args&&... args)
		{
			m_Format = std::vformat(m_View, std::make_wformat_args(std::forward<Args>(args)...));
			return *this;
		}

		template<typename Arg>
		StringFormat& operator+(Arg&& arg)
		{
			return Join(arg);
		}

		template<typename ...Args>
		StringFormat& operator+(Args&&... args)
		{
			return Join(args...);
		}

		template<typename ...Args>
		StringFormat& $(Args&&... args)
		{
			return Join(args...);
		}

		template<typename ...Args>
		static const StringFormat $(StringFormat format, Args&&... args)
		{
			format.Join(args...);
			return format;
		}

		const String& GetFormat() const { return m_Format; }
		operator const String& () const { return m_Format; }
	private:
		String m_View;
		String m_Format;
	};

	inline StringFormat operator""format(const wchar_t* str, UInt64 size)
	{
		StringFormat format(str);
		return format;
	}

	inline StringFormat operator""_format(const wchar_t* str, UInt64 size)
	{
		StringFormat format(str);
		return format;
	}

	inline StringFormat operator""fmt(const wchar_t* str, UInt64 size)
	{
		StringFormat format(str);
		return format;
	}

	inline StringFormat operator""_fmt(const wchar_t* str, UInt64 size)
	{
		StringFormat format(str);
		return format;
	}

	inline OStream& operator<<(OStream& stream, const StringFormat& format)
	{
		stream << format.GetFormat();
		return stream;
	}

	template<typename ...Args>
	inline const StringFormat $(StringFormat format, Args&&... args)
	{
		return StringFormat::$(format, args...);
	}

}

// Enabling the reserevd suffix warning
#pragma warning(default: 4455)