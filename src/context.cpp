#include "context.h"

static Context *currentContext = NULL;

Context::Context()
{
    m_current = false;
}

Context::~Context()
{

}

void Context::SetCurrent(bool current)
{
    m_current = current;

    if (!m_current && m_disposed)
        delete this;
}

void Context::SetCurrentContext(Context* context)
{
    Context* oldContext = GetCurrentContext();

    if (oldContext != context)
    {
        if (oldContext != 0)
            oldContext->SetCurrent(false);

        currentContext = context;

        if (context != 0)
            context->SetCurrent(true);
    }1
}

Context* Context::GetCurrentContext()
{
    return currentContext;
}
