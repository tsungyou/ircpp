#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

void listFiles(const fs::path& dirPath, int depth = 0) {
    for (const auto& entry : fs::directory_iterator(dirPath)) {
        std::cout << std::string(depth * 2, ' ') << "|-- " << entry.path().filename() << '\n';

        if (fs::is_directory(entry)) {
            listFiles(entry.path(), depth + 1);  // 遞迴進入子目錄
        }
    }
}

int main() {
    fs::path currentPath = fs::current_path();
    std::cout << "Scanning directory: " << currentPath << "\n";
    listFiles(currentPath);
    return 0;
}
