#include <assert.h>
#include "include/spin/SpinInteraction.h"
#include "include/kron/KronProd.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////
//{{{ cSpinInteraction
cSpinInteraction::cSpinInteraction()
{
    cout << "default construction function of SpinInteraction." << endl;
}

cSpinInteraction::cSpinInteraction(const vector<cSPIN>& spin_list)
{
    cout << "construction function of SpinInteraction with spin_list." << endl;
    _spin_list=spin_list;
}

cSpinInteraction::~cSpinInteraction()
{
    cout << "default destruction function of SpinInteraction." << endl;
}

void cSpinInteraction::make()
{
    cout << "cSpinInteraction make is called." << endl;
    cout << "domain size: " << _domain.getLength() << endl;
    cout << "matlist nTerm: " << _form.get_nTerm() << endl;

    assert(_domain.getLength() == _form.getLength());
    assert(_domain.getLength() == _coeff.getLength());
    assert(_form.get_nTerm() == _coeff.get_nCoeff() );

    if( !_spin_list.empty() )
        for(auto spin: _spin_list)
            _dim_list.push_back( spin.get_dimension() );

    INDEX_LIST  idxList=_domain.getIndexList();
    MAT_LIST    matList=_form.getMatList();
    COEFF_LIST coefList=_coeff.getCoeffList();

    vector<KronProd> kronProd_list;
    int domainSize = _domain.getLength();
    int nTerm = _form.get_nTerm();
    for(int i=0; i<domainSize; ++i)
        for(int j=0; j<nTerm; ++j)
            if(coefList[i][j] != 0.0)
            {
                KronProd kp=KronProd(_dim_list);
                kp.fill( idxList[i], coefList[i][j], matList[i][j] );
                kronProd_list.push_back( kp );
            }
    _sum_kron_prod=SumKronProd(kronProd_list);
}

ostream&  operator << (ostream& outs, cSpinInteraction& interaction)
{
    cout << interaction._sum_kron_prod << endl;
    return outs;
}
//}}}
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//{{{ SpinDipolarInteraction 
SpinDipolarInteraction::SpinDipolarInteraction()
{
    cout << "default SpinDipolarInteraction constructor. " << endl;
}

SpinDipolarInteraction::SpinDipolarInteraction(const vector<cSPIN>& spin_list)
{
    cout << "constructor of SpinDipolarInteraction with spin_list." << endl;

    int nspin;
    _spin_list=spin_list;

    _domain=SpinPair(spin_list);
    _form=TwoSpinInteractionForm(_domain);
    _coeff=DipolarInteractionCoeff(_domain);

//    cout << _domain << endl;
//    cout << _form << endl;
//    cout << _coeff << endl;
}

SpinDipolarInteraction::~SpinDipolarInteraction()
{
    cout << "default destruction function of SpinDipolarInteraction." << endl;
}
//}}}
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//{{{ SpinZeemanInteraction 
SpinZeemanInteraction::SpinZeemanInteraction()
{
    cout << "default SpinZeemanInteraction constructor. " << endl;
}

SpinZeemanInteraction::SpinZeemanInteraction(const vector<cSPIN>& spin_list, const vec& magB)
{
    cout << "constructor of SpinZeemanInteraction with spin_list." << endl;

    int nspin;
    _spin_list=spin_list;

    _domain=SingleSpin(spin_list);
    _form=SingleSpinInteractionForm(_domain);
    _coeff=ZeemanInteractionCoeff(_domain, magB);

//    cout << _domain << endl;
//    cout << _form << endl;
//    cout << _coeff << endl;
}

SpinZeemanInteraction::~SpinZeemanInteraction()
{
    cout << "default destruction function of SpinZeemanInteraction." << endl;
}
//}}}
////////////////////////////////////////////////////////////////////////////////
