//
//  Conta.hpp
//  Sistema de Controle Bancario
//
//  Created by Alice Diniz Ferreira and Paula Resende Teixeira on 10/1/19.
//  Copyright © 2019 trabalhoPOO. All rights reserved.
//

#ifndef Conta_hpp
#define Conta_hpp

#include <list>
#include <iostream>
#include <string>
#include <vector>
#include "Cliente.h"
#include "Movimentacao.hpp"

using namespace std;

class Conta {
private:
    int numConta;
    double saldo;
    Cliente cliente;
    vector <Movimentacao> movimentacoes;
    static int proximoNumConta;

public:
    
    Conta(string name , string document, string address, string phone);
    virtual void setAccount(Cliente client);
    
    // Metodos set
    virtual void setNumConta(int numAccount);
    virtual void setBalance(int balanceValue);
    virtual void setClient(Cliente client);
    virtual void setMovimentacoes(vector <Movimentacao> movs);
    virtual void setProxNumConta();
    
    // Metodos get
    virtual int getAccountNumber ();
    virtual double getBalance ();
    virtual Cliente getClient ();
    virtual vector <Movimentacao> getFinancialMovements();
    virtual int getProximoNumConta();
    
    // Funcoes
    virtual void debit (string description, double value) = 0 ;
    virtual void credit (string description, double value) = 0 ;
    virtual vector <Movimentacao> getAccountBalance();
    virtual vector <Movimentacao> getAccountBalance(struct tm startTime);
    virtual vector <Movimentacao> getAccountBalance(struct tm startTime, struct tm endTime);

    // Teste
    void newMovTest(struct tm dataMov, string description, double value);
};


#endif /* Conta_hpp */
