#pragma once

#include "base.hpp"
#include "Channel.hpp"

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
