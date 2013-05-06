#ifndef CONTEXT_H_INCLUDED
#define CONTEXT_H_INCLUDED

#include <stdio.h>

class Context{

public:

    Context();
    ~Context();

    void        SetCurrent(bool current);
    static void SetCurrentContext(Context * context);
    static      Context * GetCurrentContext();

private:
    bool    m_current;

};



#endif // CONTEXT_H_INCLUDED
