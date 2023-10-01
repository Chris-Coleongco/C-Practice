#include <stdio.h>
#include <stdint.h>

#pragma pack(push, 1) // Ensure structure alignment is one byte
typedef struct {
    uint16_t type;         // Magic identifier "BM"
    uint32_t size;         // File size in bytes
    uint16_t reserved1;    // Reserved
    uint16_t reserved2;    // Reserved
    uint32_t offset;       // Offset to image data
    uint32_t header_size;  // Header size in bytes
    int32_t width;         // Image width
    int32_t height;        // Image height
    uint16_t planes;       // Number of color planes
    uint16_t bits_per_pixel; // Bits per pixel
    uint32_t compression;  // Compression type (0 for uncompressed)
    uint32_t image_size;   // Image data size
    int32_t x_pixels_per_meter; // Pixels per meter in X direction
    int32_t y_pixels_per_meter; // Pixels per meter in Y direction
    uint32_t colors_used;  // Number of colors used (0 for full color images)
    uint32_t colors_important; // Number of important colors (usually 0)
} BMPHeader;
#pragma pack(pop)

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <image_file.bmp>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        printf("Failed to open file %s\n", argv[1]);
        return 1;
    }

    BMPHeader header;
    fread(&header, sizeof(header), 1, file);

    if (header.type != 0x4D42) { // Check if it's a BMP file
        printf("Not a BMP file\n");
        fclose(file);
        return 1;
    }




    // Open a new file for writing in binary mode
    FILE *newfile = fopen("NEW.bmp", "wb");
    if (!newfile) {
        printf("Failed to create the new BMP file.\n");
        return 1;
    }

    // Write the BMP header to the file
    fwrite(&header, sizeof(BMPHeader), 1, newfile);

    // Calculate the number of bytes per pixel based on BPP
    int bytes_per_pixel = header.bits_per_pixel / 8;

    int width = header.width;
    int height = header.height;
    int row_padding = (4 - (width * bytes_per_pixel) % 4) % 4;

    for (int y = height - 1; y >= 0; y--) {
        for (int x = 0; x < width; x++) {
            uint8_t pixel_data[4]; // Maximum of 4 bytes per pixel
            fread(pixel_data, sizeof(uint8_t), bytes_per_pixel, file);

            // Print the RGB values of the pixel

            fwrite(pixel_data, sizeof(uint8_t), 3, newfile);

            // Close the file when you're done
            

            printf("Pixel at (%d, %d): R=%u, G=%u, B=%u\n", x, y, pixel_data[2], pixel_data[1], pixel_data[0]);

            
        }
        // Skip row padding
        fseek(file, row_padding, SEEK_CUR);
    }

    // Close the file
    fclose(newfile);
    fclose(file);

    return 0;
}
