#include "data.hpp"
#include <sstream>

void	print_data(t_data *data) {


	std::cout << "video path: " << data->video << std::endl;
	std::cout << "radius: " << data->radius << std::endl;
	std::cout << "ap_width: " << data->ap_width << std::endl;
	std::cout << "ap_height: " << data->ap_height << std::endl;
	std::cout << "sigma1: " << data->sigma1 << std::endl;
	std::cout << "sigma2: " << data->sigma2 << std::endl;
}

void	parse_line(std::string line, t_data *data) {

	int pos = line.find('=');
	std::string key = line.substr(0, pos);
	std::string str_value = line.substr(pos + 1, line.size());
	int	value = 0;
	double sigma = 0.0;
	if ( key == "VIDEO" ) {
		
		data->video = str_value;
	}
	else {
		
		try {

			if ( key == "SIGMA1" || key == "SIGMA2" )
				sigma = std::stod(str_value);
			else
				value = std::stoi(str_value);
			if ( (key == "RADIUS" && value < 0) ||
				(key == "APERTURE_WIDTH" && value % 2 == 0) )
				throw "";
		}
		catch (...) {

			std::cout << "Invalid value of " << key
				<<". Value of " << key << " is set to default"
				<< std::endl;
			return ;
		}
	}
	if ( key == "RADIUS" )
		data->radius = value;
	else if ( key == "APERTURE_WIDTH" )
		data->ap_width = value;
	else if ( key == "APERTURE_HEIGHT" )
		data->ap_height = value;
	else if ( key == "SIGMA1" )
		data->sigma1 = sigma;
	else if ( key == "SIGMA2" )
		data->sigma2 = sigma;
}

t_data*	ini_parser(void) {

	std::ifstream file("./options-config.ini");
	try {

		if ( !file.is_open() )
			throw "Missing options-config.ini file";
	}
	catch (const char *str) {

		std::cout << str << std::endl;
		return NULL;
	}
	t_data *data = new t_data;
	std::string line;
	while ( std::getline(file, line) ) {

		if ( !line.empty() )
			parse_line(line, data);
	}
	print_data(data);
	return data;
}
