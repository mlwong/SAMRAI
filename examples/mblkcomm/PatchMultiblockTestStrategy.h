//
// File:        PatchMultiblockTestStrategy.h
// Package:     SAMRAI tests
// Copyright:   (c) 1997-2005 The Regents of the University of California
// Revision:    $Revision: 1.8 $
// Modified:    $Date: 2004/02/11 23:46:08 $
// Description: Base class for patch data test operations.
//

#ifndef included_hier_PatchMultiblockTestStrategy
#define included_hier_PatchMultiblockTestStrategy

#ifndef included_SAMRAI_config
#include "SAMRAI_config.h"
#endif

#ifdef DEBUG_CHECK_ASSERTIONS
#include <assert.h>
#endif

#ifndef included_tbox_Array
#include "tbox/Array.h"
#endif
#ifndef included_hier_Box
#include "Box.h"
#endif
#ifndef included_hier_BoxArray
#include "BoxArray.h"
#endif
#ifndef included_hier_BoxList
#include "BoxList.h"
#endif
#ifndef included_MultiblockTester
#include "MultiblockTester.h"
#endif
#ifndef included_geom_SkeletonGridGeometry
#include "SkeletonGridGeometry.h"
#endif
#ifndef included_tbox_Database
#include "Database.h"
#endif
#ifndef included_hier_IntVector
#include "IntVector.h"
#endif
#ifndef included_hier_Patch
#include "Patch.h"
#endif
#ifndef included_mblk_MultiblockRefinePatchStrategy
#include "MultiblockRefinePatchStrategy.h"
#endif
#ifndef included_hier_PatchHierarchy
#include "PatchHierarchy.h"
#endif
#ifndef included_tbox_Pointer
#include "Pointer.h"
#endif
#ifndef included_hier_VariableContext
#include "VariableContext.h"
#endif

using namespace SAMRAI;

//class MultiblockTester;

/**
 * Class PatchMultiblockTestStrategy defines an interface for testing specific 
 * patch data transfer operations on individual patches when using 
 * the MultiblockTester class.  This base class provides two member functions
 * for reading test input information.  These are:
 *
 * readVariableInput(): This function reads in a collection of databases,
 * each of which contains parameters for a single variable.  The names of
 * the sub-databases are arbitrary, but must be distinct.  Each variable
 * sub-database has the following input keys:
 *
 * 

 
 * 
 *    - \b  name         variable name string (required)
 *    - \b  depth        optional variable depth (default = 1)
 *    - \b  src_ghosts   optional comm source ghost width (default = 0,0,0)
 *    - \b  dst_ghosts   optional comm dest ghost width (default = 0,0,0)
 *    - \b  coarsen_operator   opt. coarsen op name (default = "NO_COARSEN")
 *    - \b  refine_operator    opt. refine op name (default = "NO_REFINE")
 *
 * 


 *
 * readRefinementInput(): This function reads in a collection of box
 * arrays, each of which describes the region to refine on each level.
 * The key names of the box arrays are arbitrary, but must be distinct. 
 * For example,
 * 
 * 


 *
 *    - \b  level0_boxes   boxes to refine on level zero.
 *    - \b  level1_boxes   boxes to refine on level one.
 *    - \b  ...            etc...
 *
 * 


 * 
 *
 * The pure virtual functions in this class that must be provided by
 * concrete test subclass:
 * \begin{enumerate}
 *    - [registerVariables(...)] register variables with MultiblockTester.
 *    - [initializeDataOnPatch(...)] set patch data on new patch.
 *    - [tagCellsToRefine(...)] tag cells on patch to refine.
 *    - [verifyResults(...)] check results of communication operations.
 * \end{enumerate} 
 *
 * The following virtual functions are given default non-operations in this
 * class so that concrete test subclass can either implement them to test
 * specific functionality or simply ignore.  They are pure virtual in the
 * coarsen and refine patch strategy classes:
 * \begin{enumerate}
 *    - [setPhysicalBoundaryConditions(...)]
 *    - [preprocessRefine(...)]
 *    - [postprocessRefine(...)]
 *    - [preprocessCoarsen(...)]
 *    - [postprocessCoarsen(...)]
 * \end{enumerate}
 */

class PatchMultiblockTestStrategy
{
public:
  /**
   * The constructor initializes variable data arrays to zero length.
   */
   PatchMultiblockTestStrategy();

   /**
    * Virtual destructor for PatchMultiblockTestStrategy.
    */
   virtual ~PatchMultiblockTestStrategy();

   /**
    * Grid geometry access operations.
    */
   void setGridGeometrySize(const int num_blocks)
   {
      d_grid_geometry =
         new tbox::Pointer< geom::SkeletonGridGeometry<NDIM> >[num_blocks];
   }

   void setGridGeometry(
      tbox::Pointer< geom::SkeletonGridGeometry<NDIM> > grid_geom,
      const int n) 
   {
#ifdef DEBUG_CHECK_ASSERTIONS
      assert(!grid_geom.isNull());
#endif

      d_grid_geometry[n] = grid_geom;
   }

   tbox::Pointer< geom::SkeletonGridGeometry<NDIM> > getGridGeometry(
      const int n) const
   {
      return(d_grid_geometry[n]);
   }

   /**
    * Utility functions for managing patch data context.
    */
   void setDataContext(tbox::Pointer<hier::VariableContext> context)
   {
#ifdef DEBUG_CHECK_ASSERTIONS
      assert(!context.isNull());
#endif
      d_data_context = context;
   }

   void setDestinationContext(tbox::Pointer<hier::VariableContext> context)
   {
#ifdef DEBUG_CHECK_ASSERTIONS    
      assert(!context.isNull());
#endif 
      d_dst_context = context;
   }

