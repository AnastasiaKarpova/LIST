#define _CRT_SECURE_NO_WARNINGS 
#pragma warning (disable: 4326)
#include<iostream>
#include<string>
#include<conio.h>
#include<map>
#include<vector>
#include<list>
#include<ctime>
#include<fstream>
#include<sstream>

using std::cin;
using std::cout;
using std::endl;


#define tab "\t"
#define delimiter "\n--------------------------------------\n"


const std::map<double, std::string> OFFENSES =
{
	{12.1, "Первый/второй раз за год ехал без техосмотра или на неоформленном авто"},
	{12.2, "Ехал на машине с грязным номером"},
	{12.3, "Передал управление машиной человеку без прав"},
	{12.5, "Управлял машиной, на которой неисправен руль или тормоза"},
	{12.6, "Не пристегнулся ремнем сам или один из пассажиров"},
	{12.7, "Управлял авто без водительского удостоверения"},
	{12.8, "Сел за руль нетрезвым / Передал управление ТС нетрезвому водителю"},
	{12.9, "Превысил скорость на 20-40 км/ч / Превысил скорость на 40-60 км/ч"},
	{12.10, "Занимался учебной ездой на магистрали / Нарушил правила на ж/д путях"},
	{12.11, "Остановился на машистрали или ехал медленее 40 км/ч / Неправильная перевозка детей до 11 лет включительно"},
	{12.12, "Ехал на запрещающий сигнал светофора или регулировщика"},
	{12.13, "Выехал на пересечение дорог либо пересек дорогу и создал пробку / Не уступил машине с преимуществом на перекрестке"},
	{12.14, "Развернулся или ехал задним ходом там, где это запрещено / Перед поворотом или разворотом не занял крайний ряд в нужном напралении"},
	{12.15, "Выехал на встречную полосу / Ехал по обочине или пересек колонну авто или людей"},
	{12.16, "Нарушил требования знаков или разметки"},
	{12.17, "Ехал либо остановился на полосе маршрутного транспорта или путях трамваев"},
	{12.19, "Остановился или припарковался там, где это запрещено"},
	{12.20, "Не включил аварийку / Не предупредил сигналом об обгоне"},
	{12.21, "Нарушил порядок буксировкиа: не включил аварийку или ехал быстрее 50 км/ч"},
	{12.23, "Перевозил людей вне кабины авто"},
	{12.26, "Сел за руль нетрезвым и отказался от медосвидетельствования"},
	{12.36, "Говорил по телефону без гарнитуры во время езды"},
};

class PoliceDatabase
{
	double id;
	std::string place;
	tm time;
	std::map<std::string, std::vector<std::string>> offense_list;
public:
	double get_offenses_id()const
	{
		return id;
	}
	const std::string& get_place()const
	{
		return place;
	}
	const std::string& get_time()const
	{
		const int SIZE = 256;
		char formatted[SIZE]{};
		strftime(formatted, SIZE, "%R %e.%m.%Y", &time);
		return formatted;
	}
	const std::string& get_offenses()const
	{
		return OFFENSES.at(id);
	}
	const time_t get_timestamp()const
	{
		tm copy = time;
		return mktime(&copy);
	}
	void set_offenses_id(double id)
	{
		this->id = id;
	}
	void set_place(const std::string& place)
	{
		this->place = place;
	}
	void set_time(const std::string& time)
	{
		char* time_buffer = new char[time.size() + 1] {};
		strcpy(time_buffer, time.c_str());
		int time_elements[5]{};
		int i = 0;
		char delimiters[] = ":./ ";
		for (char* pch = strtok(time_buffer, delimiters); pch; pch = strtok(NULL, delimiters))
			time_elements[i++] = std::atoi(pch);
		delete[] time_buffer;
		this->time.tm_hour = time_elements[0];
		this->time.tm_min = time_elements[1];
		this->time.tm_mday = time_elements[2];
		this->time.tm_mon = time_elements[3];
		this->time.tm_year = time_elements[4] - 1900;
	}
	void set_timestamp(time_t timestamp)
	{
		time = *localtime(&timestamp);
	}
	PoliceDatabase() {}
	PoliceDatabase(double offenses_id,const std::string& place, const std::string& time)
	{
		this->time = {};  //tm()
		this->set_offenses_id(offenses_id);
		this->set_place(place);
		this->set_time(time);
#ifdef DEBUG
		cout << "Constructor:\t" << this << endl;
#endif //DEBUG
	}
	~PoliceDatabase()
	{
#ifdef DEBUG
		cout << "Destructor:\t" << this << endl;
#endif //DEBUG
	}
	void add(const std::string& car_number, const std::string& offense)
	{
		offense_list[car_number].push_back(offense);
	}
	
};
void PrintNumber(std::map<std::string, std::list<PoliceDatabase>>& base, std::string& number)
{
	std::map<std::string, std::list<PoliceDatabase>> range;
	std::map<std::string, std::list<PoliceDatabase>>::const_iterator num;
	
		/*for (std::map<std::string, std::list<PoliceDatabase>>::const_iterator map_it = num.begin(); map_it != base.end(); ++map_it)
		{
			cout << map_it->first << ":\n";
			cout << endl;
		}*/
}
void printrangenumber()
{

}

