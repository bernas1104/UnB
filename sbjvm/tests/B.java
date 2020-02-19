public class B extends A {
    static C teste;
    public int stick;

    public B(){
        stick = 5;
    }

    public static void mimimi(){
        a = 2;
        b = 2.0;
        B testando = new B();
        hello();

        teste = new C();
        System.out.println(testando.stick);
    }
}