
#include <iostream>
#include <vector>
using namespace std;

double qx(double x) {
    return -sqrt(x + 1);
}
double px(double x) {
    return -0.5 / (x + 1);
}
double fx(double x) {
    return -2 * (x + 1) * (x + 1);
}
double ux(double x) {
    return 2 * sqrt((x + 1) * (x + 1) * (x + 1));
}
int main()
{
    setlocale(LC_ALL, "Russian");
    double a = 0;
    double b = 1;
    //Краевые условия
    double d1 = -1;
    double d2 = 1;
    double d = 1;

    double e1 = sqrt(2);
    double e2 = -e1;
    double e = 2;

    //кол-во узлов
    const int n = 100;
    //шаг
    double h = (b - a) / n;

    //массивы для трехдиагональной матрицы
    double aa[n + 1];
    double bb[n + 1];
    double cc[n + 1];
    double ff[n + 1];
    double t[n + 1];
    double beti[n + 1];
    double ai[n + 1];
    double u [n + 1];
    for (int i = 0; i <= n; i++)
    {
        t[i] = a + h * i;
        aa[i] = 1 - px(t[i]) * h / 2;
        bb[i] = 1 + px(t[i]) * h / 2;
        cc[i] = 2 - qx(t[i]) * h * h;
        ff[i] = h * h * fx(t[i]);
    }    
    ai[1] = d2 / (d2 - d1 * h);
    beti[1] = -(d * h) / (d2 - d1 * h);
    
    //Прямой ход метода прогонки
    for (int i = 1; i <= n-1; i++)
    {
        ai[i + 1] = bb[i] / (cc[i] - ai[i] * aa[i]);
        beti[i + 1] = (aa[i] * beti[i] - ff[i]) / (cc[i] - ai[i] * aa[i]);
    }

    u[n] = (e2 * beti[n] + e * h) / (e2 + h * e1 - e2 * ai[n]);    
    //Обратный
    for (int i = n-1; i >=0; i--)
    {
        u[i] = (ai[i + 1] * u[i + 1] + beti[i + 1]);
    }
    double eps = 0;
    
    for (int i = 0; i <= n; i++)
    {
        cout << u[i] << " полученное; " << ux(t[i]) << " истинное\n";
        eps = max(eps, abs((u[i] - ux(t[i]))));
    }
    cout << eps;


    

}


