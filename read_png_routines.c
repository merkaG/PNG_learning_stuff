#include <stdio.h>

# include "png.h"
# include "read_png_routines.h"

/* !!!  Global variables don't work in reentrant programs, where 
 * 		the same routines may get called in parallel to handle different images
 * */

static png_struct png_ptr; /* used internally by libpng to keep track of the current 
							  state of the PNG image at any given moment */
static png_info info_ptr; /* used to indicate what the png state will be after all 
							 of the user-requested transformations are performed */


static void
 print_infos(void)
 {
	 fprintf(stdout, " Compiled with libpng %s; using libpng %s.\n",
      PNG_LIBPNG_VER_STRING, png_libpng_ver);
	 
	 fprintf(stderr, " Compiled with zlib %s; using zlib %s.\n",
      ZLIB_VERSION, zlib_version);
 }


static int 
 readpng_init(FILE *infile, long *pWidth, long *pHeight)
 {
   uint8_t sig[8];
                             
   fread(sig, 1, 8, infile);
   
   if (!png_check_sig(sig, 8))
   {
	 printf("png_check_sig failed");
     return ERR_BAD_SIGNATURE;   /* bad signature */
   }
	
   /* now read the png file */
   png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL,
                                    NULL);
    if (!png_ptr)
    {
      printf("error out of memory");
      return ERR_OUT_OF_MEM;   /* out of memory */
    }
    info_ptr = png_create_info_struct(png_ptr);
    
    if (!info_ptr) 
    {
      png_destroy_read_struct(&png_ptr, NULL, NULL);
      return ERR_OUT_OF_MEM;   /* out of memory */
    }  
    
    

    if (setjmp(png_ptr->jmpbuf)) {
      png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        return 2;
    }
 }
