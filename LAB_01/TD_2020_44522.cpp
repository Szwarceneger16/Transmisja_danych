#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include <fstream>
#include <string>
#include <direct.h>
#include <cstdio>
#include <locale>
#include <vector>

#define _PIXEL_SIZE_X "3840"
#define _PIXEL_SIZE_Y "2160"

typedef double(*funkcja_t)(double const &);

using namespace std;

//void print(std::string pathname, std::string out, std::vector<std::string> files, std::vector<std::string> plot_arguments, std::string title,double xctis,double yctis)
//{
//	if (files.size() == 0) return;
//	std::string name_out;
//	
//	std::string xx = to_string(xctis);
//	xx[xx.find(',')] = '.';
//	std::string yy = to_string(xctis);
//	yy[yy.find(',')] = '.';
//	name_out = "gnuplot -p -e \"cd '" + pathname + "'; set xlabel 'Os X'; set ylabel 'Os Y'; set terminal png font arial 11 size "+ _PIXEL_SIZE_X +","+ _PIXEL_SIZE_Y+"; set xtics " + xx
//		+ (std::string)"; set ytics " + yy + "; set title '" + title + "'; show title; set output '" + out + ".png'; plot '" + files[0] + "' with points " + plot_arguments[0];
//	//cout << name_out;
//	
//	for (int i = 1; i < files.size(); i++)
//	{
//		name_out += ",'" + files[i] + "' with points " + plot_arguments[i];
//	}
//
//	name_out += ";\"";
//	system(name_out.c_str());
//}

void print(std::string pathname, std::string out, std::vector<std::string> files, std::vector<std::string> plot_arguments, std::string title)
{
	if (files.size() == 0) return;
	std::string name_out;

	name_out = "gnuplot -p -e \"cd '" + pathname + "';set xlabel 'Os X'; set ylabel 'Os Y'; set terminal png font arial 11 size " + _PIXEL_SIZE_X + "," + _PIXEL_SIZE_Y + ";"
		+(std::string)" set title '" + title + "'; show title; set output '" + out + ".png'; plot '" + files[0] + "' with points " + plot_arguments[0];
	//cout << name_out;

	for (int i = 1; i < files.size(); i++)
	{
		name_out += ",'" + files[i] + "' with points " + plot_arguments[i];
	}

	name_out += ";\"";
	system(name_out.c_str());
}

//void print(std::string pathname,std::string out, std::vector<std::string> files, std::vector<std::string> plot_arguments, std::string title, double xctis, double yctis, std::string options)
//{
//	if (files.size() == 0) return;
//	std::string xx = to_string(xctis);
//	xx[xx.find(',')] = '.';
//	std::string yy = to_string(xctis);
//	yy[yy.find(',')] = '.';
//	std::string name_out = "gnuplot -p -e \"cd '" + pathname + "';set xlabel 'Os X'; set ylabel 'Os Y'; set terminal png font arial 11 size " + _PIXEL_SIZE_X + "," + _PIXEL_SIZE_Y + "; set xtics " + xx
//		+ (std::string)"; set ytics " + yy + "; set title '" + title + "'; show title; " + options + " set output '" + out + ".png'; plot '" + files[0] + "' with points " + plot_arguments[0];
//	//cout << name_out;
//	for (int i = 1; i < files.size(); i++)
//	{
//		name_out += ",'" + files[i] + "' with points " + plot_arguments[i];
//	}
//
//	name_out += ";\"";
//	system(name_out.c_str());
//}

void print(std::string pathname, std::string out, std::vector<std::string> files, std::vector<std::string> plot_arguments, std::string title, std::string options)
{
	if (files.size() == 0) return;

	std::string name_out = "gnuplot -p -e \"cd '" + pathname + "';set xlabel 'Os X'; set ylabel 'Os Y'; set terminal png font arial 11 " + _PIXEL_SIZE_X + "," + _PIXEL_SIZE_Y + "; "
		+ (std::string)"set title '" + title + "'; show title; " + options + " set output '" + out + ".png'; plot '" + files[0] + "' with points " + plot_arguments[0];
	//cout << name_out;
	for (int i = 1; i < files.size(); i++)
	{
		name_out += ",'" + files[i] + "' with points " + plot_arguments[i];
	}

	name_out += ";\"";
	system(name_out.c_str());
}

