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

#define ARG1 " pointtype 6 pointsize 0.25 lc rgb 'blue' title 'wykres funkcji sin(x)' "
#define ARG2 " lc rgb 'red' title 'wykres zkwantyzowanej funkcji sin(x)' "
#define ARG3 " pointtype 6 pointsize 0.3 lc rgb 'black' title 'probki zkwantyzowane' "
//#define ARG4 " using 1:(10 * $2); with linespoints pointtype 6 pointsize 0.3 lc rgb 'black' title 'probki zkwantyzowane' "

namespace function
{
	double A = 1.0;
	double fm = 2.0;
	double fn = 10 * fm;
	double ka = 0.5;
	double kp = 1.0;

	double info_signal(double t)
	{	
		return A * sin(2 * M_PI * fm * t);
	}

	double amplitude_modulate(double t)
	{
		return (ka * info_signal(t) + 1) * cos(2 * M_PI * fn * t);
	}

	double phase_modulate(double t)
	{
		return cos(2 * M_PI * fn * t + kp * info_signal(t));
	}

}


int main()
{
	const std::string file_name("zad2 A ");
	std::string path = "C:\\Users\\GSzwa\\source\\repos\\TD_2020_44522\\LAB_04";

	/*my_plot wykres1(path, file_name + " wykres");
	std::string name = wykres1.function_plot(function::info_signal, ARG2, 0, 3, 0.005);
	wykres1.print_plot();*/

	//============================================================

	my_plot wykres2(path, file_name + " modulacja amplitudy");
	wykres2.function_plot(function::amplitude_modulate, ARG1, 0, 3, 0.005);
	//wykres2.print_plot();

	std::string path_wykres1 = wykres2.get_path();

	std::vector<double> quant_table = dft::load_file_real(path_wykres1);
	std::vector<std::complex<double>> dft_tab = dft::dft(quant_table);
	std::string name = dft::save_file_spectrum(path + "\\wykresy\\spectrum.dot", dft_tab, 0.005);
	my_plot wykres2_A(path, file_name + " widmo modulacji amplitudy");
	wykres2_A.read_file(name,ARG3);
	wykres2_A.print_plot("set logscale y 10; show logscale; ");

	//====================================================

	my_plot wykres3(path, file_name + " modulacja fazy");
	wykres3.function_plot(function::phase_modulate, ARG1, 0,3, 0.005);
	//wykres3.print_plot();

	std::string path_wykres2 = wykres3.get_path();

	std::vector<double> quant_table2 = dft::load_file_real(path_wykres2);
	std::vector<std::complex<double>> dft_tab2 = dft::dft(quant_table2);
	std::string name2 = dft::save_file_spectrum(path + "\\wykresy\\spectrum.dot", dft_tab2, 0.005);
	my_plot wykres3_A(path, file_name + " widmo modulacji fazy");
	wykres3_A.read_file(name2, ARG3);
	wykres3_A.print_plot("set logscale y 10; show logscale; ");
}

