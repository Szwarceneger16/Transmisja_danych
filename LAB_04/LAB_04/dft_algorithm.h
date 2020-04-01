#include <cmath>
#include <complex>
#include <time.h>
#include <iomanip>

namespace dft
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

	std::vector<double> idft(std::vector<std::complex<double>> tab)
	{
		int N = tab.size();
		std::vector<double> new_tab;
		new_tab.resize(N);
		std::vector<double>::iterator it_real = new_tab.begin();
		std::vector<std::complex<double>>::iterator it_complex = tab.begin();
		std::complex<double> temp(0, 0);

		for (int k = 0; k < N; k++)
		{
			for (int n = 0; n < N; n++)
			{
				temp += *it_complex * std::polar(1.0, (n * k * (2 * M_PI) / double(N)));
				it_complex++;
			}
			*it_real = (1.0 / double(N)) * temp.real();
			temp = (0, 0);
			it_complex = tab.begin();
			it_real++;
		}

		return new_tab;
	}

	/*std::vector<std::complex<double>> fft(std::vector<double> tab)
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
	}*/

	std::vector<double> load_file_real(std::string path)
	{
		std::fstream load_file;
		std::vector<double> new_tab;

		load_file.open(path, std::ios::in);
		double actual1 = 0.0, actual2 = 0.0;

		while (!load_file.eof())
		{
			load_file >> actual1 >> actual2;
			new_tab.push_back(actual2);
		}
		load_file.close();

		if (new_tab.size() == 0)
		{
			new_tab.resize(1);
			return new_tab;
		}
		else
			return new_tab;
	}

	std::vector<std::complex<double>> load_file_complex(std::string path)
	{
		std::fstream load_file;
		std::vector<std::complex<double>> new_tab;

		load_file.open(path, std::ios::in);
		double actual1 = 0.0;
		std::complex<double> actual2 = 0.0;

		while (!load_file.eof())
		{
			load_file >> actual1 >> actual2;
			new_tab.push_back(actual2);
		}
		load_file.close();

		if (new_tab.size() == 0)
		{
			new_tab.resize(1);
			return new_tab;
		}
		else
			return new_tab;
	}

	std::string save_file_spectrum(std::string path, std::vector<std::complex<double>> input_tab, double Ts)
	{
		std::fstream save_file;
		std::vector<std::complex<double>>::iterator it1 = input_tab.begin();
		save_file.open(path, std::ios::out | std::ios::trunc);

		int N = input_tab.size();
		const double xx = 1.0/Ts;
		for (size_t k = 0; k < N; k++)
		{
			save_file << ((xx*k)/double(N)) << " " << 10* log10(abs(*it1)) << std::endl;
			it1++;

		}

		save_file.close();
		return path;
	}

	std::string save_file_real(std::string path, std::vector<double> input_tab, double Ts)
	{
		std::fstream save_file;
		std::vector<double>::iterator it1 = input_tab.begin();
		save_file.open(path, std::ios::out | std::ios::trunc);
		double x = 0.0;

		int N = input_tab.size();
		for (size_t k = 0; k < N; k++)
		{
			x += Ts;
			save_file << x << " " << *it1 << std::endl;
			it1++;
		}

		save_file.close();
		return path;
	}

	std::string save_file_complex(std::string path, std::vector<std::complex<double>> input_tab, double Ts)
	{
		std::fstream save_file;
		std::vector<std::complex<double>>::iterator it1 = input_tab.begin();
		save_file.open(path, std::ios::out | std::ios::trunc);
		double x = 0.0;

		int N = input_tab.size();
		for (size_t k = 0; k < N; k++)
		{
			x += Ts;
			save_file << x << " " << *it1 << std::endl;
			it1++;
		}

		save_file.close();
		return path;
	}
}

