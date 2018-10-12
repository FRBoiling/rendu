//
// Created by boil on 18-10-12.
//

#include <string>
#include <rendu/log/Logger.h>

using namespace std;
using namespace rendu::log;

class Foo {
public:
//    Foo(const std::string &Copied1, std::string &ReadOnly1)
//            : Copied(Copied1), ReadOnly(ReadOnly1) {
//        LOG_DEBUG << "const-references";
//    }

    Foo(std::string Copied, const std::string &ReadOnly)
            : Copied(std::move(Copied)), ReadOnly(ReadOnly) {
        LOG_DEBUG<<"move...";
    }

public:
    std::string Copied;
    const std::string &ReadOnly;
};

std::string get_cwd() {
    return "get_cwd_str";
};

void f(std::string &Path) {
    // The parameter corresponding to 'get_cwd()' is move-constructed. By
    // using pass-by-value in the Foo constructor we managed to avoid a
    // copy-construction.
    LOG_DEBUG << Path ;

    Foo foo(get_cwd(), Path);
    Path = "22222";
    LOG_DEBUG << foo.ReadOnly << "\n";

}

int main() {
    Logger::setLogLevel(DEBUG);

    string strValue = "right value";

    f(strValue);

    LOG_DEBUG << strValue;
}