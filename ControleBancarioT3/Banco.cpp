//
//  Banco.cpp
//  Sistema de Controle Bancario
//
//  Created by Alice Diniz Ferreira and Paula Resende Teixeira on 10/2/19.
//  Copyright © 2019 trabalhoPOO. All rights reserved.
//

#include <ctime>
#include "Banco.hpp"
#include "ExceptionClass.hpp"
#include "Cliente.h"
#include "Conta.hpp"
#include "ContaCorrente.hpp"
#include "Poupanca.hpp"
#include <fstream>

using namespace std;

Banco::Banco(string bankName){
    setBank(bankName);
};

void Banco::setBank(string bankName){
    nomeBanco = bankName;
    clientes = {};
    contasCorrente = {};
    poupancas = {};
};

vector <Cliente> Banco::getClientList () {
    return clientes;
}

vector <ContaCorrente> Banco::getCorrenteList (){
    return contasCorrente;
}

vector <Poupanca> Banco::getPoupancaList (){
    return poupancas;
};

void Banco::newClient(Cliente client) {
    if (findClient(client.getDocumentNumber()) == -1) {
        clientes.push_back(client);
    }
    else {
        throw ExceptionClass(2);
    }
};

//void Banco::newBankAccount(Cliente client) {
//    string docNum = client.getDocumentNumber();
//    if (checkClientHasAccount(docNum,2) == -1 ) {
//        newClient(client);
//        Poupanca newAcc = Poupanca(client.getName(), docNum, client.getAddress(), client.getPhone());
//        poupancas.push_back(newAcc);
//    }
//    else {
//        throw ExceptionClass(3);
//    }
//};


void Banco::newBankAccount(Cliente client,  double creditLimit) {
    string docNum = client.getDocumentNumber();
    if (checkClientHasAccount(docNum, 1) == -1 ) {
        newClient(client);
        ContaCorrente newAcc = ContaCorrente(client.getName(), docNum, client.getAddress(), client.getPhone(), creditLimit);
        contasCorrente.push_back(newAcc);
    }
    else {
        throw ExceptionClass(3);
    }
};

int Banco::findClient(string cpf_cnpj){
    int clientPosition = 0 ;
    for (auto client :clientes) {
        if (client.getDocumentNumber() == cpf_cnpj){
            return clientPosition;
        }
        clientPosition ++;
    }
    return -1;
}

void Banco::removeClient(string cpf_cnpj) {
    int index = findClient(cpf_cnpj);
    bool deleteClient = true;
    if (index == -1){
        deleteClient = false;
    }
    if (deleteClient) {
        int notFound = 0;
        for ( int tipoConta = 1 ; tipoConta <3 ; tipoConta ++) {
            int accIndex = checkClientHasAccount(cpf_cnpj, tipoConta);
            if ( accIndex != - 1) {
                int accNumber;
                if (tipoConta == 1) {
                    accNumber = contasCorrente[accIndex].getAccountNumber();
                }
                else {
                    accNumber = poupancas[accIndex].getAccountNumber();
                }
                removeBankAccount(accNumber, tipoConta);
            }
            else {
                notFound ++;
            }
        }
        if (notFound != 2) {
            clientes.erase(clientes.begin()+index);
        } else {
            throw ExceptionClass(4);
        }
    }
};

void Banco::removeBankAccount(int accountNumber, int tipoConta) {
    int accIndex = findAccountIndex(accountNumber, tipoConta);
    if ( accIndex != - 1){
        if ( tipoConta == 1 ) {
            contasCorrente.erase(contasCorrente.begin() + accIndex);
        }
        else {
            poupancas.erase(poupancas.begin()+ accIndex);
        }
    }
    else{
        throw ExceptionClass(5);
    }
};

