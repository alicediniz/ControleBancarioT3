//
//  SaldoDiaBase.hpp
//  Sistema de Controle Bancario
//
//  Created by Alice Diniz Ferreira and Paula Resende Teixeira on 11/30/2019.
//  Copyright © 2019 trabalhoPOO. All rights reserved.
//

#ifndef SaldoDiaBase_hpp
#define SaldoDiaBase_hpp

#include <list>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class SaldoDiaBase {
private:
    int diaBase;
    double saldoDiaBase;
public:
    // Construtor
    SaldoDiaBase(int diaBase, double saldoDiaBase);
    
    // Metodos Set
    void setSaldo(int baseDate, double baseDateBalance);
    void setDate (int baseDate);
    void setValue (double baseDateBalance);

    // Metodos get
    int getDate ();
    double getValue ();
    
};

#endif /* SaldoDiaBase_hpp */
