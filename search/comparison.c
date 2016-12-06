#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
// For profiling
#include <time.h>

// Size of each individual image
int image_width=0;
int image_height=0;
// Size of area to search for a correlation | must be divisible by 2
int search_width=0;
int search_height=0;
// Size of the correlation snapshot used | must be divisible by 2
int corr_window_width=16;
int corr_window_height=16;

/* This is an implementation of http://www1.cs.columbia.edu/CAVE/publications/pdfs/Bhat_PAMI98.pdfs */

// (forward) linked list
typedef struct Number
{
    struct Number *next;
    int value;
} Number;

void rank(unsigned char *img[], int offset_x, int offset_y, Number *pi)
{
    // pi is sorted by rank, with memory position denoting original order

    int index = 1;
    Number *tmp = 0;
    // Go through the entire environment
    for (int x=offset_x-corr_window_width/2; x<offset_x+corr_window_width/2; x++)
    {
        for (int y=offset_y-corr_window_height/2; y<offset_y+corr_window_height/2; y++)
        {
            // Store the pixel value into the next LL element
            pi[index].value = img[x][y];
            // And now insert that element into the LL so that it stays sorted
            // This way, the LL will be sorted, and the rank will be encoded in the memory position, as that won't change
            tmp = pi;
            for (int counter=0; counter < index-1 && tmp->next->value > pi[index].value; counter++)
            {
                tmp = tmp->next;
            }
            // Insertion
            pi[index].next = tmp->next;
            tmp->next = &(pi[index]);

            index++;
        }
    }
}

double distance(Number *pi_1, Number *pi_2)
{
    // Returns distance between two ranked LLs, normalized -1 to 1, as described here: http://www1.cs.columbia.edu/CAVE/publications/pdfs/Bhat_PAMI98.pdf
    // The same variable names are used as in the text, it is recommended to read passage 3.3

    Number *tmp;
    int d[corr_window_width*corr_window_height];

    // Write rank in pi_2's value field. We don't need this in pi_1
    // Initialize d
    tmp = pi_2[0].next;
    for (int i=0; i<corr_window_width * corr_window_height; i++)
    {
        tmp->value = i;
        tmp = tmp->next;
        d[i] = -1;
    }

    // Iterating through rank
    // We want to know what rank there is in pi_2 at the place where pi_1 has rank=i.
    // Then we calculate how big the distance (=number of ranks that are out of position) between the value and an optimum is and save it to d.
    tmp = pi_1[0].next;
    for (int i=0; i<corr_window_width * corr_window_height; i++)
    {
        for (int j=i; j<pi_2[tmp-pi_1].value; j++)
        {
            d[j]++;
        }
        tmp = tmp->next;
    }

    // Get the highest value in d
    int d_max=0;
    for (int i=0; i<corr_window_width * corr_window_height; i++)
    {
        if (d[i] > d_max)
        {
            d_max = d[i];
        }
    }

    // Normalize the result from -1 to +1
    return 1.0 - 2.0*d_max / (corr_window_width*corr_window_height/2);
}

void height_map(unsigned char* left_image[], unsigned char* right_image[], unsigned char* output_image[])
{
    int stime = clock(); // Profiling

    // Speed / Memory tradeoff; we precalculate and store all the rankings of both images
    Number ***pi_1 = malloc(sizeof(Number**)*(image_width-corr_window_width));
    Number ***pi_2 = malloc(sizeof(Number**)*(image_width-corr_window_width));
    int **raw_distance = malloc(sizeof(int*)*image_width-corr_window_width);
    for (int i=0; i<image_width-corr_window_width; i++)
    {
        pi_1[i] = malloc(sizeof(Number*)*(image_height-corr_window_height));
        pi_2[i] = malloc(sizeof(Number*)*(image_height-corr_window_height));
        raw_distance[i] = malloc(sizeof(int*)*(image_height-corr_window_height));
    }

    int max_dist = 0, min_dist = search_width*search_height;

    // Precalculate the rankings
    printf("Calculating ranks");
    fflush(stdout);
    for (int x=0; x<image_width-corr_window_width; x++)
    {
        for (int y=0; y<image_height-corr_window_height; y++)
        {
            Number* tmp = malloc(sizeof(Number)*(corr_window_width*corr_window_height+1));
            rank(left_image, x+corr_window_width/2, y+corr_window_height/2, tmp);
            pi_1[x][y] = tmp;

            tmp = malloc(sizeof(Number)*(corr_window_width*corr_window_height+1));
            rank(right_image, x+corr_window_width/2, y+corr_window_height/2, tmp);
            pi_2[x][y] = tmp;
        }
    }

    // Profiling
    int dtime = clock();
    printf(" %fs\n", (dtime - stime)/(double)CLOCKS_PER_SEC);
    stime = dtime;
    double total_time = 0;

    // Match images pixel by pixel, computing a height map.
    printf("Matching:\n");
    fflush(stdout);
    for (int x = 0; x < image_width-corr_window_width; x++)
    {
        for (int y = 0; y < image_height-corr_window_height; y++)
        {
            double best_match = -1;
            double correlation;
            int f=search_width*search_width + search_height*search_height;

            // Go through all possible environments and measure the best correlation
            for (int k=-search_width/2; k<search_width/2; k++)
            {
                for (int l=-search_height/2; l<search_height/2; l++)
                {
                    // Skip pixel outside of the image
                    if (x+k < 0 || y+l < 0 || x+k >= image_width-corr_window_width || y+l >= image_height-corr_window_height)
                        continue;

                    // Calculate the correlation between I2 and I1, and if it's the best yet found (or if it's equal to the best but nearer) then keep
                    correlation = distance(pi_1[x][y], pi_2[x+k][y+l]);
                    if (correlation > best_match || (correlation == best_match && k*k + l*l < f))
                    {
                        best_match = correlation;
                        // Euclidean distance (squared, because we only care about comparision)
                        f = k*k + l*l;
                    }
                }
            }

            raw_distance[x][y] = f;
            if (max_dist < f) max_dist = f;
            if (min_dist > f) min_dist = f;
        }

        // Profiling
        dtime = clock();
        total_time += (dtime-stime)/(double)CLOCKS_PER_SEC;
        printf(
                "\r%i%% - row took %.3fs, approx. %.2f min left.  ",
                100*x/(image_width-corr_window_width),
                (dtime-stime)/(double)CLOCKS_PER_SEC,
                (total_time*(image_width-corr_window_width)/(x+1)-total_time)/60
            );
        fflush(stdout);
        stime = dtime;
    }

    printf("\rFinished matching in %.3f min.                               \n", total_time/60);

    // Fit distances and clean up.
    double dist_dif = max_dist - min_dist;
    for (int x = 0; x < image_width-corr_window_width; x++)
    {
        for (int y = 0; y < image_height-corr_window_height; y++)
        {
            output_image[x+corr_window_width/2][y+corr_window_height/2] = 255*(raw_distance[x][y]-min_dist)/dist_dif;
            free(pi_1[x][y]);
            free(pi_2[x][y]);
        }
    }
}

