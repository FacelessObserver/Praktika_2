#include <iostream>
#include <functional>
#include <cmath>
#include <vector>
#include <locale>
#include <ctime>

using namespace std;

void passive_search(function<float(float)> func, float st, float en, float step)
{
    int iters = 0;
    srand(time(0));

    for (float x = st + step; x < en - step; x += step)
    {
        iters ++;
        float prev = func(x - step);
        float curr = func(x);
        float next = func(x + step);

        if (curr > prev && curr > next)
        {
            cout << "Точка максимума\n" << "x = " << x << ", y = " << func(x) << endl;
        }

        else if (curr < prev && curr < next)
        {
            cout << "Точка минимума\n" << "x = " << x << ", y = " << func(x) << endl;
        }
    }
    cout << endl << "Количество итераций: " << iters << endl;
    cout << "Время работы программы: " << clock()/1000.0 << endl << endl;
}

void dividing_in_half(function<float(float)> func, float st, float en, float epsilon, bool minimum)
{
    int iters = 0;
    srand(time(0));
    float alpha_0 = st, beta_0 = en;

    cout << "Пошаговые приближения:" << endl;

    while (true)
    {
        iters ++;
        float delta = (beta_0 - alpha_0) / 10;
        float alpha = (alpha_0 + beta_0) / 2 - delta;
        float beta = alpha + 2 * delta;
        float alpha_1, beta_1, f_alpha = func(alpha), f_beta = func(beta);

        if (minimum ? (f_alpha <= f_beta) : (f_alpha >= f_beta))
        {
            alpha_1 = alpha_0;
            beta_1 = beta;
        }
        else
        {
            alpha_1 = alpha;
            beta_1 = beta_0;
        }

        float x = (alpha_1 + beta_1) / 2;

        if (beta_1 - alpha_1 < epsilon)
        {
            cout << "Итоговое приближение: " << "x = " << x << " y = " << func(x) << endl;
            break;
        }
        else
        {
            cout << "x = " << x << " y = " << func(x) << endl;
            alpha_0 = alpha_1;
            beta_0 = beta_1;
        }
    }
    cout << endl << "Количество итераций: " << iters << endl;
    cout << "Время работы программы: " << clock()/1000.0 << endl << endl;
}

void golden_ratio(function<float(float)> func, float st, float en, float epsilon, bool minimum)
{
    int iters = 0;
    srand(time(0));
    float alpha_0 = st, beta_0 = en;

    const float sqrt_5 = sqrt(5.0);
    const float ratio_1 = 2.0 / (3.0 + sqrt_5);
    const float ratio_2 = 2.0 / (1.0 + sqrt_5);

    cout << "Пошаговые приближения:" << endl;

    while (true)
    {
        iters ++;
        float delta = beta_0 - alpha_0;

        float alpha = alpha_0 + delta * ratio_1;
        float beta = alpha_0 + delta * ratio_2;

        float alpha_1, beta_1;
        float f_alpha = func(alpha);
        float f_beta = func(beta);

        if (minimum ? (f_alpha <= f_beta) : (f_alpha >= f_beta))
        {
            alpha_1 = alpha_0;
            beta_1 = beta;
        }
        else
        {
            alpha_1 = alpha;
            beta_1 = beta_0;
        }

        float x = (alpha_1 + beta_1) / 2;

        if (beta_1 - alpha_1 < epsilon)
        {
            cout << "Итоговое приближение: " << "x = " << x << " y = " << func(x) << endl;
            break;
        }
        else
        {
            cout << "x = " << x << " y = " << func(x) << endl;
            alpha_0 = alpha_1;
            beta_0 = beta_1;
        }
    }
    cout << endl << "Количество итераций: " << iters << endl;
    cout << "Время работы программы: " << clock()/1000.0 << endl << endl;
}

int fibonachi_num(int n)
{
    int F_0 = 1, F_1 = 1;
    for (int i = 2; i <= n; i ++)
    {
        int temp = F_1;
        F_1 = temp + F_0;
        F_0 = temp;
    }
    return F_1;
}

void fibonachi(function<float(float)> func, float st, float en, float epsilon, bool minimum = true)
{
    int iters = 0, N = 1, k = 0;
    srand(time(0));
    float alpha_0 = st, beta_0 = en, delta_0 = en - st;

    cout << "Пошаговые приближения:" << endl;

    while (delta_0 / fibonachi_num(N + 1) > epsilon)
    {
        N ++;
    }

    while (true)
    {
        iters ++;
        float delta = beta_0 - alpha_0;
        int fib_nk = fibonachi_num(N - k), fib_nk_1 = fibonachi_num(N - k - 1), fib_nk_2 = fibonachi_num(N - k - 2);
        float alpha = alpha_0 + (float)fib_nk_2 / fib_nk * delta;
        float beta = alpha_0 + (float)fib_nk_1 / fib_nk * delta;
        float alpha_1, beta_1;
        float f_alpha = func(alpha);
        float f_beta = func(beta);

        if (minimum ? (f_alpha <= f_beta) : (f_alpha >= f_beta))
        {
            alpha_1 = alpha_0;
            beta_1 = beta;
        }
        else
        {
            alpha_1 = alpha;
            beta_1 = beta_0;
        }

        float x = (alpha_1 + beta_1) / 2;

        if (k >= N - 2)
        {
            cout << "Итоговое приближение: " << "x = " << x << " y = " << func(x) << endl;
            break;
        }
        else
        {
            cout << "x = " << x << " y = " << func(x) << endl;
            alpha_0 = alpha_1;
            beta_0 = beta_1;
            k ++;
        }
    }
    cout << endl << "Количество итераций: " << iters << endl;
    cout << "Время работы программы: " << clock()/1000.0 << endl << endl;
}

int main()
{
    setlocale(LC_ALL, "Russian");

    auto Function = [](float x)
    {
        return pow(x, 3) - x + exp(-x);
    };

    cout << "Экстремумы функции x^3 - x + e^(-x)" << endl << endl;

    cout << "МЕТОД ПАССИВНОГО ПОИСКА" << endl << endl;
    passive_search(Function, -5, 3, 0.001);

    cout << "МЕТОД ДЕЛЕНИЯ ОТРЕЗКА ПОПОЛАМ" << endl << endl;
    cout << "Точки минимума" << endl;
    dividing_in_half(Function, -5, -3, 0.000001, true);
    dividing_in_half(Function, 0, 3, 0.000001, true);
    cout << "Точка максимума" << endl;
    dividing_in_half(Function, -3, 0, 0.000001, false);

    cout << "МЕТОД ЗОЛОТОГО СЕЧЕНИЯ" << endl << endl;
    cout << "Точки минимума" << endl;
    golden_ratio(Function, -5, -3, 0.000001, true);
    golden_ratio(Function, 0, 3, 0.000001, true);
    cout << "Точка максимума" << endl;
    golden_ratio(Function, -3, 0, 0.000001, false);

    cout << "МЕТОД ФИБОНАЧИ" << endl << endl;
    cout << "Точки минимума" << endl;
    fibonachi(Function, -5, -3, 0.000001, true);
    fibonachi(Function, 0, 3, 0.000001, true);
    cout << "Точка максимума" << endl;
    fibonachi(Function, -3, 0, 0.000001, false);
    return 0;
}
