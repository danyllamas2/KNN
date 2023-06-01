/*
Centro Universitario de Ciencias Exactas e Ingenierias 
Clasificación Inteligente de datos D04
Profesor: Aviña Mendez Jose Antonio
Alumno: Avila Llamas Fausto Daniel
Fecha de ultima actualización: 01/06/2023

                       * * * * * ALGORTIMO KNN * * * * *
El siguiente programa muestra una implemetación basica sobre el algortimo k vecinos más
proximos (KNN). Cuenta con un dataset ya predefinido, el cual indica en base a la edad
y al prestamo, el default status de cada persona, utilizando 0 para NO Y 1 para SI. Se 
ingresan nuevos datos de edad y prestamo para predecir el default status. Para lograrlo,
el alogirtmo empieza calculado la distancia euclidiana entre los puntos, luego procede a
ordenarlos en un vector de manera ascendente y por medio de un valor de K determina con que 
status tiene más coincidencias y por ende el resultado predecido. Finalmente imprime en
pantalla las escuaciones de las distancias euclidianas calculadas y el resultado final.
*/
#include <iostream>
#include <vector> //Para utilizar vectores
#include <cmath> //Para operaciones mátematicas
#include <algorithm> //Para el algortimo sort
#include <string.h> //Para convertir doubles a string

using namespace std;

struct DataPoint {
    vector<double> features;
    int label;
};

// Calculamos la distancia euclidiana entre los puntos.
double euclideanDistance(const vector<double>& point1, const vector<double>& point2) {
    double distance = 0.0;
    double opera;
    for (size_t i = 0; i < point1.size(); ++i) {
        opera = point1[i] - point2[i];
        string m = to_string(opera);
        distance += pow(opera, 2);
    }

    double r = sqrt(distance);
    string d = to_string(distance);
    cout << "ED: √(" << d << "(" << opera << ")^2)" << " = " << r << endl;
    return r;
}

// Algoritmo KNN
int KNN(const vector<DataPoint>& trainingData, const vector<double>& newPoint, int k) {
    // Creamos un vector para almacenar las distancias y utilizamos etiquetas para representar el default.
    vector<pair<double, int>> distancesLabels;

    // Calculamos la distancia entre el nuevo punto y los demás.
    for (const auto& dataPoint : trainingData) {
        double distance = euclideanDistance(dataPoint.features, newPoint);
        distancesLabels.push_back(make_pair(distance, dataPoint.label));
    }

    // Con el método sort ordenamos las distancias de menor a mayor (ascendente).
    sort(distancesLabels.begin(), distancesLabels.end());

    // Realizamos el conteto de las etiquetas más cercanas.
    vector<int> cont(k, 0);
    for (int i = 0; i < k; ++i) {
        cont[distancesLabels[i].second]++;
    }

    // Buscamos la etiqueta a la que corresponde el nuevo punto.
    int maxCont = 0;
    int predictedLabel = -1;
    for (int i = 0; i < k; ++i) {
        if (cont[i] > maxCont) {
            maxCont = cont[i];
            predictedLabel = i;
        }
    }

    return predictedLabel;
}

int main() {

    // Valor de k (sqrt(N))
    int k = 3;

    double a, b;

    // DataSet (Age, Loan, Default)
    vector<DataPoint> trainingData = {
        {{25.0, 40000.0},  0},
        {{35.0, 60000.0},  0}, 
        {{45.0, 80000.0},  0},
        {{20.0, 20000.0},  0},
        {{35.0, 120000.0}, 0},
        {{52.0, 18000.0},  0},
        {{23.0, 95000.0},  1},
        {{40.0, 62000.0},  1},
        {{60.0, 100000.0}, 1},
        {{48.0, 220000.0}, 1},
        {{33.0, 150000.0}, 1}
    };

    // Ingresamos los datos de "Age" y "Loan".
     a = 48.0;
     b = 142000.0;
    vector<double> newPoint = {a, b};

    cout <<"* * * * * IMPLEMENTACIÓN DEL ALGORTIMO KNN * * * * *\n"<<endl;
   
    int predictedLabel = KNN(trainingData, newPoint, k);
    cout << "\nFor age = " << a << " and loan = " << b << endl;
    cout << "Default status: " << predictedLabel << endl;
    return 0;
}