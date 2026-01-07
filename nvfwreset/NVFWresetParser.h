#ifndef NVFWRESET_PARSER_H
#define NVFWRESET_PARSER_H

#include <string>
#include <memory>
#include "cmdparser/cmdparser.h"
#include "NVFWresetParams.h"
#include "common/tools_version.h"

class NVFWresetParser : public CommandLineRequester
{
public:
    NVFWresetParser();
    ~NVFWresetParser(){};
    ParseStatus Parse(int argc, char** argv);
    NVFWresetParams* getParsedParams() const { return _parsedParams.get(); }
    virtual ParseStatus HandleOption(std::string name, std::string value);

protected:
    CommandLineParser _cmdParser;
    ParseStatus ParseCommand(std::string command);
    virtual void initOptions();

private:
    std::unique_ptr<NVFWresetParams> _parsedParams;
};

#endif // NVFWRESET_PARSER_H
