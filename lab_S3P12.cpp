#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>

using namespace std;

class Geography
{
    private:
        int id;
        string name;
        string country;
        string type;
        int height;
        double area;
        int population;

    public:
        // Конструктор по умолчанию
        Geography()
            : id(0), name(" "), country(" "), type(" "), height(0), area(0.0), population(0) {}

        // Конструктор с параметрами
        Geography(int id, string name, string country, string type, int height, double area, int population)
            : id(id), name(name), country(country), type(type), height(height), area(area), population(population) {}

        // Методы доступа (геттеры)
        int getId() const { return id; }
        string getName() const { return name; }
        string getCountry() const { return country; }
        string getType() const { return type; }
        int getHeight() const { return height; }
        double getArea() const { return area; }
        int getPopulation() const { return population; }

        // Методы редактирования (сеттеры)
        void setId(int newId) { id = newId; }
        void setName(const string& newName) { name = newName; }
        void setCountry(const string& newCountry) { country = newCountry; }
        void setType(const string& newType) { type = newType; }
        void setHeight(int newHeight) { height = newHeight; }
        void setArea(double newArea) { area = newArea; }
        void setPopulation(int newPopulation) { population = newPopulation; }

        // Метод для отображения данных объекта
        void display() const
        {
            cout << left << setw(5) << "Id" << "|"
                 << setw(25) << "Title" << "|"
                 << setw(15) << "Country" << "|"
                 << setw(15) << "Type" << "|"
                 << setw(10) << "Height" << "|"
                 << setw(15) << "Area" << "|"
                 << setw(20) << "Population"
                 << endl;
            cout << setw(101) << "-----------------------------------------------------------------------------------------------------" << endl;
            cout << left << setw(5) << id << "|"
                 << setw(25) << name << "|"
                 << setw(15) << country << "|"
                 << setw(15) << type << "|"
                 << setw(10) << height << "|"
                 << setw(15) << area << "|"
                 << setw(20) << population
                 << endl;
            cout << setw(101) << "-----------------------------------------------------------------------------------------------------" << endl;
        }
};

// Функция для загрузки данных из файла
Geography* loadData(const string& filename, int& count)
{
    ifstream file(filename);
    
    count = 0;
    int tempCount = 0;
    int id, height, population;
    double area;
    string name, country, type;

    while (file >> id
                >> name
                >> country
                >> type
                >> height
                >> area
                >> population)
    {
        ++tempCount;
    }

    file.close();

    file.open(filename);

    Geography* dataArray = new Geography[tempCount];

    for (int i = 0; i < tempCount; ++i)
    {
        file >> id
             >> name
             >> country
             >> type
             >> height
             >> area
             >> population;
        dataArray[i] = Geography(id, name, country, type, height, area, population);
    }

    file.close();
    count = tempCount;

    cout << endl;
    cout << endl;
    cout << "Данные успешно загружены из файла.\n";
    cout << endl;
    return dataArray;
}

// Функция для создания объекта с помощью конструктора по умолчанию
Geography createObjectDefault()
{
    return Geography();
}

// Функция для создания объекта с помощью конструктора с параметрами
Geography createObjectWithParameters(Geography* dataArray, int& count)
{
    int id, height, population;
    double area;
    string name, country, type;
    string input;

    while (true)
    {
        cout << endl;
        cout << "Введите Id: ";
        cin >> input;
        try
        {
            id = stoi(input);

        bool idExists = false;
            for (int i = 0; i < count; ++i)
            {
                if (dataArray[i].getId() == id)
                {
                    idExists = true;
                    break;
                }
            }

            if (idExists)
            {
                cout << endl;
                cout << "Ошибка: Id уже занят. Повторите ввод.\n";
            }
            else
            {
                break;
            }
        }
        catch (invalid_argument&)
        {
            cout << endl;
            cout << "Ошибка: Id должен быть числом. Повторите ввод.\n";
        }
    }

    cout << endl;
    cout << "Введите название: ";
    cin >> name;
    cout << "Введите страну: ";
    cin >> country;
    cout << "Введите тип объекта: ";
    cin >> type;

    while (true)
    {
        cout << "Введите высоту: ";
        cin >> input;
        try
        {
            height = stoi(input);
            break;
        }
        catch (invalid_argument&)
        {
            cout << endl;
            cout << "Ошибка: высота должна быть числом. Повторите ввод.\n";
            cout << endl;
        }
    }

    while (true)
    {
        cout << "Введите площадь: ";
        cin >> input;
        try
        {
            area = stod(input);
            break;
        }
        catch (invalid_argument&)
        {
            cout << endl;
            cout << "Ошибка: площадь должна быть числом. Повторите ввод.\n";
            cout << endl;
        }
    }

    while (true)
    {
        cout << "Введите население: ";
        cin >> input;
        try
        {
            population = stoi(input);
            break;
        }
        catch (invalid_argument&)
        {
            cout << endl;
            cout << "Ошибка: население должно быть числом. Повторите ввод.\n";
            cout << endl;
        }
    }

    return Geography(id, name, country, type, height, area, population);
}

