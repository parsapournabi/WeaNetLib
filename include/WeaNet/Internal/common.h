#ifndef COMMON_H
#define COMMON_H

/// Network base class interface.
class INetwork {
private:
    virtual void createSocket() = 0;
public:
    virtual void close() = 0;
};

#endif

