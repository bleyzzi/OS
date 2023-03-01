#include <fstream>
#include "employee.h"

int main(int argc, char *argv[])
{
	std::ifstream fin(argv[1], std::ios::binary);
	std::ofstream fout(argv[2]);
	double salary_per_hour = atof(argv[3]);

	int records_num;
	fin.read((char *)&records_num, sizeof(int));
	employee *records = new employee[records_num];

	for (int i = 0; i < records_num; i++)
	{
		fin.read((char *)&records[i], sizeof(employee));
	}

	for (int i = 0; i < records_num; i++)
	{
		fout << "ID: " << records[i].num << " Name: " << records[i].name << " Hours: " << records[i].hours << " Total salary: " << records[i].hours * salary_per_hour << std::endl;
	}
	fin.close();
	fout.close();

	delete[] records;

	return 0;
}