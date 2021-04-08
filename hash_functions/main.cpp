#include <stdint.h>
#include <stdio.h>

#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>

#include "fnv/fnv1a.h"
#include "sip/sip.h"

using namespace std;

enum class HashAlgorithm {
  FNV32,
  FNV64,
  FNV128,
  SIP32,
  SIP64,
  SIP128,
  SIP32H,
  SIP64H,
  SIP128H
};
enum class DataSource { FILE, STRING, STDIN };

int main(int argc, char* argv[])
{
  HashAlgorithm hash = HashAlgorithm::FNV32;
  optional<DataSource> source;
  string source_str;
  bool profile = false;

  for (int i = 1, num_algos = 0; i < argc; i++)
  {
    string arg;

    if (argv[i])
    {
      if (argv[i][0] == '-')
      {
        arg = argv[i] + 1;

        if (arg == "h")
        {
          cout << "hashtest\n\n";
          cout << "Examples:\n";
          cout << "\thashtest [-p] [";
          cout << "--fnv32";
          cout << "|--fnv64";
          cout << "|--fnv128";
          cout << "|--sip32{h}";
          cout << "|--sip64{h}";
          cout << "|--sip128{h}";
          cout << "] ";
          cout << "[-f FILE|-s STRING|FILE]\n";
          cout << "\thashtest -h";
          cout << endl;
          exit(2);
        }
        else if (arg == "p")
        {
          profile = true;
        }
        else if (arg == "-fnv32")
        {
          hash = HashAlgorithm::FNV32;
          num_algos++;
        }
        else if (arg == "-fnv64")
        {
          hash = HashAlgorithm::FNV64;
          num_algos++;
        }
        else if (arg == "-fnv128")
        {
          hash = HashAlgorithm::FNV128;
          num_algos++;
        }
        else if (arg == "-sip32")
        {
          hash = HashAlgorithm::SIP32;
          num_algos++;
        }
        else if (arg == "-sip64")
        {
          hash = HashAlgorithm::SIP64;
          num_algos++;
        }
        else if (arg == "-sip128")
        {
          hash = HashAlgorithm::SIP128;
          num_algos++;
        }
        else if (arg == "-sip32h")
        {
          hash = HashAlgorithm::SIP32H;
          num_algos++;
        }
        else if (arg == "-sip64h")
        {
          hash = HashAlgorithm::SIP64H;
          num_algos++;
        }
        else if (arg == "-sip128h")
        {
          hash = HashAlgorithm::SIP128H;
          num_algos++;
        }
        else if (arg == "s")
        {
          if (source != nullopt)
          {
            cout << "Source already configured" << endl;
            exit(1);
          }

          source = DataSource::STRING;

          i++;
          if (i >= argc || (argv[i] == nullptr))
          {
            cout << "STRING expected after -s" << endl;
            exit(1);
          }

          source_str = argv[i];
        }
        else if (arg == "f")
        {
          if (source != nullopt)
          {
            cout << "Source already configured" << endl;
            exit(1);
          }

          source = DataSource::FILE;

          i++;
          if (i >= argc || (argv[i] == nullptr))
          {
            cout << "FILENAME expected after -f" << endl;
            exit(1);
          }

          source_str = argv[i];
        }
        else
        {
          cout << "Unknown option: " << argv[i] << endl;
          exit(1);
        }
      }
      else
      {
        arg = argv[i];

        if (arg.length())
        {
          if (source != nullopt)
          {
            cout << "Source already configured" << endl;
            exit(1);
          }

          source = DataSource::FILE;
          source_str = arg;
        }
      }
    }

    if (num_algos > 1)
    {
      cout << "Hash algorithm can only be specified once" << endl;
      exit(1);
    }
  }

  // If no file or string is specified, use stdin
  if (source == nullopt) source = DataSource::STDIN;

  if (source == DataSource::FILE)
  {
    auto in = ifstream(source_str.data());

    if (!in.is_open())
    {
      cout << "Could not open file: " << source_str << endl;
      exit(1);
    }

    stringstream sstr;
    sstr << in.rdbuf();
    source_str = sstr.str();
    source = DataSource::STRING;
  }
  else if (source == DataSource::STDIN)
  {
    char ch;
    stringstream sstr;

    while (cin.get(ch))
    {
      sstr << ch;
    }

    source_str = sstr.str();
    source = DataSource::STRING;
  }

  auto start = chrono::high_resolution_clock::now();

  stringstream results;

  switch (hash)
  {
    case HashAlgorithm::FNV32: {
      auto val = Hash::Fnv1a::hash32(source_str.data(), source_str.length());
      results << "fnv-32: ";
      results << "0x";
      results << setfill('0') << setw(8) << hex << val;
      results << endl;
    }
    break;
    case HashAlgorithm::FNV64: {
      auto val = Hash::Fnv1a::hash64(source_str.data(), source_str.length());
      results << "fnv-64: ";
      results << "0x";
      results << setfill('0') << setw(16) << hex << val;
      results << endl;
    }
    break;
    case HashAlgorithm::FNV128: {
      auto val = Hash::Fnv1a::hash128(source_str.data(), source_str.length());
      results << "fnv-128: ";
      results << "0x";
      results << setfill('0') << setw(16) << hex << val.w64[1];
      results << setfill('0') << setw(16) << hex << val.w64[0];
      results << endl;
    }
    break;
    case HashAlgorithm::SIP32: {
      auto val = Hash::Sip::hash32(source_str.data(), source_str.length());
      results << "sip-32: ";
      results << "0x";
      results << setfill('0') << setw(8) << hex << val;
      results << endl;
    }
    break;
    case HashAlgorithm::SIP64: {
      auto val = Hash::Sip::hash64(source_str.data(), source_str.length());
      results << "sip-64: ";
      results << "0x";
      results << setfill('0') << setw(16) << hex << val;
      results << endl;
    }
    break;
    case HashAlgorithm::SIP128: {
      auto val = Hash::Sip::hash128(source_str.data(), source_str.length());
      results << "sip-128: ";
      results << "0x";
      results << setfill('0') << setw(16) << hex << val.w64[1];
      results << setfill('0') << setw(16) << hex << val.w64[0];
      results << endl;
    }
    break;
    case HashAlgorithm::SIP32H: {
      auto val = Hash::Sip::hash32h(source_str.data(), source_str.length());
      results << "sip-32H: ";
      results << "0x";
      results << setfill('0') << setw(8) << hex << val;
      results << endl;
    }
    break;
    case HashAlgorithm::SIP64H: {
      auto val = Hash::Sip::hash64h(source_str.data(), source_str.length());
      results << "sip-64H: ";
      results << "0x";
      results << setfill('0') << setw(16) << hex << val;
      results << endl;
    }
    break;
    case HashAlgorithm::SIP128H: {
      auto val = Hash::Sip::hash128h(source_str.data(), source_str.length());
      results << "sip-128H: ";
      results << "0x";
      results << setfill('0') << setw(16) << hex << val.w64[1];
      results << setfill('0') << setw(16) << hex << val.w64[0];
      results << endl;
    }
    break;
  }

  auto elapsed = chrono::high_resolution_clock::now() - start;
  long long microseconds = chrono::duration_cast<std::chrono::microseconds>(elapsed).count();

  cout << results.str();

  if (profile)
  {
    cout << microseconds << " us" << endl;
    cout << source_str.length() << " bytes" << endl;
  }

  // const char* b = "1234567890abcdefg";
  // val: b6e2fe55b55a0d1f90bbc6ab04080924
  //
  // const char* b = "abcd";
  // val: 696f7cc66e757277b806e97644f1b9e5
  //
  // const char* b = "a";
  // val: d228cb696f1a8caf78912b704e4a8964
  //
  // const char* b = "abcdefghijklmnopqrstuvwxyz1234567890";
  // val: 9c3de1c5da11148ef7c569160e6d4eeb

  // Hash::Sip::hash128();

  return 0;
}
