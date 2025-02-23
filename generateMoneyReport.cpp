#include <iostream> // cout


enum Analysis {
    eMonthly, // 0
    eAnnual // 1
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

int main( int argc,      // Number of strings in array argv
          char *argv[])   // Array of command-line argument strings
{
    std::string pathFiles("");
    if(argc == 1 || argc > 3) {
        std::cout << "You have to enter at least a valid path where csv files are and type of analysis you want(montly or annual)" << std::endl;
    } else if(argc == 2) {
        std::cout << "You have to specify the type of analysis you want(montly or annual)" << std::endl;
    } else{
        pathFiles = argv[1];
        std::string analysisType = argv[2];
        switch (std::stoi(argv[2])) // Converts string to int
        {
        case eMonthly:
            std::cout << "Monthly report" << std::endl;
            std::cout << "path: " << pathFiles << std::endl;
            break;
        case eAnnual:
            std::cout << "Annual report" << std::endl;
            break;
        default:
            break;
        }
    }
}