void print_usage_and_exit(const char *progName)
{
    fprintf(stderr, "usage: %s left_file right_file -o output_file -width image_width -height image_height"
            " [-corr corr_window_width]", progName);
    exit(1);
}

int main(int argc, char *argv[])
{
    char *left = NULL;
    char *right = NULL;
    char *output = NULL;

    // Parse arguments
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-corr") == 0)
        {
            if (i + 1 <= argc - 1)
            {
                i++;
                corr_window_width = atoi(argv[i]);
                corr_window_width += corr_window_width%2; // We need to be even.
                corr_window_height = corr_window_width;
            }
            else
            {
                print_usage_and_exit(argv[0]);
            }
        }
        else if (strcmp(argv[i], "-width") == 0)
        {
            if (i + 1 <= argc - 1)
            {
                i++;
                image_width = atoi(argv[i]);
            }
            else
            {
                print_usage_and_exit(argv[0]);
            }
        }
        else if (strcmp(argv[i], "-height") == 0)
        {
            if (i + 1 <= argc - 1)
            {
                i++;
                image_height = atoi(argv[i]);
            }
            else
            {
                print_usage_and_exit(argv[0]);
            }
        }
        else if (strcmp(argv[i], "-o") == 0)
        {
            if (i + 1 <= argc - 1)
            {
                i++;
                output = argv[i];
            }
            else
            {
                print_usage_and_exit(argv[0]);
            }
        }
        else if (argv[i][0] != '-') // Hopefully the input file
        {
            if (left == NULL)
            {
                left = argv[i];
            } else if (right == NULL)
            {
                right = argv[i];
            }
            else
            {
                print_usage_and_exit(argv[0]);
            }
        }
        else
        {
            print_usage_and_exit(argv[0]);
        }
    }
    if (left == NULL || right == NULL || output == NULL || image_height == 0 || image_width == 0)
    {
        print_usage_and_exit(argv[0]);
    }
    search_width = corr_window_width + 20; // To be sure it is enough.
    search_height = corr_window_height + 8;

    // Read the input files and extract the data
    FILE *left_file, *right_file;
    left_file = fopen(left, "rb");
    right_file = fopen(right, "rb");
    if (left_file == 0 || right_file == 0)
    {
        printf("\nError opening a file.");
        fflush(stdout);
        return 0;
    }

    unsigned char **left_image = malloc(sizeof(unsigned char*)*image_width);
    unsigned char **right_image = malloc(sizeof(unsigned char*)*image_width);
    unsigned char **output_image = malloc(sizeof(unsigned char*)*image_width);

    for (int i=0; i<image_width; i++)
    {
        left_image[i] = malloc(sizeof(unsigned char)*image_height);
        right_image[i] = malloc(sizeof(unsigned char)*image_height);
        output_image[i] = malloc(sizeof(unsigned char)*image_height);
    }

    for (int j=0; j<image_height; j++)
    {
        for (int i=0; i<image_width; i++)
        {
            left_image[i][j] = fgetc(left_file);
            right_image[i][j] = fgetc(right_file);
            output_image[i][j] = 0;
        }
    }
    fclose(left_file);
    fclose(right_file);

    // We now have both images as 2d arrays and an output array. Begin the actual processing.
    height_map(left_image, right_image, output_image);

    // Print output
    FILE *output_file;
    output_file = fopen(output, "wb");
    for (int j=0; j<image_height; j++)
    {
        for (int i=0; i<image_width; i++)
        {
            fputc(output_image[i][j], output_file);
        }
    }
    fclose(output_file);
}
