#pragma once

enum class QueueOperationStatus {
    SUCCESS , 
    FULL    , 
    EMPTY   , 
    BUSY    , 
    CLOSED
};
