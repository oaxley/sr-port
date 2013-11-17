;/****************************************************************************
;** MODULE:	cd.h
;** AUTHOR:	Sami Tammilehto / Fennosoftec OY
;** DOCUMENT:	?
;** VERSION:	1.0
;** REFERENCE:	-
;** REVISED BY:	-
;*****************************************************************************
;**
;** C / Include - THIS FILE AND AD.H SHOULD BE IN SYNC
;** - data types and related constants
;**
;****************************************************************************/


#ifndef INCLUDED_CD

#pragma pack(1)

#define angle	unsigned	/* 0..65535, 65536=360 degrees */

#define	visfl	short	
#define VF_UP		1	/* direction in which a vertex is out */
#define VF_DOWN		2	/* of screen. */
#define VF_LEFT		4
#define VF_RIGHT	8
#define VF_NEAR		16	/* too close */
#define VF_FAR		32

struct s_rmatrix /* special matrix specifying position & rotation */
{
	int	m[9];
	int	x;
	int	y;
	int	z;
};
#define rmatrix	struct s_rmatrix

struct s_vlist
{
	int	x;
	int	y;
	int	z;
	short	normal;
	short	RESERVED;
};
#define vlist	struct s_vlist

struct s_nlist
{
	short	x;
	short	y;
	short	z;
	short	RESERVED;
};
#define nlist	struct s_nlist

struct s_fvlist
{
	float	x;
	float	y;
	float	z;
	short	normal;
	short	RESERVED;
};
#define fvlist	struct s_fvlist

struct s_pvlist
{
	float	x;
	float	y;
	visfl	vf; // if vf&VF_NEAR, the x/y are undefined
	short	RESERVED[3];
};
#define pvlist	struct s_pvlist

#define polylist short
/* polylist contents:
	word: number of words in list (including last 0)
	word: sort polygon for this list
	word: pointer to polygon 1 inside polydata
	word: pointer to polygon 2 inside polydata
	word: pointer to polygon 3 inside polydata
	...
	word: 0 = end of list */

#define polydata char 
/* polydata consists of first a zero word, following by variable
   length records: 
byte	sides (=n)
byte	flags (=8 lower bits of PF flags)
byte	color
byte	RESERVED
word	normal (index inside normal vertices list)
word	vertex 1
word	vertex 2
...
word	vertex n
Total length for one record is: 4+2*n
*/

struct s_object
{
	int	flags;	/* flags (see below) */
	struct s_object	*parent; /* parent object */
	rmatrix *r0;	/* rotation/position relative to parent */
	rmatrix	*r;	/* rotation/position (modified by camera etc from r0)*/
	polydata *pd;	/* polygon data block */
	int	pdlen;	/* length of polygon data block in bytes */
	int	plnum;	/* number of pl-lists */
	short	*pl[16]; /* unsorted order (0) + precalculated polygon 
			   lists from max 16 directions (1..8). List contents:
			   word: length in words
			   word: closest vertex (for list 0, center vertex)
			   word: 1st polygon
			   word: 2nd polygon
			   ...
			   word: 0 */
	int	vnum;	/* number of vertices */
	int	nnum;	/* number of normals */
	int	nnum1;	/* number of basic normals. Normals betwen nnum1..nnum
			   are for gouraud shading */
	vlist	*v0;	/* original vertices. */
	nlist	*n0;	/* original normals */
	fvlist	*v;	/* calced: rotated vertices */
	nlist	*n;	/* calced: rotated normals */
	pvlist	*pv;	/* calced: projected vertices */
	visfl	vf;	/* calced: visibility flag for entire pointlist (log.and) */
	char	*name;	/* asciiz name for object */
};
#define object struct s_object

/* flags for objects & faces (lower 8 bits in face flags are the side number) */
#define F_DEFAULT	0xf001	/* for objects only - all enabled, visible */
#define F_VISIBLE	0x0001	/* object visible */
#define F_FLIP		0x0100
#define F_2SIDE		0x0200
#define F_SHADE8	0x0400	/* only on shade can be selected at a time */
#define F_SHADE16	0x0800
#define F_SHADE32	0x0C00
#define F_GOURAUD	0x1000
#define F_TEXTURE	0x2000

#define INCLUDED_CD

#define MAXSIDES	16

#define POLYSIDES	0
#define POLYCOLOR	1
#define POLYFLAGS	2
#define POLYVXSEG	3
#define POLYX		4
#define POLYY		5
#define POLYVX		(4 + MAXSIDES * 2)
#define POLYGR		(4 + 2 * MAXSIDES * 2)
#define POLYTX		(4 + 2 * MAXSIDES * 2 + 1)
#define POLYSIZE	(4 + 3 * MAXSIDES * 2)

#endif