void Banco::newDeposit(int accountNumber, double value, string description) {
    if (value <= 0) {
        throw ExceptionClass(6);
    }
    int accIndex = findAccountIndex(accountNumber, 1);
    if ( accIndex != - 1) {
        contasCorrente[accIndex].credit(description, value);
    }
    else {
        throw ExceptionClass(5);
    }
};

void Banco::newDeposit(int accountNumber, double value, int dataBase,string description) {
    if (value <= 0) {
        throw ExceptionClass(6);
    }
    int accIndex = findAccountIndex(accountNumber, 1);
    if ( accIndex != - 1) {
        poupancas[accIndex].credit(description,value, dataBase);
    }
    else {
        throw ExceptionClass(5);
    }
};


void Banco::newWithdraw(int accountNumber, double value, string description ) {
    if (value <= 0) {
        throw ExceptionClass(6);
    }
    int accIndex = findAccountIndex(accountNumber,1);
    if ( accIndex != -1) {
        contasCorrente[accIndex].debit(description, value);
    }
    else {
        throw ExceptionClass(5);
    }
};

void Banco::newWithdraw(int accountNumber, double value, int dataBase, string description ) {
    if (value <= 0) {
        throw ExceptionClass(6);
    }
    int accIndex = findAccountIndex(accountNumber,2);
    if ( accIndex != -1) {
        poupancas[accIndex].debit(description, value, dataBase);
    }
    else {
        throw ExceptionClass(5);
    }
};

void Banco::newTransaction (int sourceAccountNumber, int destinationAccountNumber, double value, int tipoConta1 , int tipoConta2){
    if (value <= 0) {
        throw ExceptionClass(6);
    }
    if ( findAccountIndex(sourceAccountNumber, tipoConta1) == -1 ) {
        throw ExceptionClass(7);
    }
    if (findAccountIndex(destinationAccountNumber, tipoConta2) == -1) {
        throw ExceptionClass(8);
    }
    double atualSaldo;
    if (tipoConta1 == 1 ) {
        atualSaldo = contasCorrente[sourceAccountNumber].getBalance();
    }
    else {
        atualSaldo = poupancas[sourceAccountNumber].getBalance();
    }
    if ( atualSaldo - value >= 0 ) {
        string descriptionSource = "Transferência para conta " + std::to_string(destinationAccountNumber);
        string descriptionDestination = "Transferência da conta " + std::to_string(sourceAccountNumber);
        if ( tipoConta1 == 1) {
            newWithdraw(sourceAccountNumber, value, descriptionSource);
        }
        else {
            time_t timeNow = time(0);
            struct tm actualDay = *localtime(&timeNow);
            int day = actualDay.tm_mday;
            newWithdraw(sourceAccountNumber, value, day, descriptionSource);
        }
        
        if ( tipoConta2 == 1 ) {
            newDeposit(destinationAccountNumber, value, descriptionDestination);
        }
        else {
            time_t timeNow = time(0);
            struct tm actualDay = *localtime(&timeNow);
            int day = actualDay.tm_mday;
            newDeposit(destinationAccountNumber, value, day, descriptionDestination);
        }
    }
    else {
        throw ExceptionClass(9);
    }
};

void Banco::newFee (double value) {
    string description = "Cobrança de tarifa";
    int j;
    for (j = 0; j < contasCorrente.size(); j++ ) {
        contasCorrente[j].debit(description, value);
    }
};

void Banco::newSavingsIncome() {
    time_t timeNow = time(0);
    struct tm actualDay = *localtime(&timeNow);
    int day = actualDay.tm_mday;

    for (int j = 0; j < poupancas.size(); j++) {
        poupancas[j].creditIncome(day);
    }
};

