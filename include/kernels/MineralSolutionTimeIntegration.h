/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/*                        Grizzly                               */
/*                                                              */
/*           (c) 2015 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef MINERALSOLUTIONTIMEINTEGRATION
#define MINERALSOLUTIONTIMEINTEGRATION

#include "TimeDerivative.h"

// Forward Declaration
class MineralSolutionTimeIntegration;

/**
 * validParams returns the parameters that this Kernel accepts / needs
 * The actual body of the function MUST be in the .C file.
 */
template<>
InputParameters validParams<MineralSolutionTimeIntegration>();

/**
 * Define the Kernel for a CoupledConvectionReactionSub operator that looks like:
 *
 * storage * delta pressure / delta t
 *
 * This first line is defining the name and inheriting from Kernel.
 */
class MineralSolutionTimeIntegration : public TimeDerivative
{
public:

  MineralSolutionTimeIntegration(const std::string & name, InputParameters parameters);

protected:
  /**
   * Responsible for computing the residual at one quadrature point
   *
   * This should always be defined in the .C
   * @return The residual of mass accumulation of primary species concentration.
   */
  virtual Real computeQpResidual();

  /**
   * Responsible for computing the diagonal block of the preconditioning matrix.
   * This is essentially the partial derivative of the residual with respect to
   * the variable this kernel operates on ("u").
   *
   * Note that this can be an approximation or linearization.  In this case it's
   * not because the Jacobian of this operator is easy to calculate.
   *
   * This should always be defined in the .C
   * @return The diagonal jacobian of mass accumulation of primary species concentration.
   */
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  /// Material property of porosity
  MaterialProperty<Real> & _porosity;


  /// coupling with the minerals subject to kinetic dissolution/precipitation
  /// stochiometric weights for a reactive species in minerals
  std::vector<Real> _sto_v;
  /// Coupled time derivatives of mineral concentrations (stored and computed as Aux variables).
  std::vector<VariableValue *> _dvals_dt;

};

#endif // MINERALSOLUTIONTIMEINTEGRATION
