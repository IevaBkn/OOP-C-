#include <iostream>
#include <sstream>
#include <exception>
#include <stdexcept>
#include <iomanip>
#include <cassert>

using namespace std;

class Package {
    private:
        static int objectCount;
        static int last_Id;
        int orderNumber, weight, id;
        string from, to;

    public:
        Package(string from, string to) { 
            init(from, to, 1, 1);
        }
        Package(string from, string to, int weight) {
            init(from, to, weight, 1);
        }
        
        ~Package() {
            --objectCount;
        }

        void setOrderNumber(int orderNumber) {
            if(orderNumber < 1 || orderNumber > 9999) {
                throw invalid_argument("Exception in Package: orderNumber must be an integer 1-9999");
            }
            this->orderNumber = orderNumber;
        }
        void setWeight(int weight) {
            if(weight <= 0) {
                throw invalid_argument("Exception in Package: weight must be positive");
            }
            this->weight = weight;
        }

    private:
        void init(string from, string to, int weight, int orderNumber) {
            ++objectCount;
            id = ++last_Id;
            setFrom(from);
            setTo(to);
            setWeight(weight);
            setOrderNumber(orderNumber);
        }
        void setFrom(string from) {
            this->from = from;
        }
        void setTo(string to) {
            this->to = to;
        }
        
    public:
        int getOrderNumber() {
            return orderNumber;
        }
        int getWeight() {
            return weight;
        }
        int getId() {
            return id;
        }
        static int getObjectCount() {
            return objectCount;
        }
        string getFrom() {
            return from;
        }
        string getTo() {
            return to;
        }

        string toString() {
            stringstream pp;
            pp << setw(4) << setfill('0') << getOrderNumber() << getWeight() << getFrom() << getTo();
            return pp.str();
        }
};
int Package::last_Id = 0;
int Package::objectCount = 0;

int main() {
    try{
        // Test 1
        {
            Package p1("Lithuania", "USA", 5);
            p1.setOrderNumber(1);
            assert(p1.getOrderNumber() == 1);
            assert(p1.getWeight() == 5);
            assert(p1.getFrom() == "Lithuania");
            assert(p1.getTo() == "USA");
            assert(p1.getId() > 0);
            string s = p1.toString();
            assert(s.find("0001") != string::npos);
            assert(s.find("5") != string::npos);
            assert(s.find("Lithuania") != string::npos);
            assert(s.find("USA") != string::npos);
            cout << "1 test: PASSED" << endl;
        }
        
        // Test 2
        {
            Package p2("Lithuania", "North Macedonia", 1);
            p2.setOrderNumber(9999);
            assert(p2.getOrderNumber() == 9999);
            p2.setWeight(3);
            assert(p2.getWeight() == 3);
            cout << "2 test: PASSED" << endl;
        }

        // Test 3
        {
            Package p3("Lithuania", "Thailand", 2);
            bool thrown = false;
            try {
                p3.setWeight(0);
            } catch (exception &e) {
                thrown = true;
            }
            assert(thrown);
            thrown = false;
            try {
                p3.setOrderNumber(0);
            } catch (exception &e) {
                thrown = true;
            }
            assert(thrown);
            thrown = false;
            try {
                p3.setOrderNumber(10000);
            } catch (exception &e) {
                thrown = true;
            }
            assert(thrown);
            cout << "3 test: PASSED" << endl;
        }
        
        // Test 4
        {
            Package p41("Lithuania", "Iceland", 1);
            int id1 = p41.getId();
            Package p42("Lithuania", "Australia", 1);
            int id2 = p42.getId();
            Package p43("Lithuania", "Latvia", 1);
            int id3 = p43.getId();
            
            assert(id1 > 0);
            assert(id2 > 0);
            assert(id3 > 0);
            assert(id1 < id2);
            assert(id2 < id3);
            assert(id1 < id3);
            assert(id1 != id2);
            assert(id2 != id3);
            assert(id1 != id3);
            cout << "4 test: PASSED" << endl;
        }

        // Test 5
        {
            assert(Package::getObjectCount() == 0);
            Package *p51 = new Package("Lithuania","Columbia", 1);
            assert(Package::getObjectCount() == 1);
            Package *p52 = new Package("Lithuania","Somalia", 1);
            assert(Package::getObjectCount() == 2);
            delete p51;
            assert(Package::getObjectCount() == 1);
            delete p52;
            assert(Package::getObjectCount() == 0);
            cout << "5 test: PASSED\n";
        }

    } catch (...) {
        cout << "Unexpected error occured" << endl;
    }
    return 0;
}