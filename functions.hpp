#pragma once
#ifdef _WIN32
#include <Windows.h>
#endif
#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>

void inputFile(std::ofstream& newFile, const std::string& b, const std::filesystem::directory_entry& dd, const bool& status) {
	time_t now;
	struct tm nowlocal;
	now = time(NULL);
	localtime_s(&nowlocal, &now);

	newFile << std::setfill('0')
		<< "Filename: " << b << "\n"
		<< "Path: " << dd.path() << "\n"
		<< "Date: "
		<< std::setw(2) << nowlocal.tm_mday << "."
		<< std::setw(2) << nowlocal.tm_mon + 1 << "."
		<< nowlocal.tm_year + 1900 << "\n"
		<< "Time: "
		<< std::setw(2) << nowlocal.tm_hour << ":"
		<< std::setw(2) << nowlocal.tm_min << ":"
		<< std::setw(2) << nowlocal.tm_sec << "\n" 
		<< "Copyed: "<< status <<"\n"
		<< std::endl;
	std::cout << "\n";
}
void findFileByName(std::string filenameWhichGetCopy,const std::string& fusion, std::ofstream& newFile) {
	bool status = false;
	system("cls");
	std::cin.ignore(50, '\n');
	std::cout << "Name for File to Copy:\n";
	std::getline(std::cin, filenameWhichGetCopy);

	std::filesystem::path PathCopyTo("D:\\");
	std::filesystem::path p(fusion);
	try {
		if (std::filesystem::exists(p)) {
			std::cout << "\nPath on Device exists!\n";
			std::cout << "\n";
			
			try {
				for (const auto& dd : std::filesystem::recursive_directory_iterator("C:\\", std::filesystem::directory_options::skip_permission_denied | std::filesystem::directory_options::follow_directory_symlink)) {
					//std::cout << dd << std::endl; //faster without.
					if (dd.path().string().find(filenameWhichGetCopy) != std::string::npos) {
						std::cout << "\nFOUND FILE!\n";
						std::cout << dd.path() << std::endl;
						try {
							status = true;
							std::filesystem::copy_file(dd.path(), PathCopyTo / dd.path().filename());
							std::cout << "COPY SUCCESS!\n";
							inputFile(newFile, filenameWhichGetCopy, dd, status);
						}
						catch (const std::exception&) {
							status = false;
							std::cerr << "Copy failed! Find information in FileStealer.txt!\n";
							inputFile(newFile, filenameWhichGetCopy, dd, status);
						}
					}
					
				}
			}
			catch (const std::exception&) {
				std::cerr << "Search failed.\n";
				system("pause");
				system("cls");
				std::cout << "\n";
			}
		}
		else {
			std::cerr << "Path does not exist!\n";
			system("pause");
		}
	}
	catch (const std::exception&) {
		std::cerr << "Search failed - fatal error!\n";
		system("pause");
	}
}
void information(const std::filesystem::path& forShowInfos) {
	system("cls");
	std::cin.ignore(50, '\n');
	std::ifstream dataTXT{ forShowInfos };//Path for Output on console.
	if (dataTXT.fail() || !dataTXT.is_open()) {
		std::cerr << "Fail open FileStealerInfo.txt!\n";
		std::cout << "Back to Menue in 2 Seconds.\n";
		std::cout << "\n";
		Sleep(1000);
		//continue;
	}
	else {
		std::string output;
		while (getline(dataTXT, output)) {
			std::cout << output << std::endl;
		}
		dataTXT.close();
		system("pause");
		system("cls");
	}
}
void findByList(const std::filesystem::path& ListOnDevice, std::ofstream& newFile) {
	bool status = false;
	system("cls");
	std::cin.ignore(50, '\n');
	std::cout << "Edit the List." << "\n" << std::endl;
	std::ifstream dataList{ ListOnDevice };
	std::string output;
	
	std::filesystem::path PathCopyTo("D:\\");
	std::filesystem::path p("D:\\FileStealerInfo.txt");
	while (getline(dataList, output)) {
		try {
			for (const auto& lol : std::filesystem::recursive_directory_iterator("C:\\", std::filesystem::directory_options::skip_permission_denied | std::filesystem::directory_options::follow_directory_symlink)) {
				//cout << lol << std::endl; //faster without.
				if (lol.path().string().find(output) != std::string::npos) {
					std::cout << "\nFOUND FILE!\n";
					std::cout << lol.path() << std::endl;
					try {
						status = true;
						std::filesystem::copy_file(lol.path(), PathCopyTo / lol.path().filename());
						std::cout << "COPY SUCCESS!\n";
						inputFile(newFile, output, lol, status);
					}
					catch (const std::exception&) {
						status = false;
						std::cerr << "Copy failed! Find information in FileStealer.txt!\n";
						inputFile(newFile, output, lol, status);
					}
				}
			}
		}
		catch (const std::exception&) {
			std::cout << output << std::endl;
			std::cerr << "Search failed or file does not exist.\n";
			std::cout << "\n";
		}
	}
	dataList.close();
	system("pause");
	system ("cls");
}
