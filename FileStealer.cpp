#ifdef _WIN32
#include <Windows.h>
#endif
#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "functions.hpp"
int main() {
	int option{};
	std::string filenameWhichGetCopy;
	std::string fusion = "D:\\FileStealerInfo.txt";
	std::string createNameList = "D:\\NameList.txt";
	std::ofstream listFile(createNameList, std::ios::app);
	std::ofstream newFile(fusion, std::ios::app);
	std::filesystem::path forShowInfos(fusion);
	std::filesystem::path ListOnDevice(createNameList);

	while (true){
		std::cout << "1. Searching File." << std::endl << "2. for read FileStealerInfo.txt." << std::endl << "3. Search all from NameList.txt." << std::endl << "4. Exit Program." << std::endl;
		std::cin >> option;
		std::cout << "\n";
		system("cls");
		if (std::cin.fail()){
			std::cerr << "Your Input is not a Number!" << "\n";
			std::cin.clear();
			std::cin.ignore(50, '\n');
		}
		else {
			switch (option) {
			case 1: {
				findFileByName(filenameWhichGetCopy,fusion,newFile);
			}
				break;
			case 2: {
				information(forShowInfos);
			}
				break;
			case 3: {
				findByList(ListOnDevice,newFile);
			}
				break;
			case 4: {
				return 0;
			}
				break;
			default:
				std::cerr << "Invalid Number!\n";
			}
		}
	}
	return EXIT_SUCCESS;
}

