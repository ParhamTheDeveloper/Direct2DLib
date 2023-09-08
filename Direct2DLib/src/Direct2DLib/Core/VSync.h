#pragma once

#include "Base.h"

namespace D2DLib
{

	class D2DLIB_API VSync
	{
	public:
		virtual void SetVSync(bool vsync);

		const bool& GetVSync() const { return m_VSync; }
	protected:
		void SyncFrame();
	protected:
		bool m_VSync;
		IDXGISwapChain* m_SwapChain = nullptr;
	};

}