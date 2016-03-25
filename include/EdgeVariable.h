//
// File:	EdgeVariable.h
// Package:	SAMRAI patch data
// Copyright:	(c) 1997-2005 The Regents of the University of California
// Revision:	$Revision: 173 $
// Modified:	$Date: 2005-01-19 09:09:04 -0800 (Wed, 19 Jan 2005) $
// Description:	hier::Variable class for defining edge centered variables
//

#ifndef included_pdat_EdgeVariable
#define included_pdat_EdgeVariable

#ifndef included_SAMRAI_config
#include "SAMRAI_config.h"
#endif
#ifndef included_tbox_Complex
#include "tbox/Complex.h"
#endif
#ifndef included_String
#include <string>
using namespace std;
#define included_String
#endif
#ifndef included_hier_Variable
#include "Variable.h"
#endif

namespace SAMRAI {
    namespace pdat {

/**
 * Class EdgeVariable<DIM> is a templated variable class used to define 
 * edge-centered quantities on an AMR mesh.  It is templated on the type 
 * of the underlying data (e.g., double, int, bool, etc.).   Edge variable 
 * data is associated with the edges of cells.  Edge data is stored in 
 * DIM arrays, each of which holds values for edges having the same tangent 
 * vector.  For example, a three-dimensional edge variable can be used to 
 * create edge-centered data arrays over a box [l0:u0,l1:u1,l2:u2] that can 
 * be dimensioned as: 
 * \verbatim

     [ l0 : u0 ,
       l1 : u1+1 ,
       l2 : u2+1 , d ]   ,

     [ l0 : u0+1 ,
       l1 : u1 ,
       l2 : u2+1 , d ]   ,

     [ l0 : u0+1 ,
       l1 : u1+1 ,
       l2 : u2 , d ]   ,

 * \endverbatim
 * for the x, y, and z (or 0, 1, 2) face directions, respectively, and
 * where d is the depth index (i.e., number of values at each edge index
 * location).  One- and two- dimensional edge variables define storage 
 * similarly.  For more information on indexing and manipulating edge patch 
 * data objects, see the classes EdgeData<DIM> and EdgeGeometry<DIM>.
 *
 * @see pdat::EdgeData
 * @see pdat::EdgeDataFactory
 * @see hier::Variable
 */

template<int DIM, class TYPE>
class EdgeVariable : public hier::Variable<DIM>
{
public:
   /**
    * Create an edge variable object having properties specified by the
    * name, depth (i.e., number of data values at each index location), and
    * coarse-fine interface representation.  Default arguments are provided 
    * for the last two.  The default depth is one.  The fine boundary representation
    * boolean value indicates which values (either coarse or fine) take
    * precedence during coarsen and refine operations.  The default state
    * is that fine data values take precedence on coarse-fine interfaces.
    */
   EdgeVariable(const string &name,
                      int depth = 1,
                      bool fine_boundary_represents_var = true);

   /**
    * Virtual destructor for edge variable objects.
    */
   virtual ~EdgeVariable<DIM,TYPE>();

   /**
    * Return a boolean value indicating how data for the edge variable will be treated 
    * on coarse-fine interfaces.  True (default case set in constructor) indicates
    * that fine patch values take precedence.  False indicates that values on fine patches
    * at a coarse-fine interface should be interpolated from coarser level values.
    */
   bool fineBoundaryRepresentsVariable() const {return d_fine_boundary_represents_var;}

   /**
    * Return true since the edge data index space extends beyond the interior of 
    * patches.  That is, edge data lives on patch borders.
    */
   bool dataLivesOnPatchBorder() const {return true;}

private:
   bool d_fine_boundary_represents_var; 
 
   EdgeVariable(const EdgeVariable<DIM,TYPE>&);// not implemented
   void operator=(const EdgeVariable<DIM,TYPE>&);	// not implemented

};

}
}
#endif

#ifdef INCLUDE_TEMPLATE_IMPLEMENTATION
#include "EdgeVariable.C"
#endif
