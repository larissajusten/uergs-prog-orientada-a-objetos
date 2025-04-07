#include <iostream>
#include <stdlib.h>
#include <vector>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;


class Printavel {
    public:
        virtual ~Printavel() {}
        virtual void print() = 0;
};


class Salvavel {
    public:
        virtual ~Salvavel() {}
        virtual void salvarItem(string item) = 0;
        virtual void carregarItem(string item) = 0;
};


class Coordenada{
     protected:
         double coordenadaX;
         double coordenadaY;

     public:
         Coordenada(double x, double y) { 
             coordenadaX = x;
             coordenadaY = y;
          }
         Coordenada() { 
          }

         vector<double> getCoordenadas() {
             return { coordenadaX, coordenadaY };
         }

         void setCoordenadas(double x, double y) {
             coordenadaX = x;
             coordenadaY = y;
         }
};


class Rota : public Printavel {
    protected:
        int id;
        string nome;
        vector<Coordenada> coordenadas;
    
    public:

        Rota(){ }

        Rota(int id, string nome){ this->id = id; this->nome = nome;}

        string getNome() {
            return nome;
        }

        int getId() {
            return id;
        }

        vector<Coordenada> getCoordenadas() {
            return coordenadas;
        }

        void setNome(string nome) {
            this->nome = nome;
        }

        void setId(int id) {
            this->id = id;
        }

        void setCoordenadas(vector<Coordenada> coordenadas) {
            this->coordenadas = coordenadas;
        }

        void print() {
            cout << "id: " << this->getId() << ", nome: " << this->getNome() << ", rotas: ";
            for(Coordenada coord : coordenadas){
                cout << "(" << coord.getCoordenadas()[0] << ", " << coord.getCoordenadas()[1] << "), ";
            }
            cout << endl;
        }

        void adicionarCoordenada(Coordenada coordenada){
            coordenadas.push_back(coordenada);
        }
};


class Rotas : public Printavel, public Salvavel {
    protected:
        vector<Rota> listaDeRotas;

    public:
        Rotas() { }       

        void adicionarItem(Rota rota) {
           listaDeRotas.push_back(rota);
        }

        void apagarItem(int id) {
            for(int i = 0; i < listaDeRotas.size(); i++){
                if(listaDeRotas.at(i).getId() == id){
                    listaDeRotas.erase(listaDeRotas.begin() + i);
                }
            }
        }

        void print() {
            for(Rota item : listaDeRotas){
                item.print();
            }
        }

        void mostrarItem(int id) {
            for(int i = 0; i < listaDeRotas.size(); i++){
                if(listaDeRotas.at(i).getId() == id){
                    listaDeRotas.at(i).print();
                }
            }
        }

        void abrirNavegador() {
            cout << "Abrindo página web..." << endl;
            system("\"C:\\Program Files\\Mozilla Firefox\\firefox.exe\" google.com/search?q=rotas");
        }

        void salvarItem(string filename){
            ofstream file (filename);
            if (file.is_open())
            {
                for(Rota item : listaDeRotas){
                    file << item.getId() << ',' << item.getNome();
                    for(Coordenada coord : item.getCoordenadas()){
                        file << ',' << coord.getCoordenadas()[0] << ',' << coord.getCoordenadas()[1] << endl;
                    }
                }
                file.close();
            }
            else {
                cout << "Unable to open file";
            }
        }

        void carregarItem(string arquivo){
            int i = 0;
            string linha;
            int id;
            double x, y;
            string nome;
            ifstream file(arquivo);
            if (file.is_open())
            {
                while( getline(file, linha) ){
                    id = stoi(linha.substr(0,linha.find(',')));
                    linha.erase(0,linha.find(',')+1);
                    nome = linha.substr(0,linha.find(','));
                    linha.erase(0,linha.find(',')+1);
                    listaDeRotas.push_back(Rota(id, nome));
                    while(linha.find(',') != -1){
                        x = stod(linha.substr(0,linha.find(',')));
                        linha.erase(0,linha.find(',')+1);
                        y = stod(linha.substr(0,linha.find(',')));
                        linha.erase(0,linha.find(',')+1);
                        listaDeRotas.back().adicionarCoordenada(Coordenada(x,y));
                    }
                } 
                file.close();
            }
            else {
                cout << "Não foi possivel abrir o arquivo"; 
            }
        }

