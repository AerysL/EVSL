#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "blaslapack.h"
#include "def.h"
#include "evsl.h"
#include "internal_proto.h"
#include "string.h"  //for memset
#include "struct.h"
#include "float.h"
/**----------------------------------------------------------------------
 *
 *    Finds the least-square polynomial approximation to function ffun
 *    in interval given by intv
 *
 *    @param[in] *intv Stores the interval of interest \\
 *        intv[0:1] Interval of interest
 *    @param[in] maxDeg Maximum degree of the polynomial appoximation
 *    @param[in] ffun Function to generate an approximation for
 *    @param[in] tol Tolerance for approximation
 *
 *    @param[out] mu
 *    @param[out] c
 *    @param[out] h
 *    @param[out] deg Number of degrees used (elements in mu) 
 *
 *
 *----------------------------------------------------------------------*/

int lsPol1(const double *const intv, const int maxDeg, double (*ffun)(double), const double tol, double* mu, double c, double h, int* deg) {
    const double a = intv[0];
    const double b = intv[1];
    c = (a + b) / 2;
    h = (b - a) / 2;
    //------------------------- Number of points for Gauss-Chebyshev
    //integration
    const int npts = maxDeg * 4;
    const double theta = PI / npts;

    // printf("c: %f", c);
    // printf("h: %f", h);
    // printf("npts: %i", npts);
    double* theti;
    Malloc(theti, npts, double);
    int i = 0;
    for(i = 0; i < npts*2; i+=2) {
        theti[i/2] =  (i + 1) * (PI / (2 * npts));
    }

    double* xi;
    Malloc(xi, npts, double);

    for(i = 0; i < npts; i++) {
        xi[i] = cos(theti[i]);
    }

    double* gi;
    Malloc(gi, npts, double);
    apfun1(c, h, xi, ffun, npts, gi);
    free(xi);

    // ----------------------- Degree loop
    // ----------------------- Each coefficient generated by gauss-Chebyshev
    // quadature.
    int ptsNrm = 300; // Number of points for norm infinity
    Malloc(xi, ptsNrm, double);
    linspace(-1, 1, ptsNrm, xi);
    
    //Compute f(x) once
    
    double* yx;
    Malloc(yx, npts, double);
    apfun1(c, h, xi, ffun, ptsNrm, yx);


    double* yi;
    Malloc(yi, npts, double);
    double* ya; 
    Malloc(ya, npts, double);
    double tt;
    double na;
    //Malloc(na, npts, double);

    int k = 0;
    for(k = 0; k < maxDeg; k++) {
        for(i = 0; i < npts; i++) {
            yi[i] = cos(k * theti[i]);
        }
        double t = 2.0 / npts;
        if(k == 0) {
            t = t * 0.5;
        }
        double sum = 0;
        for(i = 0; i < npts; i++) {
            sum += yi[i] * gi[i];
        }
        mu[k] = t * sum;
        // printf("Sum: %f \n", sum);
        // printf("mu[%i]: %f \n",k, mu[k]);
        chebxPltd(k, mu, ptsNrm, xi, ya);
        // printf("ya: %f \n", ya);
        double max = -DBL_MAX;
        for(i = 0; i < ptsNrm; i++) {
            na = (ya[i] - yx[i]) / yx[i];
            if(na > max) {
                max = na;
            }
        }
        tt = max; //infinity norm of a vector should just be it's max element
        // printf("tt: %f \n", tt);
        if ( tt < tol) {
            deg[0] = k+1;
            break;
        }
    }
    for(k = 0; k < deg[0]; k++) {
        printf("%f \n", mu[k]);
    }
    free(xi);
    free(yi);
    free(ya);
    free(yx);
    free(theti);
    free(gi);

}
