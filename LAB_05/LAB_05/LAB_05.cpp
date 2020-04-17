#define _USE_MATH_DEFINES
//#define _PIXEL_SIZE_X "7680"
//#define _PIXEL_SIZE_X "4320"
#define _PIXEL_SIZE_X "3840"
#define _PIXEL_SIZE_X "2160"
#include<sstream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstddef>
#include <bitset>
#include "my_plot.h"
#include "dft_algorithm.h"

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

	//std::cout << wynik << std::endl;
	/*int stringSize = (wynik.size() / 10) + 1;
	int* table = new int[stringSize]();
	std::string temp = "";
	for (int i = 0; i < stringSize; i+=11)
	{
		for (short j = i; j <= (i+10); j++)
		{
			temp.append(1,wynik[j]);
		}
		table[i] = stoi(temp);
			temp.clear();
	}*/

	return wynik;
};


namespace function {
	double fm = 2.0;
	double fi = 0;

	//-----------------------------------
	double A0 = 1.0;
	double A1 = 0.0;
	double za(double t, int const data) // kluczowanie amplitudy
	{
		if (data == 0)
			return (A1 * sin(2 * M_PI * fm * t + fi));
		else 
			return (A0 * sin((2 * M_PI * fm * t)+ fi));
	}

	//-----------------------------------
	double fm0 = 1.0;
	double fm1 = 4.0;
	double zf(double t, int const data)// kluczowanie czestotliowsci
	{
		return data == 0 ? A0 * sin(2 * M_PI * fm0 * t + fi) : A0 * sin(2 * M_PI * fm1 * t + fi);
	}

	//-----------------------------------
	double fi0 = 0;
	double fi1 = M_PI;
	double zp(double t, int const data) // kluczowanie fazy
	{
		return data == 0 ? A0 * sin(2 * M_PI * fm * t + fi0) : A0 * sin(2 * M_PI * fm * t + fi1);
	}
}

double generuj(double t, int const data)
{
	return data == 0 ? 0 : 1;
}

/* ZMIERZONE SZEROKOSCI PASMA SYGNAŁU dla f sygnału = 25Hz
	ZAD 4
	kluczowanie amplitudy = 2 Hz
	kluczowanie czestotliowsci = 1Hz
	kluczowanie fazy = 3Hz

*/

//#define __DFT

int main()
{
	std::string path_wykres1;
	std::vector<double> quant_table;
	std::vector<std::complex<double>> dft_tab;

	const std::string file_name("zad3 ");
	const std::string file_name2("zad4 ");
	std::string path = "C:\\Users\\GSzwa\\source\\repos\\TD_2020_44522\\LAB_05";

	char moja[10] = "abc";
	//std::cout << moja << std::endl;
	std::string ret = S2BS(moja);
	ret = ret.substr(0, 11);
	double Tb = 2.0/10; //zad3
	//double Tb = 1.0; //zad2
	double Ts = 0.005;
	int N = ret.size() * (1 / Tb);
	function::fm = (N) * pow(Tb,-1);
	function::fm0 = (N + 1) / Tb;
	function::fm1 = (N + 2) / Tb;

	my_plot wykres1(path, file_name + " sygnal infromacyjny");
	std::string name = wykres1.function_plot(generuj,ARG1, ret,Ts,Tb);
	wykres1.print_plot("set yrange [-2:3]; ");
	path_wykres1 = wykres1.get_path();

#ifdef __DFT
	quant_table = dft::load_file_real(path_wykres1);
	dft_tab = dft::dft(quant_table);
	name = dft::save_file_spectrum(path + "\\wykresy\\spectrum.dot", dft_tab, function::fm);
	my_plot wykres1_A(path, file_name2 + " widmo sygnal informacyjny");
	wykres1_A.read_file(name, ARG3);
	wykres1_A.print_plot();
#endif // DEBUG

	my_plot wykres2(path, file_name + " kluczowanie amplitudy");
	name = wykres2.function_plot(function::za,ARG1, ret,Ts, Tb);
	wykres2.print_plot("set yrange [-2:3]; ");
	path_wykres1 = wykres2.get_path();
	
#ifdef __DFT
	quant_table = dft::load_file_real(path_wykres1);
	dft_tab = dft::dft(quant_table);
	name = dft::save_file_spectrum(path + "\\wykresy\\spectrum.dot", dft_tab, function::fm);
	my_plot wykres2_A(path, file_name2 + " widmo kluczowanie amplitudy");
	wykres2_A.read_file(name, ARG3);
	wykres2_A.print_plot();
#endif // __DFT

	

	my_plot wykres3(path, file_name + " kluczowanie czestotliowsci");
	name = wykres3.function_plot(function::zf, ARG1, ret, Ts, Tb);
	wykres3.print_plot("set yrange [-2:3]; ");
	path_wykres1 = wykres3.get_path();

#ifdef __DFT
	quant_table = dft::load_file_real(path_wykres1);
	dft_tab = dft::dft(quant_table);
	name = dft::save_file_spectrum(path + "\\wykresy\\spectrum.dot", dft_tab, function::fm);
	my_plot wykres3_A(path, file_name2 + " widmo kluczowanie czestotliowsci");
	wykres3_A.read_file(name, ARG3);
	wykres3_A.print_plot();
#endif // __DFT

	

	my_plot wykres4(path, file_name + " kluczowanie fazy");
	name = wykres4.function_plot(function::zp, ARG1, ret, Ts, Tb);
	wykres4.print_plot("set yrange [-2:3]; ");
	path_wykres1 = wykres4.get_path();

#ifdef __DFT
	quant_table = dft::load_file_real(path_wykres1);
	dft_tab = dft::dft(quant_table);
	name = dft::save_file_spectrum(path + "\\wykresy\\spectrum.dot", dft_tab, function::fm);
	my_plot wykres4_A(path, file_name2 + " widmo kluczowanie fazy");
	wykres4_A.read_file(name, ARG3);
	wykres4_A.print_plot();
#endif // __DFT
	


}
