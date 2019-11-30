//
//  Poupanca.hpp
//  Sistema de Controle Bancario
//
//  Created by Alice Diniz Ferreira and Paula Resende Teixeira on 11/30/2019.
//  Copyright © 2019 trabalhoPOO. All rights reserved.
//

#ifndef Poupanca_hpp
#define Poupanca_hpp

#include <list>
#include <iostream>
#include <string>
#include <vector>
#include "Cliente.h"
#include "Movimentacao.hpp"
#include "Conta.hpp"
#include "SaldoDiaBase.hpp"

using namespace std;

class Poupanca : public Conta {
private:
    vector<SaldoDiaBase> saldoPoupanca;

public:
    Poupanca(string name , string document, string address, string phone, )
        : Conta(name, document, address, phone){}

    // Metodos get
    int getAccountNumber ();
    double getBalance ();
    Cliente getClient ();
    vector <Movimentacao> getFinancialMovements();
    vector <SaldoDiaBase> getDateBaseBalance();
    
    // Funcoes
    void debit (string description, double value);
    void credit (string description, double value);
    vector <Movimentacao> getAccountBalance();
    vector <Movimentacao> getAccountBalance(struct tm startTime);
    vector <Movimentacao> getAccountBalance(struct tm startTime, struct tm endTime);
};


#endif /* Poupanca_hpp */
