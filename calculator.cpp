// less memory usage, faster and I tried using Function prototype 

#include <iostream>
#include <limits>

//Function prototype 
double Action(double Result, double number, char Operation);
void Error();

int main(){
    
    double number, Result=0;
    char Operation;
    bool FirstTime=true;
 
    do{
        
        std::cout << "input number number: ";
        while (!(std::cin >> number)){
            Error();
            std::cout << "Invalid input. Please input a number: ";
        }
        
        if (FirstTime){
            Result=number;
            FirstTime=false;
        } else {
            Result= Action( number, Result, Operation);
        }

        do{
            std::cout << "input action (+, -, *, /, =): ";
            std::cin >> Operation;
        }while (Operation!='+' && Operation!='-' && Operation!='*' && Operation!='/' && Operation!='=');
       
        if (Operation=='='){
            break;
        }

    } while (Operation!='=');
   
    std::cout <<"result: " << Result;
    
    return 0;
}

//Function declaration 
void Error(){
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
};

double  Action (double Result, double number, char Operation){
    switch (Operation){
            case '+':
                Result+=number;
                break;
            case '-':
                Result-=number;
                break;
            case '*':
                Result*=number;
                break;
            case '/':
                    while (number==0){
                         std::cout << "Division by zero is not allowed. Input a number different from 0: ";
                        std::cin >> number;
                    }
                Result/=number;
                break;
    }
    return Result;
};