/*
 * base.hpp
 *
 *  Created on: 2 Dec 2020
 *      Author: julianporter
 */

#ifndef DIRTYLFO_BASE_HPP_
#define DIRTYLFO_BASE_HPP_

#include "Jukebox.h"
#include <type_traits>
#include <cmath>
#include <algorithm>
#include <vector>


namespace meromorph {

using int32 = TJBox_Int32;
using uint32 = TJBox_UInt32;
using int64 = TJBox_Int64;
using uint64 = TJBox_UInt64;
using float64 = TJBox_Float64;
using float32 = TJBox_AudioSample;

using Tag = uint32;
using Channel = uint32;

enum State : int32 {
	Off = 0, On = 1, Bypassed = 2
};

enum Mode : uint32 {
		Scale = 2,
		Bypass = 1,
		Threshold = 0
	};

void trace(const char *tmpl);
void trace(const char *tmpl,const float32 value);
void trace(const char *tmpl,const float32 value1,const float32 value2);

 float32 toFloat(const TJBox_Value diff);
 bool toBool(const TJBox_Value diff);
 int32 toInt(const TJBox_Value diff);

 void append(char *str,const char *root,const char *ext);

}






#endif /* DIRTYLFO_BASE_HPP_ */
