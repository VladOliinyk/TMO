#include <model.h>
#include <iostream>

// the number of minutes when the in queue are 1, 2 and 3 cars;
int t_och1 = 0, t_och2 = 0, t_och3 = 0;

// the number of minutes spent on the service;
int sm_t_obs = 0;

// the number of arrived cars on the service;
int post = 0;

// the number of denial cars of service;
int otk = 0;

// the number of serviced machines;
int obsl = 0;

// the number of minutes of duration of service;
int t_obsl = 0;

int getPost(){
    return post;
}

int getObsl(){
    return obsl;
}
int getOtk(){
    return otk;
}
int getSm_t_obs(){
    return sm_t_obs;
}
int getT_och1(){
    return t_och1;
}
int getT_och2(){
    return t_och2;
}
int getT_och3(){
    return t_och3;
}

int poissonRandom(double expectedValue) {
    int n = 0; //iteration counter
    long double limit;
    long double x; //pseudo random number
    limit = exp(-expectedValue);
    x = rand() / (long double)RAND_MAX;
    while (x > limit) {
        n++;
        x *= rand() / (long double)RAND_MAX;
    }
    return n;
}

void calculate(int k) {
    /*t_och1 = 0;
    t_och2 = 0;
    t_och3 = 0;
    sm_t_obs = 0;
    post = 0;
    otk = 0;
    obsl = 0;
    t_obsl = 0;*/

    // some random value 0 .. 1200 ( t1 = rand() % 1200; )
    long int t1 = 0;
    int t_okon = 0, och = 0;


    for (long int t = 1; t < k; t++) {

        t1 = rand() % PROBABILITY_MAX +1;

        if (och == 1)
            t_och1++;
        if (och == 2)
            t_och2++;
        if (och == 3)
            t_och3++;

        //1
        if ( (t1 >= 1)
             && (t1 <= PROBABILITY_COME)
             && (t_okon == 0)
             && (och >= 0)
             && (och <= 3) )
        {
            t_okon = poissonRandom(65);
            sm_t_obs = sm_t_obs + t_okon;
            obsl++;
            post++;
            continue;
        }

        //2
        if ( (t1 >= 1)
             && (t1 <= PROBABILITY_COME)
             && (t_okon > 0)
             && (och >= 0)
             && (och < 3) )
        {
            t_okon--;
            obsl++;
            och++;
            post++;
            continue;
        }

        //3
        if ( (t1 >= 1)
             && (t1 <= PROBABILITY_COME)
             && (t_okon > 0)
             && (och == 3) )
        {
            t_okon--;
            otk++;
            post++;
            continue;
        }

        //4
        if ( (t1 > PROBABILITY_COME)
             && (t_okon > 0) )
        {
            t_okon--;
            continue;
        }

        //5
        if ( (t1 > PROBABILITY_COME)
             && (t_okon == 0)
             && (och > 0) )
        {
            t_okon = poissonRandom(65);
            sm_t_obs = sm_t_obs + t_okon;
            och--;
            continue;
        }
    }
}
