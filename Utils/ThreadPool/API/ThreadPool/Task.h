#pragma once

class Task {
public:
    Task() = default;
    
    virtual ~Task() = default;
    
    virtual void Execute() = 0;
};
