#pragma once

#include "base.hpp"
#include <vector>
#include "Haar.hpp"

namespace meromorph {
namespace wavelet {

enum Tags : Tag {
	Detail1 = 11,
	Detail2 = 12,
	Detail3 = 13,
	Detail4 = 14,
	Approximation = 15,
	Algorithm = 16,
};

enum Mode : unsigned {
		Scale = 2,
		Bypass = 1,
		Threshold = 0
	};

class WaveletChannel {
private:
	haar::Haar wavelet;

	TJBox_ObjectRef aIn;
	TJBox_ObjectRef aOut;

	std::vector<float32> buffer;
	std::vector<float32> outs;
	std::vector<float32> ring;
	uint32 ringOffset=0;

	uint32 readAudio();
	void writeAudio();

public:
	static const TJBox_Int64 BUFFER_SIZE;
	WaveletChannel(const char *code);

	void process(const Mode algorithm);
	void bypass();
	void reset();
	void set(const uint32 n,const float32 value) { wavelet.setThreshold(n,value); }

	bool isConnected() const;
};

class WaveletFX {
private:
	WaveletChannel left;
	WaveletChannel right;

	Mode alg = Mode::Threshold;
	State state = State::On;

	bool connectedL = false;
	bool connectedR = false;

	void set(const uint32 n,const TJBox_Value value);

	void processButtons(const TJBox_PropertyDiff iPropertyDiffs[], uint32 iDiffCount);
public:

	explicit WaveletFX();
//	~CFollower();


    void RenderBatch(const TJBox_PropertyDiff iPropertyDiffs[], TJBox_UInt32 iDiffCount);

};

}}
