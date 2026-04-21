#include "GetPot"
#include "json.hpp"
#include "readParameters.hpp"
#include <fstream>
parameters
readParameters(std::string const &filename, bool verbose)
{
  parameters defaults;
  // checks if file exists and is readable
  std::ifstream check(filename);
  if(!check) //or if(check.bad())
    {
      std::cerr << "ERROR: Parameter file " << filename << " does not exist"
                << std::endl;
      std::cerr << "Reverting to default values." << std::endl;
      if(verbose)
        std::cout << defaults;
      check.close();
      return defaults;
    }
  else
    check.close();

  // open file with a getpot object and pass as c string the content of filename
  // getpot reads the file and parse its content, organize internal database to store the content
  // we can interrogate the getpot file
  GetPot     ifile(filename.c_str());
  parameters values;
  // Read parameters from getpot ddata base
  // Read parameters from GetPot database
  // check if the file contains a variable with that name and get its value, if not get a default value
  values.itermax = ifile("itermax", defaults.itermax);
  values.toler = ifile("toler", defaults.toler);
  values.L = ifile("L", defaults.L);
  values.a1 = ifile("a1", defaults.a1);
  values.a2 = ifile("a2", defaults.a2);
  values.To = ifile("To", defaults.To);
  values.Te = ifile("Te", defaults.Te);
  values.k = ifile("k", defaults.k);
  values.hc = ifile("hc", defaults.hc);
  values.M = ifile("M", defaults.M);
  values.solverType = ifile("solverType", defaults.solverType);
  {
    std::cout << "PARAMETER VALUES IN GETPOT FILE" << "\n";
    ifile.print();
    std::cout << std::endl;
    std::cout << "ACTUAL VALUES" << "\n" << values;
  }
  return values;
}

parameters
readParameters_json(std::string const &filename, bool verbose)
{
  // Parameter default constructor fills it with the defaults values
  parameters defaults;
  // checks if file exixts and is readable
  std::ifstream check(filename);
  if(!check)
    {
      std::cerr << "ERROR: Parameter file " << filename << " does not exist"
                << std::endl;
      std::cerr << "Reverting to default values." << std::endl;
      if(verbose)
        std::cout << defaults;
      check.close();
      return defaults;
    }
  else
    check.close();

  std::ifstream  jfile(filename);
  nlohmann::json ifile;
  jfile >> ifile;
  parameters values;
  // Read parameters from JSON object
  values.itermax = ifile.value("itermax", defaults.itermax);
  values.toler = ifile.value("toler", defaults.toler);
  values.L = ifile.value("L", defaults.L);
  values.a1 = ifile.value("a1", defaults.a1);
  values.a2 = ifile.value("a2", defaults.a2);
  values.To = ifile.value("To", defaults.To);
  values.Te = ifile.value("Te", defaults.Te);
  values.k = ifile.value("k", defaults.k);
  values.hc = ifile.value("hc", defaults.hc);
  values.M = ifile.value("M", defaults.M);
  values.solverType = ifile.value("solverType", defaults.solverType);
  if(verbose)
    {
      std::cout << "PARAMETER VALUES IN JSON FILE" << "\n";
      std::cout << std::setw(4) << ifile;
      std::cout << std::endl;
      std::cout << "ACTUAL VALUES" << "\n" << values;
    }
  return values;
}
