package client;

public class Main {

       public static void main(String[] args) {
            for (int i = 1; i < 1000; i ++) {
            	Runnable c = new Client("127.0.0.1", 12000);
            	Thread t = new Thread(c);
            	t.start();
        	}
    	}

}
