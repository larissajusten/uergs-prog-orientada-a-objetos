#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <list>

#define PI 3.14159265

using namespace std;

enum Forma { POLAR, RETANGULAR };

class Imprimivel
{
  public:
    virtual void imprime() = 0;
};

class Salvavel
{
  public:
    virtual void salva() = 0;
    virtual void carrega() = 0;
};

class Complexo : public Imprimivel, public Salvavel
{
  private:
    Forma forma = RETANGULAR;
    double real, imaginario, magnitude, angulo;
    int indexDoObjeto = 0;

  /** Construtores */
  public:
    Complexo()
    {
      indexDoObjeto = 0;
      real = 0;
      imaginario = 0;
      geraESalvaFormaPolar();
    }

    Complexo(int index, double primeiroParametro, double segundoParametro)
    {
      indexDoObjeto = index;
      real = primeiroParametro;
      imaginario = segundoParametro;
      geraESalvaFormaPolar();
    }

    Complexo(int index, Forma formaSelecionada, double primeiroParametro, double segundoParametro)
    {
      if(formaSelecionada == RETANGULAR)
      {
        indexDoObjeto = index;
        real = primeiroParametro;
        imaginario = segundoParametro;
        geraESalvaFormaPolar();
      }
      else
      {
        indexDoObjeto = index;
        forma = POLAR;
        magnitude = primeiroParametro;
        angulo = segundoParametro;
        geraESalvaFormaRetangular();
      }
    }

  /** Getter e Setter */
  public:
    double getReal() { return real; }

    double getImaginario() { return imaginario; }

    double getMagnitude() { return magnitude; }

    double getAngulo() { return angulo; }

    string getFormaPolar()
    {
      string magnitude = to_string(getMagnitude());
      string angulo = to_string(getAngulo());
      return  magnitude + " L " + angulo ;
    }

    string getFormaRetangular()
    {
      string real = to_string(getReal());
      string imaginario = to_string(getImaginario());
      return real + " + " + (imaginario + "i");
    }

  private:
    void setReal(double real) { this->real = real; }

    void setImaginario(double imaginario) { this->imaginario = imaginario; }

    void setMagnitude(double magnitude) { this->magnitude = magnitude; }

    void setAngulo(double angulo) { this->angulo = angulo; }

  /** Classes das interfaces */
  public:
    virtual void imprime()
    {
      string magnitude = to_string(getMagnitude());
      string angulo = to_string(getAngulo());
      cout << "Retangular: " << magnitude << " L " << angulo << endl;

      string real = to_string(getReal());
      string imaginario = to_string(getImaginario());
      cout << "Polar: " << real << " + " << (imaginario + "i") << endl;
    }

    virtual void salva()
    {
      cout << "Salvando numero complexo...\n" << endl;
      fstream myfile;

      string nomeDoArquivo = "numerosComplexos" + to_string(indexDoObjeto) + ".txt";

      myfile.open(nomeDoArquivo, ios::in | ios::app);

      if(myfile.is_open())
      {
        myfile << "Forma polar: " << getFormaPolar() << endl;
        myfile << "Forma retangular: " << getFormaRetangular() << endl;
        myfile << "/" << endl;
      }
      else
      {
        cout << "ERRO: N�o foi possivel abrir o arquivo";
      }

      myfile.close();
    }

    virtual void carrega()
    {
      cout << "Carregando  numero complexo...\n" << endl;

      int i=0;
      string line;
      fstream myfile;
      string word[16];

      string nomeDoArquivo = "numerosComplexos" + to_string(indexDoObjeto) + ".txt";

      myfile.open(nomeDoArquivo, ios::in | ios::app);

      if (myfile.is_open())
      {
        while(myfile.good())
        {
          getline(myfile, line, ' ');
          if (line != " ")
          {
            word[i]=line;
            i++;
          }
        }
      }
      else
      {
          cout << "ERRO: N�o foi possivel abrir o arquivo.";
      }

      myfile.close();

      setMagnitude(stod(word[2]));
      setAngulo(stod(word[4]));

      setReal(stod(word[6]));
      setImaginario(stod(word[8].erase(word[8].size() - 2)));
    }

