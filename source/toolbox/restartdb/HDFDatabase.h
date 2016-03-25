//
// File:	HDFDatabase.h
// Package:	SAMRAI toolbox
// Copyright:	(c) 1997-2005 The Regents of the University of California
// Revision:	$Revision: 173 $
// Modified:	$Date: 2005-01-19 09:09:04 -0800 (Wed, 19 Jan 2005) $
// Description:	A database structure that stores HDF5 format data.
//

#ifndef included_tbox_HDFDatabase
#define included_tbox_HDFDatabase

#ifndef included_SAMRAI_config
#include "SAMRAI_config.h"
#endif

/*
************************************************************************
*  THIS CLASS WILL BE UNDEFINED IF THE LIBRARY IS BUILT WITHOUT HDF5
************************************************************************
*/
#ifdef HAVE_HDF5

#define TBOX_HDFDATABSE_MAX_DIMENSION (3)

#ifndef included_tbox_Database
#include "tbox/Database.h"
#endif
#ifndef included_tbox_Array
#include "tbox/Array.h"
#endif
#ifndef included_tbox_DatabaseBox
#include "tbox/DatabaseBox.h"
#endif
#ifndef included_tbox_Complex
#include "tbox/Complex.h"
#endif
#ifndef included_tbox_List
#include "tbox/List.h"
#endif
#ifndef included_tbox_Pointer
#include "tbox/Pointer.h"
#endif
#ifndef included_tbox_PIO
#include "tbox/PIO.h"
#endif
#ifndef included_String
#include <string>
using namespace std;
#define included_String
#endif
#ifndef included_hdf5
#define included_hdf5
#undef RCSID
#include "hdf5.h"
#ifdef inline
#undef inline
#endif
#endif


namespace SAMRAI {
   namespace tbox {


/**
 * Class HDFDatabase implements the interface of the Database
 * class to store data in the HDF5 (Hierarchical Data Format) data format.
 *
 * It is assumed that all processors will access the database in the same
 * manner.  Error reporting is done using the SAMRAI error reporting macros.
 *
 * @see tbox::Database
 */

class HDFDatabase : public Database
{
public:
   /**
    * The HDF database constructor creates an empty database with the
    * specified name.  By default the database will not be associated
    * with a file until it is mounted, using the mount() member function.
    * 
    * When assertion checking is active, the name string must be non-empty.
    */
   HDFDatabase(const string& name);

   /**
    * The database destructor closes the HDF5 group or data file.
    */
   virtual ~HDFDatabase();

   /**
    * Return true if the specified key exists in the database 
    * and false otherwise.  
    * 
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual bool keyExists(const string& key);

   /**
    * Return an array of all keys in the current database.  Note that 
    * no keys from subdatabases contained in the current database
    * will appear in the array.  To get the keys of any other
    * database, you must call this routine for that database. 
    */
   virtual Array<string> getAllKeys();

   /**
    * Return the size of the array associated with the key.  If the key
    * does not exist, then zero is returned.
    *
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual int getArraySize(const string& key);

   /**
    * Return true or false depending on whether the specified key 
    * represents a database entry.  If the key does not exist or if
    * the string is empty, then false is returned. 
    */
   virtual bool isDatabase(const string& key);

   /**
    * Create a new database with the specified key name and return a
    * pointer to it.  A new group with the key name is also created 
    * in the data file. 
    *
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual Pointer<Database> putDatabase(const string& key);

   /**
    * Get the database with the specified key name.  If the specified
    * key does not represent a database entry in the database, then
    * an error message is printed and the program exits.
    * 
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual Pointer<Database> getDatabase(const string& key);

   /**
    * Return true or false depending on whether the specified key
    * represents a boolean entry.  If the key does not exist or if
    * the string is empty, then false is returned.
    */
   virtual bool isBool(const string& key);

