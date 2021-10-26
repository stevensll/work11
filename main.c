#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define IN "/dev/random"
#define ARR_SIZE 10
#define OUT "output.txt"
unsigned int get_random(int fd){
    unsigned int num;
    //read takes in a file descriptor (created from open()), writes it to a buffer based on count bytes
    //since we want an int we read 4 bytes or size(num)
    int e = read(fd, &num, sizeof(num));
    if (e < 0){
        printf("\tError reading file from /dev/random\n");
        printf("\t%s\n", strerror(errno));
        return 0;
    }
    return num;   
}

int main() {

    printf("Opening /dev/random\n");
    int file1d = open(IN, O_RDONLY);
    if (file1d < 0){
        printf("Error opening /dev/random\n");
        printf("%s\n", strerror(errno));
        return 0;
    }
    printf("\n\tSuccess\n");

    printf("\nGenerating random numbers:\n\n");
    unsigned int arr[ARR_SIZE];
    unsigned int i;
    for(i = 0; i < ARR_SIZE; i++){
        arr[i] = get_random(file1d);
        printf("\trandom %d: %u\n", i, arr[i]);
    }
    printf("\n\tSuccess\n");

    printf("\nCreating output.txt\n");
    int file2d = open(OUT, O_WRONLY | O_CREAT, 0644);
       if (file2d < 0){
        printf("Error creating output.txt\n");
        printf("%s\n", strerror(errno));
        return 0;
    }
    printf("\n\tSuccess\n");

    printf("\nWriting to output.txt\n");
    int we = write(file2d, arr, sizeof(arr));
       if (we < 0){
        printf("Error writing to output.txt\n");
        printf("%s\n", strerror(errno));
        return 0;
    }
    printf("\n\tSuccess\n");

    //need to create a new file descriptor, since read left the filedescriptor at the last byte
    printf("\nOpening output.txt\n");
    int file3d = open(OUT, O_RDONLY);
       if (file3d < 0){
        printf("Error opening output.txt\n");
        printf("%s\n", strerror(errno));
        return 0;
    }
    printf("\n\tSuccess\n");

    printf("\nReading output.txt\n");
    unsigned int read_arr[ARR_SIZE];
    int read3d = read(file3d, read_arr, sizeof(read_arr));
       if (read3d < 0){
        printf("Error reading output.txt\n");
        printf("%s\n", strerror(errno));
        return 0;
    }
    for(i = 0; i < ARR_SIZE; i++){
        printf("\tVerifying random %d: %u\n", i,read_arr[i]);
    }
    printf("\n\tSuccess\n");

    close(file1d);
    close(file2d);
    close(file3d);
    return 0;
}