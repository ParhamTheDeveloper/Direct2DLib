/*
MIT License

Copyright (c) 2023 D2DLib

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

For more information about the author, please visit:
[ParhamTheDeveloper](https://github.com/ParhamTheDeveloper)
*/

#pragma once

// Entry header file

#include "Core/Base.h"
#include "Core/Application.h"
#include "Renderer/Renderer.h"
#include "Renderer/ResourceManager.h"
#include "Transitions/InterpolatorTransition.h"
#include "Transitions/ColorTransition.h"
#include "Transitions/TransitionManager.h"
#include "Direct2DLib/Core/StringFormat.h"
#include "Renderer/Light.h"

// Enabling the C4251 warning for STD dll-interfaces
// We reset it when the user includes the client header file (This header file)
#ifdef D2DLIB_EXPORTS
	#ifndef D2DLIB_CLIENT_IMPORTS
		#pragma warning(default: 4251)
	#endif
#endif