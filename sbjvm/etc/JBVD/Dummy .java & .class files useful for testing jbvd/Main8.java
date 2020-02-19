import java.io.*;

public class Main8 {
	
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
			catch(IOException e){
				System.out.println("IO Exception caught");
			}
			catch(Exception e){
				System.out.println("Exception caught");
			}
			finally{
				if(input != null){
					input.close();
				}
			}
    	}
}
