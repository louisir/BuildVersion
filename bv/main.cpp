#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <sstream>

int main(int argc, char* argv[])
{
    // 检查是否至少有两个参数
    if (argc < 2)
    {
        std::cout << "Usage: <executable> <file path>" << std::endl;
        return 1;
    }

    bool b_output = false;

    // 遍历命令行参数
    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];

        // 检查是否存在 --out 参数
        if (arg == "--out")
        {
            b_output = true;
        }
    }

    // 获取文件路径
    std::string filePath = argv[1];
    //    std::cout << "File path: " << filePath << std::endl;

    // 打开文件以读取内容
    std::ifstream file(filePath);
    if (!file.is_open())
    {
        std::cout << "Failed to open file." << std::endl;
        return 1;
    }

    // 读build_counter
    std::string build_counter;
    std::getline(file, build_counter);

    // 关闭文件
    file.close();

    long build_counter_l = std::stol(build_counter);
    if(b_output){
        // 打开文件以写入内容
        std::ofstream outputFile(filePath);
        if (!outputFile.is_open())
        {
            //        std::cout << "Failed to open file for writing." << std::endl;
            return 1;
        }

        build_counter_l++;
        outputFile << build_counter_l;

        // 关闭输出文件
        outputFile.close();
    }

    std::time_t currentTime = std::time(nullptr);
    std::tm localTime;
#ifdef _WIN32
    localtime_s(&localTime, &currentTime);
#endif

#ifdef __linux__
    localtime_r(&currentTime, &localTime);
#endif
//    // 格式化日期和时间
//    std::stringstream ss;
//    ss << std::put_time(&localTime, "%Y-%m-%d %H:%M:%S");
//    std::cout << build_counter_l << " | " << ss.str() << std::endl;
    std::cout << build_counter_l << std::endl;
    return 0;
}
