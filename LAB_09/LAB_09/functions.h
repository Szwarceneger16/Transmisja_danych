//#include "dft_algorithm.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <complex>
#include <time.h>
#include <iomanip>
#include <algorithm>

#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstddef>
#include <bitset>

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

	std::vector<std::pair<double, double>> multiply(std::vector<std::pair<double, double>> sygnal, std::vector<double> nosny)
	{
		if ((sygnal.size() != nosny.size())) throw _exception();

		std::vector<std::pair<double, double>>::iterator it = sygnal.begin();
		std::vector<double>::iterator it2 = nosny.begin();
		auto last = sygnal.end();
		int t = 0;
		while (it != last)
		{
			(it->second) = ((*it2) * (it->second));
			it2++;
			it++;
		}
		return sygnal;
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

	std::vector<std::pair<double, double>> load_file_real(std::string path)
	{
		std::fstream load_file;
		std::vector<std::pair<double, double>> new_tab;

		load_file.open(path, std::ios::in);
		double actual1 = 0.0, actual2 = 0.0;

		while (!load_file.eof())
		{
			load_file >> actual1 >> actual2;
			new_tab.push_back(std::pair<double, double>(actual1, actual2));
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

	std::string save_file_spectrum(std::string path, std::vector<std::complex<double>> input_tab, double fm)
	{
		std::fstream save_file;
		std::vector<std::complex<double>>::iterator it1 = input_tab.begin();
		save_file.open(path, std::ios::out | std::ios::trunc);
		std::vector<double> log_tab;
		int N = input_tab.size();

		for (int i = 0; i < N; i++)
		{
			log_tab.push_back(10 * log10(abs(*it1)));
			it1++;
		}

		double log_max = *std::max_element(log_tab.begin(), log_tab.end());
		//const double xx = 1.0/Ts;
		for (size_t k = 0; k < N; k++)
		{
			save_file << ((fm * k) / double(N)) << " " << log_tab[k] - log_max << std::endl;

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

	std::string save_file_real(std::string path, std::vector<std::pair<double, double>> input_tab)
	{
		std::fstream save_file;
		std::vector<std::pair<double, double>>::iterator it1 = input_tab.begin();
		auto last = input_tab.empty() ? input_tab.end() : std::prev(input_tab.end(), 0);

		save_file.open(path, std::ios::out | std::ios::trunc);
		while (it1 != last)
		{
			save_file << it1->first << " " << it1->second << std::endl;
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

namespace matrix {

	std::vector<std::vector<int>> initialize(int const n, int const m)
	{
		std::vector<std::vector<int>> wektor(n, std::vector<int>(m, 0));
		return wektor;
	};

	void print_matrix(std::vector<std::vector<int>> const in)
	{
		for (int i = 0; i < in.size(); i++)
		{
			for (int j = 0; j < in.at(i).size(); j++)
			{
				std::cout << in.at(i).at(j) << "  ";
			}
			std::cout << std::endl;
		}
	};

	std::vector<std::vector<int>> multiply(std::vector<std::vector<int>> A, std::vector<std::vector<int>> B)
	{
		auto wynik = initialize(A.size(), B.at(0).size());
		int temp = 0;

		if (A.at(0).size() != B.size()) throw std::domain_error("Demension matrix error");

		for (int i = 0; i < A.size(); i++)
		{
			for (int j = 0; j < B.at(0).size(); j++)
			{
				for (int k = 0; k < A.at(0).size(); k++)
				{
					temp += A[i][k] * B[k][j];
				}
				wynik.at(i).at(j) = temp;
				temp = 0;
			}
		}
		return wynik;
	};
}

enum Endian
{
	littleEndian = 1,
	bigEndian = 2
};


std::string S2BS(std::string in, Endian sw = littleEndian)
{

	int N = in.size();
	std::string wynik;

	if (sw == littleEndian)
	{
		for (int j = 0; j <= N; j++)
		{
			std::bitset<8> x(in[j]);
			wynik += x.to_string();
		}
	}
	else
	{
		for (int i = N; i >= 0; i++)
		{
			std::bitset<8> x(in[i]);
			wynik += x.to_string();
		}
	}

	return wynik;
};

std::string SB2S(std::string in, Endian sw = littleEndian)
{

	int N = in.size()-1;
	std::string wynik;
	int temp = 0;

	if (sw == littleEndian)
	{
		for (int j = 0; j <= N-6; j+=8)
		{
			for (int i = 0; i < 8; i++)
			{
				temp += (pow(2, 7-i) * (in[j+i]-48));
			}
			wynik.push_back(static_cast<char>(temp));
			temp = 0;
		}
		
	}
	else
	{
		for (int j = 0; j <= N; j += 8)
		{
			for (int i = 0; i < 7 ; i++)
			{
				temp += pow(i, 2) * in[j-i];
			}
			wynik.push_back(temp);
			temp = 0;
		}
		
	}

	return wynik;
};

static class Hamming74_SECDED {
	static std::vector<std::vector<int>> const G_matrix;
	static std::vector<std::vector<int>> const H_matrix;

	static std::vector<int> mod2(std::vector<int> in)
	{
		std::vector<int>  a = {in.at(0) % 2};
		return a;
	}

	static std::string _code(bool d1,bool d2,bool d3,bool d4)
	{
		std::string wyn;
		std::vector<std::vector<int>> const d_matrix = { {d1},{d2},{d3},{d4} };
		auto coded_matrix = matrix::multiply(G_matrix, d_matrix);
		std::transform(coded_matrix.begin(), coded_matrix.end(), coded_matrix.begin(), mod2);
		int parzystosc = 0;
		for (std::vector<std::vector<int>>::iterator it = coded_matrix.begin(); it != coded_matrix.end(); it++)
		{
			parzystosc += it->at(0);
		}
		wyn += std::to_string(parzystosc % 2);
		for (std::vector<std::vector<int>>::iterator it = coded_matrix.begin(); it != coded_matrix.end(); it++)
		{
			wyn += std::to_string(it->at(0));
		}
		return wyn;
	}

	static std::string _decode(bool d1, bool d2, bool d3, bool d4, bool d5, bool d6, bool d7, bool d8)
	{
		std::vector<std::vector<int>> const d_matrix = { {d2},{d3},{d4},{d5},{d6},{d7},{d8} };
		auto decoded_matrix = matrix::multiply(H_matrix, d_matrix);
		std::transform(decoded_matrix.begin(), decoded_matrix.end(), decoded_matrix.begin(), mod2);
		int parzystosc = (d1 + d2 + d3 + d4 + d5 + d6 + d7 + d8) % 2;
		int blad = (decoded_matrix.at(2).at(0)*4) + (decoded_matrix.at(1).at(0) * 2) + decoded_matrix.at(0).at(0);

		if (parzystosc == 0 && blad == 0)
			return std::to_string(d4) + std::to_string(d6) + std::to_string(d7) + std::to_string(d8);
		else if (parzystosc == 1 && blad > 0)
		{
			switch (blad)
			{
			case 1:
				d8 = !d8;
				break;
			case 2:
				d7 = !d7;
				break;
			case 3:
				d6 = !d6;
				break;
			case 4:
				d5 = !d5;
				break;
			case 5:
				d4 = !d4;
				break;
			case 6:
				d3 = !d3;
				break;
			case 7:
				d2 = !d2;
				break;
			default:
				break;
			}
			return std::to_string(d4) + std::to_string(d6) + std::to_string(d7) + std::to_string(d8);
		}
		else
			return "";
	}
public:
	static std::string code(std::string in)
	{
		if (in.size() % 4 != 0) return NULL;
		std::string wynik;
		for (int i = 0; i < in.size(); i+=4)
		{
			auto temp = _code(std::stoi(in.substr(i, 1)), std::stoi(in.substr(i + 1, 1)), std::stoi(in.substr(i + 2, 1)), std::stoi(in.substr(i + 3, 1)));
			wynik.append(temp);
		}
		return wynik;
	}
	static std::string decode(std::string in)
	{

		if (in.size() % 8 != 0) return NULL;
		std::string wynik;
		int wyciete = 0;
		for (int i = 0; i < in.size(); i += 8)
		{
			auto temp = _decode(std::stoi(in.substr(i, 1)), std::stoi(in.substr(i + 1, 1)), std::stoi(in.substr(i + 2, 1)), std::stoi(in.substr(i + 3, 1)), std::stoi(in.substr(i + 4, 1)), std::stoi(in.substr(i + 5, 1)), std::stoi(in.substr(i + 6, 1)), std::stoi(in.substr(i + 7, 1)));
			if (temp != "")
				wynik.append(temp);
			else
				wyciete++;
		}
		if (wyciete > 0) std::cout << "uszkodoznych ramek bylo: " << wyciete << std::endl;
		return wynik;
	}
	static std::string destroy(std::string in,int bit,int ramka = 0)
	{
		if (in.size() % 8 != 0) return NULL;
		if (in[((ramka+1) * 8) - bit ] == '1')
			in[((ramka + 1) * 8) - bit ] = '0';
		else
			in[((ramka + 1) * 8) - bit ] = '1';
		return in;
	}
};

std::vector<std::vector<int>> const Hamming74_SECDED::G_matrix = { {1,1,0,1},{1,0,1,1},{1,0,0,0},{0,1,1,1},{0,1,0,0},{0,0,1,0},{0,0,0,1} };
std::vector<std::vector<int>> const Hamming74_SECDED::H_matrix = { {1,0,1,0,1,0,1},{0,1,1,0,0,1,1},{0,0,0,1,1,1,1} };

namespace demodualtor
{
	std::string TTL(std::vector<std::pair<double, double>> const &input, double Tb = 1.0)
	{
		double Ts = input.at(1).first - input.at(0).first;
		std::string wynik;
		std::vector<std::pair<double, double>>::const_iterator it = input.begin();

		while((std::distance(it, input.end()) >= floor(Tb / Ts)))
		{
			if (it->second < 0.5) wynik.append("0");
			else wynik.append("1");

			std::advance(it, floor(Tb / Ts));
		}

		return wynik;
	}

	std::string Manchester(std::vector<std::pair<double, double>> const& input, double Tb = 1.0)
	{
		double Ts = input.at(1).first - input.at(0).first;
		std::string wynik;
		std::vector<std::pair<double, double>>::const_iterator it = input.begin(),it2 = input.begin();
		std::advance(it, floor((Tb / Ts) * 0.4));
		std::advance(it2, floor((Tb / Ts) * 0.6));

		while ((std::distance(it2, input.end()) >= floor(Tb / Ts)))
		{
			if (it->second < 0.0 && it2->second > 0.0) wynik.append("0");
			else if (it->second > 0.0 && it2->second < 0.0) wynik.append("1");

			std::advance(it, floor(Tb / Ts));
			std::advance(it2, floor(Tb / Ts));
		}
		if (it->second < 0.0 && it2->second > 0.0) wynik.append("0");
		else if (it->second > 0.0 && it2->second < 0.0) wynik.append("1");
		return wynik;
	}

	std::string NRZI(std::vector<std::pair<double, double>> const& input, double Tb = 1.0)
	{
		double Ts = input.at(1).first - input.at(0).first;
		std::string wynik;
		std::vector<std::pair<double, double>>::const_iterator it = input.begin(), it2 = input.begin();
		std::advance(it2, 10);
		if ((it->second < 0.0 && it2->second > 0.0) || (it->second > 0.0 && it2->second < 0.0)) wynik.append("1");
		else wynik.append("0");

		std::advance(it, floor((Tb / Ts)*0.8));
		std::advance(it2, floor(Tb / Ts));

		while ((std::distance(it2, input.end()) >= floor(Tb / Ts)))
		{
			if ((it->second < 0.0 && it2->second > 0.0) || (it->second > 0.0 && it2->second < 0.0)) wynik.append("1");
			else wynik.append("0");

			std::advance(it, floor(Tb / Ts));
			std::advance(it2, floor(Tb / Ts));
		}
		if ((it->second < 0.0 && it2->second > 0.0) || (it->second > 0.0 && it2->second < 0.0)) wynik.append("1");
		else wynik.append("0");
		return wynik;

	}

	std::string BAMI(std::vector<std::pair<double, double>> const& input, double Tb = 1.0)
	{
		double Ts = input.at(1).first - input.at(0).first;
		std::string wynik;
		std::vector<std::pair<double, double>>::const_iterator it = input.begin(), it2 = input.begin();
		std::advance(it2, 10);
		if ((it->second < 0.5 && it2->second > 0.5) || (it->second > -0.5 && it2->second < -0.5)) wynik.append("1");
		else wynik.append("0");

		std::advance(it, floor((Tb / Ts) * 0.8));
		std::advance(it2, floor(Tb / Ts));

		while ((std::distance(it2, input.end()) >= floor(Tb / Ts)))
		{
			if ((it->second < 0.5 && it2->second > 0.5) || (it->second > -0.5 && it2->second < -0.5)) wynik.append("1");
			else wynik.append("0");

			std::advance(it, floor(Tb / Ts));
			std::advance(it2, floor(Tb / Ts));
		}
		if ((it->second < 0.5 && it2->second > 0.5) || (it->second > -0.5 && it2->second < -0.5)) wynik.append("1");
		else wynik.append("0");
		return wynik;
	}
}

namespace modulators
{
	double zegar(double const& t, int const& data)
	{
		return data;
	}
	double const Tb = 1.0;

	double TTL(double const& t, int const& data)
	{
		return data;
	}

	double Manchester(double const& t, int const& data)
	{
		if (data == 0)
		{
			if (t < (Tb / 2.0))
			{
				return -1;
			}
			else
			{
				return 1;
			}
		}
		else
		{
			if (t >= (Tb / 2.0))
			{
				return -1;
			}
			else
			{
				return 1;
			}
		}
	}

	int NRZI_back = 1;
	double NRZI(double const& t, int const& data)
	{
		if (data == 1 && t < 0.005)
		{
			if (NRZI_back == 1) NRZI_back = -1;
			else NRZI_back = 1;
		}
		return NRZI_back;

	}

	int BAMI_back = 0;
	double BAMI(double const& t, int const& data)
	{
		if (data == 0.0) return 0;

		if (data == 1 && t < 0.005)
		{
			if (BAMI_back == 1) BAMI_back = -1;
			else BAMI_back = 1;
		}
		return BAMI_back;

	}
}