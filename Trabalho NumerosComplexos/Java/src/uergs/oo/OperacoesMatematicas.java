package uergs.oo;

public interface OperacoesMatematicas {

    String soma(Complexo parcela, Forma formaGerada);
    String subtracao(Complexo subtrativo, Forma formaGerada);
    String multiplicacao(Complexo fator, Forma formaGerada);
    String divisao(Complexo divisor, Forma formaGerada);
    String comparacao(Complexo valor);
}
