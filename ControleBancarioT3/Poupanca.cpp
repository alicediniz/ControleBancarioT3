//
//  Poupanca.hpp
//  Sistema de Controle Bancario
//
//  Created by Alice Diniz Ferreira and Paula Resende Teixeira on 11/30/2019.
//  Copyright © 2019 trabalhoPOO. All rights reserved.
//

#include <string>
#include <vector>
#include "Conta.hpp"
#include "Poupanca.hpp"
#include "Cliente.h"

using namespace std;

Poupanca::Poupanca(string name , string document, string address, string phone, double limit):conta(name, document, address, phone) {
    saldoPoupanca = {};
    setAccount(cliente);
};

void Poupanca::setAccount(Cliente client){
    numConta = proximoNumConta;
    saldo = 0;
    cliente = client;
    movimentacoes = {};
    proximoNumConta++;
};

int Poupanca::getAccountNumber () {
    return numConta;
};

double Poupanca::getBalance (){
    double savings = 0;
    for (auto balance : saldoPoupanca) {
        savings = savings + balance.getValue();
    }
    return savings;
}

double Poupanca::getCreditLimit () {
    return limiteCredito;
};

Cliente Poupanca::getClient () {
    return cliente;
};

vector <Movimentacao> Poupanca::getFinancialMovements() {
    return movimentacoes;
};

vector <SaldoDiaBase> Poupanca::getDateBaseBalance() {
    return saldoPoupanca;
};

void Poupanca::debit(string description, double value) {
    // double novoSaldo = saldo - value;
    // if (novoSaldo <= limiteCredito || description == "Cobrança de tarifa" || description == "Cobrança de CPMF") {
    //     saldo = novoSaldo;
    //     Movimentacao newMov = Movimentacao(description, 'D', value);
    //     movimentacoes.push_back(newMov);
    // }
    // else {
    //     cout << "Saldo insuficiente para debito" << endl;
    // }
};

void Poupanca::credit (string description, double value) {
    // double novoSaldo = saldo + value;
    // saldo = novoSaldo;
    // Movimentacao newMov = Movimentacao(description, 'C', value);
    // movimentacoes.push_back(newMov);
};

vector <Movimentacao> Poupanca::getAccountBalance(){
    return getFinancialMovements();
};

vector <Movimentacao> Poupanca::getAccountBalance(struct tm startTime){
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

vector <Movimentacao> Poupanca::getAccountBalance(struct tm startTime, struct tm endTime){
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



int Poupanca::proximoNumConta = 0;



void Poupanca::newMovTest (struct tm dataMov, string description, double value){
    Movimentacao newMov = Movimentacao(description, 'T', value);
    newMov.setMovimentation(dataMov, description, 'T', value);
    movimentacoes.push_back(newMov);
    cout << "Ola" << endl;
};