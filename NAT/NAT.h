#pragma once

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>  

class NatMapper {

public:
	//default constructor
	NatMapper(){}
	
	//function to read and fill out maps
	bool ReadNatMap(std::string &inputFile);

	//function to write output of flows. checks each map, the first map it sees it stops.
	bool WriteNatFlowOutput(std::string &flowFile);

private:
	std::unordered_map<std::string, std::string> m_exact_pair_to_pair; //this map corresponds to exact matches of ip:port pairs
	std::unordered_map<std::string, std::string> m_port_to_pair; //this map corresponds to ports that work with any ip
	std::unordered_map<std::string, std::string> m_ip_to_pair; //this map corresponds to ips that work with any port
};