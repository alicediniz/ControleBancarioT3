//
//  ContaCorrente.hpp
//  Sistema de Controle Bancario
//
//  Created by Alice Diniz Ferreira and Paula Resende Teixeira on 11/30/2019.
//  Copyright © 2019 trabalhoPOO. All rights reserved.
//

#include <string>
#include <vector>
#include "Conta.hpp"
#include "ContaCorrente.hpp"
#include "Cliente.h"

using namespace std;
//
//  Conta.cpp
//  Sistema de Controle Bancario
//
//  Created by Alice Diniz Ferreira and Paula Resende Teixeira on 10/1/19.
//  Copyright © 2019 trabalhoPOO. All rights reserved.
//
#include <string>
#include <vector>
#include "Conta.hpp"
#include "Cliente.h"

using namespace std;

ContaCorrente::ContaCorrente(string name , string document, string address, string phone, double limit)
    : Conta(name, document, address, phone), limiteCredito(limiteCredito) {
    setAccount(cliente);
};

void ContaCorrente::setAccount(Cliente client){
    numConta = proximoNumConta;
    saldo = 0;
    cliente = client;
    movimentacoes = {};
    proximoNumConta++;
};

int ContaCorrente::getAccountNumber () {
    return numConta;
};

double ContaCorrente::getBalance () {
    return saldo;
};

double ContaCorrente::getCreditLimit () {
    return limiteCredito;
};

Cliente ContaCorrente::getClient () {
    return cliente;
};

vector <Movimentacao> ContaCorrente::getFinancialMovements() {
    return movimentacoes;
};

void ContaCorrente::debit(string description, double value) {
    double novoSaldo = saldo - value;
    if (novoSaldo <= limiteCredito || description == "Cobrança de tarifa" || description == "Cobrança de CPMF") {
        saldo = novoSaldo;
        Movimentacao newMov = Movimentacao(description, 'D', value);
        movimentacoes.push_back(newMov);
    }
    else {
        cout << "Saldo insuficiente para debito" << endl;
    }
};

void ContaCorrente::credit (string description, double value) {
    double novoSaldo = saldo + value;
    saldo = novoSaldo;
    Movimentacao newMov = Movimentacao(description, 'C', value);
    movimentacoes.push_back(newMov);
};

vector <Movimentacao> ContaCorrente::getAccountBalance(){
    return getFinancialMovements();
};

vector <Movimentacao> ContaCorrente::getAccountBalance(struct tm startTime){
    vector <Movimentacao> movs = {};
    vector <Movimentacao> accountMovs = getFinancialMovements();
    if (accountMovs.empty()) {
        return {};
    }
    else {
        time_t timeNow = time(0);
        for (auto v : accountMovs) {
            struct tm movDate = v.getDate();
            if ((mktime(&movDate) >= mktime(&startTime)) and (mktime(&movDate) <= timeNow)){
                movs.push_back(v);
            }
        }
    }
    return movs;
};

vector <Movimentacao> ContaCorrente::getAccountBalance(struct tm startTime, struct tm endTime){
    vector <Movimentacao> movs = {};
    vector <Movimentacao> accountMovs = getFinancialMovements();
    if (accountMovs.empty()) {
        return {};
    }
    else {
        for (auto v : accountMovs) {
            struct tm movDate = v.getDate();
            if ((mktime(&movDate) >= mktime(&startTime)) and (mktime(&movDate) <= mktime(&endTime))){
                movs.push_back(v);
            }
        }
    }
    return movs;
};



int ContaCorrente::proximoNumConta = 0;



void ContaCorrente::newMovTest (struct tm dataMov, string description, double value){
    Movimentacao newMov = Movimentacao(description, 'T', value);
    newMov.setMovimentation(dataMov, description, 'T', value);
    movimentacoes.push_back(newMov);
    cout << "Ola" << endl;
};


