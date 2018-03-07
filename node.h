#include <string>
#include <vector>

class Node {
    public:
        std::string title;
        std::string enterDescription;

        std::string enemy;
        std::vector<std::string> objects;

        std::string exitNorth;
        std::string exitSouth;
        std::string exitEast;
        std::string exitWest;

        std::string onEnter;
        std::string onLeave;

        std::vector<std::string> searchables;
        std::vector<std::string> findables;
        std::vector<std::string> searchText;

        Node(std::string, std::string, std::string, std::string,
                std::string, std::string, std::string, std::string,
                std::string, std::vector<std::string>, std::vector<std::string>,
                std::vector<std::string>, std::vector<std::string>);

        Node();

        // Need for "take", "drop" commands
        int objectExists(std::string);
        int searchableExists(std::string);
        void addObject(std::string);

        void print();
};
