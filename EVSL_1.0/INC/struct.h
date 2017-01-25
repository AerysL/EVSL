#ifndef STRUCT_H
#define STRUCT_H

#include <complex.h>

/*- - - - - - - - sparse matrix formats */
// the coordinate (COO) format, 0-based
// ir, jc, vv : triples for all nonzeros (of size nnz)
typedef struct _cooMat {
  int nrows, ncols, nnz, *ir, *jc;
  double *vv;
} cooMat;

// the compressed sparse row (CSR) format, 0-based
// ia: row pointers (of size nrows+1)
// ja: column indices (of size nnz)
// a: numeric values (of size nnz)
// nnz == ia[nrows]
typedef struct _csrMat {
  int nrows, ncols, *ia, *ja;
  double  *a;
} csrMat;


typedef struct _polparams {
  // parameters for polynomial filter - default values set
  // by set_polparams
  // The following are input to find_deg -default values are set
  // by set_pol_par
  int max_deg;        // max allowed degree
  int min_deg ;       // min allowed degree
  int damping;        // 0 = no damping, 1 = Jackson, 2 = Lanczos
  double thresh_ext;  // threshold for accepting polynom. for end intervals 
  double thresh_int;  // threshold for interior intervals 
  // The following are output - i.e., set by set_pol:
  double *mu;         // allocation done by set_pol
  double cc;          // center of interval - used by chebAv
  double dd;          // half-width of interval - used by chebAv
  double gam;         // center of delta function used
  double bar;         // p(theta)>=bar indicates a wanted Ritz 
                      // eigenvalue 
  // The following is used both as input and output for find_pol
  int deg ;           // if deg == 0 before calling find_deg then
                      // the polynomial degree is  computed
                      // internally. Otherwise it is of degree deg.
                      // [and  thresh_ext and thresh_int are not used]
                      // default value=0 - set by call to set_pol_def
} polparams;

typedef struct _ratparams {
  // parameters for rational filter
  int num;            // number of the poles
  int *mulp;          // multiplicity of each pole
  int pow;            // total multiplicites of all poles
  int pw;             // default multiplicity of each pole
  int method;         // type of poles: 0: Cauchy pole, 1: Mid-point
  double beta;        // LS approximation weight
  double aa;          // left endpoint of the interval
  double bb;          // right endpoint of the interval
  double bar;         // rational function value at boundaries
  // The following are output - i.e., set by find_ratf
  complex double *omega;// weights allocation done by find_ratf
  complex double *zk; // locations of poles done by find_ratf
  double cc;          // center of interval
  double dd;          // half-width of interval
} ratparams;

/* solver function prototype:
 * n  is the size  of the system,  br, bz are  the right-hand
 * side (real and  imaginary parts of complex vector),  xr, xz will
 * be the  solution (complex vector),  and "data" contains  all the
 * data  needed  by  the  solver. 
 */
typedef void (*solveShiftFunc)(int n, double *br, double *bz, double *xr, \
              double *xz, void *data);

typedef struct _solveShift {
  solveShiftFunc func;
  void **data;
} solveShift;

#endif
