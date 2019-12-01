//
//  Interface.cpp
//  Sistema de Controle Bancario
//
//  Created by Alice Diniz Ferreira on 10/5/19.
//  Edited by Monique Stephanie Rodrigues Silva 10/11/19.
//  Edited by Paula Resende Teixeira on 10/15/19.
//  Copyright © 2019 trabalhoPOO. All rights reserved.
//

#include "Interface.hpp"
#include "Banco.hpp"
#include "ExceptionClass.hpp"
#include <time.h>
#include <string>
#include <ctime>
#include "ContaCorrente.hpp"
#include "Poupanca.hpp"

using namespace std;

Interface::Interface(string bankName):interfaceBanco(bankName) {};

Banco Interface::getBank() {
    return interfaceBanco;
}

void Interface::menu()
{
    while (1)
    {
        int opcao;
        puts("  [1] - Cadastrar novo Cliente\n");
        puts("  [2] - Abrir Nova Conta\n");
        puts("  [3] - Excluir Cliente\n");
        puts("  [4] - Excluir Poupança\n");
        puts("  [5] - Excluir Conta Corrente\n");
        puts("  [6] - Depositar Poupança\n");
        puts("  [7] - Depositar Conta Corrente\n");
        puts("  [8] - Sacar Poupança\n");
        puts("  [9] - Sacar Conta Corrente\n");
        puts(" [10] - Transferencia\n");
        puts(" [11] - Cobrar Tarifa\n");
        puts(" [12] - Cobrar CPMF\n");
        puts(" [13] - Saldo\n");
        puts(" [13] - Extrato\n");
        puts(" [14] - Listar Clientes\n");
        puts(" [15] - Listar Contas Corrente\n");
        puts(" [16] - Listar Contas Poupança\n");
        puts(" [17] - Teste\n");
        puts(" [18] - Creditar rendimento em poupança\n");
        puts("Qualquer outra tecla para Sair");
        puts("\n\n");
        cin >> opcao;
        switch (opcao)
        {
        case 1: //METODO PARA CRIAR NOVO CLIENTE E INSERIR NA LISTA DE CLIENTES
        {
            criaNovoCliente();
            break;
        }

        case 2: //METODO PARA CRIAR NOVA CONTA E INSERIR NA LISTA DE CONTAS
        {
            criaNovaConta();
            break;
        }

        case 3: //METODO PARA EXCLUIR UM CLIENTE QUE NÃO TENHA CONTA
        {
            excluiCliente();
            break;
        }

        case 4: //METODO PARA EXCLUIR UMA CONTA POUPANCA DE UM CLIENTE
        {
            excluiConta(2);
            break;
        }

        case 5: //METODO PARA EXCLUIR UMA CONTA CORRENTE DE UM CLIENTE
        {
            excluiConta(1);
            break;
        }
                
        case 6: //METODO PARA DEPOSITAR EM UMA CONTA POUPANCA
        {
            deposita(2);
            break;
        }
                        
        case 7: //METODO PARA DEPOSITAR EM UMA CONTA CORRENTE
        {
            deposita(1);
            break;
        }
                
        case 8: //METODO PARA SACAR DE UMA CONTA POUPANCA
        {
            saca(2);
            break;
        }

        case 9: //METODO PARA SACAR DE UMA CONTA CORRENTE
        {
            saca(1);
            break;
        }
                
        case 10: //METODO PARA TRANSFERÊNCIA ENTRE CONTAS
        {
            transfere();
            break;
        }

        case 11: //METODO PARA COBRAR TARIFA
        {
            interfaceBanco.newFee(15.0);
            break;
        }

        case 12: //METODO PARA COBRAR CPMF
        {
            cout << "Sera tarifado CPMF." << endl;
            interfaceBanco.newTaxCPMF();
            break;
        }

        case 13: //METODO PARA VER SALDO
        {
            checaSaldo();
            break;
        }
        case 14: //METODO PARA LISTAR EXTRATO
        {
            listStatement();
            break;
        }

        case 15:
        {
            listaClientes();
            break;
        }

        case 16:
        {
            listaContasCorrentes();
            break;
        }
        case 17:
        {
            listaPoupancas();
            break;
        }
        case 18: {
            interfaceBanco.testeStatement();
            break;
        }
        case 19: //METODO PARA CREDITAR RENDIMENTO NAS POUPANÇAS
        {
            interfaceBanco.newSavingsIncome();
            break;
        }
        case 0:
            return;
            break;

        default:
            return;
            break;
        }
    };
};

