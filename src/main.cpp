#include "cppScratch/test.hpp"
#include "cppScratch/dal/dal.hpp"

#include <vector>
#include <string>

#include <nlohmann/json.hpp>
#include <boost/program_options.hpp>

using namespace std;
namespace po = boost::program_options;

void on_age(int age)
{
  std::cout << "On age: " << age << '\n';
}

int main(int argc, const char *argv[]) {
    ////////////
    // DECLARE
    ////////////

    try{

        int def;
        po::options_description desc("Allowed options");
        desc.add_options()
            ("help", "produce help message")
            ("compression,c", po::value<int>(), "set compression level")
            ("def,d", po::value<int>(&def)->default_value(10), "set def level")
            ("abc", po::value<int>()->default_value(25), "set abc level")
            ("phone", po::value<std::vector<std::string>>()->multitoken()->
        zero_tokens()->composing(), "Phone")
            ("age,a", po::value<int>()->notifier(on_age), "age")
            ("config", po::value<std::string>(), "Config file")
        ;

        po::options_description other("Other");
        desc.add_options()
            ("other-option,o", po::value<int>(), "another option")
        ;

        // Hidden options, will be allowed both on command line and
        // in config file, but will not be shown to the user.
        po::options_description hidden("Hidden options");
        hidden.add_options()
            ("input-file", po::value< vector<string> >(), "input file")
        ;  

        po::positional_options_description p;
        p.add("phone", -1);

        po::options_description cmdline_options;
        cmdline_options.add(desc).add(other).add(hidden);

        po::options_description config_file_options;
        config_file_options.add(desc).add(hidden);

        po::options_description visible("Allowed options");
        visible.add(desc).add(other);

        ////////////
        // PARSE
        ////////////

        po::variables_map vm;
        po::store(po::command_line_parser(argc, argv)
                .options(desc)
                .positional(p)
                .run(), 
            vm);
        if (vm.count("config"))
        {
            cout << "Attempting file config load" << endl;
            std::ifstream ifs{vm["config"].as<std::string>().c_str()};
            if (ifs) {
                cout << "File opened, loading..." << endl;
                po::store(po::parse_config_file(ifs, config_file_options), vm);
            }
        }
        po::notify(vm);    

        if (vm.count("help")) {
            cout << desc << "\n";
            return 1;
        }

        if (vm.count("compression")) {
            cout << "Compression level was set to " 
        << vm["compression"].as<int>() << ".\n";
        } else {
            cout << "Compression level was not set.\n";
        }

        if (vm.count("def")) {
            cout << "def level was set to " 
        << vm["def"].as<int>() << ".\n";
        } else {
            cout << "def level was not set.\n";
        }

        // if (vm.count("phone"))
        // {
        //     cout << "phone are: " 
        //         << vm["phone"].as< vector<string> >() << "\n";
        // }

        cout << "hello world" << endl;
        dal_func();
        example_func();
    }
    catch (const po::error &ex)
    {
        std::cerr << ex.what() << '\n';
    }
}