  /** Utilizadas no construtor */
  private:
    void geraESalvaFormaPolar()
    {
      double divisaoImagReal = verificaExcecoes(getImaginario()/getReal());
      double angulo = atan(divisaoImagReal)* 180/PI;

      double magnitude = sqrt(pow(getReal(), 2) + pow(getImaginario(), 2));

      setMagnitude(arredondaValor(magnitude));
      setAngulo(arredondaValor(angulo));
    }

    void geraESalvaFormaRetangular()
    {
      double parteReal = getMagnitude() * cos(getAngulo() * 180/PI);
      double parteImaginaria = getMagnitude() * sin(getAngulo() * 180/PI);

      setReal(arredondaValor(parteReal));
      setImaginario(arredondaValor(parteImaginaria));
    }

  /** Util */
  private:
    double verificaExcecoes(double valor)
    {
      if(isnanf(valor) || isinf(valor)) { return 0; }
      return valor;
    }

    double arredondaValor(double valor) { return (double)round(valor * 10000) / 10000; }

    string transformaResultadoParaFormaPolar(double parteReal, double parteImaginaria)
    {
      double divisaoImagReal = verificaExcecoes(getImaginario()/getReal());
      double angulo = atan(divisaoImagReal)* 180 / PI;
      double magnitude = sqrt(pow(parteReal, 2) + pow(parteImaginaria, 2));

      return to_string(arredondaValor(magnitude)) + " L " + to_string(arredondaValor(angulo));
    }

    string transformaResultadoParaFormaRetangular(double magnitude, double angulo)
    {
      double parteReal = magnitude * cos(angulo * PI/180);
      double parteImaginaria = magnitude * sin(angulo * PI/180);

      return to_string(arredondaValor(parteReal)) + " + " + (to_string(arredondaValor(parteImaginaria)) + "i");
    }

  /** Operacoes Matematicas */
  public:
    string soma(Complexo* parcela, Forma formaGerada)
    {
      double somaParteReal = getReal() + parcela->getReal();
      double somaParteImaginaria = getImaginario() + parcela->getImaginario();

      if(formaGerada == POLAR) { return transformaResultadoParaFormaPolar(somaParteReal, somaParteImaginaria); }

      string parteReal = to_string(arredondaValor(somaParteReal));
      string parteImaginaria = to_string(arredondaValor(somaParteImaginaria)) + "i";
      return parteReal + " + " + parteImaginaria;
    }

    string subtracao(Complexo* subtrativo, Forma formaGerada)
    {
      double subtracaoParteReal = getReal() - subtrativo->getReal();
      double subtracaoParteImaginaria = getImaginario() - subtrativo->getImaginario();

      if(formaGerada == POLAR) { return transformaResultadoParaFormaPolar(subtracaoParteReal, subtracaoParteImaginaria); }

      string parteImaginaria = to_string(arredondaValor(subtracaoParteImaginaria)) + "i";

      if(subtrativo->getImaginario() > getImaginario())
      {
        parteImaginaria = to_string(arredondaValor(subtracaoParteImaginaria) * -1) + "i";
        return to_string(arredondaValor(subtracaoParteReal)) + " - " + parteImaginaria;
      }

      return to_string(arredondaValor(subtracaoParteReal)) + " + " + parteImaginaria;
    }

    string multiplicacao(Complexo* fator, Forma formaGerada)
    {
      double magnitude = getMagnitude() * fator->getMagnitude();
      double angulo = getAngulo() + fator->getAngulo();

      if(formaGerada == RETANGULAR) { return transformaResultadoParaFormaRetangular(magnitude, angulo); }

      return to_string(arredondaValor(magnitude)) + " L " + to_string(arredondaValor(angulo));
    }

    string divisao(Complexo* divisor, Forma formaGerada)
    {
      double magnitude = verificaExcecoes(getMagnitude() / divisor->getMagnitude());
      double angulo = getAngulo() - divisor->getAngulo();

      if(formaGerada == RETANGULAR) { return transformaResultadoParaFormaRetangular(magnitude, angulo); }

      return to_string(arredondaValor(magnitude)) + " L " + to_string(arredondaValor(angulo));
    }

