#pragma once		  

#define _USE_MATH_DEFINES
#include <complex>
#include <vector>

template <typename T>
using cvec = std::vector<std::complex<T>>;

template<typename T> 
void FFT(cvec<T>& data)
{
	int n = data.size();

	if(n <= 1)
		return;

	//if n is not power of 2 (can only occur at first iteration)
	//no need to check for the 0 case, n is already larger than 1
	if(n & (n - 1) != 0)
	{
		n = pow(2, ceil(log2(n))); //set new size to next n that is power of 2

		for(int i = data.size(); n; i++)
			data[i] = std::complex<T>(); //fill with 0s
	}

	int n2 = n / 2;

	cvec<T> evenData = cvec<T>(n2);
	cvec<T> oddData = cvec<T>(n2);

	for(int i = 0; i < n2; i++)
	{
		evenData[i] = data[2 * i];
		oddData[i] = data[2 * i + 1];
	}

	FFT<T>(evenData);
	FFT<T>(oddData);

	for(int i = 0; i < n2; i++)
	{
		std::complex<T> t = std::polar(1.0, -2 * M_PI * i / n) * oddData[i];
		data[i] = evenData[i] + t;
		data[i + n2] = evenData[i] - t;
	}
}