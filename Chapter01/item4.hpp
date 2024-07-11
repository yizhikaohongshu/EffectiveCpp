#include <iostream>

class FileSystem
{
public:
    std::size_t numDisks() const { return 10; }
};

extern FileSystem tfs;
