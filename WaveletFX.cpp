/*
 * DirtyLFO.cpp
 *
 *  Created on: 2 Dec 2020
 *      Author: julianporter
 */



#include "WaveletFX.hpp"
#include <cstring>

namespace meromorph { namespace wavelet {




#define NLAYERS 4
#define BLOCK (1<<NLAYERS)
#define RING 5

#define EPSILON 1.0e-6
#define THRESHOLD_MAX 1.0f

const int64 WaveletChannel::BUFFER_SIZE = 64;

void append(char *str,const char *root,const char *ext) {
	strcpy(str,root);
	strcat(str,ext);
}

WaveletChannel::WaveletChannel(const char *code) :
		wavelet(NLAYERS), buffer(BUFFER_SIZE), outs(BUFFER_SIZE), ring(RING) {
	char inP[80];
	append(inP,"/audio_inputs/audioIn",code);
	trace(inP);
	aIn = JBox_GetMotherboardObjectRef(inP);
	char outP[80];
	append(outP,"/audio_outputs/audioOut",code);
	trace(outP);
	aOut = JBox_GetMotherboardObjectRef(outP);
}

uint32 WaveletChannel::readAudio() {
	auto ref = JBox_LoadMOMPropertyByTag(aIn, kJBox_AudioInputBuffer);
	auto length = std::min<int64>(JBox_GetDSPBufferInfo(ref).fSampleCount,BUFFER_SIZE);
	if(length>0) { JBox_GetDSPBufferData(ref, 0, length, buffer.data()); }
	return static_cast<int32>(length);
}
void WaveletChannel::writeAudio() {
	auto ref = JBox_LoadMOMPropertyByTag(aOut, kJBox_AudioOutputBuffer);
	if(!buffer.empty()) JBox_SetDSPBufferData(ref, 0, buffer.size(), buffer.data());
}


void WaveletChannel::bypass() {
	if(readAudio()) writeAudio();
}





void WaveletChannel::process(const Mode alg) {

	if(readAudio()) {
	for(auto offset = 0;offset < BUFFER_SIZE; offset+=BLOCK) {
		auto start = buffer.data()+offset;
		wavelet.analyse(start);
		ring[ringOffset]=wavelet.absMaximum();
		ringOffset=(ringOffset+1)%RING;
		auto ringMax = *std::max_element(ring.begin(),ring.begin()+RING);
		switch(alg) {
		case Mode::Threshold:
			wavelet.threshold(float32(ringMax+EPSILON));
			break;
		case Mode::Bypass:
			break;
		case Mode::Scale:
			wavelet.scale();
			break;
		}
		wavelet.synthesise(start);
	}
	writeAudio();
	}
}

void WaveletChannel::reset() {
	ring.assign(RING,0);
	ringOffset=0;
	//for(auto i=0;i<RING;i++) wavelet.setThreshold(i,0);
	wavelet.reset();
}

WaveletFX::WaveletFX() : left("L"), right("R") {}


inline float32 toFloat(const TJBox_Value diff) {
	return static_cast<float32>(JBox_GetNumber(diff));
}
inline bool toBool(const TJBox_Value diff) {
	return static_cast<float32>(JBox_GetNumber(diff))>0;
}
inline int32 toInt(const TJBox_Value diff) {
	return static_cast<int32>(static_cast<float32>(JBox_GetNumber(diff)));
}


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
			left.process(alg);
			right.process(alg);
			break;
		}
}

}}
