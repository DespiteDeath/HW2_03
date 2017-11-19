#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include <future>


using namespace std;
namespace fs = boost::filesystem;

double getFileSize(const fs::path& pathToCheck, double size) {
    size = size + fs::file_size(pathToCheck);
    return size;
}

string getFileName(string fileAddress) {
    fs::path filePath = fileAddress;
    fs::path textFile = filePath.filename();
    return textFile.string();
}

string getFileData(string fileAddress) {
    fs::path filePath = fileAddress;
    std::time_t ftime = fs::last_write_time(filePath);
    return asctime(gmtime(&ftime));
}

int infoFile(string fileName, string fileData, double fileSize) {

    std::cout << "\nFilename in dir: " << fileName << std::endl;
    std::cout << "Time: " << fileData << std::endl;
    std::cout << "Size: " << fileSize/1000 << " Kb" << std::endl;
    return 0;
}

void DisplayFileInfo(string fileAddress) {

    std::packaged_task<string(string)> taskName(getFileName);
    std::packaged_task<string(string)> taskData(getFileData);
    std::packaged_task<double(string, double)> taskSize(getFileSize);
    std::packaged_task<int(string, string, double)> taskFile(infoFile);

    std::future<string> fileName = taskName.get_future();
    std::future<string> fileData = taskData.get_future();
    std::future<double> fileSize = taskSize.get_future();
    std::future<int> putInto = taskFile.get_future();

    taskName(fileAddress);
    taskData(fileAddress);
    taskSize(fileAddress, 0);
    taskFile(fileName.get(), fileData.get(), fileSize.get());

}


int main(int argc, char* argv[])
{
  string some;

  try {
    for(int i = 1; i < argc; i++){
      some = argv[i];
      DisplayFileInfo(argv[i]);
    }
  }
  catch(const exception& e) {
    cout << e.what() << endl;
  }
}