   void setScratchContext(tbox::Pointer<hier::VariableContext> context)
   {
#ifdef DEBUG_CHECK_ASSERTIONS
      assert(!context.isNull());
#endif
      d_scr_context = context;
   }

   ///
   tbox::Pointer<hier::VariableContext> getDataContext() const
   {
      return(d_data_context);
   }

   ///
   tbox::Pointer<hier::VariableContext> getDestinationContext() const
   {
      return(d_dst_context);
   }

   ///
   tbox::Pointer<hier::VariableContext> getScratchContext() const
   {
      return(d_scr_context);
   }

   void clearDataContext()
   {
      d_data_context.setNull();
   }

   void clearDestinationContext()
   {
      d_dst_context.setNull();
   }

   void clearScratchContext()
   {
      d_scr_context.setNull();
   }

   /**
    * Read variable parameters from input database.
    */
   void readVariableInput(tbox::Pointer<tbox::Database> db);

   /**
    * Read arrays of refinement boxes from input database.
    */
   void readRefinementInput(tbox::Pointer<tbox::Database> db); 

   /**
    * Set tags in cells to refine based on boxes provided in input.
    */
   void tagCellsInInputBoxes(hier::Patch<NDIM>& patch,
                             int level_number,
                             int tag_index);

   /**
    * Virtual functions in interface to user-supplied boundary conditions,
    * coarsen and refine operations.
    */
   virtual void setPhysicalBoundaryConditions(
      hier::Patch<NDIM>& patch,
      const double time,
      const hier::IntVector<NDIM>& gcw) const;

   virtual void fillSingularityBoundaryConditions(
      hier::Patch<NDIM>& patch,
      tbox::List<mblk::MultiblockRefineSchedule<NDIM>::SingularityPatch>&
         singularity_patches,
      const hier::Box<NDIM>& fill_box,
      const hier::BoundaryBox<NDIM>& boundary_box) {}

   ///
   virtual void preprocessRefine(
      hier::Patch<NDIM>& fine,
      const hier::Patch<NDIM>& coarse,
      const tbox::Pointer<hier::VariableContext>& context,
       const hier::Box<NDIM>& fine_box,
       const hier::IntVector<NDIM>& ratio) const;

   ///
   virtual void postprocessRefine(
      hier::Patch<NDIM>& fine,
      const hier::Patch<NDIM>& coarse,
      const tbox::Pointer<hier::VariableContext>& context,
      const hier::Box<NDIM>& fine_box,
      const hier::IntVector<NDIM>& ratio) const;

   ///
   virtual void preprocessCoarsen(
      hier::Patch<NDIM>& coarse,
      const hier::Patch<NDIM>& fine,
      const tbox::Pointer<hier::VariableContext>& context,
      const hier::Box<NDIM>& coarse_box,
      const hier::IntVector<NDIM>& ratio) const;

   ///
   virtual void postprocessCoarsen(
      hier::Patch<NDIM>& coarse,
      const hier::Patch<NDIM>& fine,
      const tbox::Pointer<hier::VariableContext>& context,
      const hier::Box<NDIM>& coarse_box,
      const hier::IntVector<NDIM>& ratio) const; 

   /**
    * This function is called from the MultiblockTester constructor.  Its
    * purpose is to register variables used in the patch data test
    * and appropriate communication parameters (ghost cell widths,
    * coarsen/refine operations) with the MultiblockTester object, which
    * manages the variable storage.
    */
   virtual void registerVariables(MultiblockTester* commtest) = 0;

   /**
    * Virtual function for setting data on new patch in hierarchy.
    *
    * @param src_or_dst Flag set to 's' for source or 'd' for destination
    *        to indicate variables to set data for.
    */
   virtual void initializeDataOnPatch(
      hier::Patch<NDIM>& patch,
      const tbox::Pointer<hier::PatchHierarchy<NDIM> > hierarchy,
      int level_number,
      int block_number,
      char src_or_dst) = 0;

   /**
    * Virtual function for tagging cells to refine on the patch.
    */
   virtual void tagCellsToRefine(
      hier::Patch<NDIM>& patch,
      const tbox::Pointer<hier::PatchHierarchy<NDIM> > hierarchy,
      int level_number,
      int tag_index) = 0;

   /**
    * Virtual function for checking results of communication operations.
    */
   virtual void verifyResults(
      hier::Patch<NDIM>& patch,
      const tbox::Pointer<mblk::MultiblockPatchHierarchy<NDIM> > hierarchy,
      int level_number,
      int block_number) = 0;

protected:
   /*
    * Arrays of information read from input file describing test variables
    */
   tbox::Array<string>    d_variable_src_name;
   tbox::Array<string>    d_variable_dst_name;
   tbox::Array<int>       d_variable_depth;
   tbox::Array<hier::IntVector<NDIM> > d_variable_src_ghosts;
   tbox::Array<hier::IntVector<NDIM> > d_variable_dst_ghosts;
   tbox::Array<string>    d_variable_coarsen_op;
   tbox::Array<string>    d_variable_refine_op;

   /*
    * Arrays of information read from input file describing test variables
    */
   tbox::Array< hier::BoxArray<NDIM> > d_refine_level_boxes;

private:
   tbox::Pointer< geom::SkeletonGridGeometry<NDIM> >* d_grid_geometry;

   tbox::Pointer<hier::VariableContext> d_data_context;
   tbox::Pointer<hier::VariableContext> d_dst_context;
   tbox::Pointer<hier::VariableContext> d_scr_context;

};

#endif