// Функция для создания массива объектов
Geography* createObjectArray(Geography* dataArray, int& count, int newCount)
{
    Geography* newDataArray = new Geography[count + newCount];

    for (int i = 0; i < count; ++i)
    {
        newDataArray[i] = dataArray[i];
    }

    for (int i = 0; i < newCount; ++i)
    {
        cout << endl;
        cout << "Запись № " << (count + i) << " " << endl;
        newDataArray[count + i] = createObjectWithParameters(dataArray, count);
    }

    count += newCount;
    
    cout << endl;
    cout << "Массив объектов создан:\n";
    cout << endl;
    return newDataArray;
}

// Функция для просмотра данных конкретного объекта
void viewObject(Geography* dataArray, int count)
{
    string input;
    cout << endl;
    cout << "Введите Id объекта для просмотра (0 - " << count - 1 << "): ";
    cin >> input;

    int index;

    try
    {
        index = stoi(input);
    }
    catch (invalid_argument&)
    {
        cout << endl;
        cout << "Ошибка: Id должен быть числом. Возврат в главное меню.\n";
        return;
    }

    if (index >= 0 && index < count)
    {
        cout << endl;
        dataArray[index].display();
    } 
    else
    {
        cout << endl;
        cout << "Некорректный Id. Пожалуйста, введите значение от 0 до " << count - 1 << ".\n";
    }
}

// Функция для редактирования данных конкретного объекта
void editObject(Geography* dataArray, int count)
{
    string input_index;
    cout << endl;
    cout << "Введите Id объекта для редактирования (0 - " << count - 1 << "): ";
    cin >> input_index;

    int index;
    try
    {
        index = stoi(input_index);
    }
    catch (invalid_argument&)
    {
        cout << endl;
        cout << "Ошибка: Id должен быть числом. Возврат в главное меню.\n";
        return;
    }

    if (index >= 0 && index < count)
    {
        string name, country, type, input_height, input_area, input_population;
        int height, population;
        double area;

        cout << endl;
        cout << "Введите новое название: ";
        cin >> name;
        cout << "Введите новую страну: ";
        cin >> country;
        cout << "Введите новый тип объекта: ";
        cin >> type;

        cout << "Введите новую высоту: ";
        cin >> input_height;
        try
        {
            height = stoi(input_height);
        }
        catch (invalid_argument&)
        {
            cout << endl;
            cout << "Ошибка: высота должна быть числом. Возврат в главное меню.\n";
            return;
        }

        cout << "Введите новую площадь: ";
        cin >> input_area;
        try
        {
            area = stod(input_area);
        }
        catch (invalid_argument&)
        {
            cout << endl;
            cout << "Ошибка: площадь должна быть числом. Возврат в главное меню.\n";
            return;
        }

        cout << "Введите новое население: ";
        cin >> input_population;
        try
        {
            population = stoi(input_population);
        }
        catch (invalid_argument&)
        {
            cout << endl;
            cout << "Ошибка: население должно быть числом. Возврат в главное меню.\n";
            return;
        }

        dataArray[index].setName(name);
        dataArray[index].setCountry(country);
        dataArray[index].setType(type);
        dataArray[index].setHeight(height);
        dataArray[index].setArea(area);
        dataArray[index].setPopulation(population);

        cout << endl;
        cout << "Объект успешно обновлен:\n";
        cout << endl;
        dataArray[index].display();
    }
    else
    {
        cout << endl;
        cout << "Некорректный Id. Пожалуйста, введите значение от 0 до " << count - 1 << ".\n";
    }
}

