#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include <string>
#include <vector>

#include "my_plot.h"
#include "my_quant.h"

#define ARG1 "pointtype 6 pointsize 0.25 lc rgb 'red' title 'wykres funkcji sin(x)' "
#define ARG2 " lc rgb 'red' title 'wykres zkwantyzowanej funkcji sin(x)' "
#define ARG3 "pointtype 6 pointsize 0.3 lc rgb 'black' title 'probki zkwantyzowane' "

double A, f, fi;
double fun_1(double t)
{
	return (A * sin((2 * M_PI * f * t) + fi));
}

int main(int argc,char* argv[])
{
	A = 1.0;
	f = 6.0;
	fi = 5.0*M_PI;

	/*std::string path(argv[0]);
	path = path.substr(0, path.find_last_of('\\'));*/
	std::string path = "C:\\Users\\GSzwa\\source\\repos\\TD_2020_44522\\LAB_02\\LAB_02";

	my_plot wykres1(path, "wykres_zad3");
	
	//std::cout << wykres1.debug() ;
	std::string name = wykres1.function_plot(fun_1, ARG1, 0, 2, 0.002);
	wykres1.print_plot();
	
	my_quant wykres2(path, "kwantyfikacja_zad3");
	name = wykres2.quantize(2, pow(2, 8), ARG2 ,ARG3 , name);
	wykres2.print_quant();

}
