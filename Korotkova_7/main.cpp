#define _USE_MATH_DEFINES
#include <iostream>
#include <iomanip>

using namespace std;

void to_polar(double x, double y, double& r, double& phi)
{
	r = sqrt(x * x + y * y);

	if (x > 0 && y >= 0)
	{
		phi = atan(y / x);
	}
	else if (x > 0 && y < 0)
	{
		phi = atan(y / x) + 2 * M_PI;
	}
	else if (x < 0)
	{
		phi = atan(y / x) + M_PI;
	}
	else if (x == 0 && y > 0)
	{
		phi = M_PI_2;
	}
	else if (x == 0 && y < 0)
	{
		phi = 3 * M_PI_2;
	}
	else
	{
		phi = 0;
	}

	phi = phi * 180 / M_PI;
}

int max_index(double* mas, int size)
{
	int index = 0;
	double max = mas[0];
	for (int i = 1; i < size; i++)
	{
		if (mas[i] > max)
		{
			index = i;
			max = mas[i];
		}
	}
	return index;
}

int max(double* mas, int size)
{
	int index = max_index(mas, size);
	return mas[index];
}

void read_mas(double* mas, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << "[" << i << "] = ";
		cin >> mas[i];
	}
}

void write_mas(double* mas, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << mas[i] << " ";
	}
	cout << endl;
}

void remove_triplets(double** mas, int& size, double v1, double v2, double v3)
{
	int r = 0;//индекс чтения
	int w = 0;//индекс записи
	double* nmas = new double[size];//новый массив
	while (r < size - 3)
	{
		double t1 = (*mas)[r];
		double t2 = (*mas)[r + 1];
		double t3 = (*mas)[r + 2];
		nmas[w] = t1;
		nmas[w + 1] = t2;
		nmas[w + 2] = t3;
		if (t1 == v1 && t2 == v2 && t3 == v3)//если тройка подходит
		{
			r += 3;//чтение вперёт на 3
		}
		else
		{
			w++;//иначе сдвигаемся на 1 символ
			r++;
		}
	}
	//если в массиве ещё остались числа - они не могут быть тройкой - переписываем просто так
	while (r < size)
	{
		nmas[w] = (*mas)[r];
		w++;
		r++;
	}
	double* m = new double[w];//конечный массив нужной длины
	for (int i = 0; i < w; i++)
	{
		m[i] = nmas[i];
	}
	//сохраняем результат для возврата
	*mas = m;
	size = w;
}


int main()
{
	setlocale(LC_ALL, "russian");
	cout << "Выполнила студентка группы УЗС-111 Короткова Анастасия Игоревна\n";
	cout << "Программа для работы с массивами с помощью функций\n";

	int n = 6;
	double* xs = new double[6]{1, 3, 5, 7, 9, 11};
	double* ys = new double[6]{2, 4, 6, 8, 10, 12};


	double* rs = new double[n];
	double* phis = new double[n];

	for (int i = 0; i < n; i++)
	{
		to_polar(xs[i], ys[i], rs[i], phis[i]);
	}

	int m_r_i = max_index(rs, n); //max_rad_index
	int m_d_i = max_index(phis, n); //max_deg_index

	cout << "Точка с максимальным радиус-вектором: " << m_r_i <<
		": Декартовые(" << setprecision(3) << xs[m_r_i] << "; " << setprecision(3) << ys[m_r_i] << ")" <<
		"; Полярные(" << setprecision(3) << rs[m_r_i] << "; " << setprecision(3) << phis[m_r_i] << ")\n";

	cout << "Точка с максимальным углом: " << m_d_i <<
		": Декартовые(" << setprecision(3) << xs[m_d_i] << "; " << setprecision(3) << ys[m_d_i] << ")" <<
		"; Полярные(" << setprecision(3) << rs[m_d_i] << "; " << setprecision(3) << phis[m_d_i] << ")\n";

	cout << setprecision(3);
	cout << "X: ";
	write_mas(xs, n);
	cout << "Y: ";
	write_mas(ys, n);
	cout << "R: ";
	write_mas(rs, n);
	cout << "PHI: ";
	write_mas(phis, n);

	double v1, v2, v3;
	cout << "Введите тройку чисел для удаления: ";
	cin >> v1 >> v2 >> v3;

	remove_triplets(&xs, n, v1, v2, v3);

	cout << "Элементы удалены\nX: ";
	write_mas(xs, n);

	system("pause");
}