void Interface::criaNovoCliente()
{
    string nome;
    string cpf_cnpj;
    string endereco;
    string telefone;

    cout << "Nome Completo:" << endl;
    cin.ignore();
    getline(cin, nome);
    cout << "Número CPF/CNPJ:" << endl;
    cin >> cpf_cnpj;
    cout << "Endereço:" << endl;
    cin.ignore();
    getline(cin, endereco);
    cout << "Número de telefone:" << endl;
    cin >> telefone;

    Cliente novoCliente = Cliente(nome, cpf_cnpj, endereco, telefone);
    try {
        interfaceBanco.newClient(novoCliente);
        cout << "Cliente cadastrado com sucesso" << endl;
    }
    catch (ExceptionClass& error) {
        cout << error.what() << endl;
    };
};

void Interface::criaNovaConta()
{
    string nome;
    string cpf_cnpj;
    string endereco;
    string telefone;
    double limiteDeCredito;
    
    cout << "Digite os dados do cliente para gerar a conta" << endl;
    cout << "Nome Completo: " << endl;
    cin.ignore();
    getline(cin, nome);
    cout << "Número CPF/CNPJ: " << endl;
    cin >> cpf_cnpj;
    cout << "Endereço: " << endl;
    cin.ignore();
    getline(cin, endereco);
    cout << "Número de telefone: " << endl;
    cin >> telefone;
    cout << "Limite de Credito: " << endl;
    cin >> limiteDeCredito;
    
    Cliente cliente = Cliente(nome, cpf_cnpj, endereco, telefone);
    try {
        interfaceBanco.newBankAccount(cliente, limiteDeCredito);
        cout << "Conta criada com sucesso" << endl;
    }
    catch (ExceptionClass& error) {
        cout << error.what() << endl;
    };
    
}

void Interface::excluiCliente () {
    string cadastro;
    
    cout << "Digite CPF/CNPJ para excluir o cadastro do cliente:";
    cin >> cadastro;

    try {
        interfaceBanco.removeClient(cadastro);
        cout << "Cliente excluido da base de dados" << endl;
    }
    catch (ExceptionClass& error) {
        cout << error.what() << endl;
    };
}


void Interface::excluiConta(int tipoConta) {
    int numConta;
    cout << "Digite a o numero da conta que deseja excluir:";
    cin >> numConta;

    try {
        interfaceBanco.removeBankAccount(numConta,tipoConta);
        cout << "Conta excluida" << endl;
    }
    catch (ExceptionClass& error) {
        cout << error.what() << endl;
    };
    
}

void Interface::deposita(int tipoConta) {
    int numConta;
    double valorDeposito;
    cout << "Para um novo deposito, digite numero da conta:";
    cin >> numConta;
    cout << "Digite o valor do deposito:\n";
    cin >> valorDeposito;

    try {
        if (tipoConta == 1 ) {
            interfaceBanco.newDeposit(numConta, valorDeposito);
        }
        else {
            time_t timeNow = time(0);
            struct tm actualDay = *localtime(&timeNow);
            int day = actualDay.tm_mday;
            interfaceBanco.newDeposit(numConta, valorDeposito,day);
        }
        
    }
    catch (ExceptionClass& error) {
        cout << error.what() << endl;
    };
}

void Interface::saca(int tipoConta) {
    int numConta;
    double valorSaque;
    cout << "Para novo saque digite o numero da conta :\n";
    cin >> numConta;
    cout << "Valor do saque:\n";
    cin >> valorSaque;

    try {
        if (tipoConta == 1 ) {
            interfaceBanco.newWithdraw(numConta, valorSaque);
        }
        else {
            time_t timeNow = time(0);
            struct tm actualDay = *localtime(&timeNow);
            int day = actualDay.tm_mday;
            interfaceBanco.newWithdraw(numConta, valorSaque, day);
        }
    }
    catch (ExceptionClass& error) {
        cout << error.what() << endl;
    };
}

void Interface::transfere() {
    int contaOrigem;
    int contaDestino;
    double valorTransferencia;
    int tipoContaFonte;
    int tipoContaDestino;
    
    cout << "Digite o numero da conta de origem: \n";
    cin >> contaOrigem;
    cout << "Digite o tipo da conta de origem (1 para CC e 2 para Poupanca)\n";
    cin >> tipoContaFonte;
    
    cout << "Digite o numero da conta de destino: \n";
    cin >> contaDestino;
    cout << "Digite o tipo da conta de destino (1 para CC e 2 para Poupanca)\n";
    cin >> tipoContaDestino;
    
    cout << "Digite o valor da transferencia: \n";
    cin >> valorTransferencia;

    try {
        interfaceBanco.newTransaction(contaOrigem, contaDestino, valorTransferencia, tipoContaFonte, tipoContaDestino);
    }
    catch (ExceptionClass& error) {
        cout << error.what() << endl;
    };
    
}

