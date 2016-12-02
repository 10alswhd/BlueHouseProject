import java.util.List;
import java.util.ArrayList;

/**
 * Temporal DB class.
 * 
 * @author Francisco.Carriedo
 * May 16, 2012
 */
public class DB {
  private boolean debug = true;
  private List<Prod> productList = new ArrayList<Prod>();
  private List<ProdGroup> productGroupList = new ArrayList<ProdGroup>();
  private List<Categ> categoryList = new ArrayList<Categ>();

  public DB() {
    init();
  }

  private void init() { // Init with some data
    // Create all products.
    for (int i = 0; i < 3; i++)
      productList.add(new Prod(i, "Prod " + i));

    // Create the product groups
    productGroupList.add(new ProdGroup(1, "Group 1", Arrays.asList(productList.get(0), productList.get(1))));
    productGroupList.add(new ProdGroup(2, "Group 2", Arrays.asList(productList.get(1), productList.get(2))));

    // Create existing categories.
    for (int i = 0; i < 3; i++)
      // Just adding the first two products to every category.
      categoryList.add(new Categ(i, "Category " + i, Arrays.asList(productList.get(0), productList.get(1))));

  }

  @SuppressWarnings("unchecked")
  public <T> List<T> findAll(Class<T> clazz) {
    if(clazz.isAssignableFrom(Prod.class)) return (List<T>)productList;
    else if(clazz.isAssignableFrom(ProdGroup.class)) return (List<T>)productGroupList;
    else if(clazz.isAssignableFrom(Categ.class)) return (List<T>)categoryList;

    return null;
  }

  @SuppressWarnings("unchecked")
  public <T> T find(long id, Class<T> clazz) {
    if(clazz.isAssignableFrom(Prod.class)){
      for(Prod p : productList) if(p.getId() == id) return (T) p;
    } else if(clazz.isAssignableFrom(ProdGroup.class)) {
      for(ProdGroup pg : productGroupList) if(pg.getId() == id) return (T) pg;
    } else if(clazz.isAssignableFrom(Categ.class)) {
      for(Categ c : categoryList) if(c.getId() == id) return (T) c;
    }

    return null;
  }

  public <U> U add(U obj) {
    if(obj == null) return obj;
    Class<?> clazz = obj.getClass();
    if(clazz.isAssignableFrom(Prod.class)){
      Prod prod = (Prod)obj;
      prod.setId(productList.get(productList.size()-1).getId() + 1); // The next sequential id.
      productList.add(prod);
    } else if(clazz.isAssignableFrom(ProdGroup.class)){
      ProdGroup prodGroup = (ProdGroup)obj;
      prodGroup.setId(productGroupList.get(productGroupList.size()-1).getId() + 1); // The next sequential id.
      productGroupList.add(prodGroup);
    } else if(clazz.isAssignableFrom(Categ.class)){
      Categ categ = (Categ)obj;
      categ.setId(categoryList.get(categoryList.size()-1).getId() + 1); // The next sequential id.
      categoryList.add(categ);
    }

    return obj;
  }	

  public <U> U update(U obj) {
    if(obj == null) return obj;
    Class<?> clazz = obj.getClass();
    if(clazz.isAssignableFrom(Prod.class)){
      Prod prod = (Prod)obj;
      for(int i=0; i<productList.size(); i++) {
        if(productList.get(i).getId() == prod.getId()) {
          productList.set(i, prod); break;
        }
      }
    } else if(clazz.isAssignableFrom(ProdGroup.class)) {
      ProdGroup prodGroup = (ProdGroup)obj;
      for(int i=0; i<productGroupList.size(); i++) {
        if(productGroupList.get(i).getId() == prodGroup.getId()) {
          productGroupList.set(i, prodGroup); break;
        }
      }
    } else if(clazz.isAssignableFrom(Categ.class)) {
      Categ categ = (Categ)obj;
      for(int i=0; i<categoryList.size(); i++) {
        if(categoryList.get(i).getId() == categ.getId()) {
          categoryList.set(i, categ); break;
        }
      }
    }

    return obj;
  }

  public <U> U delete(U obj) {
    if(obj == null) return obj;
    Class<?> clazz = obj.getClass();
    if(clazz.isAssignableFrom(Prod.class)){
      Prod prod = (Prod)obj;
      productList.remove(prod);
    } else if(clazz.isAssignableFrom(ProdGroup.class)){
      ProdGroup prodGroup = (ProdGroup)obj;
      productGroupList.remove(prodGroup);
    } else if(clazz.isAssignableFrom(Categ.class)){
      Categ categ = (Categ)obj;
      categoryList.remove(categ);
    }

    return obj;
  }

  public void dumpToStdOut() {
    if(debug) {
      System.out.println("===============================");
      System.out.println("Products========");
      for(Prod prod : productList) System.out.println(prod);
      System.out.println("ProductGroups===");
      for(ProdGroup prodGroup : productGroupList) System.out.println(prodGroup);
      System.out.println("Categories======");
      for(Categ categ : categoryList) System.out.println(categ);
      System.out.println("===============================");
    }
  }
}
