package week9;

public interface Borrowable {
	void borrow(String Borrower);
	void giveBack();
	boolean isBorrowed();
}
