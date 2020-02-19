import java.io.*;

public class Main11 {
	public static void main(String[] args) throws Exception{
			int i=0;
			try{
				i=10;
			}
			catch(Exception e){
				i=11;
			}
			finally{
				i=0;
				try {
					System.out.println("try");
				}
                		catch (Exception e1) {
                    		System.out.println("Exception caught");
                		}
				finally{
					System.out.println("finally");
				}

			}
	}

}
