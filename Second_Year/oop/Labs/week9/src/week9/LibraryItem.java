package week9;

public abstract class LibraryItem {
	
	public LibraryItem(int ID, String TITLE) 
	{
		setId(ID);
		setTitle(TITLE);
	}
	
	private int id;
	private String title;
	
	

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public String getTitle() {
		return title;
	}

	public void setTitle(String title) {
		this.title = title;
	}
	
	
	public abstract void SingleString();
}