  /** Operacoes para comparar */
  private:
    int compararPorAngulo(Complexo* valor, string valorFormatado)
    {
      double divisaoImagRealA = verificaExcecoes(getImaginario()/getReal());
      double anguloA = atan(divisaoImagRealA)* 180 / PI;

      double divisaoImagRealB = verificaExcecoes(valor->getImaginario()/valor->getReal());
      double anguloB = atan(divisaoImagRealB)* 180 / PI;

      if(isgreater(anguloA, anguloB)) { return 1; }
      else if(isless(anguloA, anguloB)) { return -1; }
      else { return 0; }
  }

  public:
    int comparacao(Complexo* valor)
    {
      double magnitudeNumeroA = arredondaValor(sqrt(pow(getReal(), 2) + pow(getImaginario(), 2)));
      double magnitudeNumeroB = arredondaValor(sqrt(pow(valor->getReal(), 2) + pow(valor->getImaginario(), 2)));

      string valorFormatado = to_string(valor->getReal()) + " + " + (to_string(valor->getImaginario()) + "i");

      if(isgreater(magnitudeNumeroA, magnitudeNumeroB)) { return 1; }
      else if(isless(magnitudeNumeroA, magnitudeNumeroB)) { return -1; }
      else { return compararPorAngulo(valor, valorFormatado); }
    }
};

class MatrizComplexoAbstrata
{
  protected:
    int linhas = 1;
    int colunas = 1;
    Complexo **matrizNumerosComplexos;
    int indexDoObjeto = 0;

  /** Getter e Setter */
  public:
    int getLinhas() { return linhas; }

    int getColunas() { return colunas; }

    Complexo **getMatriz() { return matrizNumerosComplexos; }

  /** Util */
    void adicionarNumero(int linha, int coluna, Complexo *elemento)
    {
      if(linha<linhas && coluna<colunas)
      {
        matrizNumerosComplexos[linha][coluna]= *elemento;
      }
    }

    virtual void ordenar() = 0;

  protected:
    void geraMatriz()
    {
      matrizNumerosComplexos = new Complexo*[getLinhas()];
      for (int i = 0; i < getLinhas(); ++i) {
          matrizNumerosComplexos[i] = new Complexo[getColunas()];
      }
    }
};

class MatrizComplexoDerivada : public MatrizComplexoAbstrata, public Imprimivel, public Salvavel
{
  /** Construtores */
  public :
    MatrizComplexoDerivada(int index, int x, int y)
    {
      indexDoObjeto = index;
      linhas = x;
      colunas = y;
      geraMatriz();
    }

  /** Garbage collector */
    ~MatrizComplexoDerivada()
    {
      for (int i = 0; i < colunas; ++i)
      {
        delete [] matrizNumerosComplexos[i];
        delete [] matrizNumerosComplexos;
      }
    }

  /** Classes das interfaces */
    virtual void imprime()
    {
      for (int i = 0; i < getLinhas(); ++i)
      {
        for (int j = 0; j <  getColunas(); ++j)
        {
          Complexo ** gM = getMatriz();
          Complexo gM_= gM[i][j];
          cout << "linha=" <<  i << " / " << "coluna=" << j << endl;
          cout << "valor: " << gM_.getFormaRetangular() << endl;
        }
      }
    }

    virtual void salva()
    {
      cout << "Salvando matriz...\n" << endl;
      fstream myfile;

      string nomeDoArquivo = "matrizComplexo" + to_string(indexDoObjeto) + ".txt";

      myfile.open(nomeDoArquivo, ios::out);

      if(myfile.is_open())
      {
        for(int i = 0; i < getLinhas(); ++i)
        {
          for(int j = 0; j <  getColunas(); ++j)
          {
            Complexo ** gM = getMatriz();
            Complexo gM_= gM[i][j];
            myfile << gM_.getFormaRetangular() << endl;
          }
        }
      }
      else
      {
        cout << "ERRO: N�o foi possivel abrir o arquivo";
      };

      myfile.close();
    }

