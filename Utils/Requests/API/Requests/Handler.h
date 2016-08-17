#pragma once

#include <functional>

namespace Http {
    class Handler {
    public:
        Handler() = default;

        virtual ~Handler() = default;

        virtual void terminate() = 0;

        virtual void ifPending(std::function<void()> ifPendingProc) = 0;
    };
}
