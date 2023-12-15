#include <iostream>
#include <cstdlib>
#include <filesystem>
#include <sstream>

int main() {
    // Set the input directory
    const std::string inputDirectory = "D:\\Downloads\\ffmpeg\\New folder";

    // Set the NVENC codec and CBR bitrate
    const std::string codec = "hevc_nvenc";
    const std::string bitrate = "4000k";

    // Iterate through each file in the input directory
    for (const auto& entry : std::filesystem::directory_iterator(inputDirectory)) {
        if (entry.is_regular_file()) {
            // Extract file information
            std::string inputFile = entry.path().string();
            std::string outputFileName = entry.path().filename().stem().string(); // Extract the file name without extension
            std::string outputFileExtension = entry.path().filename().extension().string(); // Extract the file extension

            // Create the new file name
            std::string newFileName = outputFileName + ".new" + outputFileExtension;
            std::string outputFile = inputDirectory + "\\" + newFileName;

            // FFmpeg command for conversion
            std::string ffmpegCommand = "ffmpeg -hwaccels cuda -i \"" + inputFile + "\" -c:v " + codec +
                                        " -b:v " + bitrate + " -c:a copy -c:s copy \"" + outputFile + "\"";

            // Execute FFmpeg command
            int result = std::system(ffmpegCommand.c_str());

            // Check if the conversion was successful
            if (result == 0) {
                // Delete the original file
                std::filesystem::remove(inputFile);
                std::cout << "Conversion successful for: " << inputDirectory << "\\" << newFileName << std::endl;
            } else {
                std::cerr << "Error during conversion for: " << inputDirectory << "\\" << newFileName << std::endl;
            }
        }
    }

    return 0;
}
