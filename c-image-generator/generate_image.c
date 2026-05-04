#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jpeglib.h>

#define WIDTH  800
#define HEIGHT 600

void draw_rect(unsigned char *img, int x0, int y0, int x1, int y1,
               unsigned char r, unsigned char g, unsigned char b) {
    for (int y = y0; y < y1 && y < HEIGHT; y++)
        for (int x = x0; x < x1 && x < WIDTH; x++) {
            int idx = (y * WIDTH + x) * 3;
            img[idx]     = r;
            img[idx + 1] = g;
            img[idx + 2] = b;
        }
}

int main() {
    unsigned char *img = calloc(WIDTH * HEIGHT * 3, 1);
    if (!img) { fprintf(stderr, "Out of memory\n"); return 1; }

    /* gradient background */
    for (int y = 0; y < HEIGHT; y++)
        for (int x = 0; x < WIDTH; x++) {
            int idx = (y * WIDTH + x) * 3;
            img[idx]     = (unsigned char)(x * 255 / WIDTH);
            img[idx + 1] = (unsigned char)(y * 255 / HEIGHT);
            img[idx + 2] = 180;
        }

    /* colored rectangles */
    draw_rect(img, 50,  50,  250, 200, 255,  80,  80);
    draw_rect(img, 300, 50,  500, 200,  80, 200,  80);
    draw_rect(img, 550, 50,  750, 200,  80, 120, 255);
    draw_rect(img, 175, 250, 625, 450, 255, 220,  50);

    /* write JPEG */
    FILE *out = fopen("output.jpg", "wb");
    if (!out) { fprintf(stderr, "Cannot open output.jpg\n"); free(img); return 1; }

    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr       jerr;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, out);

    cinfo.image_width      = WIDTH;
    cinfo.image_height     = HEIGHT;
    cinfo.input_components = 3;
    cinfo.in_color_space   = JCS_RGB;

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, 90, TRUE);
    jpeg_start_compress(&cinfo, TRUE);

    while (cinfo.next_scanline < cinfo.image_height) {
        JSAMPROW row = &img[cinfo.next_scanline * WIDTH * 3];
        jpeg_write_scanlines(&cinfo, &row, 1);
    }

    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);
    fclose(out);
    free(img);

    printf("Generated output.jpg (%dx%d, 90%% quality)\n", WIDTH, HEIGHT);
    return 0;
}
