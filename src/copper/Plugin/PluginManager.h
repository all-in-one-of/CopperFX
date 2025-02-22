#ifndef PLUGIN_MANAGER_H
#define PLUGIN_MANAGER_H

#include <boost/dll/runtime_symbol_info.hpp> // for program_location()
#include <boost/dll/shared_library.hpp>
#include <boost/make_shared.hpp>
#include <boost/container/map.hpp>
#include <boost/filesystem.hpp>
#include <iostream>

#include "copper/Util/Singleton.h"
#include "copper/Plugin/PluginApi.h"

namespace dll = boost::dll;


// This class takes care of loading all the core related plugins like operators and data types
// It also registers internally defined ones..
// For gui related plugins we'll use another manager so we can completely skip scanning, registering and loading 
// them when not needed, like command line processing...
// And yes it's a singleton. There is no foreseeble need to have two instances. But...

namespace copper {

class PluginManager: public Singleton<PluginManager> {
  public:
    PluginManager(const boost::filesystem::path& plugins_directory);

    void printPluginLibs() const;

    bool loadPluginLib(const boost::filesystem::path& plugin_file_path);

    std::size_t countPluginLibs() const;

  private:
    // Name => plugin
    typedef boost::container::map<std::string, dll::shared_library> plugins_t;

    boost::filesystem::path _plugins_directory;
    plugins_t               _plugins;

    // loads all plugins in plugins_directory_
    void loadAll();

    // Gets `my_plugin_api` instance using "create_plugin" or "plugin" imports,
    // stores plugin with its name in the `plugins_` map.
    void insertPlugin(BOOST_RV_REF(dll::shared_library) lib);
};

inline bool is_shared_library(const boost::filesystem::path& p) {
    const std::string s = p.string();
    return (s.find(".dll") != std::string::npos || s.find(".so") != std::string::npos || s.find(".dylib") != std::string::npos)
            && s.find(".lib") == std::string::npos
            && s.find(".exp") == std::string::npos
            && s.find(".pdb") == std::string::npos
            && s.find(".manifest") == std::string::npos
            && s.find(".rsp") == std::string::npos
            && s.find(".obj") == std::string::npos
            && s.find(".a") == std::string::npos;
}

}

#endif // PL_PLUGINMANAGER_H