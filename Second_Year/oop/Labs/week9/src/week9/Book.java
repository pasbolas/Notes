package week9;

public class Book extends LibraryItem implements Borrowable{
	
	String author;
	boolean borrowed_status;
	String Borrower_Name;
	
	public Book(int ID, String TITLE, String author) {
		super(ID, TITLE);
		this.author = author;
		this.borrowed_status = false;
	}
	
	public void borrow(String borrower) {
		if (this.borrowed_status == false)
		{
			this.Borrower_Name = borrower;
			this.borrowed_status = true;
			System.out.println("book is borrowed");
		} else {
			System.out.println("book cannot be borrowed");
		}
	}
	
	public void giveBack() {
		if (borrowed_status) {
			this.borrowed_status = false;
			this.Borrower_Name = "";
			System.out.println("book is borrowed returned");
		}
		else {
			System.out.println("book cannot be returned");
		}
	}
	
	public boolean isBorrowed() {
		if (this.borrowed_status) {
			return true;
		}
		else {
			return false;
		}
	}
	
	public String toString() {
		return ("Book["+ super.getId() +"] " + super.getTitle() + " " + author + " ( Borrowed by " + Borrower_Name + " )");
	}
	
	public String toDataString() {
		// Format: BOOK;id;title;author;borrowed;borrowerName
		return "BOOK;" + getId() + ";" + getTitle() + ";" + author + ";" + borrowed_status + ";" + Borrower_Name;
	}
	
	public void SingleString() {};
}
