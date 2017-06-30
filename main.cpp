#include "configuration.h"

#include <tnt/tntnet.h>

#include <cxxtools/arg.h>
#include <cxxtools/xml/xml.h>
#include <cxxtools/log.h>

#include <iostream>
#include <fstream>

log_define("weblauf")

int main(int argc, char* argv[])
{
  try
  {
    Configuration& configuration = Configuration::it();
    cxxtools::Arg<const char*> configfilename(argc, argv, 'c', "weblauf.xml");

    std::ifstream configfile(configfilename);
    if (!configfile)
      throw std::runtime_error(std::string("could not open configuration file ") + configfilename.getValue());

    configfile >> cxxtools::xml::Xml(configuration);

    log_init(configuration.logConfiguration);

    tnt::Tntnet app;
    app.init(configuration);

    if (!configuration.htdocs().empty())
    {
      app.mapUrl("^/(.*)", "static@tntnet")
         .setPathInfo(configuration.htdocs() + "/$1");
    }

    app.mapUrl("^/(.*)", "modules")
       .setPathInfo("$1");

    // map static resources
    app.mapUrl("^/(.*)", "resources")
       .setPathInfo("resources/$1");

    // map / to weblauf2
    app.mapUrl("^/$", "webmain");

    app.mapUrl("^/(.*)\\.action$", "actionmain")
       .setArg("next", "$1");

    // map /comp to comp
    app.mapUrl("^/([^.].+)$", "$1");

    // map /comp.ext to ext/comp
    app.mapUrl("^/(.+)\\.(.+)$", "$2/$1");

    app.run();
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }
}

