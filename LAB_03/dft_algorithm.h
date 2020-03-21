#include <cmath>
#include <complex>
#include <time.h>
#include <iomanip>

namespace algo
{
	constexpr std::complex<double> M_I(0.0, 1.0);

	std::vector<std::complex<double>> dft(std::vector<double> tab)
	{
		int N = tab.size();
		std::vector<std::complex<double>> new_tab;
		new_tab.resize(N);
		std::vector<std::complex<double>>::iterator it1 = new_tab.begin();

		for (int k = 0; k < N; k++)
		{
			for (int n = 0; n < N; n++)
			{
				*it1 += tab[n] * exp((-2 * M_PI * M_I * double(k) * double(n)) / double(N));
			}
			it1++;
		}
		return new_tab;
	}

	std::vector<std::complex<double>> fft(std::vector<double> tab)
	{
		int N = tab.size();
		if (N == 0) return std::vector<std::complex<double>>(0);
		if (N == 1) return std::vector<std::complex<double>>(tab.at(0));

		std::vector<double> new_tab_even(N/2, 0);
		std::vector<double> new_tab_odd(N/2, 0);
		for (int i = 0; i < (N / 2); i++)
		{
			new_tab_even.at(i) = tab.at(2 * i);
			new_tab_odd.at(i) = tab.at(2 * i + 1);
		}
		std::vector<std::complex<double>> ret_even = fft(new_tab_even);
		std::vector<std::complex<double>> ret_odd = fft(new_tab_odd);

		std::vector<std::complex<double>> new_tab;
		new_tab.resize(N);
		std::vector<std::complex<double>>::iterator it1 = new_tab.begin();
		std::vector<std::complex<double>>::iterator it2 = new_tab.begin();
		int pol = N / 2;
		std::next(it2, pol);
		for (int k = 0; k < pol; k++)
		{
			*it1 = ret_even.at(k) + (ret_odd.at(k) * exp((-2 * M_PI * M_I * (double)k) / double(N)));
			*it2 = ret_even.at(k) - (ret_odd.at(k) * exp((-2 * M_PI * M_I * (double)k) / double(N)));
			it1++;
			it2++;
		}

		return new_tab;
	}

}

