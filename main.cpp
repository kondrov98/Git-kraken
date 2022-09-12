#include <iostream>
#include <string>
#include <math.h>


class number
{
private:
	short* num;
	short number_of_digits;
public:
	number()
	{

	}

	number(short number_of_digits) : number_of_digits(number_of_digits), num(new short[number_of_digits])
	{
	}

	number(short number_of_digits, short* num) : number_of_digits(number_of_digits), num(num)
	{
		
	}

	short get_number_of_digits()
	{
		return this->number_of_digits;
	}

	void overwriting_mass(short number_of_digits)
	{
		num = new short[number_of_digits];
		this->number_of_digits = number_of_digits;
	}

	void  set_num_from_string(const std::string& str_number)
	{
		num[0] = str_number[0] != '-' ? 0 : -1;
		short i = 1;
		while (i != number_of_digits)
		{
			num[i] = num[0]!=-1 ? str_number[i-1] - '0': str_number[i] - '0';
			i++;
		}
		
	}

	void delete_mass()
	{
		delete[] num;
	}

	void  set_num(short* num, short number_of_digits)
	{
		for (short i = 0; i < number_of_digits; i++)
		{
			this->num[i] = num[i];
		}
	}


	void  print_num()
	{
		short i = 1;
		if(number_of_digits==1)
			std::cout << "0";
		else
		{
			if (num[0] == -1)
			{
				std::cout << "-";
			}
		}

		while (i != this->number_of_digits)
		{
			std::cout << num[i];
			i++;
		}
	} 

	short* get_num()
	{
		return this->num;
	}

	void string_processing(std::string str_number)
	{
		short i = 1;
		while (str_number[i] != '\0')
		{
			i++;
		}
		if (str_number[0] == '-')
			i--;
		number_of_digits = i+1;
	}
	
	friend bool comparing_numbers(number& num_1, number& num_2);

	friend number operator+ (number& num_1, number& num_2);
	

	friend number operator- (number& num_1, number& num_2);



};

number operator+ (number& num_1, number& num_2)
{
	short i = num_1.number_of_digits >= num_2.number_of_digits ? num_1.number_of_digits : num_2.number_of_digits;
	short j = num_1.number_of_digits >= num_2.number_of_digits ? num_2.number_of_digits : num_1.number_of_digits;
	number num_3(i);

	for(short x=i-1;x>=1;x--)
	{
		if (j-1 >= 1)
		{	
			num_3.num[x] = num_1.num[x] + num_2.num[j-1];
				j--;			
		}
		num_1.num[x - 1] += num_3.num[x] / 10;
		num_3.num[x - 1] =  num_1.num[x - 1];
		num_3.num[x] %= 10;
	}


	if (!num_3.num[0])
		num_1.set_num(num_3.num, num_3.number_of_digits);
	else
	{
		num_1.overwriting_mass(num_3.number_of_digits + 1);
		i = num_1.number_of_digits;
		num_1.num[0] = 0;
		for (short x = i-1; x >= 1; x--)
		{
			num_1.num[x] = num_3.num[x-1];
		}
	}
	num_3.delete_mass();
	return num_1;
}

number operator- (number& num_1, number& num_2)
{
	short i = num_1.number_of_digits >= num_2.number_of_digits ? num_1.number_of_digits : num_2.number_of_digits;//наибольшее колличество цифр одного из 2ух чисел
	short j = num_1.number_of_digits >= num_2.number_of_digits ? num_2.number_of_digits : num_1.number_of_digits;//наименьшее колличество цифр одного из 2ух чисел
	number num_3(i);
	for (short x=i-1;x>=1; x--)
	{
		if (j-1 >= 1)
		{
			num_3.num[x] = comparing_numbers(num_1, num_2) ? num_1.num[x] - num_2.num[j-1]: num_2.num[x] - num_1.num[j-1];
			j--;
		}

		if (comparing_numbers(num_1, num_2))
		{
			num_1.num[x - 1] = num_3.num[x] >= 0 ? num_1.num[x - 1] : num_1.num[x - 1] - 1;
		}
		else
		{
			num_2.num[i - 1] = num_3.num[i] >= 0 ? num_2.num[i - 1] : num_2.num[i - 1] - 1;	
		}
		num_3.num[x] = num_3.num[x] >= 0 ? num_3.num[x] : num_3.num[x] + 10;
		num_3.num[x - 1] = comparing_numbers(num_1, num_2) == true ? num_1.num[x - 1] : num_2.num[x - 1];
	}

	if (num_3.num[1])
		num_1.set_num(num_3.num, num_3.number_of_digits);

	else
	{
		short x = 0;
		while (num_3.num[x+1]==0)
		{
			x++;
		}

		num_1.overwriting_mass(num_3.number_of_digits - x);
		i = num_1.number_of_digits;
		num_1.num[0] = 0;

		for (short xi = i - 1; xi >= 1; xi--)
		{
			num_1.num[xi] = num_3.num[xi+x];
		}	
	}
	num_3.delete_mass();
	return num_1;
}