std::pair<double,double> wyroznik_trojmianu_wykres(double a, double b, double c,double const start, double const koniec, double dok)
{
	int delta = pow(b, 2) - (4 * (long long)a * c);

	std::fstream delta_wykres,mz_wykres;
	delta_wykres.open("wykresy\\function.dat", std::ios::out | std::ios::trunc);

	long long l_dok = (koniec - start) / dok;
	double actual = start;
	for (int i = 0; i < l_dok; i++)
	{
		delta_wykres << actual << " " << (pow(actual, 2) * a + actual * b + c) << std::endl;
		actual += dok;
	}

	delta_wykres.close();

	std::pair<double, double> wynik;
	std::string option;

	mz_wykres.open("wyroznik_trojmianu\\points.dat", std::ios::out | std::ios::trunc);
	if (delta < 0)
	{
		wynik = std::pair<double, double>(NAN, NAN);
		option = "set label 'brak miejsc zerowych' at graph 0.5,0.5 center font 'Arial, 24'; ";
	}
	else if (delta == 0)
	{
		wynik = std::pair<double, double>((((-1) * b) / (2 * a)), NAN);
		mz_wykres << wynik.first << " " << (pow(wynik.first, 2) * a + wynik.first * b + c) << std::endl;
		option = "set label 'jedno miejsce zerowe' at graph 0.5,0.5 center font 'Arial, 24'; ";
	}
	else
	{
		wynik = std::pair<double, double>((sqrt(delta)-b)/(2*a), (-sqrt(delta) - b) / (2 * a));
		mz_wykres << wynik.first << " " << (pow(wynik.first, 2) * a + wynik.first * b + c) << std::endl;
		mz_wykres << wynik.second << " " << (pow(wynik.second, 2) * a + wynik.second * b + c) << std::endl;
		option = "set label 'dwa miejsca zerowe' at graph 0.5,0.5 center font 'Arial, 24'; ";;
	}
	mz_wykres.close();

	std::vector<std::string> files{ "function.dat", "points.dat" };
	std::vector<std::string> plot_option{ "pointtype 6 pointsize 0.5 lc rgb 'red' title 'funkcja " + to_string((int)a)+"*x^2 + " + to_string((int)b) + "*x + " + to_string((int)c) +"'", "pointtype 3 pointsize 3 lc rgb 'black' title 'miejsca zerowe'" };
	

	print("C:/Users/GSzwa/source/repos/TD_2020_44522/wykresy","wyroznik trojmianu",files ,plot_option,"wyróznik trójmianu kwadratowego",option);
	return wynik;
}

double fun_x(double const& t)
{
	return (pow(t, 2) * 2 + t * 2 + 4);
}

double fun_y (double const& t)
{
	return (2 * pow(fun_x(t), 2) + 12 * cos(t));
}

double fun_z(double const& t)
{
	return (sin(2*M_PI*7*t)*fun_x(t)-0.2*log10(abs(fun_y(t))+M_PI));
}

double fun_u(double const& t)
{
	return (sqrt(abs(fun_y(t)* fun_y(t)*fun_z(t)))-1.8*sin(0.4*t*fun_z(t)*fun_x(t)));
}

double fun_v(double const& t)
{
	if (t < 0.22)
		return ((1 - 7 * t) * sin((2 * M_PI * t * 10) / (t + 0.04)));
	else if (t < 0.7)
		return (0.63 * t * sin(125 * t));
	else
		return (pow(t, -0.662) + 0.77 * sin(8 * t));
}

double fun_p(double const& t)
{
	double sum = 0;
	double N[] = { 2.0,4.0,22.0 };
	for (int i = 0; i < 3; i++)
	{
		sum += ((cos(12 * t * pow(N[i], 2)) + cos(16 * t * N[i])) / (pow(N[i], 2)));
	}
	return sum;
}

int fun_plot(funkcja_t fun, std::string out, std::string funkcja,double t, double const start, double const koniec, double dok)
{
	std::fstream wykres;
	wykres.open("wykresy\\function.dat", std::ios::out | std::ios::trunc);
	long long l_dok = (koniec - start) / dok;
	double actual = start;
	for (int i = 0; i < l_dok; i++)
	{
		wykres << actual << " " << fun(actual) << std::endl;
		actual += dok;
	}
	wykres.close();

	std::vector<std::string> files{ "function.dat" };
	std::vector<std::string> plot_option{ "pointtype 6 pointsize 0.25 lc rgb 'red' title 'funkcja " + funkcja + "'" };

	cout << fun(koniec) << " " << fun(start);
	print("C:/Users/GSzwa/source/repos/TD_2020_44522/wykresy",out, files, plot_option, out);

	return fun(t);
}


int main()
{
	_mkdir("wykresy");
	setlocale(LC_ALL, "pl_PL");
	
	//std::pair< double, double > wynik = wyroznik_trojmianu_wykres(2, 2, 4,-10,10,0.01);
	
	/*cout.setf(ios::fixed);
	cout << wynik.first << " " << wynik.second ;*/

	fun_plot(fun_y,"wykres_y","funkcja y",1, 0, 1, (1.0 / 22050));
}