// Функция для просмотра данных всех объектов
void viewData(Geography* dataArray, int count)
{
    cout << left << setw(5) << "Id" << "|"
         << setw(25) << "Title" << "|"
         << setw(15) << "Country" << "|"
         << setw(15) << "Type" << "|"
         << setw(10) << "Height" << "|"
         << setw(15) << "Area" << "|"
         << setw(20) << "Population"
         << endl;
    for (int i = 0; i < count; ++i)
    {
        cout << setw(101) << "-----------------------------------------------------------------------------------------------------" << endl;
        cout << left << setw(5) << dataArray[i].getId() << "|"
             << setw(25) << dataArray[i].getName() << "|"
             << setw(15) << dataArray[i].getCountry() << "|"
             << setw(15) << dataArray[i].getType() << "|"
             << setw(10) << dataArray[i].getHeight() << "|"
             << setw(15) << dataArray[i].getArea() << "|"
             << setw(20) << dataArray[i].getPopulation()
             << endl;
    }
    cout << setw(101) << "-----------------------------------------------------------------------------------------------------" << endl;
}

// Функция для вычисления общей площади объектов
double calculateTotalArea(Geography* dataArray, int count)
{
    double totalArea = 0;
    for (int i = 0; i < count; ++i)
    {
        totalArea += dataArray[i].getArea();
    }
    return totalArea;
}

// Функция для сохранения данных в файл
void saveData(Geography* dataArray, int count, const string& filename)
{
    ofstream file(filename);
    
    for (int i = 0; i < count; ++i)
    {
        file << dataArray[i].getId() << " "
             << dataArray[i].getName() << " "
             << dataArray[i].getCountry() << " "
             << dataArray[i].getType() << " "
             << dataArray[i].getHeight() << " "
             << dataArray[i].getArea() << " "
             << dataArray[i].getPopulation() << endl;
    }

    file.close();
    cout << endl;
    cout << "Данные успешно сохранены в файл: " << filename << endl;
}

int main()
{
    Geography* dataArray = nullptr;
    int count = 0;
    string filename = "geography_data.txt"; 

    dataArray = loadData(filename, count);

    string choice;

    while (true)
    {
        cout << "\nМеню:\n";
        cout << "1. Создать объект с помощью конструктора по умолчанию\n";
        cout << "2. Создать объект с помощью конструктора с параметрами\n";
        cout << "3. Создать массив объектов\n";
        cout << "4. Просмотреть данные конкретного объекта\n";
        cout << "5. Редактировать данные конкретного объекта\n";
        cout << "6. Просмотреть данные всех объектов\n";
        cout << "7. Вычислить общую площадь объектов\n";
        cout << "8. Сохранить данные в файл\n";
        cout << "0. Выход\n";
        cout << endl;
        cout << "Ваш выбор: ";
        cin >> choice;

        if (choice == "1")
        {
            Geography obj = createObjectDefault();
            cout << endl;
            cout << "Объект создан с помощью конструктора по умолчанию:\n";
            cout << endl;
            obj.display();
            continue;
        }
        
        if (choice == "2")
        {
            Geography obj = createObjectWithParameters(dataArray, count);
            cout << endl;
            cout << "Объект создан с помощью конструктора с параметрами:\n";
            cout << endl;
            obj.display();
            continue;
        }
        
        if (choice == "3")
        {
            string input_newCount;
            cout << endl;
            cout << "Введите количество объектов: ";
            cin >> input_newCount;
            try
            {
                int newCount = stoi(input_newCount);
                dataArray = createObjectArray(dataArray, count, newCount);
                viewData(dataArray, count);
            }
            catch (invalid_argument&)
            {
                cout << endl;
                cout << "Ошибка: количесвто объектов должно быть числом. Возврат в главное меню.\n";
            }           
            continue;
        }
        
        if (choice == "4")
        {
            viewObject(dataArray, count);
            continue;
        }
        
        if (choice == "5")
        {
            editObject(dataArray, count);
            continue;
        }
        
        if (choice == "6")
        {
            cout << endl;
            viewData(dataArray, count);
            continue;
        }
        
        if (choice == "7")
        {
            double totalArea = calculateTotalArea(dataArray, count);
            cout << endl;
            cout << "Общая площадь всех объектов: " << totalArea << " км²\n";
            continue;
        }
        
        if (choice == "8")
        {
            cout << endl;
            cout << "Введите имя файла для сохранения данных: ";
            cin >> filename;
            saveData(dataArray, count, filename);
            continue;
        }
        
        if (choice == "0")
        {
            cout << endl;
            cout << "Выход из программы.\n";
            cout << endl;
            exit (0);
        }
        
        else
        {
            cout << endl;
            cout << "Неверный выбор. Попробуйте еще раз.\n";
            continue;
        }
    }

    return 0;
    delete[] dataArray;
}
