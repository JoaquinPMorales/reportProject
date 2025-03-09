#include <iostream> // cout
#include <filesystem>
#include <fstream>
#include <vector>

enum Analysis {
    eMonthly = 1,
    eAnnual
};

static const std::vector<std::string> eatOutKey = {"glovo", "justEat", "BurguerKing", "McDonalds", "Restaurante"};
static const std::vector<std::string> streamingKey = {"netflix", "AmazonPrime"};
static const std::vector<std::string> cashOutKey = {"Retirada de efectivo"};
static const std::vector<std::string> internetPaymentsKeys = {"Paypal", "Amazon", "Compra Internet"};
static const std::vector<std::string> foodKeys = {"Mercadona", "Lidl"};
static const std::vector<std::string> petrolKeys = {"Alcampo"};
static const std::vector<std::string> rentKeys = {"Alquiler"};
static const std::vector<std::string> gasKeys = {"Iberdrola Gas"};
static const std::vector<std::string> electricityKeys = {"Iberdrola Electricidad"};
static const std::vector<std::string> carLoanKey = {"Consumer Finance", "Parking", "Linea Directa"};
static const std::vector<std::string> foodAtWorkKeys = {"Comida", "Siemens Getafe", "Desayuno"};

struct LeisureCosts {
    double eatOut = 0;
    double streaming = 0;
    double cashOut = 0;
    double internetPayments = 0;

    double getLeisureCosts() {
        return eatOut + streaming + cashOut + internetPayments;
    }
};

struct Costs {
    double food = 0;
    double petrol = 0;
    double rent = 0;
    double gas = 0;
    double electricity = 0;
    double carLoan = 0;
    double foodAtWork = 0;
    LeisureCosts leisureCosts;
    double generalCosts = 0;

    double getTotalCosts() {
        return generalCosts + food + petrol + rent + gas + electricity + carLoan + foodAtWork + leisureCosts.getLeisureCosts();
    }
};

struct MoneyReport{
    double income = 0;
    Costs  costs;
    
