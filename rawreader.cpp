#include "stdio.h"
#include <fstream>
#include <string>
#include "Stack.h"
#include "Queue.h"
#pragma warning(disable:4996)
using namespace std;
const int WIDTH = 256; // image width
const int HEIGHT = 256; // image height

Result flipped(string name) {
    fileStack s; // flipeed option will use the stack
    FILE* input_file, * output_file;

    unsigned char input_data[256][256];
    unsigned char output_data[256][256];

    string inputPath = "image_files/images/" + name + ".RAW";
    string outputPath = "Result/" + name + "_flipped" + ".RAW"; //Path and name to save

    // read .RAW
    input_file = fopen(inputPath.c_str(), "rb");
    if (input_file == NULL) {
        return EditFileLoadError; // input file not Load error 
    }
	
    fread(input_data, sizeof(unsigned char), WIDTH * HEIGHT, input_file); // read the input file


    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            s.Push(input_data[i][j]);
        }
    }

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            output_data[i][j] = s.Pop();
        }
    }

    // Save converted images
    output_file = fopen(outputPath.c_str(), "w+");
    fwrite(output_data, sizeof(unsigned char), WIDTH * HEIGHT, output_file);

    if (output_file == NULL) {
        return EditFileLoadError; // when outputFile is not opened
    }

    fclose(input_file);
    fclose(output_file);
    return Success;
}

Result adjusted(string name, int light) { // bright adjusted
    Queue q; // adjusted option will use the queue
    FILE* input_file, * output_file;

    unsigned char input_data[256][256];
    unsigned char output_data[256][256];

    string inputPath = "image_files/images/" + name + ".RAW";
    string outputPath = "Result/" + name + "_adjusted" +".RAW";

    input_file = fopen(inputPath.c_str(), "rb");
    if (input_file == NULL) {
        return EditFileLoadError; // when input file is not opened
    }
    fread(input_data, sizeof(unsigned char), WIDTH * HEIGHT, input_file);

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int input = input_data[i][j] + light;
            if (input > 255) input = 255;
            if (input < 0) input = 0;
            q.push(input);
        }
    }

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            output_data[i][j] = q.pop();
        }
    }

    // Store converted images
    output_file = fopen(outputPath.c_str(), "w+");
    fwrite(output_data, sizeof(unsigned char), WIDTH * HEIGHT, output_file);

    if (output_file == NULL) {
        return EditFileLoadError;
    }

    fclose(input_file);
    fclose(output_file);
    return Success;
}

Result resized(string name) { // reduce the size
    fileStack s;
    Queue q;
    FILE* input_file, * output_file;

    unsigned char input_data[256][256];
    unsigned char output_data[128][128];

    string inputPath = "image_files/images/" + name + ".RAW";
    string outputPath = "Result/" + name + "_resized" +".RAW";

    input_file = fopen(inputPath.c_str(), "rb");
    if (input_file == NULL) {
        return EditFileLoadError; // when input_file is not opened
    }
    fread(input_data, sizeof(unsigned char), WIDTH * HEIGHT, input_file);

    for (int i = 0; i < HEIGHT; i= i+2) {
        for (int j = 0; j < WIDTH; j= j+2) {
            int input = input_data[i][j] + input_data[i][j+1] + input_data[i+1][j] + input_data[i+1][j+1];
            input = input / 4;
            q.push(input); // using queue
        }
    }

	// Store converted images
    for (int i = 0; i < HEIGHT/2; i++) {
        for (int j = 0; j < WIDTH/2; j++) {
            output_data[i][j] = q.pop(); // using queue
        }
    }

    output_file = fopen(outputPath.c_str(), "w+");
    fwrite(output_data, sizeof(unsigned char), WIDTH * HEIGHT / 4, output_file);

    if (output_file == NULL) {
        return EditFileLoadError;
    }

    fclose(input_file);
    fclose(output_file);
    return Success;
}