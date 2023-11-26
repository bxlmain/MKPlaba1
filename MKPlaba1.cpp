#define _USE_MATH_DEFINES
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib> 
#include <string> 
#include <ctime> 

using namespace std;
//обозначим нужные нам константы
const double e = 0.8276646992;
const double eps = 0.0001;

double OrbitEccentricity(double E) {  //формула эксцентриситета орбиты
    return atan(sqrt((1 + e) / (1 - e)) * tan(E / 2)) * 2;
}

double IterationMethod(double Efut, double En, double M) {  //метод итерации
    if (fabs(En - Efut) < eps)
    {
        cout << Efut << endl;
        return Efut;
    }
    else
    {
        return IterationMethod(e * sin(Efut) + M, Efut, M);
    }
}

double HalfDivisionMethod(double a, double b, double M) {   //метод половинного деления
    if (fabs(b - a) < 2 * eps * fabs(((a + b) / 2) - e * sin((a + b) / 2) - M) < eps)
    {
        return b + a / 2;
    }
    else if ((a - e * sin(a) - M) * (((a + b) / 2) - e * sin((a + b) / 2) - M) < 0)
    {
        return HalfDivisionMethod(a, (a + b) / 2, M);
    }
    else
    {
        return HalfDivisionMethod((a + b) / 2, b, M);
    }
}


double GoldenRatioMethod(double a, double b, double X, double M) {   //метод золотого сечения
    if (fabs(b - a) < 2 * eps * fabs(((a + b) / 2) - e * sin((a + b) / 2) - M) < eps)
    {
        return a + (b - a) / X;
    }
    else if ((a - e * sin(a) - M) * (((a + b) / 2) - e * sin((a + b) / 2) - M) < 0)
    {
        return GoldenRatioMethod(a, a + (b - a) / X, X, M);
    }
    else
    {
        return GoldenRatioMethod(a + (b - a) / X, b, X, M);
    }
}


double NTMethod(double dif, double E, double M) { //метод Ньютона
    if (dif < eps)
    {
        return E - dif;
    }
    else
    {
        return GoldenRatioMethod((E - e * sin(E) - M) / ((eps - e * sin(E + eps) - e * sin(E)) / eps), E - (E - e * sin(E) - M) / ((eps - e * sin(E + eps) - e * sin(E)) / eps), M);
    }
}

int main() {
    ofstream outputFile;
    ifstream inputFile;
    outputFile.open("IterationMethod.txt");
    if (outputFile.is_open()) {
  
        for (int i = 0; i <= 360; i++)
        {
            double E1 = e * sin(i * 2 * M_PI / 360) + (i * 2 * M_PI / 360);
            double E0 = i * 2 * M_PI / 360;
            outputFile << HalfDivisionMethod(E1, E0, i * 2 * M_PI / 360) << endl;
        }
    }
    else {
        cerr << "Не удалось открыть файл" << endl;
    }
    outputFile.close();
    
    inputFile.open("IterationMethod.txt");
    outputFile.open("TIterationMethod.txt");
    if (inputFile.is_open()) {
        for (int i = 0; i <= 360; i++)
        {
            char ch[50];
            inputFile.getline(ch, 50);
            string str = ch;
            char* ptrEnd;
            outputFile << OrbitEccentricity(strtod(ch, &ptrEnd)) << endl;
        }
    }
    else {
        cerr << "Не удалось открыть файл" << endl;
    }
    inputFile.close();
    outputFile.close();

    outputFile.open("HalfDivisionMethod.txt");
    if (outputFile.is_open()) {
        for (int i = 0; i <= 360; i++)
        {
            outputFile << HalfDivisionMethod((i - 10) * 2 * M_PI / 360, (i + 10) * 2 * M_PI / 360, i * 2 * M_PI / 360) << endl;
        }
    }
    else {
        cerr << "Не удалось открыть файл" << endl;
    }
    outputFile.close();
    
    inputFile.open("HalfDivisionMethod.txt");
    outputFile.open("THalfDivisionMethod.txt");
    if (inputFile.is_open()) {
        for (int i = 0; i <= 360; i++)
        {
            char ch[50];
            inputFile.getline(ch, 50);
            string str = ch;
            char* ptrEnd;
            outputFile << OrbitEccentricity(strtod(ch, &ptrEnd)) << endl;
        }
    }
    else {
        cerr << "Не удалось открыть файл" << endl;
    }
    inputFile.close();
    outputFile.close();

    outputFile.open("GoldenRatioMethod.txt");
    if (outputFile.is_open()) {
        for (int i = 0; i <= 360; i++)
        {
            outputFile << GoldenRatioMethod((i - 10) * 2 * M_PI / 360, (i + 10) * 2 * M_PI / 360, (pow(5, 0.5) + 1) / 2, i * 2 * M_PI / 360) << endl;
        }
    }
    else {
        cerr << "Не удалось открыть файл" << endl;
    }
    outputFile.close();
    
    inputFile.open("GoldenRatioMethod.txt");
    outputFile.open("TrueGoldenRatioMethod.txt");
    if (inputFile.is_open()) {
        for (int i = 0; i <= 360; i++)
        {
            char ch[50];
            inputFile.getline(ch, 50);
            string str = ch;
            char* ptrEnd;
            outputFile << OrbitEccentricity(strtod(ch, &ptrEnd)) << endl;
        }
    }
    else {
        cerr << "Не удалось открыть файл" << endl;
    }
    inputFile.close();
    outputFile.close();
    
    outputFile.open("NTMethod.txt");
    if (outputFile.is_open()) {
        for (int i = 0; i <= 360; i++)
        {
            outputFile << GoldenRatioMethod(((i + 20) * 2 * M_PI / 360 - e * sin((i + 20) * 2 * M_PI / 360) - i * 2 * M_PI / 360) / ((eps - e * sin((i + 20) * 2 * M_PI / 360 + eps) - e * sin((i + 20) * 2 * M_PI / 360)) / eps), ((i + 20) * 2 * M_PI / 360, i * 2 * M_PI / 360)) << endl;
        }
    }
    else {
        cerr << "Не удалось открыть файл" << endl;
    }
    outputFile.close();
    
    inputFile.open("NTMethod.txt");
    outputFile.open("TNTMethod.txt");
    if (inputFile.is_open()) {
        for (int i = 0; i <= 360; i++)
        {
            char ch[50];
            inputFile.getline(ch, 50);
            string str = ch;
            char* ptrEnd;
            outputFile << OrbitEccentricity(strtod(ch, &ptrEnd)) << endl;
        }
    }
    else {
        cerr << "Не удалось открыть файл" << endl;
    }
    
    inputFile.close();
    outputFile.close();
    return 0;
}