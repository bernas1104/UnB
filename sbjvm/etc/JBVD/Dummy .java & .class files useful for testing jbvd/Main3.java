import java.io.*;

public class Main3 {

       public static void main(String[] args) throws Exception{
	   
		InputStream input = null;
	   
		    try{
				input = new FileInputStream("c:\\data\\input-text.txt");
				int data = input.read();
			}
			catch(IOException e){
				System.out.println("Exception caught");
			}
			finally{
				input.close();
			}
    	}

}