        int validarId(int id){
            int existe = -1;
            for(Rota r : listaDeRotas){
                if(r.getId() == id){
                    existe = 1;
                    break;
                }
            }
            return existe;
        }

        Rota getRota(int id){
            for(Rota r : listaDeRotas){
                if(r.getId() == id){
                    return r;
                }
            }
        }

};



int main() {
    Rotas rotas;
    double voltaMenu;
    double x, y;
    string nome;
    int id;
    int entradaMenu, idItemSelecionado;
    string arquivo;
    Coordenada coordenada;

    while(1 == 1) {
        cout << "\n\nMENU DE OPERACOES POSSIVEIS " << endl;
        cout << "1-adicionar rota." << endl;
        cout << "2-adicionar coordenada." << endl;
        cout << "3-mostrar todas as rotas." << endl;
        cout << "4-Mostrar rota por id." << endl;
        cout << "5-Apaga rota." << endl;
        cout << "6-Salva rotas." << endl;
        cout << "7-Carrega rotas." << endl;
        cout << "8-Abre navegador." << endl;
        cout << "0-Encerrar." << endl;
        cout << "Operacao: ";
        cin >> entradaMenu;

        if(entradaMenu == 0) break;

        switch (entradaMenu) {

            // cria rota - ok
            case 1:  
                cout << "Digite o id da rota: " << endl;
                cin >> id;
                if(rotas.validarId(id) == 1){
                    cout << "o id inserido já existe!" << endl;
                    break;
                }
                cout << "Digite o nome da rota: " << endl;
                cin >> nome;
                rotas.adicionarItem(Rota(id,nome));
                system("pause");
                break;
            // cria coordenada - ok
            case 2:  
                cout << "Digite o id da rota da nova coordenada: " << endl;
                cin >> x;
                if(rotas.validarId(id) == -1){
                    cout << "o id inserido não existe!" << endl;
                    break;
                }
                cout << "Digite a coordenada X: " << endl;
                cin >> x;
                cout << "Digite a coordenada Y: " << endl;
                cin >> y;
                coordenada = Coordenada(x,y);
                rotas.getRota(id).adicionarCoordenada(coordenada);
                system("pause");
                break;

            // mostra rotas - ok
            case 3:
                cout << "Todos items do objeto rotas: " << endl;
                rotas.print();
                system("pause");
                break;

            // mostra rota - ok
            case 4:
                cout << "Digite o id da rota: ";
                cin >> id;
                if(rotas.validarId(id) == -1){
                    cout << "o id inserido não existe!" << endl;
                    break;
                }
                rotas.mostrarItem(id);
                system("pause");
                break;

            // apaga rota - ok
            case 5:
                cout << "Digite o id do item que deseja apagar: ";
                cin >> id;
                if(rotas.validarId(id) == -1){
                    cout << "o id inserido não existe!" << endl;
                    break;
                }
                rotas.apagarItem(id);
                system("pause");
                break;

            // salva lista
            case 6:
                cout << "Digite o nome do arquivo para salvar: " << endl;
                cin >> arquivo;
                rotas.salvarItem(arquivo);
                system("pause");
                break;

            // carrega lista
            case 7:
                cout << "Digite o nome do arquivo para carregar: " << endl;
                cin >> arquivo;
                rotas.carregarItem(arquivo);
                system("pause");
                break;

            // abrir navegador
            case 8:
                rotas.abrirNavegador();
                system("pause");
                break;

            default:
                cout << "Opção inválida." << endl;
                cout << endl;
                system("pause");
                break;
        }
    }   

    return 0;
}
