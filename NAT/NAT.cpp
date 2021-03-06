// NAT.cpp : Defines the entry point for the console application.
//

 
#include "NAT.h"


bool NatMapper::ReadNatMap(std::string &inputFile)
{
	std::ifstream nat_file("NAT.txt");
	if (!nat_file.good()) return false;

	std::string line;
	std::string delimiter = ":";

	while (std::getline(nat_file, line))
	{
		if (!line.empty()) {
			std::istringstream iss(line);

			std::string first_pair; //help from https://stackoverflow.com/questions/2880903/simple-string-parsing-with-c for string tokenizing
			if (std::getline(iss, first_pair, ','))
			{

				std::string second_pair;
				std::getline(iss, second_pair, ',');

				std::string ip = first_pair.substr(0, first_pair.find(delimiter)); //help from : https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
				std::string port = first_pair.substr(first_pair.find(delimiter) + 1, first_pair.length());

				if (ip == "*") {
					m_port_to_pair[port] = second_pair;
				}
				else if (port == "*") {
					m_ip_to_pair[ip] = second_pair;
				}
				else {
					m_exact_pair_to_pair[first_pair] = second_pair;
				}
			}
		}
	}
	return true;
}

bool NatMapper::WriteNatFlowOutput(std::string &flowFile)
{
	std::ifstream flow_file(flowFile); //help from https://stackoverflow.com/questions/8863505/simple-file-write-function-in-c
	if (!flow_file.good()) return false;
	std::ofstream output;
	output.open("OUTPUT.txt");
	std::string arrow = "->";
	std::string line;
	std::string delimiter = ":";

	while (std::getline(flow_file, line))
	{
		if (!line.empty()) {
			std::istringstream iss(line);

			std::string pair = line;

			std::string ip = pair.substr(0, pair.find(delimiter));
			std::string port = pair.substr(pair.find(delimiter) + 1, pair.length());
			bool exists = false;

			if (m_exact_pair_to_pair.find(pair) != m_exact_pair_to_pair.end()) //needed refresher for unordered_map api https://stackoverflow.com/questions/34512437/simplest-method-to-check-whether-unordered-map-of-unordered-maps-contains-key
				output << pair << " " << arrow << " " << m_exact_pair_to_pair[pair] << "\n";

			else if (m_ip_to_pair.find(ip) != m_ip_to_pair.end())
				output << pair << " " << arrow << " " << m_ip_to_pair[ip] << "\n";

			else if (m_port_to_pair.find(port) != m_port_to_pair.end())
				output << pair << " " << arrow << " " << m_port_to_pair[port] << "\n";

			else
				output << "No nat match for " << pair << "\n";

		}
	}


	output.close();

	return true;
}


int main()
{

	NatMapper nat_mapper;

	std::string nat_file;
	std::cout << "Please input NAT file name and path:";
	std::cin >> nat_file;
	std::cout << "Please input Flow file name and path:";
	std::string flow_file;
	std::cin >> flow_file;
	nat_mapper.ReadNatMap(nat_file);
	nat_mapper.WriteNatFlowOutput(flow_file);

	std::cout << "Output has be written to default location of directory under OUTPUT.txt \n Press any key to continue";
	int x;
	std::cin >> x;

	return 0;
}