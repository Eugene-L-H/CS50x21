#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>



int main(int argc, char *argv[])
{
    typedef uint8_t BYTE;
    int jpeg_count = -1;
    bool jpeg_found = false;
    FILE *img = NULL;

    // The user must input a file to be recovered.
    if (argc != 2)
    {
        printf("Usage: ./recover image\n.");
        return 1;
    }

    // Open memory card.
    FILE *file = fopen(argv[1], "r"); // Open file contents to be recovored.

    if (file == NULL)
    {
        printf("Unable to open the file.\n");
        return 1;
    }


    // Initialize buffer to read data from card into.
    BYTE buffer[512];

    // Repeat until end of card:
    while (fread(&buffer, 512, 1, file) == 1) // Read 512 bytes into buffer.
    {
        // Check header for JPEG pattern.
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3]) == 0xe0)
        {
            // Close previous jpg if open.
            if (jpeg_found)
            {
                fclose(img);
            }

            jpeg_found = true; // Program can begin writing JPEGs once one is found.
            jpeg_count += 1;

            // Create jpeg filename.
            char filename[8];
            sprintf(filename, "%03i.jpg", jpeg_count);

            // Create a new JPEG file to start writing.
            img = fopen(filename, "w");
        }

        // Write buffer to JPEG file.
        if (jpeg_found)
        {
            fwrite(&buffer, 512, 1, img);
        }

    }

    fclose(file);
    return 0;
}