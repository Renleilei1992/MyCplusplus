
/* 一个用于windows系统的简单管理 Handle 句柄对象及时释放的类  */
/*
struct HandleObject {

    HandleObject(HANDLE h)
        :_handle(h)
    {
    }
    HandleObject() = default;

    HandleObject& operator=(HANDLE h)
    {
        _handle = h;
        return *this;
    }

    HandleObject(const HandleObject& other) = delete;

    HandleObject(HandleObject&& other)
    {
        _handle = other._handle;
        other._handle = INVALID_HANDLE_VALUE;
    }

    ~HandleObject()
    {
        if (_handle && INVALID_HANDLE_VALUE != _handle)
            CloseHandle(_handle);
    }


private:
    HANDLE _handle = INVALID_HANDLE_VALUE;
};
*/