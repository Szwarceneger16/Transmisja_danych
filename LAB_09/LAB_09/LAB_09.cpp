#define _PIXEL_SIZE_X "7680"
#include <iostream>
#include "functions.h"
#include "my_plot.h"

#define ARG1 " with linespoints pointtype 6 pointsize 1 lc rgb 'red' "
#define ARG2 " with linespoints lc rgb 'red'  "
#define ARG3 " with linespoints pointtype 6 pointsize 0.3 lc rgb 'black' "

int main()
{
	const std::string file_name("kanal ");
	//const std::string file_name2("zad4 ");
	std::string path = "C:\\Users\\GSzwa\\source\\repos\\TD_2020_44522\\LAB_09";
	double Ts = 0.01;

	std::string tekst = "Hello World!";
    auto dane = S2BS(tekst);

	my_plot wykres0(path, file_name + " sygnal S2BS");
	wykres0.function_plot(modulators::zegar, ARG1, dane, Ts, modulators::Tb);
	//wykres0.print_plot("set yrange [-0.5:1.5]; set xtics 1; ");
	
	auto zakodowany = Hamming74_SECDED::code(dane);
	my_plot wykres6(path, file_name + " po kodowaniu Hamminga");
	wykres6.function_plot(modulators::zegar, ARG1, zakodowany, Ts, modulators::Tb);
	//wykres6.print_plot("set yrange [-1.5:1.5]; set xtics 1; ");

	std::string zegar = "";
	for (int i = 0; i < zakodowany.size()/2.0; i++)
	{
		zegar.append("0");
		zegar.append("1");
		//zegar.append("1");
	}

	my_plot wykres3(path, file_name + " sygnal NRZI");
	auto name = wykres3.function_plot(modulators::NRZI, ARG1, zakodowany, Ts, modulators::Tb);
	//wykres3.print_plot("set yrange [-1.5:1.5]; set xtics 1; ");
	auto dem_tab = dft::load_file_real(name);
	auto dem_TTL = demodualtor::BAMI(dem_tab);
	//std::cout << zakodowany << std::endl << dem_TTL << std::endl;

	//my_plot wykres1(path, file_name + " sygnal zegarowy");
	//name = wykres1.function_plot(modulators::zegar, ARG1, zegar, Ts, modulators::Tb);
	//wykres1.print_plot("set yrange [-0.5:1.5]; set xtics 1; ");

	auto zdekodowany = Hamming74_SECDED::decode(zakodowany);
	
	my_plot wykres7(path, file_name + " po dekodowaniu Hamminga NRZI");
	wykres7.function_plot(modulators::zegar, ARG1, zakodowany, Ts, modulators::Tb);
	wykres7.print_plot("set yrange [-1.5:1.5]; set xtics 1; ");

	std::cout << tekst << std::endl << SB2S(zdekodowany) << std::endl;

}
