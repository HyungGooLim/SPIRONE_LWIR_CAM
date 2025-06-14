#ifndef RAW2JPG_H
#define RAW2JPG_H

#ifdef __cplusplus
extern "C" {
#endif

int convertRawToJpg(const short* rawData, int width, int height, const char* outputFilename);

#ifdef __cplusplus
}
#endif

#endif  // RAW2JPG_H
