
package week9;

import java.util.ArrayList;

public class Library {

    // ============================================================
    // Fields
    // ============================================================

    // TODO: Complete this declaration 
    // This ArrayList will store all library items (e.g. Book, Movie)
    private ArrayList<LibraryItem> items = new ArrayList<>();

    // TODO: Create a variable nextId to act as a counter 
    //       to store the unique ID for each Book or Movie item
    static int nextId= 1;


    // ============================================================
    // Constructor
    // ============================================================

    public Library() {
        // Nothing special to do here yet
    }


    // ============================================================
    // Methods
    // ============================================================

    // TODO: Complete this method to add a new Book into the ArrayList
    // Steps:
    //  • Create a new Book using nextId, title, and author
    //  • Add it to the ArrayList
    //  • Increment nextId
    //  • Print a confirmation message
    
    // DONE
    public void addBook(String title, String author) {
        Book book = new Book(nextId++, title, author);
        
        
        // TODO: Add the Book to the ArrayList
        items.add(book);
        System.out.println("Added: " + book);
    }


    // TODO: Complete this method to list all items currently in the ArrayList
    // Steps:
    //  • If the list is empty, print "No items in the library."
    //  • Otherwise, loop through the ArrayList and print each item
    
    //DONE
    public void listItems() {
        if (items.isEmpty()) {
            System.out.println("No items in the library.");
            return;
        }

        for (LibraryItem item : items) {
            System.out.println(item);
        }
    }


    // ============================================================
    // Accessory
    // ============================================================

    // This method returns the ArrayList (used later for file I/O)
    public ArrayList<LibraryItem> getItems() {
        return items;
    }
}