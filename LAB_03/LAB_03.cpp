#define _USE_MATH_DEFINES
#define _PIXEL_SIZE_X "7680"
#define _PIXEL_SIZE_X "4320"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "my_plot.h"
#include "my_quant.h"
#include "dft_algorithm.h"

#define ARG1 "pointtype 6 pointsize 0.25 lc rgb 'red' title 'wykres funkcji sin(x)' "
#define ARG2 " lc rgb 'red' title 'wykres zkwantyzowanej funkcji sin(x)' "
#define ARG3 "pointtype 6 pointsize 0.3 lc rgb 'black' title 'probki zkwantyzowane' "

double A = 1.0, f = 2.0, fi = 5.0 * M_PI;

double fun_1(double t)
{
	return (A * sin((2 * M_PI * f * t) + fi));
}

std::vector<double> load_from_file_to_table(std::string path)
{
	std::fstream load_file;
	std::vector<double> new_tab;
	
	load_file.open(path, std::ios::in);
	double actual1 = 0.0,actual2 = 0.0;

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

std::string save_to_file_from_table(std::string path, std::vector<std::complex<double>> input_tab, double fs)
{
	std::fstream save_file;
	std::vector<std::complex<double>>::iterator it1 = input_tab.begin();
	save_file.open(path, std::ios::out | std::ios::trunc);

	int N = input_tab.size();
	for (size_t k = 0; k < N; k++)
	{
		save_file << k << " " << (10*log10(sqrt( pow(it1->real(),2)+ pow(it1->imag(), 2)))) << std::endl;
		it1++;
	}

	save_file.close();
	return path;
}

int main(int argc, char* argv[])
{
	std::string path(argv[0]);
	path = path.substr(0, path.find_last_of('\\'));
	//std::string path = "C:\\Users\\GSzwa\\source\\repos\\TD_2020_44522\\LAB_02\\LAB_02";

	my_plot wykres1(path, "wykres zad2");


	//std::cout << wykres1.debug() ;
	std::string name = wykres1.function_plot(fun_1, ARG1, 0, 10, 0.01);
	wykres1.print_plot();
	
	std::string path_wykres1 = wykres1.get_path();

	std::vector<double> quant_table = load_from_file_to_table(path_wykres1);
	std::vector<std::complex<double>> dft_tab = algo::dft(quant_table);
	name = save_to_file_from_table(path+"\\dft.dot", dft_tab,(1/0.01));
	my_plot wykres3(path, "wykres zad2 2");
	wykres3.read_file(name,ARG3);
	wykres3.print_plot();
}

