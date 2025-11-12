package week9;

import java.util.ArrayList;

public class LibraryApp {
    public static void main(String[] args) {

        // ============================================================
        // TODO 1: Create a Library object 
        //
        // ============================================================
    	Library newlibrary = new Library();

        // ============================================================
        // TODO 2: Library object has an ArrayList. 
    	// Add three books using the Library’s addBook() method
    	
    	newlibrary.addBook("Harry Potter", "Albert Einstein");
    	newlibrary.addBook("Harry Potter 2", "Nicola Tesla");
    	newlibrary.addBook("Harry Potter 3", "Stephen Hawkings");
    	
    	
    	 //What do you pass into the method
        // 
        // ============================================================


        // ============================================================
        // TODO 3: Display all books currently stored in the ArrayList
        // Use library.listItems();
        // ============================================================
        System.out.println("\nListing all items:");
        newlibrary.listItems();


       
         ArrayList<LibraryItem> items = newlibrary.getItems();
         System.out.println("\nThere are currently " + items.size() + " items in the ArrayList.");


        // ============================================================
        // TODO 5: Demonstrate Borrowable behaviour on the first item
        // Steps:
        //  • Check that the list is not empty
        //  • Get the first item from the ArrayList
        //  • Use instanceof to check if it implements Borrowable
        //  • Cast it and call borrow() and giveBack() to test behaviour
        // ============================================================
        
        if (!items.isEmpty()) {
            LibraryItem first = items.get(0);
            if (first instanceof Borrowable) {
                Borrowable b = (Borrowable) first;
                System.out.println("\nBorrowing and returning the first book:");
                b.borrow("Alice");
                System.out.println(first);
                b.giveBack();
                System.out.println(first);
            }
        }
        
    }
}