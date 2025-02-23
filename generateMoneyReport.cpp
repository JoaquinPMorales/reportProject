#include <iostream> // cout


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

    std::cout << "You selected: " << optionSelected << std::endl;
}