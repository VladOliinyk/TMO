#include <iostream>
#include <cstdlib>

#include <model.h>

#include <iomanip>

using namespace std;

double power(double x, int y) {
    double result = 1;
    for (int i=1; i <= y; i++) {
        result *= x;
    }
    return result;
}

int main()
{
    setlocale(LC_ALL,"Russian");

    //input
    int pPlace = 3;
    double lambda = 0.85;
    double time_sr = 1.05;

    //calc
    int N = pPlace + 1;

    double mu = 1 / time_sr;
    double rho = lambda / mu;

    cout << endl;
    cout << " 1. The arrival intensity:       lambda = " << lambda << endl
         << " 2. The service flow intensity:      mu = " << mu << endl
         << " 3. The given flow intensity:       rho = " << rho << endl;


    double *P = new double[N+1];
    P[0] = ( 1 - rho ) / ( 1 - power(rho, N+1));
    for (int i = 1; i < N+1; i++) {
        P[i] = power(rho, i) * P[0];
    }

    cout << " 4. The final probability: " << endl;
    for (int i=0; i < N+1; i++) {
        cout << "        : P[" << i << "] = " << P[i] << endl;
    }


    double P_cancel = P[N];
    cout << " 5. The probability of failure: " << P_cancel << endl;

    double q = 1-P_cancel;
    cout << " 6. Relative throughput:  q = " << q << endl;

    double A = lambda * q;
    cout << " 7. Absolute throughput:  A = " << A << endl;


    double numerator = ( rho * (1 - (N+1)) * power(rho, N) + N * power(rho, N+1) );
    double denumerator = ( (1-rho)*(1-power(rho, N+1)) );

    double Ls = numerator / denumerator;

    Ls = 0;
    for (int i=0; i < N+1; i++) {
        Ls+= i * P[i];
    }
    // L[s]:=rho*(1-(N+1)*rho^N+N*rho^(N+1))/((1-rho)*(1-rho^(N+1)));
    cout << " 8. The average number of cars:  Ls = " << Ls << endl;

    double Ws = Ls / (lambda * (1 - P[N]));
    // W[s]:=L[s]/(lambda*(1-P[N]));
    cout << " 9. The average time of stay:    Ws = " << Ws << endl;

    double Wq = Ws - 1/mu;
    // W['q']:=W[s]-1/mu;
    cout << " 10. The average length of stay of the orders in the queue:   Wq = " << Wq << endl;

    double Lq = lambda * (1 - P[N]) * Wq;
    // L['q']:=lambda*(1-P[N])*W['q'];
    cout << " 11. The average number of requests in queue (queue length):  Lq = " << Lq << endl;

    delete [] P;


    cout << endl << endl;


    calculate(5000);
    cout << " Entered the service  " << getPost() << endl;
    cout << "              Served  " << getObsl() << endl;
    cout << "      Denied service  " << getOtk() << endl;
    cout << "    Spent on service  " << getSm_t_obs() << " min." << endl;
    cout << setw(7) << getT_och1() << " min. 1 car in queue " << endl;
    cout << setw(7) << getT_och2() << " min. 2 car in queue" << endl;
    cout << setw(7) << getT_och3() << " min. 3 car in queue" << endl;


    cout << endl;
    cout << "Lets try 50 more times: " << endl;
    for (int i=0; i < 20; i++) {
        calculate(5000);
        cout << "try " << setw(2) << i << "   Entered the service  " << getPost() << endl;
    }


    cout << endl;
    return 0;
}
