#include <iostream>
using namespace std;

class GaiTree{
    public:
        struct Offense{
            int running_a_red;
            int speeding;
            int illegal_parking;
        };
        struct Car{
            string number; //key
            Offense list; //value
            Car* leftCar;
            Car* rightCar;
            Car(const string inKey):leftCar(NULL), rightCar(NULL), number(inKey), list({0,0,0}){}
            ~Car(){
                delete leftCar;
                delete rightCar;
            }
        };

        Car* root;
        size_t sizeOfTree;

        GaiTree(){};
        ~GaiTree(){};

        Offense& operator[](const string& index){
            Car** current = &root;
            while((*current) == nullptr){ ///������? == ��������, � != ���? ������ ��� �������� "�������"?
                if(index == (*current)->number){
                    return (*current)->list;
                }
                if(index > (*current)->number){
                    current = &((*current)->rightCar);
                }
                else{
                    current = &((*current)->leftCar);
                }
            }
            (*current) = new Car(index);
            ++sizeOfTree;
            return (*current)->list;
        }

        void listPrinter(Car* node){
            cout << "Car Number: " << node->number << endl;
            cout << "\tOffense list:" << endl << "Running a red: " << node->list.running_a_red << endl;
            cout << "Speeding: " << node->list.speeding << endl;
            cout << "Illegal parking: " << node->list.illegal_parking << endl << endl;
        }

        void showTree(Car* node){
            if(node){
                showTree(node->leftCar);
                showTree(node->rightCar);
                listPrinter(node);
            }
        }
};

int main()
{
    GaiTree DB1;

    DB1["2371GB"] = {3,5,7};
    DB1["6748UI"] = {1,2,1};
    DB1["5677FF"] = {2,0,4};

    DB1.showTree(DB1.root);
    return 0;
}
