#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <sstream>
#include <limits>

struct FirewallRule {
    std::string ipAddress;
    bool allow;
};

bool isPacketAllowed(const std::string& ipAddress, const std::vector<FirewallRule>& firewallRules) {
    for (const auto& rule : firewallRules) {
        if (rule.ipAddress == ipAddress) {
            return rule.allow;
        }
    }
    return false;
}

void addFirewallRule(std::vector<FirewallRule>& firewallRules) {
    std::string ipAddress;
    char choice;

    std::cout << "Enter IP address: ";
    std::cin >> ipAddress;

    std::cout << "Allow or block? (a/b): ";
    std::cin >> choice;

    bool allow = (choice == 'a' || choice == 'A');
    firewallRules.push_back({ipAddress, allow});

    std::cout << "Firewall rule added successfully." << std::endl;
}

void removeFirewallRule(std::vector<FirewallRule>& firewallRules) {
    std::string ipAddress;

    std::cout << "Enter IP address to remove: ";
    std::cin >> ipAddress;

    for (auto it = firewallRules.begin(); it != firewallRules.end(); ++it) {
        if (it->ipAddress == ipAddress) {
            firewallRules.erase(it);
            std::cout << "Firewall rule removed successfully." << std::endl;
            return;
        }
    }

    std::cout << "Firewall rule not found for the given IP address." << std::endl;
}

void clearFirewallRules(std::vector<FirewallRule>& firewallRules) {
    firewallRules.clear();
    std::cout << "All firewall rules cleared." << std::endl;
}

void printFirewallRules(const std::vector<FirewallRule>& firewallRules) {
    std::cout << "Firewall Rules:" << std::endl;
    for (const auto& rule : firewallRules) {
        std::string action = rule.allow ? "Allow" : "Block";
        std::cout << "IP: " << rule.ipAddress << "  Action: " << action << std::endl;
    }
}

void countFirewallRules(const std::vector<FirewallRule>& firewallRules) {
    std::cout << "Total firewall rules: " << firewallRules.size() << std::endl;
}

void searchFirewallRule(const std::vector<FirewallRule>& firewallRules) {
    std::string ipAddress;

    std::cout << "Enter IP address to search: ";
    std::cin >> ipAddress;

    for (const auto& rule : firewallRules) {
        if (rule.ipAddress == ipAddress) {
            std::string action = rule.allow ? "Allow" : "Block";
            std::cout << "Firewall rule found for IP: " << rule.ipAddress << "  Action: " << action << std::endl;
            return;
        }
    }

    std::cout << "No firewall rule found for the given IP address." << std::endl;
}

void blockAllTraffic(std::vector<FirewallRule>& firewallRules) {
    firewallRules.clear();
    firewallRules.push_back({"0.0.0.0", false});
    std::cout << "All traffic blocked. Firewall rules updated." << std::endl;
}

void allowAllTraffic(std::vector<FirewallRule>& firewallRules) {
    firewallRules.clear();
    firewallRules.push_back({"0.0.0.0", true});
    std::cout << "All traffic allowed. Firewall rules updated." << std::endl;
}

std::string getHiddenPath(const std::string& filename) {
    return "./shadow/" + filename;
}

bool authenticate(std::string& username, std::string& password) {
    std::ifstream credentialsFile(getHiddenPath("credentials.txt"));
    if (credentialsFile.is_open()) {
        std::string storedUsername;
        std::string storedPassword;

        std::getline(credentialsFile, storedUsername);
        std::getline(credentialsFile, storedPassword);

        credentialsFile.close();

        if (username == storedUsername && password == storedPassword) {
            return true;
        }
    }

    return false;
}

bool isAuthorized(const std::string& username) {
    std::ifstream authUsersFile(getHiddenPath("authorized_users.txt"));
    if (authUsersFile.is_open()) {
        std::string line;
        while (std::getline(authUsersFile, line)) {
            if (line == username) {
                return true;
            }
        }
        authUsersFile.close();
    }

    return false;
}

void saveFirewallRules(const std::vector<FirewallRule>& firewallRules) {
    std::ofstream rulesFile(getHiddenPath("firewall_rules.txt"));
    if (rulesFile.is_open()) {
        for (const auto& rule : firewallRules) {
            std::string action = rule.allow ? "Allow" : "Block";
            rulesFile << rule.ipAddress << " " << action << std::endl;
        }
        rulesFile.close();
        std::cout << "Firewall rules saved successfully." << std::endl;
    }
}

void loadFirewallRules(std::vector<FirewallRule>& firewallRules) {
    firewallRules.clear();
    std::ifstream rulesFile(getHiddenPath("firewall_rules.txt"));
    if (rulesFile.is_open()) {
        std::string line;
        while (std::getline(rulesFile, line)) {
            std::istringstream iss(line);
            std::string ipAddress;
            std::string action;
            iss >> ipAddress >> action;
            bool allow = (action == "Allow");
            firewallRules.push_back({ipAddress, allow});
        }
        rulesFile.close();
        std::cout << "Firewall rules loaded successfully." << std::endl;
    }
}

void printMenu() {
    std::cout << "=======================" << std::endl;
    std::cout << "Firewall Menu" << std::endl;
    std::cout << "=======================" << std::endl;
    std::cout << "1. Add Firewall Rule" << std::endl;
    std::cout << "2. Remove Firewall Rule" << std::endl;
    std::cout << "3. Clear All Firewall Rules" << std::endl;
    std::cout << "4. Print Firewall Rules" << std::endl;
    std::cout << "5. Count Firewall Rules" << std::endl;
    std::cout << "6. Search Firewall Rule" << std::endl;
    std::cout << "7. Block/Allow Traffic" << std::endl;
    std::cout << "8. Exit" << std::endl;
    std::cout << "=======================" << std::endl;
    std::cout << std::endl;
}

int main() {
    std::string username;
    std::string password;

    std::cout << "Firewall Management System" << std::endl;
    std::cout << "--------------------------" << std::endl;

    std::cout << "Enter username: ";
    std::cin >> username;

    std::cout << "Enter password: ";
    std::cin >> password;

    if (!authenticate(username, password)) {
        std::cout << "Invalid username or password. Access denied." << std::endl;
        return 0;
    }

    if (!isAuthorized(username)) {
        std::cout << "You are not authorized to access the firewall. Access denied." << std::endl;
        return 0;
    }

    std::vector<FirewallRule> firewallRules;

    loadFirewallRules(firewallRules);

    while (true) {
        printMenu();

        int choice;
        std::cout << "Enter your choice (1-8): ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addFirewallRule(firewallRules);
                break;
            case 2:
                removeFirewallRule(firewallRules);
                break;
            case 3:
                clearFirewallRules(firewallRules);
                break;
            case 4:
                printFirewallRules(firewallRules);
                break;
            case 5:
                countFirewallRules(firewallRules);
                break;
            case 6:
                searchFirewallRule(firewallRules);
                break;
            case 7: {
                char blockChoice;
                std::cout << "Block or allow traffic? (b/a): ";
                std::cin >> blockChoice;

                if (blockChoice == 'b' || blockChoice == 'B') {
                    blockAllTraffic(firewallRules);
                } else if (blockChoice == 'a' || blockChoice == 'A') {
                    allowAllTraffic(firewallRules);
                } else {
                    std::cout << "Invalid choice. Please try again." << std::endl;
                }
                break;
            }
            case 8:
                saveFirewallRules(firewallRules);
                std::cout << "Exiting the Firewall Management System." << std::endl;
                return 0;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }

        std::cout << std::endl;
    }

    return 0;
}