   /**
    * Create a boolean scalar entry in the database with the specified
    * key name. 
    * 
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual void putBool(const string& key, const bool& data);

   /**
    * Create a boolean array entry in the database with the specified
    * key name.
    * 
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual void putBoolArray(
      const string& key, const Array<bool>& data);

   /**
    * Create a boolean array entry in the database with the specified
    * key name. 
    * 
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual void putBoolArray(
      const string& key, const bool* const data, const int nelements);

   /**
    * Get a boolean entry in the database with the specified key name.
    * If the specified key does not exist in the database, then an 
    * error message is printed and the program exits.
    *
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual bool getBool(const string& key);

   /**
    * Get a boolean entry in the database with the specified key name.
    * If the specified key does not exist in the database, then the default
    * value is returned.  
    *
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual bool getBoolWithDefault(
      const string& key, const bool& defaultvalue);

   /**
    * Get a boolean entry from the database with the specified key
    * name.  If the specified key does not exist in the database, 
    * then an error message is printed and the program exits.
    *
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual Array<bool> getBoolArray(const string& key);

   /**
    * Get a boolean entry from the database with the specified key
    * name.  If the specified key does not exist in the database,
    * or the given number of elements does no match the number of
    * elements in the database, then an error message is printed and 
    * the program exits.  
    *
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual void getBoolArray(
      const string& key, bool* data, const int nelements);

   /**
    * Return true or false depending on whether the specified key
    * represents a box entry.  If the key does not exist or if
    * the string is empty, then false is returned.
    */
   virtual bool isDatabaseBox(const string& key);

   /**
    * Create a box scalar entry in the database with the specified
    * key name.  
    * 
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual void putDatabaseBox(const string& key, const DatabaseBox& data);

   /**
    * Create a box array entry in the database with the specified
    * key name. 
    * 
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual void putDatabaseBoxArray(
      const string& key, const Array<DatabaseBox>& data);

   /**
    * Create a box array entry in the database with the specified
    * key name. 
    * 
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual void putDatabaseBoxArray(
      const string& key, const DatabaseBox* const data, const int nelements);

   /**
    * Get a box entry in the database with the specified key name.
    * If the specified key does not exist in the database, 
    * then an error message is printed and the program exits.
    * 
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual DatabaseBox getDatabaseBox(const string& key);

   /**
    * Get a box entry in the database with the specified key name.
    * If the specified key does not exist in the database, then the default
    * value is returned.  
    *
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual DatabaseBox getDatabaseBoxWithDefault(
      const string& key, const DatabaseBox& defaultvalue);

   /**
    * Get a box entry from the database with the specified key
    * name.  If the specified key does not exist in the database,
    * then an error message is printed and the program exits.
    *
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual Array<DatabaseBox> getDatabaseBoxArray(const string& key);

   /**
    * Get a box entry from the database with the specified key
    * name.  If the specified key does not exist in the database,
    * or the given number of elements does no match the number of
    * elements in the database, then an error message is printed and 
    * the program exits.
    *
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual void getDatabaseBoxArray(
      const string& key, DatabaseBox* data, const int nelements);

   /**
    * Return true or false depending on whether the specified key
    * represents a char entry.  If the key does not exist or if
    * the string is empty, then false is returned.
    */
   virtual bool isChar(const string& key);

   /**
    * Create a character scalar entry in the database with the specified
    * key name.  
    * 
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual void putChar(const string& key, const char& data);

   /**
    * Create a character array entry in the database with the specified
    * key name. 
    * 
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual void putCharArray(
      const string& key, const Array<char>& data);

   /**
    * Create a character array entry in the database with the specified
    * key name.  
    * 
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual void putCharArray(
      const string& key, const char* const data, const int nelements);

   /**
    * Get a character entry in the database with the specified key name.
    * If the specified key does not exist in the database, 
    * then an error message is printed and the program exits.
    * 
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual char getChar(const string& key);

   /**
    * Get a character entry in the database with the specified key name.
    * If the specified key does not exist in the database, then the default
    * value is returned.  
    * 
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual char getCharWithDefault(
      const string& key, const char& defaultvalue);

   /**
    * Get a character entry from the database with the specified key
    * name.  If the specified key does not exist in the database, 
    * then an error message is printed and the program exits.
    * 
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual Array<char> getCharArray(const string& key);

   /**
    * Get a character entry from the database with the specified key
    * name.  If the specified key does not exist in the database,
    * or the given number of elements does no match the number of
    * elements in the database, then an error message is printed and 
    * the program exits.
    *
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual void getCharArray(
      const string& key, char* data, const int nelements);

   /**
    * Return true or false depending on whether the specified key
    * represents a complex entry.  If the key does not exist or if
    * the string is empty, then false is returned.
    */
   virtual bool isComplex(const string& key);

