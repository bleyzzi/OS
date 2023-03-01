#include <windows.h>
#include <iostream>
#include <fstream>
#include "employee.h"
#include <conio.h>
#include <string>

void startProcess(char* buffer) {
	STARTUPINFO si;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(si);
	PROCESS_INFORMATION pi;
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));

	if (!CreateProcess(NULL, buffer, NULL, NULL, FALSE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi))
	{
		std::cout << "\nERROR: Unable to open process\n";
		std::cout << "Press any key to exit...";
		system("pause");
	}

	WaitForSingleObject(pi.hProcess, INFINITE);
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
}

int main()
{
	char binary_file_name[256];

	std::cout << "Enter binary file name: ";
	std::cin.getline(binary_file_name, 256);
	int records_num = 0;
	std::cout << "Enter the number of records: ";
	std::cin >> records_num;
	std::cin.ignore();

	char buffer[1000];
	sprintf_s(buffer, "%s %s %d", "creator.exe", binary_file_name, records_num);
	startProcess(buffer);

	std::cout << "Information in binary file:" << std::endl;
	std::ifstream fin(binary_file_name, std::ios::binary);
	fin.read((char *)&records_num, sizeof(int));
	employee *records = new employee[records_num];

	for (int i = 0; i < records_num; i++)
	{
		fin.read((char *)&records[i], sizeof(employee));
	}

	std::cout << records[0].num << " " << records[0].name << " " << records[0].hours;
	for (int i = 1; i < records_num; i++)
	{
		std::cout << std::endl
			 << records[i].num << " " << records[i].name << " " << records[i].hours;
	}

	delete[] records;
	fin.close();

	char output_file_name[256];
	std::cout << "\n\nEnter output file name: ";
	std::cin.getline(output_file_name, 256);
	double salary_per_hour = 0.0;
	std::cout << "Enter salary value per one hour: ";
	std::cin >> salary_per_hour;

	buffer[0] = '\0';
	sprintf_s(buffer, "%s %s %s %lf", "reporter.exe", binary_file_name, output_file_name, salary_per_hour);
	startProcess(buffer);
	
	std::ifstream finReportInfo(output_file_name);

	std::cout << std::endl
		 << "Information in output file:" << std::endl;
	char str[1000];
	for (int i = 0; i < records_num; i++)
	{
		finReportInfo.getline(str, 1000);
		for (int i = 0; str[i] != '\0'; i++)
			printf("%c", str[i]);
		std::cout << std::endl;
	}
	finReportInfo.close();
	return 0;
}