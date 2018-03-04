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

        std::string extra1;
        std::string extra2;
        std::string extra3;

        Node(std::string, std::string, std::string, std::string,
                std::string, std::string, std::string, std::string,
                std::string, std::string, std::string, std::string, std::vector<std::string>);

        Node();


        void print();
};
