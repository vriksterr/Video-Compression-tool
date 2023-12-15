#include <cstdlib>
#include <cstdio>
#include <filesystem>
#include <iostream>
#include <unordered_set>

namespace fs = std::filesystem;

// Set of video file extensions to consider
const std::unordered_set<std::string> videoExtensions = {".mp4", ".mkv", ".avi", ".mov", ".wmv", ".flv", ".webm"};

int convertVideo(const char* inputFilePath, const char* outputFilePath) {
    // Construct the ffmpeg command with the modified file locations
    const char* ffmpegCommand = "ffmpeg -i \"%s\" -c:v hevc_nvenc -preset medium -b:v 6000k -minrate 4000k -maxrate 16000k -bufsize 16000k -c:a aac -c:s mov_text -map 0 \"%s\"";

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

void processDirectory(const fs::path& directory) {
    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.is_regular_file()) {
            const std::string inputFilePath = entry.path().string();
            const std::string outputDirectory = entry.path().parent_path().string();
            const std::string fileName = entry.path().filename().string();
            const std::string outputFilePath = outputDirectory + "\\" + fileName + ".mp4";

            // Check if the file has a video extension
            if (videoExtensions.find(entry.path().extension().string()) != videoExtensions.end()) {
                std::cout << "Converting: " << inputFilePath << std::endl;

                // Convert the video
                int result = convertVideo(inputFilePath.c_str(), outputFilePath.c_str());

                if (result == 0) {
                    std::cout << "Conversion successful!" << std::endl;
                } else {
                    std::cerr << "Conversion failed with error code: " << result << std::endl;
                }
            }
        } else if (entry.is_directory()) {
            // Recursive call for subdirectories
            processDirectory(entry);
        }
    }
}

int main() {
    const char* inputDirectory = "D:\\Downloads\\ffmpeg\\New folder";

    // Start processing the top-level directory
    processDirectory(inputDirectory);

    return 0;
}
