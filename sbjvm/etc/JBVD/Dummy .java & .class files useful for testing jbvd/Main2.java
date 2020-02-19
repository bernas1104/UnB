import java.io.*;

public class Main2{
	
	private int integer;

       public static void main(String args) throws Exception{
	   
		InputStream input = null;
	   
		    try{
				String t = null;
				args="test";
				t = args;
				input = new FileInputStream("c:\\data\\input-text.txt");
				int data = input.read();
				while(data != -1) {
					data = input.read();
				}
			}
			catch(IOException e1){
				System.out.println("Exception caught");
			}
			finally{
				if(input != null){
					input.close();
				}
			}
    	}
}
