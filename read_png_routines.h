#if ! READ_PNG_ROUTINES_
#define READ_PNG_ROUTINES_

#define ERR_BAD_SIGNATURE     -3
#define ERR_OUT_OF_MEM        -4

/**@brief: PNG is contituted of chunks:
 * 
 *   chunk {length(4bytes), type(4bytes), data, CRC(4bytes)}
 * 
 *    PNG streams are in big-endian format
 *      
 *    -----------------------------------
 *   |      length (data length only)    |
 *   |-----------------------------------|
 *   |      type (name)                  |
 *   |-----------------------------------|
 *   |      Data                         |
 *   |-----------------------------------|
 *   |      CRC (data and type)          |
 *    ----------------------------------- 
 * 
 *  - The CRC is always present even when there is no data.
 *  - The combination of length fields and CRC values is already 
 *    sufficient to check the basic integrity of a PNG file
 * 
 *   _--_--_--__--_--_--__--_--_--__--_--_--__--_--_--__--_--_--__--_--_--__--_--_--__--_--_--__--_--_--__--_--_--_
 *   
 *  PNG file: {signature(8bytes), chunks}
 *   
 *   The simplest possible PNG file is composed of the PNG signature and only three chunk types:
 *   - the image header chunk, IHDR
 *   - the image data chunk, IDAT
 *   - the end-of-image chunk, IEND 
 * 
 *    -----------------------------------
 *   |      Signature 8 bytes            |
 *   |-----------------------------------|
 *   |      IHDR                         |
 *   |-----------------------------------|     <---  Layout of the simplest PNG
 *   |      IDAT                         |
 *   |-----------------------------------|
 *   |      IEND                         |
 *    ----------------------------------- 
 *   
 *   IHDR must be the first chunk in a PNG image, and it includes all of the details about the type of the image:
 *   its height and width, pixel depth, compression and filtering methods, interlacing method, whether it has an alpha (transparency) channel,
 *   and whether it's a truecolor, grayscale, or colormapped (palette) image. 
 *   
 *   IDAT contains all of the image's compressed pixel data
 *   (big data chunks cause the decoder to wait for CRC at the end of stream ==> not recommended)
 *   (commonly the data size are of 8 or 32 kbytes)
 * 
 *   IEND is the simplest chunk of all; it contains no data, just indicates that there are no more chunks in the image. 
 *   IEND is primarily useful when the PNG image is being transferred over the network as a stream
 *   
 * 
 *    -----------------------------------
 *   |      Signature 8 bytes            |
 *   |-----------------------------------|
 *   |      IHDR                         |
 *   |-----------------------------------|     
 *   |      PLTE                         | 
 *   |-----------------------------------|    <----- the structure of a colormapped PNG 
 *   |      IDAT                         |            (also known as palette-based or index-based images)             
 *   |-----------------------------------|
 *   |      IEND                         |
 *    ----------------------------------- 
 * 
 *   PLTE: the palette chunk simply contains a sequence of red, green, and blue values, where a value of 0 is black and 255 is full intensity; 
 *   anywhere from 1 to 256 RGB triplets are allowed, depending on the pixel depth of the image. 
 *   (That is, for a 4-bit image, no more than 16 palette entries are allowed.)
 * */



/**@brief: print informations about the used libs 
 * 
 * @args: void
 * @return: void
 * */
static void
printf_infos(void);

/**@brief:
 * 
 * png files is opened in binary mode
 * PNG spec requires dimensions should not exceed  2^31 - 1
 *  
 * first, check the file in input matches the PNG signature bytes: read 8 bytes.  
 * */
static int 
 readpng_init(FILE *infile, long *pWidth, long *pHeight)


#endif 
