#include <iostream>
#include <fstream>
#include "employee.h"

int main(int argc, char* argv[])
{
	std::ofstream fout(argv[1], std::ios::binary);

	int records_num = atoi(argv[2]);
	employee* records = new employee[records_num];

	std::cout << "\nType information about " << records_num << " employees:\n" << std::endl;
	for (int i = 0; i < records_num; i++)
	{
		std::cout << "Employee " << (i + 1) << ": ";
		std::cin >> records[i].num >> records[i].name >> records[i].hours;
		std::cout << std::endl;
	}

	fout.write((char*)&records_num, sizeof(int));
	for (int i = 0; i < records_num; i++) {
		fout.write((char*)&records[i], sizeof(employee));
	}

	fout.close();

	delete[] records;

	return 0;
}