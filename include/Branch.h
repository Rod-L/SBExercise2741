#pragma once

#include <vector>
#include <string>

class Branch{
    Branch* parent;
    std::vector<Branch> children;
    std::string settlerName;
    int branchNumber;
    int level;

    void clear_parent();

    void add_child(Branch& child);

public:
    explicit Branch(int inBranchNumber = 1, int inLevel = 0, Branch* inParent = nullptr);

    std::string representation() const;

    Branch* get_top_parent(int inLevel = 0) const;

    const std::vector<Branch>& get_children() const;

    void grow_children(int amount);

    void settle_elves();

    const Branch* find_elf(std::string& elfName) const;

    void list_neighbours(const Branch* exclude = nullptr) const;
};