std::ostream& operator<<(std::ostream& os, const PoliceDatabase& obj)
{
	return os << obj.get_time() << ":\t" << obj.get_place() << " - " << obj.get_offenses();
}
std::ofstream& operator<<(std::ofstream& os, const PoliceDatabase& obj)
{
	os << obj.get_offenses_id() << " " << obj.get_timestamp() << " " << obj.get_place();
	return os;
}
std::istream& operator>>(std::istream& is, PoliceDatabase& obj)
{
	double id;
	time_t timestamp;
	std::string place;
	is >> id >> timestamp;
	std::getline(is, place, ',');
	obj.set_offenses_id(id);
	obj.set_timestamp(timestamp);
	obj.set_place(place);
	return is;
}

void print(const std::map<std::string, std::list<PoliceDatabase>>& base);
void save(const std::map<std::string, std::list<PoliceDatabase>>& base, const std::string& filename);
//std::map<std::string, std::list<PoliceDatabase>> load(const std::string& filename);

void main()
{
	setlocale(LC_ALL, "");
	int i;
	std::string num;
	std::map<std::string, std::list<PoliceDatabase>> base =
	{
		{"п456ае", {PoliceDatabase(12.6, "ул. Некрасова", "10:10 26.07.2024"), PoliceDatabase(12.9, "пл. Победы", "17:30 5.09.2024")}},
		{"т234пс", {PoliceDatabase(12.12, "ул. 2-Сосневская", "12:50 1.06.2024"), PoliceDatabase(12.13, "ул. Космонавтов", "17:42 1.07.2024")}},
		{"р466ом", {PoliceDatabase(12.15, "ул. Александровская", "21:50 4.05.2024"), PoliceDatabase(12.16, "ул. Планетарная", "14:55 10.08.2024"), PoliceDatabase(12.36, "ул. Полетная", "21:56 29.08.2024")}},
		{"о492ои", {PoliceDatabase(12.11, "Южное шоссе", "13:25 4.08.2024"), PoliceDatabase(12.8, "ул. Носова", "14:55 17.08.2024")}},
		{"ч349га", {PoliceDatabase(12.20, "ул. Советская", "21:15 6.03.2024"), PoliceDatabase(12.12, "ул. Клюквино", "9:40 12.08.2024"), PoliceDatabase(12.36, "ул. Полетная", "13:57 16.02.2024")}},
		{"з674пч", {PoliceDatabase(12.36, "ул. Виноградная", "19:35 12.01.2024"), PoliceDatabase(12.16, "пр. Солнечный", "11:18 10.08.2024"), PoliceDatabase(12.36, "пр-т Шереметьевский", "21:56 29.08.2024")}},
	};
	
	cout << "База данных правонарушений ГАИ" << endl;
	cout << endl;
	cout << "Выберите одно из следующих действий" << endl;
	cout << "Вывод базы данных" << endl;
	cout << "Вывод по заданному номеру" << endl;
	cout << "Вывод по даипазону номеров" << endl;
	cout << "Добавить правонарушителя" << endl;
	cout << "Выгрузить базу в файл" << endl;
	cout << "Загрузить базу из файла" << endl;
	cout << endl;

	do
	{
		cin >> i;
		PoliceDatabase car;

		switch (i)
		{
		case 1:
			cout << "Вывод всей базы данных\n" << endl;
			print(base);
			break;

		case 2:
			cout << "Вывод правонарушений по заданному номеру\n" << endl;
			cout << "Укажите номер интересующего Вас автомобиля: " << endl;
			cin >> num;
			//PrintNumber(num);
			break;

		case 3:
			cout << "Вывод правонаруений по диапазону номеров\n" << endl;
			cout << "Укажите диапазон номеров для поиска" << endl;
			printrangenumber();
			break;

		case 4:
			cout << "Добавить правонарушителя\n" << endl;
			car.add("A348CB", (12.3, "ул. Носова", "12:10 13.08.2023"));
			print(base);
			break;

		case 5:
			cout << "Выгрузить базу в файл\n" << endl;
			print(base);
			save(base, "Police database.txt");
			cout << "Файл выгружен" << endl;
			break;

		case 6:
			cout << "Загрузить базу из файла\n" << endl;
			std::map<std::string, std::list<PoliceDatabase>> base;
			std::ifstream fin("Police database.txt");
			if (fin.is_open())
			{
				while (!fin.eof())
				{
					const int SIZE = 102400;
					char buffer[SIZE]{};
					fin.getline(buffer, SIZE);
					cout << buffer << endl;
				}
				fin.close();
			}
			else
			{
				std::cerr << "Error: file not found" << endl;
			}
			cout << "Файл загружен" << endl;
			break;

		}
	} while (i == 0);
}

