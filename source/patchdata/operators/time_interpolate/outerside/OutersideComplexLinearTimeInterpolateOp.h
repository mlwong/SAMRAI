//
// File:	OutersideComplexLinearTimeInterpolateOp.h
// Package:	SAMRAI patchdata
// Copyright:   (c) 1997-2005 The Regents of the University of California
// Revision:	$Revision: 173 $
// Modified:	$Date: 2005-01-19 09:09:04 -0800 (Wed, 19 Jan 2005) $
// Description: Linear time interp operator for complex outerside data.
//

#ifndef included_pdat_OutersideComplexLinearTimeInterpolateOp
#define included_pdat_OutersideComplexLinearTimeInterpolateOp

#ifndef included_SAMRAI_config
#include "SAMRAI_config.h"
#endif
#ifndef included_tbox_Pointer
#include "tbox/Pointer.h"
#endif
#ifndef included_String
#include <string>
using namespace std;
#define included_String
#endif
#ifndef included_xfer_TimeInterpolateOperator
#include "TimeInterpolateOperator.h"
#endif

namespace SAMRAI {
    namespace pdat {

/**
 * Class OutersideComplexLinearTimeInterpolateOp<DIM> implements standard
 * linear time interpolation for complex outreside patch data.  Recall
 * that outerside patch data uses the same indices as side-centered data
 * but the data only exists on the sides that coincide with patch boundaries.
 * It is derived from the xfer::TimeInterpolateOperator<DIM> base class.
 * The interpolation uses FORTRAN numerical routines.
 *
 * The findCoarsenOperator() operator function returns true if the input
 * variable is an outerside complex type, and the string is 
 * "STD_LINEAR_TIME_INTERPOLATE".
 * 
 * @see xfer::TimeInterpolateOperator
 */

template<int DIM> class OutersideComplexLinearTimeInterpolateOp 
: public xfer::TimeInterpolateOperator<DIM>
{
public:
   /**
    * Uninteresting default constructor.
    */
   OutersideComplexLinearTimeInterpolateOp();

   /**
    * Uninteresting virtual destructor.
    */
   virtual ~OutersideComplexLinearTimeInterpolateOp<DIM>();

   /**
    * Return true if the variable and name string match the standard
    * complex outreside interpolation; otherwise, return false.
    */
   bool findTimeInterpolateOperator(const tbox::Pointer< hier::Variable<DIM> >& var,
                                    const string &op_name) const;

   /**
    * Perform linear time interpolation between two complex outerside
    * patch data sources and place result in the destination patch data.
    * Time interpolation is performed on the intersection of the destination 
    * patch data and the input box.  The time to which data is interpolated 
    * is provided by the destination data.
    */
   void timeInterpolate(hier::PatchData<DIM>& dst_data,
                        const hier::Box<DIM>& where,
                        const hier::PatchData<DIM>& src_data_old,
                        const hier::PatchData<DIM>& src_data_new) const;

private:

};

}
}
#endif

#ifdef INCLUDE_TEMPLATE_IMPLEMENTATION
#include "OutersideComplexLinearTimeInterpolateOp.C"
#endif
