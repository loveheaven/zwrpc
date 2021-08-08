#include "logging.h"
#include <spdlog/sinks/daily_file_sink.h>

SimLog& SimLog::Instance()
{
	static SimLog log;
	return log;
}
void SimLog::InitSimLog(std::string logger_name, std::string file_name, int log_level)
{
	//设置日志等级
	//spdlog::set_level(static_cast<spdlog::level::level_enum>(log_level));
	
	my_logger_ = spdlog::daily_logger_mt(logger_name, file_name, 0, 0);
	
	spdlog::set_pattern("[%Y-%m-%d %T][thread %t][%l]%v");   //设置logger的输出格式
 
	//当遇到错误级别以上的立刻刷新到日志
	my_logger_->flush_on(spdlog::level::info);
 
}

 
SimLog::SimLog()
{
}
 
 
SimLog::~SimLog()
{
	//spdlog::drop_all();
}
void SimLog::SetLevel(int level)
{
	spdlog::set_level(static_cast<spdlog::level::level_enum>(level));
}
