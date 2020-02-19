import java.io.*;

public class Main18 {
	public static void main(String[] args) throws Exception{
			int i=0;
			try{
				try {
                    		i=1;
                	      } catch (Exception e1) {
                    		System.out.println("Exception 1 caught");
                		}
				finally{
					System.out.println("finally 1");
				}

			}
			catch(Exception e){
				i=11;
			}
			finally{
				i=0;
			}
	}

}
