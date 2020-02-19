public class SwitchTest {

    public static void main(String[] args) {
        int a = 10;
        double b = 9;

        b++;
        System.out.println(b);

        switch(a){
            case 1:
                b += 2;
                System.out.println("Hello, World i");
                break;
            case 10:
                System.out.println("Hello, World ii");
                break;
            case 100:
                // Prints "Hello, World" to the terminal window.
                a++;
                b += 7;
                System.out.println("Hello, World ii");
                break;
            case 1000:
                System.out.println("Hello, World iv");
                break;
            default:
                System.out.println("oh well");
        }
    }

}