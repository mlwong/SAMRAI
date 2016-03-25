//
// File:	CartesianCellComplexConservativeLinearRefine.h
// Package:	SAMRAI geometry
// Copyright:   (c) 1997-2005 The Regents of the University of California
// Revision:	$Revision: 173 $
// Modified:	$Date: 2005-01-19 09:09:04 -0800 (Wed, 19 Jan 2005) $
// Description: Conservative linear refine operator for cell-centered 
//              complex data on a Cartesian mesh.
//

#ifndef included_geom_CartesianCellComplexConservativeLinearRefine
#define included_geom_CartesianCellComplexConservativeLinearRefine

#ifndef included_SAMRAI_config
#include "SAMRAI_config.h"
#endif
#ifndef included_hier_Box
#include "Box.h"
#endif
#ifndef included_hier_IntVector
#include "IntVector.h"
#endif
#ifndef included_hier_Patch
#include "Patch.h"
#endif
#ifndef included_tbox_Pointer
#include "tbox/Pointer.h"
#endif
#ifndef included_String
#include <string>
using namespace std;
#define included_String
#endif
#ifndef included_xfer_RefineOperator
#include "RefineOperator.h"
#endif

namespace SAMRAI {
    namespace geom {

/**
 * Class CartesianCellComplexConservativeLinearRefine implements
 * conservative linear interpolation for cell-centered complex patch data 
 * defined over a Cartesian mesh.  In particular, the interpolation is 
 * implemented by applying the standard conservative linear interpolation 
 * to each of the real and imaginary parts of the complex data array 
 * independently.  This operator is derived from the base class 
 * xfer::RefineOperator<DIM>.  The numerical operations for the interpolation 
 * use FORTRAN numerical routines.
 *
 * The findRefineOperator() operator function returns true if the input 
 * variable is cell-centered complex, and the string is 
 * "CONSERVATIVE_LINEAR_REFINE".
 * 
 * @see xfer::RefineOperator
 */

template<int DIM> class CartesianCellComplexConservativeLinearRefine 
: public xfer::RefineOperator<DIM>
{
public:
   /**
    * Uninteresting default constructor.
    */
   CartesianCellComplexConservativeLinearRefine();

   /**
    * Uninteresting virtual destructor.
    */
   virtual ~CartesianCellComplexConservativeLinearRefine<DIM>();

   /**
    * Return true if the variable and name string match cell-centered 
    * complex conservative linear interpolation; otherwise, return false.
    */
   bool findRefineOperator(const tbox::Pointer< hier::Variable<DIM> >& var,
                           const string &op_name) const; 

   /**
    * Return name string identifier of this refinement operator.
    */
   const string& getOperatorName() const;

   /**
    * The priority of cell-centered complex conservative linear is 0.
    * It will be performed before any user-defined interpolation operations. 
    */
   int getOperatorPriority() const;

   /**
    * The stencil width of the conservative linear interpolation operator is 
    * the vector of ones.
    */
   hier::IntVector<DIM> getStencilWidth() const;

   /**
    * Refine the source component on the coarse patch to the destination
    * component on the fine patch using the cell-centered complex conservative
    * linear interpolation operator.  Interpolation is performed on the 
    * intersection of the destination patch and the fine box.   It is assumed 
    * that the coarse patch contains sufficient data for the stencil width of 
    * the refinement operator.
    */
   void refine(hier::Patch<DIM>& fine,
               const hier::Patch<DIM>& coarse,
               const int dst_component,
               const int src_component,
               const hier::Box<DIM>& fine_box,
               const hier::IntVector<DIM>& ratio) const;

private:
   string d_name_id; 

};

}
}
#endif

#ifdef INCLUDE_TEMPLATE_IMPLEMENTATION
#include "CartesianCellComplexConservativeLinearRefine.C"
#endif
