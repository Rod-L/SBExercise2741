#include <vector>
#include <iostream>
#include "Branch.h"

Branch::Branch(int inBranchNumber, int inLevel, Branch* inParent) {
    parent = nullptr;
    level = inLevel;
    branchNumber = inBranchNumber;
    if (inParent != nullptr) inParent->add_child(*this);
}

Branch::~Branch() {
    for (auto child : *children) delete child;
    delete children;
}

std::string Branch::representation() const {
    std::string repr;
    repr.append(children->empty() ? "middle" : "main");
    repr.append(" branch #");
    repr.append(std::to_string(branchNumber));
    repr.append(" of tree #");
    repr.append(std::to_string(get_top_parent()->branchNumber));
    return repr;
}

const std::vector<Branch*>* Branch::get_children() const {
    return children;
}

void Branch::clear_parent() {
    if (parent == nullptr) return;

    std::vector<Branch*>* vec = parent->children;
    for (auto it = vec->begin(); it != vec->end(); ++it) {
       if (*it == this) vec->erase(it);
    }
    parent = nullptr;
}

Branch* Branch::get_parent() const {
    return (parent == nullptr ? (Branch*)this : parent);
}

Branch* Branch::get_top_parent(int inLevel) const {
    if (level <= inLevel || parent == nullptr) {
        return (Branch*)this;
    } else {
        return parent->get_top_parent(inLevel);
    }
}

void Branch::add_child(Branch &child) {
    if (child.parent != nullptr) child.clear_parent();
    child.parent = this;
    child.level = level + 1;
    children->push_back(&child);
}

void Branch::grow_children(int amount) {
    for (int i = 0; i < amount; ++i) {
        add_child(*(new Branch(i + 1, level + 1)));
    }
}

void Branch::settle_elves() {
    if (level > 0) {
        std::cout << "Enter name of elf settling at " << representation() << ":" << std::endl;
        std::string name;
        std::cin >> name;
        if (name != "none") settlerName = name;
    }

    for (Branch* child : *children) {
        child->settle_elves();
    }
}

const Branch* Branch::find_elf(std::string& elfName) const {
    if (settlerName == elfName) return this;
    for (Branch* child : *children) {
        auto result = child->find_elf(elfName);
        if (result != nullptr) return result;
    }
    return nullptr;
}

void Branch::list_neighbours(const Branch* exclude) const {
    if (exclude == nullptr) exclude = this;

    if (this != exclude && !settlerName.empty()) {
        std::cout << settlerName << std::endl;
    }
    for (Branch* child : *children) {
        child->list_neighbours(exclude);
    }
}

