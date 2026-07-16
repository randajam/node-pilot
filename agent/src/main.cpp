#include "Application.hpp"
#include "Config.hpp"
#include "ConfigLoader.hpp"

int main() {
    config::Config config = config::ConfigLoader::load("config.json");
    Application app(config);
    return app.run();
}