   /**
    * Create a complex scalar entry in the database with the specified
    * key name.  
    * 
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual void putComplex(const string& key, const dcomplex& data);

   /**
    * Create a complex array entry in the database with the specified
    * key name.
    * 
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual void putComplexArray(
      const string& key, const Array<dcomplex>& data);

   /**
    * Create a complex array entry in the database with the specified
    * key name.
    * 
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual void putComplexArray(
      const string& key, const dcomplex* const data, const int nelements);

   /**
    * Get a complex entry in the database with the specified key name.
    * If the specified key does not exist in the database 
    * then an error message is printed and the program exits.  
    *
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual dcomplex getComplex(const string& key);

   /**
    * Get a complex entry in the database with the specified key name.
    * If the specified key does not exist in the database, then the default
    * value is returned. 
    *
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual dcomplex getComplexWithDefault(
      const string& key, const dcomplex& defaultvalue);

   /**
    * Get a complex entry from the database with the specified key
    * name.  If the specified key does not exist in the database 
    * then an error message is printed and the program exits.  
    *
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual Array<dcomplex> getComplexArray(const string& key);

   /**
    * Get a complex entry from the database with the specified key
    * name.  If the specified key does not exist in the database,
    * or the given number of elements does no match the number of
    * elements in the database, then an error message is printed and 
    * the program exits.
    *
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual void getComplexArray(
      const string& key, dcomplex* data, const int nelements);

   /**
    * Return true or false depending on whether the specified key
    * represents a double entry.  If the key does not exist or if
    * the string is empty, then false is returned.
    */
   virtual bool isDouble(const string& key);

   /**
    * Create a double scalar entry in the database with the specified
    * key name.
    * 
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual void putDouble(const string& key, const double& data);

   /**
    * Create a double array entry in the database with the specified
    * key name.
    * 
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual void putDoubleArray(
      const string& key, const Array<double>& data);

   /**
    * Create a double array entry in the database with the specified
    * key name.
    * 
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual void putDoubleArray(
      const string& key, const double* const data, const int nelements);

   /**
    * Get a double entry in the database with the specified key name.
    * If the specified key does not exist in the database 
    * then an error message is printed and the program exits.
    *
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual double getDouble(const string& key);

   /**
    * Get a double entry in the database with the specified key name.
    * If the specified key does not exist in the database, then the default
    * value is returned.  
    *
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual double getDoubleWithDefault(
      const string& key, const double& defaultvalue);

   /**
    * Get a double entry from the database with the specified key
    * name.  If the specified key does not exist in the database 
    * then an error message is printed and the program exits.  
    *
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual Array<double> getDoubleArray(const string& key);

   /**
    * Get a double entry from the database with the specified key
    * name.  If the specified key does not exist in the database,
    * or the given number of elements does no match the number of
    * elements in the database, then an error message is printed and 
    * the program exits.
    *
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual void getDoubleArray(
      const string& key, double* data, const int nelements);

   /**
    * Return true or false depending on whether the specified key
    * represents a float entry.  If the key does not exist or if
    * the string is empty, then false is returned.
    */
   virtual bool isFloat(const string& key);

   /**
    * Create a float scalar entry in the database with the specified
    * key name.
    * 
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual void putFloat(const string& key, const float& data);

   /**
    * Create a float array entry in the database with the specified
    * key name.
    * 
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual void putFloatArray(
      const string& key, const Array<float>& data);

   /**
    * Create a float array entry in the database with the specified
    * key name.
    * 
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual void putFloatArray(
      const string& key, const float* const data, const int nelements);

   /**
    * Get a float entry in the database with the specified key name.
    * If the specified key does not exist in the database 
    * then an error message is printed and the program exits.
    * 
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual float getFloat(const string& key);

   /**
    * Get a float entry in the database with the specified key name.
    * If the specified key does not exist in the database, then the default
    * value is returned.  
    * 
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual float getFloatWithDefault(
      const string& key, const float& defaultvalue);

   /**
    * Get a float entry from the database with the specified key
    * name.  If the specified key does not exist in the database 
    * then an error message is printed and the program exits.  
    * 
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual Array<float> getFloatArray(const string& key);

   /**
    * Get a float entry from the database with the specified key
    * name.  If the specified key does not exist in the database,
    * or the given number of elements does no match the number of
    * elements in the database, then an error message is printed and 
    * the program exits.
    *
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual void getFloatArray(
      const string& key, float* data, const int nelements);

   /**
    * Return true or false depending on whether the specified key
    * represents an integer entry.  If the key does not exist or if
    * the string is empty, then false is returned.
    */
   virtual bool isInteger(const string& key);

