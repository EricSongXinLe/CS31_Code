// Code for Project 1
    // Report rice survey results
    
    #include <iostream>
    using namespace std;
    
    int main()
    {
        //compile error 1: MISSING int numberSurveyed;
        int preferBasmati;
        int preferJasmine;
    
        cout << "How many people were surveyed? ";
        cin >> numberSurveyed; //error 1 cause:'Use of undeclared identifier'
        cout << "How many of them prefer basmati rice over jasmine rice? ";
        cin >> preferBasmati;
        cout << "How many of them prefer jasmine rice over basmati rice? ";
        cin >> preferJasmine //compile error 2: MISSING ';' after expression
    
        double pctBasmati = 100.0 * preferBasmati / numberSurveyed;
        double pctJasmine = 100.0 * preferJasmine / numberSurveyed;

        cout.setf(ios::fixed);
        cout.precision(1);
    
        cout << endl;
        cout << pctBasmati << "% prefer basmati rice over jasmine rice." << endl;
        cout << pctJasmine << "% prefer jasmine rice over basmati rice." << endl;

        if (preferBasmati > preferJasmine)
            cout << "More people prefer basmati rice over jasmine rice." << endl;
        else
            cout << "More people prefer jasmine rice over basmati rice." << endl;
    }
