#pragma once

namespace Http {
    enum class RequestExecutionStatus {
        UNKNOWN, PENDING, EXECUTING, TERMINATED, FINISHED
    };
}
