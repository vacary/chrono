//
// PROJECT CHRONO - http://projectchrono.org
//
// Copyright (c) 2013 Project Chrono
// All rights reserved.
//
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file at the top level of the distribution
// and at http://projectchrono.org/license-chrono.txt.
//

#ifndef CHITERATIVEAPGD_H
#define CHITERATIVEAPGD_H

#include "chrono/solver/ChIterativeSolver.h"

namespace chrono {

/// An iterative solver based on Nesterov's
/// Projected Gradient Descent.
/// The problem is described by an LCP of type
///
///    | M -Cq'|*|q|- | f|= |0| ,   c>=0, l>=0, l*c=0;
///    | Cq  0 | |l|  |-b|  |c|
///
/// or similar CCP problem.

class ChApi ChIterativeAPGD : public ChLcpIterativeSolver {
    // Chrono RTTI, needed for serialization
    CH_RTTI(ChIterativeAPGD, ChLcpIterativeSolver);

  protected:
    //
    // DATA
    //

    double residual;
    int nc;
    ChMatrixDynamic<> gamma_hat, gammaNew, g, y, gamma, yNew, r, tmp;

  public:
    //
    // CONSTRUCTORS
    //

    ChIterativeAPGD(int mmax_iters = 1000,     ///< max.number of iterations
                    bool mwarm_start = false,  ///< uses warm start?
                    double mtolerance = 0.0    ///< tolerance for termination criterion
                    )
        : ChLcpIterativeSolver(mmax_iters, mwarm_start, mtolerance, 0.0001){

          };

    virtual ~ChIterativeAPGD(){};

    //
    // FUNCTIONS
    //

    // Performs the solution of the LCP.
    virtual double Solve(ChSystemDescriptor& sysd);

    void ShurBvectorCompute(ChSystemDescriptor& sysd);
    double Res4(ChSystemDescriptor& sysd);

    double GetResidual() { return residual; }

    void Dump_Rhs(std::vector<double>& temp) {
        for (int i = 0; i < r.GetRows(); i++) {
            temp.push_back(r(i, 0));
        }
    }

    void Dump_Lambda(std::vector<double>& temp) {
        for (int i = 0; i < gamma_hat.GetRows(); i++) {
            temp.push_back(gamma_hat(i, 0));
        }
    }
};

} // end namespace chrono

#endif