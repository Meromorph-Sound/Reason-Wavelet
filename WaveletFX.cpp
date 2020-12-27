/*
 * DirtyLFO.cpp
 *
 *  Created on: 2 Dec 2020
 *      Author: julianporter
 */



#include "WaveletFX.hpp"
#include <cstring>

namespace meromorph { namespace wavelet {

WaveletFX::WaveletFX() : left("L"), right("R") {}

void WaveletFX::set(const uint32 n,const TJBox_Value value) {
	float32 f=toFloat(value);
	left.set(n,f);
	right.set(n,f);
}

void WaveletFX::processButtons(const TJBox_PropertyDiff iPropertyDiffs[], uint32 iDiffCount) {
	for(auto i=0;i<iDiffCount;i++) {
		auto diff=iPropertyDiffs[i];
		Tag tag = diff.fPropertyTag;
		trace("Processing changed property ^0",tag);
		switch(tag) {

		case kJBox_CustomPropertiesOnOffBypass:
			state = static_cast<State>(toFloat(diff.fCurrentValue));
			break;
		case kJBox_TransportRequestResetAudio:
			trace("Reset request");
			left.reset();
			right.reset();
			break;
		case kJBox_AudioInputConnected:
			connectedL = left.isConnected();
			connectedR = right.isConnected();
			break;
		case Tags::Detail1:
			set(0,diff.fCurrentValue);
			break;
		case Tags::Detail2:
			set(1,diff.fCurrentValue);
			break;
		case Tags::Detail3:
			set(2,diff.fCurrentValue);
			break;
		case Tags::Detail4:
			set(3,diff.fCurrentValue);
			break;
		case Tags::Approximation:
			set(4,diff.fCurrentValue);
			break;
		case Tags::Algorithm:
			alg = toInt(diff.fCurrentValue) > 0 ? Mode::Scale : Mode::Threshold;
			break;
		}
	}
}


void WaveletFX::RenderBatch(const TJBox_PropertyDiff diffs[], TJBox_UInt32 nDiffs) {

	processButtons(diffs,nDiffs);
		switch(state) {
		case State::Off:
			break;
		case State::Bypassed:
			left.bypass();
			right.bypass();
			break;
		case State::On:
			if(connectedL) left.process(alg);
			if(connectedR) right.process(alg);
			break;
		}
}

}}
