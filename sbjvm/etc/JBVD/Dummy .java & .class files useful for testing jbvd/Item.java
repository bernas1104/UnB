public class Item {
 
   private static int uniqueId = 1;
 
   private int itemId;
   private String itemName;
 
   public Item(String itemName)
   {
     this.itemName = itemName;
     itemId = uniqueId;
     uniqueId++;
   }
 }