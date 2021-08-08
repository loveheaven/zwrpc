
#pragma once

#include <sstream>
#include "OSConfig.h"
#include <spdlog/spdlog.h>

 
#ifdef OS_WIN32
//strrchr:查找字符在指定字符串从右面开始的第一次出现的位置，如果成功，返回该字符以及后面的字符，如果失败，返回NULL
//strcgr:查找字符在指定字符串首次出现的位置
#define __FILENAME__ (strrchr(__FILE__,'\\')?(strrchr(__FILE__,'\\')+1):__FILE__)
#else
#define __FILENAME__ (strrchr(__FILE__,'/')?(strrchr(__FILE__,'/')+1):__FILE__)
#endif //_WIN32
 
 
#ifndef SUFFIX
//在错误级别的日志后面追加文件名，函数名，行号
#define SUFFIX(msg) std::string(msg).append("  <")\
	.append(__FILENAME__).append("> <").append(__FUNCTION__)\
	.append("> <").append(std::to_string(__LINE__))\
	.append(">").c_str()
#endif //suffix



#define LTrace(msg,...)  SimLog::Instance().GetLogger()->trace(SUFFIX(msg),__VA_ARGS__)
#define LDebug(...)  SimLog::Instance().GetLogger()->debug(__VA_ARGS__)
#define LInfo(...)  SimLog::Instance().GetLogger()->info(__VA_ARGS__)
#define LWarn(...) SimLog::Instance().GetLogger()->warn(__VA_ARGS__)
#define LError(msg,...)  SimLog::Instance().GetLogger()->error(SUFFIX(msg),__VA_ARGS__)
#define LCritical(...)  SimLog::Instance().GetLogger()->critical(__VA_ARGS__)
 
#define BAIDU_CHECK_OP(name, op, val1, val2)                                  \
    if (std::string* _result =                                          \
        Check##name##Impl((val1), (val2),                    \
                                     #val1 " " #op " " #val2))          \
        LInfo(*_result)



// Build the error message string.  This is separate from the "Impl"
// function template because it is not performance critical and so can
// be out of line, while the "Impl" code should be inline.  Caller
// takes ownership of the returned string.
template<class t1, class t2>
std::string* MakeCheckOpString(const t1& v1, const t2& v2, const char* names) {
    std::ostringstream ss;
    ss << names << " (" << v1 << " vs " << v2 << "). ";
    std::string* msg = new std::string(ss.str());
    return msg;
}

// Helper functions for BAIDU_CHECK_OP macro.
// The (int, int) specialization works around the issue that the compiler
// will not instantiate the template version of the function on values of
// unnamed enum type - see comment below.
#define BAIDU_DEFINE_CHECK_OP_IMPL(name, op)                            \
    template <class t1, class t2>                                       \
    inline std::string* Check##name##Impl(const t1& v1, const t2& v2,   \
                                          const char* names) {          \
        if (v1 op v2) return NULL;                                      \
        else return MakeCheckOpString(v1, v2, names);                   \
    }                                                                   \
    inline std::string* Check##name##Impl(int v1, int v2, const char* names) { \
        if (v1 op v2) return NULL;                                      \
        else return MakeCheckOpString(v1, v2, names);                   \
    }
BAIDU_DEFINE_CHECK_OP_IMPL(EQ, ==)
BAIDU_DEFINE_CHECK_OP_IMPL(NE, !=)
BAIDU_DEFINE_CHECK_OP_IMPL(LE, <=)
BAIDU_DEFINE_CHECK_OP_IMPL(LT, < )
BAIDU_DEFINE_CHECK_OP_IMPL(GE, >=)
BAIDU_DEFINE_CHECK_OP_IMPL(GT, > )
#undef BAIDU_DEFINE_CHECK_OP_IMPL

#define CHECK_EQ(val1, val2) BAIDU_CHECK_OP(EQ, ==, val1, val2)
#define CHECK_NE(val1, val2) BAIDU_CHECK_OP(NE, !=, val1, val2)
#define CHECK_LE(val1, val2) BAIDU_CHECK_OP(LE, <=, val1, val2)
#define CHECK_LT(val1, val2) BAIDU_CHECK_OP(LT, < , val1, val2)
#define CHECK_GE(val1, val2) BAIDU_CHECK_OP(GE, >=, val1, val2)
#define CHECK_GT(val1, val2) BAIDU_CHECK_OP(GT, > , val1, val2)

class SimLog
{
private:
	std::shared_ptr<spdlog::logger> my_logger_;
 
public:	
	static SimLog &Instance();
	void InitSimLog(std::string logger_name, std::string file_name, int log_level = spdlog::level::trace);
 
	void SetLevel(int level = spdlog::level::trace);
 
	auto GetLogger()-> decltype(my_logger_)
	{
		return my_logger_;
	}
	
private:
	SimLog();
	~SimLog();
	DISALLOW_COPY_AND_ASSIGN(SimLog);
 
};

