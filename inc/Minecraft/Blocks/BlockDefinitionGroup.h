#pragma once

class BlockDefinitionGroup {
private:
    int mLastBlockId;

public:
    void registerBlocks();

    int getNextBlockId() {
        return mLastBlockId++;
    }
};