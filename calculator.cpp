#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <deque>
#include <cassert>

// correct the equation for mistakes
std::string Correct(std::string str) {
    size_t i = 0;
    char choice;
    int brackets = 0;
    while (i < str.length()) {
        if (str[i]==' '){ // check for spaces and delete if found
            str.erase(i, 1);
        }
        if (!isdigit(str[i]) && str[i]!='.' && str[i]!='+' && str[i]!='-' && str[i]!='*' 
            && str[i]!='/' && str[i]!='(' && str[i]!=')') { // check for symbol unwanted symbols
            do{ // repeat until given possible answer
                if (choice =='y') break; // continue with the answer
                std::cout << "\nInvalid character/s detected\n";
                std::cout << "Do you want to continue the equation by removing it? (y/n): ";   
                std::cin >> choice;
            }while (choice!='y' && choice!='n');
            if (choice == 'y') {
                str.erase(i, 1);
                continue; // Re-evaluate current position
            } else {
                return "";
            }
        }
        if (i!=0 && str[i]=='(' && (isdigit(str[i-1]) || str[i-1]==')')){ // insert '*'  befor '('
            str.insert(str.begin() + i, '*');
            i++; // correct the position
        }
        if(str[i]=='(') brackets++;
        if(str[i]==')') brackets--;
        i++;
    }
    if (brackets != 0) {
        std::cout << "Error: Unmatched brackets.\n";
        return "";
    }
    return str;
}

//divide the number from the symbols
std::string Tokenize(std::string str) {
    size_t i = 0;
    std::string symbol;
    std::string box = ""; // temporary string to contain the char for the numbers
    std::string fin = ""; // the output

    //until it it finish the string
    while (i <= str.length())
    {
        // check if the char is unary, binary and if it is more than 1 digit number
        if((str[i] == '-' && (i == 0 || !isdigit(str[i-1]))) || isdigit(str[i]) || str[i]=='.') {
            box += str[i]; 
        }
        else {
            // put the number in the final string and # at the end, and clear after
            if (box!=""){
                fin += box + '#';
                box = "";
            }

            // put the symbol in the final string and # at the end
            if (i!=str.length()){
                symbol = str[i];
                fin += symbol + '#';
            }
        }
        i++;
    }
    return fin;
}

// calculate
double  Action (double Result, double number, std::string Operation){
    char character = Operation[0];

    switch (character){
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

//sort the equation and calculate
double RPolish(std::string str) {
    size_t i = 0;
    std::string box = ""; // temporary string to contain the char for the numbers
    std::string fin = ""; // the output
    std::deque<std::string> secondRoad; // temporary string to contain the symbols and the "+""-"
    std::stack<double> hold; // hold the numbers
    double number_l, number_r; // stod and for the function

    while (i<str.length()){
        //to check if the box is digit
        bool digit = false;
        while (str[i] != '#'){
            box+=str[i];
            if(isdigit(str[i])){
                digit = true;
            }
            i++;
        }
        i++;
        // if it is number push to stack
        if (digit==true){

            number_r = stod(box);
            hold.push(number_r);
        }
        else{
            if (box == "+" || box=="-"){

                if (secondRoad.front() == "+" || secondRoad.front() == "-" 
                || secondRoad.front() == "*" || secondRoad.front() == "/")
                {
                    
                    fin=secondRoad.front();//hold the symbol
                    number_r = hold.top(); // take the right number (in the equation)
                    hold.pop();
                    number_l = hold.top(); // take the left number (in the equation)
                    hold.pop();
                    number_r = Action(number_l, number_r, fin); //calculate
                    hold.push(number_r); // take the calculated result

                    secondRoad.pop_front(); // remove the symbol from the second road
                    secondRoad.push_front(box); // put the new symbol in the second road
                }
                else {
                    secondRoad.push_front(box);
                }
                
            }
            else if (box == "*" || box == "/"){
                // check if the symbol befor was mult. or div.
                if (secondRoad.front() == "*" || secondRoad.front() == "/"){
                    fin=secondRoad.front();//hold the symbol
                    number_r = hold.top(); // take the right number (in the equation)
                    hold.pop();
                    number_l = hold.top(); // take the left number (in the equation)
                    hold.pop();
                    number_r = Action(number_l, number_r, fin); //calculate
                    hold.push(number_r); // take the calculated result

                    secondRoad.pop_front(); // remove the symbol from the second road
                    secondRoad.push_front(box); // put the new symbol in the second road
                }
                else {
                    secondRoad.push_front(box);
                }
            }
            else if (box == "(" ){
                secondRoad.push_front(box);
            }
            else if (box == ")"){
                while (secondRoad.front() != "("){ 
                    fin=secondRoad.front();//hold the symbol
                    number_r = hold.top(); // take the right number (in the equation)
                    hold.pop();
                    number_l = hold.top(); // take the left number (in the equation)
                    hold.pop();
                    number_r = Action(number_l, number_r, fin); //calculate
                    hold.push(number_r); // take the calculated result

                    secondRoad.pop_front(); // remove the symbol from the second road
                }
                secondRoad.pop_front(); // remove the "("
            }
        }
    box = ""; // clear the box
    }

    for (int k = 0; !secondRoad.empty(); k++) { // loop through the deque
        fin=secondRoad.front();//hold the symbol
        number_r = hold.top(); // take the right number (in the equation)
        hold.pop();
        number_l = hold.top(); // take the left number (in the equation)
        hold.pop();
        number_r = Action(number_l, number_r, fin); //calculate
        hold.push(number_r); // take the calculated result

        secondRoad.pop_front(); // remove the symbol from the second road
    }

    return hold.top();
}

int main (){

while (true) {
    //Input 
    std::string input;
    std::cout << "Input equation (type '=' to exit): \n";
    std::getline(std::cin, input);
    double result;

    if (input.empty()) {
        std::cout << "No input provided.\n";
        continue;
    }
    if (input[0] == '=') break;

    // action
    input = Correct(input);
    if (input=="") break;
    input = Tokenize(input);
    result = RPolish(input);

    //Result
    std::cout << "Result: " << result << std::endl;
    }

    return 0;
}