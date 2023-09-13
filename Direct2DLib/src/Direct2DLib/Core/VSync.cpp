#include "Direct2DLibpch.h"
#include "VSync.h"

namespace D2DLib
{

	void VSync::SetVSync(bool vsync)
	{
		m_VSync = vsync;
	}

	void VSync::SyncFrame()
	{
		if (m_VSync)
		{
			// m_SwapChain->Present(1, 0);
		}
	}

}
