/*
 * Channel.hpp
 *
 *  Created on: 26 Dec 2020
 *      Author: julianporter
 */

#ifndef CHANNEL_HPP_
#define CHANNEL_HPP_

#include "base.hpp"
#include <vector>
#include "Haar.hpp"

namespace meromorph {
namespace wavelet {

template<typename T>
class CircularBuffer {
private:
	T* buffer;
	uint64 readP;
	uint64 writeP;
	uint32 size;

public:
	CircularBuffer(const uint32 n) : readP(0), writeP(0), size(n) {
		buffer = new T[n];
	}
	virtual ~CircularBuffer() {
		if(buffer!=nullptr) delete [] buffer;
	}

	uint64 availableToRead() const {
		if(writeP>readP) return writeP-readP;
		else return 0;
	}

	void reset() {
		readP=0;
		writeP=0;
	}

	void write(const uint32 n,T *data) {
		for(auto i=0;i<n;i++) buffer[(writeP++)%size] = data[i];
	}
	uint32 read(const uint32 n,T*data) {
		auto get = std::min(availableToRead(),(uint64)n);
		for(auto i=0;i<get;i++) data[i] = buffer[(readP++)%size];
		return (uint32) get;
	}
};

class WaveletChannel {
private:
	static const float32 EPSILON;
	static const float32 THRESHOLD_MAX;

	haar::Haar wavelet;

	TJBox_ObjectRef aIn;
	TJBox_ObjectRef aOut;

	std::vector<float32> buffer;
	std::vector<float32> previous;
	std::vector<float32> ring;
	uint32 ringOffset=0;


	uint32 readAudio();
	void writeAudio();
	bool detectedSilence();

public:
	static const int64 BUFFER_SIZE;
	static const uint32 NLAYERS;
	static const uint32 BLOCK;
	static const uint32 RING;
	WaveletChannel(const char *code);

	void process(const Mode algorithm);
	void bypass();
	void reset();
	void set(const uint32 n,const float32 value) { wavelet.setThreshold(n,value); }

	bool isConnected() const;
};

}} /* namespace meromorph */

#endif /* CHANNEL_HPP_ */
