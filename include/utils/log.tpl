namespace utils
{
namespace log
{
    template <typename ... Args>
    void log(LOG_LVL lvl,Args&& ... args)
    {
        switch(lvl)
        {
            case INFO:
                info(args...);break;
            case WARNNING:
                warnning(args ...);break;
            case ERROR:
                error(args ...); break;
            case CRITICAL:
                critical(args ...);break;
            default:
                error("utils::log::log()","Unknow value of lvl. Message show as info:");
                info(args ...);
                break;

        }
    }
}
}
