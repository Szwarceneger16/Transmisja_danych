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

double fun_1(double const t)
{
	return (A * sin((2 * M_PI * f * t) + fi));
}

double fun_x(double const t)
{
	return (pow(t, 2) * 2 + t * 2 + 4);
}

double fun_y(double const t)
{
	return (2 * pow(fun_x(t), 2) + 12 * cos(t));
}

double fun_z(double const t)
{
	return (sin(2 * M_PI * 7 * t) * fun_x(t) - 0.2 * log10(abs(fun_y(t)) + M_PI));
}

double fun_u(double const t)
{
	return (sqrt(abs(fun_y(t) * fun_y(t) * fun_z(t))) - 1.8 * sin(0.4 * t * fun_z(t) * fun_x(t)));
}

double fun_v(double const t)
{
	if (t < 0.22)
		return ((1 - 7 * t) * sin((2 * M_PI * t * 10) / (t + 0.04)));
	else if (t < 0.7)
		return (0.63 * t * sin(125 * t));
	else
		return (pow(t, -0.662) + 0.77 * sin(8 * t));
}

int N = 22;

double fun_p(double t)
{
	double sum = 0;
	for (int i = 0; i < N; i++)
	{
		sum += ((cos(12 * t * pow(N, 2)) + cos(16 * t * N)) / ((pow(N, 2)) == 0.0 ? 1 : pow(N, 2)));
	}
	return sum;
}



int main(int argc, char* argv[])
{
	const std::string file_name("zad2 funkcja 9 ");
	/*std::string path(argv[0]);
	path = path.substr(0, path.find_last_of('\\'));*/
	std::string path = "C:\\Users\\GSzwa\\source\\repos\\TD_2020_44522\\LAB_03";

	my_plot wykres1(path, file_name+"wykres");

	//std::cout << wykres1.debug() ;
	std::string name = wykres1.function_plot(fun_p, ARG1, 0,225, 0.1);
	wykres1.print_plot();
	
	std::string path_wykres1 = wykres1.get_path();

	std::vector<double> quant_table = algo::load_from_file_to_table(path_wykres1);
	std::vector<std::complex<double>> dft_tab = algo::dft(quant_table);
	name = algo::save_to_file_from_table(path+"\\dft.dot", dft_tab,0.1);
	my_plot wykres3(path, file_name + "widmo");
	wykres3.read_file(name,ARG3);
	wykres3.print_plot();
}

