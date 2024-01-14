#pragma once

#include "Amber/Core/Core.h"
#include <string>

namespace Amber
{

	class Texture
	{
	public:
		
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void Bind(uint32_t slot = 0) const = 0;

	};

	class Texture2D : public Texture
	{
	public:
		Texture2D(const std::string& path); 
		Texture2D() {}
		static Ref<Texture2D> Create(const std::string& path);

	};


}