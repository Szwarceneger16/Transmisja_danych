
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "functions.h"
#include "my_plot.h"

#define ARG1 " with linespoints pointtype 1 pointsize 2 lc rgb 'red' "

std::vector<float> szum(int numSamples = 1)
{
	const static int q = 15;
	const static float c1 = (1 << q) - 1;
	const static float c2 = ((int)(c1 / 3)) + 1;
	const static float c3 = 1.f / c1;
	float random = 0.f;
	std::vector<float> noise;

	for (int i = 0; i < numSamples; i++)
	{
		random = ((float)rand() / (float)(RAND_MAX + 1));
		noise.push_back((2.f * ((random * c2) + (random * c2) + (random * c2)) - 3.f * (c2 - 1.f)) * c3);
	}
	return noise;
}


std::vector<std::pair<double, double>> zaszum(std::vector<std::pair<double, double>> tab,double alfa)
{
	int nn = 0;
	auto noise = szum(16);
	for (int n = 0; n < tab.size(); n++)
	{
		tab[n].second = (tab[n].second * alfa) + (noise[nn] * (1.0 - alfa));
		nn++;
		if (nn >= noise.size())
		{
			nn = 0;
		}
	}
	return tab;
}

double BER(std::string in1, std::string in2)
{
	std::string::iterator it_in1 = in1.begin();
	std::string::iterator it_in2 = in2.begin();
	double ile = 0;
	while (it_in1 != in1.end() && it_in2 != in2.end())
	{
		if (it_in1 != it_in2) ile++;
		it_in1++;
		it_in2++;
	}
	return ile / in1.size();
}

int main()
{
	const std::string file_name("zadanie kanalowe ");
	//const std::string file_name2("zad4 ");
	std::string path = "C:\\Users\\GSzwa\\source\\repos\\TD_2020_44522\\LAB_09_10";
	double Ts = 0.01;

	std::string tekst = "AlaMa";
    auto dane = S2BS(tekst);

	//my_plot wykres0(path, file_name + " sygnal wejsciowy");
	//wykres0.function_plot(modulators::zegar, ARG1, dane, Ts, modulators::Tb);
	//wykres0.print_plot("set yrange [-1.5:1.5]; set xtics 10; ");
	
	auto zakodowany = Hamming74_SECDED::code(dane);
	//my_plot wykres6(path, file_name + " po Hammingu");
	//wykres6.function_plot(modulators::zegar, ARG1, zakodowany, Ts, modulators::Tb);
	//wykres6.print_plot("set yrange [-1.5:2.0]; set xtics 10; ");

	std::string zegar = "";
	for (int i = 0; i < zakodowany.size()/2.0; i++)
	{
		zegar.append("0");
		zegar.append("1");
		//zegar.append("1");
	}

	float alfa = 0.5;

	my_plot wykres3(path, file_name + " kodowanie BAMI");
	auto name_gl = wykres3.function_plot(modulators::Manchester, ARG1, zakodowany, Ts, modulators::Tb);
	//wykres3.print_plot("set yrange [-2.0:2.0]; set xtics 10; ");
	auto mod_tab = dft::load_file_real2(name_gl);

	//std::cout << zakodowany << std::endl << dem_TTL << std::endl;

	auto mod_tab2 = dft::load_file_real2(name_gl);
	//std::vector<std::complex<double>> dft_tab = dft::dft(mod_tab2);
	//auto name = dft::save_file_spectrum(path + "\\wykresy\\spectrum1.dot", dft_tab, 0.01);
	//my_plot wykres_widmo1(path, file_name + " widmo BAMI przed alfa " + std::to_string(alfa));
	//wykres_widmo1.read_file(name, ARG1);
	//wykres_widmo1.print_plot();

	mod_tab2 = zaszum(mod_tab2, alfa);

	//dft_tab = dft::dft(mod_tab2);
	//name = dft::save_file_spectrum(path + "\\wykresy\\spectrum1.dot", dft_tab, 0.01);
	//my_plot wykres_widmo2(path, file_name + " widmo BAMI po alfa " + std::to_string(alfa));
	//wykres_widmo2.read_file(name, ARG1);
	//wykres_widmo2.print_plot();

	auto dem = demodualtor::Manchester(mod_tab);

	//my_plot wykres1(path, file_name + " sygnal zegarowy");
	//name = wykres1.function_plot(modulators::zegar, ARG1, zegar, Ts, modulators::Tb);
	//wykres1.print_plot("set yrange [-2.0:2.0]; set xtics 10; ");

	auto zdekodowany = Hamming74_SECDED::decode(dem);
	
	//my_plot wykres7(path, file_name + " po Hammingu dekodowanie BAMI");
	//wykres7.function_plot(modulators::zegar, ARG1, zakodowany, Ts, modulators::Tb);
	//wykres7.print_plot("set yrange [-2.0:2.0]; set xtics 10; ");

	std::cout << tekst << std::endl << SB2S(zdekodowany) << " | " << BER(dane, zdekodowany) <<std::endl;

}