bool comparing_numbers(number& num_1, number& num_2)
{
	short i = num_1.number_of_digits >= num_2.number_of_digits ? num_1.number_of_digits : num_2.number_of_digits;//наибольшее колличество цифр одного из 2ух чисел
	short j = num_1.number_of_digits >= num_2.number_of_digits ? num_2.number_of_digits : num_1.number_of_digits;//наименьшее колличество цифр одного из 2ух чисел
	bool m = 0;

	if (i == j)
	{
		short k = 1;
		while (k != i)
		{
			if (num_1.num[k] > num_2.num[k])
			{
				m++;
				break;
			}
			k++;																															//Проверяем какое число больше num_1 или num_2
		}
	}
	else
	{
		if (num_1.number_of_digits > num_2.number_of_digits)
		{
			m++;
		}
	}
	return m;
}

number summ(number& num_1, number& num_2)
{
	std::cout << "\n(";
	num_1.print_num();
	std::cout << ") + (";
	num_2.print_num();
	std::cout << ") = ";

	if (num_1.get_num()[0] == -1 && num_2.get_num()[0] == -1)
	{
		num_1.get_num()[0] = 0;
		num_2.get_num()[0] = 0;
		num_1=num_1 + num_2;
		num_1.get_num()[0] = -1;
	}
	else
	{
		if ((num_1.get_num()[0] == -1 && num_2.get_num()[0] == 0) || (num_1.get_num()[0] == 0 && num_2.get_num()[0] == -1))
		{		
			num_1.get_num()[0] = 0;
			num_1=comparing_numbers(num_1, num_2) == true ? num_1 - num_2: num_2 - num_1;
			num_1.get_num()[0] = comparing_numbers(num_1, num_2) == true ? -1 : 0;
		}
		else
		{
				num_1=(num_1 + num_2);
		}
	}
	return num_1;
	
}

number difference(number& num_1, number& num_2)
{
	std::cout << "\n(";
	num_1.print_num();
	std::cout << ") - (";
	num_2.print_num();
	std::cout << ") = ";
	if (num_1.get_num()[0] == -1 && num_2.get_num()[0] == -1)
	{
		num_1.get_num()[0] = 0;
		num_2.get_num()[0] = 0;
		num_1 = comparing_numbers(num_1, num_2) == true ? num_1 - num_2 : num_2 - num_1;
		num_1.get_num()[0] = comparing_numbers(num_1, num_2) == true ? -1 : 0;
	}
	else
	{
		if ((num_1.get_num()[0] == -1 && num_2.get_num()[0] == 0)|| (num_1.get_num()[0] == 0 && num_2.get_num()[0] == -1))
		{
			num_1.get_num()[0] = 0;
			num_1 = num_1 + num_2;
			num_1.get_num()[0] = comparing_numbers(num_1, num_2) == true ? 0 : -1;
		}
		else
		{
			num_1 = comparing_numbers(num_1, num_2) == true ? num_1 - num_2: num_2 - num_1;
			num_1.get_num()[0] = comparing_numbers(num_1, num_2) == true ? 0 : -1;
		}
	}

	return num_1;
}


int main()
{
	setlocale(LC_ALL, "Rus");
	while (1)
	{
		std::string number_1;
		std::string number_2;
		std::string number_3;

		std::cout << "\nВведите первое число, или, если хотите закрыть программу, слово \"stop\": ";
		std::cin >> number_1;
		if (number_1 == "stop")
			break;

		std::cout << "\nВведите второе число, или, если хотите закрыть программу, слово \"stop\": ";
		std::cin >> number_2;
		if (number_2 == "stop")
			break;

		
		std::cout << "\nВведите \"+\", если хотите сумму двух чисел, или \"-\", если хотите разность двух чисел, или, если хотите закрыть программу, слово \"stop\": ";
		std::cin >> number_3;
		if (number_3 == "stop")
			break;
		



		number Number_1;
		Number_1.string_processing(number_1);
		Number_1.overwriting_mass(Number_1.get_number_of_digits());
		Number_1.set_num_from_string(number_1);

		number Number_2;
		Number_2.string_processing(number_2);
		Number_2.overwriting_mass(Number_2.get_number_of_digits());
		Number_2.set_num_from_string(number_2);

		if (number_3 == "+")
		{
			Number_1=summ(Number_1, Number_2);
			Number_1.print_num();
		}


		if (number_3 == "-")
		{
			Number_1 = difference(Number_1, Number_2);
			Number_1.print_num();
		}

		if (Number_1.get_num() != Number_1.get_num())
		{
			Number_1.delete_mass();
			Number_2.delete_mass();
		}
		else
		{
			Number_1.delete_mass();
		}
		
		
		std::cout << "\n";
	}
	return 0;
}