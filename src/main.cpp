#include <iostream>
#include <string>
#include <vector>

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

void blockTrafficFromRange(std::vector<FirewallRule>& firewallRules) {
    std::string startIp, endIp;

    std::cout << "Enter starting IP address: ";
    std::cin >> startIp;

    std::cout << "Enter ending IP address: ";
    std::cin >> endIp;

    firewallRules.push_back({startIp, false});
    firewallRules.push_back({endIp, false});

    std::cout << "Blocked traffic from IP range " << startIp << " to " << endIp << ". Firewall rules updated." << std::endl;
}

void allowTrafficFromRange(std::vector<FirewallRule>& firewallRules) {
    std::string startIp, endIp;

    std::cout << "Enter starting IP address: ";
    std::cin >> startIp;

    std::cout << "Enter ending IP address: ";
    std::cin >> endIp;

    firewallRules.push_back({startIp, true});
    firewallRules.push_back({endIp, true});

    std::cout << "Allowed traffic from IP range " << startIp << " to " << endIp << ". Firewall rules updated." << std::endl;
}

void blockTrafficByProtocol(std::vector<FirewallRule>& firewallRules) {
    std::string protocol;

    std::cout << "Enter protocol to block: ";
    std::cin >> protocol;

    firewallRules.push_back({protocol, false});

    std::cout << "Blocked traffic for protocol " << protocol << ". Firewall rules updated." << std::endl;
}

void allowTrafficByProtocol(std::vector<FirewallRule>& firewallRules) {
    std::string protocol;

    std::cout << "Enter protocol to allow: ";
    std::cin >> protocol;

    firewallRules.push_back({protocol, true});

    std::cout << "Allowed traffic for protocol " << protocol << ". Firewall rules updated." << std::endl;
}

void blockTrafficByPort(std::vector<FirewallRule>& firewallRules) {
    std::string port;

    std::cout << "Enter port to block: ";
    std::cin >> port;

    firewallRules.push_back({port, false});

    std::cout << "Blocked traffic for port " << port << ". Firewall rules updated." << std::endl;
}

void allowTrafficByPort(std::vector<FirewallRule>& firewallRules) {
    std::string port;

    std::cout << "Enter port to allow: ";
    std::cin >> port;

    firewallRules.push_back({port, true});

    std::cout << "Allowed traffic for port " << port << ". Firewall rules updated." << std::endl;
}

void printMainMenu() {
    std::cout << "=======================" << std::endl;
    std::cout << "Firewall Menu" << std::endl;
    std::cout << "=======================" << std::endl;
    std::cout << "1. Manage Firewall Rules" << std::endl;
    std::cout << "2. Block/Allow All Traffic" << std::endl;
    std::cout << "3. Exit" << std::endl;
    std::cout << "=======================" << std::endl;
    std::cout << "Enter your choice: ";
}

void printFirewallRulesMenu() {
    std::cout << "=======================" << std::endl;
    std::cout << "Manage Firewall Rules" << std::endl;
    std::cout << "=======================" << std::endl;
    std::cout << "1. Add Firewall Rule" << std::endl;
    std::cout << "2. Remove Firewall Rule" << std::endl;
    std::cout << "3. Clear All Rules" << std::endl;
    std::cout << "4. Print Rules" << std::endl;
    std::cout << "5. Count Rules" << std::endl;
    std::cout << "6. Search Rule by IP" << std::endl;
    std::cout << "7. Go Back" << std::endl;
    std::cout << "=======================" << std::endl;
    std::cout << "Enter your choice: ";
}

void printBlockAllowMenu() {
    std::cout << "=======================" << std::endl;
    std::cout << "Block/Allow All Traffic" << std::endl;
    std::cout << "=======================" << std::endl;
    std::cout << "1. Block All Traffic" << std::endl;
    std::cout << "2. Allow All Traffic" << std::endl;
    std::cout << "3. Block Traffic by IP Range" << std::endl;
    std::cout << "4. Allow Traffic by IP Range" << std::endl;
    std::cout << "5. Block Traffic by Protocol" << std::endl;
    std::cout << "6. Allow Traffic by Protocol" << std::endl;
    std::cout << "7. Block Traffic by Port" << std::endl;
    std::cout << "8. Allow Traffic by Port" << std::endl;
    std::cout << "9. Go Back" << std::endl;
    std::cout << "=======================" << std::endl;
    std::cout << "Enter your choice: ";
}

int main() {
    std::vector<FirewallRule> firewallRules;

    int mainChoice;
    int firewallChoice;
    int blockAllowChoice;

    do {
        printMainMenu();
        std::cin >> mainChoice;

        switch (mainChoice) {
            case 1:
                do {
                    printFirewallRulesMenu();
                    std::cin >> firewallChoice;

                    switch (firewallChoice) {
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
                        case 7:
                            break;
                        default:
                            std::cout << "Invalid choice. Please try again." << std::endl;
                            break;
                    }
                } while (firewallChoice != 7);
                break;
            case 2:
                do {
                    printBlockAllowMenu();
                    std::cin >> blockAllowChoice;

                    switch (blockAllowChoice) {
                        case 1:
                            blockAllTraffic(firewallRules);
                            break;
                        case 2:
                            allowAllTraffic(firewallRules);
                            break;
                        case 3:
                            blockTrafficFromRange(firewallRules);
                            break;
                        case 4:
                            allowTrafficFromRange(firewallRules);
                            break;
                        case 5:
                            blockTrafficByProtocol(firewallRules);
                            break;
                        case 6:
                            allowTrafficByProtocol(firewallRules);
                            break;
                        case 7:
                            blockTrafficByPort(firewallRules);
                            break;
                        case 8:
                            allowTrafficByPort(firewallRules);
                            break;
                        case 9:
                            break;
                        default:
                            std::cout << "Invalid choice. Please try again." << std::endl;
                            break;
                    }
                } while (blockAllowChoice != 9);
                break;
            case 3:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    } while (mainChoice != 3);

    return 0;
}
