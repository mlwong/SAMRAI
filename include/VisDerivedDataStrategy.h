//
// File:        VisDerivedDataStrategy.h
// Package:     SAMRAI application utilities
// Copyright:   (c) 1997-2003 The Regents of the University of California
// Revision:    $Revision: 601 $
// Modified:    $Date: 2005-09-06 11:23:15 -0700 (Tue, 06 Sep 2005) $
// Description: Interface for writing user-defined data to either
//              VisIt or Vizamrai file
//

#ifndef included_appu_VisDerivedDataStrategy
#define included_appu_VisDerivedDataStrategy

#ifndef included_SAMRAI_config
#include "SAMRAI_config.h"
#endif
#ifndef included_hier_Box
#include "Box.h"
#endif
#ifndef included_hier_Patch
#include "Patch.h"
#endif
#ifndef included_String
#include <string>
using namespace std;
#define included_String
#endif
#ifndef included_tbox_Utilities
#include "tbox/Utilities.h"
#endif

namespace SAMRAI {
    namespace appu {

/*!
 * @brief Class VisDerivedDataStrategy<DIM> is an abstract base class
 * that defines an interface allowing an VisItDataWriter<DIM> object
 * and/or an CartesianVizamraiDataWriter<DIM> object to generate plot
 * files that contain "derived" quantities; that is, data that does
 * not reside on the hierarchy, but which is derived from data that
 * does reside on the hierarchy.  The derived data may be scalar,
 * vector, or tensor (VisIt only), and cell-centered or node-centered
 * (VisIt only).  A concrete object of this type must be registered
 * with the data writer if any derived variable is registered with the
 * data writer.  The registration of the concrete strategy object may
 * be done independently using the method setDerivedDataWriter()
 * (Vizamrai only) or setDefaultDerivedDataWriter() (VisIt only) from
 * the relevant DataWriter class, or the concrete strategy object may
 * be registered concurrently with the derived variable using the
 * method registerDerivedPlotScalar/Vector/Tensor().
 *
 * The concrete strategy object is responsible for supplying an
 * implementation of the function packDerivedDataIntoDoubleBuffer()
 * which calculates the derived data and writes it into the double
 * precision buffer passed in to it.
 *
 * This class is shared by both VisDataWriter<DIM> and 
 * CartesianVizamraiDataWriter<DIM>.
 *
 * @see appu::VisItDataWriter
 */

template<int DIM> class VisDerivedDataStrategy 
{
public:
   /*!
    * @brief Default constructor for VisDerivedDataStrategy<DIM>.
    */
   VisDerivedDataStrategy();

   /*!
    * @brief Destructor for VisDerivedDataStrategy<DIM>.
    */
   virtual ~VisDerivedDataStrategy<DIM>();

   /*!
    * @brief This function calculates and packs derived
    * cell-centered data to a 1D double precision buffer.  In the case
    * of the VisIt data writer, node-centered data may also be used.
    * It is called once for each component of multicomponent data.
    *
    * The buffer will be already allocated.  This routine is needed to
    * construct data values that are not stored on the hierarchy, but
    * which may be important to visualize.  The data to be packed
    * corresponds to the plot variable that the user has registered
    * with the data writer using
    * registerDerivedPlotScalar/Vector/Tensor() with the string
    * "variable_name".  The data to be packed is derived from the data
    * that lives on the given patch.  The box describes the patch
    * region over which to pack the data.  It is assumed that all data
    * needed to compute the derived quantity exists on the given
    * patch.
    *
    * The method packDerivedDataIntoDoubleBuffer() will be called DIM
    * times for vector data, and DIM*DIM times for tensor data, with
    * the integer "depth_index" argument indicating the particular
    * component of vector to be packed.  For scalar values, the
    * depth_index will be 0.
    *
    * This routine must include ghost data if the ghost_cell_width
    * parameter was set when the derived data was registered. The data
    * must be packed into the buffer in column major order, the
    * ordering used by SAMRAI, i.e. (f(x_0,y_0,z_0), f(x_1,y_0,z_0),
    * f(x_2,y_0,z_0), ...). If the derived data was registered as
    * node-centered, a buffer of node-centered data is expected.
    * Derived data need not be defined on all patches.  It is the
    * responsibility of this routine to determine if data exists on
    * the patch and set the return value of of this routine
    * appropriately: true if the data exists on the patch, false
    * otherwise.
    *
    * @param buffer Double precision array into which derived data is
    *  packed.  
    * @param patch hier::Patch on which to calculate and pack derived data.
    * @param region hier::Box region over which to pack data.  
    * @param variable_name Name identifier for the derived variable as
    *  registered in registerDerivedPlotScalar/Vector/Tensor().
    * @param depth_index For scalar quantities index will be zero.
    *  For vector data, index varies between 0 and DIM-1.  For tensor 
    *  data, index varies from 0 (DIM*DIM)-1.  
    * @return Boolean value indicating if derived data defined on this
    *  patch.
    */
   virtual bool packDerivedDataIntoDoubleBuffer(
      double *buffer,
      const hier::Patch<DIM>& patch,
      const hier::Box<DIM>& region,
      const string& variable_name,
      int   depth_index) = 0;
   };

}
}
#endif

#ifdef INCLUDE_TEMPLATE_IMPLEMENTATION
#include "VisDerivedDataStrategy.C"
#endif
