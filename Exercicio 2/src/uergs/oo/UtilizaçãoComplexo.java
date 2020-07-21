package uergs.oo;

public class UtilizaçãoComplexo {
    public static void main(String[] args) {
        Complexo numero1 = new Complexo(1, 1);
        Complexo numero2 = new Complexo(Forma.POLAR,0, 0);

        System.out.println("\n============================================");
        System.out.println("[Numero1] Forma retangular: " + numero1.getFormaRetangular());
        System.out.println("[Numero1] Forma polar: " + numero1.getFormaPolar());

        System.out.println("\n[Numero2] Forma retangular: " + numero2.getFormaRetangular());
        System.out.println("[Numero2] Forma polar: " + numero2.getFormaPolar());

        System.out.println("\n============================================");
        String somaRetangular = numero1.soma(numero2, Forma.RETANGULAR);
        String somaPolar = numero1.soma(numero2, Forma.POLAR);
        System.out.println("Soma retangular: " + somaRetangular);
        System.out.println("Soma polar: " + somaPolar);

        System.out.println("\n============================================");
        String subtracaoRetangular = numero1.subtracao(numero2, Forma.RETANGULAR);
        String subtracaoPolar = numero1.subtracao(numero2, Forma.POLAR);
        System.out.println("Subtracao retangular: " + subtracaoRetangular);
        System.out.println("Subtracao polar: " + subtracaoPolar);

        System.out.println("\n============================================");
        String divisaoRetangular = numero1.divisao(numero2, Forma.RETANGULAR);
        String divisaoPolar = numero1.divisao(numero2, Forma.POLAR);
        System.out.println("Divisao retangular: " + divisaoRetangular);
        System.out.println("Divisao polar: " + divisaoPolar);

        System.out.println("\n============================================");
        String multiplicacaoRetangular = numero1.multiplicacao(numero2, Forma.RETANGULAR);
        String multiplicacaoPolar = numero1.multiplicacao(numero2, Forma.POLAR);
        System.out.println("Multiplicacao retangular: " + multiplicacaoRetangular);
        System.out.println("Multiplicacao polar: " + multiplicacaoPolar);

        System.out.println("\n============================================");
        String comparacaoA = numero1.comparacao(numero2);
        System.out.println("[Numero1] Comparação: " + comparacaoA);

        String comparacaoB = numero2.comparacao(numero1);
        System.out.println("[Numero2] Comparação: " + comparacaoB);
    }
}
