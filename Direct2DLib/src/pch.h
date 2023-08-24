#pragma once

// Windows header files

#include <Windows.h>

// Direct2D header files

#include <d2d1_3.h>
#include <d2d1effects_2.h>
#include <dwrite.h>
#include <wincodec.h>

// DirectX header files

#include <d3d11.h>

#pragma comment(lib, "Winmm.lib")
#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "Windowscodecs.lib")

// STD header files

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <map>
#include <deque>
#include <stack>
#include <thread>
#include <future>
#include <utility>
#include <cmath>
#include <cassert>

#define _USE_MATH_DEFINES
#include <math.h>