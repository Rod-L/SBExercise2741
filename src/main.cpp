#include <iostream>
#include <vector>
#include "Branch.h"

int main() {
    std::cout << "How many trees are in forest?" << std::endl;
    int trunksCount;
    std::cin >> trunksCount;

    // Grow forest
    std::vector<Branch*> trees;
    for (int i = 0; i < trunksCount; ++i) {
        auto trunk = new Branch;
        trunk->grow_children(rand() % 3 + 3);
        trees.push_back(trunk);

        for (Branch* bigBranch : *trunk->get_children()) {
            bigBranch->grow_children(rand() % 2 + 2);
        }
    }

    // Settle elves
    for (auto tree : trees) tree->settle_elves();

    // Interact with user
    while (true) {
        std::cout << "What elf do you want to know about?\n"
                     "(Enter name or 'exit')\n";
        std::string elfName;
        std::cin >> elfName;

        if (elfName == "exit") break;

        const Branch *branch;
        for (auto tree: trees) {
            branch = tree->find_elf(elfName);
            if (branch != nullptr) break;
        }

        if (branch == nullptr) {
            std::cout << elfName << " don't live in this tree village." << std::endl;
        } else {
            std::cout << elfName << " lives at " << branch->representation() << std::endl;
            std::cout << "His neighbours are:" << std::endl;
            branch->get_top_parent(1)->list_neighbours();
        }
    }
}