void Banco::newTaxCPMF () {
    string description = "Cobrança de CPMF";
    double descountFee = 0.0038;
    double descountValue = 0 ;
    vector <Movimentacao> movimentacoesAux;
    time_t lastDay = time(0);
    time_t firtsDay = lastDay - 7*24*60*60;

    for (auto acc:contasCorrente) {
        movimentacoesAux = acc.getFinancialMovements();
        for (auto mov:movimentacoesAux){
            if(mov.getDebitCredit() == 'D'){
                struct tm movDate = mov.getDate();
                if(mktime(&movDate) >= firtsDay || mktime(&movDate) <= lastDay ) {
                    descountValue = mov.getValue();
                }
            }
        }

        descountValue = descountValue * descountFee;
        newWithdraw(acc.getAccountNumber(), descountValue, description);
    }
}

double Banco::bankBalance(int accountNumber, int tipoConta) {
    int accIndex = findAccountIndex(accountNumber, tipoConta);
    double saldo = 0.0;
    if( accIndex != - 1) {
        if ( tipoConta == 1) {
            saldo = contasCorrente[accIndex].getBalance();
        }
        else {
            saldo = poupancas[accIndex].getBalance();
        }
    }
    else {
        throw ExceptionClass(5);
    }
    return saldo;
};

vector <Movimentacao> Banco::bankStatement(int accountNumber) {
    time_t timeNow = time(0);
    struct tm actualMonth;
    actualMonth = *localtime(&timeNow);
    actualMonth.tm_mday = 1;
    vector <Movimentacao> statement;
    
    int accIndex = findAccountIndex(accountNumber,1);
    if (accIndex != - 1) {
        statement = bankStatement(accountNumber, actualMonth);
    }
    else {
        throw ExceptionClass(5);
    }
    return statement;
};

vector <Movimentacao> Banco::bankStatement(int accountNumber, struct tm startTime) {
    int accIndex = findAccountIndex(accountNumber,1);
    vector <Movimentacao> statement;
    if (accIndex != -1) {
        statement =  contasCorrente[accountNumber].getAccountBalance(startTime);
    }
    else {
        throw ExceptionClass(5);
    }
    return statement;
};

vector <Movimentacao> Banco::bankStatement(int accountNumber, struct tm startTime, struct tm endTime) {
    int accIndex = findAccountIndex(accountNumber,1);
    vector <Movimentacao> statement;
    if (accIndex != -1) {
        statement =  contasCorrente[accIndex].getAccountBalance(startTime, endTime);
    }
    else {
        throw ExceptionClass(5);
    }
    return statement;
};

void Banco::writeFile(string fileName, string operation, string text) {
    ofstream outputFile;
    outputFile.open(fileName, ios::app);
    outputFile << operation + ":\n";
    outputFile << text + "\n";
    outputFile.close();
};

void Banco::readFile(string fileName) {
    ifstream inputFile;
    inputFile.open(fileName);
    string readData;
    if(inputFile.is_open()) {
        while (getline(inputFile, readData)) {
            //leitura linha a linha
        }
    };
    inputFile.close();
};

int Banco::findAccountIndex(int accountNumber, int tipoConta) {
    if (tipoConta == 1) {
        for (int j= 0; j< contasCorrente.size(); j++ ) {
            if (contasCorrente[j].getAccountNumber() == accountNumber) {
                return j;
            }
        }
    }
    else {
        for (int j= 0; j< poupancas.size(); j++ ) {
            if (poupancas[j].getAccountNumber() == accountNumber) {
                return j;
            }
        }
    }

    return -1;
}

int Banco::checkClientHasAccount(string documentNumber, int tipoConta) {
    int count = 0;
    if ( tipoConta == 1 ) {
        vector <ContaCorrente> listAccs = contasCorrente;
        for (auto acc:listAccs) {
            if ( acc.getClient().getDocumentNumber()  == documentNumber) {
                return count;
            }
            count++;
        }
    }
    else {
//        vector <Poupanca> listAccs = poupancas;
//        for (auto acc:listAccs) {
//            if ( acc.getClient().getDocumentNumber()  == documentNumber) {
//                return count;
//            }
//            count++;
//        }
        return 0;
    }
    return -1;
}
