#ifndef KRONPROD_H
#define KRONPROD_H

#include <vector>
#include <armadillo>
#include "include/spin/SpinInteractionDefine.h"

using namespace std;
using namespace arma;

/// \defgroup KronProd Kron
///@{

cx_mat Flat(const cx_mat& m);
cx_mat Sharp(const cx_mat& m);
cx_mat CircleC(const cx_mat& m);
typedef cx_mat(MatExpanFunc) (const cx_mat&);

extern MatExpanFunc* FLAT;
extern MatExpanFunc* SHARP;
extern MatExpanFunc* CIRCLEC;

////////////////////////////////////////////////////////////////////////////////
//{{{ KronProd
class KronProd
{
public:
    KronProd();
    KronProd(DIM_LIST dim_list);
    ~KronProd();

    void   fill(INDICES idx, MULTIPLIER coeff, TERM mat);
    cx_mat full();
    DIM_LIST getDimList(){return _dim_list;};

    friend KronProd Expand(const KronProd& kp, MatExpanFunc * exppan_func);
    friend ostream&  operator << (ostream& outs, const KronProd& kp);
protected:
private:
    DIM_LIST   _dim_list;
    INDICES    _spin_index;
    MULTIPLIER _coeff;
    TERM       _mat;
};
//}}}
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//{{{ SumKronProd
class SumKronProd
{
public:
    SumKronProd();
    SumKronProd(const vector<KronProd>& kp_lst);
    ~SumKronProd();

    cx_mat full();
    vector<KronProd> getKronProdList(){return _kron_prod_list;};
    DIM_LIST getDimList(){return _dim_list;};
    
    friend SumKronProd Expand(const SumKronProd& skp, MatExpanFunc * exppan_func);
    friend SumKronProd& operator + (SumKronProd& sum, const SumKronProd skp);
    friend ostream&  operator << (ostream& outs, SumKronProd& skp);
protected:
    DIM_LIST _dim_list;
    vector<KronProd> _kron_prod_list;
private:
};
//}}}
////////////////////////////////////////////////////////////////////////////////

/// @}
#endif

