#define USE_BOOST

#ifdef USE_BOOST
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#else
#include "filesystem.h"
#endif

#include <stdio.h>

#ifdef USE_BOOST

int foo(int i) {
    return i+1;
}

int main() {
    boost::filesystem::path p(".");
    boost::filesystem::directory_iterator it(p), dirEnd;
    for (; it!= dirEnd; ++it) {

        boost::filesystem::directory_entry* entry = it.operator->();

        operator==(it->path().extension(), "adb");

        if (boost::filesystem::is_regular_file(entry->status())) {
            printf("%s \n", it->path().string().c_str());
        }
    }
}
#else
int main() {
    mstflint::common::filesystem::path p("/");
    mstflint::common::filesystem::directory_iterator it(p), end;
    for (; operator!=(it, end); ++it) {

        mstflint::common::filesystem::directory_entry* entry = it.operator->();

        if (mstflint::common::filesystem::is_regular_file(it->status())) {
            printf("%s \n", it->path().string().c_str());
            fflush(stdout);
        }
    }
}
#endif