void Interface::checaSaldo(){
    int numeroConta;
    int tipoConta;
    cout << "Digite o tipo da conta (1 para CC e 2 para Poupanca)\n";
    cin >> tipoConta;
    cout << "Digite sua conta: ";
    cin >> numeroConta;

    try {
        cout << interfaceBanco.bankBalance(numeroConta,tipoConta) << endl;
    }
    catch (ExceptionClass& error) {
        cout << error.what() << endl;
    };
    
}

void Interface::listaClientes() {
    vector <Cliente> listClients = interfaceBanco.getClientList();
    for (auto cliente : listClients ){
        cout << "Nome: " << cliente.getName() << endl;
    }
}

void Interface::listaContasCorrentes() {
    vector <ContaCorrente> listCurrentsAccs = interfaceBanco.getCorrenteList();
    for (auto acc : listCurrentsAccs){
        cout << "Cliente: " << acc.getClient().getName() << endl;
        cout << "Número da Conta: " << acc.getAccountNumber() << endl;
    }
}

void Interface::listaPoupancas() {
//    vector <Poupanca> listSavingsAccs = interfaceBanco.getPoupancaList();
//    for (auto acc : listSavingsAccs){
//        cout << "Cliente: " << acc.getClient().getName() << endl;
//        cout << "Número da Conta: " << acc.getAccountNumber() << endl;
//    }
}


void Interface::listStatement() {
    char extrato;
    int numConta;
    string stringStartDate;
    string stringEndDate;
    
    struct tm inputStartDate;
    struct tm inputEndDate;
    
    cout << "Escolha o tipo de extrato desejado:\n"
         << " A) Extrato do ultimo mes.\n"
         << " B) Extrato com data incial ate data vigente.\n"
         << " C) Extrato entre as datas escolhidas.\n"
         << endl;
    cin >> extrato;

    if (extrato == 'a' || extrato == 'A'){
        cout << "Digite numero da conta: " << endl;
        cin >> numConta;

        try {
            vector <Movimentacao> auxStatement = interfaceBanco.bankStatement(numConta);
            printStatement(auxStatement);
        }
        catch (ExceptionClass& error) {
            cout << error.what() << endl;
        };
    }
    
    if (extrato == 'b' || extrato == 'B'){
        cout << "Digite numero da conta: " << endl;
        cin >> numConta;
        cout << "Digite a data incial: (Formato DD/MM/AAAA)" << endl;
        cin >> stringStartDate;
        inputStartDate = handleStringDate(stringStartDate);

        try {
            vector <Movimentacao> auxStatement = interfaceBanco.bankStatement(numConta, inputStartDate);
            printStatement(auxStatement);
        }
        catch (ExceptionClass& error) {
            cout << error.what() << endl;
        };
    }

    if (extrato == 'c' || extrato == 'C'){
        cout << "Digite numero da conta: " << endl;
        cin >> numConta;
        cout << "Digite a data incial: " << endl;
        cin >> stringStartDate;
        cout << "Digite a data final: " << endl;
        cin >> stringEndDate;
        inputStartDate = handleStringDate(stringStartDate);
        inputEndDate = handleStringDate(stringEndDate);
        
        try {
            vector <Movimentacao> auxStatement = interfaceBanco.bankStatement(numConta, inputStartDate, inputEndDate);
            printStatement(auxStatement);
        }
        catch (ExceptionClass& error) {
            cout << error.what() << endl;
        };
    }
}


struct tm Interface::handleStringDate(string inputDate) {
    int day = stoi(inputDate.substr(0,inputDate.find("/")));
    
    string monthYear = inputDate.substr(inputDate.find("/") + 1);
    int month = stoi(monthYear.substr(0, monthYear.find("/")));
    int year = stoi(monthYear.substr(monthYear.find("/")+1));
    
    time_t timeNow = time(0);
    struct tm convertedDate;
    convertedDate = *localtime(&timeNow);

    convertedDate.tm_mday = day;
    convertedDate.tm_mon = month - 1;
    convertedDate.tm_year = year - 1900;
    return convertedDate;
}


void Interface::printStatement(vector <Movimentacao> statements){
    for (auto it : statements){
        struct tm dataInicial = it.getDate();
        cout << "Data:" << dataInicial.tm_mday << "/" << (dataInicial.tm_mon + 1) << "/" << (dataInicial.tm_year + 1900) << endl;
        cout << "Descrição:" << it.getDescription() << endl;
        cout << "Valor:" << it.getValue() << endl;
        cout << "\n\n";
    }
}
