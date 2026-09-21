/*======================================================================
 *
 * DESCRIPT.H -- Compaq Visual Fortran Descriptor definitions
 *               and routines for use from Microsoft Visual C++.
 *
 */

#include <stdarg.h>
#include <stdio.h>

#define DescriptorMaxRank 7

// See the descript.f90 file for more information on what each of these
// fields does.
//
struct DescriptorTriplet {
	int		Extent;		// Number of elements in this dimension
	int		Mult;		// Multiplier for this dimension
	int		LowerBound;	// LowerBound of this dimension
};

struct Descriptor {
	int		Base;		// Base address
	int		Len;		// Len of data type, used only for
					// character strings.
	int		Offset;
	int		Reserved;	// Reserved for future use.
	int		Rank;		// Rank of pointer
	struct DescriptorTriplet Dim[DescriptorMaxRank];
};

enum { DescriptRowOrder, DescriptColumnOrder };
//---------------------------------------------------------------------------
void *DescriptorElementAddress( struct Descriptor *dp, int rank, ... );
void DescriptorAssign( struct Descriptor *dp, void *base,
			           int size, int columnorder, int rank, ... );
void DescriptorPrint( struct Descriptor *dp, int rank );
//---------------------------------------------------------------------------