void print(const std::map<std::string, std::list<PoliceDatabase>>& base)
{
	for (std::map<std::string, std::list<PoliceDatabase>>::const_iterator map_it = base.begin(); map_it != base.end(); ++map_it)
	{
		cout << map_it->first << ":\n";
		for (std::list<PoliceDatabase>::const_iterator it = map_it->second.begin(); it != map_it->second.end(); ++it)
		{
			cout << *it << endl;
		}
		cout << endl;
	}
}
void save(const std::map<std::string, std::list<PoliceDatabase>>& base, const std::string& filename)
{
	std::ofstream fout(filename);
	for (std::map<std::string, std::list<PoliceDatabase>>::const_iterator map_it = base.begin(); map_it != base.end(); ++map_it)
	{
		fout << map_it->first << ":\t";
		for (std::list<PoliceDatabase>::const_iterator it = map_it->second.begin(); it != map_it->second.end(); ++it)
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
//std::map<std::string, std::list<PoliceDatabase>> load(const std::string& filename)
//{
//	std::map<std::string, std::list<PoliceDatabase>> base;
//	std::ifstream fin(filename);
//	if (fin.is_open())
//	{
//		//while (!fin.eof())
//		//{
//		//	std::string licence_plate;
//		//	std::getline(fin, licence_plate, ':');
//		//	fin.ignore();
//		//	std::string database;
//		//	std::getline(fin, database);
//		//	char* sz_buffer = new char[database.size() + 1] {};
//		//	strcpy(sz_buffer, database.c_str());
//		//	char delimiters[] = ",";
//		//	for (char* pch = strtok(sz_buffer, delimiters); pch; pch = strtok(NULL, delimiters))
//		//	{
//		//		//std::cout << pch << "\t";
//		//		//std::string s_crime = pch;
//		//		std::stringstream ss_database(pch, std::ios_base::in | std::ios_base::out);
//		//		PoliceDatabase database(0, "place", "00:00 01.01.2000");
//		//		//ss_crime >> database;
//		//		base[licence_plate].push_back(database);
//		//	}
//		//	cout << endl;
//		//	/*std::string licence_plate;
//		//	std::getline(fin, licence_plate, ':');
//		//	fin.ignore();
//		//	Crime crime(0, "place", "time");
//		//	fin >> crime;
//		//	base[licence_plate].push_back(crime);*/
//		//}
//		while (!fin.eof())
//		{
//			const int SIZE = 102400;
//			char buffer[SIZE]{};
//			fin.getline(buffer, SIZE);
//			cout << buffer << endl;
//		}
//		fin.close();
//	}
//	else
//	{
//		std::cerr << "Error: file not found" << endl;
//	}
//	//return base;
//}
