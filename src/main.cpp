#include <iostream>
#include <fstream>

const int xN = 20;

using namespace std;


bool check_file(string f_name) {

    int size_w, size_h;  //Размеры матрицы
    int i = 0;           //Счетчик
    int temp;            //Временная переменная для проверки значения
    char symb = ' ';     //Считанный символ


    ifstream ifs(f_name);
    if (!ifs.is_open())  //Открыт ли файл
    {
        cout << "\nОшибка открытия файла \'" << f_name << "\'.\n";
        return false;
    }
    while (symb == ' ') //Проверяем файл на наличие данных
    {
        symb = ifs.get();
        if (ifs.eof()) {
            cout << "\nФайл пуст.\n";
            return false;
        }
    }
    ifs.clear();
    ifs.seekg(0);

    ifs >> size_w;      //Считываем ширину матрицы

    if (ifs.eof()) {
        cout << "\nВ файле недостаточно данных.\n";
        return false;
    }
    ifs >> size_h;      //Считываем высоту матрицы

    do {
        if (ifs.fail()) 
        {
            cout << "\nВ файле обнаружены недопустимые символы.\n";
            return false;
        }
        i++; //Считаем количество переменных
        ifs >> temp;    
    } while (!ifs.eof()); //Проверяем на корректность данных весь файл в данном цикле

    if (i != size_w * size_h) //Проверяем количество элементов в файле
    {
        cout << "\nРазмеры матрицы в файле \'" << f_name << "\' заданы неверно\n";
        return false;
    }
    if ((size_w < 1) || (size_h < 1)) //Проверка заданных в файле размеров матрицы
    {
        cout << "Размер матрицы должен быть больше либо равен 1*1\n";
        return false;
    }
    if ((size_w > xN) || (size_h > xN)) //Поместится ли матрица в массив массивов
    {
        cout << "Матрица слишком велика.\n";
        return false;
    }
    ifs.clear();
    ifs.close();
    return true;
}

void input(string f_name, int matrix[xN+1][xN]) {

    
    int size_w, size_h;
    
    ifstream ifs(f_name);
    ifs >> size_w;    //Считываем размеры
    ifs >> size_h;

    matrix[0][0] = size_w;  //Сохраняем в самом массиве
    matrix[0][1] = size_h;

    for (int i = 1; i <= size_w; i++) {
        for (int j = 0; j < size_h; j++) {
            ifs >> matrix[i][j];            //Считываем всю матрицу
            //cout << matrix[i][j] << ' ';
        }
        //cout << endl;
    }

    ifs.clear();
    ifs.close();
}

int* sum(int matrix[][xN],int sum_el[xN+1]) //Сумма элементов строк
{

    
    int size_w = matrix[0][0];  //Достаем размеры матрицы
    int size_h = matrix[0][1];  
    sum_el[0] = size_w;         

    for (int i = 1; i <= size_w; i++) {
        sum_el[i] = 0;  //Инициализируем элементы массива сумм
        for (int j = 0; j < size_h; j++) {
            sum_el[i] += matrix[i][j];   //Считаем сумму
        }
        cout << "Сумма элементов " << i << "-ой строки:" << sum_el[i] << endl;
    }
    cout << endl;
    return sum_el;
}

int sum_max(int sum_el[xN+1]) //Поиск максимального элемента массива
{
    
    int max_s = sum_el[1];

   

    for (int i = 2; i <= sum_el[0]; i++) {
        if (max_s <= sum_el[i]) {
            max_s = sum_el[i]; //А вот и сам поиск
        }
    }
    cout << "Максимальная сумма = " << max_s << endl;
    return max_s;
    
}

void print_matrix(int matrix[][xN]) //Печать матрицы
{

    int size_w = matrix[0][0]; //Вытаскиваем размеры
    int size_h = matrix[0][1];

    for (int i = 1; i <= size_w; i++) {
        for (int j = 0; j < size_h; j++) {
            cout << matrix[i][j]<<' ';  //Выводим в консоль
        }
        cout << endl;
    }
    cout << endl;
}


int main() //main
{
    setlocale(LC_ALL, "Russian");

    int matrix1[xN+1][xN]; //Массивы массивов. в которых будут матрицы и их размеры
    int matrix2[xN+1][xN];

    const char file_matr_1[] = "test_01(1).txt";
    const char file_matr_2[] = "test_01(2).txt";

    //const char file_matr_1[] = "test_02(1).txt";
    //const char file_matr_2[] = "test_02(2).txt";

    if (check_file(file_matr_1)) {
        cout << "Первая матрица:" << endl;    //Начало работы с перво матрицей

        input(file_matr_1,matrix1);         //Считываем матрицу 1

        print_matrix(matrix1);                //Печать матрицы

        int sum1[xN];
        int max_sum1;

        sum(matrix1,sum1);                  //Суммирование элементов строк матрицы
        max_sum1 = sum_max(sum1);             //Поиск максимального значения

    }
    else {
        cout << "\nВ файле с матрицей 1 обнаружены ошибки. (см. выше) \nПереход к следующей матрице\n\n\n";
    }


    if (check_file(file_matr_2)) {
        cout << "Вторая матрица:" << endl;
        input(file_matr_2,matrix2);   //Считываем матрицу 2
        print_matrix(matrix2);        //Печатаем ее

        int max_sum2;
        int sum2[xN];
     

        sum(matrix2, sum2);    //Считаем сумму строк

        max_sum2 = sum_max(sum2);     //Ищем максимальную сумму.
    }
    else {
        cout << "В файле с матрицей 2 обнаружены ошибки. (см. выше)\n\n";
    }
    return 0;
}