   /**
    * Create an integer scalar entry in the database with the specified
    * key name.
    * 
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual void putInteger(const string& key, const int& data);

   /**
    * Create an integer array entry in the database with the specified
    * key name.
    * 
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual void putIntegerArray(
      const string& key, const Array<int>& data);

   /**
    * Create an integer array entry in the database with the specified
    * key name.
    * 
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual void putIntegerArray(
      const string& key, const int* const data, const int nelements);

   /**
    * Get an integer entry in the database with the specified key name.
    * If the specified key does not exist in the database 
    * then an error message is printed and the program exits.
    *
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual int getInteger(const string& key);

   /**
    * Get an integer entry in the database with the specified key name.
    * If the specified key does not exist in the database, then the default
    * value is returned.  
    *
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual int getIntegerWithDefault(
      const string& key, const int& defaultvalue);

   /**
    * Get an integer entry from the database with the specified key
    * name.  If the specified key does not exist in the database 
    * then an error message is printed and the program exits.
    *
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual Array<int> getIntegerArray(const string& key);

   /**
    * Get an integer entry from the database with the specified key
    * name.  If the specified key does not exist in the database,
    * or the given number of elements does no match the number of
    * elements in the database, then an error message is printed and 
    * the program exits.
    *
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual void getIntegerArray(
      const string& key, int* data, const int nelements);

   /**
    * Return true or false depending on whether the specified key
    * represents a string entry.  If the key does not exist or if
    * the string is empty, then false is returned.
    */
   virtual bool isString(const string& key);

   /**
    * Create a string scalar entry in the database with the specified
    * key name.
    * 
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual void putString(const string& key, const string& data);

   /**
    * Create a string array entry in the database with the specified
    * key name.
    *
    * When assertion checking is active, the key string must be non-empty. 
    */
   virtual void putStringArray(
      const string& key, const Array<string>& data);

   /**
    * Create a string array entry in the database with the specified
    * key name.
    *
    * When assertion checking is active, the key string must be non-empty. 
    */
   virtual void putStringArray(
      const string& key, const string* const data, const int nelements);

   /**
    * Get a string entry in the database with the specified key name.
    * If the specified key does not exist in the database 
    * then an error message is printed and the program exits.
    *
    * When assertion checking is active, the key string must be non-empty. 
    */
   virtual string getString(const string& key);

   /**
    * Get a string entry in the database with the specified key name.
    * If the specified key does not exist in the database, then the default
    * value is returned.  
    *
    * When assertion checking is active, the key string must be non-empty. 
    */
   virtual string getStringWithDefault(
      const string& key, const string& defaultvalue);

   /**
    * Get a string entry from the database with the specified key
    * name.  If the specified key does not exist in the database 
    * then an error message is printed and the program exits.
    *
    * When assertion checking is active, the key string must be non-empty. 
    */
   virtual Array<string> getStringArray(const string& key);

   /**
    * Get a string entry from the database with the specified key
    * name.  If the specified key does not exist in the database,
    * or the given number of elements does no match the number of
    * elements in the database, then an error message is printed and 
    * the program exits.
    *
    * When assertion checking is active, the key string must be non-empty.
    */
   virtual void getStringArray(
      const string& key, string* data, const int nelements);

   /**
    * Print contents of current database to the specified output stream.  
    * If no output stream is specified, then data is written to stream pout.
    * Note that none of the subdatabases contained in the current database 
    * will have their contents printed.  To view the contents of any other
    * database, you must call this print routine for that database. 
    */
   virtual void printClassData(ostream& os = pout);

