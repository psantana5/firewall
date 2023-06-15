#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <sstream>
#include <limits>
#include <windows.h>



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

std::string hashPassword(const std::string& password) {
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hashLength;

    EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
    const EVP_MD* md = EVP_sha256();

    EVP_DigestInit_ex(mdctx, md, nullptr);
    EVP_DigestUpdate(mdctx, password.c_str(), password.length());
    EVP_DigestFinal_ex(mdctx, hash, &hashLength);
    EVP_MD_CTX_free(mdctx);

    std::stringstream ss;
    for (unsigned int i = 0; i < hashLength; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return ss.str();
}

bool authenticate(std::string& username, std::string& password) {
    std::string directoryPath = "shadow";
    std::string filePath = directoryPath + "/credentials.txt";

    // Create the hidden directory
    if (!CreateDirectory(directoryPath.c_str(), NULL) && GetLastError() != ERROR_ALREADY_EXISTS) {
        std::cout << "Failed to create the hidden directory. Exiting..." << std::endl;
        return false;
    }

    // Make the directory hidden
    if (!SetFileAttributes(directoryPath.c_str(), FILE_ATTRIBUTE_HIDDEN)) {
        std::cout << "Failed to set the hidden attribute for the directory. Exiting..." << std::endl;
        return false;
    }

    // Set appropriate permissions for the credentials file
    SECURITY_ATTRIBUTES securityAttributes;
    securityAttributes.nLength = sizeof(SECURITY_ATTRIBUTES);
    securityAttributes.bInheritHandle = FALSE;

    PSECURITY_DESCRIPTOR securityDescriptor = NULL;
    if (!ConvertStringSecurityDescriptorToSecurityDescriptor(
            "D:(A;OICI;GA;;;WD)", // Deny read access to everyone
            SDDL_REVISION_1,
            &securityDescriptor,
            NULL)) {
        std::cout << "Failed to convert security descriptor. Exiting..." << std::endl;
        return false;
    }

    securityAttributes.lpSecurityDescriptor = securityDescriptor;

    HANDLE fileHandle = CreateFile(
        filePath.c_str(),
        GENERIC_WRITE,
        0,
        &securityAttributes,
        CREATE_NEW,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (fileHandle == INVALID_HANDLE_VALUE) {
        std::cout << "Failed to create the credentials file. Exiting..." << std::endl;
        LocalFree(securityDescriptor);
        return false;
    }

    CloseHandle(fileHandle);
    LocalFree(securityDescriptor);

    std::ifstream credentialsFile(filePath);
    if (credentialsFile.is_open()) {
        std::getline(credentialsFile, username);
        std::string encryptedPassword;
        std::getline(credentialsFile, encryptedPassword);
        credentialsFile.close();

        std::string inputPassword;
        std::cout << "Enter your password: ";
        std::getline(std::cin, inputPassword);

        if (hashPassword(inputPassword) == encryptedPassword) {
            return true;
        } else {
            std::cout << "Invalid password. Authentication failed." << std::endl;
            return false;
        }
    } else {
        std::ofstream newCredentialsFile(filePath);
        if (newCredentialsFile.is_open()) {
            std::cout << "Welcome! Let's set up your firewall credentials." << std::endl;
            std::cout << "Enter a username: ";
            std::getline(std::cin, username);
            std::string inputPassword;
            std::cout << "Enter a password: ";
            std::getline(std::cin, inputPassword);
            std::string encryptedPassword = hashPassword(inputPassword);
            newCredentialsFile << username << "\n" << encryptedPassword << std::endl;
            newCredentialsFile.close();
            std::cout << "Credentials set successfully. Please restart the firewall." << std::endl;
        } else {
            std::cout << "Failed to create credentials file. Exiting..." << std::endl;
        }
        return false;
    }
}

int main() {
    std::vector<FirewallRule> firewallRules;

    std::string username, password;
    if (!authenticate(username, password)) {
        return 0;
    }

    int choice;
    do {
        printMenu();
        std::cout << "Enter your choice (1-8): ";
        std::cin >> choice;
        std::cout << std::endl;

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
            case 7:
                // Submenu for blocking/allowing traffic
                int submenuChoice;
                do {
                    std::cout << "1. Block All Traffic" << std::endl;
                    std::cout << "2. Allow All Traffic" << std::endl;
                    std::cout << "3. Block Traffic by IP Range" << std::endl;
                    std::cout << "4. Allow Traffic by IP Range" << std::endl;
                    std::cout << "5. Block Traffic by Protocol" << std::endl;
                    std::cout << "6. Allow Traffic by Protocol" << std::endl;
                    std::cout << "7. Block Traffic by Port" << std::endl;
                    std::cout << "8. Allow Traffic by Port" << std::endl;
                    std::cout << "9. Go Back to Main Menu" << std::endl;
                    std::cout << "Enter your choice (1-9): ";
                    std::cin >> submenuChoice;
                    std::cout << std::endl;

                    switch (submenuChoice) {
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
                            break;  // Go back to the main menu
                        default:
                            std::cout << "Invalid choice. Please try again." << std::endl;
                            break;
                    }
                    std::cout << std::endl;
                } while (submenuChoice != 9);
                break;
            case 8:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
        std::cout << std::endl;
    } while (choice != 8);

    return 0;
}
