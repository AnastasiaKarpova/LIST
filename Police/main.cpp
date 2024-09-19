#define _CRT_SECURE_NO_WARNINGS 
#pragma warning (disable: 4326)
#include<iostream>
#include<string>
#include<conio.h>
#include<map>
#include<list>
#include<ctime>
#include<fstream>

using std::cin;
using std::cout;
using std::endl;


#define tab "\t"
#define delimiter "\n--------------------------------------\n"

const std::map<int, std::string> VIOLATIONS =
{
	{1, "Ремень безопасности"},
	{2, "Парковка в неположенном месте"},
	{3, "Пересечение сплошной"},
	{4, "Превышение скорости"},
	{5, "Отсутствие водительского удостоверения"},
	{6, "Отсутствие права управления автомобиля"},
	{7, "Отсутствие страховки"},
	{8, "Проезд на красный"},
	{9, "Выезд на встречную полосу"},
	{10, "Дрифт на перекрестке"},
	{11, "Езда в нетрезвом состоянии"},
	{12, "Оскорбление офицера"},
	{13, "Внесение изменений в конструкцию автомобиля"},
	{14, "Перевозка негабаритного груза"},
	{15, "Превышение максимальной нагрузки на ось"},
	{16, "Перевозка ребенка без кресла"},
};

class Crime
{
	//std::string license_plate;
	int id;
	std::string place;
	tm time;
public:
	/*const std::string& get_license_plate()const
	{
		return license_plate;
	}*/
	int get_violation_id()const
	{
		return id;
	}
	const std::string& get_violation()const
	{
		return VIOLATIONS.at(id);
	}
	const std::string get_time()const
	{
		/*std::string result = asctime(&time);
		result.pop_back();
		return result;*/
		const int SIZE = 256;
		char formatted[SIZE]{};
		strftime(formatted, SIZE, "%R %e.%m.%Y", &time);
		return formatted;
	}
	const time_t get_timestamp()const
	{
		tm copy = time;
		return mktime(&copy);
	}

	/*void set_license_plate(const std::string& license_plate)
	{
		this->license_plate = license_plate;
	}*/
	const std::string& get_place()const
	{
		return place;
	}
	void set_violation_id(int id)
	{
		this->id = id;
	}
	void set_place(const std::string& place)
	{
		this->place = place;
	}
	void set_time(const std::string& time)
	{
		//1)Создаем временную строку для того чтобы пропарсить полученную строку
		char* time_buffer = new char[time.size() + 1] {};
		//2) Копируем полученную строку в бувер:
		strcpy(time_buffer, time.c_str());
		//Функция strcpy(dst, src); копируе содержимое строки источника (src - Source) в строку получателя (dst - Destination)
		
		//3)Создаем массив для хранения элементов времени:
		int time_elements[5]{};
		int i = 0;
		char delimiters[] = ":./ ";
		for (char* pch = strtok(time_buffer, delimiters); pch; pch = strtok(NULL, delimiters))
				time_elements[i++] = std::atoi(pch);
		//Функция std::atoi() 'ASCII - string to int' преобразует строку в целое число
		delete[] time_buffer;
		//4) Сохраняем элементы времени в структуру 'tm':
		
		this->time.tm_hour = time_elements[0];
		this->time.tm_min = time_elements[1];
		this->time.tm_mday = time_elements[2];
		this->time.tm_mon = time_elements[3];
		this->time.tm_year = time_elements[4] - 1900;

		//this -> time = time;
	}
	

	// Constructors:
	Crime(/*const std::string& license_plate*/ int violation_id,
		const std::string& place, const std::string& time)
	{
		//set_license_plate(license_plate);
		this->time = {};  //tm()
		this->set_violation_id(violation_id);
		this->set_place(place);
		this->set_time(time);
#ifdef DEBUG
		cout << "Constructor:\t" << this << endl;
#endif //DEBUG
	}
	~Crime()
	{
#ifdef DEBUG
		cout << "Destructor:\t" << this << endl;
#endif //DEBUG
	}

};


