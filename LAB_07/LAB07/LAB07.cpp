#define _USE_MATH_DEFINES
//#define _PIXEL_SIZE_X "7680"
//#define _PIXEL_SIZE_X "4320"
#define _PIXEL_SIZE_X "3840"
#define _PIXEL_SIZE_X "2160"
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstddef>
#include <bitset>
#include <iostream>
#include "dft_algorithm.h"
#include "my_plot.h"

#define ARG1 " with linespoints pointtype 6 pointsize 1 lc rgb 'red' "
#define ARG2 " with linespoints lc rgb 'red'  "
#define ARG3 " with linespoints pointtype 6 pointsize 0.3 lc rgb 'black' "

enum Endian
{
	littleEndian = 1,
	bigEndian = 2
};

// STRUMIEN BINARNY = 011000010110001001100011
std::string S2BS(char in[], Endian sw = littleEndian)
{

	int N = strlen(in) - 1;
	std::ostringstream str;
	std::string wynik;

	if (sw == littleEndian)
	{
		for (int i = 0; i <= N; i++)
		{
			std::bitset<8> x(in[i]);
			str << x;
		}
	}
	else
	{
		for (int i = N; i >= 0; i++)
		{
			std::bitset<8> x(in[i]);
			str << x;
		}
	}

	str << std::endl;
	wynik = str.str();

	return wynik;
};

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


int main()
{
	std::string path_wykres1;
	std::vector<double> quant_table;
	//std::vector<std::complex<double>> dft_tab;

	const std::string file_name("zad3 ");
	const std::string file_name2("zad4 ");
	std::string path = "C:\\Users\\GSzwa\\source\\repos\\TD_2020_44522\\LAB_07";

	char moja[10] = "abcd";
	//std::cout << moja << std::endl;
	std::string ret = S2BS(moja);
	ret = ret.substr(0, 16);
	std::cout << ret << std::endl;
	std::string zegar = "01010101010101010";
	double Ts = 0.01;
	std::string name;
	std::vector<std::pair<double, double>> dem_tab;

	//my_plot wykres0(path, file_name + " sygnal S2BS");
	//name = wykres0.function_plot(modulators::zegar, ARG1, ret, Ts, modulators::Tb);
	//wykres0.print_plot("set yrange [-0.5:1.5]; set xtics 0.5; ");

	//my_plot wykres1(path, file_name + " sygnal zegarowy");
	//name = wykres1.function_plot(modulators::zegar, ARG1, zegar, Ts, modulators::Tb);
	//wykres1.print_plot("set yrange [-0.5:1.5]; set xtics 0.5; ");

	my_plot wykres2(path, file_name + " sygnal TTL");
	name = wykres2.function_plot(modulators::TTL, ARG1, ret, Ts, modulators::Tb);
	dem_tab = dft::load_file_real(name);
	std::cout << demodualtor::TTL(dem_tab) << "    -- TTL" << std::endl;
	//wykres2.print_plot("set yrange [-0.5:1.5]; set xtics 0.5; ");

	my_plot wykres3(path, file_name + " sygnal Manchester");
	name = wykres3.function_plot(modulators::Manchester, ARG1, ret, Ts, modulators::Tb);
	dem_tab = dft::load_file_real(name);
	std::cout << demodualtor::Manchester(dem_tab) << "    -- Manchester" << std::endl;
	//wykres3.print_plot("set yrange [-1.5:1.5]; set xtics 0.5; ");

	my_plot wykres4(path, file_name + " sygnal NRZI");
	name = wykres4.function_plot(modulators::NRZI, ARG1, ret, Ts, modulators::Tb);
	dem_tab = dft::load_file_real(name);
	std::cout << demodualtor::NRZI(dem_tab) << "    -- NRZI" << std::endl;
	//wykres4.print_plot("set yrange [-1.5:1.5]; set xtics 0.5; ");

	my_plot wykres5(path, file_name + " sygnal BAMI");
	name = wykres5.function_plot(modulators::BAMI, ARG1, ret, Ts, modulators::Tb);
	dem_tab = dft::load_file_real(name);
	std::cout << demodualtor::BAMI(dem_tab) << "    -- BAMI" << std::endl;
	//wykres5.print_plot("set yrange [-1.5:1.5]; set xtics 0.5; ");

}