    double getSavings() {
        return income - costs.getTotalCosts();
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

Analysis analysisType;

void filterEntryCosts(const ReportEntry& entry, MoneyReport& finalReport)
{
    size_t pos = std::string::npos;
    //bool hasBeenAsigned = false;
    // Filter eat out payments
    for (size_t i = 0; i < eatOutKey.size(); ++i)
    {
        if(std::string::npos != entry.entryColumns.at(ReportEntry::eConceptPayment).find(eatOutKey.at(i)))
        {
            finalReport.costs.leisureCosts.eatOut += stod(entry.entryColumns.at(ReportEntry::eAmount));
            return;
        }
    }

    // Filter streaming payments
    for (size_t i = 0; i < streamingKey.size(); ++i)
    {
        if(std::string::npos != entry.entryColumns.at(ReportEntry::eConceptPayment).find(streamingKey.at(i)))
        {
            finalReport.costs.leisureCosts.streaming += stod(entry.entryColumns.at(ReportEntry::eAmount));
            return;
        }
    }

    // Filter cashout
    for (size_t i = 0; i < cashOutKey.size(); ++i)
    {
        if(std::string::npos != entry.entryColumns.at(ReportEntry::eConceptPayment).find(cashOutKey.at(i)))
        {
            finalReport.costs.leisureCosts.cashOut += stod(entry.entryColumns.at(ReportEntry::eAmount));
            return;
        }
    }

    // Filter Food payments
    for (size_t i = 0; i < foodKeys.size(); ++i)
    {
        if(std::string::npos != entry.entryColumns.at(ReportEntry::eConceptPayment).find(foodKeys.at(i)))
        {
            finalReport.costs.food += stod(entry.entryColumns.at(ReportEntry::eAmount));
            return;
        }
    }

    // Filter Petrol payments
    for (size_t i = 0; i < petrolKeys.size(); ++i)
    {
        if(std::string::npos != entry.entryColumns.at(ReportEntry::eConceptPayment).find(petrolKeys.at(i)))
        {
            finalReport.costs.petrol += stod(entry.entryColumns.at(ReportEntry::eAmount));
            return;
        }
    }

    // Filter Rent payments
    for (size_t i = 0; i < rentKeys.size(); ++i)
    {
        if(std::string::npos != entry.entryColumns.at(ReportEntry::eConceptPayment).find(rentKeys.at(i)))
        {
            finalReport.costs.rent += stod(entry.entryColumns.at(ReportEntry::eAmount));
            return;
        }
    }

    // Filter gas payments
    for (size_t i = 0; i < gasKeys.size(); ++i)
    {
        if(std::string::npos != entry.entryColumns.at(ReportEntry::eConceptPayment).find(gasKeys.at(i)))
        {
            finalReport.costs.gas += stod(entry.entryColumns.at(ReportEntry::eAmount));
            return;
        }
    }

    // Filter electricity payments
    for (size_t i = 0; i < electricityKeys.size(); ++i)
    {
        if(std::string::npos != entry.entryColumns.at(ReportEntry::eConceptPayment).find(electricityKeys.at(i)))
        {
            finalReport.costs.electricity += stod(entry.entryColumns.at(ReportEntry::eAmount));
            return;
        }
    }

    // Filter car loan payments
    for (size_t i = 0; i < carLoanKey.size(); ++i)
    {
        if(std::string::npos != entry.entryColumns.at(ReportEntry::eConceptPayment).find(carLoanKey.at(i)))
        {
            finalReport.costs.carLoan += stod(entry.entryColumns.at(ReportEntry::eAmount));
            return;
        }
    }

    // Filter food at work payments
    for (size_t i = 0; i < foodAtWorkKeys.size(); ++i)
    {
        if(std::string::npos != entry.entryColumns.at(ReportEntry::eConceptPayment).find(foodAtWorkKeys.at(i)))
        {
            finalReport.costs.foodAtWork += stod(entry.entryColumns.at(ReportEntry::eAmount));
            return;
        }
    }

    // Filter Internet payments
    for (size_t i = 0; i < internetPaymentsKeys.size(); ++i)
    {
        if(std::string::npos != entry.entryColumns.at(ReportEntry::eConceptPayment).find(internetPaymentsKeys.at(i)))
        {
            finalReport.costs.leisureCosts.internetPayments += stod(entry.entryColumns.at(ReportEntry::eAmount));
            return;
        }
    }

    std::cout << "Payment not filtered: " << entry.entryColumns.at(ReportEntry::eConceptPayment) << std::endl;
    finalReport.costs.generalCosts += stod(entry.entryColumns.at(ReportEntry::eAmount));
    
}

void generateReport(const std::vector<ReportEntry>& entries, MoneyReport& finalReport) {
    for (size_t i = 0; i < entries.size(); i++)
    {
        double amount = stod(entries.at(i).entryColumns.at(ReportEntry::eAmount));
        if(amount > 0.0) {
            finalReport.income += amount;
        } else {
            filterEntryCosts(entries.at(i), finalReport);
        }
    }
    
}

void printReport(MoneyReport& finalReport) {
    std::cout << "-----------------You final report!-----------------" << std::endl;
    if(analysisType == eAnnual)
        std::cout << "You selected Annual report" << std::endl;
    else
        std::cout << "You selected Montly report" << std::endl;
    
    std::cout << "Your incomes are: " << finalReport.income << std::endl;
    std::cout << "-----------------Costs-----------------" << std::endl;
    std::cout << "Your eat out costs: " << finalReport.costs.leisureCosts.eatOut << std::endl;
    std::cout << "Your internet payments: " << finalReport.costs.leisureCosts.internetPayments << std::endl;
    std::cout << "Your streaming costs: " << finalReport.costs.leisureCosts.streaming << std::endl;
    std::cout << "Your cash out: " << finalReport.costs.leisureCosts.cashOut << std::endl;
    std::cout << "Your total leisure costs are: " << finalReport.costs.leisureCosts.getLeisureCosts() << std::endl;

    std::cout << "Your food costs: " << finalReport.costs.food << std::endl;
    std::cout << "Your petrol: " << finalReport.costs.petrol << std::endl;
    std::cout << "Your rent costs: " << finalReport.costs.rent << std::endl;
    std::cout << "Your gas costs: " << finalReport.costs.gas << std::endl;
    std::cout << "Your electricity costs: " << finalReport.costs.electricity << std::endl;
    std::cout << "Your car loan: " << finalReport.costs.carLoan << std::endl;
    std::cout << "Your food at work costs: " << finalReport.costs.foodAtWork << std::endl;

    std::cout << "Your total costs are: " << finalReport.costs.getTotalCosts() << std::endl;
    std::cout << "-----------------Final-----------------" << std::endl;
    std::cout << "Final net cost: " << finalReport.getSavings() << std::endl;
}

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
                analysisType = eMonthly;
                break;
            case eAnnual:
                isValidResponse = true;
                std::cout << "You selected Annual report." << std::endl;
                analysisType = eAnnual;
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
            //std::cout << "Read line: " << line << std::endl;
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

    MoneyReport finalReport;
    generateReport(reportEntries, finalReport);
    printReport(finalReport);

    std::cout << "Number of entries the report you want to analyze has: " << reportEntries.size() << std::endl;

    return 0;
}