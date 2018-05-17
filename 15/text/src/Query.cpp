//
// Created by qinhan on 2018/5/17.
//
#include "include/Query.h"

std::ostream &operator<<(const std::ostream &os, const Query &query) {
    return os<<query->req();
}


