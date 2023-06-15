#include <iostream>


void menu() {
    std::cout << "Firewall main menu" << std::endl;
    std::cout << "1. View Firewall Rules" << std::endl;
    std::cout << "2. Add Firewall Rule" << std::endl;
    std::cout << "3. Remove Firewall Rule" << std::endl;
    std::cout << "4. Save Firewall Configuration" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "Enter your choice: ";

    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1:
            std::cout << "View Firewall Rules" << std::endl;
            break;
        case 2:
            std::cout << "Add Firewall Rule" << std::endl;
            break;
        case 3:
            std::cout << "Remove Firewall Rule" << std::endl;
            break;
        case 4:
            std::cout << "Save Firewall Config" << std::endl;
            break;
        case 5:
            std::cout << "Exiting..." << std::endl;
            break;
        default:
            std::cout << "Invalid choice!" << std::endl;
            break;
    }
}

int main() {
    menu();
    return 0;
}
