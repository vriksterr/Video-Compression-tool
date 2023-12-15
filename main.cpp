#include <cstdlib>
#include <cstdio>


int main() {
    // Modify the file location and name
    const char* inputFilePath = "D:\\Downloads\\ffmpeg\\New folder\\(500) Days of Summer (2009)\\(500) Days of Summer (2009) [imdbid-tt1022603] - [WEBDL-2160p].mkv";
    const char* outputFilePath = "D:\\Downloads\\ffmpeg\\New folder\\(500) Days of Summer (2009)\\output_video.mp4";

    // Construct the ffmpeg command with the modified file locations
    const char* ffmpegCommand = "ffmpeg -i \"%s\" -c:v hevc_nvenc -preset medium -b:v 6000k -minrate 4000k -maxrate 16000k -bufsize 16000k -c:a aac \"%s\"";

    // Calculate the size needed for the command
    size_t commandSize = snprintf(nullptr, 0, ffmpegCommand, inputFilePath, outputFilePath) + 1;
    char* fullCommand = new char[commandSize];

    // Fill in the modified file locations in the command
    snprintf(fullCommand, commandSize, ffmpegCommand, inputFilePath, outputFilePath);

    // Execute the ffmpeg command using system function
    int result = system(fullCommand);

    // Cleanup
    delete[] fullCommand;

    return result;
}
