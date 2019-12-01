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
#include "ExceptionClass.hpp"

using namespace std;

Poupanca::Poupanca(string name , string document, string address, string phone):Conta(name, document, address, phone) {
    Cliente client = Cliente(name, document, address,phone);
    setAccount(client);
};

void Poupanca::setAccount(Cliente client){
    setNumConta(getProximoNumConta());
    setBalance(0);
    setClient(client);
    setMovimentacoes({});
    setProxNumConta();
    saldoPoupanca = {};
};

double Poupanca::getBalance (){
    double savings = 0;
    for (auto balance : saldoPoupanca) {
        savings = savings + balance.getValue();
    }
    return savings;
}

vector <SaldoDiaBase> Poupanca::getSavingsMovements() {
    return saldoPoupanca;
};

int Poupanca::findBaseDateSaving(int baseDate) {
    for (int j= 0; j< saldoPoupanca.size(); j++ ) {
        if (saldoPoupanca[j].getDate() == baseDate) {
            return saldoPoupanca[j].getValue();
        }
    }
    return -1;
}

int Poupanca::checkBaseDate(int baseDate) {
    for (int j= 0; j< saldoPoupanca.size(); j++ ) {
        if (saldoPoupanca[j].getDate() == baseDate) {
            return j;
        }
    }
    return -1;
}

vector<int> Poupanca::checkNearestBaseDate(int baseDate) {
    vector <int> vetorDeDiferencas;
    for (int j= 0; j< saldoPoupanca.size(); j++ ) {
        int baseDateModule = abs(baseDate - saldoPoupanca[j].getDate());
        vetorDeDiferencas.push_back(baseDateModule);
    }
    return vetorDeDiferencas;
}


void Poupanca::debit(string description, double value, int baseDate) {
    if (baseDate == 29 || baseDate == 30 || baseDate == 31){
        baseDate = 28;
    }
    try {
        vector <int> distanciasDatas = checkNearestBaseDate(baseDate);
        bool breakOut = false;
        while (distanciasDatas.size() != 0 || !breakOut){
            int minValue = *min_element(distanciasDatas.begin(), distanciasDatas.end());
            for(int j= 0; j< distanciasDatas.size(); j++){
                if(distanciasDatas[j] == minValue){
                    if( value <= saldoPoupanca[j].getValue()){
                        int novoSaldo = saldoPoupanca[j].getValue() - value;
                        saldoPoupanca[j].setValue(novoSaldo);
                        breakOut = true;
                        break;
                    }
                    else {
                        distanciasDatas.erase(distanciasDatas.begin()+j);
                    }
                }
            }
        }
        if (distanciasDatas.size() == 0) {
            throw 1;
        }

        vector <Movimentacao> newMovs = getFinancialMovements();
        Movimentacao newMov = Movimentacao(description, 'D', value);
        newMovs.push_back(newMov);
        setMovimentacoes(newMovs);
    }
    catch (int e) {
        throw ExceptionClass(e);
    }
};

void Poupanca::credit (string description, double value, int baseDate) {
    int novoSaldo = 0;

    if (baseDate == 29 || baseDate == 30 || baseDate == 31){
        baseDate = 28;
    }

    int datePosition = checkBaseDate(baseDate);

    if (datePosition != -1) {
        novoSaldo = findBaseDateSaving(baseDate) + value;
        saldoPoupanca[datePosition].setValue(novoSaldo);
    }
    else {
        SaldoDiaBase newSaving = SaldoDiaBase(baseDate, value);
        saldoPoupanca.push_back(newSaving);
    }

    vector <Movimentacao> newMovs = getFinancialMovements();
    Movimentacao newMov = Movimentacao(description, 'C', value);
    newMovs.push_back(newMov);
    setMovimentacoes(newMovs);
};

void Poupanca::creditIncome (int baseDate) {
    int novoSaldo = 0;

    if (baseDate == 29 || baseDate == 30 || baseDate == 31){
        baseDate = 28;
    }

    int datePosition = checkBaseDate(baseDate);

    if (datePosition != -1) {
        novoSaldo = findBaseDateSaving(baseDate)*(1.01);
        saldoPoupanca[datePosition].setValue(novoSaldo);
        
        vector <Movimentacao> newMovs = getFinancialMovements();
        Movimentacao newMov = Movimentacao("Rendimentos", 'C', novoSaldo);
        newMovs.push_back(newMov);
        setMovimentacoes(newMovs);
    }
};
