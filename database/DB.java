public class DB {

    public static User getStoredUser() {
        User user = null;

        Realm realm = Realm.getDefaultInstance();
        RealmResults<RealmUser> results = realm.allObjects(RealmUser.class);
        if(results.size() > 0) {
            RealmUser realmUser = results.first();
            user = new User(realmUser);
        }

        return user;
    }

    public static void removeStoredUser() {
        Realm realm = Realm.getDefaultInstance();
        realm.beginTransaction();
        Realm.getDefaultInstance().clear(RealmUser.class);
        realm.commitTransaction();
        removeStoredCustomer();
    }

    public static void storeUser(User user) {
        removeStoredUser();
        if(user != null) {
            RealmUser realmUser = new RealmUser(user);
            Realm realm = Realm.getDefaultInstance();
            realm.beginTransaction();
            realm.copyToRealm(realmUser);
            realm.commitTransaction();
        }
    }

    public static Customer getStoredCustomer() {
        Customer customer = null;

        Realm realm = Realm.getDefaultInstance();
        RealmResults<RealmCustomer> results = realm.allObjects(RealmCustomer.class);
        if(results.size() > 0) {
            RealmCustomer realmCustomer = results.first();
            customer = new Customer(realmCustomer);
        }

        return customer;
    }

    public static void removeStoredCustomer() {
        Realm realm = Realm.getDefaultInstance();
        realm.beginTransaction();
        Realm.getDefaultInstance().clear(RealmCustomer.class);
        realm.commitTransaction();
    }

    public static void storeCustomer(Customer customer) {
        removeStoredCustomer();
        if(customer != null) {
            RealmCustomer realmCustomer = new RealmCustomer(customer);
            Realm realm = Realm.getDefaultInstance();
            realm.beginTransaction();
            realm.copyToRealm(realmCustomer);
            realm.commitTransaction();
        }
    }

    public static List<Weighing> getWeighings() {
        List<Weighing> weighings = new ArrayList<Weighing>();

        Realm realm = Realm.getDefaultInstance();
        RealmResults<RealmWeighing> results = realm.allObjects(RealmWeighing.class);
        if(results.size() > 0) {
            for(int i = 0; i < results.size(); i++){
                RealmWeighing realmWeighing = results.get(i);
                weighings.add(new Weighing(realmWeighing));
            }
        }

        return weighings;
    }

    public static Weighing getLatestWeighing() {
        List<Weighing> weighings = getWeighings();
        Weighing weighing = null;
        if(weighings.size() > 0) {
            Collections.sort(weighings, new Comparator<Weighing>() {
                @Override
                public int compare(Weighing lhs, Weighing rhs) {
                    return rhs.getCreatedAt().compareTo(lhs.getCreatedAt());
                }
            });
            weighing = weighings.get(0);
        }

        return weighing;
    }

    public static void storeWeighing(Weighing weighing) {
        if(weighing != null) {
            RealmWeighing realmWeighing = new RealmWeighing(weighing);
            Realm realm = Realm.getDefaultInstance();
            realm.beginTransaction();
            realm.copyToRealmOrUpdate(realmWeighing);
            realm.commitTransaction();
        }
    }
}