    virtual void carrega()
    {
      cout << "Carregando matriz...\n" << endl;

      int i = 0;
      string line;
      fstream myfile;
      string word[50];
      vector<Complexo*> numero;

      string nomeDoArquivo = "matrizComplexo" + to_string(indexDoObjeto) + ".txt";

      myfile.open(nomeDoArquivo, ios::in);

      if (myfile.is_open())
      {
        while(getline(myfile, line))
        {
          stringstream ss(line);
          while(getline(ss, line, '+'))
          {
            if (line != " ")
            {
              word[i]=line;
              i++;
            }
          }
        }
      }
      else
      {
        cout << "ERRO: N�o foi possivel abrir o arquivo.";
      }

      myfile.close();

      srand(time(NULL));

      for(int j = 0; j < 50; j++)
      {
        Complexo *numeroTemporario = new Complexo((rand() % 10 + 100), stod(word[j]), stod(word[j+1]));
        numero.push_back(numeroTemporario);
        j++;
      }

      for (int n = 0; n < getLinhas(); n++)
      {
        for (int p = 0; p < getColunas(); p++)
        {
          int k = n * getColunas() + p;
          adicionarNumero(n, p, numero[k]);
        }
      }
    }

    void  ordenar()
    {
      Complexo temp;

      for (int i = 0; i < getLinhas(); i++)
      {
        for (int j = 0; j < getColunas(); j++)
        {
          for (int l = 0; l < getLinhas(); l++)
          {
            for (int c = 0; c < getColunas(); c++)
            {
              if (matrizNumerosComplexos[i][j].comparacao(&matrizNumerosComplexos[l][c]) == 1)
              {
                temp = matrizNumerosComplexos[i][j];
                matrizNumerosComplexos[i][j] = matrizNumerosComplexos[l][c];
                matrizNumerosComplexos[l][c] = temp;
              }
            }
          }
        }
      }
    }
};

int main()
{
  srand(time(NULL));

  Complexo *numero1, *numero2;

  numero1 = new Complexo((rand() % 10 + 5), 1, 1);
  numero2 = new Complexo((rand() % 10), POLAR, 5, 25);

  numero1->salva();
  numero1->carrega();

  numero2->salva();
  numero2->carrega();

  MatrizComplexoDerivada* matriz = new MatrizComplexoDerivada((rand() % 10 + 10), 5, 5);

  matriz->adicionarNumero(1, 2, numero1);
  matriz->adicionarNumero(0, 1, numero2);

  matriz->salva();
  matriz->carrega();

  cout <<"\n**********************MATRIZ**********************"<< endl;
  cout <<"!Linhas: " << matriz->getLinhas() << endl;
  cout <<"!Colunas: " << matriz->getColunas() << endl;

  cout <<"\n**********************IMPRIME MATRIZ**********************"<< endl;
  matriz->imprime();

  cout <<"\n**********************ORDENA MATRIZ**********************"<< endl;
  matriz->ordenar();

  cout <<"\n**********************IMPRIME MATRIZ APOS ORDENAR**********************"<< endl;
  matriz->imprime();

  //"================OPERA��ES NUMEROS COMPLEXOS================"
  string somaRetangular = numero1->soma(numero2, RETANGULAR);
  string somaPolar = numero1->soma(numero2, POLAR);

  string subtracaoRetangular = numero1->subtracao(numero2, RETANGULAR);
  string subtracaoPolar = numero1->subtracao(numero2, POLAR);

  string divisaoRetangular = numero1->divisao(numero2, RETANGULAR);
  string divisaoPolar = numero1->divisao(numero2, POLAR);

  string multiplicacaoRetangular = numero1->multiplicacao(numero2, RETANGULAR);
  string multiplicacaoPolar = numero1->multiplicacao(numero2, POLAR);

  cout << "\n================NUMEROS COMPLEXOS================" << endl;
  numero1->imprime();
  numero2->imprime();

  cout << "\n================SOMA================" << endl;
  cout << "Soma retangular: " << somaRetangular << endl;
  cout << "Soma polar: " << somaPolar << endl;

  cout << "\n================SUBTRACAO================" << endl;
  cout << "Subtracao retangular: " << subtracaoRetangular << endl;
  cout << "Subtracao polar: " << subtracaoPolar << endl;

  cout << "\n================DIVISAO================" << endl;
  cout << "Divisao retangular: " << divisaoRetangular << endl;
  cout << "Divisao polar: " << divisaoPolar << endl;

  cout << "\n================MULTIPLICACAO================" << endl;
  cout << "Multiplicacao retangular: " << multiplicacaoRetangular << endl;
  cout << "Multiplicacao polar: " << multiplicacaoPolar << endl;

  cout <<"\n**********************delete MATRIZ**********************"<< endl;
  delete matriz;

  matriz->imprime();

  return 0;
}
