#include <stdio.h>
#include <jpeglib.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // File pointers
    FILE *infile, *outfile;

    // Image structs
    struct jpeg_decompress_struct cinfo;
    struct jpeg_compress_struct cinfo_out; // Change to jpeg_compress_struct for compression
    struct jpeg_error_mgr jerr;

    // Image buffer
    JSAMPROW row_pointer[1];

    // Check the input file
    infile = fopen(argv[1], "rb");
    if (infile == NULL)
    {
        printf("Cannot open file input\n");
        return 1;
    }

    // Create decompress struct
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, infile);

    // Read the image header
    jpeg_read_header(&cinfo, TRUE);

    // Start decompressing the image
    jpeg_start_decompress(&cinfo);

    // Allocate memory for the image buffer
    int row_stride = cinfo.output_width * cinfo.output_components;
    unsigned char *image_buffer = (unsigned char *)malloc(row_stride * cinfo.output_height);
    if (image_buffer == NULL)
    {
        printf("Cannot allocate memory for the image buffer\n");
        return 1;
    }

    // Read the image data
    while (cinfo.output_scanline < cinfo.output_height)
    {
        row_pointer[0] = &image_buffer[cinfo.output_scanline * row_stride];
        jpeg_read_scanlines(&cinfo, row_pointer, 1);
    }

    // Finish decompressing the image
    jpeg_finish_decompress(&cinfo);

    // Loop through all the pixels and set red and green channels to 0
    for (int i = 0; i < cinfo.output_height * row_stride; i += 3)
    {
        // Get the current pixel
        unsigned char b = image_buffer[i + 2];
        // Set the red and green channels to 0
        image_buffer[i] = 0;
        image_buffer[i + 1] = 0;
        image_buffer[i + 2] = b;
    }

    // Open the output file
    outfile = fopen(argv[2], "wb");
    if (outfile == NULL)
    {
        printf("Cannot open output file\n");
        return 1;
    }

    // Create compress struct
    cinfo_out.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo_out); // Use compress struct here
    jpeg_stdio_dest(&cinfo_out, outfile);

    // Set the image parameters for output
    cinfo_out.image_width = cinfo.image_width;
    cinfo_out.image_height = cinfo.image_height;
    cinfo_out.input_components = cinfo.output_components; // Corrected
    cinfo_out.in_color_space = cinfo.out_color_space; // Corrected

    // Set the default compression parameters
    jpeg_set_defaults(&cinfo_out);

    // Start compressing the image
    jpeg_start_compress(&cinfo_out, TRUE);

    // Write the image data
    while (cinfo_out.next_scanline < cinfo_out.image_height)
    {
        row_pointer[0] = &image_buffer[cinfo_out.next_scanline * row_stride];
        jpeg_write_scanlines(&cinfo_out, row_pointer, 1);
    }

    // Finish compressing the image
    jpeg_finish_compress(&cinfo_out);

    // Close the files
    fclose(infile);
    fclose(outfile);
    
    // Free the image buffer
    free(image_buffer);

    return 0;
}
