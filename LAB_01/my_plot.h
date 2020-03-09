// my_plot.h - Contains declarations of drawing chart functions
#pragma once


// This class contains method to drawing multiple function in one chart
// Firsly, initialize an instance of class and pass argv[0] (actual directory path) and title of chart
// Next, use fun_plot use sa many times as you have function to draw
// After, use print to make png file with charts

// Also you can change resolution using set_resolution, default is  3840 x 2160


class my_plot {
	std::vector<std::string> __files;
	std::vector<std::string> __plot_arguments;
	std::string __out_path;
	std::string __title;
	std::string _PIXEL_SIZE_X;
	std::string _PIXEL_SIZE_Y;
public:
	__declspec(dllexport) my_plot(std::string __out_name, std::string __title);
	__declspec(dllexport) int fun_plot(double (*fun) (double), std::string, double, double const, double const, double);
	__declspec(dllexport) void print(std::string = "");
	__declspec(dllexport) void set_resolution(int, int);
};