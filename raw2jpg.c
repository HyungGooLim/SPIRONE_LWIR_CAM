#include "raw2jpg.h"
#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>

int convertRawToJpg(const short* rawData, int width, int height, const char* outputFilename) {
    if (!rawData || width <= 0 || height <= 0 || !outputFilename) {
        fprintf(stderr, "[convertRawToJpg] Invalid input\n");
        return -1;
    }

    // 1. 14bit 데이터 정규화 → 8bit grayscale
    unsigned char* gray8bit = malloc(width * height);
    if (!gray8bit) {
        fprintf(stderr, "[convertRawToJpg] Memory allocation failed\n");
        return -2;
    }

    short min = 16383, max = 0;
    for (int i = 0; i < width * height; ++i) {
        if (rawData[i] < min) min = rawData[i];
        if (rawData[i] > max) max = rawData[i];
    }

    float scale = 255.0f / (max - min);
    for (int i = 0; i < width * height; ++i) {
        int val = (int)((rawData[i] - min) * scale);
        if (val < 0) val = 0;
        if (val > 255) val = 255;
        gray8bit[i] = (unsigned char)val;
    }

    // 2. libjpeg 설정
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;

    FILE* outfile = fopen(outputFilename, "wb");
    if (!outfile) {
        fprintf(stderr, "[convertRawToJpg] Cannot open file %s\n", outputFilename);
        free(gray8bit);
        return -3;
    }

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, outfile);

    cinfo.image_width = width;
    cinfo.image_height = height;
    cinfo.input_components = 1;             // grayscale
    cinfo.in_color_space = JCS_GRAYSCALE;

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, 90, TRUE);     // 품질 0~100

    jpeg_start_compress(&cinfo, TRUE);
    while (cinfo.next_scanline < cinfo.image_height) {
        JSAMPROW row_pointer = &gray8bit[cinfo.next_scanline * width];
        jpeg_write_scanlines(&cinfo, &row_pointer, 1);
    }
    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);

    fclose(outfile);
    free(gray8bit);

    printf("[convertRawToJpg] Saved JPEG to %s\n", outputFilename);
    return 0;
}
