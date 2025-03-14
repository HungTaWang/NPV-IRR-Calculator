#include<iostream>
#include <math.h>
using namespace std;

class FN{
public:
    FN();
    FN &setCashFlow();
    FN &calculateNPV();
    FN &calculateIRR();
    FN &printCashFlow();
    FN &printDiscountedCashFlow();
    FN &printNPV();
    FN &printIRR();
    static void modifyRate();
private:
    double cashFlow[100];
    double cashFlowX[100];
    int cashOrder;
    static double annualRate;
    double NPV;
    double IRR;
};

FN::FN(){
    IRR=0.00;
    NPV=0.00;
    cashOrder = 0;
    for(int i=0;i<100;i++){
        cashFlow[i] = cashFlowX[i] =0.00;
    }
    setCashFlow();
}

FN &FN::setCashFlow(){
    for(int i=0;i<100;i++){
        if(i==0){
            cout << "Initial investment cost" << ": ";
        }
        if(i>0){
            cout << "Cash flow" << i << ": ";
        }
        cin >> cashFlow[cashOrder];
        if(cashFlow[cashOrder] == -1){
            break;
        }
        else{
            cashOrder += 1;
        }
    }
    return *this;
}

FN &FN::calculateNPV(){
    for(int i=0;i<cashOrder;i++){
        cashFlowX[i] = cashFlow[i] / pow(1+annualRate,i);
    }
    for(int i=0;i<cashOrder;i++){
        NPV += cashFlow[i] / pow(1+annualRate,i);
    }
    return *this;
}

FN &FN::calculateIRR(){
    double cashFlow1[100];
    double cashFlow2[100];
    double cashFlow3[100];

    for(int i=0;i<100;i++){
        cashFlow1[i] = cashFlow2[i] = cashFlow3[i] = cashFlow[i];
    }

    double IRR1=0.00;
    double IRR2=1.00;
    double IRR3=2.00;
    double NPV1=0.00;
    double NPV2=0.00;
    double NPV3=0.00;

    while(true){
        NPV1=0.00;
        NPV2=0.00;
        NPV3=0.00;
        
        for(int i=0;i<cashOrder;i++){
            NPV1 += cashFlow1[i] / pow(1+IRR1, i);
        }
        for(int i=0;i<cashOrder;i++){
            NPV2 += cashFlow2[i] / pow(1+IRR2, i);
        }

        if(NPV1<0 && NPV2>0){
            IRR3 = (IRR1+IRR2) / 2;
            for(int i=0;i<cashOrder;i++){
            NPV3 += cashFlow3[i] / pow(1+IRR3, i);
            }
            if(NPV3>0){
                IRR2 = IRR3;
            }
            if(NPV3<0){
                IRR1 = IRR3;
            }
        }

        if(NPV1>0 && NPV2<0){
            IRR3 = (IRR1+IRR2) / 2;
            for(int i=0;i<cashOrder;i++){
            NPV3 += cashFlow3[i] / pow(1+IRR3, i);
            }
            if(NPV3>0){
                IRR1 = IRR3;
            }
            if(NPV3<0){
                IRR2 = IRR3;
            }
        }

        if(NPV1==0 || NPV2==0){
            if(NPV1==0){
                IRR = IRR1;
            }
            if(NPV2==0){
                IRR = IRR2;
            }
        }

        if(NPV1>0 && NPV2>0){
            IRR = 1;
            break;
        }

        if(NPV1<0 && NPV2<0){
            IRR = -1;
            break;
        }

        //cout <<"\nNPV1 ="<< NPV1 <<endl;
        //cout <<"NPV2 ="<< NPV2 <<endl;
        //cout <<"NPV3 ="<< NPV3 <<endl;
        //cout <<"IRR1 ="<< IRR1 <<endl;
        //cout <<"IRR2 ="<< IRR2 <<endl;
        //cout <<"IRR3 ="<< IRR3 <<endl;

        if(IRR2-IRR1<0.0000000001){
            IRR = (IRR1+IRR2)/2;
            break;
        }

    }

    return *this;
}

FN &FN::printDiscountedCashFlow(){
    for(int i=0;i<cashOrder;i++){
        if(i==0){
            cout << "Initial investment cost" << ": "  << cashFlowX[i] << endl;
        }
        if(i>0){
            cout  << "Cash flow" << i << ": " << cashFlowX[i] << endl;
        }
        
    }

    return *this;
}

FN &FN::printNPV(){
    cout << "NPV: " << NPV << endl;

    return *this;
}

FN &FN::printIRR(){
    if(IRR==1){
        cout << "IRR: " << IRR*100 << "%" << " (This project may always be profitable!)" << endl;
    }
    else if(IRR==-1){
        cout << "IRR: " << IRR*100 << "%" << " (This project may always be unprofitable!)" << endl;
    }
    else{
        cout << "IRR: " << IRR*100 << "%" << endl;

    }

    return *this;
}

double FN::annualRate = -1;

void FN::modifyRate(){
    cout << "Please input your discount rate (%): ";
    double r;
    cin>>r;
    annualRate = r/100.00;
}


int main(){
    int a;

    FN::modifyRate();
    cout << "\nIf the cash flow is a cost, please input a negative number.\nInput -1 to quit!" << endl;
    cout << "\nOriginal cash flows: " << endl;
    FN cal;

    cout << "\nDiscounted cash flows: " << endl;
    cal.calculateNPV().printDiscountedCashFlow();

    cout << "\nFinancial analysis: " << endl;
    cal.printNPV().calculateIRR().printIRR();

    cout << "\nPress any button + Enter to quit! " << endl;
    cin>>a;
}