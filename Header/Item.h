#pragma once
#include <afx.h>

struct Item
{
    int     id;          // sample payload
    CTime   expiryTime;  // absolute expiry time

    Item(int _id, const CTime& expiry)
        : id(_id), expiryTime(expiry)
    {
    }
};
