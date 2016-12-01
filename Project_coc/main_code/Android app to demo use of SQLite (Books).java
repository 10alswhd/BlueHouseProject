import android.os.Bundle;
import android.support.v7.app.ActionBarActivity;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import java.util.ArrayList;
import java.util.List;


public class MainActivity extends ActionBarActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // get DB from helper class
        MySQLiteHelper db = new MySQLiteHelper(this);

        // clean table to start with
        db.deleteAllBooks();

        // add Books
        db.addBook(new Book("Android Application Development Cookbook", "Wei Meng Lee"));
        db.addBook(new Book("Android Programming: The Big Nerd Ranch Guide", "Bill Phillips and Brian Hardy"));
        db.addBook(new Book("Learn Android App Development", "Wallace Jackson"));

        // get all books
        List<Book> list = db.getAllBooks();

        // update book
        Book secondBook = db.getBook(list.get(1).getId());
        secondBook.setAuthor("Bosse");
        db.updateBook(secondBook);

        // delete book
        Book thirdBook = db.getBook(list.get(2).getId());
        db.deleteBook(thirdBook);

        // get all books
        list = db.getAllBooks();

        // without a custom adapter we need a list of strings
        ArrayList<String> books = new ArrayList<String>();
        for(Book book : list){
            books.add(book.getTitle() + " by " + book.getAuthor());
        }

        // show all books in a ListView
        ListView listView = (ListView) findViewById(R.id.listView);
        ArrayAdapter<String> adapter = new ArrayAdapter<String>(
                this,
                android.R.layout.simple_list_item_1,
                books
        );
        listView.setAdapter(adapter);
    }
}
