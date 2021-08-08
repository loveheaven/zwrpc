#include "logging.h"

int main(int argc, char** argv) {

SimLog::Instance().InitSimLog("logTest", std::string("logs/log.txt"), spdlog::level::info);
SimLog::Instance().SetLevel(spdlog::level::info);
    
}