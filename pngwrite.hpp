#include <iostream>
#include <glm/glm.hpp>
#include <png.h>
#include <stdio.h>
#include <vector>
#include <filesystem>

int write_png(std::vector<std::vector<glm::vec4>> data,int width = 128,int height = 128) {
    //png_byte color_type;
    //png_byte bit_depth;
    png_bytep *row_pointers = NULL;
    

    std::cout << "Writing png to file.\n";
    std::filesystem::current_path();
    FILE *fp = fopen("test1.png","wb");
    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING,NULL,NULL,NULL);
    png_infop info = png_create_info_struct(png);
    png_init_io(png,fp);
    png_set_IHDR(
        png,
        info,
        width,
        height,
        8,
        PNG_COLOR_TYPE_RGBA,
        PNG_INTERLACE_NONE,
        PNG_COMPRESSION_TYPE_DEFAULT,
        PNG_FILTER_TYPE_DEFAULT
        );
    png_write_info(png,info);
    row_pointers = (png_bytep*)malloc(sizeof(png_bytep)*height);
    for(int y=0; y<height; y++){
        row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png,info));
    }
    for(int y=0; y<height; y++){
        for(int z=0; z<width; z++){
            row_pointers[y][4*z]=(unsigned char)(data[y][z].x * 255);
            row_pointers[y][4*z + 1]=(unsigned char)(data[y][z].y * 255);
            row_pointers[y][4*z + 2]=(unsigned char)(data[y][z].z * 255);
            row_pointers[y][4*z + 3]=(unsigned char)(data[y][z].w * 255);
        }
    }
    png_write_image(png,row_pointers);
    png_write_end(png,NULL);
    for(int y=0; y<height; y++){
        free(row_pointers[y]);
    }
    free(row_pointers);
    fclose(fp);
    png_destroy_write_struct(&png,&info);
    return 0;
}
