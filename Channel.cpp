/*
 * Channel2.cpp
 *
 *  Created on: 26 Dec 2020
 *      Author: julianporter
 */

#include "Channel.hpp"

namespace meromorph { namespace wavelet {



const uint32 WaveletChannel::NLAYERS = 4;
const uint32 WaveletChannel::BLOCK = 1<<NLAYERS;
const uint32 WaveletChannel::RING = 1+NLAYERS;

const float32 WaveletChannel::EPSILON = 1.0e-6;
const float32 WaveletChannel::THRESHOLD_MAX = 1.0;

const int64 WaveletChannel::BUFFER_SIZE = 64;

#define AudioInRoot "/audio_inputs/audioIn"
#define AudioOutRoot "/audio_outputs/audioOut"

WaveletChannel::WaveletChannel(const char *code) :
		wavelet(NLAYERS), buffer(BUFFER_SIZE), previous(BLOCK), ring(RING) {
	char inP[80];
	append(inP,AudioInRoot,code);
	trace(inP);
	aIn = JBox_GetMotherboardObjectRef(inP);
	char outP[80];
	append(outP,AudioOutRoot,code);
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

bool WaveletChannel::detectedSilence() {
	auto minmax = std::minmax_element(buffer.begin(),buffer.end());
	auto mi = fabs(*minmax.first);
	auto ma = fabs(*minmax.second);
	auto upper=std::max(mi,ma);
	return upper<kJBox_SilentThreshold;
}


void WaveletChannel::bypass() {
	if(readAudio() && !detectedSilence()) writeAudio();
}

void WaveletChannel::process(const Mode alg) {

	if(readAudio() && !detectedSilence()) {
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

bool WaveletChannel::isConnected() const {
	auto sock = JBox_LoadMOMPropertyByTag(aIn,kJBox_AudioInputConnected);
	if(JBox_GetType(sock)==kJBox_Boolean) return JBox_GetBoolean(sock);
	else return false;
}


}}/* namespace meromorph */
