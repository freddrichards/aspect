/*
  Copyright (C) 2014 by the authors of the ASPECT code.

  This file is part of ASPECT.

  ASPECT is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2, or (at your option)
  any later version.

  ASPECT is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with ASPECT; see the file doc/COPYING.  If not see
  <http://www.gnu.org/licenses/>.
*/



#ifndef __aspect__model_glisovic_forte_old_h
#define __aspect__model_glisovic_forte_old_h

#include <aspect/material_model/interface.h>
#include <aspect/simulator_access.h>

namespace aspect
{
  namespace MaterialModel
  {
    using namespace dealii;

    namespace internal
    {
      class RadialViscosityLookup;
    }

    /**
     * A material model that consists of globally constant values for all
     * material parameters except that the density decays linearly with the
     * temperature and increases linearly with pressure.
     *
     * The model is considered incompressible or compressible, depending on
     * the compressibility.
     *
     * @ingroup MaterialModels
     */
    template <int dim>
    class GlisovicForteOld : public MaterialModel::Interface<dim>, public ::aspect::SimulatorAccess<dim>
    {
      public:

        /**
        * Initialization function. Loads the material data and sets up
        * pointers.
        */
        virtual
        void
        initialize ();

        /**
         * Called at the beginning of each time step and allows the material
         * model to update internal data structures.
         */
        //  virtual void update();

        /**
         * @name Physical parameters used in the basic equations
         * @{
         */
        virtual double viscosity (const double                  temperature,
                                  const double                  pressure,
                                  const std::vector<double>    &compositional_fields,
                                  const SymmetricTensor<2,dim> &strain_rate,
                                  const Point<dim>             &position) const;

        virtual double density (const double temperature,
                                const double pressure,
                                const std::vector<double> &compositional_fields,
                                const Point<dim> &position) const;

        virtual double compressibility (const double temperature,
                                        const double pressure,
                                        const std::vector<double> &compositional_fields,
                                        const Point<dim> &position) const;

        virtual double specific_heat (const double temperature,
                                      const double pressure,
                                      const std::vector<double> &compositional_fields,
                                      const Point<dim> &position) const;

        virtual double thermal_expansion_coefficient (const double      temperature,
                                                      const double      pressure,
                                                      const std::vector<double> &compositional_fields,
                                                      const Point<dim> &position) const;

        virtual double thermal_conductivity (const double temperature,
                                             const double pressure,
                                             const std::vector<double> &compositional_fields,
                                             const Point<dim> &position) const;

        /**
         * @}
         */


        /**
         * @name Qualitative properties one can ask a material model
         * @{
         */

        /**
         * Return whether the model is compressible or not.  Incompressibility
         * does not necessarily imply that the density is constant; rather, it
         * may still depend on temperature or pressure. In the current
         * context, compressibility means whether we should solve the contuity
         * equation as $\nabla \cdot (\rho \mathbf u)=0$ (compressible Stokes)
         * or as $\nabla \cdot \mathbf{u}=0$ (incompressible Stokes).
         */

        virtual bool is_compressible () const;
        /**
         * @}
         */

        /**
         * @name Reference quantities
         * @{
         */
//        virtual double reference_density () const;

        virtual double reference_viscosity () const;

//        virtual double reference_thermal_expansion_coefficient () const;

//        double reference_thermal_diffusivity () const;

        double reference_cp () const;
        /**
         * @}
         */

        /**
        *          * Function to compute the material properties in @p out given the
        *                   * inputs in @p in. If MaterialModelInputs.strain_rate has the length
        *                            * 0, then the viscosity does not need to be computed.
        *                                     */
        virtual
        void
        evaluate(const MaterialModel::MaterialModelInputs<dim> &in,
                 MaterialModel::MaterialModelOutputs<dim> &out) const;

        /**
         * @name Functions used in dealing with run-time parameters
         * @{
         */
        /**
         * Declare the parameters this class takes through input files.
         */
        static
        void
        declare_parameters (ParameterHandler &prm);

        /**
         * Read the parameters this class declares from the parameter file.
         */
        virtual
        void
        parse_parameters (ParameterHandler &prm);
        /**
         * @}
         */

      private:

        double reference_temperature;

        /**
         * The reference surface temperature
         */
        double reference_rho;

        /**
         * The reference viscosity
         */
        double reference_eta;

        /**
         * The constant thermal expansivity
         */
        double thermal_alpha;

        /**
         * The constant specific heat
         */
        double reference_specific_heat;

        /**
         * The constant compressibility.
         */
        double reference_compressibility;

        /**
         * The constant thermal conductivity.
         */
        double k_value;

        /**
         * The minimum value of viscosity that is present in the mantle.
         */
        double min_eta;

        /**
         * The maximum value of viscosity that is present in the mantle.
         */
        double max_eta;

        /**
         * The maximum variations in viscosity at a given depth layer. Plus / Minus that value.
         */
        double max_lateral_eta_variation;

        /**
         * Scaling of temperature into viscosity.
         */
        double thermal_viscosity_exponent;

        /**
         * Average temperature at given depth.
         */
        std::vector<double> avg_temp;

        /**
         * Directory and file for viscosity model.
         */
        std::string datadirectory;
        std::string radial_viscosity_file_name;

        /**
         * Pointer to an object that reads and processes data for the radial
         * viscosity profile.
         */
        std::unique_ptr<internal::RadialViscosityLookup> radial_viscosity_lookup;

        bool thermal_cond_constant;
        bool reference_rho_constant;
        bool thermal_alpha_constant;
//        bool thermal_diff_off;
        bool adiabat_temp;
        double vis_lat_cutoff;
    };

  }
}

#endif