   /**
    * Open a database file using the fileName.  The file name string is
    * the name of the file to open.  The flags string is the name of
    * the file status: possible values are "R" for read only and "W"
    * for write.   
    *
    * When assertion checking is active, strings must be non-empty.
    */
   virtual int mount(const string& file_name,
                     const string& flags);

   /**
    * Close the database file.
    */
   virtual void unmount();

   /**
    * Return the group_id so VisIt can access an object's HDF database.
    */
   hid_t getGroupId();

private:
   HDFDatabase(const HDFDatabase&);   // not implemented
   void operator=(const HDFDatabase&);     // not implemented

   /*
    * Static function passed HDF5 iterator routine to look up database keys.
    */
   static herr_t iterateKeys(hid_t loc_id,
                             const char *name,
                             void *opdata);

   /*
    * Static member used to construct list of keys when searching for
    * database keys via the HDF5 iterator routine.
    */
   static void addKeyToList(const char *name,
                            int type,
                            void* database);

   /*
    * Private constructor used internally to create sub-databases.
    */
   HDFDatabase(const string& name, hid_t group_ID);

   /*
    * Private utility routine for inserting array data in the database
    */
   void insertArray(hid_t parent_id,
                    const char *name,
                    hsize_t offset,
                    int ndims,
                    const hsize_t dim[/*ndims*/],
                    const int *perm,
                    hid_t member_id) const;

   /*!
    * @brief Create an HDF compound type for box.
    *
    * When finished, the type should be closed using H5Tclose(hid_t).
    *
    * @param char_type 'n' mean use native types; 'f' = means use
    *        types for file.
    * @return the compound type id.
    * @internal We currently create a new compound type every
    * time we write a compound.  It would be more efficient to
    * cache the type id for the file.
    */
   hid_t createCompoundDatabaseBox( char type_spec ) const;

   /*!
    * @brief Create an HDF compound type for complex.
    *
    * When finished, the type should be closed using H5Tclose(hid_t).
    *
    * @param char_type 'n' mean use native types; 'f' = means use
    *        types for file.
    * @return the compound type id.
    * @internal We currently create a new compound type every
    * time we write a compound.  It would be more efficient to
    * cache the type id for the file.
    */
   hid_t createCompoundComplex( char type_spec ) const;
  
   /*
    * Private utility routines for searching keys in database;
    */
   void performKeySearch();
   void cleanupKeySearch();

   /*!
    * @brief Write attribute for a given dataset.
    *
    * Currently only one attribute is kept for each dataset: its type.
    * The type attribute is used to determine what kind of data the
    * dataset represent.
    *
    * @param type_key Type identifier for the dataset
    * @param dataset_id The HDF dataset id
    */
    void writeAttribute(int type_key,
		        hid_t dataset_id);

   /*!
    * @brief Read attribute for a given dataset.
    *
    * Currently only one attribute is kept for each dataset: its type.
    * The type attribute is returned.
    *
    * @param dataset_id The HDF dataset id
    * @return type attribute
    */
   int readAttribute( hid_t dataset_id );

   struct hdf_complex {
      double re;
      double im;
   };

   /*
    * The following structure is used to store (key,type) pairs when
    * searching for keys in the database.
    */
   struct KeyData {
      string d_key;   // group or dataset name
      int    d_type;  // type of entry
   };

   static string s_top_level_search_group;
   static string s_group_to_search;
   static int s_still_searching;
   static int s_found_group;

   /*
    * HDF5 file and group id, boolean flag indicating whether database 
    * is associated with a mounted file, and name of this database object.
    */
   /*!
     @brief Whether database is mounted to a file
   */
   bool  d_is_file;
   /*!
     @brief ID of file attached to database

     Is either -1 (not mounted to file) or set to the return value from
     opening a file.
     Set to -1 on unmounting the file.
   */
   hid_t d_file_id;
   /*!
     @brief ID of group attached to database

     A database object is always attached to a group.
     The group id is set in the constructor when constructing from a group.
     If the object mounts a file, the group id is the file id.
   */
   hid_t d_group_id;

   /*
    * Name of this database object (passed into constructor, and list
    * of (key,type) pairs assembled when searching for keys.
    */ 
   string d_database_name;

   List<KeyData> d_keydata;

};


}
}

#endif

#endif
