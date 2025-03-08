#include <iostream> // cout
#include <filesystem>
#include <fstream>
#include <vector>

enum Analysis {
    eMonthly = 1,
    eAnnual
};

struct LeisureCosts {
    double eatOut;
    double streaming;
    double cashOut;
    double internetPayments;

    double getTotal() {
        return eatOut + streaming + cashOut + internetPayments;
    }
};

struct Costs {
    double food;
    double petrol;
    double rent;
    double gas;
    double electricity;
    double carLoan;
    double foodAtWork;
    LeisureCosts leisureCosts;

    double getTotal() {
        return food + petrol + rent + gas + electricity + carLoan + foodAtWork + leisureCosts.getTotal();
    }
};

struct MoneyReport{
    double income;
    Costs  costs;
    
    double getSavings() {
        return income - costs.getTotal();
    }
};

struct ReportEntry {
    enum EntryPos{
        eOperationDate,
        ePayDate,
        eConceptPayment,
        eAmount
    };
    std::vector<std::string> entryColumns;
};

std::vector<ReportEntry> reportEntries;

int main(int argc,      // Number of strings in array argv
          char *argv[])   // Array of command-line argument strings
{
    std::string pathFiles("");

    std::cout << "-----------------Welcome to the money report program!-----------------" << std::endl;
    bool isValidResponse = false;
    int optionSelected(0);
    do {
        std::cout << "Please select one of the options:" << std::endl;
        std::cout << "1) Monthly report" << std::endl;
        std::cout << "2) Annual report" << std::endl;
        std::string response("");
        std::cin >> response;
        try
        {
            optionSelected = std::stoi(response);
        }
        catch (const std::invalid_argument&) {
            std::cout << "Error: String '" << response << "' is not a valid number\n";
        }
        catch (const std::out_of_range&) {
            std::cout << "Error: Number '" << response << "' is too large or small\n";
        }
        switch (optionSelected){
            case eMonthly:
                isValidResponse = true;
                std::cout << "You selected Montly report." << std::endl;
                break;
            case eAnnual:
                isValidResponse = true;
                std::cout << "You selected Annual report." << std::endl;
                break;
            default:
                std::cout << "Invalid response." << std::endl;
                break;
        }
    } while(!isValidResponse);

    isValidResponse = false;
    std::filesystem::path pathFile;
    do
    {
        std::cout << "Now you have to write the full path of the file which contains bank data to analyze"  << std::endl;
        std::cin >> pathFiles;
        pathFile = std::filesystem::path(pathFiles);
        if (!std::filesystem::exists(pathFile))
        {
            std::cout << "The file you write does not exist, try again" << std::endl;
        }
        else
        {
            isValidResponse = true;
        }
    }while(!isValidResponse);

    // Read from the text file
    std::ifstream reportFile(pathFile.string());
    std::string line;
    if(reportFile.is_open()) {
        while (getline(reportFile, line))
        {
            if(line.empty()) {
                break;
            } else if(line.find("FECHA VALOR") != std::string::npos) {
                continue;
            }
            std::cout << "Read line: " << line << std::endl;
            ReportEntry entry;
            int index = 0;
            size_t pos = 0;
            while ((pos = line.find(";")) != std::string::npos)
            {
                entry.entryColumns.push_back(line.substr(0, pos));
                line.erase(0, pos + 1);
            }
            reportEntries.push_back(entry);
        }
        reportFile.close();
    }

    std::cout << "Number of entries the report you want to analyze has: " << reportEntries.size() << std::endl;

    return 0;
}