std::ostream& operator<<(std::ostream& os, const Crime& obj)
{
	return os << obj.get_time() << ":\t"  << obj.get_place() << " - " << obj.get_violation();
}
std::ofstream& operator<<(std::ofstream& os, const Crime& obj)
{
	os << obj.get_violation_id() << " " << obj.get_timestamp() << " " << obj.get_place();
	return os;
}


void print(const std::map<std::string, std::list<Crime>>& base);
void save(const std::map<std::string, std::list<Crime>>& base, const std::string& filename);
//void load(const std::map<std::string, std::list<Crime>>& base, const std::string& filename);

//void Save(const std::map<std::string,std::list<Crime>> base, const std::string filename)
//{
//	std::ofstream fout(filename);
//	/*int violation_id;
//	std::string place;
//	std::string time;*/
//	if (fout.is_open())
//	{
//		
//	}
//	fout.close();
//	
//}
//void Load(const std::map<std::string, std::list<Crime>> base, const std::string& filename)
//{
//	std::ifstream fin(filename);
//	/*int violation_id; 
//	std::string place; 
//	std::string time; */
//	if (fin.is_open())
//	{
//		while (!fin.eof())
//		{
//			
//
//		}
//		fin.close();
//	}
//	else
//	{
//		std::cerr << "Error: File not found" << endl;
//	}
//}

void main()
{
	setlocale(LC_ALL, "");
	/*Crime crime(1, "ул. Ленина", "18:10 1.09.2024");
	cout << crime << endl;*/
	std::map<std::string, std::list<Crime>> base =
	{
		{"a777bb", {Crime(1, "ул. Ленина", "18:10 1.09.2024"), Crime(2, "пл. Свободы", "12:25 20.08.2024")}},
		{"a000bb", {Crime(6, "ул. Космонавтов", "17:50 1.08.2024"), Crime(8, "ул. Космонавтов", "17:45 01.08.2024")}},
		{"a001aa", {Crime(10, "ул. Пролетарская", "21:50 1.08.2024"), Crime(9, "ул. Пролетарская", "21:50 1.08.2024"), Crime(11, "ул. Пролетарская", "21:50 1.08.2024"), Crime(12, "ул. Пролетарская", "22:05 1.08.2024")}},
	};
	//Save(base, "Database.txt");
	//Load(base, "Database.txt");
	print(base);
	save(base, "base.txt");
	//load(base, "base.txt");
}

void print(const std::map<std::string, std::list<Crime>>& base)
{
	for (std::map<std::string, std::list<Crime>>::const_iterator map_it = base.begin(); map_it != base.end(); ++map_it)
	{
		cout << map_it->first << ":\n";
		for (std::list<Crime>::const_iterator it = map_it->second.begin(); it != map_it->second.end(); ++it)
		{
			cout << "\t" << *it << endl;
		}
		cout << delimiter << endl;
	}
}
void save(const std::map<std::string, std::list<Crime>>& base, const std::string& filename)
{
	std::ofstream fout(filename);
	for (std::map<std::string, std::list<Crime>>::const_iterator map_it = base.begin(); map_it != base.end(); ++map_it)
	{
		fout << map_it->first << ":\t";
		for (std::list<Crime>::const_iterator it = map_it->second.begin(); it != map_it->second.end(); ++it)
		{
			 
			fout << *it << ", ";
		}
		fout.seekp(-1, std::ios::cur); //Метод seekp(offset, direction) задает позицию курсора записи (р - pur)
		// -1 смещение на один символ обратно, std::ios::cur - показывает что смещение производится от текущей позиции курсора
		fout << ";\n";
	}
	fout.close();
	std::string command = "notepad " + filename;
	system(command.c_str());
}
//void load(const std::map<std::string, std::list<Crime>>& base, const std::string& filename)
//{
//	std::ifstream fin(filename);
//	for (std::map<std::string, std::list<Crime>>::const_iterator map_it = base.begin(); map_it != base.end(); ++map_it)
//	{
//		fin >> map_it->first << ":\n";
//		for (std::list<Crime>::const_iterator it = map_it->second.begin(); it != map_it->second.end(); ++it)
//		{
//			fin >> "\t" << *it << endl;
//		}
//		fin >> delimiter << endl;
//	}
//	fin.close();
//}