//#include "Tracy.hpp"
#include <iostream>
#include "Helper.h"
#include "IPatternMatching.h"
#include "AhoCorasickAutomaton.h"
#include "KnuthMorrisPratt.h"
#include "IAnalysis.h"
#include "SequentialAnalysis.h"
#include "ParellelAnalysis.h"
#include "boost/property_tree/ptree.hpp"
#include "boost/property_tree/ini_parser.hpp"

using namespace std;
using namespace boost::property_tree;

/// <summary>
/// Main class
/// </summary>
void main()
{
    try {
        ptree pt;
        ini_parser::read_ini("config.ini", pt);

        string input = pt.get<string>("file.input_path");
        int algorithm = pt.get<int>("algorithm.type");
        int parellel = pt.get<int>("algorithm.parellel");

        IAnalysis* analysis;

        if (parellel == 1)
            analysis = new ParellelAnalysis(input, algorithm);
        else
            analysis = new SequentialAnalysis(input, algorithm);

        analysis->generateReport();

        system("pause");

    }
    catch (const std::exception& e) {
        std::cerr << "An exception occurred: " << e.what() << std::endl;

        // Stop the console from closing.
        std::cout << "Press Enter to continue...";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return;
}